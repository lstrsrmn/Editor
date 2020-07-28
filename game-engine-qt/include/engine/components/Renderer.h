//
// Created by lstrsrmn on 08/05/2020.
//

#ifndef GAME_ENGINE_RENDERER_H
#define GAME_ENGINE_RENDERER_H

#include "Component.h"

class Camera;
class DirectionalLight;

class Renderer : public Component {
public:
    virtual void render(const Camera&, DirectionalLight*) = 0;
    void setGameObject(GameObject *gameObject) override;
    virtual ~Renderer() override;
private:
};


#endif //GAME_ENGINE_RENDERER_H
