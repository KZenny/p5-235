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



