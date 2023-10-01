#include "GameObjectsManager.hpp"

void GameObjectsManager::add(std::shared_ptr<AGameObject> newObj)
{
	gameObjects.push_back(newObj);
}

std::size_t GameObjectsManager::size() const
{
	return gameObjects.size();
}

void GameObjectsManager::update(float deltaTime)
{
	for (auto& el : gameObjects)
	{
		el->update(deltaTime);
	}
}

void GameObjectsManager::render(sf::RenderTarget& renderTarget)
{
	for (auto& el : gameObjects)
	{
		renderTarget.draw(*el.get());
	}
}

std::vector<std::shared_ptr<AGameObject>> GameObjectsManager::getVector()
{
	return gameObjects;
}