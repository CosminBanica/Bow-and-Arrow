#include "Balloon.h"

#include <Core/Engine.h>

using namespace std;

Balloon::Balloon(glm::vec3 center, float radius, Color type)
{
	x = center.x;
	y = center.y;
	this->radius = radius;
	color = type;
}

Balloon::~Balloon()
{
}

float Balloon::GetX()
{
	return x;
}

float Balloon::GetY()
{
	return y;
}

float Balloon::GetRadius()
{
	return radius;
}

Color Balloon::GetColor()
{
	return color;
}

bool Balloon::GetBroken()
{
	return broken;
}

float Balloon::GetScalingX()
{
	return breakScalingX;
}

float Balloon::GetScalingY()
{
	return breakScalingY;
}

void Balloon::Break()
{
	broken = true;
}

void Balloon::LiftBalloon(float update)
{
	y += update;
	snaking += 0.05;
	x += 4 * cos(snaking);
}

void Balloon::ChangeScalingX(float update)
{
	breakScalingX += update;
}

void Balloon::ChangeScalingY(float update)
{
	breakScalingY += update;
}