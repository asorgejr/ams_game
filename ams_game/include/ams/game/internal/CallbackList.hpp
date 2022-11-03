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

/*[export module ams.game.CallbackList]*/
/*[exclude begin]*/
#pragma once
#include <ams/List.hpp>
/*[exclude end]*/
#include <functional>
#include <vector>
/*[import ams.List]*/

/*[export]*/ namespace ams::internal {

template<typename T>
class CallbackList : public List<T> {
private:
  std::function<void(T)> _addCallback{};
  std::function<void(T)> _removeCallback{};
public:
  using List<T>::List;
  
  CallbackList(std::function<void(T)> addCallback, std::function<void(T)> removeCallback)
  : _addCallback(addCallback),
  _removeCallback(removeCallback) {}
  
  CallbackList(const CallbackList& other) = delete;
  
  CallbackList operator=(const CallbackList& other) = delete;

  ~CallbackList() {
    clear();
  }
  
  void push_back(T value) override {
    List<T>::push_back(value);
    _addCallback(value);
  }
  
  void push_front(T value) override {
    List<T>::push_front(value);
    _addCallback(value);
  }
  
  void pop_back() override {
    _removeCallback(List<T>::back());
    List<T>::pop_back();
  }
  
  void pop_front() override {
    _removeCallback(List<T>::front());
    List<T>::pop_front();
  }
  
  void clear() override {
    for (auto& value : List<T>::mData) {
      _removeCallback(value);
    }
    List<T>::clear();
  }
  
  void reserve(size_t size) override {
    List<T>::reserve(size);
  }
  
  void resize(size_t size, T value=T()) override {
    if (size > List<T>::size()) {
      List<T>::resize(size, value);
    } else {
      for (size_t i = size; i < List<T>::size(); ++i) {
        _removeCallback(List<T>::at(i));
      }
      List<T>::resize(size, value);
    }
  }
  
  void shrink_to_fit() override {
    List<T>::shrink_to_fit();
  }

  void insert(typename List<T>::const_iterator it, const T& value) override {
    List<T>::insert(it, value);
    _addCallback(value);
  }

  void erase(typename List<T>::const_iterator it) override {
    List<T>::boundsCheck(it);
    _removeCallback(*it);
    List<T>::erase(it);
  }

  // modifiers
  void swap(CallbackList& other) {
    std::swap(_addCallback, other._addCallback);
    std::swap(_removeCallback, other._removeCallback);
    List<T>::swap(other);
  }

  // observers
  void setAddCallback(std::function<void(T)> addCallback) {
    _addCallback = addCallback;
  }

  void setRemoveCallback(std::function<void(T)> removeCallback) {
    _removeCallback = removeCallback;
  }

  std::function<void(T)> getAddCallback() const {
    return _addCallback;
  }
  
  std::function<void(T)> getRemoveCallback() const {
    return _removeCallback;
  }

  /**
   * @brief Adds a value to the list and calls the add callback.
   * @param value - The value to add.
   */
  void add(T value) {
    push_back(value);
  }

  /**
   * @brief Removes a value from the list and calls the remove callback.
   * @param value - The value to remove.
   */
  void remove(T value) {
    auto it = std::find(List<T>::begin(), List<T>::end(), value);
    if (it != List<T>::end()) {
      _removeCallback(value);
      List<T>::erase(it);
    }
  }

  /**
   * @brief Removes a value from the list and calls the remove callback.
   * @param index - The index of the value to remove.
   */
  void removeAt(size_t index) {
    _removeCallback(List<T>::at(index));
    List<T>::erase(List<T>::begin() + index);
  }

  /**
   * @brief Removes a value if the predicate returns true and calls the remove callback.
   */
  void removeIf(std::function<bool(T)> predicate) {
    for (auto it = List<T>::begin(); it != List<T>::end();) {
      if (predicate(*it)) {
        _removeCallback(*it);
        it = List<T>::erase(it);
      } else {
        ++it;
      }
    }
  }

  /**
   * @brief Removes the value at the front of the list and calls the remove callback.
   */
  void removeFirst() {
    _removeCallback(List<T>::front());
    List<T>::erase(List<T>::begin());
  }

  /**
   * @brief Removes the value at the back of the list and calls the remove callback.
   */
  void removeLast() {
    _removeCallback(List<T>::back());
    List<T>::pop_back();
  }

  /**
   * @brief Removes all values from the list and calls the remove callback.
   */
  void removeAll() {
    clear();
  }

  /**
   * @brief Replace the value at the given index with the new value and calls both the remove and add callback.
   * @param index - The index of the value to replace.
   * @param newValue - The value to replace with.
   */
  void replaceAt(size_t index, T newValue) {
    _removeCallback(List<T>::mData[index]);
    List<T>::mData[index] = newValue;
    _addCallback(newValue);
  }

  /**
   * @brief Replace all occurrences of the old value with the new value and calls both the remove and add callback.
   * @param oldValue - The value to replace.
   * @param newValue - The value to replace with.
   */
  void replace(T oldValue, T newValue) {
    for (auto& value : List<T>::mData) {
      if (value == oldValue) {
        _removeCallback(oldValue);
        value = newValue;
        _addCallback(newValue);
      }
    }
  }

  /**
   * @brief Replace all values if the predicate returns true and calls both the remove and add callback.
   * @param predicate - The predicate to test.
   * @param newValue - The value to replace with.
   */
  void replaceIf(std::function<bool(T)> predicate, T newValue) {
    for (auto& value : List<T>::mData) {
      if (predicate(value)) {
        _removeCallback(value);
        value = newValue;
        _addCallback(newValue);
      }
    }
  }

  /**
   * @brief Replace the first occurrence of the value with the new value and calls both the remove and add callback.
   * @param newValue - The value to replace with.
   */
  void replaceFirst(T oldValue, T newValue) {
    auto it = std::find(List<T>::begin(), List<T>::end(), oldValue);
    if (it != List<T>::end()) {
      _removeCallback(oldValue);
      *it = newValue;
      _addCallback(newValue);
    }
  }

  /**
   * @brief Replace the last occurrence of the value with the new value and calls both the remove and add callback.
   * @param newValue - The value to replace with.
   */
  void replaceLast(T oldValue, T newValue) {
    auto it = std::find(List<T>::rbegin(), List<T>::rend(), oldValue);
    if (it != List<T>::rend()) {
      _removeCallback(oldValue);
      *it = newValue;
      _addCallback(newValue);
    }
  }

};

} // ams
