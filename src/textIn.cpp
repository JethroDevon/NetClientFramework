#include "textIn.h"

///TO-DO: have the font size dictate the size of the text box, have the text box be the total size of the largest font and have them drawn at the bottom.
///take the corners off the edges or make the border really thin, the background colour light grey by default with functions to change all colours
///functions to change font with error handling, functions to return a list of available fonts also
///include a send button with true or false affected, add a reduced constructor with very basic defaults


//constructor with button object initialised in initialiser list
textIn::textIn(std::string _name, std::string _initText, int _x, int _y, int _width, int _height, bool _withButton, sf::RenderWindow &_rw): name( _name), initText( _initText),
    withButton( _withButton), Sprites(_rw, "media/cb.bmp") {

    //selected is default false
    setSelected(false);

    //set x y and width of box heights set at 30 for now
    setXY( _x, _y);
    setWH(_width, _height);

    setCaret(_x, _y, getHeight());
    caretIndex = 1;
    caretPosition.push_back(caretX);

    if (!font.loadFromFile("media/Pink Bunny.ttf")){

        std::cout<<"Likely name of font incorrect";
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
    rectangle.setSize(sf::Vector2f(getWidth(), getHeight()));
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

    //if there are any text objects to cycle through
    if(text.size() != 0){

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&  caretIndex > 0){

             caretIndex--;
             setCaret(caretPosition.at(caretIndex), getPosY(), getHeight());
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && (caretIndex < caretPosition.size() -1)){

            caretIndex++;
            setCaret(caretPosition.at(caretIndex), getPosY(), getHeight());
        }
    }

    //this is not key pressed event at all this is textEntered its entirely different
    if (e.type == sf::Event::TextEntered){

        if (e.text.unicode < 128 && getSelected()){

             //if the same key as the last one was pressed not too recently
            if(lastKey == e.text.unicode ){

                //if a second has passed
                if(getTicks(0.1)){

                    //if the caret is next to the front most text object append text to the front of the vector else
                    //insert the character to the point where the caret is colliding
                    if(text.size() == 0 || caretX > (text.back().getPosition().x + text.back().getLocalBounds().width) - 10){

                        addChar(e.text.unicode);
                    }else{

                        insertChar( textIndex(), e.text.unicode);
                    }
               }

             //if backspace has been hit
            }else if( 8 == e.text.unicode){

                    //if the caret is next to the front most text object remove the front most object with remove char
                    //else remove the character at the point where the caret is colliding
                    if( text.size() == 0 || caretX > (text.back().getPosition().x + text.back().getLocalBounds().width) - 10){

                        removeChar();
                    }else{

                        if(caretIndex != 0)
                            removeChar(textIndex());
                    }

             //if the caret is next to the front most text object append text to the front of the vector else
            //insert the character to the point where the caret is colliding
            }else if(text.size() == 0 || caretX > (text.back().getPosition().x + text.back().getLocalBounds().width)  - 10)  {

                addChar(e.text.unicode);
                lastKey = e.text.unicode;
                getTicks(0.08);

            }else{

                insertChar(textIndex(), e.text.unicode);
                lastKey = e.text.unicode;
                getTicks(0.08);
            }
        }
    }
}

//moves caret to last position in array
//moves caret to first position in array
void textIn::caretBack(){

     setCaret(caretPosition.at(0), getPosY(), getHeight());
     caretIndex = 0;
}

//moves caret to first position in array
void textIn::caretFront(){

     setCaret(caretPosition.at(caretPosition.size()), getPosY(), getHeight());
     caretIndex = caretPosition.size();
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

    setCaret( text.back().getPosition().x + text.back().getLocalBounds().width, getPosY(), getHeight());

    //stores the position of the caret on an array and iterates an iterator for it by one
    caretPosition.push_back(caret.getPosition().x);
    caretIndex++;
}

