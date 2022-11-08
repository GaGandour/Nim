#include <iostream>

using namespace std;

class NimMessenger {
    public:
        NimMessenger () {}

        void chooseFirstPlayer () {
            cout << "Digite 1 se voce quer ser o primeiro a jogar.\nDigite 2 se voce quer ser o segundo a jogar.\n"; 
        }

        void chooseTableWriter () {
            cout << "Digite 1 se voce quer escolher o tabuleiro.\nDigite 2 se voce quer escolher o primeiro jogador.\n";
        }

        void pcChoosesPCAsFirstPlayer () {
            cout << "O computador quer ser o primeiro jogador!\n\n";
        }

        void pcChoosesUserAsFirstPlayer () {
            cout << "O computador escolheu voce para ser o primeiro jogador!\n\n";
        }

        void expectTable () {
            cout << "Escreva as linhas:" << endl;
        }

        void youWin () {
            cout << "Voce ganhou!!!\n\n";
        }

        void youLose () {
            cout << "Voce perdeu!!!\n\n";
        }

        void expectPlayersMove () {
            cout << "Escreva o número da linha seguido do número de pauzinhos que voce quer riscar.\n";
        }

        void pressEnterToGetPCMove () {
            cout << "Aperte ENTER para ver a jogada do computador...\n";
        }

        void describePlayersMove () {
            cout << "\nSua jogada:\n\n";
        }

        void describePCMove (int lastEliminatedNumber, int lastChangedLin) {
            cout << "Jogada do computador: (riscou " << lastEliminatedNumber << " da linha " << lastChangedLin << ")\n\n";
        }

        void singleOptionError () {
            cout << "Por favor, digite uma opcao valida.\n";
        }

        void multipleOptionError () {
            cout << "Por favor, escreva valores validos.\n";
        }
};