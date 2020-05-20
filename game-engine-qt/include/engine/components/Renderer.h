//
// Created by lstrsrmn on 08/05/2020.
//

#ifndef GAME_ENGINE_RENDERER_H
#define GAME_ENGINE_RENDERER_H

#include "Component.h"
#include "../graphics/Camera.h"
#include "../graphics/lighting/DirectionalLight.h"


class Renderer : public Component {
public:
    virtual void render(const Camera&, const DirectionalLight&) = 0;
    void setGameObject(GameObject *gameObject) override;
private:
};


#endif //GAME_ENGINE_RENDERER_H
