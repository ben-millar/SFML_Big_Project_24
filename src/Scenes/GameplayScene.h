#pragma once

#include <Globals.h>
#include <Scenes/SceneManager/SceneManager.h>
#include <Scenes/IBaseScene.h>

class GameplayScene : public IBaseScene {
public:
	GameplayScene();
	~GameplayScene();

	virtual void processEvents() override;

	virtual void update(sf::Time t_dT) override;

	virtual void render() override;
};
