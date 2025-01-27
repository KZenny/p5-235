/**
 * @class ChessBoard
 * @brief Represents an 8x8 board of Chess Pieces used to play chess
 */

#pragma once

#include <vector>
#include "pieces_module.hpp"

class ChessBoard {
    private:
        // Define board size (8x8)
        static const int BOARD_LENGTH = 8;
        
        bool playerOneTurn;
        
        std::string p1_color;
        std::string p2_color;

        std::vector<std::vector<ChessPiece*>> board;

    public:
        /**
         * Default constructor. 
         * @post The board is setup with the following restrictions:
         * 1) board is initialized to a 8x8 2D vector of ChessPiece pointers
         *      - ChessPiece derived classes are dynamically allocated and constructed as follows:
         *          - Pieces on the BOTTOM half of the board are set to be "moving up" | of color "BLACK"
         *          - Pieces on the UPPER half of the board are set to be NOT "moving up"| of color "WHITE"
         *          - Their row & col members reflect their position on the board
         *          - All other parameters are default initialized.
         *   
         *      - Pawns (P), Rooks(R), Bishops(B), Kings(K), Queens(Q), and Knights(N) are placed in the following format (ie. the standard setup for chess):
         *          
         *          7 | R N B K Q B N R
         *          6 | P P P P P P P P
         *          5 | * * * * * * * *
         *          4 | * * * * * * * *
         *          3 | * * * * * * * *
         *          2 | * * * * * * * *
         *          1 | P P P P P P P P
         *          0 | R N B K Q B N R
         *              +---------------
         *              0 1 2 3 4 5 6 7
         *      
         *          (With * denoting empty cells)
         * 
         * 2) playerOneTurn is set to true.
         * 3) p1_color is set to "BLACK", and p2_color is set to "WHITE"
         */
        ChessBoard();

        /**
         * @brief Constructs a ChessBoard object with a given board configuration and player turn.
         * 
         * @param instance A 2D vector representing a board state, where each element is a pointer to a ChessPiece.
         * @param p1Turn A boolean indicating whether it's player one's turn. True for player one, false for player two.
         * 
         * @post Initializes the board layout, sets player one's color to "BLACK" and player two's color to "WHITE".
         */
        ChessBoard(const std::vector<std::vector<ChessPiece*>>& board, const bool& p1Turn);

        /**
         * @brief Gets the ChessPiece (if any) at (row, col) on the board
         * 
         * @param row The row of the cell
         * @param col The column of the cell
         * @return ChessPiece* A pointer to the ChessPiece* at the cell specified by (row, col) on the board
         */
        ChessPiece* getCell(const int& row, const int& col) const;

        /**
         * @brief Destructor. 
         * @post Deallocates all ChessPiece pointers stored on the board at time of deletion. 
         */
        ~ChessBoard();
};