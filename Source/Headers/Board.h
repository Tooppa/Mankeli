//
// Created by Tomas on 16.3.2021.
//
#pragma once
#include <iostream>
#include "Enums.h"

class Board {
public:
    U64 generatePawnAttacks(int color, int square); // Generates a pawn attack from color and a square
    U64 generateKnightAttacks(int square);          // Generates knight attacks
    U64 generateKingAttacks(int square);            // Generates king attacks
    U64 generateBoardWithOneFile(int file);         // Generates an empty board with one of its files filled (with ones)
    void initAttacks();                             // Fills appropriate attack tables
    void printBitBoard(U64);                        // Prints a bitboard from a U64(unsigned long long) value

private:
    U64 _bitBoards[12];                             // Stores bitboards for every peace for both colors
    U64 _pawnAttacks[2][64];                        // Stores all possible pawn attacks except french word
    U64 _knightAttacks[64];                         // Stores all possible knight attacks
    U64 _kingAttacks[64];                           // Stores all possible king attacks
};
