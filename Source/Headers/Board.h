//
// Created by Tomas on 16.3.2021.
//
#pragma once
#include <iostream>

#define u64 unsigned long long
// bit manipulation
#define setBit(bitboard, square) (bitboard |= (1ULL << square))
#define getBit(bitboard, square) ((bitboard >> square) & 1ULL)
#define popBit(bitboard, square) (getBit(bitboard, square) ? bitboard ^= (1ULL << square) : 0)
enum {
    a8, b8, c8, d8, e8, f8, g8, h8,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a5, b5, c5, d5, e5, f5, g5, h5,                 // square coordinates
    a4, b4, c4, d4, e4, f4, g4, h4,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a1, b1, c1, d1, e1, f1, g1, h1
};
enum { white, black };                              // colors. White is 0 and black is 1

class Board {
public:
    u64 generatePawnAttacks(int color, int square); // Generates a pawn attack from color and a square
    u64 getPawnAttack(int color, int square);       // Gets a bitboard with attacks from color and a square
    void initPawnAttacks();                         // Fills _pawnAttacks table with every possible attack for every pawn (both colors)
    void printBitBoard(u64);                        // Prints a bitboard from a u64(unsigned long long) value

private:
    u64 _bitBoards[12];
    u64 _pawnAttacks[2][64];
};
