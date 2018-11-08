/*----------------------------------------------------------
 *				HTBLA-Leonding / Klasse: 2AHDV
 * ---------------------------------------------------------
 * Exercise Number: 0
 * Title:			chess.c
 * Author:			P. Bauer
 * Due Date:		November 03, 2010
 * ----------------------------------------------------------
 * Description:
 * Implementation of basic chess functions.
 * ----------------------------------------------------------
*/
#include <stdlib.h>
#include "general.h"
#include "chess.h"

void init_chess_board(ChessBoard chess_board)
{
    for (size_t y = 0; y < 8; y++)
    {
        for (size_t x = 0; x < 8; x++)
        {
            chess_board[y][x].is_occupied = false;
        }
    }
}

void setup_chess_board(ChessBoard chess_board)
{
    init_chess_board(chess_board);

    for (char c = 'a'; c <= 'h'; c++)
    {
        add_piece(chess_board, c, 2, {White, Pawn});
        add_piece(chess_board, c, 7, {Black, Pawn});
    }

    //White
    add_piece(chess_board, 'a', 1, {White, Rook});
    add_piece(chess_board, 'h', 1, {White, Rook});
    add_piece(chess_board, 'b', 1, {White, Knight});
    add_piece(chess_board, 'g', 1, {White, Knight});
    add_piece(chess_board, 'c', 1, {White, Bishop});
    add_piece(chess_board, 'f', 1, {White, Bishop});
    add_piece(chess_board, 'd', 1, {White, Queen});
    add_piece(chess_board, 'e', 1, {White, King});

    //Black
    add_piece(chess_board, 'a', 8, {Black, Rook});
    add_piece(chess_board, 'h', 8, {Black, Rook});
    add_piece(chess_board, 'b', 8, {Black, Knight});
    add_piece(chess_board, 'g', 8, {Black, Knight});
    add_piece(chess_board, 'c', 8, {Black, Bishop});
    add_piece(chess_board, 'f', 8, {Black, Bishop});
    add_piece(chess_board, 'd', 8, {Black, Queen});
    add_piece(chess_board, 'e', 8, {Black, King});
}

bool is_piece(struct ChessPiece pc, enum PieceColor color, enum PieceType type)
{
    return pc.color == color && pc.type == type;
}

bool is_square_occupied(ChessBoard chess_board, File file, Rank rank)
{
    return chess_board[rank - 1][file - 'a'].is_occupied;
}

bool add_piece(ChessBoard chess_board, File file, Rank rank, struct ChessPiece piece)
{
    if (!is_square_occupied(chess_board, file, rank) && isSquareInBounds(file, rank - 1))
    {
        chess_board[rank - 1][file - 'a'].is_occupied = true;
        chess_board[rank - 1][file - 'a'].piece = piece;
        return true;
    }

    return false;
}

bool remove_piece(ChessBoard chess_board, File file, Rank rank)
{
    if (isSquareInBounds(file, rank - 1) && is_square_occupied(chess_board, file, rank))
    {
        add_piece(chess_board, file, rank, {});
        chess_board[rank - 1][file - 'a'].is_occupied = false;
        return true;
    }

    return false;
}

struct ChessSquare* get_square(ChessBoard chess_board, File file, Rank rank)
{
    if(file > 'h' || (file < 'a' && rank > 8) || rank < 1)
    {
        return 0;
    }

    return &chess_board[rank - 1][file - 'a'];
}

struct ChessPiece get_piece(ChessBoard chess_board, File file, Rank rank)
{
    if (isSquareInBounds(file, rank - 1) && is_square_occupied(chess_board, file, rank))
    {
        return chess_board[rank - 1][file - 'a'].piece;
    }

    struct ChessPiece piece;
    piece.type = NoPiece;
    return piece;
}

bool squares_share_file(File s1_f, Rank s1_r, File s2_f, Rank s2_r)
{
    return s1_f == s2_f && isSquareInBounds(s1_f, s1_r - 1) && isSquareInBounds(s2_f, s2_r - 1);
}

bool squares_share_rank(File s1_f, Rank s1_r, File s2_f, Rank s2_r)
{
    return s1_r == s2_r && isSquareInBounds(s1_f, s1_r - 1) && isSquareInBounds(s2_f, s2_r - 1);
}

bool squares_share_diagonal(File s1_f, Rank s1_r, File s2_f, Rank s2_r)
{
    if (isSquareInBounds(s1_f, s1_r - 1) && isSquareInBounds(s2_f, s2_r - 1))
    {
        for (int i = 1; i < 9; i++)
        {
            bool is_lower_than_one = i < 1;
            if (!is_lower_than_one && (s1_r - i == s2_r || s1_r + i == s2_r) && (s1_f - i - 'a' == s2_f - 'a' || s1_f - 'a' + i == s2_f - 'a')) return true;
        }
    }
    return false;
}

bool squares_share_knights_move(File s1_f, Rank s1_r, File s2_f, Rank s2_r)
{
  return    ((s1_r - 2 == s2_r || s1_r + 2 == s2_r) && (s1_f - 1 - 'a' == s2_f - 'a' || s1_f + 1 - 'a' == s2_f - 'a'))
         || ((s1_r - 1 == s2_r || s1_r + 1 == s2_r) && (s1_f - 2 - 'a' == s2_f - 'a' || s1_f + 2 - 'a' == s2_f - 'a'));
}

bool squares_share_pawns_move(enum PieceColor color, enum MoveType move, File s1_f, Rank s1_r, File s2_f, Rank s2_r)
{
    if (move == NormalMove)
    {
        return s1_r + 1 == s2_r || s1_r - 1 == s2_r;
    }
    else  if (move == CaptureMove)
    {
        return (s1_r + 1 == s2_r && s1_f + 1 == s2_f) || (s1_r - 1 == s2_r && s1_f - 1 == s2_f);
    }

    return false;
}

bool squares_share_kings_move(File s1_f, Rank s1_r, File s2_f, Rank s2_r)
{
  return (s1_f + 1 == s2_f && s1_r == s2_r) || (s1_f - 1 == s2_f && s1_r == s2_r) ||
         (s1_f == s2_f + 1 && s1_r == s2_r) || (s1_f == s2_f && s1_r == s2_r - 1);
}

bool squares_share_queens_move(File s1_f, Rank s1_r, File s2_f, Rank s2_r)
{
    return squares_share_diagonal(s1_f, s1_r, s2_f, s2_r) || s1_f == s2_f || s1_r == s2_r;
}



bool isSquareInBounds(File file, Rank rank)
{
    return file - 'a' < 8 && file - 'a' >= 0 && rank < 8 && rank >= 0;
}
