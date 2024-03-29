#ifndef CARCONTROL_H_INCLUDED
#define CARCONTROL_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cmath>

using namespace std;
using namespace sf;

class Car{  //Car class
private:
    double x,y,speed,dist,xspeed,initY,decel; //Car position X and Y. Car speed. Distance traveled at a time.
    int playerNO; //Player number 1 or 2
    bool state,xstate; //Tells you if the button is held.
    Sprite model;
    Clock timer;
public:
    Car(int,double);
    double go(double);
    vector<double> position();
    double showDist();
    double showSpeed();
    void setSkin(Texture &);
    void setSize(float ,float);
    Sprite drawModel();
    void changePosition(double,double);
    void setPosition(double,double);
    friend bool operator==(Car &,Car &);
};

Car::Car(int number,double h){ //Set player car
    playerNO = number;
    speed = 0;
    dist = 0;
    state = 0;
    xstate = 0;
    y = h/2-300;
    initY = h/2-300;
    xspeed = 1;
    decel = 0.1;
    if(playerNO == 1) x = 250;
    if(playerNO == 2) x = 700;
    if(playerNO == 191) {x = 600;y = h-50;initY = h-50;decel = 0;xspeed = 3;}
}

double Car::go(double dt){ //How fast and far go. When key is pressed cat go faster
    double lastSpeed = speed,lastXSpeed = xspeed;
    if(playerNO == 1){
        if(Keyboard::isKeyPressed(Keyboard::A) && state == 0) {speed += 1.4;state = 1;}
        else if(!Keyboard::isKeyPressed(Keyboard::A)) state = 0;
        if(Keyboard::isKeyPressed(Keyboard::S) && xstate == 0) {xspeed *= -1;xstate = 1;}
        else if(!Keyboard::isKeyPressed(Keyboard::S)) xstate = 0;
        if(x <= 200) x = 200;
        if(x >= 450) x = 450;
    }
    if(playerNO == 2){
        if(Keyboard::isKeyPressed(Keyboard::L) && state == 0) {speed += 1.4;state = 1;}
        else if(!Keyboard::isKeyPressed(Keyboard::L)) state = 0;
        if(Keyboard::isKeyPressed(Keyboard::K) && xstate == 0) {xspeed *= -1;xstate = 1;}
        else if(!Keyboard::isKeyPressed(Keyboard::K)) xstate = 0;
        if(x <= 650) x = 650;
        if(x >= 900) x = 900;
    }
    if(playerNO == 191){
        double cool = timer.getElapsedTime().asSeconds();
        if(x >= 900 || x <= 200) xspeed *= -1;
        if(cool >= rand()%35+5) {speed = 10;xspeed = 0;}
        if(y <= -200) {y = initY;timer.restart();speed = 0;xspeed = 3;}
        y -= speed*dt;
        x += xspeed*dt;
    }
    dist = 0.5 * (lastSpeed + speed) * dt;
    speed -= decel*dt;
    if(speed <= 0) speed = 0;
    if(playerNO == 1 && x >= 200 && x <= 450) x += 0.5 * (lastXSpeed + xspeed) * dt;
    if(playerNO == 2 && x >= 650 && x <= 900) x += 0.5 * (lastXSpeed + xspeed) * dt;
    //cout << dist << endl;
    return dist;
}

bool operator==(Car &player,Car &cop){
    if(player.model.getGlobalBounds().intersects(cop.model.getGlobalBounds())) return true;
    else return false;
}

vector<double> Car::position(){ //Gives the X and Y position of the car.
    vector<double> a = {x,y};
    return a;
}

double Car::showDist(){ //gives the distance the car has traveled at the time.
    return dist;
}

double Car::showSpeed(){ //Gives the speed of a cat at the time.
    return speed;
}

void Car::setSize(float a,float b){ //Set the sprite of the cat
    model.setScale(a,b);
}

void Car::setSkin(Texture &texture){ //Set the sprite of the cat
    model.setTexture(texture);
}

Sprite Car::drawModel(){ //Set the position of the sprite or use in app.draw(player.drawModel());
    model.setPosition(x,y);
    return model;
}
void Car::changePosition(double a=0, double b=0){
    x += a;
    y += b;
}

void Car::setPosition(double a,double b){
    x = a;
    y = b;
}

#endif  CARCONTROL_H_INCLUDED
