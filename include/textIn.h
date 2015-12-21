#ifndef TEXTIN_H
#define TEXTIN_H

#include <SFML/Graphics.hpp>
#include "Button.h"
#include <string>
#include <vector>

//text input box takes key press when mouse is clicked within bounds and sets a flag called
//sendText to true, when this is set to true the function send will return the string in the text box
//of field, this function takes a title in first args, default text in second that will disappear on mouse click
//an x and y position a box length int and a true or false bool that sets whether or not to add a button at the end
//with 'send' written on to set sendText flag to true, the last argument is the render window to draw to
class textIn{
    public:

        //constructor, arg1; title of text box, arg2; text box initialised with this string, arg3 and arg 4
        //are xpos and ypos to draw top left of box, arg5 = width of box, arg6 whether or not to include a send button
        //next to the text input box
        textIn(std::string, std::string, int, int, int, bool, sf::RenderWindow &);

        //reference to the window to render on
        sf::RenderWindow & rw;

        //prepares elements in the textbox to be drawn in the right places
        void setRects();

        //functions to draw the caret and set its position
        void setCaret( int, int, int);
        void drawCaret();

        //listens to keypresses when selected
        void keyListen(sf::Event &);

        //displays the box to draw text in
        void drawText();

        //returns string to send text on
        std::string send();

        //returns state of boolean 'selected'
        bool getSelected();

        //returns true if mouse is over text box when function is called
        bool mouseOver();

        //listens for mouse click over the rectangle
        void mouseListen();

        //keeps track of time so as to draw caret blinking on and off
        bool getTicks(double);

        //returns index of text object in text vector that the caret is colliding with
        int textIndex();

        //sets state of boolean 'selected'
        void setSelected(bool);

        //inserts text in arg2 at index in arg1
        void insertChar(int, int);

        //adds a character to the string text, takes a unicode integer as args
        void addChar(int);

        //removes last character from the string text unless its empty
        void removeChar();

        //removes a sf::Text obecect from vector text at the index num in args
        void removeChar(int);

        //gets or returns the string 'text'
        std::string getText();

        //get integer private variables for id number if set and xpos and ypos and width
        int getXpos();
        int getYpos();
        int getWidth();
        int getID();

        //sets an id number for text box
        void setID(int);

    private:

        //stores sf::font
        sf::Font font;

        //position object to store mouse position
        sf::Vector2i position;

        //this will be the send button
        Button sendButton;

        //this rectangle displays text within it, caret will display  the text cursor
        sf::RectangleShape rectangle, caret;

        //this is to store passed time for a timer function to draw the caret blinking
        std::clock_t startTime;

        //sendtext is true if there is text to send, selected is true if mouse is over the text box when it clicks
        //caretX and caretY keep track of where the caret is but do not effect its moving
        bool sendText, selected, withButton;
        int xpos, ypos, boxWidth, ID, caretX, caretY;

        //lastKey remembers the last key code hit and calls the ticks function, this way the user doesn't
        //stream characters out when they just want one
        int lastKey;

        //name for heading of text input box if needed and text to appear in
        //text box automatically
        std::string name, initText;

        //stores an array of individual characters, these will be drawn in the form of a
        //sentence but allow the insertion of text
        std::vector<sf::Text> text;
};

#endif // TEXTIN_H
