#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>

class ImageLoader{
    public:
        ImageLoader(std::string);
        virtual ~ImageLoader();

        //returns a pointer to an image named in args, if path has not been loaded before
        //the image is put on an image vector for future use and a pointer to it is still returned
        //could be a seen as both a setter and getter.
        sf::Image & getImage(std::string);

    private:

        std::map<std::string, sf::Image> imageMap;

        //error image is initialised in constructor and returned to show a bad image was loaded
        sf::Image &errorImage;

        sf::Image image;
};

#endif // IMAGELOADER_H
