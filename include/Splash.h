#ifndef SPLASH_H
#define SPLASH_H

#include "Sprites.h"

//splash screen class can be called at the beginning of a program with minimum setting up/initialisation
//pass in a window object followed by path to image, next two args slice it up into an animation, last args is duration
class Splash: public Sprites{

    public:

        //the first argument is takes any renderWindow passed into main, it will resize it to the size of the frames
        //in the contact sheet who's directory address will be passed into second args, the next two args are the number
        //of frames across and the number of frames down, the final arg is the time to run the splash screen for, a function
        //called returnWindow in the class can resize the screen afterwards if needs be
        Splash(sf::RenderWindow &,std::string, int, int, double);

        //this constructor runs the forever looping splash screen that will
        //run untill splashKill() is called
        Splash(sf::RenderWindow &,std::string, int, int);

        //draws splash screen for as long as args if initialised correctly
        void runSplash(double);

        //forever running overloaded version
        void runSplash();

        //returns true while splash is running false when it has stopped
        bool splashAlive();

        //kills everRunnning splash screen
        void splashKill();

        //resets window to set sizes
        void returnWindow(int, int, std::String);

        //object to refere to window passed into args with
        sf::RenderWindow &splashWin;

    private:

        bool splashRunning;
};

#endif // SPLASH_H
