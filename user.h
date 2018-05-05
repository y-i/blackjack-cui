#pragma once
#include <iostream>
#include <vector>
#include "./card.h"

class User {
public:
    User(Deck &d) {
        for (int i = 0; i < 2; ++i) hands.push_back(d.draw());
    }
    std::vector<Card> hands;
    int calcPoint() const {
        int sum = 0;
        int counta = 0;
        for (auto &c: hands) {
            int point = c.getPoint();
            if (point == 1) ++counta;
            sum += point;
        }
        while (counta-- && sum <= 21 - 10) sum += 10;
        return sum;
    }
    bool isBurst() const {
        return calcPoint() > 21;
    }
    bool isBJ() const {
        return calcPoint() == 21;
    }
    virtual bool draw(Deck &d) = 0;
};

class Player: public User {
public:
    Player(Deck &d): User(d) {}
    bool draw(Deck &d) {
        char in;
        std::cout << "Draw a card ? (y/n) -> ";
        std::cin >> in;
        if (in == 'y') {
            hands.push_back(d.draw());
            return true;
        } else {
            return false;
        }
    }
};

class Dealer: public User {
public:
    Dealer(Deck &d): User(d) {}
    bool draw(Deck &d) {
        while (calcPoint() < 17) hands.push_back(d.draw());
        return true;
    }
};