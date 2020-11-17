#include "Tema1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transforms2D.h"
#include "Objects2D.h"
#include "Balloon.h"
#include "Arrow.h"
#include "Bow.h"
#include "Shuriken.h"

using namespace std;

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

void Tema1::DrawBalloon(int i) 
{
	if (Balloons[i].GetColor() == red) {
		RenderMesh2D(meshes["ovalRed"], shaders["VertexColor"], modelMatrix);
	}
	if (Balloons[i].GetColor() == yellow) {
		RenderMesh2D(meshes["ovalYellow"], shaders["VertexColor"], modelMatrix);
	}
	RenderMesh2D(meshes["pLineWhite"], shaders["VertexColor"], modelMatrix);
}

void Tema1::DrawPowerBar(std::string slider, std::string bar, std::string contur)
{
	modelMatrix = glm::mat3(1);
	modelMatrix = Transform2D::Translate(50, 45) * Transform2D::Scale(-scalingSlider, 1) *
				  Transform2D::Translate(-50, -45) * modelMatrix;
	modelMatrix = Transform2D::Translate(300, 0) * modelMatrix;
	RenderMesh2D(meshes[slider], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix = Transform2D::Translate(50, 45) * Transform2D::Scale(6, 1) *
				  Transform2D::Translate(-50, -45) * modelMatrix;
	RenderMesh2D(meshes[bar], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix = Transform2D::Translate(49, 45.5) * Transform2D::Scale(5.72, 1) *
				  Transform2D::Translate(-49, -45.5) * modelMatrix;
	RenderMesh2D(meshes[contur], shaders["VertexColor"], modelMatrix);
}

void Tema1::SpawnShuriken(float deltaTimeSeconds)
{
	if (shurikenTimer <= shurikenFrequency) {
		shurikenTimer += deltaTimeSeconds;
	}
	else {
		shurikenTimer = 0;
		glm::vec3 shurikenSpawn = glm::vec3(1400, 100 + (std::rand() % (650 - 100 + 1)), 0);
		Shurikens.push_back(Shuriken(shurikenSpawn));
	}
}

void Tema1::SpawnBalloons(float deltaTimeSeconds, char type)
{
	switch (type) {
		case 'r':
			if (redTimer <= redTimerReset) {
				redTimer += deltaTimeSeconds;
			}
			else {
				redTimer = 0;
				glm::vec3 balloonSpawn = glm::vec3(500 + (std::rand() % (1150 - 500 + 1)), -300, 0);
				Balloons.push_back(Balloon(balloonSpawn, 50, red));
			}
			break;
		case 'y':
			if (yellowTimer <= yellowTimerReset) {
				yellowTimer += deltaTimeSeconds;
			}
			else {
				yellowTimer = 0;
				glm::vec3 balloonSpawn = glm::vec3(500 + (std::rand() % (1150 - 500 + 1)), -300, 0);
				Balloons.push_back(Balloon(balloonSpawn, 50, yellow));
			}
			break;
	}
}

void Tema1::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	// red balloon
	glm::vec3 center = glm::vec3(0, 0, 0);
	Mesh* oval1 = Objects2D::CreateOval("ovalRed", center, balloonRadius, glm::vec3(1, 0, 0), 1.5, 1);
	AddMeshToList(oval1);

	// yellow balloon
	Mesh* oval2 = Objects2D::CreateOval("ovalYellow", center, balloonRadius, glm::vec3(1, 1, 0), 1.5, 1);
	AddMeshToList(oval2);
	
	// balloon string with custom number of string lines
	glm::vec3 lineStart = center + glm::vec3(0, -50, 0);
	Mesh* pLine1 = Objects2D::CreatePLine("pLineWhite", lineStart, strings, stringLength, glm::vec3(1, 1, 1));
	AddMeshToList(pLine1);

	// bow
	bow = Bow(glm::vec3(50, (float)resolution.y / 2, 0));
	Mesh* bowMesh = Objects2D::CreateBow("bow", glm::vec3(0, 0, 0), bowRadius, glm::vec3(1, 1, 1));
	AddMeshToList(bowMesh);

	// arrow shaft and head
	Mesh* shaft = Objects2D::CreateShaft("shaft", glm::vec3(0, 0, 0), shaftSize, glm::vec3(1, 1, 1));
	AddMeshToList(shaft);

	Mesh* head = Objects2D::CreateArrowHead("head", glm::vec3(shaftSize, 0, 0), headSize, glm::vec3(1, 1, 1));
	AddMeshToList(head);

	arrow = Arrow(bow.GetCenter(), shaftSize + headSize);

	// shuriken
	Mesh* shuriken = Objects2D::CreateShuriken("shuriken", glm::vec3(0, 0, 0), shurikenSize, glm::vec3(1, 1, 1));
	AddMeshToList(shuriken);

	// power bar meshes
	Mesh* powerBar = Objects2D::CreateSquare("powerBar", glm::vec3(50, 20, 0), 50, 1);
	AddMeshToList(powerBar);

	Mesh* powerBarContur = Objects2D::CreateSquare("powerBarContur", glm::vec3(49, 18, 0), 53, 0, 1, glm::vec3(1, 1, 1));
	AddMeshToList(powerBarContur);

	Mesh* powerBarSlider = Objects2D::CreateSquare("powerBarSlider", glm::vec3(50, 20, 0), 50, 1, 1);
	AddMeshToList(powerBarSlider);

	// green heart
	Mesh* life = Objects2D::CreateHeart("life", glm::vec3(0, 0, 0), 40, glm::vec3(0, 1, 0));
	AddMeshToList(life);
}

void Tema1::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds) 
{
	// update difficulty
	gameDifficulty += deltaTimeSeconds * 0.1;
	shurikenFrequency = 1.4 - ((gameDifficulty - 2.70) / 100) * 20;
	if (shurikenFrequency < maxShurikenFrequency) {
		shurikenFrequency = maxShurikenFrequency;
	}

	// render number of lives
	for (int i = 0; i < boiLives; ++i) {
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(1000 + 100 * i, 50);
		RenderMesh2D(meshes["life"], shaders["VertexColor"], modelMatrix);
	}

	// spawn new balloons
	SpawnBalloons(deltaTimeSeconds, 'r');
	SpawnBalloons(deltaTimeSeconds, 'y');
	
	// update ballon positions
	for (int i = 0; i < Balloons.size(); ++i) {
		// if balloon is out of screen, delete it from list
		if (Balloons[i].GetY() > window->GetResolution().y + balloonRadius + stringLength * strings) {
			Balloons.erase(Balloons.begin() + i);
		}
		else {
			if (!Balloons[i].GetBroken()) {		// if ballon is not broken, lift it
				Balloons[i].LiftBalloon(deltaTimeSeconds * 200 * log(gameDifficulty));

				modelMatrix = glm::mat3(1);
				modelMatrix *= Transform2D::Translate(Balloons[i].GetX(), Balloons[i].GetY());

				DrawBalloon(i);
			}
			else {		// if balloon is broken, animate it's deflation
				modelMatrix = glm::mat3(1);
				modelMatrix *= Transform2D::Translate(Balloons[i].GetX(), Balloons[i].GetY());
				modelMatrix = Transform2D::Translate(Balloons[i].GetX(), Balloons[i].GetY()) *
							  Transform2D::Scale(Balloons[i].GetScalingX(), Balloons[i].GetScalingY()) *
							  Transform2D::Translate(-Balloons[i].GetX(), -Balloons[i].GetY()) * modelMatrix;

				Balloons[i].ChangeScalingX(-0.7 * deltaTimeSeconds);
				Balloons[i].ChangeScalingY(-0.7 * deltaTimeSeconds);

				DrawBalloon(i);

				// when ballon is fully deflated, delete it from balloon list
				if (Balloons[i].GetScalingX() < 0 || Balloons[i].GetScalingY() < 0) {
					Balloons.erase(Balloons.begin() + i);
				}
			}
		}
	}

	// update bow position and rotate it according to mouse location
	modelMatrix = glm::mat3(1);
	modelMatrix = Transform2D::Translate(bow.GetCenter().x, bow.GetCenter().y) *
				  Transform2D::Rotate(mouseAngle) * modelMatrix;
	RenderMesh2D(meshes["bow"], shaders["VertexColor"], modelMatrix);

	// check for game over and update arrow position
	if (boiLives > 0) {
		if (shootArrow) {
			// if arrow has been shot, check if it's time to bring it back to bow
			if (arrow.GetEnd().x > window->GetResolution().x + 100 || arrowTimer > 5 ||
				arrow.GetEnd().y > window->GetResolution().y + 50 ||
				arrow.GetEnd().y < -50) {
				arrowTimer = 0;
				shootArrow = 0;
				arrowSpeed = minArrowSpeed;

				arrow.PlaceArrow(bow.GetCenter());

				modelMatrix = glm::mat3(1);
				modelMatrix *= Transform2D::Translate(arrow.GetEnd().x, arrow.GetEnd().y);

				modelMatrix = Transform2D::Translate(arrow.GetEnd().x, arrow.GetEnd().y) *
							  Transform2D::Rotate(mouseAngle) * Transform2D::Translate(-arrow.GetEnd().x, -arrow.GetEnd().y) *
							  modelMatrix;

				RenderMesh2D(meshes["shaft"], shaders["VertexColor"], modelMatrix);
				RenderMesh2D(meshes["head"], shaders["VertexColor"], modelMatrix);
			} else {	// if arrow is still in view, move it according to gravity
				arrowTimer += deltaTimeSeconds;
				shootAngle -= deltaTimeSeconds * gravity;
				arrow.MoveArrow(deltaTimeSeconds * arrowSpeed * cos(shootAngle), deltaTimeSeconds * arrowSpeed * sin(shootAngle));

				modelMatrix = glm::mat3(1);
				modelMatrix *= Transform2D::Translate(arrow.GetEnd().x, arrow.GetEnd().y);

				modelMatrix = Transform2D::Translate(arrow.GetEnd().x, arrow.GetEnd().y) * Transform2D::Rotate(shootAngle) *
					Transform2D::Translate(-arrow.GetEnd().x, -arrow.GetEnd().y) * modelMatrix;

				RenderMesh2D(meshes["shaft"], shaders["VertexColor"], modelMatrix);
				RenderMesh2D(meshes["head"], shaders["VertexColor"], modelMatrix);

				// arrow-balloon collision
				for (int i = 0; i < Balloons.size(); ++i) {
					float x = Balloons[i].GetX() - (arrow.GetEnd().x + (shaftSize + headSize) * cos(shootAngle));
					float y = Balloons[i].GetY() - (arrow.GetEnd().y + (shaftSize + headSize) * sin(shootAngle));
					if (x * x + y * y < Balloons[i].GetRadius() * Balloons[i].GetRadius() && !Balloons[i].GetBroken()) {
						if (Balloons[i].GetColor() == red) {
							score -= 10;
						}
						if (Balloons[i].GetColor() == yellow) {
							score += 20;
						}
						Balloons[i].Break();
						cout << "Score: " << score << endl;
					}
				}
			}
		}
		else {	// if arrow hasn't been shot, draw it centered on the bow
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(arrow.GetEnd().x, arrow.GetEnd().y);

			modelMatrix = Transform2D::Translate(arrow.GetEnd().x, arrow.GetEnd().y) * Transform2D::Rotate(mouseAngle) *
						  Transform2D::Translate(-arrow.GetEnd().x, -arrow.GetEnd().y) * modelMatrix;

			RenderMesh2D(meshes["shaft"], shaders["VertexColor"], modelMatrix);
			RenderMesh2D(meshes["head"], shaders["VertexColor"], modelMatrix);
		}
	} else {	// when you run out of lives you lose the ability to shoot the arrow
		if (boiLives == 0) {
			cout << "You lose!!" << endl;
			--boiLives;
			arrow.PlaceArrow(glm::vec3(-200, -200, 0));
		}
	}

	// spawn shuriken
	SpawnShuriken(deltaTimeSeconds);

	// update shuriken positions
	for (int i = 0; i < Shurikens.size(); ++i) {
		// if shuriken is out of screen, delete it from shuriken list
		if (Shurikens[i].GetX() < -shurikenSize || Shurikens[i].GetY() < -shurikenSize) {
			Shurikens.erase(Shurikens.begin() + i);
		} else {
			if (!Shurikens[i].IsStopped()) {	// if shuriken is not stopped by arrow, update its location
				Shurikens[i].Move(-deltaTimeSeconds * 500 * log(gameDifficulty), 0);
				Shurikens[i].Rotate(deltaTimeSeconds * 40);

				modelMatrix = glm::mat3(1);
				modelMatrix = Transform2D::Translate(Shurikens[i].GetX(), Shurikens[i].GetY()) *
							  Transform2D::Rotate(Shurikens[i].GetAngle()) * modelMatrix;
				RenderMesh2D(meshes["shuriken"], shaders["VertexColor"], modelMatrix);

				// arrow-shuriken collision
				float x = Shurikens[i].GetX() - (arrow.GetEnd().x + (shaftSize + headSize) * cos(shootAngle));
				float y = Shurikens[i].GetY() - (arrow.GetEnd().y + (shaftSize + headSize) * sin(shootAngle));
				if (x * x + y * y < shurikenSize * shurikenSize && shootArrow) {
					score += 50;
					Shurikens[i].Stop();
					cout << "Score: " << score << endl;
				}

				// bow-shuriken collision
				x = Shurikens[i].GetX() - bow.GetCenter().x;
				y = Shurikens[i].GetY() - bow.GetCenter().y;
				if (x * x + y * y < shurikenSize * shurikenSize + bowRadius * bowRadius * 2 && !Shurikens[i].HitBow() && boiLives > 0) {
					--boiLives;
					Shurikens[i].Hit();
					cout << "You have " << boiLives << " lifes left!!" << endl;
				}
			}
			else {	// if shuriken is stopped by arrow, make it fall
				Shurikens[i].Move(0, -deltaTimeSeconds * 500);

				modelMatrix = glm::mat3(1);
				modelMatrix *= Transform2D::Translate(Shurikens[i].GetX(), Shurikens[i].GetY());
				RenderMesh2D(meshes["shuriken"], shaders["VertexColor"], modelMatrix);
			}
		}
	}

	// draw the power bar
	DrawPowerBar("powerBarSlider", "powerBar", "powerBarContur");
}

