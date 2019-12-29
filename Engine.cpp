#include <SFML/Graphics.hpp>
#include "Engine.h"
#include "chef.h"
#include "pan.h"
using namespace sf;

Engine::Engine()
{
    // Получаем разрешение экрана, создаем окно SFML и View
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;

    Window.create(VideoMode(800, 600), "Panic in the Pizzeria");

    // Загружаем фон в текстуру
    BackgroundTexture.loadFromFile("image/wall.jpg");
    // Связываем спрайт и текстуру
    BackgroundSprite.setTexture(BackgroundTexture);
}

void Engine::input()
{
    // Обрабатываем нажатие Escape
    if (Keyboard::isKeyPressed(Keyboard::Escape))
    {
        Window.close();
    }

    // Обрабатываем нажатие клавиш движения
    if (Keyboard::isKeyPressed(Keyboard::Left))
    {
        pan.moveLeft();
    }
    else
    {
        pan.stopLeft();
    }

    if (Keyboard::isKeyPressed(Keyboard::Right))
    {
        pan.moveRight();
    }
    else
    {
        pan.stopRight();
    }

}

void Engine::update(float dtAsSeconds)
{
    pan.update(dtAsSeconds);
}

void Engine::draw()
{
    // Стираем предыдущий кадр
    Window.clear(Color::White);

    // Отрисовываем фон
    Window.draw(BackgroundSprite);
    // Отрисовываем повара
    Window.draw(chef.getSprite());
    // И Сковороду
    Window.draw(pan.getSprite());

    // Отображаем все, что нарисовали
    Window.display();
}

void Engine::start()
{
    // Расчет времени
    Clock clock;
    Event event;

    while (Window.isOpen())
    {
        while (Window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                Window.close();
        }
 
        // Перезапускаем таймер и записываем отмеренное время в dt
        Time dt = clock.restart();

        float dtAsSeconds = dt.asSeconds();

        input();
        update(dtAsSeconds);
        draw();
    }
}