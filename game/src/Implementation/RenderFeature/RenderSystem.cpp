#include "RenderSystem.h"

#include "raylib.h"
#include "raymath.h"
#include "RenderableMarker.h"
#include "Implementation/CommonComponents/BoxInfo.h"
#include "Implementation/CommonComponents/CapsuleInfo.h"
#include "Implementation/CommonComponents/SphereInfo.h"
#include "Implementation/MoveFeature/TransformInfo.h"

void RenderSystem::execute(entt::registry & world, const Camera& camera)
{
	BeginDrawing();
	ClearBackground(BLACK);
	BeginMode3D(camera);

	DrawGrid(100, 1.0f);

	const auto boxes_view = world.view<TransformInfo, BoxInfo, RenderableMarker>();
	for (auto [entity,pos,box] : boxes_view.each())
		DrawCubeV(Vector3Add(pos.transform.translation, box.local_offset), box.size, box.color);

	const auto sphere_view = world.view<TransformInfo, SphereInfo, RenderableMarker>();
	for (auto [entity, pos, sphere] : sphere_view.each())
		DrawSphere(Vector3Add(pos.transform.translation, sphere.pos), sphere.radius, sphere.color);

	const auto capsule_view = world.view<TransformInfo, CapsuleInfo, RenderableMarker>();
	for (auto [entity, pos, capsule] : capsule_view.each())
		DrawCapsule(Vector3Add(pos.transform.translation, capsule.begin), Vector3Add(pos.transform.translation, capsule.end), capsule.radius, capsule.slices, capsule.rings,capsule.color);

	EndMode3D();
	EndDrawing();
}
