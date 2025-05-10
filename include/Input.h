#pragma once

#include "GLFW/glfw3.h"

class InputHandler {
    public:

    InputHandler(GLFWwindow* window);
    ~InputHandler();

    bool GetKey(int key);
    bool GetKeyDown(int key);

    bool GetScancode(int scancode);
    bool GetScancodeDown(int scancode);

    private:

    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};