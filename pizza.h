
#include <SFML/Graphics.hpp>

class Pizza
{
public:
	float dx, dy, x, y, speed, moveTimer;//добавили переменную таймер дл€ будущих целей
	int w, h;
	Texture texture;
	Sprite sprite;
	String name;

	Pizza(Image& image, float x, float y, int w, int h, String Name);
	/*{
		//x = X; y = Y; w = W; h = H;
		moveTimer = 0; name = Name;
		speed = 0; dx = 0; dy = 15;
		name = "Pizza";
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin(w / 2, h / 2);
	}*/
	void update(float elapsedTime);
};