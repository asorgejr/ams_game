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

#include <gtest/gtest.h>

#ifndef AMS_MODULES
#include <ams/spatial/Vec.hpp>
#include <ams/game/Window.hpp>
#else
import ams.spatial.Vec;
import ams.game.Window;
#endif

using namespace ams;

const WindowConfig TestCfgAllFalse {
  .title = "test",
  .size = { 800, 600 },
  .position = { 100, 100 },
  .fullscreen = false,
  .resizable = false,
  .maximized = false,
  .minimized = false,
};

TEST(Window, CreateWindow) {
  if (Display::getDisplays().empty()) {
    FAIL() << "Test requires at least one display.";
  }
  Display display(Display::getDisplays()[0]);
  Window window(display, TestCfgAllFalse);
  EXPECT_TRUE(window.getHandle() != nullptr);
  window.destroy();
}

TEST(Window, WindowOptionsValid) {
  if (Display::getDisplays().empty()) {
    FAIL() << "Test requires at least one display.";
  }
  Display display(Display::getDisplays()[0]);
  Window window(display, TestCfgAllFalse);
  EXPECT_EQ(window.getTitle(), TestCfgAllFalse.title);
  EXPECT_EQ(window.getSize(), TestCfgAllFalse.size);
  EXPECT_EQ(window.getPosition(), TestCfgAllFalse.position);
  EXPECT_EQ(window.getIsFullscreen(), TestCfgAllFalse.fullscreen);
  EXPECT_EQ(window.getIsResizable(), TestCfgAllFalse.resizable);
  EXPECT_EQ(window.getIsMaximized(), TestCfgAllFalse.maximized);
  EXPECT_EQ(window.getIsMinimized(), TestCfgAllFalse.minimized);
  window.destroy();
}

TEST(Window, WindowUpdateCycle) {
  if (Display::getDisplays().empty()) {
    FAIL() << "Test requires at least one display.";
  }
  Display display(Display::getDisplays()[0]);
  Window window(display, TestCfgAllFalse);
  int updateCount = 0;
  Function<void> callback = { [&updateCount]() { updateCount++; } };
  window.registerWindowRefreshCallback(callback);
  window.update();
  EXPECT_EQ(updateCount, 1);
  window.destroy();
}

TEST(Window, ConstructDestroyCreate) {
  Display display(Display::getDisplays()[0]);
  Window window(display, TestCfgAllFalse);
  EXPECT_NE(window.getHandle(), nullptr);
  window.destroy();
  EXPECT_EQ(window.getHandle(), nullptr);
  window.create();
  EXPECT_NE(window.getHandle(), nullptr);
  window.destroy();
}

TEST(Window, StartMinimized) {
  Display display(Display::getDisplays()[0]);
  WindowConfig cfg { .title="MinimizedWindow", .minimized = true };
  Window window(display, cfg);
  EXPECT_EQ(window.getIsMinimized(), cfg.minimized);
  window.destroy();
}

TEST(Window, StartMinimizedSwitchToWindowed) {
  Display display(Display::getDisplays()[0]);
  WindowConfig cfg { .title="MinimizedWindow", .minimized = true };
  Window window(display, cfg);
  EXPECT_EQ(window.getIsMinimized(), cfg.minimized);
  window.setIsMinimized(false);
  EXPECT_EQ(window.getIsMinimized(), false);
  window.destroy();
}

TEST(Window, StartMaximized) {
  Display display(Display::getDisplays()[0]);
  WindowConfig cfg { .title="MaximizedWindow", .maximized = true };
  Window window(display, cfg);
  EXPECT_EQ(window.getIsMaximized(), cfg.maximized);
  window.destroy();
}

TEST(Window, StartMaximizedSwitchToWindowed) {
  Display display(Display::getDisplays()[0]);
  WindowConfig cfg { .title="MaximizedWindow", .maximized = true };
  Window window(display, cfg);
  EXPECT_EQ(window.getIsMaximized(), cfg.maximized);
  window.setIsMaximized(false);
  EXPECT_EQ(window.getIsMaximized(), false);
  window.destroy();
}

TEST(Window, StartMinimizedSwitchToMaximized) {
  Display display(Display::getDisplays()[0]);
  WindowConfig cfg { .title="MinimizedWindow", .minimized = true };
  Window window(display, cfg);
  EXPECT_EQ(window.getIsMinimized(), cfg.minimized);
  window.setIsMaximized(true);
  EXPECT_EQ(window.getIsMaximized(), true);
  window.destroy();
}

TEST(Window, StartFullscreen) {
  Display display(Display::getDisplays()[0]);
  WindowConfig cfg { .title="FullscreenWindow", .fullscreen = true };
  Window window(display, cfg);
  EXPECT_EQ(window.getIsFullscreen(), cfg.fullscreen);
  window.destroy();
}

TEST(Window, StartFullscreenSwitchToWindowed) {
  Display display(Display::getDisplays()[0]);
  WindowConfig cfg { .title="FullscreenWindow", .fullscreen = true };
  Window window(display, cfg);
  EXPECT_EQ(window.getIsFullscreen(), cfg.fullscreen);
  window.setIsFullscreen(false);
  EXPECT_EQ(window.getIsFullscreen(), false);
  window.destroy();
}


// options order of precedence:
//   resizable > fullscreen > maximized > minimized > focused.

WindowConfig TestCfgImpossible {
  .title = "test",
  .size = { 801, 601 }, // should be set to closest supported size by display (most likely 800x600)
  .position = { 100, 100 }, // should be ignored
  .fullscreen = true,
  .resizable = true, // should be ignored
  .maximized = true, // should be set to false
  .minimized = true, // should be set to false
};

TEST(Window, WindowOptionsResolveImpossibleConfiguration) {
  if (Display::getDisplays().empty()) {
    FAIL() << "Test requires at least one display.";
  }
  Display display(Display::getDisplays()[0]);
  auto rezs = display.getSupportedResolutions();
  EXPECT_NE(rezs.size(), 0);
  auto nearest = ams::nearest(TestCfgImpossible.size, rezs);
  Window window(display, TestCfgImpossible);
  // give the system some time to process fullscreen window creation.
  std::this_thread::sleep_for(std::chrono::seconds(5));
  window.update(); // draw the window after fullscreen
  EXPECT_EQ(window.getTitle(), TestCfgImpossible.title);
  EXPECT_EQ(window.getSize(), nearest);
  EXPECT_EQ(window.getPosition(), Vec2<int>(0, 0));
  EXPECT_EQ(window.getIsFullscreen(), TestCfgImpossible.fullscreen);
  EXPECT_EQ(window.getIsResizable(), TestCfgImpossible.resizable);
  EXPECT_NE(window.getIsMaximized(), TestCfgImpossible.maximized); // fullscreen overrides maximized
  EXPECT_NE(window.getIsMinimized(), TestCfgImpossible.minimized); // fullscreen overrides minimized
  window.destroy();
}
