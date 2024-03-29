#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cmath>
#include <fstream>
#include <sstream>
#include "carControl.h"

using namespace std;
using namespace sf;

//Game constant
    const double SCREEN_WIDTH = 1280;
    const double SCREEN_HEIGHT = 720;
    const int borderLeft = 140;
    const int borderRight = 1140;

//Create Main Windows
RenderWindow app(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),"Pixel Car Racist 1.0");

//Game over
int gameOver(int );
int gameOvervs(int ,int);

bool IsPlayed = 0;
bool crash1 = 0;
bool crash2 = 0;

int main()
{
    srand(time(0));
    app.setFramerateLimit(60);
    //Game music
    SoundBuffer gameSoundBuffer,clicking,hovering,trs,ds,r1,r2,r3,r4,r5,siren;
    gameSoundBuffer.loadFromFile("sound/game.wav");
    clicking.loadFromFile("sound/click.wav");
    hovering.loadFromFile("sound/hover.wav");
    trs.loadFromFile("sound/trs.wav");
    ds.loadFromFile("sound/ds.wav");
    r1.loadFromFile("sound/r1.wav");
    r2.loadFromFile("sound/r2.wav");
    r3.loadFromFile("sound/r3.wav");
    r4.loadFromFile("sound/r4.wav");
    r5.loadFromFile("sound/r5.wav");
    siren.loadFromFile("sound/siren.wav");
    Sound GameSound,click,hover,trss,dss,r1s,r2s,r3s,r4s,r5s,sirens;
    GameSound.setBuffer(gameSoundBuffer);
    click.setBuffer(clicking);
    hover.setBuffer(hovering);
    trss.setBuffer(trs);
    dss.setBuffer(ds);
    r1s.setBuffer(r1);
    r2s.setBuffer(r2);
    r3s.setBuffer(r3);
    r4s.setBuffer(r4);
    r5s.setBuffer(r5);
    sirens.setBuffer(siren);

    //Include texture and font
    Texture background, racer, racer2, button1, button2, button3, ticon, vicon, cb1, cb2, cb3, p1m1, p1m2, p2m1, p2m2, dashcar, dashmap, cop;
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
    if(!p1m1.loadFromFile("ui/p1m1.png")) return 19;
    if(!p1m2.loadFromFile("ui/p1m2.png")) return 20;
    if(!p2m1.loadFromFile("ui/p2m1.png")) return 21;
    if(!p2m2.loadFromFile("ui/p2m2.png")) return 22;
    if(!racer2.loadFromFile("cars/racer2.png")) return 23;
    if(!button3.loadFromFile("ui/d.png")) return 24;
    if(!cb3.loadFromFile("ui/d2.png")) return 25;
    if(!dashcar.loadFromFile("cars/dashcar.png")) return 26;
    if(!dashmap.loadFromFile("cars/dashmap.png")) return 27;
    if(!cop.loadFromFile("cars/pl.png")) return 69;

    Image icon;
    if(icon.loadFromFile("ui/icon.png")){
        app.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }

    //Background
    Sprite Background(background),Background1(background);

    //Time record mode button
    Sprite spr_ButtonTR(button1);
    spr_ButtonTR.setPosition(((SCREEN_WIDTH/2)-180),250);

    //Vs mode button
    Sprite spr_ButtonVS(button2);
    spr_ButtonVS.setPosition(((SCREEN_WIDTH/2)-140),150);

    //D mode button
    Sprite spr_ButtonD(button3);
    spr_ButtonD.setPosition(((SCREEN_WIDTH/2)-180),350);

    //Time record icon
    Sprite spr_ticon(ticon);
    spr_ticon.setPosition(1230,0);
    spr_ticon.setScale(0.1,0.1);

    //VS icon coming soon
    Sprite spr_vicon(vicon);
    spr_vicon.setPosition(1230,0);
    spr_vicon.setScale(0.1,0.1);

    //Player car
    //Sprite player1Car(racer),player2Car(racer2),Cop(cop);
    Car player1(1,SCREEN_HEIGHT),player2(2,SCREEN_HEIGHT),Cop(191,SCREEN_HEIGHT);
    player1.setSkin(racer);
    player2.setSkin(racer2);
    player1.setSize(0.8,0.8);
    player2.setSize(0.8,0.8);
    Cop.setSkin(cop);
    Cop.setSize(0.6,0.6);
    double travel = 0,travel2 = 0;

    //Car position
    double BackgroundY1 = 0;
    double BackgroundY2 = -600;

    //Modes
    bool Is1 = 0;
    bool Is2 = 0;
    bool TRmode = 0;
    bool VSmode = 0;
    bool Dmode = 0;
    bool isD = 0;
    bool isG = 0;
    FloatRect clickableArea = spr_ButtonTR.getGlobalBounds();
    FloatRect clickableArea2 = spr_ButtonVS.getGlobalBounds();
    FloatRect clickableArea3 = spr_ButtonD.getGlobalBounds();

    //Police
    crash1 = 0;
    crash2 = 0;

    //Time
    Clock clock,clock2,clock3,clock4;
    Time dt,delay = seconds(6.0f);
    float duration = 30.0f;

    //Mash
    bool p1m;
    bool p2m;
    Sprite P1M1(p1m1);
    P1M1.setPosition(20,SCREEN_HEIGHT/2);
    Sprite P2M1(p2m1);
    P2M1.setPosition(1200,SCREEN_HEIGHT/2);

    //Scoreboard
    int score = 0;
    int scorevs = 0;
    int scored = 0;

    //Press P to start game text
    Text text_MainWindowText ( "Press P To Start The Game", font);
    text_MainWindowText.setCharacterSize( 15 );
    text_MainWindowText.setColor( Color::White );
    text_MainWindowText.setPosition( 450 , 30 );
    Text debugm("Don't Select Any Button to Free Roam Mode",font,10);
    debugm.setPosition( 430 , 50 );

    ifstream scoreFile("score.txt");
    if (scoreFile.is_open())
    {
        scoreFile >> score;
        scoreFile.close();
    }

    ifstream scoreFile1("scorevs.txt");
    if (scoreFile1.is_open())
    {
        scoreFile1 >> scorevs;
        scoreFile1.close();
    }

    ifstream scoreFile2("scoredash.txt");
    if (scoreFile2.is_open())
    {
        scoreFile2 >> scored;
        scoreFile2.close();
    }

    Text highs("Highest score : " + to_string(score) + " km",font,15);
    highs.setPosition(0,700);

    Text highvs("Highest score : " + to_string(score) + " km",font,15);
    highvs.setPosition(0,700);

    Text highd("Highest score : " + to_string(score) + " km",font,15);
    highd.setPosition(0,700);

    ostringstream scoreString;
    scoreString << "Highest Score: " << score << " km";;
    highs.setString(scoreString.str());

    ostringstream scoreString1;
    scoreString1 << "Highest Score: " << scorevs << " km";;
    highvs.setString(scoreString1.str());

    ostringstream scoreString2;
    scoreString2 << "Highest Score: " << scored << " km";;
    highd.setString(scoreString2.str());
    highd.setFillColor(Color::Red);

    //Game Sound Loop
    if(IsPlayed == 0){
        GameSound.setVolume(20);
        GameSound.play();
        GameSound.setLoop(true);
        IsPlayed = 1;
    }

    //GAME LOOP
    while(app.isOpen()){

        Event event;
        //Initial position
        //player1Car.setPosition(player1Pos[0],player1Pos[1]);
        //player2Car.setPosition(player2Pos[0],player2Pos[1]);
        while(app.pollEvent(event))
        {
                switch(event.type){
                    //In case of clicking exit
                    case Event::Closed:{
                        isG = 1;
                        app.close();
                        break;
                    }

                    //In case of keyboard press
                    case Event::KeyPressed:
                    //Press P to start
                    if(Keyboard::isKeyPressed(Keyboard::P)){
                        highs.setString(scoreString.str());
                        clock.restart();
                        clock3.restart();
                        while(duration > 0){
                            //Time setting
                            Time time = clock.getElapsedTime();
                            if(!isD and Dmode == 1){
                                duration = 15.0;
                                isD = 1;
                                Background.setTexture(dashmap);
                                Background1.setTexture(dashmap);
                                player1.setSkin(dashcar);
                            }
                            duration -= time.asSeconds();
                            //cout << duration << endl;
                            clock.restart();
                            double dt = time.asSeconds();
                            dt *= 100;
                            //cout << dt << endl;

                            //Set car position
                            //double faster1 = 0,faster2 = 0;
                            if(clock3.getElapsedTime().asSeconds() > 5 and Dmode == 1){
                                if(player1.position()[1] <= SCREEN_HEIGHT/2-300){
                                    player1.setPosition(player1.position()[0],SCREEN_HEIGHT/2-300);
                                    player2.changePosition(0,(player1.showSpeed()-player2.showSpeed())*dt);
                                }
                                if(player2.position()[1] <= SCREEN_HEIGHT/2-300){
                                    player2.setPosition(player2.position()[0],SCREEN_HEIGHT/2-300);
                                    player1.changePosition(0,(player2.showSpeed()-player1.showSpeed())*dt);
                                }
                                //player1Car.setPosition(player1Pos[0],player1Pos[1]);
                                //player2Car.setPosition(player2Pos[0],player2Pos[1]);

                                //Create scrolling background
                                Background.setPosition(0,BackgroundY1);
                                Background1.setPosition(0,BackgroundY2);
                                if (BackgroundY2>0)
                                {
                                    BackgroundY1=0;
                                    BackgroundY2=BackgroundY1-750;
                                }
                                BackgroundY1 += max(player1.showSpeed(),player2.showSpeed())*dt;
                                BackgroundY2 += max(player1.showSpeed(),player2.showSpeed())*dt;
                            }
                            else if(Dmode != 1){
                                if(player1.position()[1] <= SCREEN_HEIGHT/2-300){
                                    player1.setPosition(player1.position()[0],SCREEN_HEIGHT/2-300);
                                    player2.changePosition(0,(player1.showSpeed()-player2.showSpeed())*dt);
                                }
                                if(player2.position()[1] <= SCREEN_HEIGHT/2-300){
                                    player2.setPosition(player2.position()[0],SCREEN_HEIGHT/2-300);
                                    player1.changePosition(0,(player2.showSpeed()-player1.showSpeed())*dt);
                                }
                                //player1Car.setPosition(player1Pos[0],player1Pos[1]);
                                //player2Car.setPosition(player2Pos[0],player2Pos[1]);

                                //Create scrolling background
                                Background.setPosition(0,BackgroundY1);
                                Background1.setPosition(0,BackgroundY2);
                                if (BackgroundY2>0)
                                {
                                    BackgroundY1=0;
                                    BackgroundY2=BackgroundY1-750;
                                }
                                BackgroundY1 += max(player1.showSpeed(),player2.showSpeed())*dt;
                                BackgroundY2 += max(player1.showSpeed(),player2.showSpeed())*dt;
                            }

                            //Press key car speed up
                            //Car go
                            if(Dmode != 1){
                                player1.go(dt);
                                player2.go(dt);
                                Cop.go(dt);
                                if(player1==Cop) {if(isG != 1)sirens.play();crash1 = 1;gameOvervs(travel,travel2);}
                                if(player2==Cop) {if(isG != 1)sirens.play();crash2 = 1;gameOvervs(travel,travel2);}
                                if(player1.position()[1]> SCREEN_HEIGHT and VSmode ==1) gameOvervs(travel,travel2);
                                if(player2.position()[1]> SCREEN_HEIGHT and VSmode ==1) gameOvervs(travel,travel2);
                            }
                            else if(clock3.getElapsedTime().asSeconds() < 5 and Dmode == 1) player1.go(dt);

                            if(!Is1 and TRmode == 1 and duration < 8){
                                trss.play();
                                Is1 = 1;
                            }
                            if(!Is2 and Dmode == 1){
                                dss.play();
                                Is2 = 1;
                            }

                            //Distance traveled
                            if(clock3.getElapsedTime().asSeconds() > 5 and Dmode == 1) travel += player1.showDist();
                            else if(Dmode != 1)travel += player1.showDist();
                            Text P1text("P1 Distance ",font,15);
                            P1text.setFillColor(Color::Blue);
                            P1text.setPosition(5,0);
                            Text P1text2(to_string((int)travel),font,15);
                            P1text2.setPosition(P1text.getPosition().x + P1text.getGlobalBounds().width,0);
                            Text P1text3(" km",font,15);
                            P1text3.setFillColor(Color::Blue);
                            if(Dmode == 1) P1text2.setFillColor(Color::Green);
                            P1text3.setPosition(P1text2.getPosition().x + P1text2.getGlobalBounds().width,0);
                            travel2 += player2.showDist();
                            Text P2text("P2 Distance ",font,15);
                            P2text.setFillColor(Color::Blue);
                            P2text.setPosition(5,20);
                            Text P2text2(to_string((int)travel2),font,15);
                            P2text2.setPosition(P2text.getPosition().x + P2text.getGlobalBounds().width,20);
                            Text P2text3(" km",font,15);
                            P2text3.setPosition(P2text2.getPosition().x + P2text2.getGlobalBounds().width,20);

                            //Distance Compare
                            if(travel<travel2 and VSmode == 1){
                                P1text2.setFillColor(Color::Red);
                                P2text2.setFillColor(Color::Green);
                                if(clock4.getElapsedTime() >= delay and VSmode == 1){
                                    int xt = rand() % 5;
                                    if(xt==0) r1s.play();
                                    if(xt==1) r2s.play();
                                    if(xt==2) r3s.play();
                                    if(xt==3) r4s.play();
                                    if(xt==4) r5s.play();
                                    clock4.restart();
                                }
                            }
                            else if(travel>travel2 and VSmode == 1){
                                P1text2.setFillColor(Color::Green);
                                P2text2.setFillColor(Color::Red);
                                if(clock4.getElapsedTime() >= delay and VSmode == 1){
                                    int xt = rand() % 5;
                                    if(xt==0) r1s.play();
                                    if(xt==1) r2s.play();
                                    if(xt==2) r3s.play();
                                    if(xt==3) r4s.play();
                                    if(xt==4) r5s.play();
                                    clock4.restart();
                                }
                            }

                            //Clear and redraw position
                            app.clear();
                            app.draw(Background);
                            app.draw(Background1);
                            app.draw(player1.drawModel());
                            if(VSmode == 1) {app.draw(player2.drawModel());app.draw(Cop.drawModel());}

                            //Mash Button
                            if(p1m == 0){
                                if(Keyboard::isKeyPressed(Keyboard::A)){
                                    P1M1.setTexture(p1m2);
                                    p1m = 1;
                                }
                            }
                            else if(!Keyboard::isKeyPressed(Keyboard::A)){
                                P1M1.setTexture(p1m1);
                                p1m = 0;
                            }

                            if(p2m == 0){
                                if(Keyboard::isKeyPressed(Keyboard::L)) {
                                    P2M1.setTexture(p2m2);
                                    p2m = 1;
                                }
                            }
                            else if(!Keyboard::isKeyPressed(Keyboard::L)){
                                P2M1.setTexture(p2m1);
                                p2m = 0;
                            }

                            Text freer("This is Free Roam. Just Drivin' And Chillin'",font,15);
                            Text outt("Press ESC To Exit This Mode",font,10);
                            if(Dmode == 0 and VSmode == 0 and TRmode == 0)
                            {
                                duration = 30.0;
                                outt.setPosition( 500 , 30 );
                                freer.setPosition( 750 , 0 );
                                app.draw(outt);
                                app.draw(freer);
                                if(Keyboard::isKeyPressed(Keyboard::Escape)) gameOver(travel);;
                            }

                            Text timer("Time left : " + to_string((int)duration) + " seconds",font,15);
                            if(TRmode == 1){
                                ostringstream scoreString;
                                scoreString << "Highest Score: " << score << " km";
                                app.draw(spr_ticon);
                                app.draw(highs);
                                timer.setPosition(880,0);
                                app.draw(timer);
                            }

                            Text dash("Your current speed : " + to_string(player1.showSpeed()),font,15);
                            if(Dmode == 1){
                                ostringstream scoreString2;
                                scoreString2 << "Highest Score: " << scored << " km";
                                app.draw(spr_ticon);
                                app.draw(highd);
                                dash.setPosition(800,0);
                                dash.setFillColor(Color::Blue);
                                app.draw(dash);
                                timer.setPosition(840,20);
                                timer.setFillColor(Color::Blue);
                                app.draw(timer);
                            }

                            Text versus("Time to deal with your friends",font,15);
                            if(VSmode == 1){
                                ostringstream scoreString1;
                                scoreString1 << "Highest Score: " << scorevs << " km";
                                app.draw(spr_vicon);
                                app.draw(highvs);
                                versus.setPosition(800,0);
                                timer.setPosition(800,20);
                                app.draw(timer);
                                app.draw(versus);
                            }

                            if(VSmode == 1) {
                                app.draw(P2text);
                                app.draw(P2text2);
                                app.draw(P2text3);
                            }

                            app.draw(P1M1);
                            if(VSmode == 1) app.draw(P2M1);
                            app.draw(P1text);
                            app.draw(P1text2);
                            app.draw(P1text3);
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
                                    TRmode = 1;
                                    VSmode = 0;
                                    Dmode = 0;
                                    spr_ButtonD.setTexture(button3);
                                    spr_ButtonTR.setTexture(cb1);
                                    spr_ButtonVS.setTexture(button2);
                                }
                                else{
                                    TRmode = 0;
                                    VSmode = 0;
                                    Dmode = 0;
                                    spr_ButtonVS.setTexture(button2);
                                    spr_ButtonD.setTexture(button3);
                                    spr_ButtonTR.setTexture(button1);
                                }
                            }
                            if (clickableArea2.contains(mousePosition)) {
                                hover.play();
                                if(spr_ButtonVS.getTexture() == &button2){
                                    VSmode = 1;
                                    TRmode = 0;
                                    Dmode = 0;
                                    spr_ButtonD.setTexture(button3);
                                    spr_ButtonVS.setTexture(cb2);
                                    spr_ButtonTR.setTexture(button1);
                                }
                                else{
                                    TRmode = 0;
                                    VSmode = 0;
                                    Dmode = 0;
                                    spr_ButtonD.setTexture(button3);
                                    spr_ButtonVS.setTexture(button2);
                                    spr_ButtonTR.setTexture(button1);
                                }
                            }
                            if (clickableArea3.contains(mousePosition)) {
                                hover.play();
                                if(spr_ButtonD.getTexture() == &button3){
                                    VSmode = 0;
                                    TRmode = 0;
                                    Dmode = 1;
                                    spr_ButtonD.setTexture(cb3);
                                    spr_ButtonVS.setTexture(button2);
                                    spr_ButtonTR.setTexture(button1);
                                }
                                else{
                                    TRmode = 0;
                                    VSmode = 0;
                                    Dmode = 0;
                                    spr_ButtonD.setTexture(button3);
                                    spr_ButtonVS.setTexture(button2);
                                    spr_ButtonTR.setTexture(button1);
                                }
                            }
                        }
                        break;

                    default:
                        break;
            }
        }
        //When mode is TR and time <= 0 go to GameOver
        if(TRmode == 1 and duration <=0){
            if(travel > score){
            ofstream scoreFile("score.txt");
            if (scoreFile.is_open()){
                scoreFile << travel;
                scoreFile.close();
                }
            }
            sleep(seconds(1));
            click.play();
            gameOver(travel);
        }

        //When mode is VS and time <= 0 go to GameOvervs
        if(VSmode == 1 and duration <=0){
            if(travel > scorevs or travel2 > scorevs){
            ofstream scoreFile1("scorevs.txt");
            if (scoreFile1.is_open()){
                if(travel > travel2) scoreFile1 << travel;
                if(travel < travel2) scoreFile1 << travel2;
                scoreFile1.close();
                }
            }
            sleep(seconds(1));
            click.play();
            gameOvervs(travel,travel2);
        }

        //When mode is D and speed <= 0 go to GameOver
        if(Dmode == 1 and duration <=0){
            if(travel > scored){
            ofstream scoreFile2("scoredash.txt");
            if (scoreFile2.is_open()){
                scoreFile2 << travel;
                scoreFile2.close();
                }
            }
            sleep(seconds(1));
            click.play();
            gameOver(travel);
        }

        app.clear();
        app.draw(player1.drawModel());
        app.draw(player2.drawModel());
        app.draw(Cop.drawModel());
        app.draw(Background);
        app.draw(Background1);
        app.draw(text_MainWindowText);
        app.draw(debugm);
        app.draw(spr_ButtonVS);
        app.draw(spr_ButtonTR);
        app.draw(spr_ButtonD);
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
        sleep(seconds(2));
        main();
    }
    return 999;
}

int gameOvervs(int dis,int dis2){
    Texture gameover;
    Font font;
    if(!gameover.loadFromFile("cars/over.png")) return 20;
    if(!font.loadFromFile("font/xirod.ttf")) return 12;
    Sprite Gameover(gameover);
    while(app.isOpen()){
        Text go("P1 Win and Got " + to_string(dis) + " km",font,30);
        Text go2("P2 Win and Got " + to_string(dis2) + " km",font,30);
        go.setPosition(SCREEN_WIDTH/2-270,SCREEN_HEIGHT/2);
        go2.setPosition(SCREEN_WIDTH/2-270,SCREEN_HEIGHT/2);
        app.clear();
        if(crash1 == 1) app.draw(go2);
        else if(crash2 == 1) app.draw(go);
        else if(dis > dis2) app.draw(go);
        else app.draw(go2);
        app.display();
        sleep(seconds(2));
        main();
    }
    return 999;
}