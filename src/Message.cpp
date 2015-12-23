#include "Message.h"

///TO-DO sizing and scale of buttons and text matched to draw position


//constructor for an options message box takes true in last arg for a standard dialogue message box, okay sets selected to true and closes the box, cancel
//lets bool selected remain false and closes the box, read is set to true on both, button objects are default constructed based on position of method box
Message::Message(sf::RenderWindow &_rw, int _x, int _y, std::string _text, bool _t): rw(_rw), xpos( _x), ypos(_y),  message(_text), okay( _x + 50, _y + 90, 70, 40, "Okay", _rw), cancel( _x + 130 , _y + 90, 70, 40, "Cancel", _rw){

    isOptions = _t;
     if (!font.loadFromFile("media/OpenSans-Bold.ttf")){

         std::cout << "Error loading button font\n" << std::endl;
    }else{

        //std::cout << "Font loaded\n" << std::endl;
        sftext.setFont(font);

        //sets the text to draw
        sftext.setString(message);
    }

    //prepares the rectangle for the button
    setRect();
}

//prepares a rectangle object to be the message background
void Message::setRect(){

    rectangle.setFillColor(sf::Color::White);
    rectangle.setOutlineColor(sf::Color::Black);
    rectangle.setOutlineThickness(1);

    //position set to draw
    rectangle.setPosition(sf::Vector2f(xpos, ypos));

    //size is set to a standard, may add a scrolling
    //text field if text is too big later
    rectangle.setSize(sf::Vector2f(250, 150));

    //set text position in message box to draw in centre
    //may apply more attractive placement later
    sftext.setPosition(xpos+10,ypos+50);
    sftext.setColor(sf::Color::Black);

    //sets text size to be one quarter of box height
    sftext.setCharacterSize(20);
}

//draws the message box
void Message::drawMess(){

    //draws rectangle and text
    rw.draw(rectangle);
    rw.draw(sftext);

    //depending if an options message or a basic message
    if(isOptions){

        //clicking either options box will close the message box however clicking okay
        //will set the boolean called selected to true, clicking either button will set
        //boolean called read to true
        okay.drawBunt();
        cancel.drawBunt();

        //detects button clicks
        if(okay.getSelected())
            selected = true;
        if(cancel.getSelected())
            read = true;
    }else{

        //clicking okay will close the dialogue box, boolean called read will be set to true.
        okay.drawBunt();

        //detects button clicks
        if(okay.getSelected())
            selected = true;
    }
}

//returns true if okay was clicked on an options message box
bool Message::getSelected(){

    return selected;
}

//returns true if any button was clicked on any message box
bool Message::getRead(){

    return read;
}

//sets colours for message box, else they are left to default
void Message::setBorderColor(sf::Color _bocol){

      rectangle.setOutlineColor(_bocol);
}

void Message::setBackgroundColor(sf::Color _bacol){

      rectangle.setFillColor(_bacol);
}

