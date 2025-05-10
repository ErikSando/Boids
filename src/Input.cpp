#include "Input.h"

InputHandler::InputHandler(GLFWwindow* window) {
    glfwSetKeyCallback(window, KeyCallback);
}

InputHandler::~InputHandler() {

}

void InputHandler::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

}