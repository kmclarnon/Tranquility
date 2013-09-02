#ifndef _TRILLEK_FPS_CAMERA_H_
#define _TRILLEK_FPS_CAMERA_H_

#include "Common.h"
#include "Camera.h"

class FPSCamera : public Camera
{
public:
    FPSCamera();

    virtual void update();
    void moveForward(double time, bool keyDown);
    void moveBackward(double time, bool keyDown);
    void moveLeft(double time,bool keyDown);
    void moveRight(double time,bool keyDown);

private:
    void moveEx(double time, bool keyDown, double &speed);

    double frameTime;
    double forwardStepSpeed, backwardStepSpeed, maxSpeed;

    double forwardSpeed, backwardSpeed;
    double leftSpeed, rightSpeed;
};

#endif