#include "Robot.h"
#include "Hole.h"
#include<ctime>
#include "iostream"
#include <SFML/Graphics.hpp>
int main()
{
    srandom(time(NULL));
    Hole hole({15, 10}, 15, 64, 10, 15, 4);

    sf::RenderWindow window(sf::VideoMode(hole.size.first*10+10, hole.size.second*10+10), "SFML window");

    ///PRINT ROBOTS
    std::vector<sf::RectangleShape> GR_Robots(hole.robots.size(), sf::RectangleShape(sf::Vector2f(10, 10)));
    for(int i = 0; i<hole.robots.size(); i++){
        GR_Robots[i].setPosition(sf::Vector2f(hole.robots[i].mCoordinates.first*10,
                                              hole.robots[i].mCoordinates.second*10));

    }

    std::vector<sf::RectangleShape> GR_Eat(hole.eat.size(), sf::RectangleShape(sf::Vector2f(10, 10)));
    for(int i = 0; i<hole.eat.size(); i++){
        GR_Eat[i].setPosition(sf::Vector2f(hole.eat[i].first*10,
                                           hole.robots[i].mCoordinates.second*10));
//        std::cout<<GR_Robots[i].getPosition().x<<' '<<GR_Robots[i].getPosition().y<<std::endl;
        GR_Eat[i].setFillColor(sf::Color::Red);
    }

    int past = time(NULL);

    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }


        window.clear();
        for(auto& i: GR_Robots){
            window.draw(i);
        }
        for(auto& i: GR_Eat){
            window.draw(i);
        }
        window.display();

        if(time(NULL) - past>=1 and hole.robots.size()>hole.minR){
            hole.step();
            GR_Robots = std::vector<sf::RectangleShape>(hole.robots.size(), sf::RectangleShape(sf::Vector2f(10, 10)));
            for(int i = 0; i<hole.robots.size(); i++){
                GR_Robots[i].setPosition(sf::Vector2f(hole.robots[i].mCoordinates.first*10,
                                                      hole.robots[i].mCoordinates.second*10));

            }
            GR_Eat = std::vector<sf::RectangleShape>(hole.eat.size(), sf::RectangleShape(sf::Vector2f(10, 10)));
            for(int i = 0; i<hole.eat.size(); i++){
                GR_Eat[i].setPosition(sf::Vector2f(hole.eat[i].first*10,
                                                   hole.robots[i].mCoordinates.second*10));
                GR_Eat[i].setFillColor(sf::Color::Red);
            }
            past = time(NULL);
        }
        if(hole.robots.size() <= hole.minR){
            GR_Eat.clear();
        }
    }
	return 0;
}
