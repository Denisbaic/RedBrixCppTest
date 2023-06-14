#include "MathUtils.h"

#include "raymath.h"

Vector3 MathUtils::InterpConstantTo(Vector3 const& Current, Vector3 const& Target, float DeltaTime, float InterpSpeed)
{
	const Vector3 Delta = Vector3Subtract(Target, Current);
	const float DeltaM = Vector3Length(Delta);
	const float MaxStep = InterpSpeed * DeltaTime;

	if (DeltaM > MaxStep)
	{
		if (MaxStep > 0.f)
		{
			const Vector3 DeltaN = { Delta.x / DeltaM,Delta.y / DeltaM,Delta.z / DeltaM };
			return Vector3Add(Current, { DeltaN.x * MaxStep, DeltaN.y * MaxStep, DeltaN.z * MaxStep });
		}
		return Current;
	}

	return Target;
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
