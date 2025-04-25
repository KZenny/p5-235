#include "Transform.hpp"

/**
 * @brief Rotates a square matrix 90 degrees clockwise.
 * @pre The input 2D vector must be square 
 *      (ie. the number of cells per row equals the number of columns)
 * 
 * @param matrix A const reference to a 2D vector of objects of type T
 * @return A new 2D vector representing the rotated matrix
 */
template <typename T>
std::vector<std::vector<T>> Transform::rotate(const std::vector<std::vector<T>>& matrix) {
    // your code here.
    int n = matrix.size();
    // Create a new matrix for the result
    std::vector<std::vector<T>> rotated(n, std::vector<T>(n));

    // Rotate the matrix 90 degrees clockwise
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            rotated[j][n - 1 - i] = matrix[i][j];
        }
    }

    return rotated;
}

/**
 * @brief Swaps the elements of a square matrix across its vertical axis of symmetry
 * @pre The input 2D vector must be square 
 *      (ie. the number of cells per row equals the number of columns)
 * 
 * @param matrix A const reference to a 2D vector of objects of type T
 * @return A new 2D vector representing the transformed matrix
 */
template <typename T>
std::vector<std::vector<T>> Transform::flipAcrossVertical(const std::vector<std::vector<T>>& matrix) {
    // your code here
    int n = matrix.size();
    // Create a new matrix for the result
    std::vector<std::vector<T>> flipped(n, std::vector<T>(n));

    // Flip across the vertical axis (left-right)
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            flipped[i][n - 1 - j] = matrix[i][j];
        }
    }

    return flipped;
}

/**
 * @brief Swaps the elements of a square matrix across its horizontal axis of symmetry
 * @pre The input 2D vector must be square 
 *      (ie. the number of cells per row equals the number of columns)
 * 
 * @param matrix A const reference to a 2D vector of objects of type T
 * @return A new 2D vector representing the transformed matrix
 */
template <typename T>
std::vector<std::vector<T>> Transform::flipAcrossHorizontal(const std::vector<std::vector<T>>& matrix) {
    // your code here
    int n = matrix.size();
    // Create a new matrix for the result
    std::vector<std::vector<T>> flipped(n, std::vector<T>(n));

    // Flip across the horizontal axis (top-bottom)
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            flipped[n - 1 - i][j] = matrix[i][j];
        }
    }

    return flipped;
}

// Alias for readability
typedef std::vector<std::vector<char>> CharacterBoard;

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
std::vector<std::vector<CharacterBoard>> Transform::groupSimilarBoards(const std::vector<CharacterBoard>& boards) {
    std::vector<std::vector<CharacterBoard>> groupedBoards;
    std::vector<bool> visited(boards.size(), false);  

    for (size_t i = 0; i < boards.size(); ++i) {
        if (visited[i]) continue;

        std::vector<CharacterBoard> currentGroup;
        currentGroup.push_back(boards[i]);
        visited[i] = true;

        // Compare to every other unvisited board
        for (size_t j = i + 1; j < boards.size(); ++j) {
            if (visited[j]) continue;

            bool isSimilar = false;
            std::vector<CharacterBoard> transformations = Transform::getAllTransformations(boards[j]);

            for (const auto& variant : transformations) {
                if (Transform::areBoardsEqual(boards[i], variant)) {
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

// Helper function to generate all transformations of a given board
static std::vector<CharacterBoard> Transform::getAllTransformations(const CharacterBoard& board) {
    std::vector<CharacterBoard> transformations;

    // Generate all rotations
    CharacterBoard rotated = board;
    for (int i = 0; i < 4; ++i) {
        transformations.push_back(rotated);
        rotated = Transform::rotate(rotated);
    }

    // Generate flips for each rotation
    std::vector<CharacterBoard> currentTransformations = transformations;
    for (const auto& rotatedBoard : currentTransformations) {
        transformations.push_back(Transform::flipAcrossVertical(rotatedBoard));
        transformations.push_back(Transform::flipAcrossHorizontal(rotatedBoard));
    }

    // return all unique transformations in a vector
    return transformations;
}

// Helper function to compare two boards for equality
static bool Transform::areBoardsEqual(const CharacterBoard& board1, const CharacterBoard& board2) {
    return board1 == board2;
}


