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
 #include "chess.h"

void init_chess_board(ChessBoard chess_board)
{
    for (int file = 0; file < 8; file++)
    {
        for (int rank = 0; rank < 8; rank++)
        {
            chess_board[file][rank].is_occupied = false;
        }
    }
}

ChessSquare* get_square(ChessBoard chess_board, File file, Rank rank)
{
    if (file - 'a' < 8 && rank <= 8 && file - 'a' >= 0 && rank > 0)
    {
        return &chess_board[file - 'a'][rank];
    }
    return 0;
}

bool is_piece(struct ChessPiece pc, enum PieceColor color, enum PieceType type)
{
    return pc.color == color && pc.type == type;
}

bool is_square_occupied(ChessBoard chess_board, File file, Rank rank)
{
    return chess_board[file - 'a'][rank].is_occupied;
}

bool add_piece(ChessBoard chess_board, File file, Rank rank, struct ChessPiece piece)
{
    if (file - 'a' < 8 && rank <= 8 && file - 'a' >= 0 && rank > 0)
    {
        if (!chess_board[file - 'a'][rank].is_occupied)
        {
            chess_board[file - 'a'][rank].is_occupied = true;
            chess_board[file - 'a'][rank].piece = piece;
            return true;
        }
    }
    return false;
}

struct ChessPiece get_piece(ChessBoard chess_board, File file, Rank rank)
{
    ChessSquare* square = get_square(chess_board, file, rank);
    if (square != 0)
    {
        return square->piece;
    }

    struct ChessPiece error_piece;
    error_piece.type = NoPiece;
    return error_piece;
}

void setup_chess_board(ChessBoard chess_board)
{

}

bool 	remove_piece(ChessBoard chess_board, File file, Rank rank)
{
    return false;
}

bool 	squares_share_file(File s1_f, Rank s1_r, File s2_f, Rank s2_r)
{
    return false;
}

bool 	squares_share_rank(File s1_f, Rank s1_r, File s2_f, Rank s2_r)
{
    return false;
}

bool 	squares_share_diagonal(File s1_f, Rank s1_r, File s2_f, Rank s2_r)
{
    return false;
}

bool 	squares_share_knights_move(File s1_f, Rank s1_r, File s2_f, Rank s2_r)
{
    return false;
}

bool 	squares_share_pawns_move(enum PieceColor color, enum MoveType move, File s1_f, Rank s1_r, File s2_f, Rank s2_r)
{
    return false;
}

bool 	squares_share_queens_move(File s1_f, Rank s1_r, File s2_f, Rank s2_r)
{
    return false;
}

bool 	squares_share_kings_move(File s1_f, Rank s1_r, File s2_f, Rank s2_r)
{
    return false;
}
