#include "headers/Field.h"
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

Field field(100, 100, 2500, 1000, 1000, 100);

void updateWindow(sf::RenderWindow& window){
    sf::Time t1 = sf::seconds(0.5f);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
//        std::vector<sf::RectangleShape> to_draw;
        for(int i = 0; i<field.field.size(); i++){
            for(int j = 0; j<field.field[i].size(); j++){
                if(field.field[i][j] != NULL){
                    sf::RectangleShape rectangle(sf::Vector2f(10, 10));
                    rectangle.setPosition(sf::Vector2f(j*10, i*10));
                    if(field.field[i][j] ->type == "Robot"){
                        rectangle.setFillColor(sf::Color::Blue);
                    }
                    if(field.field[i][j] ->type == "Eat"){
                        rectangle.setFillColor(sf::Color::Red);
                    }
                    if(field.field[i][j] ->type == "Poison"){
                        rectangle.setFillColor(sf::Color::Green);
                    }
                    if(field.field[i][j] ->type == "Wall"){
                        rectangle.setFillColor(sf::Color::White);
                    }
                    window.draw(rectangle);
                }
            }
        }
        window.display();
        field.Step();
//        sf::sleep(t1);
    }
}



int main()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(1010, 1010), "My window");
    updateWindow(window);

    return 0;
}

