#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

enum Color { red, yellow };

class Balloon
{
public:
	Balloon(glm::vec3 centre, float radius, Color type);
	~Balloon();

	float GetX();
	float GetY();
	float GetRadius();
	bool GetBroken();
	Color GetColor();
	float GetScalingX();
	float GetScalingY();
	void LiftBalloon(float update);
	void Break();
	void ChangeScalingX(float update);
	void ChangeScalingY(float update);


private:
	float radius;
	float x;
	float y;
	Color color;
	bool broken = false;
	float breakScalingX = 1, breakScalingY = 1;
	float snaking = 0;

protected:
	
};