#include "../../include/engine/graphics/Display.h"

Display::Display(int width, int height, const std::string &title) {

    _width = width;
    _height = height;

#ifdef GAME_STAND_ALONE
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

//    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,
//                                  SDL_WINDOW_OPENGL);
//    glContext = SDL_GL_CreateContext(window);

//    GLenum status = glewInit();
//    if (status != GLEW_OK) {
//        printf("Glew didn't initialise: %d\n", status);
//    }
#endif
    _closed = false;

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
}

Display::~Display() {
#ifdef GAME_STAND_ALONE
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
#endif
}

void Display::update() {
#ifdef GAME_STAND_ALONE
//    SDL_GL_SwapWindow(window);
//
//    SDL_Event e;
//
//    while (SDL_PollEvent(&e)) {
//        if (e.type == SDL_QUIT) {
//            _closed = true;
//        }
//    }
#else

#endif
}

bool Display::closed() const {
    return _closed;
}

void Display::clear(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

float Display::getAR() const {
    return ((float)_width / (float)_height);
}
