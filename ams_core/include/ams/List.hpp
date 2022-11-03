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

/*[export module ams.List]*/
/*[exclude begin]*/
#pragma once
#include "config.hpp"
/*[exclude end]*/
#include <vector>
#include <stdexcept>
/*[import ams.config]*/

/*[export]*/ namespace ams {

using index_t = int32_t;

/**
 * @brief A simple sequential list.
 * @tparam T - The type of the list.
 * @tparam Allocator - The allocator to use.
 * @tparam NegativeIndexing - If true, negative indexing is allowed.
 * @details This class is a simple sequential list. It is a wrapper around std::vector.
 * Any methods that modify the size of the list are virtual, so that they can be overridden.
 * When NegativeIndexing is true, negative indexing (e.g. -1 == size() - 1) is allowed. Negative indexing defaults
 * to true if AMS_NEGATIVE_INDEXING is defined.
 */
template<typename T, typename Allocator = std::allocator<T>, bool NegativeIndexing = AMSNegativeIndexing>
class List {
protected:
  std::vector<T, Allocator> mData{};
  
public:
  // iterators
  using iterator = typename std::vector<T>::iterator;
  using const_iterator = typename std::vector<T>::const_iterator;

  // reverse iterators
  using reverse_iterator = typename std::vector<T>::reverse_iterator;
  using const_reverse_iterator = typename std::vector<T>::const_reverse_iterator;

  // constructors
  List() = default;

  explicit List(size_t size) : mData(size) {}

  List(size_t size, const T& value) : mData(size, value) {}

  List(std::initializer_list<T> list) : mData(list) {}
  
  /**
   * @brief Iterator range constructor.
   * @note This constructor is unsafe, as it does not check if the iterators are valid.
   * @tparam TIterator - The iterator type.
   * @param first - The first element.
   * @param last - The last element.
   */
  List(const_iterator first, const_iterator last) {
    if constexpr (AMSExceptions)
      if (first > last)
        throw std::invalid_argument("first > last");
    assign(first, last);
  }

  List(const List& other) = default;

  List& operator=(const List& other) = default;

  List(List&& other) noexcept = default;

  List& operator=(List&& other) noexcept = default;

  ~List() = default;

  // mimick std::vector methods
  
  /**
   * @brief Add an element to the end of the list.
   * @param value 
   */
  virtual void push_back(T value) {
    mData.push_back(value);
  }

  /**
   * @brief Remove the last element from the list.
   */
  virtual void pop_back() {
    mData.pop_back();
  }

  /**
   * @brief Remove all elements from the list.
   */
  virtual void clear() {
    mData.clear();
  }

  /**
   * @brief Reserve space for a number of elements.
   * @param size - The number of elements to reserve space for.
   */
  virtual void reserve(size_t size) {
    mData.reserve(size);
  }

  /**
   * @brief Resize the list to a specific size.
   * @param size - The new size of the list.
   * @param value - The value to fill the list with.
   */
  virtual void resize(size_t size, T value = T()) {
    mData.resize(size, value);
  }
  
  /**
   * @brief Erase an element from the list.
   * @param it - The iterator to the element to erase.
   */
  virtual void erase(const_iterator it) {
    boundsCheck(it);
    mData.erase(it);
  }

  /**
   * @brief Shrink the list to fit the number of elements.
   */
  virtual void shrink_to_fit() {
    mData.shrink_to_fit();
  }

  /**
   * @brief Get the number of elements in the list.
   * @return size_t 
   */
  [[nodiscard]] size_t size() const {
    return mData.size();
  }
  
  /**
   * @brief Get the number of elements that can be stored in the list without reallocation.
   * @return size_t 
   */
  [[nodiscard]] size_t capacity() const {
    return mData.capacity();
  }
  
  /**
   * @brief Assign values from an iterator range.
   * @param first - The first element.
   * @param last - The last element.
   */
  virtual void assign(const_iterator first, const_iterator last) {
    mData.assign(first, last);
  }

  T& operator[](index_t index) {
    boundsCheck(index);
    if constexpr (NegativeIndexing)
      return mData[index < 0 ? mData.size() + index : index];
    else return mData[index];
  }

  const T& operator[](index_t index) const {
    boundsCheck(index);
    if constexpr (NegativeIndexing)
      return mData[index < 0 ? mData.size() + index : index];
    else return mData[index];
  }
  
  /**
   * @brief Get the element at the specified index.
   * @param index - The index of the element to get.
   * @return T& 
   */
  T& at(index_t index) {
    boundsCheck(index);
    if constexpr (NegativeIndexing)
      return mData.at(index < 0 ? mData.size() + index : index);
    else return mData.at(index);
  }
  
  /**
   * @brief Get the element at the specified index.
   * @param index - The index of the element to get.
   * @return const T& 
   */
  const T& at(index_t index) const {
    boundsCheck(index);
    if constexpr (NegativeIndexing)
      return mData.at(index < 0 ? mData.size() + index : index);
    else return mData.at(index);
  }
  
  /**
   * @brief Get the first element in the list.
   * @return T& 
   */
  T& front() {
    return mData.front();
  }
  
  /**
   * @brief Get the first element in the list.
   * @return const T& 
   */
  const T& front() const {
    return mData.front();
  }
  
  /**
   * @brief Get the last element in the list.
   * @return T& 
   */
  T& back() {
    return mData.back();
  }
  
  /**
   * @brief Get the last element in the list.
   * @return const T& 
   */
  const T& back() const {
    return mData.back();
  }

  /**
   * @brief Get an iterator to the first element in the list.
   * @return iterator 
   */
  iterator begin() {
    return mData.begin();
  }
  
  /**
   * @brief Get an iterator to the first element in the list.
   * @return const_iterator 
   */
  const_iterator begin() const {
    return mData.begin();
  }
  
  /**
   * @brief Get an iterator to the first element in the list.
   * @return const_iterator 
   */
  const_iterator cbegin() const {
    return mData.cbegin();
  }
  
  /**
   * @brief Get an iterator to the element after the last element in the list.
   * @return iterator 
   */
  iterator end() {
    return mData.end();
  }
  
  /**
   * @brief Get an iterator to the element after the last element in the list.
   * @return const_iterator 
   */
  const_iterator end() const {
    return mData.end();
  }
  
  /**
   * @brief Get an iterator to the element after the last element in the list.
   * @return const_iterator 
   */
  const_iterator cend() const {
    return mData.cend();
  }
  
  /**
   * @brief Get a reverse iterator to the last element in the list.
   * @return reverse_iterator 
   */
  reverse_iterator rbegin() {
    return mData.rbegin();
  }
  
  /**
   * @brief Get a reverse iterator to the last element in the list.
   * @return const_reverse_iterator 
   */
  const_reverse_iterator rbegin() const {
    return mData.rbegin();
  }
  
  /**
   * @brief Get a reverse iterator to the last element in the list.
   * @return const_reverse_iterator 
   */
  const_reverse_iterator crbegin() const {
    return mData.crbegin();
  }
  
  /**
   * @brief Get a reverse iterator to the element before the first element in the list.
   * @return reverse_iterator 
   */
  reverse_iterator rend() {
    return mData.rend();
  }
  
  /**
   * @brief Get a reverse iterator to the element before the first element in the list.
   * @return const_reverse_iterator 
   */
  const_reverse_iterator rend() const {
    return mData.rend();
  }
  
  /**
   * @brief Get a reverse iterator to the element before the first element in the list.
   * @return const_reverse_iterator 
   */
  const_reverse_iterator crend() const {
    return mData.crend();
  }
  
  /**
   * @brief Check if the list is empty.
   * @return true if the list is empty.
   */
  [[nodiscard]] bool empty() const {
    return mData.empty();
  }

  /**
   * @brief Insert an element into the list.
   * @param it - The iterator to the element before which to insert.
   * @param value - The value to insert.
   */
  virtual void insert(const_iterator it, const T& value) {
    boundsCheck(it);
    mData.insert(it, value);
  }
  
  /**
   * @brief Gets the pointer to the underlying data.
   * @return T* 
   */
  T* data() {
    return mData.data();
  }
  
  /**
   * @brief Swap the contents of this list with another list.
   */
  virtual void swap(List<T, Allocator, NegativeIndexing>& other) {
    mData.swap(other.mData);
  }

  // non-standard

  /**
   * @brief Gets a copy of the underlying data.
   * @return std::vector<T>
   */
  std::vector<T> get() {
    return mData;
  }

  /**
   * @brief Get const reference to the underlying data.
   * @return const std::vector<T>& 
   */
  const std::vector<T>& get() const {
    return mData;
  }
  
  /**
   * @brief Adds an element to the front of the list.
   * @param element - The element to add.
   */
  virtual void push_front(T element) {
    mData.insert(mData.begin(), element);
  }
  
  /**
   * @brief Removes the first element in the list.
   */
  virtual void pop_front() {
    mData.erase(mData.begin());
  }

  /**
   * @brief Makes a partial copy of the list. If start < end, the elements will be copied in reverse order.
   * @param start - The iterator to the first element to copy.
   * @param end - The iterator to the element after the last element to copy.
   */
  List<T> slice(const_iterator start, const_iterator end) {
    boundsCheck(start);
    boundsCheck(end);
    List<T> ret;
    if (start > end)
      for (auto it = start; it != end; --it)
        ret.push_back(*it);
    else
      for (auto it = start; it != end; ++it)
        ret.push_back(*it);
    return ret;
  }

  /**
   * @brief Makes a partial copy of the list. If start < end, the elements will be copied in reverse order.
   * @param start - The iterator to the first element to copy.
   * @param end - The iterator to the element after the last element to copy.
   */
  List<T> slice(const_iterator start, const_iterator end) const {
    boundsCheck(start);
    boundsCheck(end);
    List<T> ret;
    if (start > end)
      for (auto it = start; it != end; --it)
        ret.push_back(*it);
    else
      for (auto it = start; it != end; ++it)
        ret.push_back(*it);
    return ret;
  }

  /**
   * @brief Makes a partial copy of the list. If start < end, the elements will be copied in reverse order.
   * @param start - The index of the first element to copy.
   * @param end - The index of the element after the last element to copy.
   */
  List<T> slice(index_t start, index_t end) {
    boundsCheck(start);
    boundsCheck(end);
    if constexpr (NegativeIndexing) {
      if (start < 0) start = mData.size() + start;
      if (end < 0) end = mData.size() + end;
    }
    auto startIt = mData.begin() + start;
    auto endIt = mData.begin() + end;
    return slice(startIt, endIt);
  }

  /**
   * @brief Makes a partial copy of the list. If start < end, the elements will be copied in reverse order.
   * @param start - The index of the first element to copy.
   * @param end - The index of the element after the last element to copy.
   */
  List<T> slice(index_t start, index_t end) const {
    boundsCheck(start);
    boundsCheck(end);
    if constexpr (NegativeIndexing) {
      if (start < 0) start = mData.size() + start;
      if (end < 0) end = mData.size() + end;
    }
    auto startIt = mData.begin() + start;
    auto endIt = mData.begin() + end;
    return slice(startIt, endIt);
  }

protected:
  constexpr void boundsCheck(index_t index) {
    if constexpr (AMSExceptions) {
      if constexpr (NegativeIndexing) {
        // if index is negative, check if the absolute value is less than or equal to the size
        // if index is positive, check if the index is less than the size
        if (index < 0 ? -index > mData.size() : index >= mData.size()) {
          throw std::out_of_range("Index out of range");
        }
        
      }
      else if (index < 0 || index >= mData.size())
        throw std::out_of_range("Index out of range.");
    }
  }
  
  void boundsCheck(const_iterator it) {
    if constexpr (AMSExceptions)
      if (it < mData.begin() || it > mData.end())
        throw std::out_of_range("Iterator out of range.");
  }

};

} // namespace ams
