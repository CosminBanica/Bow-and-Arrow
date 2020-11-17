#include "Objects2D.h"
#include "Balloon.h"

#include <Core/Engine.h>

Mesh* Objects2D::CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, bool fill, bool colorFlag, glm::vec3 color)
{
	glm::vec3 corner = leftBottomCorner;
	std::vector<VertexFormat> vertices;

	if (colorFlag) {
		vertices =
		{
			VertexFormat(corner, color),
			VertexFormat(corner + glm::vec3(length, 0, 0), color),
			VertexFormat(corner + glm::vec3(length, length, 0), color),
			VertexFormat(corner + glm::vec3(0, length, 0), color)
		};
	} else {
		vertices =
		{
			VertexFormat(corner, glm::vec3(1, 1, 0)),
			VertexFormat(corner + glm::vec3(length, 0, 0), glm::vec3(1, 0, 0)),
			VertexFormat(corner + glm::vec3(length, length, 0), glm::vec3(1, 0, 0)),
			VertexFormat(corner + glm::vec3(0, length, 0), glm::vec3(1, 1, 0))
		};
	}

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };

	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}

Mesh* Objects2D::CreateOval(std::string name, glm::vec3 center, float radius, glm::vec3 color, float ratio, bool fill) 
{
	const float PI = 3.1415926f;
	std::vector<VertexFormat> vertices;
	float increment = 2.0f * PI / 100;
	unsigned short indice = 0;
	std::vector<unsigned short> indices;

	Mesh* balloon = new Mesh(name);

	if (!fill) {
		balloon->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		indices.push_back(indice++);
		vertices.push_back(VertexFormat(center, glm::vec3(1, 1, 1)));
		balloon->SetDrawMode(GL_TRIANGLE_FAN);
	}
	
	for (float currAngle = 0.0f; currAngle <= 2.0f * PI + increment; currAngle += increment)
	{
		vertices.push_back(VertexFormat(center + glm::vec3(radius * cos(currAngle) / ratio, radius * sin(currAngle), 0), color));
		indices.push_back(indice++);
	}

	balloon->InitFromData(vertices, indices);
	return balloon;
}

Mesh* Objects2D::CreatePLine(std::string name, glm::vec3 start, int lines, float lineLength, glm::vec3 color)
{
	std::vector<VertexFormat> vertices;
	std::vector<unsigned short> indices;
	unsigned short indice = 0;

	Mesh* pLine = new Mesh(name);

	int oscil = 1;
	float xPos = 0, yPos = 0;

	vertices.push_back(VertexFormat(start + glm::vec3(xPos, yPos, 0), color));
	indices.push_back(indice++);

	xPos -= lineLength * oscil / 2;
	yPos -= lineLength / 2;
	oscil *= -1;
	vertices.push_back(VertexFormat(start + glm::vec3(xPos, yPos, 0), color));
	indices.push_back(indice++);
	xPos -= lineLength * oscil;
	yPos -= lineLength;
	oscil *= -1;

	for (int i = 0; i < lines - 1; ++i) {
		vertices.push_back(VertexFormat(start + glm::vec3(xPos, yPos, 0), color));
		indices.push_back(indice++);
		xPos -= lineLength * oscil;
		yPos -= lineLength;
		oscil *= -1;
	}

	pLine->SetDrawMode(GL_LINE_STRIP);
	pLine->InitFromData(vertices, indices);
	return pLine;
}

Mesh* Objects2D::CreateBow(std::string name, glm::vec3 start, float radius, glm::vec3 color)
{
	const float PI = 3.1415926f;
	std::vector<VertexFormat> vertices;
	std::vector<unsigned short> indices;
	unsigned short indice = 0;
	float increment = 2.0f * PI / 100;

	Mesh* bow = new Mesh(name);

	for (float currAngle = 1.5f * PI; currAngle <= 2.5f * PI + increment; currAngle += increment)
	{
		vertices.push_back(VertexFormat(start + glm::vec3(radius * cos(currAngle) / 1.5, radius * sin(currAngle), 0), color));
		indices.push_back(indice++);
	}

	//float startX = vertices[vertices.size() - 1].position.x;
	//float startY = vertices[vertices.size() - 1].position.y;

	indices.push_back(0);
	bow->SetDrawMode(GL_LINE_LOOP);
	bow->InitFromData(vertices, indices);
	return bow;
}

Mesh* Objects2D::CreateShaft(std::string name, glm::vec3 start, float length, glm::vec3 color) 
{
	std::vector<VertexFormat> vertices;
	std::vector<unsigned short> indices;

	Mesh* shaft = new Mesh(name);

	vertices.push_back(VertexFormat(start, color));
	indices.push_back(0);
	vertices.push_back(VertexFormat(start + glm::vec3(length, 0, 0), color));
	indices.push_back(1);

	shaft->SetDrawMode(GL_LINE_STRIP);
	shaft->InitFromData(vertices, indices);
	return shaft;
}

