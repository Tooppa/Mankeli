//
// Created by Tomas on 16.3.2021.
//
#pragma once
#include <iostream>
#include "Enums.h"

class Board {
public:
    U64 generatePawnAttacks(int color, int square); // Generates a pawn attack from color and a square
    U64 getPawnAttack(int color, int square);       // Gets a bitboard with attacks from color and a square
    U64 generateBoardWithOneFile(int file);         // Generates an empty board with one of its files filled (with ones)
    void initPawnAttacks();                         // Fills _pawnAttacks table with every possible attack for every pawn (both colors)
    void printBitBoard(U64);                        // Prints a bitboard from a U64(unsigned long long) value

private:
    U64 _bitBoards[12];                             // Stores bitboards for every peace for both colors
    U64 _pawnAttacks[2][64];                        // Stores all possible pawn attacks except french word
};
