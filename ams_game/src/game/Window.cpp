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

#ifndef AMS_MODULES
#include <ams/spatial/Vec.hpp>
#include "ams/game/Window.hpp"
#include "ams/game/Application.hpp"
#include "ams/game/Platform.hpp"
#include <regex>
#else
import ams.spatial.Vec;
import ams.game.Window;
import ams.game.Application;
import ams.game.Platform;
import <regex>;
#endif

#include <GLFW/glfw3.h>


const std::regex windowNameRgx = std::regex("^[a-zA-Z0-9_.-]+[a-zA-Z0-9_. -]+$");

namespace ams {

Window* Window::getWindow(GLFWwindow* window) {
  return _windows[window];
}

Window::Window(Display& display, const WindowConfig& opt) : Object(opt.title),
_display(display),
_window(nullptr, glfwDestroyWindow)
{
  checkTitle(opt.title);
  checkSize(opt.size);
  _isFullscreen = opt.fullscreen;
  _isResizable = opt.resizable;
  if (!_isFullscreen) {
    _isMaximized = opt.maximized;
    _isIconified = opt.minimized && !_isMaximized;
  }
  _minSize = opt.minSize;
  _maxSize = opt.maxSize;
  _position = opt.position;
  create();

  glfwSetCharCallback(_window.get(), handleCharEvent);
  glfwSetCharModsCallback(_window.get(), handleCharModsEvent);
  glfwSetKeyCallback(_window.get(), handleKeyEvent);
  glfwSetMouseButtonCallback(_window.get(), handleMouseButtonEvent);
  glfwSetScrollCallback(_window.get(), handleMouseScrollEvent);
  glfwSetCursorPosCallback(_window.get(), handleMousePositionEvent);
  glfwSetCursorEnterCallback(_window.get(), handleCursorEnterEvent);
  glfwSetDropCallback(_window.get(), handleDropEvent);
  glfwSetWindowCloseCallback(_window.get(), handleWindowCloseEvent);
  glfwSetWindowFocusCallback(_window.get(), handleWindowFocusEvent);
  glfwSetWindowIconifyCallback(_window.get(), handleWindowIconifyEvent);
  glfwSetWindowPosCallback(_window.get(), handleWindowPositionEvent);
  glfwSetWindowSizeCallback(_window.get(), handleWindowSizeEvent);
  glfwSetFramebufferSizeCallback(_window.get(), handleFramebufferSizeEvent);
  glfwSetWindowRefreshCallback(_window.get(), handleWindowRefreshEvent);
  glfwSetWindowMaximizeCallback(_window.get(), handleWindowMaximizeEvent);
  glfwSetWindowContentScaleCallback(_window.get(), handleWindowContentScaleEvent);

  // statically register this window.
  _windows[_window.get()] = this;
}

Window::~Window() {
  destroy();
}

void Window::create() {
  if (_window) {
    return;
  } // if user tries to create a window that already exists, do nothing.

  if (glfwInit() == GLFW_FALSE) {
    if constexpr (AMSExceptions) {
      throw std::runtime_error("Failed to initialize GLFW");
    }
  }

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, _isResizable ? GLFW_TRUE : GLFW_FALSE);

  if (_isFullscreen)
    _window.reset(glfwCreateWindow(_size.x, _size.y, name.c_str(), _display.getHandle(), nullptr));
  else
    _window.reset(glfwCreateWindow(_size.x, _size.y, name.c_str(), nullptr, nullptr));
  if constexpr (AMSExceptions) {
    if (!_window)
      throw std::runtime_error("Failed to create window");
  }

  setSizeLimits(_minSize, _maxSize);
  setPosition(_position);
  if (_isFullscreen)
    setIsFullscreen(_isFullscreen);
  else if (_isMaximized)
    setIsMaximized(_isMaximized);
  else if (_isIconified)
    setIsIconified(_isIconified);
  _isCreated = true;
}

void Window::destroy() {
  if (!_window) {
    return;
  }
  _windows.erase(_window.get());
  _window.reset();
  _isCreated = false;
  if (_windows.empty()) 
    glfwTerminate();
}

void Window::update() {
  glfwPollEvents();
}

#pragma region Accessors

