#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
void clearScreen(int length)
{
    for (int i = 1; i <= length; i++)
        cout << '\b';
}
void changeColor(int colorCode)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, colorCode);
}
void showLoadingScreen()
{
    const int colors[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    string str = "- - -";
    changeColor(15);
    for (int i = 0; i < 16; i++)
    {
        cout << str;
        Sleep(1000);
        clearScreen(5);
        changeColor(i);
    }
}
int main()
{
    cout << endl
         << endl;
    showLoadingScreen();
}