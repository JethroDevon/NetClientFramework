#ifndef TEXTOUT_H
#define TEXTOUT_H

#include <vector>
#include "Sprites.h"

class textOut: public Sprites{

    public:

        //constructor has position (x y) and size ( width height), next is render window to draw to
        textOut(int, int, int, int, int, sf::RenderWindow &);

        //adds a string to the text array
        void addString(std::string);

        //draws the box with the text in and slider for
        //scrolling through text
        void drawBox();

        //changes font to path in args
        void changeFont(std::string);

        //setter and getter for font size
        void setFontSize(int);
        int getFontSize();

    private:

        //initialises rectangles in the text box to be drawn
        void setRects();

        //stores font size
        int fontSize;

        //
        void setLinePos();

        //pushes text object to front of vector
        void insertSFText(sf::Text);

        //contains an image for each line of text added with 'addString()' or
        //if the '\n' character is encountered a new string is made and added
        //with that function.
        std::vector<sf::Text> boxText;

        //font to draw text images with
        sf::Font font;

        //rectangles for the box to draw text in, the slider button to scroll the text and that box
        //for the slide button to sit in
        sf::RectangleShape box, slideButton, sliderBox;
};

#endif // TEXTOUT_H
