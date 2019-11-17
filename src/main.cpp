#include <SDL2/SDL.h>
#include <iostream>
#include <glad/glad.h>

const uint32_t WIDTH = 1024;
const uint32_t HEIGHT = 768;

using namespace std;

int main() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) != 0) {
        std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
        exit(1);
    }
    int numberOfJoysticks = SDL_NumJoysticks();
    if (numberOfJoysticks < 0) {
        std::cout << "Error getting number of joysticks: " << SDL_GetError() << std::endl;
        exit(1);
    }
    std::cout << std::dec << numberOfJoysticks << " joysticks found" << std::endl;
    std::string controllerName = "Sony Interactive Entertainment Controller";
    SDL_Joystick *joystick = nullptr;
    for(int i = 0; i < numberOfJoysticks; i++) {
        SDL_Joystick *currentJoystick = SDL_JoystickOpen(i);
        std::string joystickName = SDL_JoystickName(currentJoystick);
        if (joystickName.compare(controllerName) == 0) {
            joystick = currentJoystick;
            break;
        }
    }
    if (joystick == nullptr) {
        cout << "Failed to find target controller." << endl;
        exit(1);
    }
    int numberOfButtons = SDL_JoystickNumButtons(joystick);
    std::cout << std::dec << numberOfButtons << " buttons in joystick" << std::endl;
    if (numberOfButtons < 0) {
        std::cout << "Error getting number of buttons: " << SDL_GetError() << std::endl;
        exit(1);
    }
    int numberOfAxes = SDL_JoystickNumAxes(joystick);
    std::cout << std::dec << numberOfAxes << " axes in joystick" << std::endl;
    if (numberOfAxes < 0) {
        std::cout << "Error getting number of axes: " << SDL_GetError() << std::endl;
        exit(1);
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
    SDL_Window *window = SDL_CreateWindow("main", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    (void)glContext;
    if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress)) {
        cout << "Failed to initialize the OpenGL context." << endl;
        exit(1);
    }
    cout << "OpenGL " << GLVersion.major << "." << GLVersion.minor << endl;
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    bool quit = false;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
        if (SDL_JoystickGetButton(joystick, 0) != 0) {
            std::cout << "Triangle pressed" << std::endl; // TRIANGLE
        }
        if (SDL_JoystickGetButton(joystick, 1) != 0) {
            std::cout << "Circle pressed" << std::endl; // CIRCLE
        }
        if (SDL_JoystickGetButton(joystick, 2) != 0) {
            std::cout << "X pressed" << std::endl; // X
        }
        if (SDL_JoystickGetButton(joystick, 3) != 0) {
            std::cout << "Square pressed" << std::endl; // SQUARE
        }
        if (SDL_JoystickGetButton(joystick, 4) != 0) {
            std::cout << "L2 pressed" << std::endl; // L2
        }
        if (SDL_JoystickGetButton(joystick, 5) != 0) {
            std::cout << "R2 pressed" << std::endl; // R2
        }
        if (SDL_JoystickGetButton(joystick, 6) != 0) {
            std::cout << "L1 pressed" << std::endl; // L1
        }
        if (SDL_JoystickGetButton(joystick, 7) != 0) {
            std::cout << "R1 pressed" << std::endl; // R1
        }
        if (SDL_JoystickGetButton(joystick, 8) != 0) {
            std::cout << "Select pressed" << std::endl; // SELECT
        }
        if (SDL_JoystickGetButton(joystick, 9) != 0) {
            std::cout << "Start pressed" << std::endl; // START
        }
        Sint16 X = SDL_JoystickGetAxis(joystick, 0); //  LEFT OR RIGHT
        if (X != 0) {
            if (X == std::numeric_limits<int16_t>::max()) {
                std::cout << "Right pressed" << std::endl;
            } else {
                std::cout << "Left pressed" << std::endl;
            }
        }
        Sint16 Y = SDL_JoystickGetAxis(joystick, 1); // UP OR DOWN
        if (Y != 0) {
            if (Y == std::numeric_limits<int16_t>::max()) {
                std::cout << "Down pressed" << std::endl;
            } else {
                std::cout << "Up pressed" << std::endl;
            }
        }
        glClear(GL_COLOR_BUFFER_BIT);
        SDL_GL_SwapWindow(window);
    }
    SDL_Quit();
    return 0;
}
