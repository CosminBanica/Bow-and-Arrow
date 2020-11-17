#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>


class Arrow
{
public:
	Arrow();
	Arrow(glm::vec3 begin, float length);
	~Arrow();

	glm::vec3 GetTip();
	glm::vec3 GetEnd();
	void MoveArrow(float deltaX, float DeltaY);
	void PlaceArrow(glm::vec3 position);

private:
	glm::vec3 tip;
	glm::vec3 end;

protected:

};