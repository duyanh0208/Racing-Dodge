#include<iostream>
#include<cstdlib>
#include<ctime>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;


//Init game const
const double SCREEN_WIDTH=800;
const double SCREEN_HEIGHT=600;
const int borderLeft=140;
const int borderRight=660;
const int racerWidth=40;
const int racerHeight=70;
string stringscore="";
int score=0;
double gameSpeed=0.15;
double BackgroundY1=0;
double BackgroundY2=-600;
int max_score = 0;
double RacerX, RacerY,Obs1X, Obs1Y,Obs2X, Obs2Y,Obs3X, Obs3Y,Obs4X, Obs4Y;

//Init texture
Texture background, racer, obs1, obs2, obs3, obs4,gameover,background_menu,tutor_menu;

//Init Sprite
Sprite Background,Background1,Racer,Obs1,Obs2,Obs3,Obs4,Gameover,bkg_menu,tutorial_menu;

//Init Text
Text Play_button, about_button, exit_button;

//Init font
Font myfont;

//Init Sound
Sound GameSound;
SoundBuffer gameSoundBuffer;
/*#define Max_main_menu 4

class MainMenu
{
public:
    MainMenu(float width, float height);

    void draw(RenderWindow& window);
    void MoveUp();
    void MoveDown();

    int MainMenuPressed()
    {
        return MainMenuSelected;
    }
    ~MainMenu();

private:
    int MainMenuSelected;
    Font font;
    Text mainMenu[Max_main_menu];

};*/



//Create Main Windows
RenderWindow app(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),"Racing Dodge");

//Creat random Number for game loop
int getRandomNumber(int a, int b);

// Create gameover screen
void gameOver();

int set_texture()
{
    //Load all images
    if (!background.loadFromFile("cars/background.png")) return EXIT_FAILURE;
    if (!racer.loadFromFile("cars/racer.png")) return EXIT_FAILURE;
    if (!obs1.loadFromFile("cars/obs1.png")) return EXIT_FAILURE;
    if (!obs2.loadFromFile("cars/obs2.png")) return EXIT_FAILURE;
    if (!obs3.loadFromFile("cars/obs3.png")) return EXIT_FAILURE;
    if (!obs4.loadFromFile("cars/obs4.png")) return EXIT_FAILURE;
    if (!gameover.loadFromFile("cars/over.png")) return EXIT_FAILURE;
    if (!background_menu.loadFromFile("cars/bkg.png")) return EXIT_FAILURE;
    if (!tutor_menu.loadFromFile("cars/tutorial.png")) return EXIT_FAILURE;
}

void load_sprite();
bool mouse_inside_text (Text spr)
{
    Vector2i mousePos = Mouse::getPosition(app);
    if( mousePos.x > spr.getPosition().x
            && mousePos.x < spr.getPosition().x + spr.getGlobalBounds().width
            && mousePos.y > spr.getPosition().y && mousePos.y < spr.getPosition().y + spr.getGlobalBounds().height
      )
    {
        return true;
    }
    else
    {
        return false;
    }
}

