#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>
#include <Sources\Tema1\Arrow.h>


class Shuriken
{
public:
	Shuriken(glm::vec3 center);
	~Shuriken();

	glm::vec3 GetCenter();
	float GetX();
	float GetY();
	float GetAngle();
	bool IsStopped();
	bool HitBow();
	void Move(float deltaX, float deltaY);
	void Rotate(float delta);
	void Stop();
	void Hit();

private:
	glm::vec3 center;
	float angle = 0;
	bool stopped = false;
	bool hitBow = false;

protected:

};