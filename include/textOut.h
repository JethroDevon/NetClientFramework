#ifndef TEXTOUT_H
#define TEXTOUT_H

#include <vector>
#include "Sprites.h"

class textOut: public Sprites{

    public:

        //constructor has position (x y) and size ( width height), next is render window to draw to
        textOut(int, int, int, int, sf::RenderWindow &);
        ~textOut();

        //adds a string to the text array
        void addString(std::string _string);

        //draws the box with the text in and slider for
        //scrolling through text
        void drawText();

        //changes font to path in args
        void changeFont(std::string _path);

        //setter and getter for font size
        void setFontSize(int _s);
        int getFontSize();

    private:

        //initialises rectangles in the text box to be drawn
        void setRects();

        //contains an image for each line of text added with 'addString()' or
        //if the '\n' character is encountered a new string is made and added
        //with that function.
        std::vector<sf::Text> boxText;

        //font to draw text images with
        sf::Font font;

        //stores font size
        int fontSize;
};

#endif // TEXTOUT_H
