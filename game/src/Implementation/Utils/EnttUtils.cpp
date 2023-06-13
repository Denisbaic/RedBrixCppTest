#include "EnttUtils.h"

entt::entity EnttUtils::create_copy(entt::registry& world, entt::entity id)
{
	const auto new_entity = world.create(id);

	// create a copy of an entity component by component
	for (auto&& curr : world.storage()) {
		if (auto& storage = curr.second; storage.contains(id)) {
			storage.emplace(new_entity, storage.get(id));
		}
	}

	return new_entity;
}
