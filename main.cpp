#include "Robot.h"
#include "Field.h"
#include<ctime>
#include "iostream"
#include <SFML/Graphics.hpp>
#include<fstream>

int main()
{
    srand(time(NULL));
    Field field({ 100, 100 }, 64, 64, 100, 2000, 8, 1000, 1000);

    sf::RenderWindow window(sf::VideoMode(field.size.first * 10 + 600, field.size.second * 10 + 10), "SFML window");

    sf::Time sleep_long = sf::seconds(1);
    sf::Time sleep_short = sf::seconds(0.1);
    sf::Font font;
    font.loadFromFile("/home/pashs/Downloads/ArialMT.ttf"); //NEED TO CHANGE
    std::freopen("data.log", "w", stdout);
    ///PREPRINT ROBOTS
    std::vector<sf::RectangleShape> GR_Robots(field.robots.size(), sf::RectangleShape(sf::Vector2f(10, 10)));
    for (int i = 0; i < field.robots.size(); i++) {
        GR_Robots[i].setPosition(sf::Vector2f(field.robots[i].mCoordinates.first * 10,
                                              field.robots[i].mCoordinates.second * 10));
        GR_Robots[i].setFillColor(sf::Color::Blue);
    }
    ///PREPRINT EAT
    std::vector<sf::RectangleShape> GR_Eat(field.eat.size(), sf::RectangleShape(sf::Vector2f(10, 10)));
    for (int i = 0; i < field.eat.size(); i++) {
        GR_Eat[i].setPosition(sf::Vector2f(field.eat[i].first * 10,
                                           field.eat[i].second * 10));

        GR_Eat[i].setFillColor(sf::Color::Green);
    }
    ///PREPRINT WALL
    std::vector<sf::RectangleShape> GR_Walls(field.walls.size(), sf::RectangleShape(sf::Vector2f(10, 10)));
    for (int i = 0; i < field.walls.size(); i++) {
        GR_Walls[i].setPosition(sf::Vector2f(field.walls[i].first * 10,
                                             field.walls[i].second * 10));

        //GR_Walls[i].setFillColor(sf::Color::Grey);
    }
    ///PREPRINT POISON
    std::vector<sf::RectangleShape> GR_Poison(field.poison.size(), sf::RectangleShape(sf::Vector2f(10, 10)));
    for (int i = 0; i < field.walls.size(); i++) {
        GR_Poison[i].setPosition(sf::Vector2f(field.poison[i].first * 10,
                                              field.poison[i].second * 10));

        GR_Poison[i].setFillColor(sf::Color::Red);
    }

    std::vector<sf::Text> results;
    sf::Text c_step;
    c_step.setFont(font);
    c_step.setString(std::to_string(0));
    c_step.setPosition(field.size.first * 10 + 100, 0);
    ///MAIN LOOP
    int steps = 0;
    int eras = 0;
    sf::RectangleShape block;
    block.setSize(sf::Vector2f(10, field.size.second * 10 + 10));
    block.setPosition(sf::Vector2f(field.size.first * 10, 0));
    sf::Text era;
    era.setFont(font);
    era.setString(std::to_string(eras));
    era.setPosition(field.size.first * 10 + 20, 0);
    bool TAB = true;
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Tab)
                TAB = !TAB;
            if(event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Space)
                std::cout<<-eras<<' '<<steps<<std::endl;
        }


        window.clear();
        if(TAB){
            for (auto& i : GR_Eat) {
                window.draw(i);
            }

            for (auto& i : GR_Poison) {
                window.draw(i);
            }
            for (auto& i : GR_Robots) {
                window.draw(i);
            }
            for (auto& i : GR_Walls) {
                window.draw(i);
            }
        }

        for (auto& i :results) {
            window.draw(i);
        }
        window.draw(block);
        window.draw(era);

        window.display();
        if(!field.step()){
            steps++;
            if(TAB){
                GR_Robots = std::vector<sf::RectangleShape>(field.robots.size(), sf::RectangleShape(sf::Vector2f(10, 10)));
                for (int i = 0; i < field.robots.size(); i++) {
                    GR_Robots[i].setPosition(sf::Vector2f(field.robots[i].mCoordinates.first * 10,
                                                          field.robots[i].mCoordinates.second * 10));
                    GR_Robots[i].setFillColor(sf::Color::Blue);
                }
                GR_Eat = std::vector<sf::RectangleShape>(field.eat.size(), sf::RectangleShape(sf::Vector2f(10, 10)));
                for (int i = 0; i < field.eat.size(); i++) {
                    GR_Eat[i].setPosition(sf::Vector2f(field.eat[i].first * 10,
                                                       field.eat[i].second * 10));

                    GR_Eat[i].setFillColor(sf::Color::Green);
                }
                GR_Walls = std::vector<sf::RectangleShape>(field.walls.size(), sf::RectangleShape(sf::Vector2f(10, 10)));
                for (int i = 0; i < field.walls.size(); i++) {
                    GR_Walls[i].setPosition(sf::Vector2f(field.walls[i].first * 10,
                                                         field.walls[i].second * 10));

                    //GR_Walls[i].setFillColor(sf::Color::Grey);
                }
                GR_Poison = std::vector<sf::RectangleShape>(field.poison.size(), sf::RectangleShape(sf::Vector2f(10, 10)));
                for (int i = 0; i < field.walls.size(); i++) {
                    GR_Poison[i].setPosition(sf::Vector2f(field.poison[i].first * 10,
                                                          field.poison[i].second * 10));

                    GR_Poison[i].setFillColor(sf::Color::Red);
                }
            }

        }else {
            eras++;
            era.setString(std::to_string(eras));
            sf::Text c_step;
            c_step.setFont(font);
            c_step.setString(std::to_string(steps));
            c_step.setPosition(field.size.first * 10 + 100, 0);
            if(results.size()<35){
                for(auto& i: results){
                    i.move(0, 25);
                }
                results.push_back(c_step);
            }else{
                for(auto& i: results){
                    i.move(0, 25);
                }
                results.erase(results.begin());
                results.push_back(c_step);
            }
            GR_Eat.clear();
            std::cout <<eras<<' '<< steps << ' '<<std::endl;
            steps = 0;
            //sf::sleep(sleep_long);
//			field.eat.clear();
//			field.new_era();

        }

    }
    return 0;
}