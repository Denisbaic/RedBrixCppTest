#pragma once
#include "Contract/entt_header_wrapper.h"

class EnttUtils
{
public:
    static entt::entity CreateCopy(entt::registry& world, entt::entity id);
};