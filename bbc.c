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

// print the position of the piece as 'a1'
void print_piece_position(int square)
{
    printf("Piece Position: %c%d \n", 'a' + ((square) % 8), (square) / 8 + 1);
}

/***************************************\
=========================================
                Attacks
=========================================
\***************************************/

/*
    not A file
  8   0 1 1 1 1 1 1 1
  7   0 1 1 1 1 1 1 1
  6   0 1 1 1 1 1 1 1
  5   0 1 1 1 1 1 1 1
  4   0 1 1 1 1 1 1 1
  3   0 1 1 1 1 1 1 1
  2   0 1 1 1 1 1 1 1
  1   0 1 1 1 1 1 1 1

      a b c d e f g h

    not H file
  8   1 1 1 1 1 1 1 0
  7   1 1 1 1 1 1 1 0
  6   1 1 1 1 1 1 1 0
  5   1 1 1 1 1 1 1 0
  4   1 1 1 1 1 1 1 0
  3   1 1 1 1 1 1 1 0
  2   1 1 1 1 1 1 1 0
  1   1 1 1 1 1 1 1 0

      a b c d e f g h

    not HG file
  8   1 1 1 1 1 1 0 0
  7   1 1 1 1 1 1 0 0
  6   1 1 1 1 1 1 0 0
  5   1 1 1 1 1 1 0 0
  4   1 1 1 1 1 1 0 0
  3   1 1 1 1 1 1 0 0
  2   1 1 1 1 1 1 0 0
  1   1 1 1 1 1 1 0 0

      a b c d e f g h

    not AB file
  8   0 0 1 1 1 1 1 1
  7   0 0 1 1 1 1 1 1
  6   0 0 1 1 1 1 1 1
  5   0 0 1 1 1 1 1 1
  4   0 0 1 1 1 1 1 1
  3   0 0 1 1 1 1 1 1
  2   0 0 1 1 1 1 1 1
  1   0 0 1 1 1 1 1 1

      a b c d e f g h
*/

const U64 not_a_file = 18374403900871474942ULL;  // Not "A" file constant
const U64 not_h_file = 9187201950435737471ULL;   // Not "H" file constant
const U64 not_hg_file = 4557430888798830399ULL;  // Not "HG" file constant
const U64 not_ab_file = 18229723555195321596ULL; // Not "HG" file constant

// pawn attacks table [side][square]
U64 pawn_attacks[2][64];

// knight attacks table [square]
U64 knight_attacks[64];

// king's attacks table [square]
U64 king_attacks[64];

// generate pawn attacks
U64 mask_pawn_attacks(int side, int square)
{
    U64 attacks = 0ULL;  // results attack bitboard
    U64 bitboard = 0ULL; // piece bitboard

    set_bit(bitboard, square); // set piece on board

    // Not capturing illegally
    // Generate Pawn Attacks
    if (!side) // White Pawns
    {
        if ((bitboard >> 7) & not_a_file)
            attacks |= (bitboard >> 7);
        if ((bitboard >> 9) & not_h_file)
            attacks |= (bitboard >> 9);
    }
    else // Black pawns
    {
        if ((bitboard << 7) & not_h_file)
            attacks |= (bitboard << 7);
        if ((bitboard << 9) & not_a_file)
            attacks |= (bitboard << 9);
    }

    return attacks; // return attack map!!
}

// generate knight attacks
U64 mask_knight_attacks(int square)
{
    U64 attacks = 0ULL;  // results attack bitboard
    U64 bitboard = 0ULL; // piece bitboard

    set_bit(bitboard, square); // set piece on board

    // Generate Knight Attacks
    if ((bitboard >> 17) & not_h_file)
        attacks |= (bitboard >> 17);
    if ((bitboard >> 15) & not_a_file)
        attacks |= (bitboard >> 15);
    if ((bitboard >> 10) & not_hg_file)
        attacks |= (bitboard >> 10);
    if ((bitboard >> 6) & not_ab_file)
        attacks |= (bitboard >> 6);

    // For the other opposite direction
    if ((bitboard << 17) & not_a_file)
        attacks |= (bitboard << 17);
    if ((bitboard << 15) & not_h_file)
        attacks |= (bitboard << 15);
    if ((bitboard << 10) & not_ab_file)
        attacks |= (bitboard << 10);
    if ((bitboard << 6) & not_hg_file)
        attacks |= (bitboard << 6);

    return attacks; // return attack map!!
}

