#include "Light.h"

Light::Light() : Light(Color::Green) {};

Light::Light(Color color)
{
	cellColor = color;
	collideable = true;
}