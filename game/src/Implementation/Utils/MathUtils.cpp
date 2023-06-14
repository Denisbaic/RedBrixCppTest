#include "MathUtils.h"

#include "raymath.h"

Vector3 MathUtils::InterpConstantTo(Vector3 const& current, Vector3 const& target, float dt, float interp_speed)
{
	const Vector3 delta = Vector3Subtract(target, current);
	const float delta_m = Vector3Length(delta);
	const float max_step = interp_speed * dt;

	if (delta_m > max_step)
	{
		if (max_step > 0.f)
		{
			const Vector3 delta_n = { delta.x / delta_m,delta.y / delta_m,delta.z / delta_m };
			return Vector3Add(current, { delta_n.x * max_step, delta_n.y * max_step, delta_n.z * max_step });
		}
		return current;
	}

	return target;
}

BoundingBox MathUtils::BoxComponentToBB(Vector3 pos, BoxInfo const& box_component)
{
	const BoundingBox bb = { { pos.x - box_component.size.x / 2,
			pos.y - box_component.size.y / 2,
			pos.z - box_component.size.z / 2 },
		{
			pos.x + box_component.size.x / 2,
			pos.y + box_component.size.y / 2,
			pos.z + box_component.size.z / 2
		} };

	return bb;
}