// generate king attacks
U64 mask_king_attacks(int square)
{
    U64 attacks = 0ULL;  // results attack bitboard
    U64 bitboard = 0ULL; // piece bitboard

    set_bit(bitboard, square); // set piece on board

    // Generate King Attacks
    if (bitboard >> 8)
        attacks |= (bitboard >> 8);
    if ((bitboard >> 9) & not_h_file)
        attacks |= (bitboard >> 9); // While on a file it shouldn't attack in h file
    if ((bitboard >> 7) & not_a_file)
        attacks |= (bitboard >> 7); // While on 'h' file it shouldn't attack in 'a' file
    if ((bitboard >> 1) & not_h_file)
        attacks |= (bitboard >> 1);

    if (bitboard << 8)
        attacks |= (bitboard << 8);
    if ((bitboard << 9) & not_a_file)
        attacks |= (bitboard << 9);
    if ((bitboard << 7) & not_h_file)
        attacks |= (bitboard << 7);
    if ((bitboard << 1) & not_a_file)
        attacks |= (bitboard << 1);

    return attacks; // return attack map!!
}

// mask bishop attacks
U64 mask_bishop_attacks(int square)
{
    U64 attacks = 0ULL; // result attacks bitboard
    int r, f;           // init ranks and files

    // init target rank and files
    int tr = square / 8;
    int tf = square % 8;

    // mask relevant bishop occupancy bits
    for (r = tr + 1, f = tf + 1; r <= 6 && f <= 6; r++, f++)
        attacks |= (1ULL << (r * 8 + f));

    for (r = tr - 1, f = tf + 1; r >= 1 && f <= 6; r--, f++)
        attacks |= (1ULL << (r * 8 + f));

    for (r = tr + 1, f = tf - 1; r <= 6 && f >= 1; r++, f--)
        attacks |= (1ULL << (r * 8 + f));

    for (r = tr - 1, f = tf - 1; r >= 1 && f >= 1; r--, f--)
        attacks |= (1ULL << (r * 8 + f));

    return attacks; // return attack map
}

U64 mask_rook_attacks(int square)
{
    U64 attacks = 0ULL; // result attacks bitboard
    int r, f;           // init ranks and files

    // init target rank and files
    int tr = square / 8;
    int tf = square % 8;

    // mask relevant rook occupancy bits
    for (r = tr + 1; r <= 6; r++)
        attacks |= (1ULL << (r * 8 + tf));
    for (r = tr - 1; r >= 1; r--)
        attacks |= (1ULL << (r * 8 + tf));
    for (f = tf + 1; f <= 6; f++)
        attacks |= (1ULL << (tr * 8 + f));
    for (f = tf - 1; f >= 1; f--)
        attacks |= (1ULL << (tr * 8 + f));

    return attacks; // return attack map
}

// init leaper attacks
void init_leaper_attacks()
{
    for (int square = 0; square < 64; square++)
    {
        // init pawn attacks
        pawn_attacks[white][square] = mask_pawn_attacks(white, square);
        pawn_attacks[black][square] = mask_pawn_attacks(black, square);
        // init knight attacks
        knight_attacks[square] = mask_knight_attacks(square);
        // init king attacks
        king_attacks[square] = mask_king_attacks(square);
    }
}
/***************************************\
=========================================
            Main Function
=========================================
\***************************************/

int main()
{
    init_leaper_attacks();
    for (int square = 0; square < 64; square++)
    {
        print_piece_position(square);
        print_bitboard(mask_rook_attacks(square));
    }
    // print_bitboard(mask_rook_attacks(d4));

    return 0;
}