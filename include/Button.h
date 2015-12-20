#ifndef BUTTON_H
#define BUTTON_H

#include "Sprites.h"

//class draws a mouse click-able button on the screen, class is derived from sprites class
class Button: public Sprites{
    public:

        //plain button
        Button(int, int, int, int, std::string, sf::RenderWindow &);

        //button can take an image or an animation and call it on click
        Button(int, int, int, int, std::string, sf::RenderWindow &, std::string);

        //returns true if function is called and the mouse is within bounds of the object
        bool mouseOver();

        //sets selected to true or false
        void setSelected(bool _s);

        //gets whether the button is selected
        bool getSelected();

        //draw the button
        void drawBunt();

        //draws a buttons animation in the form of a sprite
        void animateButton();

        //get and set for id numbers
        int getID();
        void setID(int);

        //sets colours for text box, else they are left to default
        void setBorderColor(sf::Color);
        void setBackgroundColor(sf::Color);

        //reference to the main window
        sf::RenderWindow &rw;

        //prepares button object
        void setRect();

        //listens for mouse click over self
        void mouseListen();

    private:

        //the shape object
        sf::RectangleShape rectangle;

        //position object to store mouse position
        sf::Vector2i position;

        //this stores a drawrable image of text
        sf::Text sftext;

        //knows if the box has been selected by a mouse click, default false;
        bool selected;

        //Identity number of the button for dynamic management;
        int id;

        //string to write within the button
        std::string text;

        //font is going to remain bold sans
        sf::Font font;
};

#endif // BUTTON_H
