#include "ChessBoard.hpp"
#include "Transform.hpp"
/**
Name: Kenny Zhou
Date: 4/25/25
Purpose: The cpp file for ChessBoard. Implements queenHelper, findAllQueenReplacements, and groupSimilarBoards  */


/**
    * Default constructor. 
    * @post The board is setup with the following restrictions:
    * 1) board is initialized to a 8x8 2D vector of ChessPiece pointers
    *      - ChessPiece derived classes are dynamically allocated and constructed as follows:
    *          - Pieces on the BOTTOM half of the board are set to have color "BLACK"
    *          - Pieces on the UPPER half of the board are set to have color "WHITE"
    *          - Their row & col members reflect their position on the board
    *          - All pawns on the BOTTOM half are flagged to be moving up.
    *          - All pawns on the BOTTOM half are flagged to be NOT moving up.
    *          - All other parameters are default initialized (this includes moving_up for non-Pawns!)
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
ChessBoard::ChessBoard() 
    : playerOneTurn{true}, p1_color{"BLACK"}, p2_color{"WHITE"}, board{std::vector(8, std::vector<ChessPiece*>(8)) } {
        // Allocate pieces

        auto add_mirrored = [this] (const int& i, const std::string& type) {
            if (type == "PAWN") {
                board[1][i] = new Pawn(p1_color, 1, i, true);
                board[6][i] = new Pawn(p2_color, 6, i);
            } else if (type == "ROOK") {
                board[0][i] = new Rook(p1_color, 0, i);
                board[7][i] = new Rook(p2_color, 7, i);
            } else if (type == "KNIGHT") {
                board[0][i] = new Knight(p1_color, 0, i);
                board[7][i] = new Knight(p2_color, 7, i);            
            } else if (type == "BISHOP") {
                board[0][i] = new Bishop(p1_color, 0, i);
                board[7][i] = new Bishop(p2_color, 7, i);
            } else if (type == "KING") {
                board[0][i] = new King(p1_color, 0, i);
                board[7][i] = new King(p2_color, 7, i);
            } else if (type == "QUEEN") {
                board[0][i] = new Queen(p1_color, 0, i);
                board[7][i] = new Queen(p2_color, 7, i);
            }
        };

        std::vector<std::string> inner_pieces = {"ROOK", "KNIGHT", "BISHOP", "KING", "QUEEN", "BISHOP", "KNIGHT", "ROOK"};
        for (size_t i = 0; i < BOARD_LENGTH; i++) {
            add_mirrored(i, "PAWN");
            add_mirrored(i, inner_pieces[i]);
        }
    }

/**
 * @brief Constructs a ChessBoard object with a given board configuration and player turn.
 * 
 * @param instance A 2D vector representing a board state, where each element is a pointer to a ChessPiece.
 * @param p1Turn A boolean indicating whether it's player one's turn. True for player one, false for player two.
 * 
 * @post Initializes the board layout, sets player one's color to "BLACK" and player two's color to "WHITE".
 */
ChessBoard::ChessBoard(const std::vector<std::vector<ChessPiece*>>& instance, const bool& p1Turn)
 : playerOneTurn{p1Turn}, p1_color{"BLACK"}, p2_color{"WHITE"}, board{instance}{}

/**
 * @brief Gets the ChessPiece (if any) at (row, col) on the board
 * 
 * @param row The row of the cell
 * @param col The column of the cell
 * @return ChessPiece* A pointer to the ChessPiece* at the cell specified by (row, col) on the board
 */
ChessPiece* ChessBoard::getCell(const int& row, const int& col) const {
    return board[row][col];
}

/**
 * @brief Destructor. 
 * @post Deallocates all ChessPiece pointers stored on the board at time of deletion. 
 */
ChessBoard::~ChessBoard() {
    for (int i = 0; i < BOARD_LENGTH; i++) {
        for (int j = 0; j < BOARD_LENGTH; j++) {
            if (!board[i][j]) { continue; }
            delete board[i][j];
            board[i][j] = nullptr;
        }
    }
}

// MY CODE BELOW

// Alias for readability
typedef std::vector<std::vector<char>> CharacterBoard;

