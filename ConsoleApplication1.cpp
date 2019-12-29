#include <SFML/Graphics.hpp>
#include <windows.h>
#include "Engine.h"
using namespace sf;

int main()
{
    HWND hConsole = GetConsoleWindow();//Если компилятор старый заменить на GetForegroundWindow()
    ShowWindow(hConsole, SW_HIDE);//прячем окно консоли

    // Объявляем экземпляр класса Engine
    Engine engine;

    // Вызываем функцию start
    engine.start();

    return 0;
}
