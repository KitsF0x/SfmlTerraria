#include "AGameObject.hpp"

bool AGameObject::collidesTop(sf::FloatRect otherArea)
{
	if (getHitbox().intersects(otherArea))
	{
		float otherBottom = otherArea.top + otherArea.height;
		return (
			otherBottom > getHitbox().top &&
			otherBottom < getHitbox().top + getHitbox().height
			);
	}
	return false;
}

bool AGameObject::collidesBottom(sf::FloatRect otherArea)
{
	if (getHitbox().intersects(otherArea))
	{
		float otherTop = otherArea.top;
		return (
			otherTop > getHitbox().top &&
			otherTop < getHitbox().top + getHitbox().height
			);
	}
	return false;
}

bool AGameObject::collidesLeft(sf::FloatRect otherArea)
{
	if (getHitbox().intersects(otherArea))
	{
		float otherLeft = otherArea.left + otherArea.width;
		return (
			otherLeft > getHitbox().left &&
			otherLeft < getHitbox().left + getHitbox().width
			);
	}
	return false;
}

bool AGameObject::collidesRight(sf::FloatRect otherArea)
{
	if (getHitbox().intersects(otherArea))
	{
		float otherLeft = otherArea.left;
		return (
			otherLeft > getHitbox().left &&
			otherLeft < getHitbox().left + getHitbox().width
			);
	}
	return false;
}