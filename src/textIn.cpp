#include "textIn.h"

///TO-DO: YOU WANT YOUR TEXT FIELD TO ACTUALLY BE A VECTOR OF CHARS! WHY? SO YOU CAN USE THE CARET TO SELECT AREAS TO INSERT TEXT!!!
///overly complicated for what I have in mind but will be working as it is supposed to



//constructor with button object initialised in initialiser list
textIn::textIn(std::string _name, std::string _initText, int _x, int _y, int _width, bool _withButton, sf::RenderWindow & _rw): name( _name), initText( _initText),
    xpos( _x), ypos( _y), boxWidth( _width), withButton( _withButton), rw(_rw), sendButton(_x, _y, _width, 40, "Send", rw){


    //updates time passed since program started
    startTime = std::clock();
}

//prepares rectangle to be drawn to create a text field
void textIn::setRects(){

    //set up colours of text input box
    rectangle.setFillColor(sf::Color::White);
    rectangle.setOutlineColor(sf::Color::Black);
    rectangle.setOutlineThickness(1);

    //position set to draw
    rectangle.setPosition(sf::Vector2f(xpos, ypos));

    //size is set to a standard, may add a scrolling
    //text field if text is too big later
    rectangle.setSize(sf::Vector2f(50, getWidth()));
}

void textIn::setCaret(int _x, int _y, int _length){

     sf::Vertex caret[] = {sf::Vertex(sf::Vector2f( _x, _y)), sf::Vertex(sf::Vector2f( _x, _y + _length))};
}

void textIn::drawCaret(){

    if(getTicks(1)){

        rw.draw(caret, 2, sf::Lines);
    }
}

//returns string to send text on
std::string textIn::send(){

    return name;
}

//returns state of boolean 'selected'
bool textIn::getSelected(){

    return selected;
}

//if mouse collides with text in box return true else false
bool textIn::mouseOver(){

    //get mouse position
    position = sf::Mouse::getPosition(rw);

    if(position.x > getXpos() && position.x < getXpos() + getWidth() &&  position.y > getYpos() && position.y < getYpos() + 50){

        return true;
    }else{

        return false;
    }
}

//listen for clicks if mouse is over
void TextIn::mouseListen(){

    // left mouse button is pressed and mouse is over button
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mouseOver()){

        if(!selected){

            setSelected(true);
        }else{

            setSelected(false);
        }
    }
}

 //listens to key presses when selected, records all keyboard input
void textIn::keyListen(sf::Event &event){

    //if the box has been selected with a mouse click
    if(selected){
        if (event.type == sf::Event::KeyPressed){
            if (event.key.code == sf::Keyboard::BackSpace){

                removeChar();

            }else if (event.key.code == sf::Keyboard::Delete){

                std::cout<<" implement delete function later"<<std::endl;
            }
        }

        //this is not key pressed event at all this is textEntered its entirely different
        if (event.type == sf::Event::TextEntered){

            if (event.text.unicode < 128){

                addChar(static_cast<char>(event.text.unicode));
            }
        }
    }
}

//displays the box to draw text in
void textIn::drawText(){

    //when called listens for mouse changes
    mouseListen();

    //draws background rectangle
    rw.draw(rectangle);

    //loops through each char in the sf::Text array drawring each one
    for(auto t: text){

        rw.draw(t);
    }

    //draws the blinking caret
    drawCaret();
}

//this function returns true if double in args has passed since hte last time the function was called or the start of the program
bool textIn::getTicks(double ticksPassed){

    //updates ticks and returns true if time in args has passed
    if(((std::clock() - startTime) /(double) CLOCKS_PER_SEC) > ticksPassed){

        startTime = std::clock();
        return true;
    //returns false if time has not passed
    }else{

        return false;
    }
}

void textIn::addChar(char _c){

    sf::Text temp;
    temp.setString(_c);
    text.push_back(temp);

    //if it is the first in the erray set the position of the first character to be within the start of the text box
    if(text.size() == 1){

        text.at(1).setPosition(xpos, ypos);
    }else{

        //this puts the char in args after the previous char in the array
        text.back().setPosition(xpos + text.end()[-2].getPosition().x, ypos);
    }

    setCaret(text.back().getPosition().x, 2 + ypos, 30);
}

void textIn::removeChar(){

    if(text.size() < 0){

        text.pop_back();
    }
}

std::string textIn::getText(){

    std::string temp;
    for( int t = text.size(); t > 0; t--){

        temp += text.back().getString();
        text.pop_back();
    }

    return temp;
}

//sets state of boolean 'selected'
void textIn::setSelected(bool _s){

    selected = _s;
}

//get integer private variables for id number if set and xpos and ypos
int textIn::getXpos(){

    return xpos;
}

int textIn::getYpos(){

    return ypos;
}

int textIn::getWidth(){

    return boxWidth;
}

int textIn::getID(){

    return ID;
}

//sets an id number for text box
void textIn::setID(int _id){

    ID = _id;
}
