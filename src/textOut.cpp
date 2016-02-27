#include "textOut.h"

//xpos ypos, width, height, font size and render window to pass drawing to
textOut::textOut(int _x, int _y, int _w, int _h, int _fontSize, sf::RenderWindow &_rw): Sprites(_rw, "media/cb.bmp"){

    //sets font size
    setFontSize(_fontSize);

    //sets default font
    changeFont("media/pink_bunny/pink bunny.ttf");

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
        //rest of string after newline char in as args <- might stack backwards so keep end string and pass last /n to end of string
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

    //check that text objects length, if it fits in the box add it to the text array as is
    if(temp.getGlobalBounds().width < getWidth()){

        //pushes that text through to the vector
        insertSFText(temp);

        //else break a piece off starting from the back of the text from that long string, the length is derived from how many times the graphical text
        //is too big for the display box divided by the number of characters in the actual string, then recursively
        //call this function again with the remaining amount of text in it, taking it from the back stacks the boxText graphical text array up in the right order
    }else{

            //the split index is the point of the string to break the text off from
            int splitIndex = _string.length()/(temp.getLocalBounds().width / getWidth() + 1);

            temp.setString(_string.substr(0, splitIndex));
            insertSFText(temp);

            addString(_string.substr(splitIndex));
    }
}

void textOut::insertSFText(sf::Text _text){

    //creates an iterator for the front of the vector boxText
    std::vector<sf::Text>::iterator it;
    it = boxText.begin();
    boxText.insert ( it , _text);
}

//draws the box with text and slider for scrolling through it
void textOut::drawBox(){

    //draws the rectangle representing the box
    rw.draw(box);

    //if there is text in boxText then draw it
    if(boxText.size() != 0){

        for(int pos = 0; pos < boxText.size() ; pos++){

            //sets position to draw each sf::text object based on the dimensions
            //of the text box and the position the object is in in the array 'boxText'
            boxText.at(pos).setPosition(getPosX() + 5, getPosY() + getHeight() -  (getFontSize() * (pos + 2)));

            if( boxText.at(pos).getPosition().y > getPosY())
                rw.draw( boxText.at(pos));
        }
    }
}

//
void textOut::setLinePos(){

}

//changes font to path in args
void textOut::changeFont(std::string _path){

    //sets font from path path else outputs warning to console
    if (!font.loadFromFile(_path)){

        std::cout<<"Likely name of font incorrect"<<std::endl;
    }else{

        std::cout<<"Font loaded successfully"<<std::endl;
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


