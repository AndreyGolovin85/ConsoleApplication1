#include <SFML/Graphics.hpp>
#include <windows.h>
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


int main()
{
	HWND hConsole = GetConsoleWindow();//Если компилятор старый заменить на GetForegroundWindow()
	ShowWindow(hConsole, SW_HIDE);//прячем окно консоли

	// Объект, который, собственно, является главным окном приложения
	RenderWindow window(VideoMode(800, 600), "Panic in the Pizzeria");

	Image PizzaImage;
	PizzaImage.loadFromFile("image/pizza.bmp");//загрузка изображения пиццы
	PizzaImage.createMaskFromColor(PizzaImage.getPixel(0, 0));
	Pizza easyPizza(PizzaImage, 400, 70, 50, 50, "Pizza");//пицца, объект класса пицца

	// Переменная времени
	Clock clock;
	// Главный цикл приложения: выполняется, пока открыто окно
	while (window.isOpen())
	{
		// Дать прошедшее время в секундах
		float time = clock.getElapsedTime().asSeconds();
		// перезагружаем время
		clock.restart();
		// Переменная времени для игры
		time = time / 2;
		// Обрабатываем события в цикле
		Event event;
		while (window.pollEvent(event))
		{
			// Пользователь нажал на «крестик» и хочет закрыть окно?
			if (event.type == Event::Closed)
				// тогда закрываем его
				window.close();
		}
		// Установка цвета фона - белый
		window.clear(Color::White);
		//easyPizza update function
		easyPizza.update(time);
		// Отрисовка спрайта
		window.draw(easyPizza.sprite);
		// Отрисовка окна
		window.display();
	}

	return 0;
}