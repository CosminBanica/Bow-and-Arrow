#include "Shuriken.h"

#include <Core/Engine.h>

using namespace std;

Shuriken::Shuriken(glm::vec3 center)
{
	this->center = center;
}

Shuriken::~Shuriken()
{
}

glm::vec3 Shuriken::GetCenter()
{
	return center;
}

float Shuriken::GetX()
{
	return center.x;
}

float Shuriken::GetY()
{
	return center.y;
}

float Shuriken::GetAngle()
{
	return angle;
}

bool Shuriken::IsStopped()
{
	return stopped;
}

void Shuriken::Rotate(float delta)
{
	angle += delta;
}

bool Shuriken::HitBow()
{
	return hitBow;
}

void Shuriken::Hit()
{
	hitBow = true;
}

void Shuriken::Stop()
{
	stopped = true;
}

void Shuriken::Move(float deltaX, float deltaY)
{
	center = center + glm::vec3(deltaX, deltaY, 0);
}
