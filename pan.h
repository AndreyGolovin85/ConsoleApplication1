#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Pan
{
private:
	// Позиция сковороды
	Vector2f Pan_Position;

	// ОбЪявляем обЪект спрайт.
	Sprite Pan_Sprite;

	// Загружаем картинку и добавляем текстуру.
	Image Pan_Image;
	Texture Pan_Texture;

    // Логические переменные для отслеживания направления движения
    bool LeftPressed;
    bool RightPressed;

    // Скорость скороды в пикселях в секунду
    float Speed_Pan;

    // Открытые методы
public:

    // Настраиваем сковороду в конструкторе
    Pan();

    // Для отправки спрайта в главную функцию
    Sprite getSprite();

    // Для движения сковороды
    void moveLeft();
    void moveRight();

    // Прекращение движения
    void stopLeft();
    void stopRight();

    // Эта функция будет вызываться на каждый кадр
    void update(float elapsedTime);
};
