#include <iostream>
#include <bits/stdc++.h>
#include "nim.h"

using namespace std;

typedef vector<int> vi;
#define PC true
#define USER false

class Nim {
    public:
        Nim() {
            getTablePlayer();
            if (player == PC) {
                generateTable();
                printGame();
                expectFirstPlayer();
            }
            else {
                receiveTable();
                printGame();
                generateFirstPlayer();
            }
            validLin = nimV.size();
            game();
        }

        void expectFirstPlayer() {
            cout << "Digite 1 se voce quer ser o primeiro a jogar.\nDigite 2 se voce quer ser o segundo a jogar.\n";
            char c;
            cin >> c;
            bool chosen = false;
            while (!chosen) {
                if (c == '1') {
                    player = USER;
                    chosen = true;
                }
                if (c == '2') {
                    player = PC;
                    chosen = true;
                }
                if (!chosen) {
                    cout << "Por favor, digite uma opcao valida.\n";
                    cin >> c;
                }
            }
        }

        void generateFirstPlayer() {
            int magicNumber = getMagicNumber();
            if (magicNumber == 0) {
                player = USER;
                cout << "O computador escolheu voce para ser o primeiro jogador!\n\n";
            }
            else {
                player = PC;
                cout << "O computador quer ser o primeiro jogador!\n\n";
            }
        }

        void getTablePlayer() {
            cout << "Digite 1 se voce quer escolher o tabuleiro.\nDigite 2 se voce quer escolher o primeiro jogador.\n";
            char c;
            cin >> c;
            bool chosen = false;
            while (!chosen) {
                if (c == '1') {
                    player = USER;
                    chosen = true;
                }
                if (c == '2') {
                    player = PC;
                    chosen = true;
                }
                if (!chosen) {
                    cout << "Por favor, digite uma opcao valida.\n";
                    cin >> c;
                }
            }
        }

        void receiveTable() {
            nimV.clear();
            int n = 1;
            explainNim();
            while (n) {
                cin >> n;
                if (n)
                    nimV.push_back(n);
            }
        }


        void generateTable() {
            int L = randFromInclusiveRange(3, 9);
            nimV.clear();
            nimV = vi(L);
            for (int i = 0; i < L; i++) {
                nimV[i] = randFromInclusiveRange(1,7);
            }
        }

        void printGame() {
            int L = nimV.size();
            for (int i = 0; i < L; i++) {
                cout << i+1 << ": ";
                for (int j = 0; j < nimV[i]; j++) {
                    cout << '|';
                }
                cout << '\n';
            }
            cout << '\n';
        }

        int getMagicNumber() {
            int L = nimV.size();
            if (L == 1) {
                return nimV[0];
            }
            int res = nimV[0];
            for (int i = 1; i < L; i++) {
                res = res ^ nimV[i];
            }
            return res;
        }

        void makeMove(int magicNum) {
            if (magicNum == 0) {
                int r = randFromInclusiveRange(0, nimV.size() - 1);
                while (nimV[r] == 0) {
                    r = randFromInclusiveRange(0, nimV.size() - 1);
                }
                int v = randFromInclusiveRange(1, nimV[r]);
                nimV[r] -= v;
                lastChangedLin = r + 1;
                lastEliminatedNumber = v;
                if (nimV[r] == 0) validLin--;
                return;
            }
            int i = 0;
            bool found = false;
            while (!found) {
                if (nimV[i] & getMostSignificantBit(magicNum)) {
                    found = true;
                }
                else
                    i++;
            }

            lastChangedLin = i+1;
            int old = nimV[i];
            nimV[i] ^= magicNum;
            lastEliminatedNumber = old - nimV[i]; 
            if (nimV[i] == 0) validLin--;
        }

        void expectMove() {
            int r, v;
            cout << "Escreva o número da linha seguido do número de pauzinhos que voce quer riscar.\n";
            cin >> r >> v;
            bool played = false;
            while (!played) {
                if (r > nimV.size() || r < 1) {
                    cout << "Escreva valores validos.\n";
                    cin >> r >> v;
                }
                else if (v < 0 || v > nimV[r-1]) {
                    cout << "Escreva valores validos.\n";
                    cin >> r >> v;
                }
                else {
                    played = true;
                }
            }
            nimV[r-1] -= v;
            if (nimV[r-1] == 0) validLin--;
        }

        void game() {
            while (validLin) {
                if (player == PC) {
                    cout << "Aperte ENTER para ver a jogada do computador...\n";
                    cin.ignore();
                    cin.ignore();
                    makeMove(getMagicNumber());
                    cout << "Jogada do computador: (riscou " << lastEliminatedNumber << " da linha " << lastChangedLin << ")\n\n";
                }
                else {
                    expectMove();
                    cout << "\nSua jogada:\n\n";
                }
                changeTurns();
                printGame();
            }
            if (player == PC)
                cout << "Voce ganhou!!!\n\n";
            else
                cout << "Voce perdeu!!!\n\n";
        }

    private:
        vi nimV;
        bool player;
        int validLin;
        int lastChangedLin;
        int lastEliminatedNumber;

        void explainNim () {
            cout << "Escreva as linhas:" << endl;
        }

        int getMostSignificantBit(int n) {
            for (int i = 0; i < 32; i++) {
                if (n & (~(1 << i)))
                    n = n & (~(1 << i));
            }
            return n;
        }

        void changeTurns() {
            player = !player;
        }
};



int main () {
    srand((unsigned) time(NULL));
    Nim nim = Nim();
    return 0;
}