Mesh* Objects2D::CreateArrowHead(std::string name, glm::vec3 start, float size, glm::vec3 color)
{
	std::vector<VertexFormat> vertices;
	std::vector<unsigned short> indices;

	Mesh* head = new Mesh(name);

	vertices.push_back(VertexFormat(start + glm::vec3(size, 0, 0), color));
	indices.push_back(0);
	vertices.push_back(VertexFormat(start + glm::vec3(0, size / 2, 0), color));
	indices.push_back(1);
	vertices.push_back(VertexFormat(start + glm::vec3(0, -size / 2, 0), color));
	indices.push_back(2);

	head->SetDrawMode(GL_TRIANGLES);
	head->InitFromData(vertices, indices);
	return head;
}

Mesh* Objects2D::CreateShuriken(std::string name, glm::vec3 center, float size, glm::vec3 color)
{
	std::vector<VertexFormat> vertices;
	std::vector<unsigned short> indices;

	Mesh* shuriken = new Mesh(name);

	vertices.push_back(VertexFormat(center, color));
	indices.push_back(0);
	vertices.push_back(VertexFormat(center + glm::vec3(size, 0, 0), color));
	indices.push_back(1);
	vertices.push_back(VertexFormat(center + glm::vec3(size, size * 1.2, 0), color));
	indices.push_back(2);

	vertices.push_back(VertexFormat(center, color));
	indices.push_back(3);
	vertices.push_back(VertexFormat(center + glm::vec3(0, size, 0), color));
	indices.push_back(4);
	vertices.push_back(VertexFormat(center + glm::vec3(-size * 1.2, size, 0), color));
	indices.push_back(5);

	vertices.push_back(VertexFormat(center, color));
	indices.push_back(6);
	vertices.push_back(VertexFormat(center + glm::vec3(-size, 0, 0), color));
	indices.push_back(7);
	vertices.push_back(VertexFormat(center + glm::vec3(-size, -size * 1.2, 0), color));
	indices.push_back(8);

	vertices.push_back(VertexFormat(center, color));
	indices.push_back(9);
	vertices.push_back(VertexFormat(center + glm::vec3(0, -size, 0), color));
	indices.push_back(10);
	vertices.push_back(VertexFormat(center + glm::vec3(size * 1.2, -size, 0), color));
	indices.push_back(11);

	shuriken->SetDrawMode(GL_TRIANGLES);
	shuriken->InitFromData(vertices, indices);
	return shuriken;
}

Mesh* Objects2D::CreateHeart(std::string name, glm::vec3 center, float size, glm::vec3 color)
{
	std::vector<VertexFormat> vertices;
	std::vector<unsigned short> indices;

	Mesh* heart = new Mesh(name);

	vertices.push_back(VertexFormat(center + glm::vec3(-size, 0, 0), color));
	indices.push_back(0);
	vertices.push_back(VertexFormat(center + glm::vec3(0, -size, 0), color));
	indices.push_back(1);
	vertices.push_back(VertexFormat(center + glm::vec3(size, 0, 0), color));
	indices.push_back(2);

	const float PI = 3.1415926f;
	unsigned short indice = 3;
	float increment = 2.0f * PI / 100;

	glm::vec3 start1 = center + glm::vec3(-size / 2 + 2.5, 0, 0);
	glm::vec3 start2 = center + glm::vec3(size / 2 - 2.5, 0, 0);

	for (float currAngle = 0.0f; currAngle <= 1.0f * PI; currAngle += increment)
	{
		vertices.push_back(VertexFormat(start1, color));
		indices.push_back(indice++);
		vertices.push_back(VertexFormat(start1 + glm::vec3((size / 2 + 2.5) * cos(currAngle), (size / 2) * sin(currAngle) * 1.3, 0), color));
		indices.push_back(indice++);
		vertices.push_back(VertexFormat(start1 + glm::vec3((size / 2 + 2.5) * cos(currAngle + increment), (size / 2) * sin(currAngle + increment) * 1.3, 0), color));
		indices.push_back(indice++);
	}

	for (float currAngle = 0.0f; currAngle <= 1.0f * PI; currAngle += increment)
	{
		vertices.push_back(VertexFormat(start2, color));
		indices.push_back(indice++);
		vertices.push_back(VertexFormat(start2 + glm::vec3((size / 2 + 2.5) * cos(currAngle), (size / 2) * sin(currAngle) * 1.3, 0), color));
		indices.push_back(indice++);
		vertices.push_back(VertexFormat(start2 + glm::vec3((size / 2 + 2.5) * cos(currAngle + increment), (size / 2) * sin(currAngle + increment) * 1.3, 0), color));
		indices.push_back(indice++);
	}

	heart->SetDrawMode(GL_TRIANGLES);
	heart->InitFromData(vertices, indices);
	return heart;
}