void play_game()
{
    score = 0 ;
    RacerX=SCREEN_WIDTH/2;
	RacerY=SCREEN_HEIGHT-racerHeight;
	Obs1X=getRandomNumber(borderLeft,borderRight);
	Obs2X=getRandomNumber(borderLeft,borderRight);
	Obs3X=getRandomNumber(borderLeft,borderRight);
	Obs4X=getRandomNumber(borderLeft,borderRight);
    Obs1Y=0,Obs2Y=-100,Obs3Y=-200,Obs4Y=-300;

    GameSound.play();
    GameSound.setLoop(true);


    while(app.isOpen())
    {
        stringscore="SCORE:"+to_string(score);
        Text text(stringscore, myfont, 15);
        text.setPosition(5,0);

        //Set car position
        Racer.setPosition(RacerX,RacerY);
        Obs1.setPosition(Obs1X,Obs1Y);
        Obs2.setPosition(Obs2X,Obs2Y);
        Obs3.setPosition(Obs3X,Obs3Y);
        Obs4.setPosition(Obs4X,Obs4Y);

        //Creat scrolling background
        Background.setPosition(0,BackgroundY1);
        Background1.setPosition(0,BackgroundY2);

        if (BackgroundY2 > 0)
        {
            BackgroundY1 = 0;
            BackgroundY2 = BackgroundY1 - 500;
        }
        BackgroundY1 += 0.1;
        BackgroundY2 += 0.1;

        //Set Obs LOOP
        if (Obs1Y > SCREEN_HEIGHT)
        {
            Obs1Y = 0;
            Obs1X = getRandomNumber(borderLeft, borderRight);
            score++;
        }
        else
        {
            Obs1Y = Obs1Y + gameSpeed;
        }

        if (Obs2Y > SCREEN_HEIGHT)
        {
            Obs2Y = 0;
            Obs2X = getRandomNumber(borderLeft, borderRight);
            score++;
        }
        else
        {
            Obs2Y = Obs2Y+gameSpeed;
        }
        if (Obs3Y > SCREEN_HEIGHT)
        {
            Obs3Y = 0;
            Obs3X = getRandomNumber(borderLeft, borderRight);
            score++;
        }
        else
        {
            Obs3Y = Obs3Y + gameSpeed;
        }

        if (Obs4Y>SCREEN_HEIGHT)
        {
            Obs4Y = 0;
            Obs4X = getRandomNumber(borderLeft,borderRight);
            score++;
        }
        else
        {
            Obs4Y = Obs4Y + gameSpeed;
        }


        //Game level
        if (score>10 && score<25)
        {
            gameSpeed=0.2;
        }
        if (score>25 && score<40)
        {
            gameSpeed=0.25;
        }
        if (score>40 && score<60)
        {
            gameSpeed=0.3;
        }
        if (score>60)
        {
            gameSpeed=0.35;
        }
        if (score>100)
        {
            gameSpeed=0.4;
        }
        if (score>150)
        {
            gameSpeed=0.5;
        }

        //Create event to handle input from keyboard
        Event event;
        while (app.pollEvent(event))
        {
            if (event.type == Event::Closed)
                app.close();

            if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Left)
                    {
                        if(RacerX>borderLeft)
                        {
                            RacerX=RacerX-30;
                        }
                    }
                    if (event.key.code == sf::Keyboard::Right)
                    {
                        if(RacerX<borderRight)
                        {
                            RacerX=RacerX+30;
                        }
                    }
                    if (event.key.code == sf::Keyboard::Up)
                    {
                        if(RacerY>0)
                        {
                            RacerY=RacerY-30;
                        }
                    }
                    if (event.key.code == sf::Keyboard::Down)
                    {
                        if(RacerY<SCREEN_HEIGHT-70)
                        {
                            RacerY=RacerY+30;
                        }
                    }
                }
        }


        //Check if accident happen
        if (((RacerX>=(Obs1X-30)) &&(RacerX<=(Obs1X+30)))&&((RacerY>=(Obs1Y-30)) &&(RacerY)<=(Obs1Y+30)))
        {
            GameSound.stop();
            gameOver();
            return ;
        }

        else if (((RacerX>=(Obs2X-30)) &&(RacerX<=(Obs2X+30)))&&((RacerY>=(Obs2Y-30)) &&(RacerY)<=(Obs2Y+30)))
        {
            GameSound.stop();
            gameOver();
            return ;
        }

        else if (((RacerX>=(Obs3X-30)) &&(RacerX<=(Obs3X+30)))&&((RacerY>=(Obs3Y-30)) &&(RacerY)<=(Obs3Y+30)))
        {
            GameSound.stop();
            gameOver();
            return ;
        }

        else if (((RacerX>=(Obs4X-30)) &&(RacerX<=(Obs4X+30)))&&((RacerY>=(Obs4Y-30)) &&(RacerY)<=(Obs4Y+30)))
        {
            GameSound.stop();
            gameOver();
            return ;
        }
        //Clear and redraw position
        app.clear();
        app.draw(Background);
        app.draw(Background1);
        app.draw(Racer);
        app.draw(Obs1);
        app.draw(Obs2);
        app.draw(Obs3);
        app.draw(Obs4);
        app.draw(text);
        app.display();
    }
}
void tutorial()
{
    Text Back_to_menu;
    Back_to_menu.setFont(myfont);
    Back_to_menu.setPosition(5,5);
    Back_to_menu.setString("Back to menu");
    while(app.isOpen())
    {
        Event event;
        while (app.pollEvent(event))
        {
            if (event.type == Event::Closed)
                app.close();
        }
        if(mouse_inside_text(Back_to_menu))
        {
            Back_to_menu.setFillColor(Color::Blue);
            if(Mouse::isButtonPressed(Mouse::Left))
            {
                return ;
            }
        }
        else Back_to_menu.setFillColor(Color::White);
        app.clear();
        app.draw(tutorial_menu);
        app.draw(Back_to_menu);
        app.display();
    }
}
int main()
{
    myfont.loadFromFile("font/bubbleyummy.ttf");

    //Init game music
    gameSoundBuffer.loadFromFile("sound/game.wav");

    GameSound.setBuffer(gameSoundBuffer);

    set_texture();

    load_sprite();

        Play_button.setFont(myfont);
        Play_button.setPosition(350,240);
        Play_button.setString("Play");

        about_button.setFont(myfont);
        about_button.setPosition(350,320);
        about_button.setString("About");

        exit_button.setFont(myfont);
        exit_button.setPosition(350,400);
        exit_button.setString("Exit");


    //Set racer and Obs pos
    //GAME LOOP
    while(app.isOpen())
    {
        Event event;
        while (app.pollEvent(event))
        {
            if (event.type == Event::Closed)
                app.close();
        }
        if(mouse_inside_text(Play_button))
        {
            Play_button.setColor(Color::Blue);
            if(Mouse::isButtonPressed(Mouse::Left))
            {
                play_game();
            }
        }
        else Play_button.setFillColor(Color::White);
        if(mouse_inside_text(about_button))
        {
            about_button.setColor(Color::Blue);
            if(Mouse::isButtonPressed(Mouse::Left))
            {
                tutorial();
            }
        }
        else about_button.setFillColor(Color::White);
        if(mouse_inside_text(exit_button))
        {
            exit_button.setColor(Color::Blue);
            if(Mouse::isButtonPressed(Mouse::Left))
            {
                app.close();
            }
        }
        else exit_button.setFillColor(Color::White);
        app.clear();
        app.draw(bkg_menu);
        app.draw(Play_button);
        app.draw(about_button);
        app.draw(exit_button);
        app.display();
//        play_game();
    }

    return EXIT_SUCCESS;
}
//int startGame()
//{
//    //TODO
//}
//Game over