void Window::setSize(const Vec2<int>& size) {
  checkSize(size);
  glfwSetWindowSize(_window.get(), _size.x, _size.y);
}

Vec2<int> Window::getSize() {
  glfwGetWindowSize(_window.get(), &_size.x, &_size.y);
  return _size;
}

void Window::setTitle(const std::string& title) {
  checkTitle(title);
  if (_window)
    glfwSetWindowTitle(_window.get(), name.c_str());
}

std::string Window::getTitle() const {
  return name;
}

void Window::setPosition(const Vec2<int>& position) {
  _position = position;
  if (_window)
    glfwSetWindowPos(_window.get(), _position.x, _position.y);
}

Vec2<int> Window::getPosition() {
  glfwGetWindowPos(_window.get(), &_position.x, &_position.y);
  return Vec2<int>(_position);
}

void Window::setIsFullscreen(bool fullscreen) {
  if (fullscreen && (_isFullscreen != fullscreen || !_isCreated)) {
    auto size = getClosestResolution(_size);
    glfwSetWindowMonitor(_window.get(), _display.getHandle(), 0, 0, size.x, size.y, GLFW_DONT_CARE);
  } else {
    glfwSetWindowMonitor(_window.get(), nullptr, _position.x, _position.y, _size.x, _size.y, GLFW_DONT_CARE);
  }
  _isFullscreen = fullscreen;
}

bool Window::getIsFullscreen() const {
  return _isFullscreen;
}

void Window::setIsMaximized(bool maximized) {
  if (_isFullscreen) return;
  if (maximized && (_isMaximized != maximized || !_isCreated))
    glfwMaximizeWindow(_window.get());
  else
    glfwRestoreWindow(_window.get());
  _isMaximized = maximized;
}

bool Window::getIsMaximized() const {
  return _isMaximized;
}

void Window::setIsMinimized(bool minimized) {
  setIsIconified(minimized);
}

bool Window::getIsMinimized() {
  return getIsIconified();
}

void Window::setIsFocused(bool isFocused) {
  if (isFocused) {
    if (System.os != Platform::Linux)
      glfwFocusWindow(_window.get());
  }
  _isFocused = glfwGetWindowAttrib(_window.get(), GLFW_FOCUSED) == GLFW_TRUE;
}

bool Window::getIsFocused() {
  _isFocused = glfwGetWindowAttrib(_window.get(), GLFW_FOCUSED) == GLFW_TRUE;
  return _isFocused;
}

bool Window::getIsResizable() const {
  return glfwGetWindowAttrib(_window.get(), GLFW_RESIZABLE) == GLFW_TRUE;
}

void Window::setIsIconified(bool isIconified) {
  if (_isFullscreen) return;
  if (isIconified && (_isIconified != isIconified || !_isCreated))
    glfwIconifyWindow(_window.get());
  else
    glfwRestoreWindow(_window.get());
  _isIconified = isIconified;
}

bool Window::getIsIconified() {
  _isIconified = glfwGetWindowAttrib(_window.get(), GLFW_ICONIFIED) == GLFW_TRUE;
  return _isIconified;
}

void Window::setShouldClose(bool value) {
  glfwSetWindowShouldClose(_window.get(), value);
}

bool Window::getShouldClose() const {
  return glfwWindowShouldClose(_window.get());
}

void Window::setSizeLimits(const Vec2<int>& minSize, const Vec2<int>& maxSize) {
  _minSize = minSize;
  _maxSize = maxSize;
  glfwSetWindowSizeLimits(_window.get(), _minSize.x, _minSize.y, _maxSize.x, _maxSize.y);
}

Vec2<int> Window::getMinSize() const {
  return _minSize;
}

Vec2<int> Window::getMaxSize() const {
  return _maxSize;
}

bool Window::getIsHovered() const {
  return glfwGetWindowAttrib(_window.get(), GLFW_HOVERED) == GLFW_TRUE;
}

GLFWwindow* Window::getHandle() const {
  return _window.get();
}

#pragma endregion Accessors

void Window::checkTitle(const std::string& title) {
  if (!std::regex_match(title, windowNameRgx)) {
    if constexpr (AMSExceptions)
      throw std::invalid_argument("Window title must begin with a letter or number and must be alphanumeric.");
    else
      name = "INVALID TITLE";
  }
  name = title;
}


