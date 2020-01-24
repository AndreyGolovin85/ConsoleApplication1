#pragma once
#include <SFML/Graphics.hpp>
#include "pan.h"
#include "chef.h"
#include "pizza.h"
using namespace sf;

class Engine
{
private:

    RenderWindow Window;
    // Объявляем спрайт и текстуру для фона
    Sprite BackgroundSprite;
    Texture BackgroundTexture;

    // Экземпляр повара
    Chef chef;
    // Экземпляр сковороды
    Pan pan;
    // Экземпляр пиццы
    Pizza pizza;

    void input();
    void update(float dtAsSeconds);
    void draw();

public:
    // Конструктор движка
    Engine();

    // Функция старт вызовет все приватные функции
    void start();

};
