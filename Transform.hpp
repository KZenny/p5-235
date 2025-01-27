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
};

#include "Transform.cpp"