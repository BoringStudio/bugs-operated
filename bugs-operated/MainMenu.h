#pragma once

#include "SceneManager.h"

class MainMenu : public Scene
{
public:
	MainMenu();

	void onInit() override;

	void onClose() override;

	void onUpdate(const float dt) override;

	void onDraw(const float dt) override;

	void onLeave() override;

	void onReturn() override;
};