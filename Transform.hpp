/**
 * @namespace Transform
 * @brief Defines the interface for rotations & reflections of a square 2D Vector
 */

#pragma once 
#include <vector>
#include <algorithm>
namespace Transform {
    /**
     * @brief Rotates a square matrix 90 degrees clockwise.
     * @pre The input 2D vector must be square 
     *      (ie. the number of cells per row equals the number of columns)
     * 
     * @param matrix A const reference to a 2D vector of objects of type T
     * @return A new 2D vector representing the rotated matrix
     */
    template <typename T>
    std::vector<std::vector<T>> rotate(const std::vector<std::vector<T>>& matrix);
    
    /**
     * @brief Swaps the elements of a square matrix across its vertical axis of symmetry
     * @pre The input 2D vector must be square 
     *      (ie. the number of cells per row equals the number of columns)
     * 
     * @param matrix A const reference to a 2D vector of objects of type T
     * @return A new 2D vector representing the transformed matrix
     */
    template <typename T>
    std::vector<std::vector<T>> flipAcrossVertical(const std::vector<std::vector<T>>& matrix);
    
    /**
     * @brief Swaps the elements of a square matrix across its horizontal axis of symmetry
     * @pre The input 2D vector must be square 
     *      (ie. the number of cells per row equals the number of columns)
     * 
     * @param matrix A const reference to a 2D vector of objects of type T
     * @return A new 2D vector representing the transformed matrix
     */
    template <typename T>
    std::vector<std::vector<T>> flipAcrossHorizontal(const std::vector<std::vector<T>>& matrix);

    // Alias for readability
    typedef std::vector<std::vector<char>> CharacterBoard;

    // Helper function to generate all transformations of a given board
    std::vector<CharacterBoard> getAllTransformations(const CharacterBoard& board);

    // Helper function to compare two boards for equality
    bool areBoardsEqual(const CharacterBoard& board1, const CharacterBoard& board2);

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
     std::vector<std::vector<CharacterBoard>> groupSimilarBoards(const std::vector<CharacterBoard>& boards);
};

#include "Transform.cpp"