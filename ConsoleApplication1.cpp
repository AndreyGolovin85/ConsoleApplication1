#include <SFML/Graphics.hpp>
#include <windows.h>
#include <list>
#include <ctime>
#include <iostream>
#include <cstdlib>
#include <sstream>
using namespace sf;
using namespace std;

class GameObject
{
public:
	
	float  x, y, speed_Pan, speed_Pizza, moveTimer;//добавили переменную таймер для будущих целей
	float w, h;
	int score;
	Texture texture;
	Sprite sprite;
	String name;

	GameObject (Image& image, float X, float Y, float W, float H, String Name)
	{
		x = X; y = Y; w = W; h = H; moveTimer = 0; name = Name;
		speed_Pan = 30;
		speed_Pizza = 30;
		score = 0;
		name = "P";
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin(w/2, h/2);
	}
	
	FloatRect getRect() {
		return FloatRect(x, y, w, h);
	}
	virtual void update(float time) = 0;
};

class Pizza :public GameObject {
public:
	int numb[11] = { 0, 75, 150, 225, 300, 375, 450, 525, 600, 675, 750 };
	int A = 0; int B = 11; int num;
	bool delete_pizza = false;
	
	Pizza(Image& image, float X, float Y, float W, float H, String Name) :GameObject(image, X, Y, W, H, Name)
	{
		if (name == "Pizza") {
			sprite.getTextureRect();
		}
		random_number();
	}
	void random_number()
	{
		int num = A + rand() % ((B + 1) - A);
		x = numb[num];
	}

	void update(float time)
	{
		if (y < 600)
		{
			y += (speed_Pizza * time)*30;
		}
		if (y >= 600)
		{
			delete_pizza = true;
		}
		sprite.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта в место его центра
	}
};

class Pan :public GameObject {
public:
	bool rightPressed;
	bool leftPressed;

	Pan(Image& image, float X, float Y, float W, float H, String Name) :GameObject(image, X, Y, W, H, Name)
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
			x += (speed_Pan * time) * 40;
		}
		if (sprite.getPosition().x < 26)
		{
			sprite.setPosition(0, sprite.getPosition().x);
		}
		else if (leftPressed)
		{
			x -= (speed_Pan * time) * 40;
		}
		sprite.setPosition(x+w/2, y+h/2); //задаем позицию спрайта
	}
};

class Chef :public Pizza {
public:
	Chef(Image& image, float X, float Y, float W, float H, String Name) :Pizza(image, X, Y, W, H, Name)
	{
		if (name == "Chef") {
			sprite.getTextureRect();
		}
	}

	void update(float time)
	{
		sprite.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта в место его центра
	}
};

void draw()
{
	int count;
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
	Chef chef(ChefImage, 0, 10, 50, 50, "Chef");//пицца, объект класса пицца

	Image PanImage;
	PanImage.loadFromFile("image/pan1.bmp");
	PanImage.createMaskFromColor(PanImage.getPixel(0, 0));
	Pan pan(PanImage, 400, 551, 50, 50, "Pan");//пицца, объект класса пицца

	// Загружаем нашу картинку для пиццы.
	Image PizzaImage;
	PizzaImage.loadFromFile("image/pizza.bmp");//загрузка изображения пиццы
	PizzaImage.createMaskFromColor(PizzaImage.getPixel(0, 0));
	Pizza pizza(PizzaImage, 0, 70, 50, 50, "Pizza");//пицца, объект класса пицца

	Font font;//шрифт 
	font.loadFromFile("fonts/CyrilicOld.ttf");//передаем нашему шрифту файл шрифта
	Text textScore("", font, 25);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	Text textPizza("", font, 25);
	textScore.setFillColor(Color::Cyan);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
	textPizza.setFillColor(Color::Cyan);
	textScore.setStyle(Text::Bold);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
	textPizza.setStyle(Text::Bold);
	textScore.setPosition(680, 0);//задаем позицию текста, центр камеры
	textPizza.setPosition(10, 0);

	list<Pizza*>  list_pizza;//создаю список, сюда буду кидать объекты.
	list<Pizza*>::iterator it_pizza;//итератор чтобы проходить по эл-там списка
	// Добавляем через цикл i-тое количество пицц.
	for (count = 0; count < 5; count++)
	{
		list_pizza.push_back(new Pizza(PizzaImage, 0, 70, 50, 50, "Pizza"));//и закидываем в список
	}

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
		time = time / 4;
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
		for (it_pizza = list_pizza.begin(); it_pizza != list_pizza.end(); it_pizza++)		
		{
			(*it_pizza)->update(time);	//для всех элементов списка активируем ф-цию update
			if ((*it_pizza)->delete_pizza == true)
			{
				chef.random_number();
				delete* it_pizza;	// если этот объект выходит за край экрана, то удаляем его
				it_pizza = list_pizza.erase(it_pizza);
				count--;
			}
			for (it_pizza = list_pizza.begin(); it_pizza != list_pizza.end(); it_pizza++)//проходимся по эл-там списка
			{
				if ((*it_pizza)->getRect().intersects(pan.getRect()))//если прямоугольник спрайта объекта пересекается с сковородой
				{
					chef.random_number();
					delete* it_pizza;	// то удаляем его
					it_pizza = list_pizza.erase(it_pizza);
					pizza.score++;
					count--;
					cout << pizza.score << endl;
				}
				if (it_pizza == list_pizza.end())
				{
					break;
				}
			}
			if (it_pizza == list_pizza.end())
			{
				break;
			}
			
		}
		chef.update(time);
		pan.update(time);

		ostringstream ScoreString, PizzaString;    // объявили переменную
		ScoreString << pizza.score*10;		//занесли в нее число очков
		PizzaString << count;
		textScore.setString("Получено\n очков: " + ScoreString.str());//задает строку тексту
		textPizza.setString("Пиццы\n осталось: " + PizzaString.str());
		window.draw(textScore);//рисую этот текст
		window.draw(textPizza);

		// Отрисовка спрайта пиццы и сковороды.
		for (it_pizza = list_pizza.begin(); it_pizza != list_pizza.end(); it_pizza++)
		{
			window.draw((*it_pizza)->sprite); //рисуем list_pizza объекты
		}
		window.draw(pan.sprite);
		// Отрисовка окна
		window.display();
	}
}

int main()
{
	srand(time(NULL));
	//HWND hConsole = GetConsoleWindow();//Если компилятор старый заменить на GetForegroundWindow()
	//ShowWindow(hConsole, SW_HIDE);//прячем окно консоли
	
	draw();
	
	return 0;
}