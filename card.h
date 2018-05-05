#pragma once
#include <iostream>
#include <array>
#include <string>
#include <random>
#include <algorithm>
#include <time.h>

class Card {
    int suit, number;
public:
    Card() {}
    Card(const int &suit, const int &number): suit(suit), number(number) {}
    friend std::ostream& operator << (std::ostream& os, const Card& c);
    int getPoint() const {
        return number > 10 ? 10 : number;
    }
};

class Deck {
    std::array<Card, 52> cards;
    int index = 0;
public:
    Deck() {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 13; ++j) {
                cards[i*13+j] = Card(i,j+1);
            }
        }

        std::mt19937 engine((unsigned) time(NULL));
        std::shuffle(std::begin(cards), std::end(cards), engine);
    }
    Card draw() {
        return cards[index++];
    }
    int getCardNum() const {
        return 52 - index;
    }
};

std::ostream& operator << (std::ostream& os, const Card& c)
{
    std::string rank = std::to_string(c.number);
    if (rank == "1") rank = "A";
    else if (rank == "11") rank = "J";
    else if (rank == "12") rank = "Q";
    else if (rank == "13") rank = "K";

    os << "SHCD"[c.suit] << rank;
    return os;
};