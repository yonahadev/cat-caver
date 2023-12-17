//
//  window.hpp
//  cat-caver
//
//  Created by tom on 2023/12/02.
//

#ifndef window_hpp
#define window_hpp

#include <stdio.h>
#include "glad.h"
#include "glfw3.h"
#include "vec2.hpp"

class Window {
private:
    void setupWindow(const Vec2i &screenSize, const char *name);
public:
    GLFWwindow* ptr;
    Window(const Vec2i &screenSize, const char *name);
};

#endif /* window_hpp */
