#include <SFML/Graphics.hpp>
#include "sockWrapper.h"
#include "Connection.h"
#include "Splash.h"
#include "Button.h"
#include "Message.h"
#include "textIn.h"

int main(){

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "", false);

    Splash splash(window, "media/XD.png", 4, 4, 2);

    splash.returnWindow(800 , 600, "NetClient");

    textIn textField(  50, 50, 200, 50, window);

    textIn textField2(  50, 150, 300, 10, window);

    Button b(100,400,75,50,"EXIT!",window);

    //setting frame rate
    window.setFramerateLimit(12);

    //main window loop is presently for debugging
     while (window.isOpen()){

         sf::Event event;
         while (window.pollEvent(event)){

             if (event.type == sf::Event::Closed ||  b.getSelected())
                 window.close();
         }

        window.clear(sf::Color::White);

        textField.drawText();
        textField2.drawText();
        b.drawBunt();
        window.display();
        textField.keyListen(event);
        textField2.keyListen(event);
     }
}
