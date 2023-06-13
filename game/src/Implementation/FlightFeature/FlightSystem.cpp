#include "FlightSystem.h"

#include <chrono>

#include "FlightInfo.h"
#include "Implementation/TimerManager.h"
#include "Implementation/CommonComponents/BoxInfo.h"
#include "Implementation/CommonComponents/SphereInfo.h"
#include "Implementation/MoveFeature/TransformInfo.h"
#include "Implementation/TeamFeature/TeamInfo.h"

#include "raymath.h"

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

	//auto view_units = world.view<TransformInfo,BoxInfo, TeamInfo,UnitMarker>();

	for (auto& [entity, pos,flight_info,team_info,sphere_info] : view.each())
	{
		if(flight_info.t >=1.f)
		{
			world.destroy(entity);
			continue;
		}

		flight_info.t += std::chrono::duration<float>(TimerManager::instance().MS_PER_UPDATE).count();

		pos.transform.translation = QuadBezier(flight_info.P0, flight_info.P1, flight_info.P2, flight_info.t);

		const auto Q = LinearBezier(flight_info.P1, flight_info.P2, flight_info.t);
		pos.transform.rotation = QuaternionFromMatrix(MatrixLookAt(pos.transform.translation, Q, { 0,1,0 }));

		/*
		 for (auto& [entity2,pos2,box_info, team_info]:view_units.each())
		{
			if(team.team != team_info.team && CheckCollisionBoxSphere(BoxComponentToBB(pos2.transform.translation,box_info), sphere.pos, sphere.radius))
			{
				health.current_health -= 1.f;
				world.destroy(entity);
			}
		}
		*/
	}
}
