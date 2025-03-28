#pragma once

#include <glm/glm.hpp>
#include "Texture.h"

struct Transform
{
    Transform(glm::vec2 position, float rotation, float scale) {
        this->position = position;
        this->rotation = rotation;
        this->scale = scale;
    }

    glm::vec2 position;
    float rotation;
    float scale;
};

struct Sprite
{
    Sprite(const char* filepath, glm::vec3 color, bool autoSize = true, glm::vec2 size = glm::vec2(1, 1), const char* shaderName = "default", bool visible = true ) {
        this->filepath = filepath;
        this->color = color;
        this->autoSize = autoSize;
        this->size = size;
        this->shaderName = shaderName;
        this->visible = visible;
    }

    const char* filepath;
    glm::vec3 color;
    bool autoSize;
    glm::vec2 size = glm::vec2(1, 1);
    const char* shaderName;
    bool visible;
};

struct BoxCollider
{
    BoxCollider(float w, float h) {
        this->width = w;
        this->height = h;
    }

    float width = 0;
    float height = 0;
    bool collidedWith = false;
};

struct ScriptComponent
{
    ScriptComponent(int scriptId) {
        this->scriptId = scriptId;
    }

    int scriptId = -1;
};