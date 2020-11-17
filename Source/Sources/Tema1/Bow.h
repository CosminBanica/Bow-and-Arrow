#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>


class Bow
{
public:
	Bow();
	Bow(glm::vec3 center);
	~Bow();

	glm::vec3 GetCenter();
	void MoveCenter(float delta);

private:
	glm::vec3 center;

protected:

};