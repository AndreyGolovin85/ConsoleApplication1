#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Chef
{
    // Все private переменные могут быть доступны только внутри объекта
private:

    // Позиция повара
    Vector2f Chef_Position;

    // Объявляем объект Sprite
    Sprite Chef_Sprite;

    // Добавляем текстуру и загружаем картинку повара.
    Image image_m;
    Texture image_Texture;

    // Скорость повара в пикселях в секунду
    float Speed_Chef;

    // Открытые методы
public:

    // Настраиваем повара в конструкторе
    Chef();

    // Для отправки спрайта в главную функцию
    Sprite getSprite();

    // Эта функция будет вызываться на каждый кадр
    void update(float elapsedTime);
};
