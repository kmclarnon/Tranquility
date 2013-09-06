#include "FPSCamera.h"

FPSCamera::FPSCamera()
    : frameTime(0.0), forwardSpeed(0.0), backwardSpeed(0.0), leftSpeed(0.0), 
    rightSpeed(0.0), forwardStepSpeed(0.003), backwardStepSpeed(0.001), 
    maxSpeed(0.01)
{

}

void FPSCamera::update()
{
    // update our position based on our speed
    this->move((float)this->rightSpeed - (float)this->leftSpeed, 0.0f, (float)this->forwardSpeed - (float)this->backwardSpeed);

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

void FPSCamera::moveEx(double time, bool keyDown, double &speed)
{
    if(keyDown)
    {
        speed += time * this->forwardStepSpeed;
        if(speed > (time * this->maxSpeed))
            speed = time * this->maxSpeed;
    }
    else
    {
        speed -= time * this->backwardStepSpeed;
        if(speed < 0.0)
            speed = 0.0;
    }
}