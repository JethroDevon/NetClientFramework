#include "textIn.h"

//constructor with button object initialised in initialiser list
textIn::textIn (int _x, int _y, int _width, int _height, sf::RenderWindow &_rw): Sprites( _rw, "media/cb.bmp") {

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

//updates carets new position based on args
void textIn::setCaret(int _x, int _y, int _length){

    caret.setPosition(sf::Vector2f(_x, _y));
    caret.setFillColor(sf::Color::Red);
    caret.setSize(sf::Vector2f(1,_length));

    //updates carets position for collision detection
    caretX = _x;
    caretY = _y;

    //caret two comes into play only when the text is longer than the box
    //it needs to be initialised with something for good measure
    caret2.setPosition(sf::Vector2f(getPosX() + getWidth(), _y));
}

//draws the caret if ticks are true and if the box is selected, ticks creates a blinking caret
void textIn::drawCaret(){

    if(getSelected()){

        if(textboxOverlap() < 0){

            rw.draw(caret);
        }else{

            caret2.setPosition(sf::Vector2f(caret.getPosition().x - textboxOverlap(), caret.getPosition().y));
            caret2.setFillColor(sf::Color::Red);
            caret2.setSize(sf::Vector2f(1,getHeight()));
            rw.draw(caret2);
        }
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

            //this is on the condition that the caret is not moved to the back of the box when it is
            //writing text that is longer than the box, the user can delete stuff rather than go back
            //to see what they have written as this kind of input box is very small and needs to be lower in
            //overhead
            if(caret2.getPosition().x - 16 > getPosX()){

                caretIndex--;
                setCaret(caretPosition.at(caretIndex), getPosY(), getHeight());
            }
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


//displays the box to draw text in, and the text within it.
void textIn::drawText(){

    //when called listens for mouse changes
    mouseListen();

    //draws background rectangle
    rw.draw(rectangle);

    if( textboxOverlap() < 0 ){

        //loops through each char in the sf::Text array drawing each one
        for(auto &t: text){

            //deals with difficult space bar character (symbolized with an underscore) by ignoring him
            if(t.getString() != '_'){

                rw.draw(t);
            }
        }

    //moves the last string of characters back by the length of the amount the
    //character string was overlapped by, also removes the characters equal to the
    //length that.
    }else if(textboxOverlap() > 0 && caret2.getPosition().x > getPosX() ){

        //loops through each object on text array
        for(auto &t: text){

            if(t.getPosition().x > textboxOverlap()){

                sf::Text temptext = t;
                temptext.setPosition(t.getPosition().x - textboxOverlap() , t.getPosition().y);

                //doesn't draw the characters if they are behind the text box
                if(temptext.getPosition().x > getPosX()){

                    //removes stand in character for the space
                    if(temptext.getString() != '_')
                        rw.draw(temptext);
                }
            }
        }
    }

    //draws the blinking caret
    drawCaret();
}

//this function returns the distance that the string of texts overlaps the text box, if it doesn't it returns the minus
//distance
int textIn::textboxOverlap(){

    //if there are actually text objects on the text vector
    if(text.size() > 0){

        //return overlapped distance
        return  (text.back().getPosition().x + text.back().getLocalBounds().width) - (getPosX() + getWidth());
    }else{

        //return the minus value of the whole length of the box as there's no text to check yet
        return getWidth() * -1;
    }
}

//adds a character to the text array
void textIn::addChar(int _c){

    //creates a text graphic assigns a font and colour and size and pushes it to back of text vector
    sf::Text temp;
    temp.setFont(font);
    temp.setString( static_cast<char>(_c));
    temp.setColor(sf::Color::Black);
    temp.setCharacterSize(getHeight());
    text.push_back(temp);

    if(_c == 32){

        text.back().setString("_");
    }

    //if it is the first in the array set the position of the first character to be within the start of the text box
    if(text.size() == 1){

        text.at(0).setPosition(getPosX(), getPosY() - (getHeight()/5));
    }else{

        //this puts the char in args after the previous char in the array
        text.back().setPosition(text.end()[-2].getPosition().x + text.end()[-2].getLocalBounds().width , getPosY() - (getHeight()/5));
    }

    //moves the caret along one since a caret has been added
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
    temp.setCharacterSize(getHeight());

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
        text.at(_i).setPosition((text.at(_i ).getPosition().x + text.at(_i ).getLocalBounds().width) , getPosY() - (getHeight()/5));

        //iterates all text in front of inserted text to be drawn in front of the char before it (shimmies all the other letters along)
        for(int x = _i; x < text.size(); x++){

            text.at(x).setPosition((text.at(x -1).getPosition().x + text.at(x -1).getLocalBounds().width) , getPosY() - (getHeight()/5));
        }
    }else{

        //insert the text in the vector at index using the iterator
        text.insert(it, temp);

        //sets position of first character to be at front of text box
        text.at(0).setPosition(getPosX() , getPosY() - - (getHeight()/5));

         //iterates all text in front of inserted text to be drawn in front of the char before it (shimmies all the other letters along)
        for(int x = 1; x < text.size(); x++){

            text.at(x).setPosition((text.at(x -1).getPosition().x + text.at(x -1).getLocalBounds().width) , getPosY() - - (getHeight()/5));
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
        setCaret( getPosX() + 1, getPosY(), getHeight());
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

            text.at(x).setPosition((text.at(x -1).getPosition().x + text.at(x -1).getLocalBounds().width) ,  getPosY() - (getHeight()/5));
        }

    }else if(_i != 0){

        //delete first element
        text.erase(it);

        //set first element to be at the front of the text box
        text.at(0).setPosition(getPosX() , getPosY() - (getHeight()/5));

         //iterates all text in front of inserted text to be drawn in front of the char before it (shimmies all the other letters along)
        for(int x = 1; x < text.size(); x++){

            text.at(x).setPosition((text.at(x -1).getPosition().x + text.at(x -1).getLocalBounds().width) , getPosY()- (getHeight()/5));
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
