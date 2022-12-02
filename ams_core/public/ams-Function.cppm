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
module;
#ifndef AMS_MODULES_STD
#include <functional>
#include <random>
#endif
export module ams:Function;
#ifdef AMS_MODULES_STD
import std;
#endif


namespace ams {

/**
 * @brief Function is a wrapper for std::function with comparison operators.
 * @tparam Tr - Return type of the function.
 * @tparam Tp - Parameter type(s) of the function.
 * @example 
 * <code><p>ams::Function&lt;void, int&gt; f([](int i) {</p>
 * <p>std::cout &lt&lt i &lt&lt std::endl;</p>
 * <p>});</p></code>
 * <p>When passed as a parameter using lambda syntax, brackets must enclose the lambda:</p>
 * <p><code>
 * foo({[]() -> void { return; }}); // &lt= Brackets are required.
 * </code></p>
 */
export template <typename Tr, typename ... Tp>
class Function {
private:
  // random number generator

private:
  uint64_t _id;
  std::function<Tr(Tp...)> _function;
public:
  Function() {
    _id = getRandomId();
  }
  
  explicit Function(const std::function<Tr(Tp...)>& function) : _function(function) {
    _id = getRandomId();
  }
  
  Function(std::function<Tr(Tp...)>&& function) : _function(std::move(function)) {
    _id = getRandomId();
  }
  
  Function(const Function& other) = default;
  
  Function(Function&& other) noexcept = default;
  
  Function& operator=(const Function& other) = default;
  
  Function& operator=(Function&& other) noexcept = default;
  
  ~Function() = default;

  /**
   * @brief Get the id of the function.
   */
  uint64_t id() const {
    return _id;
  }
  
  bool operator==(const Function& other) const {
    return _id == other._id;
  }
  
  bool operator!=(const Function& other) const {
    return _id != other._id;
  }
  
  explicit operator bool() const {
    return _function.operator bool();
  }
  
  // call operator
  Tr operator()(Tp... args) const {
    return _function(args...);
  }

  // lambda assignment operator
  Function& operator=(const std::function<Tr(Tp...)>& function) {
    _function = function;
    _id = getRandomId();
    return *this;
  }
  
  // lambda move assignment
  Function& operator=(std::function<Tr(Tp...)>&& function) {
    _function = std::move(function);
    _id = getRandomId();
    return *this;
  }

private:
  uint64_t getRandomId() {
    static std::random_device rd;
    static std::mt19937_64 gen{rd()};
    static std::uniform_int_distribution<uint64_t> dis;
    return dis(gen);
  }
  
};

} // namespace ams