void Window::checkSize(const Vec2<int>& size) {
  int width = size.x;
  int height = size.y;
  if (width <= 0 || height <= 0) {
      width = width <= 0 ? 1 : width;
      height = height <= 0 ? 1 : height;
  }
  if (_isFullscreen) {
    auto res = getClosestResolution(size);
    width = res.x;
    height = res.y;
  }
  _size = {width, height};
}

Vec2<int> Window::getClosestResolution(const Vec2<int>& size) {
  auto rezs = _display.getSupportedResolutions();
  Vec2<int> closest = nearest(size, rezs);
  return closest;
}

#pragma region Operators

bool Window::operator==(const Window& other) const {
  return _window.get() == other._window.get();
}

bool Window::operator!=(const Window& other) const {
  return _window.get() != other._window.get();
}

bool Window::operator==(const GLFWwindow* other) const {
  return _window.get() == other;
}

bool Window::operator!=(const GLFWwindow* other) const {
  return _window.get() != other;
}

#pragma endregion Operators


// handleCharEvent
// std::vector<Function<void, Key>> _charCallbacks{};
// handleCharModsEvent
// std::vector<Function<void, KeyPress>> _charModsCallbacks{};
// handleKeyEvent
// std::vector<Function<void, KeyPress>> _keyCallbacks{};
// handleMouseButtonEvent
// std::vector<Function<void, MousePress>> _mouseButtonCallbacks{};
// handleMouseScrollEvent
// std::vector<Function<void, Vec2<decimal_t>>> _mouseScrollCallbacks{};
// handleMousePositionEvent
// std::vector<Function<void, Vec2<decimal_t>>> _mousePositionCallbacks{};
// handleCursorEnterEvent
// std::vector<Function<void, bool>> _cursorEnterCallbacks{};
// handleDropEvent
// std::vector<Function<void, std::vector<std::string>>> _dropCallbacks{};
// handleWindowCloseEvent
// std::vector<Function<void>> _windowCloseCallbacks{};
// handleWindowFocusEvent
// std::vector<Function<void, bool>> _windowFocusCallbacks{};
// handleWindowIconifyEvent
// std::vector<Function<void, bool>> _windowIconifyCallbacks{};
// handleWindowPositionEvent
// std::vector<Function<void, Vec2<int>>> _windowPositionCallbacks{};
// handleWindowSizeEvent
// std::vector<Function<void, Vec2<int>>> _windowSizeCallbacks{};
// handleWindowMaximizeEvent
// std::vector<Function<void, bool>> _windowMaximizeCallbacks{};
// handleFramebufferSizeEvent
// std::vector<Function<void, Vec2<int>>> _framebufferSizeCallbacks{};
// handleWindowRefreshEvent
// std::vector<Function<void>> _windowRefreshCallbacks{};
// handleWindowContentScaleEvent
// std::vector<Function<void, Vec2<decimal_t>>> _windowContentScaleCallbacks{};

void Window::handleCharEvent(GLFWwindow* window, unsigned int codepoint) {
  if (auto win = getWindow(window)) {
    auto key = glfwToKey(codepoint);
    for (auto& f : win->_charCallbacks) {
      f(key);
    }
  }
}

void Window::handleCharModsEvent(GLFWwindow* window, unsigned int codepoint, int mods) {
  if (auto win = getWindow(window)) {
    auto keyPress = KeyPress{glfwToKey(codepoint), mods};
    for (auto& f : win->_charModsCallbacks) {
      f(keyPress);
    }
  }
}

void Window::handleKeyEvent(GLFWwindow* window, int keycode, int scancode, int action, int mods) {
  if (auto win = getWindow(window)) {
    auto keyPress = KeyPress{glfwToKey(keycode), mods};
    for (auto& f : win->_keyCallbacks) {
      f(keyPress);
    }
  }
}

void Window::handleMouseButtonEvent(GLFWwindow* window, int button, int action, int mods) {
  if (auto win = getWindow(window)) {
    auto mousePress = MousePress{ams::toMouseButton(button), ams::toMouseAction(action), mods};
    for (auto& f : win->_mouseButtonCallbacks) {
      f(mousePress);
    }
  }
}

