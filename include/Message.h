#ifndef MESSAGE_H
#define MESSAGE_H

#include <SFML/Graphics.hpp>
#include "Button.h"
#include <string>


class Message{
    public:

        //options message constructor
        Message(sf::RenderWindow &, int, int, std::string, bool);

        //reference to the
        sf::RenderWindow &rw;

        //draws the message box
        void drawMess();

        //prepares message rectangle
        void setRect();

        //sets colours for message box, else they are left to default
        void setBorderColor(sf::Color);
        void setBackgroundColor(sf::Color);

        //gets if the okay button was sleected in the options message
        bool getSelected();

        //returns true if any button was clicked on any message
        bool getRead();

    private:

        //the shape object
        sf::RectangleShape rectangle;

        //button object for clicking okay and closing the dialogue box, next one is to cancel something
        //this way there can be a dialogue box and an options box
        Button okay, cancel;

        //text font
        sf::Font font;

        //flags whether or not message is dialogue or options selector, okay selected or not
        bool isOptions, selected, read;

        //this stores a drawable image of text
        sf::Text sftext;

        //will contain the message to write in the message box
        std::string message;

        //the x and y coords to build the message box, if the text is too big for the box
        //a scroll text field may be implemented later
        int xpos, ypos;
};

#endif // MESSAGE_H
