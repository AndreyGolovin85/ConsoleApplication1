#include <SFML/Graphics.hpp>
#include <list>
using namespace sf;

class Pizza
{
public:
	float dx, dy, x, y, speed, moveTimer;//добавили переменную таймер для будущих целей
	int w, h;
	Texture texture;
	Sprite sprite;
	String name;

	Pizza(Image& image, float X, float Y, int W, int H, String Name)
	{
		x = X; y = Y; w = W; h = H; moveTimer = 0; name = Name;
		speed = 0; dx = 0; dy = 15;
		name = "Pizza";
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin(w / 2, h / 2);

	}
	void update(float time)
	{
		if (y <= 700)
		{//для персонажа с таким именем логика будет такой
			y += (dy * time) * 20;
			sprite.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта в место его центра
		}
	}
};
