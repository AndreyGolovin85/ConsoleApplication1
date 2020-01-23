#include <SFML/Graphics.hpp>
#include "pan.h"
#include "Engine.h"
using namespace sf;

Pan::Pan()
{
   
    Speed_Pan = 300;     // Переменная скорости сковороды.
    Pan_Position.x = 380;// Переменная x  сковороды.
    Pan_Position.y = 575;// Переменная y сковороды.

    //Загружаем изображение и связываем текстуру и спрайт.
    Pan_Image.loadFromFile("image/pan1.bmp");
    Pan_Image.createMaskFromColor(Pan_Image.getPixel(1, 1));       // Удаляем белый фон у картинки

    Pan_Texture.loadFromImage(Pan_Image);
    Pan_Sprite.setTexture(Pan_Texture);
    Pan_Sprite.setPosition(Pan_Position);//(380, 552);
    Pan_Sprite.setOrigin(Pan_Sprite.getTextureRect().width/2 , Pan_Sprite.getTextureRect().height/2);

}
    Sprite Pan::getSprite()
    {
        return Pan_Sprite;
    }

    void Pan::moveLeft()
    {
        LeftPressed = true;
    }

    void Pan::moveRight()
    {
        RightPressed = true;
    }

    void Pan::stopLeft()
    {
        LeftPressed = false;
    }

    void Pan::stopRight()
    {
       RightPressed = false;
    }

    // Двигаем сковороду на основании пользовательского ввода в этом кадре,
    // прошедшего времени и скорости
    void Pan::update(float elapsedTime)
    {
        if (Pan_Sprite.getPosition().x > 760)                                   // Проверяем 
            Pan_Sprite.setPosition(800, Pan_Sprite.getPosition().y);     // Достигла ли сковорда
        else                                                                                // Правого края экрана, если да то сковорда останавливается.

        if (RightPressed)
        {
            Pan_Position.x += Speed_Pan * elapsedTime;                 // К позиции сковороды прибавляем скоррость умноженную на время.
        }

        if (Pan_Sprite.getPosition().x < 40)                                        //  аналогично только в лево
            Pan_Sprite.setPosition(0, Pan_Sprite.getPosition().y);
        else

        if (LeftPressed)
        {
            Pan_Position.x -= Speed_Pan * elapsedTime;
        }

        // Теперь сдвигаем спрайт на новую позицию
        Pan_Sprite.setPosition(Pan_Position);
    }