void Window::handleMouseScrollEvent(GLFWwindow* window, double xoffset, double yoffset) {
  if (auto win = getWindow(window)) {
    auto offset = Vec2<decimal_t>{xoffset, yoffset};
    for (auto& f : win->_mouseScrollCallbacks) {
      f(offset);
    }
  }
}

void Window::handleMousePositionEvent(GLFWwindow* window, double xpos, double ypos) {
  if (auto win = getWindow(window)) {
    auto pos = Vec2<decimal_t>{xpos, ypos};
    for (auto& f : win->_mousePositionCallbacks) {
      f(pos);
    }
  }
}

void Window::handleCursorEnterEvent(GLFWwindow* window, int entered) {
  if (auto win = getWindow(window)) {
    bool enteredBool = entered == GLFW_TRUE;
    for (auto& f : win->_cursorEnterCallbacks) {
      f(enteredBool);
    }
  }
}

void Window::handleDropEvent(GLFWwindow* window, int count, const char** paths) {
  if (auto win = getWindow(window)) {
    std::vector<std::string> pathsVec;
    for (int i = 0; i < count; i++) {
      pathsVec.push_back(paths[i]);
    }
    for (auto& f : win->_dropCallbacks) {
      f(pathsVec);
    }
  }
}

void Window::handleWindowCloseEvent(GLFWwindow* window) {
  if (auto win = getWindow(window)) {
    win->_isClosing = true;
    for (auto& f : win->_windowCloseCallbacks) {
      f();
    }
  }
}

void Window::handleWindowFocusEvent(GLFWwindow* window, int focused) {
  if (auto win = getWindow(window)) {
    bool focusedBool = focused == GLFW_TRUE;
    win->_isFocused = focusedBool;
    for (auto& f : win->_windowFocusCallbacks) {
      f(focusedBool);
    }
  }
}

void Window::handleWindowIconifyEvent(GLFWwindow* window, int iconified) {
  if (auto win = getWindow(window)) {
    bool iconifiedBool = iconified == GLFW_TRUE;
    win->_isIconified = iconifiedBool;
    for (auto& f : win->_windowIconifyCallbacks) {
      f(iconifiedBool);
    }
  }
}

void Window::handleWindowPositionEvent(GLFWwindow* window, int xpos, int ypos) {
  if (auto win = getWindow(window)) {
    auto pos = Vec2<int>{xpos, ypos};
    win->_position = pos;
    for (auto& f : win->_windowPositionCallbacks) {
      f(pos);
    }
  }
}

void Window::handleWindowSizeEvent(GLFWwindow* window, int width, int height) {
  if (auto win = getWindow(window)) {
    if (win->_isFullscreen) return;
    auto size = Vec2<int>{width, height};
    if (win->_size == size) return;
    win->_size = size;
    for (auto& f : win->_windowSizeCallbacks) {
      f(size);
    }
  }
}

void Window::handleWindowMaximizeEvent(GLFWwindow* window, int maximized) {
  if (auto win = getWindow(window)) {
    bool maximizedBool = maximized == GLFW_TRUE;
    win->_isMaximized = maximizedBool;
    for (auto& f : win->_windowMaximizeCallbacks) {
      f(maximizedBool);
    }
  }
}

void Window::handleFramebufferSizeEvent(GLFWwindow* window, int width, int height) {
  if (auto win = getWindow(window)) {
    auto size = Vec2<int>{width, height};
    win->_framebufferSize = size;
    for (auto& f : win->_framebufferSizeCallbacks) {
      f(size);
    }
  }
}

void Window::handleWindowRefreshEvent(GLFWwindow* window) {
  if (auto win = getWindow(window)) {
    for (auto& f : win->_windowRefreshCallbacks) {
      f();
    }
  }
}

void Window::handleWindowContentScaleEvent(GLFWwindow* window, float xscale, float yscale) {
  if (auto win = getWindow(window)) {
    auto scale = Vec2<decimal_t>{xscale, yscale};
    win->_contentScale = scale;
    for (auto& f : win->_windowContentScaleCallbacks) {
      f(scale);
    }
  }
}


// the end :)
} // ams