#include "ComponentBuffer.h"

void ComponentBuffer::update()
{
	for (Component* component : components)
		component->update();
}

void ComponentBuffer::render()
{
	for (Component* component : components)
		component->render();
}

void ComponentBuffer::addComponent(Component* component)
{
	components.emplace_back(component);
}
