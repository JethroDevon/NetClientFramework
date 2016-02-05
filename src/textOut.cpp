#include "textOut.h"

textOut::textOut(int _x, int _y, int _w, int _h, sf::RenderWindow &_rw): Sprites(_rw, "media/cb.png"){

    //set x y and width of box heights set at 30 for now
    setXY( _x, _y);
    setWH(_w, _h);

    //initialises all rectangles that will make up the box to draw in
    setRects();
}

//initialises rectangles in the text box to be drawn
void textOut::setRects(){

     //set up colours of text input box
    box.setFillColor(sf::Color::White);
    box.setOutlineColor(sf::Color::Black);
    box.setOutlineThickness(1);

    //position set to draw
    box.setPosition(sf::Vector2f(getPosX(), getPosY()));

    //size is set to a standard, may add a scrolling
    //text field if text is too big later
    box.setSize(sf::Vector2f(getWidth(), getHeight()));
}

//adds a string to the text array
void textOut::addString(std::string _string){

    //if a new line character is found
    std::size_t found = _string.find('\n');

    //break up the string, its likely the strings will be broken up by newlines before
    //but there's no harm in handling it, std::string::npos is used with size_t to return unsigned -1
    if (found != std::string::npos){

        //recursively calls this function with
        //rest of string after newline char in as args
        addString(_string.substr(found));

        //argument is now initialised with string before the newline character
        _string = _string.substr(0,found);
    }

    //creates a text graphic assigns a font and colour and size
    sf::Text temp;
    temp.setFont(font);
    temp.setString(_string);
    temp.setColor(sf::Color::Black);
    temp.setCharacterSize(fontSize);

    //check that text objects length, it has to be shorter than the text box if not break it up and
    //recursively call the remaining part in this function with getString member function belonging to text
    for(){

    }


    //pushes that text through to the vector
    boxText.push_back(temp);
}

//draws the box with the text in and slider for
//scrolling through text
void textOut::drawBox(){

    rw.draw(box);
}

//changes font to path in args
void textOut::changeFont(std::string _path){

    //sets font from path path else outputs warning to console
    if (!font.loadFromFile(_path)){

        std::cout<<"Likely name of font incorrect";
    }
}

//setter and getter for font size
void textOut::setFontSize(int _s){

    fontSize = _s;
}

//setter and getter for font size
int textOut::getFontSize(){

    return fontSize;
}


