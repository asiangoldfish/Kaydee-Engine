#include "Timestep.h"

#include <GLFW/glfw3.h>

float
Kaydee::Timestep::getElapsedTimeInSeconds() const
{
    return (float)glfwGetTime();
}

float
Kaydee::Timestep::getElapsedTimeInMilliseconds() const
{
    return glfwGetTime() * 1000.f;
}
