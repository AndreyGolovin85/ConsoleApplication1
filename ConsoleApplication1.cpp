#include <SFML/Graphics.hpp>
#include <windows.h>
#include <list>
using namespace sf;

class GameObject
{
public:
	float  x, y, speed_Pan, speed_Pizza, moveTimer;//добавили переменную таймер для будущих целей
	int w, h;
	Texture texture;
	Sprite sprite;
	String name;

	GameObject (Image& image, float X, float Y, int W, int H, String Name)
	{
		x = X; y = Y; w = W; h = H; moveTimer = 0; name = Name;
		speed_Pan = 20;
		speed_Pizza = 15;
		name = "P";
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin(w/2, h/2);
	}	
};

class Pizza :public GameObject {
public:
	double superSpeed = 40;
	bool spacePressed;

	Pizza(Image& image, float X, float Y, int W, int H, String Name) :GameObject(image, X, Y, W, H, Name)
	{
		
		if (name == "Pizza") {
			sprite.getTextureRect();
		}
	}

	void StartSuperSpeed()
	{
		spacePressed = true;
	}
	void StopSuperSpeed()
	{
		spacePressed = false;
	}

	void update(float time)
	{
		if (y < 600)
		{
			y += (speed_Pizza * time) * 20;
		}
		if (spacePressed)
		{
			y += (superSpeed * time) * 20;
		}
		sprite.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта в место его центра
	}
};

class Pan :public GameObject {
public:
	bool rightPressed;
	bool leftPressed;

	Pan(Image& image, float X, float Y, int W, int H, String Name) :GameObject(image, X, Y, W, H, Name)
	{
		if (name == "Pan") {
			sprite.getTextureRect();
		}
	}
	// Функции движения спрайта с флагом true/false.
	void moveRight()
	{
		rightPressed = true;
	}
	void stopRight()
	{
		rightPressed = false;
	}
	void moveLeft()
	{
		leftPressed = true;
	}
	void stopLeft()
	{
		leftPressed = false;
	}
	// Функция обновления позиции спрайта.
	void update(float time)
	{
		if (sprite.getPosition().x > 750)                                   // Проверяем
		{																			 // Достигла ли сковорда
			sprite.setPosition(800, sprite.getPosition().x);			// Правого края экрана, если да то сковорда останавливается.
		}
		else if (rightPressed)
		{
			x += (speed_Pan * time) * 25;
		}
		if (sprite.getPosition().x < 26)
		{
			sprite.setPosition(0, sprite.getPosition().x);
		}
		else if (leftPressed)
		{
			x -= (speed_Pan * time) * 25;
		}
		sprite.setPosition(x+w/2, y+h/2); //задаем позицию спрайта
	}
};

class Chef :public GameObject {
public:

	Chef(Image& image, float X, float Y, int W, int H, String Name) :GameObject(image, X, Y, W, H, Name)
	{
		if (name == "Chef") {
			sprite.getTextureRect();
		}
	}

	void update(float time)
	{
		if (sprite.getPosition().y > 35)
		{
			y -= (speed_Pan * time) * 10;
			if (sprite.getPosition().y == 35)
			{
				y += (speed_Pan * time) * 10;
			}
		}
		
		sprite.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта в место его центра
	}
};

void draw()
{
	// Объект, который, собственно, является главным окном приложения
	RenderWindow window(VideoMode(800, 600), "Panic in the Pizzeria");
	Image imageBG_1, imageBG_2;
	Texture textureBG_1, textureBG_2;
	Sprite spriteBG_1, spriteBG_2;
	imageBG_1.loadFromFile("image/wall01.jpg");
	imageBG_2.loadFromFile("image/wall0.jpg");
	textureBG_1.loadFromImage(imageBG_1);//передаем в него объект Image (изображения)
	textureBG_2.loadFromImage(imageBG_2);
	spriteBG_1.setTexture(textureBG_1);//передаём в него объект Texture (текстуры)
	spriteBG_2.setTexture(textureBG_2);
	spriteBG_1.setPosition(0, 0);//задаем начальные координаты появления спрайта
	spriteBG_2.setPosition(0, 126);

	Image ChefImage;
	ChefImage.loadFromFile("image/chef.bmp");
	ChefImage.createMaskFromColor(ChefImage.getPixel(0, 0));
	Chef chef(ChefImage, 370, 110, 50, 50, "Chef");//пицца, объект класса пицца

	Image PanImage;
	PanImage.loadFromFile("image/pan1.bmp");
	PanImage.createMaskFromColor(PanImage.getPixel(0, 0));
	Pan pan(PanImage, 400, 551, 50, 50, "Pan");//пицца, объект класса пицца

	// Загружаем нашу картинку для пиццы.
	Image PizzaImage;
	PizzaImage.loadFromFile("image/pizza.bmp");//загрузка изображения пиццы
	PizzaImage.createMaskFromColor(PizzaImage.getPixel(0, 0));
	Pizza pizza(PizzaImage, 400, 70, 50, 50, "Pizza");//пицца, объект класса пицца

	// Переменная времени
	Clock clock;
	// Инициализация Event.
	Event event;
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
		//Event event;
		while (window.pollEvent(event))
		{

			// Пользователь нажал на «крестик» и хочет закрыть окно?
			if (event.type == Event::Closed)
			{
				// тогда закрываем его
				window.close();
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window.close();
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
			if (Keyboard::isKeyPressed(Keyboard::Space))
			{
				pizza.StartSuperSpeed();
			}
			else
			{
				pizza.StopSuperSpeed();
			}
		}
			// Установка цвета фона - белый
			window.clear(Color::White);
			// Отрисовка верхней части фона.
			window.draw(spriteBG_1);
			// Отрисовка Повара.
			window.draw(chef.sprite);
			// Отрисовка нижней части фона, кирпичной стены.
			window.draw(spriteBG_2);
			// Вызов функций обновления спрайтов.
			chef.update(time);
			pizza.update(time);
			pan.update(time);

			// Отрисовка спрайта пиццы и сковороды.
			window.draw(pizza.sprite);
			window.draw(pan.sprite);
			// Отрисовка окна
			window.display();
	}
}

int main()
{
	HWND hConsole = GetConsoleWindow();//Если компилятор старый заменить на GetForegroundWindow()
	ShowWindow(hConsole, SW_HIDE);//прячем окно консоли
	
	draw();
	
	return 0;
}