#include <iostream>
#include <bits/stdc++.h>
#include "custom_random.h"
#include "nim_messages.h"

using namespace std;

typedef vector<int> vi;
#define PC true
#define USER false


class Nim {
    public:
        Nim() {
            nimMessenger = NimMessenger();
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

        void game() {
            while (validLin) {
                if (player == PC) {
                    nimMessenger.pressEnterToGetPCMove();
                    cin.ignore();
                    cin.ignore();
                    makeMove(getMagicNumber());
                    nimMessenger.describePCMove(lastEliminatedNumber, lastChangedLin);
                }
                else {
                    expectMove();
                    nimMessenger.describePlayersMove();
                }
                changeTurns();
                printGame();
            }
            if (player == PC)
                nimMessenger.youWin();
            else
                nimMessenger.youLose();
        }

    private:
        vi nimV;
        bool player;
        int validLin;
        int lastChangedLin;
        int lastEliminatedNumber;
        NimMessenger nimMessenger;

        void expectFirstPlayer() {
            nimMessenger.chooseFirstPlayer();
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
                    nimMessenger.singleOptionError();
                    cin >> c;
                }
            }
        }

        void generateFirstPlayer() {
            int magicNumber = getMagicNumber();
            if (magicNumber == 0) {
                player = USER;
                nimMessenger.pcChoosesUserAsFirstPlayer();
            }
            else {
                player = PC;
                nimMessenger.pcChoosesPCAsFirstPlayer();
            }
        }

        void getTablePlayer() {
            nimMessenger.chooseTableWriter();
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
                    nimMessenger.singleOptionError();
                    cin >> c;
                }
            }
        }

        void receiveTable() {
            nimV.clear();
            int n = 1;
            nimMessenger.expectTable();
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
            nimMessenger.expectPlayersMove();
            cin >> r >> v;
            bool played = false;
            while (!played) {
                if (r > nimV.size() || r < 1) {
                    nimMessenger.multipleOptionError();
                    cin >> r >> v;
                }
                else if (v < 0 || v > nimV[r-1]) {
                    nimMessenger.multipleOptionError();
                    cin >> r >> v;
                }
                else {
                    played = true;
                }
            }
            nimV[r-1] -= v;
            if (nimV[r-1] == 0) validLin--;
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