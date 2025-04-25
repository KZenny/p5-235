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

    return groupedBoards;
}





