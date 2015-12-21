#include "textIn.h"

///TO-DO: make sure that nothing is drawn till highlighted, put everything exlude operations as well as drawring caret

//constructor with button object initialised in initialiser list
textIn::textIn(std::string _name, std::string _initText, int _x, int _y, int _width, bool _withButton, sf::RenderWindow & _rw): name( _name), initText( _initText),
    xpos( _x), ypos( _y), boxWidth( _width), withButton( _withButton), rw(_rw), sendButton(_x, _y, _width, 40, "Send", rw){

    //selected is default false
    selected = false;

    setCaret(xpos, ypos, 30);

    if (!font.loadFromFile("media/openSans-Bold.ttf")){

        std::cout<<"Error loading font for text field object.";
    }

    //updates time passed since program started
    startTime = std::clock();

    setRects();
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
    rectangle.setSize(sf::Vector2f(getWidth(), 30));
}

void textIn::setCaret(int _x, int _y, int _length){

    caret.setPosition(sf::Vector2f(_x, _y));
    caret.setFillColor(sf::Color::Red);
    caret.setSize(sf::Vector2f(1,_length));

    //updates carets position for collision detection
    caretX = _x;
    caretY = _y;
}

void textIn::drawCaret(){

    if(!getTicks(2) && selected){

        rw.draw(caret);
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

    //collisions with the mouse in the rectangle
    if(position.x > getXpos() && position.x < getXpos() + getWidth() &&  position.y > getYpos() && position.y < getYpos() + 50){

        return true;
    }else{

        return false;
    }
}

//listen for clicks if mouse is over
void textIn::mouseListen(){

    // left mouse button is pressed and mouse is over button
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mouseOver()){

        //if mouse is over the rectangle when clicked selected is set to true
        if(!selected){

            setSelected(true);
        }else{

            setSelected(false);
        }
    }
}

 //listens to key presses when selected, records all keyboard input
void textIn::keyListen(sf::Event &event){

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){

        setCaret(text.at(textIndex()).getPosition().x - 1, ypos, 30);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){

         setCaret(text.at(textIndex()).getPosition().x + text.at(textIndex()).getLocalBounds().width, ypos, 30);
    }

    //this is not key pressed event at all this is textEntered its entirely different
    if (event.type == sf::Event::TextEntered){

        if (event.text.unicode < 128){

            //check if key pressed is the same as the last one
            if(lastKey == event.text.unicode ){

                //if .6 of a second has passed
                if(getTicks(0.6)){

                    //add or insert a character
                    if(textIndex() == (text.size() -1) ){

                        addChar(event.text.unicode);
                    }else{

                        text.erase(text.begin() + textIndex()-1);
                    };
                }
            }if( 8 == event.text.unicode){

                    //remove a char at end of string or remove a char in middle
                    if(textIndex() == (text.size() -1) ){

                        removeChar();
                    }else{

                        removeChar(textIndex());
                    };
            }else if(textIndex() == (text.size() -1) ){

                addChar(event.text.unicode);
                lastKey = event.text.unicode;
            }else{

                insertChar(textIndex(), event.text.unicode);
                lastKey = event.text.unicode;
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
    for(auto &t: text){

        //deals with difficult spacebar character by ignoring him
        if(t.getString() != '_'){

            rw.draw(t);
        }
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

void textIn::insertChar( int _i, int _c){

    //no point inserting text if there's no text
    if(text.size() > 2){

        //creates an iterator for text vector assigned from arg 1
        auto it = text.begin();

        //creates a text graphic assigns a font and colour and size and pushes it to back of text vector
        sf::Text temp;
        temp.setFont(font);
        temp.setColor(sf::Color::Black);
        temp.setCharacterSize(23);

        //if char to insert is pesky spacebar character...
        if(_c == 32){

            //...then replace it with an underscore
            temp.setString("_");
        }else{

            temp.setString( static_cast<char>(_c));
        }

        //insert the text in the vector at index using the iterator
        text.insert(it + _i, temp);
        text.at(_i).setPosition((text.at(_i -1).getPosition().x + text.at(_i -1).getLocalBounds().width) , ypos);

        //iterates all text in front of inserted text to be drawn in front of the char before it (shimmies all the other letters along)
        for(int x = _i; x < text.size(); x++){

            text.at(x).setPosition((text.at(x -1).getPosition().x + text.at(x -1).getLocalBounds().width) , ypos);
        }
    }
}

//adds a character to the text array
void textIn::addChar(int _c){

    //creates a text graphic assigns a font and colour and size and pushes it to back of text vector
    sf::Text temp;
    temp.setFont(font);
    temp.setString( static_cast<char>(_c));
    temp.setColor(sf::Color::Black);
    temp.setCharacterSize(25);
    text.push_back(temp);

    if(_c == 32){

        text.back().setString("_");
    }

    //if it is the first in the array set the position of the first character to be within the start of the text box
    if(text.size() == 1){

        text.at(0).setPosition(xpos, ypos);
    }else{

        //this puts the char in args after the previous char in the array
        text.back().setPosition(text.end()[-2].getPosition().x + text.end()[-2].getLocalBounds().width , ypos);
    }

    //moves caret across
    setCaret( text.back().getPosition().x + text.back().getLocalBounds().width, ypos, 30);
}

//removes last character
void textIn::removeChar(){

    if(text.size() > 0){

        text.pop_back();

        //moves caret back
        setCaret( text.back().getPosition().x + text.back().getLocalBounds().width, ypos, 30);
    }else{

        //if the text array is empty then return the caret to start
        setCaret( xpos + 5, ypos, 30);
    }
}

//removes char from position in args and changes subsequent objects to be drawn properly
void textIn::removeChar(int _i){

    text.erase(text.begin() + _i);

    //iterates all text in front of inserted text to be drawn in front of the char before it (shimmies all the other letters along)
    for(int x = _i; x < text.size(); x++){

        text.at(x).setPosition((text.at(x -1).getPosition().x + text.at(x -1).getLocalBounds().width) , ypos);
    }
}

//gets text from the text graphics vector and deals with space bar
std::string textIn::getText(){

    std::string temp;
    for( auto t: text){

        //add each char of text to string on the condition that the text is not the troublesome spacebar
        if(t.getString() != '_'){

            temp += t.getString();
        }else{

            //adds an actual space to avoid issues
            temp += ' ';
        }
    }

    return temp;
}

//this function returns the index number of the text sf::object the caret is colliding with
int textIn::textIndex(){

    if( text.size() > 1){

        for(int c = 0; c < text.size(); c++){

            if(caretX +1 > text.at(c).getPosition().x && caretX  < text.at(c).getPosition().x + text.at(c).getLocalBounds().width &&
               caretY +1 > text.at(c).getPosition().y && caretY < text.at(c).getPosition().y + text.at(c).getLocalBounds().height){

                return c;
            }
        }
    }

    //else return second to last
    return text.size()-1;
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
