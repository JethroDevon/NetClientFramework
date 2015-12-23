#include "Splash.h"

//this constructor runs the splash screen for  as many seconds as is passed in the last argument
Splash::Splash(sf::RenderWindow & _win, std::string _path, int _row, int _col, double _runTime): splashWin(_win), Sprites(_win, _path, _row, _col){

    splashRunning = true;

    //create vector variable based on screen dimensions
    sf::Vector2f size = static_cast<sf::Vector2f>(splashWin.getSize());

    //sets the window passed into args to be of the same size as each frame in the splash screen
    size.x = tex.getSize().x/_col;
    size.y = tex.getSize().y/_row;

	// apply possible size changes and reset them
	splashWin.setSize(static_cast<sf::Vector2u>(size));

	splashWin.setView(sf::View(sf::FloatRect(0.f, 0.f, size.x, size.y)));

	//call draw splash screen
    runSplash(_runTime);
}

//this constructor is for a splash screen that runs untill it is told to stop
Splash::Splash(sf::RenderWindow & _win, std::string _path, int _row, int _col): splashWin(_win), Sprites(_win, _path, _row, _col){

    splashRunning = true;

    //create vector variable based on screen dimensions
    sf::Vector2f size = static_cast<sf::Vector2f>(splashWin.getSize());

    //sets the window passed into args to be of the same size as each frame in the splash screen
    size.x = tex.getSize().x/_col;
    size.y = tex.getSize().y/_row;

	// apply possible size changes and reset them
	splashWin.setSize(static_cast<sf::Vector2u>(size));

	splashWin.setView(sf::View(sf::FloatRect(0.f, 0.f, size.x, size.y)));

	//call draw splash screen
    runSplash();
}

//runs draw for as many seconds as is passed in args
void Splash::runSplash(double _time){

    while(splashRunning){

        //closes the window once the timer is up
        if(getTicks(_time)){

            splashRunning = false;
        }

        splashWin.clear();
        splashWin.draw(getNext());
        splashWin.display();
    }
}

//runs splash screen until splashRunning is set to false with splashKill(), use carefuly
void Splash::runSplash(){

    //runs until set to false
    while(splashRunning){

        splashWin.clear();
        splashWin.draw(getNext());
        splashWin.display();
    }
}

//return window recreates the window as the user will want it to be again
void Splash::returnWindow(int _x, int _y, std::string _title){

	splashWin.create(sf::VideoMode(_x,_y), _title, true);
}

//this function is for managing other threads or programs while splash screen is running
bool Splash::splashAlive(){

    return splashRunning;
}

//this function is for managing other threads or programs while splash screen is running
void Splash::splashKill(){

    splashRunning = false;
}
