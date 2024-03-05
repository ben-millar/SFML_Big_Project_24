#pragma once

#include <sfml/Graphics.hpp>

#include <Globals.h>
#include <Scenes/SceneManager/SceneManager.h>
#include <Scenes/GameplayScene.h>

class Game
{
public:
	Game() = default;
	~Game();

	void run();

	void loadTextures();

private:
	sf::RenderWindow* createWindow(std::string t_title);
	
	sf::RenderWindow* m_window{ nullptr };
};
