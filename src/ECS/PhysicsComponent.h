#pragma once

#include "ECS.h"
#include "Components.h"

class PhysicsComponent : public Component
{
private:
	TransformComponent *transform;
	Vector2D gravityAcceleration;

public:
	PhysicsComponent() = default;

	void init() override 
	{
		transform = &entity->getComponent<TransformComponent>();
		gravityAcceleration.y = 0.01f;
	}

	void update() override
	{
		transform->velocity.add(gravityAcceleration);
	}
};