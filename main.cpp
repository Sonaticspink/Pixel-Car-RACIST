#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cmath>

using namespace std;
using namespace sf;

//Game constant
    const double SCREEN_WIDTH = 1280;
    const double SCREEN_HEIGHT = 720;
    const int borderLeft = 140;
    const int borderRight = 660;

//Create Main Windows
RenderWindow app(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),"Game kakkak V.1");

//Car status
struct Car{
    double x,y,lastspeed,speed,dist;
    bool state;
};

//Game over
int gameOver(int );

int main()
{
    //Game music
    SoundBuffer gameSoundBuffer,clicking,hovering;
    gameSoundBuffer.loadFromFile("sound/game.wav");
    clicking.loadFromFile("sound/click.wav");
    hovering.loadFromFile("sound/hover.wav");
    Sound GameSound,click,hover;
    GameSound.setBuffer(gameSoundBuffer);
    click.setBuffer(clicking);
    hover.setBuffer(hovering);

    //Include texture and font
    Texture background, racer, button1, button2, ticon, vicon, cb1 ,cb2;
    Font font;

    //Load all images
    if(!background.loadFromFile("cars/background.png")) return 10;
    if(!racer.loadFromFile("cars/racer.png")) return 11;
    if(!font.loadFromFile("font/xirod.ttf")) return 12;
    if(!button1.loadFromFile("ui/tr.png")) return 13;
    if(!button2.loadFromFile("ui/vs.png")) return 14;
    if(!cb1.loadFromFile("ui/tr2.png")) return 15;
    if(!cb2.loadFromFile("ui/vs2.png")) return 16;
    if(!ticon.loadFromFile("ui/clock.png")) return 17;
    if(!vicon.loadFromFile("ui/match.png")) return 18;

    //Background
    Sprite Background(background),Background1(background);

    //Time record mode button
    Sprite spr_ButtonTR(button1);
    spr_ButtonTR.setPosition(((SCREEN_WIDTH/2)-180),250);

    //Vs mode button
    Sprite spr_ButtonVS(button2);
    spr_ButtonVS.setPosition(((SCREEN_WIDTH/2)-140),150);

    //Time record icon
    Sprite spr_ticon(ticon);
    spr_ticon.setPosition(1230,0);
    spr_ticon.setScale(0.1,0.1);

    //VS icon coming soon
    Sprite spr_vicon(vicon);
    spr_vicon.setPosition(750,500);

    //Player car
    Sprite playerCar(racer);
    Car player = {((SCREEN_WIDTH/2)-290),SCREEN_HEIGHT/2,0,0,0,false};
    double travel;

    //Car position
    double BackgroundY1 = 0;
    double BackgroundY2 = -600;

    //Modes
    bool TRmode = 0;
    bool VSmode = 0;
    FloatRect clickableArea = spr_ButtonTR.getGlobalBounds();
    FloatRect clickableArea2 = spr_ButtonVS.getGlobalBounds();

    //Time
    Clock clock,clock2;
    Time dt;
    float duration = 10.0f;

    //Press P to start game text
    Text text_MainWindowText ( "Press P To Start The Game", font);
    text_MainWindowText.setCharacterSize( 15 );
    text_MainWindowText.setColor( Color::White );
    text_MainWindowText.setPosition( 450 , 30 );

    //GAME LOOP
    while(app.isOpen()){

        Event event;
        //Initial position
        playerCar.setPosition(player.x,player.y);

        while (app.pollEvent(event))
        {
                switch(event.type){
                    //In case of clicking exit
                    case Event::Closed:
                        app.close();
                        break;

                    //In case of keyboard press
                    case Event::KeyPressed:
                    //Press P to start
                    if(Keyboard::isKeyPressed(Keyboard::P)){
                        GameSound.setVolume(0.6);
                        GameSound.play();
                        GameSound.setLoop(true);
                        clock.restart();
                        while(duration > 0){
                            //Time setting
                            Time time = clock.getElapsedTime();
                            duration -= time.asSeconds();
                            if(TRmode == 0) duration = 10;
                            cout << duration << endl;
                            clock.restart();
                            double dt = time.asSeconds();
                            dt *= 100;

                            //Set car position
                            playerCar.setPosition(player.x,player.y);

                            //Create scrolling background
                            Background.setPosition(0,BackgroundY1);
                            Background1.setPosition(0,BackgroundY2);
                            if (BackgroundY2>0)
                            {
                                BackgroundY1=0;
                                BackgroundY2=BackgroundY1-500;
                            }
                            BackgroundY1 += player.dist;
                            BackgroundY2 += player.dist;

                            //Press key car speed up
                            if(player.state == 0){
                                if(Keyboard::isKeyPressed(Keyboard::A)) {player.speed += 2;player.state = 1;}
                            }
                            else if(!Keyboard::isKeyPressed(Keyboard::A)) player.state = 0;

                            //Car go
                            player.lastspeed = player.speed;
                            player.speed -= 0.1*dt ;
                            if(player.speed <= 0 ) player.speed = 0;
                            player.dist = 0.5*(player.lastspeed+player.speed)*dt;


                            //Distance traveled
                            travel += player.dist;
                            Text text("Distance " + to_string((int)travel) + " km",font,15);
                            text.setPosition(5,0);

                            //Clear and redraw position
                            app.clear();
                            app.draw(Background);
                            app.draw(Background1);
                            app.draw(playerCar);
                            if(TRmode == 1){
                                app.draw(spr_ticon);
                                Text timer("Time left : " + to_string(duration) + " seconds",font,15);
                                timer.setPosition(880,0);
                                app.draw(timer);
                            }
                            app.draw(text);
                            app.display();
                        }
                    }
                    break;

                    //In case of mouse clicking
                    case Event::MouseButtonPressed:
                        if (event.mouseButton.button == Mouse::Left) {
                            Vector2f mousePosition = app.mapPixelToCoords(Mouse::getPosition(app));
                            if (clickableArea.contains(mousePosition)) {
                                hover.play();
                                if(spr_ButtonTR.getTexture() == &button1){
                                    TRmode = 1 ;
                                    spr_ButtonTR.setTexture(cb1);
                                    spr_ButtonVS.setTexture(button2);
                                }
                                else{
                                    TRmode = 0 ;
                                    spr_ButtonTR.setTexture(button1);
                                }
                            }
                            if (clickableArea2.contains(mousePosition)) {
                                hover.play();
                                if(spr_ButtonVS.getTexture() == &button2){
                                    spr_ButtonVS.setTexture(cb2);
                                    spr_ButtonTR.setTexture(button1);
                                }
                                else{
                                    TRmode = 0 ;
                                    spr_ButtonVS.setTexture(button2);
                                }
                            }
                        }
                        break;

                    default:
                        break;
            }
        }
        //When mode is TR and time < 0 go to GameOver
        if(TRmode == 1 and duration <=0){
            sleep(seconds(2));
            click.play();
            gameOver(travel);
        }
        app.clear();
        app.draw(playerCar);
        app.draw(Background);
        app.draw(Background1);
        app.draw(text_MainWindowText);
        app.draw(spr_ButtonVS);
        app.draw(spr_ButtonTR);
        app.display();
    }
    return 0;
}
//Game over screen
int gameOver(int dis){
    Texture gameover;
    Font font;
    if(!gameover.loadFromFile("cars/over.png")) return 20;
    if(!font.loadFromFile("font/xirod.ttf")) return 12;
    Sprite Gameover(gameover);
    while(app.isOpen()){
        Text go("You Got " + to_string(dis) + " km",font,30);
        go.setPosition(SCREEN_WIDTH/2-200,SCREEN_HEIGHT/2);
        app.clear();
        app.draw(go);
        app.display();
        sleep(seconds(3));
        app.close();
    }
    return 999;
}

