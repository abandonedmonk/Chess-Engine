// System Headers
#include <stdio.h>

// define bitboard datatypes
#define U64 unsigned long long

// board square
enum
{
    a8,
    b8,
    c8,
    d8,
    e8,
    f8,
    g8,
    h8,
    a7,
    b7,
    c7,
    d7,
    e7,
    f7,
    g7,
    h7,
    a6,
    b6,
    c6,
    d6,
    e6,
    f6,
    g6,
    h6,
    a5,
    b5,
    c5,
    d5,
    e5,
    f5,
    g5,
    h5,
    a4,
    b4,
    c4,
    d4,
    e4,
    f4,
    g4,
    h4,
    a3,
    b3,
    c3,
    d3,
    e3,
    f3,
    g3,
    h3,
    a2,
    b2,
    c2,
    d2,
    e2,
    f2,
    g2,
    h2,
    a1,
    b1,
    c1,
    d1,
    e1,
    f1,
    g1,
    h1
};

// sides to move (colours)
enum
{
    white,
    black
};

/*
"a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8"
"a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7"
"a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6"
"a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5"
"a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4"
"a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3"
"a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2"
"a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1"
*/

/***************************************\
=========================================
            Bit Manipulation
=========================================
\***************************************/

// set/get/pop macros
#define get_bit(bb, sq) (bb & (1ULL << sq))                        // To show the presence of a piece
#define set_bit(bb, sq) (bb |= (1ULL << sq))                       // To set the presence of a piece
#define pop_bit(bb, sq) (get_bit(bb, sq) ? bb ^= (1ULL << sq) : 0) // To remove the presence of a piece

/***************************************\
=========================================
            Input/Output
=========================================
\***************************************/

// print bitboard
void print_bitboard(U64 bitboard)
{
    printf("\n");
    // loop over board ranks
    for (int rank = 0; rank < 8; rank++)
    {
        // loop over board files
        for (int file = 0; file < 8; file++)
        {
            // convert file and rank into square index
            int square = rank * 8 + file;

            // print ranks
            if (!file)
            {
                printf("  %d   ", 8 - rank);
            }

            // To show the presence of a piece, we print 1 else 0
            printf("%d ", get_bit(bitboard, square) ? 1 : 0);
        }

        // print new line every rank
        printf("\n");
    }

    // print the files
    printf("\n      a b c d e f g h \n");

    // print bitboard as unsigned decimal number
    printf("      Bitboard: %llud \n \n", bitboard);
}

/***************************************\
=========================================
                Attacks
=========================================
\***************************************/

// pawn attacks table [side][square]
U64 pawn_attacks[2][64];

// generate pawn attacks
U64 mask_pawn_attacks();

/***************************************\
=========================================
            Main Function
=========================================
\***************************************/

int main()
{
    U64 bitboard = 0ULL;

    set_bit(bitboard, e4);
    set_bit(bitboard, a4);
    set_bit(bitboard, e5);
    print_bitboard(bitboard);

    pop_bit(bitboard, e4);
    print_bitboard(bitboard);

    return 0;
}