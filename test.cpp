/*
 * @Author: Wannabtl
 * @Date: 2021-10-30 11:42:31
 * @LastEditTime: 2021-10-30 11:56:30
 * @Description: 
 */
#include <bits/stdc++.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
int main(int argc, char const *argv[])
{
    sf::RenderWindow window(sf::VideoMode(400, 400), "Circle");
    window.setFramerateLimit(60);

    sf::CircleShape circle(150);
    circle.setFillColor(sf::Color::Blue);
    circle.setPosition(10, 20);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed
                or (event.type == sf::Event::KeyPressed 
                    and event.key.code == sf::Keyboard::Escape) ) {
                window.close();
            }
            window.clear();
            window.draw(circle);
            window.display();
        }
    }
    return 0;
}