/**
* @brief A STATIC helper function for recursively solving the 8-queens problem.
* 
* This function places queens column by column, checks for valid placements,
* and stores all valid board configurations in the provided list.
* 
* @param col A const reference to aninteger representing the current column being processed.
* @param board A (non-const) reference to a 2D vector of ChessPiece*, representing the current board configuration
* @param placedQueens A (non-const) reference to a vector storing Queen*, which represents the queens we've placed so far
* @param allBoards A (non-const) reference to a vector of CharacterBoard objects storing all the solutions we've found thus far
*/
void ChessBoard::queenHelper(const int& col, std::vector<std::vector<ChessPiece*>>& board, std::vector<Queen*>& placedQueens, std::vector<CharacterBoard>& allBoards) {
    // Base case: all 8 queens are placed 
    if (col == 8) {
        // Convert board into a CharacterBoard
        CharacterBoard convertBoard(8, std::vector<char>(8, '*'));
        for (int r = 0; r < 8; r++) {
            for (int c = 0; c < 8; c++) {
                if (board[r][c] != nullptr && board[r][c]->getType() == "QUEEN") {
                    convertBoard[r][c] = 'Q';
                }
            }
        }
        allBoards.push_back(convertBoard);
        return;
    }

    // Try placing a Queen in each row of the current column 
    for (int row = 0; row < 8; row++) {
        bool safe = true;
        // Check if any of the placed queens can move to (row, col)
        for (size_t i = 0; i < placedQueens.size(); ++i) {
            Queen* queen = placedQueens[i]; 
            if (queen->canMove(row, col, board)) {
                safe = false;
                break;
            }
        }

        // If safe, place a queen and recurse
        if (safe) {
            Queen* newQueen = new Queen("WHITE", row, col, false);
            board[row][col] = newQueen;
            placedQueens.push_back(newQueen);
            queenHelper(col + 1, board, placedQueens, allBoards);
            placedQueens.pop_back();
            //Deallocate the queen and remove it from the board
            delete board[row][col];
            board[row][col] = nullptr;
        }
    }
}

/** 
* @brief Finds all possible solutions to the 8-queens problem.
* 
* @return A vector of CharacterBoard objects, 
*         each representing a unique solution 
*         to the 8-queens problem.
*/
std::vector<CharacterBoard> ChessBoard::findAllQueenPlacements() {
    // Initialize board, placedQueens, and allBoards
    std::vector<std::vector<ChessPiece*>> board(8, std::vector<ChessPiece*>(8, nullptr));
    std::vector<Queen*> placedQueens;
    std::vector<CharacterBoard> allBoards;

    // Start the recursive helper function
    queenHelper(0, board, placedQueens, allBoards);

    // Return all queen placements
    return allBoards;
}

// Helper function to generate all transformations of a given board
std::vector<CharacterBoard> ChessBoard::getAllTransformations(const CharacterBoard& board) {
    std::vector<CharacterBoard> transformations;

    // Generate all rotations
    CharacterBoard rotated = board;
    for (int i = 0; i < 4; i++) {
        transformations.push_back(rotated);
        rotated = Transform::rotate(rotated);
    }

    // Generate flips for each rotation
    std::vector<CharacterBoard> currentTransformations = transformations;
    for (size_t i = 0; i < currentTransformations.size(); i++) {
        const CharacterBoard& rotatedBoard = currentTransformations[i];
        transformations.push_back(Transform::flipAcrossVertical(rotatedBoard));
        transformations.push_back(Transform::flipAcrossHorizontal(rotatedBoard));
    }

    // return all unique transformations in a vector
    return transformations;
}

// Helper function to compare two boards for equality
bool ChessBoard::areBoardsEqual(const CharacterBoard& board1, const CharacterBoard& board2) {
    return board1 == board2;
}

/**
 * @brief Groups similar chessboard configurations by transformations.
 * 
 * This function organizes a list of chessboard configurations into groups of similar boards, 
 * where similarity is defined as being identical under a 
 *      1) Rotation (clockwise: 0°, 90°, 180°, 270°)
 *      2) Followed by a flip across the horizontal or vertical axis
 * 
 * @param boards A const ref. to a vector of `CharacterBoard` objects, each representing a chessboard configuration.
 * 
 * @return A 2D vector of `CharacterBoard` objects, 
 *         where each inner vector is a list of boards 
 *         that are transformations of each other.
 */
 std::vector<std::vector<CharacterBoard>> ChessBoard::groupSimilarBoards(const std::vector<CharacterBoard>& boards) {
    std::vector<std::vector<CharacterBoard>> groupedBoards;
    std::vector<bool> visited(boards.size(), false);  

    for (size_t i = 0; i < boards.size(); i++) {
        if (visited[i]) {
            continue; // Skip if already visited
        } 

        std::vector<CharacterBoard> currentGroup;
        currentGroup.push_back(boards[i]);
        visited[i] = true;

        // Compare to every other unvisited board
        for (size_t j = i + 1; j < boards.size(); j++) {
            if (visited[j]) continue;

            bool isSimilar = false;
            std::vector<CharacterBoard> transformations = getAllTransformations(boards[j]);

            for (size_t k = 0; k < transformations.size(); k++) {
                const CharacterBoard& variant = transformations[k];
                if (areBoardsEqual(boards[i], variant)) {
                    isSimilar = true;
                    break;
                }
            }

            if (isSimilar) {
                currentGroup.push_back(boards[j]);
                visited[j] = true;
            }
        }

        groupedBoards.push_back(currentGroup);
    }

    return groupedBoards;
}




