#include "textIn.h"

///TO-DO: make sure that nothing is drawn till highlighted, put everything exclude operations as well as drawing caret

//constructor with button object initialised in initialiser list
textIn::textIn(std::string _name, std::string _initText, int _x, int _y, int _width, bool _withButton, sf::RenderWindow &_rw): name( _name), initText( _initText),
    withButton( _withButton), Sprites(_rw, "media/cb.bmp") {

    //selected is default false
    setSelected(false);

    setXY( _x, _y);
    setWH(_width, 30);

    setCaret(_x, _y, 30);

    if (!font.loadFromFile("media/openSans-Bold.ttf")){

        std::cout<<"Error loading font for text field object.";
    }

    setRects();
}

//prepares rectangle to be drawn to create a text field
void textIn::setRects(){

    //set up colours of text input box
    rectangle.setFillColor(sf::Color::White);
    rectangle.setOutlineColor(sf::Color::Black);
    rectangle.setOutlineThickness(1);

    //position set to draw
    rectangle.setPosition(sf::Vector2f(getPosX(), getPosY()));

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

    if(!getTicks(2) && getSelected()){

        rw.draw(caret);
    }
}

//returns string to send text on
std::string textIn::send(){

    return name;
}

 //listens to key presses when selected, records all keyboard input
void textIn::keyListen(sf::Event &e){

    //if htere are any text objects to cycle through
    if(text.size() != 0){

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){

            setCaret(text.at(textIndex()-1).getPosition().x + text.at(textIndex()).getLocalBounds().width + 1, getPosY(), 30);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){

             setCaret(text.at(textIndex()+1).getPosition().x + text.at(textIndex()).getLocalBounds().width + 1, getPosY(), 30);
        }
    }

    //this is not key pressed event at all this is textEntered its entirely different
    if (e.type == sf::Event::TextEntered){

        if (e.text.unicode < 128 && getSelected()){

             //if the same key as the last one was pressed not too recently
            if(lastKey == e.text.unicode ){

                //if a second has passed
                if(getTicks(1)){


                    //if the caret is next to the front most text object append text to the front of the vector else
                    //insert the character to the point where the caret is colliding
                    if(text.size() == 0 || caretX > (text.back().getPosition().x + text.back().getLocalBounds().width) - 10){

                        addChar(e.text.unicode);
                    }else{

                        insertChar( textIndex(), e.text.unicode);
                    }
                }
             //if backspace has been hit
            }if( 8 == e.text.unicode){

                    //if the caret is next to the front most text object remove the front most object with remove char
                    //else remove the character at the point where the caret is colliding
                    if( text.size() == 0 || caretX > (text.back().getPosition().x + text.back().getLocalBounds().width) - 10){

                        removeChar();
                    }else{

                        removeChar(textIndex());
                    };
             //if the caret is next to the front most text object append text to the front of the vector else
            //insert the character to the point where the caret is colliding
            }else if(text.size() == 0 || caretX > (text.back().getPosition().x + text.back().getLocalBounds().width)  - 10)  {

                addChar(e.text.unicode);
                lastKey = e.text.unicode;
            }else{

                insertChar(textIndex(), e.text.unicode);
                lastKey = e.text.unicode;
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

    //loops through each char in the sf::Text array drawing each one
    for(auto &t: text){

        //deals with difficult space bar character by ignoring him
        if(t.getString() != '_'){

            rw.draw(t);
        }
    }

    //draws the blinking caret
    drawCaret();
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
        temp.setCharacterSize(25);

        //if char to insert is pesky spacebar character...
        if(_c == 32){

            //...then replace it with an underscore
            temp.setString("_");
        }else{

            temp.setString( static_cast<char>(_c));
        }

        //insert the text in the vector at index using the iterator
        text.insert(it + _i, temp);
        text.at(_i).setPosition((text.at(_i ).getPosition().x + text.at(_i ).getLocalBounds().width) , getPosY());

        //iterates all text in front of inserted text to be drawn in front of the char before it (shimmies all the other letters along)
        for(int x = _i; x < text.size(); x++){

            text.at(x).setPosition((text.at(x -1).getPosition().x + text.at(x -1).getLocalBounds().width) , getPosY());
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

        text.at(0).setPosition(getPosX(), getPosY());
    }else{

        //this puts the char in args after the previous char in the array
        text.back().setPosition(text.end()[-2].getPosition().x + text.end()[-2].getLocalBounds().width , getPosY());
    }

    //moves caret across
    setCaret( text.back().getPosition().x + text.back().getLocalBounds().width, getPosY(), 30);
}

//removes last character
void textIn::removeChar(){

    if(text.size() > 0){

        text.pop_back();

        //moves caret back
        setCaret( text.back().getPosition().x + text.back().getLocalBounds().width, getPosY(), 30);
    }else{

        //if the text array is empty then return the caret to start
        setCaret( getPosX() + 5, getPosY(), 30);
    }
}

//removes char from position in args and changes subsequent objects to be drawn properly
void textIn::removeChar(int _i){

    text.erase(text.begin() + _i);

    //iterates all text in front of inserted text to be drawn in front of the char before it (shimmies all the other letters along)
    for(int x = _i; x < text.size(); x++){

        text.at(x).setPosition((text.at(x -1).getPosition().x + text.at(x -1).getLocalBounds().width) , getPosY());
    }
}

//gets text from the text graphics vector and returns it as a string also deals with pesky space bar
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

    if( text.size() >= 1){

        for(int c = 1; c < text.size(); c++){

            if(caretX +1 > text.at(c).getPosition().x && caretX  < text.at(c).getPosition().x + text.at(c).getLocalBounds().width &&
               caretY +1 > text.at(c).getPosition().y && caretY < text.at(c).getPosition().y + text.at(c).getLocalBounds().height){

                return c-1;
            }
        }
    }

    //else return second to last
    return text.size()-1 ;
}


int textIn::getID(){

    return ID;
}

//sets an id number for text box
void textIn::setID(int _id){

    ID = _id;
}
