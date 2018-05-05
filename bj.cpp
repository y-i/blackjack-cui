#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <random>
#include <ctime>
#include "./card.h"
#include "./user.h"
using namespace std;

int calcSumOfHand(const vector<int> &hand) {
    int sum = 0;
    int counta = 0;
    for (auto &card: hand) {
        if (card % 13 == 0) ++counta;
        sum += min(10, card % 13 + 1);
    }
    for (int i = 0; i < counta && sum <= 11; ++i) sum += 10;
    return sum;
}

int main() {
    Deck deck;
    Player p(deck);
    Dealer d(deck);

    cout << "Game Start!" << endl;
    for (;;) {
        cout << "Player:";
        for (auto &c: p.hands) {
            cout << " " << c;
        }
        cout << endl;
        cout << "Dealer:";
        cout << " " << d.hands[0];
        cout << " " << "??";
        cout << endl;
        if (!p.draw(deck)) break;
        if (p.isBurst() || p.isBJ()) break;
    }
    d.draw(deck);
    cout << "---" << endl;
    cout << "Player:";
    for (auto &c: p.hands) {
        cout << " " << c;
    }
    cout << endl;
    cout << "Dealer:";
    for (auto &c: d.hands) {
        cout << " " << c;
    }
    cout << endl;
    int playerScore = p.calcPoint();
    int dealerScore = d.calcPoint();
    cout << "Player :" << playerScore << endl;
    cout << "Dealer :" << dealerScore << endl;
    if (p.isBurst()) cout << "Dealer Win." << endl;
    else if (d.isBurst()) cout << "Player Win." << endl;
    else if (p.isBJ()) cout << "Player Win. (BlackJack)" << endl;
    else if (playerScore == dealerScore) cout << "Draw." << endl;
    else if (playerScore > dealerScore) cout << "Plaeyer Win." << endl;
    else if (playerScore < dealerScore) cout << "Dealer Win." << endl;
    else cout << "???" << endl;

    return 0;
}