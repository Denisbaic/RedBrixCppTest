#include "FlightSystem.h"

#include <chrono>

#include "FlightInfo.h"
#include "Implementation/Utils/TimerManager.h"
#include "Implementation/CommonComponents/BoxInfo.h"
#include "Implementation/CommonComponents/SphereInfo.h"
#include "Implementation/MoveFeature/TransformInfo.h"
#include "Implementation/TeamFeature/TeamInfo.h"

#include "raymath.h"

/** Calculates the percentage along a line from MinValue to MaxValue that Value is. */

static auto GetRangePct(float MinValue, float MaxValue, float Value)
{
	// Avoid Divide by Zero.
	// But also if our range is a point, output whether Value is before or after.
	const float Divisor = MaxValue - MinValue;

	if (FloatEquals(Divisor, 0.f))
	{
		return (Value >= MaxValue) ? 1.f : 0.f;
	}

	return (Value - MinValue) / Divisor;
}

/** Basically a Vector2d version of Lerp. */
static auto GetRangeValue(std::pair<float, float> const& Range, float Pct)
{
	return Lerp(Range.first, Range.second, Pct);
}

static auto GetMappedRangeValueClamped(const std::pair<float, float>& InputRange, const std::pair<float, float>& OutputRange, const float Value)
{
	const float ClampedPct = Clamp(GetRangePct(InputRange.first, InputRange.second, Value), 0.f, 1.f);
	return GetRangeValue(OutputRange, ClampedPct);
}

extern BoundingBox BoxComponentToBB(Vector3 pos, BoxInfo const& box_component);

Vector3 LinearBezier(Vector3 P0, Vector3 P1, float t)
{
	return Vector3Add(P0, Vector3Scale(Vector3Subtract(P1, P0),t));
}

Vector3 QuadBezier(Vector3 P0, Vector3 P1, Vector3 P2, float t)
{
	const auto a = Vector3Scale(P0, (1.f - t) * (1.f - t));
	const auto b = Vector3Scale(P1, 2.f * t * (1.f - t));
	const auto c = Vector3Scale(P2, t * t);
	const auto result = Vector3Add(Vector3Add(a, b), c);

	return result;
}

void FlightSystem::execute(entt::registry& world)
{
	auto view = world.view<TransformInfo, FlightInfo, TeamInfo,SphereInfo>();

	for (auto& [entity, pos,flight_info,team_info,sphere_info] : view.each())
	{
		if(flight_info.t >=1.f)
		{
			world.destroy(entity);
			continue;
		}

		flight_info.t += GetMappedRangeValueClamped({ 0.f,flight_info.total_time }, {0.f,1.f},std::chrono::duration<float>(TimerManager::instance().MS_PER_UPDATE).count());

		pos.transform.translation = QuadBezier(flight_info.P0, flight_info.P1, flight_info.P2, flight_info.t);

		const auto Q = LinearBezier(flight_info.P1, flight_info.P2, flight_info.t);
		pos.transform.rotation = QuaternionFromMatrix(MatrixLookAt(pos.transform.translation, Q, { 0,1,0 }));

	}
}
