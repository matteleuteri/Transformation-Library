#ifndef _GAMEOBJECT
#define _GAMEOBJECT

#include <d2d1.h>
#include <stdint.h>
#include <vector>

class GameObject
{
public:
    float x;
    float y;
    float xSpeed;
    float ySpeed;
    float width;
    float height;
//    GameObject::GameObject(AnimationController *animationController, float x, float y, float xSpeed);
    // virtual void GameObject::update(int32_t timeElapsed) = 0;
    // void GameObject::animate(int32_t currentTime); 
};

#endif
