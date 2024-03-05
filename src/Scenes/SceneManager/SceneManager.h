#pragma once

#include <functional>
#include <iostream>
#include <memory>
#include <optional>
#include <unordered_map>

#include <sfml/Graphics/RenderWindow.hpp>

#include <Scenes/IBaseScene.h>
#include <Globals.h>

enum class SceneType { MAIN_MENU, GAMEPLAY };

using Scene = std::unique_ptr<IBaseScene>;
using SceneFactory = std::unordered_map<SceneType, std::function<Scene()>>;

class SceneManager
{
public:
	static SceneManager& getInstance()
	{
		static SceneManager instance;
		return instance;
	}

	SceneManager(SceneManager const&) = delete;
	void operator=(SceneManager const&) = delete;

	void setWindow(sf::RenderWindow* t_window) { m_window = t_window; }


	template<typename T, typename... A>
	void registerScene(SceneType t_sceneType, A&& ...args)
	{
		m_sceneFactory.emplace(t_sceneType, [&, args...]() mutable {
			return std::make_unique<T>(std::forward<A>(args)...);
		});
	}

	void setScene(SceneType t_sceneType)
	{
		if (const auto it = m_sceneFactory.find(t_sceneType); it != m_sceneFactory.end())
		{
			auto scene = it->second();
			scene->setWindow(m_window);
			m_currentScene = std::move(scene);
		}
		else
		{
			std::cerr << ERROR_MSG << std::endl;
		}
	}

	void processEvents() {
		withCurrentScene([](auto& scene) { scene.processEvents(); });
	}

	void update(sf::Time t_dT) {
		withCurrentScene([&t_dT](auto& scene) { scene.update(t_dT); });
	}

	void render() {
		withCurrentScene([](auto& scene) { scene.render(); });
	}


private:
	SceneManager() {}
	SceneFactory m_sceneFactory;
	std::optional<Scene> m_currentScene;
	sf::RenderWindow* m_window{ nullptr };

	template<typename ACTION>
	void withCurrentScene(ACTION t_action)
	{
		if (m_currentScene) {
			t_action(*m_currentScene.value());
		}
	}

	const std::string ERROR_MSG{
		"Trying to create scene which hasn't been registered with SceneManager"
	};
};