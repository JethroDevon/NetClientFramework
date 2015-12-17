#include <SFML/Graphics.hpp>
#include "sockWrapper.h"
#include "Connection.h"
#include "Splash.h"



int main(){

sf::RenderWindow screen(sf::VideoMode(200,200), "", false);

Splash splash(screen, "XD.png", 4, 4, 4);

splash.returnWindow(400,400,"Mow");





}
