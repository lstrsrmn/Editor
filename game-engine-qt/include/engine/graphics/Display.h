#ifndef GAME_ENGINE_DISPLAY_H
#define GAME_ENGINE_DISPLAY_H

#include <string>
#include <glm/glm.hpp>
#include <QtOpenGL>
#include <cstdio>

class Display {
public:
    Display(int, int, const std::string&);

    void clear(float, float, float, float);
    void update();
    bool closed() const;
    float getAR() const;

    virtual ~Display();

private:
    Display(const Display& other) = default;
    QWindow* window;
    QGLContext* glContext;
    bool _closed;
    unsigned int _width;
    unsigned int _height;
};


#endif //GAME_ENGINE_DISPLAY_H