void Tema1::FrameEnd()
{

}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
	// while left mouse button is being held down, increase arrow power
	if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT) && !shootArrow) {
		arrowSpeed += 0.6 * (maxArrowSpeed - minArrowSpeed) * deltaTime;
		if (arrowSpeed > maxArrowSpeed) {
			arrowSpeed = maxArrowSpeed;
		}

		if (boiLives > 0) {
			if(scalingSlider > 0) {
				scalingSlider -= 0.6 * maxSlider * deltaTime;
			}
			else {
				scalingSlider = 0;
			}
		}		
	}

	// use W and S to move bow and arrow
	if (window->KeyHold(GLFW_KEY_W) && bow.GetCenter().y < window->GetResolution().y - 100) {
		bow.MoveCenter(deltaTime * 300);
		if (!shootArrow) {
			arrow.MoveArrow(0, deltaTime * 300);
		}
	}

	if (window->KeyHold(GLFW_KEY_S) && bow.GetCenter().y > 150) {
		bow.MoveCenter(-deltaTime * 300);
		if (!shootArrow) {
			arrow.MoveArrow(0, -deltaTime * 300);
		}
	}
}

void Tema1::OnKeyPress(int key, int mods)
{
	// add key press event
}

void Tema1::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// update the angle to which to rotatea the bow and arrow, according to mouse position
	float x = mouseX - bow.GetCenter().x;
	float y = window->GetResolution().y - mouseY - bow.GetCenter().y;
	mouseAngle = atan(y / x);

	if (mouseX < bow.GetCenter().x) {
		const float PI = 3.1415926f;
		mouseAngle = mouseAngle - PI;
	}
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// when left click is released, unless the arrow is already flying, shoot it
	if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT) && !shootArrow) {
		shootArrow = true;
		shootAngle = mouseAngle;
		scalingSlider = maxSlider;
	}
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}