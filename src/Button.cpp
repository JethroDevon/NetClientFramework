#include "Button.h"

//default constructor passes error image path into sprite extension because will not be using images
Button::Button(int _x, int _y, int _w, int _h, std::string _text, sf::RenderWindow & _rw): text(_text),  rw(_rw), Sprites("media/cb.bmp"){

    setXY(_x, _y);
    setWH(_w, _h);

    //default boolean else its hanging
    selected = false;

    if (!font.loadFromFile("media/OpenSans-Bold.ttf")){

         std::cout << "Error loading button font\n" << std::endl;
    }else{

        //std::cout << "Font loaded\n" << std::endl;
        sftext.setFont(font);

        //sets the text to draw
        sftext.setString(text);
    }

    //prepares the rectangle for the button
    setRect();
}

//default constructor passes error code image path into sprite extension because will not be using images
Button::Button(int _x, int _y, int _w, int _h, std::string _text, sf::RenderWindow & _rw, std::string _path): rw(_rw), Sprites(_path){

    setXY(_x, _y);
    setWH(_w, _h);

    //default boolean else its hanging
    selected = false;
}

//returns true if function is called and the mouse is within bounds of the object
bool Button::mouseOver(){

    //get mouse position
    position = sf::Mouse::getPosition(rw);

    //do collision and return
    if(position.x > getPosX() && position.x < getPosX() + getWidth() &&  position.y > getPosY() && position.y < getPosY() + getHeight()){

        return true;
    }else{

        return false;
    }
}

//sets selected to true or false
void Button::setSelected(bool _s){

    selected = _s;
}

//gets whether the button is selected
int Button::getID(){

    return id;
}

//sets selected to true or false
void Button::setID(int _id){

    id = _id;
}

//gets whether the button is selected
bool Button::getSelected(){

    return selected;
}

//draw the button
void Button::drawBunt(){

    //detect mouse click
    mouseListen();

    //window reference draws image
    rw.draw(rectangle);
    rw.draw(sftext);
}

void Button::animateButton(){

    //detect mouse click
    mouseListen();

    //draw animation frame in its present state
    rw.draw(showFrame());

    //if not selected increment  current frame by one
    //unless its reached the end of the animation sequence
    //de-increments if selected
    if(!selected){

        if(frame != frames.size())
            nextFrame();
    }else{

        if(frame != 0)
            nextFrame();
    }
}

void Button::setRect(){

    rectangle.setFillColor(sf::Color::White);
    rectangle.setOutlineColor(sf::Color::Black);
    rectangle.setOutlineThickness(1);
    rectangle.setSize(sf::Vector2f(getWidth(), getHeight()));
    rectangle.setPosition(getPosX(), getPosY());

    sftext.setPosition(10+getPosX(), 10+getPosY());
    sftext.setColor(sf::Color::Black);

    //sets text size to be one third of box height
    sftext.setCharacterSize(1+getHeight()/3);
}

//listen for clicks if mouse is over
void Button::mouseListen(){

    // left mouse button is pressed and mouse is over button
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mouseOver()){

        if(!selected){

            setSelected(true);
        }else{

            setSelected(false);
        }
    }
}

//sets colours for text box, else they are left to default
void Button::setBorderColor(sf::Color _bocol){

      rectangle.setOutlineColor(_bocol);
}

void Button::setBackgroundColor(sf::Color _bacol){

      rectangle.setFillColor(_bacol);
}
