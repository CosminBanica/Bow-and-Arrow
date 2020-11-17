#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Objects2D
{

	// Create square with given bottom left corner, length and color
	Mesh* CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, bool fill = false, bool colorFlag = false, glm::vec3 color = glm::vec3(0, 0, 0));
	Mesh* CreateOval(std::string name, glm::vec3 center, float radius, glm::vec3 color, float ratio, bool fill = false);
	Mesh* CreatePLine(std::string name, glm::vec3 start, int lines, float lineLength, glm::vec3 color);
	Mesh* CreateBow(std::string name, glm::vec3 start, float radius, glm::vec3 color);
	Mesh* CreateShaft(std::string name, glm::vec3 start, float length, glm::vec3 color);
	Mesh* CreateArrowHead(std::string name, glm::vec3 start, float size, glm::vec3 color);
	Mesh* CreateShuriken(std::string name, glm::vec3 center, float size, glm::vec3 color);
	Mesh* CreateHeart(std::string name, glm::vec3 center, float size, glm::vec3 color);
}

