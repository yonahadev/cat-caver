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

class Window {
private:
    void setupWindow(const int width, const int height, const char *name);
public:
    GLFWwindow* ptr;
    Window(const int width, const int height, const char *name);
};

#endif /* window_hpp */
