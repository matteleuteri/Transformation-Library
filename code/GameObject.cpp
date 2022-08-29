#include "headers/GameObject.h"

GameObject::GameObject(AnimationController *animationController, float x, float y, float xSpeed): animationController(animationController), x(x), y(y), xSpeed(xSpeed)
{
    animation = animationController->animationMap["EXAMPLE1"];
    // D2D1_SIZE_F size = animation->bitmaps[0]->GetSize();
    // width = size.width;
    // height = size.height;
    // ySpeed = 0;
}

