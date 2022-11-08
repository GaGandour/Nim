#include <iostream>

using namespace std;

void clearScreen()
{
#if defined _WIN32
    system("cls");
    //clrscr(); // including header file : conio.h
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    //system("clear");
    cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
#elif defined (__APPLE__)
    system("clear");
#endif
}

class NimMenu {
    public:
        NimMenu () {}

        void mainMenu () {
            cout << "==================================" << endl << endl;
            cout << "               NIM" << endl << endl;
            cout << "Menu:" << endl;
            cout << "\t1. Jogar!" << endl;
            cout << "\t2. O que eh Nim?" << endl;
            cout << "\t3. Lingua/Language" << endl;
            cout << "\t4. Creditos" << endl << endl;
            cout << "==================================" << endl << endl;
            cout << "Digite a opcao desejada: ";
            char c;
            cin >> c;
            clearScreen();
            switch (c)
            {
            case '1':
                // play
                break;
            case '2':
                // instructions
                break;
            case '3':
                // language
                break;
            case '4':
                // credits
                break;
            default:
                break;
            }
        } // pay attention to memory stack!!! We don't want a stack overflow... 

};