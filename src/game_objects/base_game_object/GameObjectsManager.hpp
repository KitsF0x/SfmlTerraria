#pragma once

#include <vector>
#include "AGameObject.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

class GameObjectsManager
{
private:
	std::vector<std::shared_ptr<AGameObject>> gameObjects;
public:
	void add(std::shared_ptr<AGameObject> newObj);
	std::size_t size() const;
	void update(float deltaTime);
	void render(sf::RenderTarget& renderTarget);
	std::vector<std::shared_ptr<AGameObject>> getVector();
};