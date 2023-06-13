#pragma once
#include "Contract/entt_header_wrapper.h"

class EnttUtils
{
public:
    static entt::entity create_copy(entt::registry& world, entt::entity id);
};