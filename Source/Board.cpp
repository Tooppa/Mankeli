//
// Created by Tomas on 16.3.2021.
//
#include "Headers/Board.h"

void Board::printBitBoard(U64 bitboard) {
    std::cout << "\n\n";
    // ranks
    for (int i = 0; i < 8; i++) {
        // files
        for (int y = 0; y < 8; y++) {
            int square = i * 8 + y;
            // print rank number if y is zero
            if (!y)
                std::cout<< 8 - i << "  ";
            // print bits state
            std::cout << " " << getBit(bitboard, square) ? 1 : 0;
        }
        std::cout << "\n";
    }
    // print files char
    std::cout << "\n    a b c d e f g h\n\n";
}

U64 Board::generateBoardWithOneFile(int file) {
    U64 bitboard = 0ULL;
    for (int i = 0; i < 8; ++i) {
        int square = i * 8 + file;
        setBit(bitboard, square);
    }
    return bitboard;
}

U64 Board::generatePawnAttacks(int color, int square) {
    // init empty boards
    U64 attacks = 0ULL;
    U64 bitboard = 0ULL;

    // bitboard where one line is filled with ones
    U64 aFile = generateBoardWithOneFile(A);
    U64 hFile = generateBoardWithOneFile(H);

    // set piece on the board
    setBit(bitboard, square);

    // white pawns
    if (!color)
    {
        if ((bitboard >> 7) & ~aFile)
            attacks |= (bitboard >> 7);
        if ((bitboard >> 9) & ~hFile)
            attacks |= (bitboard >> 9);
    }
    else
    {
        if ((bitboard << 7) & ~hFile)
            attacks |= (bitboard << 7);
        if ((bitboard << 9) & ~aFile)
            attacks |= (bitboard << 9);
    }
    return attacks;
}

U64 Board::generateKnightAttacks( int square) {
    // init empty boards
    U64 attacks = 0ULL;
    U64 bitboard = 0ULL;

    // bitboard where one or more lines are filled with ones
    U64 aFile = generateBoardWithOneFile(A);
    U64 hFile = generateBoardWithOneFile(H);
    U64 abFile = generateBoardWithOneFile(A) | generateBoardWithOneFile(B);
    U64 hgFile = generateBoardWithOneFile(H) | generateBoardWithOneFile(G);

    // set piece on the board
    setBit(bitboard, square);

    // generate knight attacks
    if ((bitboard >> 17) & ~hFile) attacks |= (bitboard >> 17);
    if ((bitboard >> 15) & ~aFile) attacks |= (bitboard >> 15);
    if ((bitboard >> 10) & ~hgFile) attacks |= (bitboard >> 10);
    if ((bitboard >> 6) & ~abFile) attacks |= (bitboard >> 6);
    if ((bitboard << 17) & ~aFile) attacks |= (bitboard << 17);
    if ((bitboard << 15) & ~hFile) attacks |= (bitboard << 15);
    if ((bitboard << 10) & ~abFile) attacks |= (bitboard << 10);
    if ((bitboard << 6) & ~hgFile) attacks |= (bitboard << 6);

    return attacks;
}

void Board::initAttacks()
{
    // loop over 64 board squares
    for (int square = 0; square < 64; square++)
    {
        // init pawn attacks
        _pawnAttacks[white][square] = generatePawnAttacks(white, square);
        _pawnAttacks[black][square] = generatePawnAttacks(black, square);

        // knight attacks
        _knightAttacks[square] = generateKnightAttacks(square);
    }
}

U64 Board::getPawnAttack(int color, int square) {
    return _pawnAttacks[color][square];
}