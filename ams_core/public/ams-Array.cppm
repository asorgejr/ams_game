/*
 * Copyright 2022 - Anthony Sorge
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions 
 * of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING 
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON INFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER 
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE.
 */

export module ams:Array;
#ifndef AMS_MODULES_STD
import <array>;
import <stdexcept>;
import <string>;
import <vector>;
#else
import std;
#endif
import :config;


export namespace ams {

/**
 * @brief A simple array class with optional bounds checking.
 * @tparam T The type of the array.
 * @tparam N The size of the array.
 * @details This class is a simple wrapper around std::array with optional bounds checking.
 * When bounds checking is enabled, the class will throw std::out_of_range exceptions when
 * accessing elements outside of the array bounds. Bounds checking is enabled when 
 * AMS_EXCEPTIONS is defined.
 */
template <typename T, size_t N>
class Array : public std::array<T, N> {
private:
  inline static const std::string kOutOfBoundsMsg = "Index out of bounds.";
  inline static const std::string kEmptyMsg = "Array is empty.";
public:
  constexpr T &operator[](size_t index) {
    if constexpr (AMSExceptions)
      if (index < 0 || index >= N)
        throw std::out_of_range(kOutOfBoundsMsg);
    return std::array<T, N>::operator[](index);
  }
  constexpr const T &operator[](size_t index) const {
    if constexpr (AMSExceptions)
      if (index < 0 || index >= N)
        throw std::out_of_range(kOutOfBoundsMsg);
    return std::array<T, N>::operator[](index);
  }

  constexpr T &at(size_t index) {
    if constexpr (AMSExceptions)
      if (index < 0 || index >= N)
        throw std::out_of_range(kOutOfBoundsMsg);
    return std::array<T, N>::at(index);
  }

  constexpr const T &at(size_t index) const {
    if constexpr (AMSExceptions)
      if (index < 0 || index >= N)
        throw std::out_of_range(kOutOfBoundsMsg);
    return std::array<T, N>::at(index);
  }

  constexpr T &front() {
    if constexpr (AMSExceptions)
      if (N == 0)
        throw std::out_of_range(kEmptyMsg);
    return std::array<T, N>::front();
  }

  constexpr const T &front() const {
    if constexpr (AMSExceptions)
      if (N == 0)
        throw std::out_of_range(kEmptyMsg);
    return std::array<T, N>::front();
  }

  constexpr T &back() {
    if constexpr (AMSExceptions)
      if (N == 0)
        throw std::out_of_range(kEmptyMsg);
    return std::array<T, N>::back();
  }

  constexpr const T &back() const {
    if constexpr (AMSExceptions)
      if (N == 0)
        throw std::out_of_range(kEmptyMsg);
    return std::array<T, N>::back();
  }

  /**
   * @brief Reverse the order of the elements in this array.
   * @details This function reverses the order of the elements in this array.
   */
  constexpr void reverse() {
    for (size_t i = 0; i < N / 2; i++) {
      T temp = std::array<T, N>::operator[](i);
      std::array<T, N>::operator[](i) = std::array<T, N>::operator[](N - i - 1);
      std::array<T, N>::operator[](N - i - 1) = temp;
    }
  }

  /**
   * @brief Reverse the order of the elements in a copy of this array.
   * @details This function reverses the order of the elements in a copy of this array.
   * @return A copy of this array with the elements reversed.
   */
  constexpr Array<T, N> reversed() const {
    Array<T, N> result;
    for (size_t i = 0; i < N; i++) {
      result[i] = std::array<T, N>::operator[](N - i - 1);
    }
    return result;
  }

  /**
   * @brief Slice this array.
   * @details This function slices this array and returns a new array containing the elements between
   * the start and end indices. If the end index is greater than the size of the array, an exception
   * will be thrown.
   * @param start The index of the first element to include in the slice.
   * @param end The index of the last element to include in the slice.
   * @return A new array containing the elements between the start and end indices.
   */
  constexpr std::vector<T> slice(size_t start, size_t end=N-1) const {
    if constexpr (AMSExceptions)
      if (start < 0 || start >= N || end < 0 || end >= N)
        throw std::out_of_range(kOutOfBoundsMsg);
    std::vector<T> result(end - start);
    for (size_t i = start; i < end; i++) {
      result[i - start] = std::array<T, N>::operator[](i);
    }
    return result;
  }

  /**
   * @brief Slice this array.
   * @details This function slices this array and returns a new array containing the elements between
   * the start and end indices. If the end index is greater than the size of the array, an exception
   * will be thrown.
   * @param start The index of the first element to include in the slice.
   * @param end The index of the last element to include in the slice.
   * @return A new array containing the elements between the start and end indices.
   */
  constexpr std::vector<T> slice(size_t start, size_t end=N-1) {
    if constexpr (AMSExceptions)
      if (start < 0 || start >= N || end < 0 || end >= N)
        throw std::out_of_range(kOutOfBoundsMsg);
    std::vector<T> result(end - start);
    for (size_t i = start; i < end; i++) {
      result[i - start] = std::array<T, N>::operator[](i);
    }
    return result;
  }

}; // class Array

} // ams
