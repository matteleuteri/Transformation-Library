#include "headers/GameObject.h"

GameObject::GameObject(AnimationController *animationController, Transform transform, float xSpeed): animationController(animationController), x(x), y(y), xSpeed(xSpeed)
{
    animation = animationController->animationMap["EXAMPLE1"];
    D2D1_SIZE_F size = animation->bitmaps[0]->GetSize();
    std::array<std::array<float>> = { { 1.0f, 1.0f, 1.0f } };
}

