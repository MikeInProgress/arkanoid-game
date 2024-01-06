 
#include <utility>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include <random>
#include <vector>
#include <sstream>
#include "Game.h"


sf::Vertex Game::stars[2000];
sf::Clock Game::clock;

Game::Game() {
    
}

Game::Game(sf::String title) : sf::RenderWindow(sf::VideoMode(1120, 630,32), title) {
    this->setActive(true);
    this->setFramerateLimit(60);
    this->setVerticalSyncEnabled(true);

    this->setPosition(sf::Vector2i(0,0));
    this->setKeyRepeatEnabled(false);

   //this->end_credits.setFont(Game::font);
    //this->end_credits.setPosition(0,0);
    this->end_credits.setCharacterSize(30);
    this->end_credits.setFillColor(sf::Color::White);
    this->end_credits.setStyle(sf::Text::Bold);

    this->Time_max = sf::seconds(90);


    

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(1, 3500000);
    int Random_number = distr(gen);

    if ((Random_number % 2) == 0)
    {
        std::cout << "%2 = " << Random_number << std::endl;
        this->Background_Tx.loadFromFile("D:/Projects/game/2D/img/Space_1.png");
    }
    else
    {
        std::cout << "Else = " << Random_number << std::endl;
        this->Background_Tx.loadFromFile("D:/Projects/game/2D/img/Space_2.png");
    }

    this->Background.setTexture(&(this->Background_Tx));
    this->Background.setPosition(0, 0);
    this->Background.setSize(sf::Vector2f(1120,630));

    for (int i = 0; i < 2000; i++)
    {

       Game::stars[i].position = sf::Vector2f(static_cast<float>(distr(gen)%1120), static_cast<float>(distr(gen)%630));
       std::cout <<"Numer i : " << i << ", " << distr(gen) % 1120 << " " << distr(gen) % 630 << std::endl;
       if (not(Random_number%2)) Game::stars[i].color = sf::Color(155, 155, 155, 255);
       else Game::stars[i].color = sf::Color(0, 0, 0, 255); std::cout <<"Black";

    }





}

Game::~Game() {
    
}

void Game::run() {
    Set_Window(this->getSystemHandle());

    sf::Time Time_Start_game = Game::clock.getElapsedTime();
    sf::Time tick = sf::microseconds(0);
    sf::Time Time_of_pause;

    sf::Event E;
    sf::Transform Move;

    unsigned cage;

    while (this->isOpen())
    {
        while (this->pollEvent(E)) {
            if (E.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) this->close();
            if (E.type == sf::Event::KeyPressed && E.key.code == sf::Keyboard::P) this->pause = (this->pause) ? false : true;


        }

        if (this->pause)
        {//??
            this->clear(sf::Color(0xffffffff));
            this->draw(this->Background);
            this->display();
            Game::clock.restart();
            Time_of_pause = Time_Start_game;
            std::cout << "Time : " << Time_of_pause.asSeconds();
            continue;
        }


        this->draw(this->Background);
       
        this->clear(sf::Color(0xffffffffff));
        this->draw(this->Background);

       this->draw(Game::stars, 1000, sf::PrimitiveType::Points);
       for (int i = 0; i < 1000; i++)
        {
         Game::stars[i].position.x -= (i % 5 + 1);
        
         if (Move.transformPoint(Game::stars[i].position).x <= 0)
         {
             Game::stars[i].position = sf::Vector2f(1120, Game::stars[i].position.y);
         }
        }

        this->display();
    }
}

void Game::end_game(Interceptor* interceptor) {
    
}

void Game::startconsole()
{
    std::stringstream buffer;
    buffer << "Konsola" << time(0);
    std::string String = buffer.str();

    std::wstring Temporary_sring = std::wstring(String.begin(), String.end());

    LPCWSTR API_wc = Temporary_sring.c_str();
    HWND API_handle = GetConsoleWindow();

    SetWindowText(API_handle, API_wc);
    SetWindowPos(API_handle,HWND_TOPMOST,0,0,1120,630,SWP_NOMOVE);


}

void Game::Set_Window(HWND pointer_API)
{
    RECT rect;
    GetWindowRect(pointer_API, &rect);
    SetWindowPos(pointer_API, HWND_TOPMOST, rect.left, rect.top, rect.right, rect.bottom, SWP_NOMOVE);
    SetWindowLong(pointer_API, GWL_EXSTYLE, GetWindowLong(pointer_API, GWL_EXSTYLE) | WS_EX_LAYERED);
    SetLayeredWindowAttributes(pointer_API, 0x000000, 0xff, LWA_ALPHA);
}












