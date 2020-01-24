#include <SFML/Graphics.hpp>
#include "chef.h"
using namespace sf;

Chef::Chef()
{
    //ѕеременна€ скорости повара.
    Speed_Chef = 10;

    //«агружаем изображение и св€зываем текстуру и спрайт.
    image_Chef.loadFromFile("image/chef.bmp");
    image_Chef.createMaskFromColor( image_Chef.getPixel(0, 0));       // ”дал€ем синий фон картинки

    image_Texture.loadFromImage(image_Chef);
    Chef_Sprite.setTexture(image_Texture);
    Chef_Sprite.setPosition(30, 15);

    //”стнавливаем начальную позицию повара в пиксел€х.
    Chef_Position.x = 30;
    Chef_Position.y = 90;
}
Sprite Chef::getSprite()
{
    return Chef_Sprite;
}