#include "Arrow.h"

#include <Core/Engine.h>

using namespace std;

Arrow::Arrow()
{
}

Arrow::Arrow(glm::vec3 begin, float length)
{
	end = begin;
	tip = begin + glm::vec3(length, 0, 0);
}

Arrow::~Arrow()
{
}

glm::vec3 Arrow::GetTip()
{
	return tip;
}

glm::vec3 Arrow::GetEnd()
{
	return end;
}

void Arrow::MoveArrow(float deltaX, float deltaY)
{
	end = end + glm::vec3(deltaX, deltaY, 0);
	tip = tip + glm::vec3(deltaX, deltaY, 0);
}

void Arrow::PlaceArrow(glm::vec3 position)
{
	glm::vec3 aux = end;
	end = position;
	tip = end + (tip - aux);
}
