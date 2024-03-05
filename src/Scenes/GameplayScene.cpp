#include "GameplayScene.h"

GameplayScene::GameplayScene()
{
	std::cout << "Creating " << typeid(*this).name() << std::endl;
}

GameplayScene::~GameplayScene()
{
}

void GameplayScene::processEvents()
{
	sf::Event e;

	while (m_window->pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
			m_window->close();

		if (e.type == sf::Event::KeyPressed)
		{
			switch (e.key.code)
			{
			case sf::Keyboard::Escape:
				m_window->close();
				break;
			default:
				break;
			}
		}
	}
}

void GameplayScene::update(sf::Time t_dT)
{
}

void GameplayScene::render()
{
	m_window->clear();

	m_window->display();
}
