#include "FPSCamera.h"

FPSCamera::FPSCamera()
    : frameTime(0.0), forwardSpeed(0.0), backwardSpeed(0.0), leftSpeed(0.0), 
    rightSpeed(0.0), acelStepSpeed(0.003), decelStepSpeed(0.001), 
    maxSpeed(0.01), upSpeed(0.0), downSpeed(0.0)
{

}

void FPSCamera::update()
{
    // update our position based on our speed
    this->move((float)this->rightSpeed - (float)this->leftSpeed,
                (float)this->upSpeed - (float)this->downSpeed,
                (float)this->forwardSpeed - (float)this->backwardSpeed);

    this->Camera::update();
}

void FPSCamera::moveForward(double time, bool keyDown)
{
    this->moveEx(time, keyDown, this->forwardSpeed);
}

void FPSCamera::moveBackward(double time, bool keyDown)
{
    this->moveEx(time, keyDown, this->backwardSpeed);
}

void FPSCamera::moveLeft(double time, bool keyDown)
{
    this->moveEx(time, keyDown, this->leftSpeed);
}

void FPSCamera::moveRight(double time, bool keyDown)
{
    this->moveEx(time, keyDown, this->rightSpeed);
}

void FPSCamera::moveUp(double time, bool keyDown)
{
    this->moveEx(time, keyDown, this->upSpeed);
}

void FPSCamera::moveDown(double time, bool keyDown)
{
    this->moveEx(time, keyDown, this->downSpeed);
}

void FPSCamera::moveEx(double time, bool keyDown, double &speed)
{
    if(keyDown)
    {
        speed += time * this->acelStepSpeed;
        if(speed > (time * this->maxSpeed))
            speed = time * this->maxSpeed;
    }
    else
    {
        speed -= time * this->decelStepSpeed;
        if(speed < 0.0)
            speed = 0.0;
    }
}