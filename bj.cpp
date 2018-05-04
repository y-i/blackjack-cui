#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <random>
#include <ctime>
using namespace std;

int calcSumOfHand(const vector<int> &hand) {
    int sum = 0;
    for (auto &card: hand) {
        sum += min(10, card % 13 + 1);
    }
    return sum;
}

int main() {
    array<char, 4> suits = {'S', 'H', 'C', 'D'};
    array<string, 13> nums = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    array<int, 52> deck;
    iota(begin(deck), end(deck), 0);

    //random_device seed_gen;
    //mt19937 engine(seed_gen());
    mt19937 engine((unsigned) time(NULL));

    cout << "Game Start!" << endl;
    shuffle(begin(deck), end(deck), engine);
    int index = 0;
    vector<int> my, cpu;
    for (int i = 0; i < 2; ++i) my.push_back(deck[index++]);
    for (int i = 0; i < 2; ++i) cpu.push_back(deck[index++]);
    for (;;) {
        cout << "Player:";
        for (auto &n: my) {
            cout << " " << suits[n/13] << nums[n%13];
        }
        cout << endl;
        cout << "Dealer:";
        cout << " " << suits[cpu[0]/13] << nums[cpu[0]%13];
        cout << " " << "??";
        cout << endl;
        cout << "Draw a card (y/n)? -> ";
        string s;
        cin >> s;
        if (s == "y") my.push_back(deck[index++]);
        else break;
        if (calcSumOfHand(my) >= 21) break;
    }
    while (calcSumOfHand(cpu) < 17) cpu.push_back(deck[index++]);
    cout << "---" << endl;
    cout << "Player:";
    for (auto &n: my) {
        cout << " " << suits[n/13] << nums[n%13];
    }
    cout << endl;
    cout << "Dealer:";
    for (auto &n: cpu) {
        cout << " " << suits[n/13] << nums[n%13];
    }
    cout << endl;
    int playerScore = calcSumOfHand(my), dealerScore = calcSumOfHand(cpu);
    cout << "Player :" << playerScore << endl;
    cout << "Dealer :" << dealerScore << endl;
    if (playerScore > 21) cout << "Dealer Win." << endl;
    else if (dealerScore > 21) cout << "Player Win." << endl;
    else if (playerScore == dealerScore) cout << "Draw." << endl;
    else if (playerScore > dealerScore) cout << "Plaeyer Win." << endl;
    else if (playerScore < dealerScore) cout << "Dealer Win." << endl;
    else cout << "???" << endl;

    return 0;
}