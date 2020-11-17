#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>

#include "Balloon.h"
#include "Arrow.h"
#include "Bow.h"
#include "Shuriken.h"

class Tema1 : public SimpleScene
{
public:
	Tema1();
	~Tema1();

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;
	void DrawPowerBar(std::string slider, std::string bar, std::string contur);
	void SpawnShuriken(float deltaTimeSeconds);
	void SpawnBalloons(float deltaTimeSeconds, char type);
	void DrawBalloon(int i);

protected:
	glm::mat3 modelMatrix;
	float translateY = 0;
	float redTimer = 3;
	float redTimerReset = 1.3;
	float yellowTimer = 0;
	float yellowTimerReset = 1.0;
	std::vector<Balloon> Balloons;
	std::vector<Arrow> Arrows;
	Arrow arrow;
	float balloonRadius = 50;
	int strings = 4;
	float stringLength = 10;
	float bowRadius = 50;
	float shaftSize = 100;
	float headSize = 20;
	float shurikenSize = 20;
	float minArrowSpeed = 300;
	float arrowSpeed = 300;
	float maxArrowSpeed = 1300;
	bool shootArrow = false;
	glm::vec3 bowOrigin;
	Bow bow;
	float mouseAngle;
	float shootAngle;
	float arrowTimer = 0;
	int score = 0;
	float scalingSlider = 6;
	float maxSlider = 6;
	int boiLives = 3;
	std::vector<Shuriken> Shurikens;
	float shurikenTimer = 0;
	float shurikenFrequency = 1.4;
	float gameDifficulty = 2.70;
	float gravity = 0.7;
	float maxShurikenFrequency = 0.3;
};