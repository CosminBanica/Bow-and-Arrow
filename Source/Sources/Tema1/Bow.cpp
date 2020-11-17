#include "Bow.h"

#include <Core/Engine.h>

using namespace std;

Bow::Bow()
{
}

Bow::Bow(glm::vec3 center)
{
	this->center = center;
}

Bow::~Bow()
{
}

glm::vec3 Bow::GetCenter()
{
	return center;
}

void Bow::MoveCenter(float delta)
{
	center = center + glm::vec3(0, delta, 0);
}

