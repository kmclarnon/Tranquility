#include "FPSCamera.h"

FPSCamera::FPSCamera()
{

}

void FPSCamera::update()
{
    // update our position based on our speed
    this->move(this->rightSpeed - this->leftSpeed, 0.0f, this->forwardSpeed - this->backwardSpeed);

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