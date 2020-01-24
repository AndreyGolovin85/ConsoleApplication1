#include <SFML/Graphics.hpp>
#include "pizza.h"
using namespace sf;

Pizza::Pizza()
{
    //Переменная скорости повара.
    Speed_Pizza = 100;
    //Устнавливаем начальную позицию повара в пикселях.
    Pizza_Position.x = 52;  // Переменная x  пиццы.
    Pizza_Position.y = 80;  // Переменная y пиццы.

    //Загружаем изображение и связываем текстуру и спрайт.
    image_Pizza.loadFromFile("image/pizza.bmp");                             // Загружаем картинку
    image_Pizza.createMaskFromColor(image_Pizza.getPixel(0, 0));       // Удаляем белый фон картинки

    image_Texture.loadFromImage(image_Pizza);                               // Делаем из картинки текстуру
    Pizza_Sprite.setTexture(image_Texture);                                        // Делаем из текстуры спрайт
    Pizza_Sprite.setPosition(Pizza_Position);                                        // Задаем начальные координаты
}

// Эту функцию надо убрать из этого места.
void Pizza::update(float elapsedTime)
{
    Pizza_Position.y += Speed_Pizza * elapsedTime;          // К позиции пиццы прибавляем скоррость умноженную на время.

    // Сдвигаем спрайт на новую позицию
    Pizza_Sprite.setPosition(Pizza_Position);
}
Sprite Pizza::getSprite()
{
    return Pizza_Sprite;
}
