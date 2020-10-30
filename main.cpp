#include "Robot.h"
#include "Hole.h"
#include<ctime>
#include "iostream"
#include <SFML/Graphics.hpp>
int main()
{
    srandom(time(NULL));
    Hole hole({15, 10}, 20, 64, 10, 10, 4);

    sf::RenderWindow window(sf::VideoMode(hole.size.first*10+10, hole.size.second*10+10), "SFML window");

    sf::Time sleep_time = sf::seconds(0.5);

    ///PRINT ROBOTS
    std::vector<sf::RectangleShape> GR_Robots(hole.robots.size(), sf::RectangleShape(sf::Vector2f(10, 10)));
    for(int i = 0; i<hole.robots.size(); i++){
        GR_Robots[i].setPosition(sf::Vector2f(hole.robots[i].mCoordinates.first*10,
                                              hole.robots[i].mCoordinates.second*10));

    }
    ///PRINT EAT
    std::vector<sf::RectangleShape> GR_Eat(hole.eat.size(), sf::RectangleShape(sf::Vector2f(10, 10)));
    for(int i = 0; i<hole.eat.size(); i++){
        GR_Eat[i].setPosition(sf::Vector2f(hole.eat[i].first*10,
                                           hole.robots[i].mCoordinates.second*10));

        GR_Eat[i].setFillColor(sf::Color::Red);
    }

    ///MAIN LOOP
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
        for(auto& i: GR_Eat){
            window.draw(i);
        }
        for(auto& i: GR_Robots){
            window.draw(i);
        }

        window.display();

        if(hole.robots.size()>hole.minR) {
            hole.step();
            GR_Robots = std::vector<sf::RectangleShape>(hole.robots.size(), sf::RectangleShape(sf::Vector2f(10, 10)));
            for (int i = 0; i < hole.robots.size(); i++) {

                GR_Robots[i].setPosition(sf::Vector2f(hole.robots[i].mCoordinates.first * 10,
                                                      hole.robots[i].mCoordinates.second * 10));

            }
            GR_Eat = std::vector<sf::RectangleShape>(hole.eat.size(), sf::RectangleShape(sf::Vector2f(10, 10)));
            for (int i = 0; i < hole.eat.size(); i++) {
                GR_Eat[i].setPosition(sf::Vector2f(hole.eat[i].first * 10,
                                                   hole.eat[i].second * 10));
                GR_Eat[i].setFillColor(sf::Color::Red);
            }
        }else{
            GR_Eat.clear();
        }
        sf::sleep(sleep_time);
    }
	return 0;
}