void textIn::insertChar( int _i, int _c){

    //creates an iterator for text vector assigned from arg 1
    auto it = text.begin();

    //creates a text graphic assigns a font and colour and size and pushes it to back of text vector
    sf::Text temp;
    temp.setFont(font);
    temp.setColor(sf::Color::Black);
    temp.setCharacterSize(25);

    //if char to insert is pesky spacebar character...
    if(_c == 32){

        //...then replace it with an underscore, no need to draw that underscore just a space must behave like a character
        temp.setString("_");
    }else{

        temp.setString( static_cast<char>(_c));
    }

    if(_i != 0){

        //insert the text in the vector at index using the iterator
        text.insert(it + _i, temp);
        text.at(_i).setPosition((text.at(_i ).getPosition().x + text.at(_i ).getLocalBounds().width) , getPosY());

        //iterates all text in front of inserted text to be drawn in front of the char before it (shimmies all the other letters along)
        for(int x = _i; x < text.size(); x++){

            text.at(x).setPosition((text.at(x -1).getPosition().x + text.at(x -1).getLocalBounds().width) , getPosY());
        }
    }else{

        //insert the text in the vector at index using the iterator
        text.insert(it, temp);

        //sets position of first character to be at front of text box
        text.at(0).setPosition(getPosX() , getPosY());

         //iterates all text in front of inserted text to be drawn in front of the char before it (shimmies all the other letters along)
        for(int x = 1; x < text.size(); x++){

            text.at(x).setPosition((text.at(x -1).getPosition().x + text.at(x -1).getLocalBounds().width) , getPosY());
        }
    }

    //reorganises all positions of text
    resetPositions();

    //moves caret along one
    setCaret( text.at(caretIndex).getPosition().x + text.at(caretIndex).getLocalBounds().width, getPosY(), getHeight());

    //stores the new position of the character at the very front
    caretPosition.push_back(text.at(text.size() -1).getPosition().x +  text.at(text.size() -1).getLocalBounds().width);

    caretIndex++;
}

//removes last character
void textIn::removeChar(){

    if(text.size() > 0){

        //removes last char and chars position on an array as well as an iterator for iterating over it
        text.pop_back();
        caretPosition.pop_back();

        //moves caret back
        setCaret( text.back().getPosition().x + text.back().getLocalBounds().width, getPosY(), getHeight());

        caretIndex--;

    }else{

        //if the text array is empty then return the caret to start
        setCaret( getPosX() + 1, getPosY(), 30);
        caretIndex = 0;
    }
}

//removes char from position in args and changes subsequent objects to be drawn properly
void textIn::removeChar(int _i){

    //creates an iterator for text vector assigned from arg 1
    auto it = text.begin();

     if(_i != 1){

        //remove the character in the vector at index using the iterator
        text.erase(it + (_i -1));

        //iterates all text in front of inserted text to be drawn in front of the char before it (shimmies all the other letters along)
        for(int x = (_i-1); x < text.size(); x++){

            text.at(x).setPosition((text.at(x -1).getPosition().x + text.at(x -1).getLocalBounds().width) , getPosY());
        }

    }else if(_i != 0){

        //delete first element
        text.erase(it);

        //set first element to be at the front of the text box
        text.at(0).setPosition(getPosX() , getPosY());

         //iterates all text in front of inserted text to be drawn in front of the char before it (shimmies all the other letters along)
        for(int x = 1; x < text.size(); x++){

            text.at(x).setPosition((text.at(x -1).getPosition().x + text.at(x -1).getLocalBounds().width) , getPosY());
        }
    }

    if(_i != 0){
        //reorganises all positions of caret
        resetPositions();

        caretIndex--;

        setCaret(caretPosition.at(caretIndex), getPosY(), getHeight());

        //stores the new position of the character at the very front
        caretPosition.push_back(text.at(text.size() -1).getPosition().x +  text.at(text.size() -1).getLocalBounds().width);
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

//this function returns a position relating to the carets position in the string of sf::text objects
int textIn::textIndex(){

    //pre initialise temp
    int temp = 1;

    //for each position in the caret positions array
    for(int pos = 0; pos < caretPosition.size(); pos++){

        //store the index number if the position in the array the caret is at
        if(caret.getPosition().x + caret.getLocalBounds().width > caretPosition.at(pos)){

            temp = pos;
        }
    }

    //return point in array caret is at
    return temp;
}

//deletes all caret positions and rebuilds them based on the new text string
void textIn::resetPositions(){

    for(int y = caretPosition.size(); y > 0; y--){

        caretPosition.pop_back();
    }

    for(auto f: text){

        caretPosition.push_back(f.getPosition().x);
    }
}


int textIn::getID(){

    return ID;
}

//sets an id number for text box
void textIn::setID(int _id){

    ID = _id;
}
