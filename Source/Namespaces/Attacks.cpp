//
// Created by Tomas on 25.4.2021.
//
#include "../Headers/Enums.h"
#include "BitManipulation.cpp"

namespace Attacks {
    U64 generatePawnAttacks(int color, int square) {
        // init empty boards
        U64 attacks = 0ULL;
        U64 bitboard = 0ULL;

        // bitboard where one line is filled with ones
        U64 aFile = BitManipulation::generateBoardWithOneFile(A);
        U64 hFile = BitManipulation::generateBoardWithOneFile(H);

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

    U64 generateKnightAttacks( int square) {
        // init empty boards
        U64 attacks = 0ULL;
        U64 bitboard = 0ULL;

        // bitboard where one or more lines are filled with ones
        U64 aFile = BitManipulation::generateBoardWithOneFile(A);
        U64 hFile = BitManipulation::generateBoardWithOneFile(H);
        U64 abFile = BitManipulation::generateBoardWithOneFile(A) | BitManipulation::generateBoardWithOneFile(B);
        U64 hgFile = BitManipulation::generateBoardWithOneFile(H) | BitManipulation::generateBoardWithOneFile(G);

        // set piece on the board
        setBit(bitboard, square);

        // generate knight attacks
        if ((bitboard >> 17) & ~hFile)
            attacks |= (bitboard >> 17);
        if ((bitboard >> 15) & ~aFile)
            attacks |= (bitboard >> 15);
        if ((bitboard >> 10) & ~hgFile)
            attacks |= (bitboard >> 10);
        if ((bitboard >> 6) & ~abFile)
            attacks |= (bitboard >> 6);
        if ((bitboard << 17) & ~aFile)
            attacks |= (bitboard << 17);
        if ((bitboard << 15) & ~hFile)
            attacks |= (bitboard << 15);
        if ((bitboard << 10) & ~abFile)
            attacks |= (bitboard << 10);
        if ((bitboard << 6) & ~hgFile)
            attacks |= (bitboard << 6);

        return attacks;
    }

    U64 generateKingAttacks(int square) {
        // init empty boards
        U64 attacks = 0ULL;
        U64 bitboard = 0ULL;

        // bitboard where one or more lines are filled with ones
        U64 aFile = BitManipulation::generateBoardWithOneFile(A);
        U64 hFile = BitManipulation::generateBoardWithOneFile(H);

        // set piece on the board
        setBit(bitboard, square);

        // generate king attacks
        if (bitboard >> 8)
            attacks |= (bitboard >> 8);
        if ((bitboard >> 9) & ~hFile)
            attacks |= (bitboard >> 9);
        if ((bitboard >> 7) & ~aFile)
            attacks |= (bitboard >> 7);
        if ((bitboard >> 1) & ~hFile)
            attacks |= (bitboard >> 1);
        if (bitboard << 8)
            attacks |= (bitboard << 8);
        if ((bitboard << 9) & ~aFile)
            attacks |= (bitboard << 9);
        if ((bitboard << 7) & ~hFile)
            attacks |= (bitboard << 7);
        if ((bitboard << 1) & ~aFile)
            attacks |= (bitboard << 1);

        return attacks;
    }

    U64 generateBishopAttacks(int square) {
        // init empty boards
        U64 attacks = 0ULL;

        // get rank and file
        int rank = square / 8;
        int file = square % 8;

        // generate bishop attacks with out bits from the corners (2 -> 7 and b -> g)
        for (int i = rank + 1, y = file + 1; i < 7 && y < 7; i++, y++)
            attacks |= (1ULL << (i * 8 + y));
        for (int i = rank - 1, y = file + 1; i > 0 && y < 7; i--, y++)
            attacks |= (1ULL << (i * 8 + y));
        for (int i = rank + 1, y = file - 1; i < 7 && y > 0; i++, y--)
            attacks |= (1ULL << (i * 8 + y));
        for (int i = rank - 1, y = file - 1; i > 0 && y > 0; i--, y--)
            attacks |= (1ULL << (i * 8 + y));

        return attacks;
    }

// generate bishop attacks with a blocker board
    U64 bishopAttacksWithBlocker(int square, U64 block)
    {
        // result attacks bitboard
        U64 attacks = 0ULL;

        // init target rank & files
        int rank = square / 8;
        int file = square % 8;

        // generate bishop attacks
        for (int r = rank + 1, f = file + 1; r <= 7 && f <= 7; r++, f++)
        {
            attacks |= (1ULL << (r * 8 + f));
            if ((1ULL << (r * 8 + f)) & block) break;
        }
        for (int r = rank - 1, f = file + 1; r >= 0 && f <= 7; r--, f++)
        {
            attacks |= (1ULL << (r * 8 + f));
            if ((1ULL << (r * 8 + f)) & block) break;
        }
        for (int r = rank + 1, f = file - 1; r <= 7 && f >= 0; r++, f--)
        {
            attacks |= (1ULL << (r * 8 + f));
            if ((1ULL << (r * 8 + f)) & block) break;
        }
        for (int r = rank - 1, f = file - 1; r >= 0 && f >= 0; r--, f--)
        {
            attacks |= (1ULL << (r * 8 + f));
            if ((1ULL << (r * 8 + f)) & block) break;
        }

        // return attack map
        return attacks;
    }

// generate rook attacks with a blocker board
    U64 rookAttacksWithBlocker(int square, U64 block)
    {
        // result attacks bitboard
        U64 attacks = 0ULL;

        // init target rank & files
        int rank = square / 8;
        int file = square % 8;

        // generate rook attacks
        for (int r = rank + 1; r <= 7; r++)
        {
            attacks |= (1ULL << (r * 8 + file));
            if ((1ULL << (r * 8 + file)) & block) break;
        }
        for (int r = rank - 1; r >= 0; r--)
        {
            attacks |= (1ULL << (r * 8 + file));
            if ((1ULL << (r * 8 + file)) & block) break;
        }
        for (int f = file + 1; f <= 7; f++)
        {
            attacks |= (1ULL << (rank * 8 + f));
            if ((1ULL << (rank * 8 + f)) & block) break;
        }
        for (int f = file - 1; f >= 0; f--)
        {
            attacks |= (1ULL << (rank * 8 + f));
            if ((1ULL << (rank * 8 + f)) & block) break;
        }

        // return attack map
        return attacks;
    }

    U64 generateRookAttacks(int square) {
        // init empty boards
        U64 attacks = 0ULL;

        // get rank and file
        int rank = square / 8;
        int file = square % 8;

        // generate rook attacks with out bits from the corners (2 -> 7 and b -> g)
        for (int i = rank + 1; i < 7; i++)
            attacks |= (1ULL << (i * 8 + file));
        for (int i = rank - 1; i > 0; i--)
            attacks |= (1ULL << (i * 8 + file));
        for (int i = file + 1; i < 7; i++)
            attacks |= (1ULL << (rank * 8 + i));
        for (int i = file - 1; i > 0; i--)
            attacks |= (1ULL << (rank * 8 + i));

        return attacks;
    }
}