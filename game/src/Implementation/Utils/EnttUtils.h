#pragma once
#include "Contract/EnttHeaderWeapper.h"

class EnttUtils
{
public:
    static entt::entity CreateCopy(entt::registry& world, entt::entity id);
};