void load_sprite()
{
    Background.setTexture(background),
    Background1.setTexture(background),
    Racer.setTexture(racer),
    Obs1.setTexture(obs1),
    Obs2.setTexture(obs2),
    Obs3.setTexture(obs3),
    Obs4.setTexture(obs4);
    Gameover.setTexture(gameover);
    bkg_menu.setTexture(background_menu);
    tutorial_menu.setTexture(tutor_menu);
}
void gameOver()
{
    Texture troll;
    troll.loadFromFile("cars/troll.png");
    Sprite Troll(troll);
    Troll.setPosition(10,350);

    SoundBuffer gameOver;
        gameOver.loadFromFile("sound/crash.wav");
    Sound GameOver;
        GameOver.setBuffer(gameOver);
        GameOver.play();
    max_score=max(max_score,score);
    string highscore = "Your high score:" +to_string(max_score);
    while (app.isOpen())
    {
        Event event;
        while (app.pollEvent(event))
        {
            if (event.type == Event::Closed)
                app.close();
        }
//        Font myfont;
//        myfont.loadFromFile("font/bubbleyummy.ttf");
        stringscore="YOUR SCORE:"+to_string(score);

        Text text(stringscore, myfont, 30);
        text.setPosition(210,450);

        Text text_again("Play again", myfont, 30);
        text_again.setPosition(500,450);

        Text high_score(highscore,myfont,30);
        high_score.setPosition(210,410);
        if(mouse_inside_text(text_again))
        {
            text_again.setColor(Color::Blue);
            if(Mouse::isButtonPressed(Mouse::Left)) return ;
        }
        else text_again.setColor(Color::White);

        app.clear();
        app.draw(Gameover);
        app.draw(text);
        app.draw(text_again);
        app.draw(high_score);
        app.draw(Troll);
        app.display();
    }

}

int getRandomNumber(int a, int b)
{
    static bool first = true;
    if (first)
    {
        srand(time(NULL));
        first = false;
    }
    int result = a + rand() % (( b + 1 ) - a);
    result = (result/10) * 10;
    return result;
}
