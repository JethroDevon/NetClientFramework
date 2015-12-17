#include "ImageLoader.h"

//the only constructor simply assigns a pointer to an image with an image in order to
//return an error, pointer is destroyed in vector
ImageLoader::ImageLoader(std::string _path): errorImage(image){


    if(image.loadFromFile( _path)){

        //debug :output successful initialisation into console, is also good
        //to output expensive computations in order to see what could be jamming
        //std::cout<<"Image Loader successfully initialised"<<std::endl;
    }else{

        //if the default image is not found at the right path then something is wrong
         std::cout<<"default error image not found at path! "<<std::endl;
    }
}






ImageLoader::~ImageLoader(){

    //delete errorImage;
}







 //if image at _path in args is found in directory but not within the  map
 //this function still returns a pointer to that image and then adds it to the map
 //if the path could not load an error image initialised in args is returned instead
sf::Image & ImageLoader::getImage(std::string _path){

    for (  auto & img : imageMap ) {

        if(img.first == _path){

           return img.second;
        }
    }

    //creating temporary image
    sf::Image image;

    //at this point if an image has not been returned then a key value pair is
    //added to imageMap consisting of the path and the image, finally a recursive call is made.
    if(image.loadFromFile( _path)){

        //debug: output successful initialisation into console, is also good
        //to output expensive computations in order to see what could be jamming
        //std::cout<<"Image Loader recursively initialised"<<std::endl;

        //setting key value pair
        imageMap[_path] = image;
        return getImage( _path);
    }else{

        //the image has failed and a temporary error image is return to avoid a crash and to help
        //debug the cause of an image not loading
        std::cout<<"Image at "<<_path<<" not found, using default error image for debugging!"<<std::endl;
        return errorImage;
    }
};
