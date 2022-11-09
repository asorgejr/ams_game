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
/*[module]*/

/*[exclude begin]*/
#pragma once
/*[exclude end]*/
/*[ignore begin]*/
#include "ams_game_export.hpp"
/*[ignore end]*/
/*[exclude begin]*/
#include <ams/Function.hpp>
#include <ams/spatial/Vec/Vec2.hpp>
#include "Object.hpp"
#include "Display.hpp"
#include "Key.hpp"
#include "Mouse.hpp"
/*[exclude end]*/

/*[export module ams.game.Window]*/
#include <memory>
#include <functional>
#include <vector>
#include <map>
/*[import ams.Function]*/
/*[import ams.game.Object]*/
/*[import ams.game.Display]*/
/*[import ams.game.Key]*/
/*[import ams.game.MouseButton]*/

typedef struct GLFWwindow GLFWwindow;

/*[export]*/ namespace ams {

class Application;
class Window;

using WindowCallbackFunc = Function<void, const Window*>;

/**
 * @brief Window configuration options.
 * @details This struct is used to configure a window before it is created.
 * Not all options can be true at the same time. Obvious situations like a window that is both fullscreen and minimized
 * are not allowed. The window will be created with the closest possible configuration to the one specified.
 * The order of precedence is as follows:
 *   resizable > fullscreen > maximized > minimized > focused.
 */
struct WindowConfig {
  std::string title;
  Vec2<int> size={800, 600};
  Vec2<int> position={0, 0};
  bool fullscreen=false; // If true, the window will be created in fullscreen mode.
  bool resizable=true; // If true, the window can be resized.
  bool maximized=false; // If true, the window can be maximized, if it is not fullscreen.
  bool minimized=false; // If true, the window can be minimized, if it is not fullscreen.
  Vec2<int> minSize={1, 1}; // The minimum size of the window, if it is resizable.
  Vec2<int> maxSize={-1, -1}; // The maximum size of the window, if it is resizable. A value of <= 0 means no limit.
};

/**
 * @brief Window manages the creation and destruction of a GLFW window.
 */
class AMS_GAME_EXPORT Window final : public Object {
private:
  Display _display;
  std::unique_ptr<GLFWwindow, void (*)(GLFWwindow*)> _window;
  Vec2<int> _size;
  Vec2<int> _position;
  Vec2<int> _minSize {-1, -1};
  Vec2<int> _maxSize {-1, -1};
  Vec2<int> _framebufferSize;
  Vec2<float> _contentScale {1.0f, 1.0f};
  bool _isFullscreen = false;
  bool _isResizable = false;
  bool _isFocused = true;
  bool _isMaximized = false;
  bool _isIconified = false; // is minimized
  bool _isHovered = false;
  bool _isCreated = false;
  bool _isClosing = false;

  // Callbacks
  std::vector<Function<void, Key>> _charCallbacks{};
  std::vector<Function<void, const KeyPress&>> _charModsCallbacks{};
  std::vector<Function<void, const KeyPress&>> _keyCallbacks{};
  std::vector<Function<void, const MousePress&>> _mouseButtonCallbacks{};
  std::vector<Function<void, const Vec2<decimal_t>&>> _mouseScrollCallbacks{};
  std::vector<Function<void, const Vec2<decimal_t>&>> _mousePositionCallbacks{};
  std::vector<Function<void, bool>> _cursorEnterCallbacks{};
  std::vector<Function<void, std::vector<std::string>>> _dropCallbacks{};
  std::vector<Function<void>> _windowCloseCallbacks{};
  std::vector<Function<void, bool>> _windowFocusCallbacks{};
  std::vector<Function<void, bool>> _windowIconifyCallbacks{};
  std::vector<Function<void, const Vec2<int>&>> _windowPositionCallbacks{};
  std::vector<Function<void, const Vec2<int>&>> _windowSizeCallbacks{};
  std::vector<Function<void, const Vec2<int>&>> _framebufferSizeCallbacks{};
  std::vector<Function<void>> _windowRefreshCallbacks{};
  std::vector<Function<void, bool>> _windowMaximizeCallbacks{};
  std::vector<Function<void, const Vec2<decimal_t>&>> _windowContentScaleCallbacks{};
  
  /** @brief Any active Window instance will be in this vector. */
  inline static std::map<GLFWwindow*, Window*> _windows;
  
public:
  Window(Display& display, const WindowConfig& options={"Window"});
  ~Window();
  
  /**
   * @brief Creates the window with the given title and size.
   * @param isResizable - If the window is resizable.
   */
  void create();
  /**
   * @brief Destroys the window.
   */
  void destroy();
  
  /**
   * @brief Updates the window.
   * @details Updates the window by polling events. 
   * @see glfwPollEvents
   */
  void update();

#pragma region Accessors

  /**
   * @brief Sets the window title.
   * @param title - The new window title.
   */
  void setTitle(const std::string& title);
  /**
   * @brief Gets the window title.
   */
  [[nodiscard]] std::string getTitle() const;
  
  /**
   * @brief Sets the window size
   * @param size - The new window size.
   */
  void setSize(const Vec2<int>& size);
  /**
   * @brief Gets the window size.
   */
  [[nodiscard]] Vec2<int> getSize();
  
  /**
   * @brief Sets the window position.
   * @param position - The new window position in screen coordinates.
   */
  void setPosition(const Vec2<int>& position);
  /**
   * @brief Gets the window position in screen coordinates.
   */
  [[nodiscard]] Vec2<int> getPosition();
  
  /**
   * @brief Sets whether the window is fullscreen.
   * @param fullscreen - If true, the window will be fullscreen.
   */
  void setIsFullscreen(bool fullscreen);
  /**
   * @brief Gets whether the window is fullscreen.
   */
  [[nodiscard]] bool getIsFullscreen() const;

  [[nodiscard]] bool getIsResizable() const;
  
  /**
   * @brief Sets whether the window is maximized.
   * @param maximized - If true, the window will be maximized. If the window is currently fullscreen, this will have
   * no effect.
   */
  void setIsMaximized(bool maximized);
  /**
   * @brief Gets whether the window is maximized.
   */
  [[nodiscard]] bool getIsMaximized() const;
  
  /**
   * @brief Sets whether the window is minimized.
   * @param minimized - If true, the window will be minimized. If the window is currently fullscreen, this will have
   * no effect.
   */
  void setIsMinimized(bool minimized);
  /**
   * @brief Gets whether the window is minimized.
   */
  [[nodiscard]] bool getIsMinimized();
  
  /**
   * @brief Sets whether the window is focused.
   * @param isFocused - If true, the window will be focused.
   */
  void setIsFocused(bool isFocused);
  /**
   * @brief Gets whether the window is focused. If the window is not focused or minimized, this will return false.
   */
  [[nodiscard]] bool getIsFocused();
  
  /**
   * @brief Sets whether the window is iconified.
   * @param isIconified - If true, the window will be iconified.
   * @details Iconified windows are minimized.
   */
  void setIsIconified(bool isIconified);
  /**
   * @brief Gets whether the window is iconified (minimized).
   */
  [[nodiscard]] bool getIsIconified();
  
  void setShouldClose(bool shouldClose);
  bool getShouldClose() const;
  
  /**
   * @brief Sets the size limits of the window.
   * @param minSize - The minimum size of the window. A value of -1 for either dimension will disable the limit.
   * @param maxSize - The maximum size of the window. A value of -1 for either dimension will disable the limit.
   */
  void setSizeLimits(const Vec2<int>& minSize=-1, const Vec2<int>& maxSize=-1);
  /**
   * @brief Gets the minimum size of the window.
   */
  [[nodiscard]] Vec2<int> getMinSize() const;
  /**
   * @brief Gets the maximum size of the window.
   */
  [[nodiscard]] Vec2<int> getMaxSize() const;
  
  [[nodiscard]] bool getIsHovered() const;

  /**
   * @brief Gets the raw GLFW window pointer. Use with caution.
   * @details This is used internally by the engine. You should not need to use this.
   * @note The lifetime of the GLFWwindow* is managed by the Window instance. Do not delete it.
   */
  [[nodiscard]] GLFWwindow* getHandle() const;

  /**
   * @brief Gets a Window instance from a GLFW window pointer.
   * @param window - The GLFW window pointer.
   */
  static Window* getWindow(GLFWwindow* window);

#pragma endregion Accessors
  
#pragma region Operators

  // GLFWwindow comparison operators
  bool operator==(const Window& other) const;
  bool operator!=(const Window& other) const;
  bool operator==(const GLFWwindow* other) const;
  bool operator!=(const GLFWwindow* other) const;
  
#pragma endregion Operators

#pragma region CallbackRegistration
  void registerCharCallback(Function<void, Key>& callback) { _charCallbacks.push_back(callback); }
  void unregisterCharCallback(Function<void, Key>& callback) { _charCallbacks.erase(std::remove(_charCallbacks.begin(), _charCallbacks.end(), callback), _charCallbacks.end()); }

  void registerCharModsCallback(Function<void, const KeyPress&>& callback) { _charModsCallbacks.push_back(callback); }
  void unregisterCharModsCallback(Function<void, const KeyPress&>& callback) { _charModsCallbacks.erase(std::remove(_charModsCallbacks.begin(), _charModsCallbacks.end(), callback), _charModsCallbacks.end()); }

  void registerKeyCallback(Function<void, const KeyPress&>& callback) { _keyCallbacks.push_back(callback); }
  void unregisterKeyCallback(Function<void, const KeyPress&>& callback) { _keyCallbacks.erase(std::remove(_keyCallbacks.begin(), _keyCallbacks.end(), callback), _keyCallbacks.end()); }

  void registerMouseButtonCallback(Function<void, const MousePress&>& callback) { _mouseButtonCallbacks.push_back(callback); }
  void unregisterMouseButtonCallback(Function<void, const MousePress&>& callback) { _mouseButtonCallbacks.erase(std::remove(_mouseButtonCallbacks.begin(), _mouseButtonCallbacks.end(), callback), _mouseButtonCallbacks.end()); }

  void registerMouseScrollCallback(Function<void, const Vec2<decimal_t>&>& callback) { _mouseScrollCallbacks.push_back(callback); }
  void unregisterMouseScrollCallback(Function<void, const Vec2<decimal_t>&>& callback) { _mouseScrollCallbacks.erase(std::remove(_mouseScrollCallbacks.begin(), _mouseScrollCallbacks.end(), callback), _mouseScrollCallbacks.end()); }

  void registerMousePositionCallback(Function<void, const Vec2<decimal_t>&>& callback) { _mousePositionCallbacks.push_back(callback); }
  void unregisterMousePositionCallback(Function<void, const Vec2<decimal_t>&>& callback) { _mousePositionCallbacks.erase(std::remove(_mousePositionCallbacks.begin(), _mousePositionCallbacks.end(), callback), _mousePositionCallbacks.end()); }

  void registerCursorEnterCallback(Function<void, bool>& callback) { _cursorEnterCallbacks.push_back(callback); }
  void unregisterCursorEnterCallback(Function<void, bool>& callback) { _cursorEnterCallbacks.erase(std::remove(_cursorEnterCallbacks.begin(), _cursorEnterCallbacks.end(), callback), _cursorEnterCallbacks.end()); }

  void registerDropCallback(Function<void, std::vector<std::string>>& callback) { _dropCallbacks.push_back(callback); }
  void unregisterDropCallback(Function<void, std::vector<std::string>>& callback) { _dropCallbacks.erase(std::remove(_dropCallbacks.begin(), _dropCallbacks.end(), callback), _dropCallbacks.end()); }

  void registerWindowCloseCallback(Function<void> callback) { _windowCloseCallbacks.push_back(callback); }
  void unregisterWindowCloseCallback(Function<void> callback) { _windowCloseCallbacks.erase(std::remove(_windowCloseCallbacks.begin(), _windowCloseCallbacks.end(), callback), _windowCloseCallbacks.end()); }

  void registerWindowFocusCallback(Function<void, bool>& callback) { _windowFocusCallbacks.push_back(callback); }
  void unregisterWindowFocusCallback(Function<void, bool>& callback) { _windowFocusCallbacks.erase(std::remove(_windowFocusCallbacks.begin(), _windowFocusCallbacks.end(), callback), _windowFocusCallbacks.end()); }

  void registerWindowIconifyCallback(Function<void, bool>& callback) { _windowIconifyCallbacks.push_back(callback); }
  void unregisterWindowIconifyCallback(Function<void, bool>& callback) { _windowIconifyCallbacks.erase(std::remove(_windowIconifyCallbacks.begin(), _windowIconifyCallbacks.end(), callback), _windowIconifyCallbacks.end()); }

  void registerWindowPositionCallback(Function<void, const Vec2<int>&>& callback) { _windowPositionCallbacks.push_back(callback); }
  void unregisterWindowPositionCallback(Function<void, const Vec2<int>&>& callback) { _windowPositionCallbacks.erase(std::remove(_windowPositionCallbacks.begin(), _windowPositionCallbacks.end(), callback), _windowPositionCallbacks.end()); }

  void registerWindowSizeCallback(Function<void, const Vec2<int>&>& callback) { _windowSizeCallbacks.push_back(callback); }
  void unregisterWindowSizeCallback(Function<void, const Vec2<int>&>& callback) { _windowSizeCallbacks.erase(std::remove(_windowSizeCallbacks.begin(), _windowSizeCallbacks.end(), callback), _windowSizeCallbacks.end()); }

  void registerFramebufferSizeCallback(Function<void, const Vec2<int>&>& callback) { _framebufferSizeCallbacks.push_back(callback); }
  void unregisterFramebufferSizeCallback(Function<void, const Vec2<int>&>& callback) { _framebufferSizeCallbacks.erase(std::remove(_framebufferSizeCallbacks.begin(), _framebufferSizeCallbacks.end(), callback), _framebufferSizeCallbacks.end()); }

  void registerWindowRefreshCallback(Function<void>& callback) { _windowRefreshCallbacks.push_back(callback); }
  void unregisterWindowRefreshCallback(Function<void>& callback) { _windowRefreshCallbacks.erase(std::remove(_windowRefreshCallbacks.begin(), _windowRefreshCallbacks.end(), callback), _windowRefreshCallbacks.end()); }

  void registerWindowMaximizeCallback(Function<void, bool>& callback) { _windowMaximizeCallbacks.push_back(callback); }
  void unregisterWindowMaximizeCallback(Function<void, bool>& callback) { _windowMaximizeCallbacks.erase(std::remove(_windowMaximizeCallbacks.begin(), _windowMaximizeCallbacks.end(), callback), _windowMaximizeCallbacks.end()); }

  void registerWindowContentScaleCallback(Function<void, const Vec2<decimal_t>&>& callback) { _windowContentScaleCallbacks.push_back(callback); }
  void unregisterWindowContentScaleCallback(Function<void, const Vec2<decimal_t>&>& callback) { _windowContentScaleCallbacks.erase(std::remove(_windowContentScaleCallbacks.begin(), _windowContentScaleCallbacks.end(), callback), _windowContentScaleCallbacks.end()); }
#pragma endregion CallbackRegistration

private:
  void checkTitle(const std::string& title);
  void checkSize(const Vec2<int>& size);
  Vec2<int> getClosestResolution(const Vec2<int>& size);

#pragma region GLFW event handlers
private:
  /**
   * @brief handles a glfw char event.
   * @param window - The window that received the event.
   * @param codepoint - The Unicode code point of the character. See glfwGetKeyName for details.
   */
  static void handleCharEvent(GLFWwindow* window, unsigned int codepoint);
  
  /**
   * @brief handles a glfw char mods event.
   * @param window - The window that received the event.
   * @param codepoint - The Unicode code point of the character. See glfwGetKeyName for details.
   * @param mods - Bit field describing which modifier keys were held down.
   */
  static void handleCharModsEvent(GLFWwindow* window, unsigned int codepoint, int mods);
  
  /**
   * @brief handles a glfw key event.
   * @param window - The window that received the event.
   * @param key - The keyboard key that was pressed or released.
   * @param scancode - The system-specific scancode of the key.
   * @param action - The key action. One of GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT.
   * @param mods - Bit field describing which modifier keys were held down.
   */
  static void handleKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
  
  /**
   * @brief handles a glfw mouse button event.
   * @param window - The window that received the event.
   * @param button - The mouse button that was pressed or released.
   * @param action - The mouse button action. One of GLFW_PRESS or GLFW_RELEASE.
   * @param mods - Bit field describing which modifier keys were held down.
   */
  static void handleMouseButtonEvent(GLFWwindow* window, int button, int action, int mods);
  
  /**
   * @brief handles a glfw mouse scroll event.
   * @param window - The window that received the event.
   * @param xoffset - The scroll offset along the x-axis.
   * @param yoffset - The scroll offset along the y-axis.
   */
  static void handleMouseScrollEvent(GLFWwindow* window, double xoffset, double yoffset);
  
  /**
   * @brief handles a glfw mouse position event.
   * @param window - The window that received the event.
   * @param xpos - The new x-coordinate, in screen coordinates, of the cursor.
   * @param ypos - The new y-coordinate, in screen coordinates, of the cursor.
   */
  static void handleMousePositionEvent(GLFWwindow* window, double xpos, double ypos);
  
  /**
   * @brief handles a glfw cursor enter event.
   * @param window - The window that received the event.
   * @param entered - The cursor enter/leave state. One of GLFW_TRUE or GLFW_FALSE.
   */
  static void handleCursorEnterEvent(GLFWwindow* window, int entered);
  
  /**
   * @brief handles a glfw drop event.
   * @param window - The window that received the event.
   * @param count - The number of dropped files.
   * @param paths - The UTF-8 encoded file and/or directory path names.
   */
  static void handleDropEvent(GLFWwindow* window, int count, const char** paths);
  
  /**
   * @brief handles a glfw window close event.
   * @param window - The window that received the event.
   */
  static void handleWindowCloseEvent(GLFWwindow* window);
  
  /**
   * @brief handles a glfw window focus event.
   * @param window - The window that received the event.
   * @param focused - The window focus state. One of GLFW_TRUE or GLFW_FALSE.
   */
  static void handleWindowFocusEvent(GLFWwindow* window, int focused);
  
  /**
   * @brief handles a glfw window iconify event.
   * @param window - The window that received the event.
   * @param iconified - The window iconification state. One of GLFW_TRUE or GLFW_FALSE. See glfwIconifyWindow for details.
   */
  static void handleWindowIconifyEvent(GLFWwindow* window, int iconified);
  
  /**
   * @brief handles a glfw window position event.
   * @param window - The window that received the event.
   * @param xpos - The new x-coordinate, in screen coordinates, of the upper-left corner of the client area of the window.
   * @param ypos - The new y-coordinate, in screen coordinates, of the upper-left corner of the client area of the window.
   */
  static void handleWindowPositionEvent(GLFWwindow* window, int xpos, int ypos);
  
  /**
   * @brief handles a glfw window size event.
   * @param window - The window that received the event.
   * @param width - The new width, in screen coordinates, of the window.
   * @param height - The new height, in screen coordinates, of the window.
   */
  static void handleWindowSizeEvent(GLFWwindow* window, int width, int height);
  
  /**
   * @brief handles a glfw framebuffer size event.
   * @param window - The window that received the event.
   * @param width - The new width, in screen coordinates, of the window.
   * @param height - The new height, in screen coordinates, of the window.
   */
  static void handleFramebufferSizeEvent(GLFWwindow* window, int width, int height);

  /**
   * @brief handles a glfw window refresh event.
   * @param window - The window that received the event.
   */
  static void handleWindowRefreshEvent(GLFWwindow* window);

  /**
   * @brief handles a glfw window maximized event.
   * @param window - The window that received the event.
   * @param maximized - The window maximized state. One of GLFW_TRUE or GLFW_FALSE.
   */
  static void handleWindowMaximizeEvent(GLFWwindow* window, int maximized);

  /**
   * @brief handles a glfw window content scale event.
   * @param window - The window that received the event.
   * @param xscale - The new x-axis content scale of the window.
   * @param yscale - The new y-axis content scale of the window.
   */
  static void handleWindowContentScaleEvent(GLFWwindow* window, float xscale, float yscale);

#pragma endregion GLFW event handlers
  
  friend class Display;
};

} // ams
