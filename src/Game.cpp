#include <Game.h>

Game::~Game()
{
	delete m_window;
}

void Game::run()
{
	m_window = createWindow("SFML Big project");
	m_window->setKeyRepeatEnabled(false);
	m_window->setView({ SCREEN_CENTRE, RESOLUTION });

	SceneManager& sceneManager = SceneManager::getInstance();
	sceneManager.setWindow(m_window);

	sceneManager.registerScene<GameplayScene>(SceneType::GAMEPLAY);
	sceneManager.setScene(SceneType::GAMEPLAY);

	sf::Clock clock;
	sf::Time lag = sf::Time::Zero;
	constexpr sf::Time MS_PER_UPDATE = sf::seconds(1 / 60.f);

	while (m_window->isOpen()) {
		sf::Time dT = clock.restart();
		lag += dT;

		sceneManager.processEvents();

		while (lag > MS_PER_UPDATE) {
			sceneManager.update(MS_PER_UPDATE);
			lag -= MS_PER_UPDATE;
		}

		sceneManager.update(dT);
		sceneManager.render();
	}
}

void Game::loadTextures()
{
}

sf::RenderWindow* Game::createWindow(std::string t_title)
{
	return new sf::RenderWindow(
		sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
		t_title, sf::Style::Titlebar | sf::Style::Close
	);
}
