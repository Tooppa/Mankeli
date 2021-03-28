//
// Created by Tomas on 16.3.2021.
//
#include "Headers/Board.h"

int main()
{
    Board test;

    test.printBitBoard(test.generateRookAttacks(e3));
    return 0;
}
