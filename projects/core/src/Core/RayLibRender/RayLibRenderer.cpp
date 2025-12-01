#include "RayLibRenderer.h"

#define GRAPHICS_API_OPENGL_33
#define RAYLIB_SUPPORT_MODULE_RSHAPES
#define RAYLIB_SUPPORT_MODULE_RTEXTURES
#define RAYLIB_SUPPORT_MODULE_RMODELS
#define RAYLIB_SUPPORT_MODULE_RTEXT
#include <raylib.h>

namespace Core {

	void RayLibRenderer::BeginRender()
	{
		BeginDrawing();
	}

	void RayLibRenderer::ClearScreen(const Color& color)
	{
		::Color rlColor = { color.r, color.g, color.b, color.a };
		ClearBackground(rlColor);
	}

	void RayLibRenderer::DrawText(const char* text, int posX, int posY, int fontSize, const Color& color)
	{
		::Color rlColor = { color.r, color.g, color.b, color.a };
		::DrawText(text, posX, posY, fontSize, rlColor);
	}

	void RayLibRenderer::DrawRectangle(int posX, int posY, int width, int height, const Color& color)
	{
		::DrawRectangle(posX, posY, width, height, { color.r, color.g, color.b, color.a });
	}

	void RayLibRenderer::DrawRectangleLines(int posX, int posY, int width, int height, const Color& color)
	{
		::DrawRectangleLines(posX, posY, width, height, { color.r, color.g, color.b, color.a });
	}

	void RayLibRenderer::DrawCircle(int centerX, int centerY, float radius, const Color& color)
	{
		::DrawCircle(centerX, centerY, radius, { color.r, color.g, color.b, color.a });
	}

	void RayLibRenderer::DrawCircleLines(int centerX, int centerY, float radius, const Color& color)
	{
		::DrawCircleLines(centerX, centerY, radius, { color.r, color.g, color.b, color.a });
	}

	void RayLibRenderer::DrawLine(int startX, int startY, int endX, int endY, const Color& color)
	{
		::DrawLine(startX, startY, endX, endY, { color.r, color.g, color.b, color.a });
	}

	void RayLibRenderer::DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, const Color& color)
	{
		::Vector2 v1 = { (float)x1, (float)y1 };
		::Vector2 v2 = { (float)x2, (float)y2 };
		::Vector2 v3 = { (float)x3, (float)y3 };
		::DrawTriangle(v1, v2, v3, { color.r, color.g, color.b, color.a });
	}

	void RayLibRenderer::BeginMode3D(const Camera3D& camera)
	{
		::Camera3D rlCamera = {};
		rlCamera.position = { camera.position.x, camera.position.y, camera.position.z };
		rlCamera.target = { camera.target.x, camera.target.y, camera.target.z };
		rlCamera.up = { camera.up.x, camera.up.y, camera.up.z };
		rlCamera.fovy = camera.fovy;
		rlCamera.projection = camera.projection;
		::BeginMode3D(rlCamera);
	}

	void RayLibRenderer::DrawCube(const Vector3& position, float width, float height, float length, const Color& color)
	{
		::DrawCube({ position.x, position.y, position.z }, width, height, length, { color.r, color.g, color.b, color.a });
	}

	void RayLibRenderer::DrawCubeWires(const Vector3& position, float width, float height, float length, const Color& color)
	{
		::DrawCubeWires({ position.x, position.y, position.z }, width, height, length, { color.r, color.g, color.b, color.a });
	}

	void RayLibRenderer::DrawCubeRotated(const Vector3& position, const Vector3& rotationAxis, float rotationAngle, float width, float height, float length, const Color& color)
	{
		::Vector3 size = { width, height, length };
		::DrawCubeV({ position.x, position.y, position.z }, size, { color.r, color.g, color.b, color.a });
	}

	void RayLibRenderer::DrawCubeWiresRotated(const Vector3& position, const Vector3& rotationAxis, float rotationAngle, float width, float height, float length, const Color& color)
	{
		::Vector3 size = { width, height, length };
		::DrawCubeWiresV({ position.x, position.y, position.z }, size, { color.r, color.g, color.b, color.a });
	}

	void RayLibRenderer::DrawGrid(int slices, float spacing)
	{
		::DrawGrid(slices, spacing);
	}

	void RayLibRenderer::EndMode3D()
	{
		::EndMode3D();
	}

	void RayLibRenderer::EndRender()
	{
		EndDrawing();
	}

}
