#pragma once

#include "IRayLibRenderer.h"

namespace Core {

	class RayLibRenderer : public IRayLibRenderer
	{
	public:
		RayLibRenderer() = default;
		~RayLibRenderer() override = default;

	void BeginRender() override;
	void ClearScreen(const Color& color) override;
	
	// Text
	void DrawText(const char* text, int posX, int posY, int fontSize, const Color& color) override;
	
	// Basic shapes
	void DrawRectangle(int posX, int posY, int width, int height, const Color& color) override;
	void DrawRectangleLines(int posX, int posY, int width, int height, const Color& color) override;
	void DrawCircle(int centerX, int centerY, float radius, const Color& color) override;
	void DrawCircleLines(int centerX, int centerY, float radius, const Color& color) override;
	void DrawLine(int startX, int startY, int endX, int endY, const Color& color) override;
	void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, const Color& color) override;
	
	// 3D drawing
	void BeginMode3D(const Camera3D& camera) override;
	void DrawCube(const Vector3& position, float width, float height, float length, const Color& color) override;
	void DrawCubeWires(const Vector3& position, float width, float height, float length, const Color& color) override;
	void DrawCubeRotated(const Vector3& position, const Vector3& rotationAxis, float rotationAngle, float width, float height, float length, const Color& color) override;
	void DrawCubeWiresRotated(const Vector3& position, const Vector3& rotationAxis, float rotationAngle, float width, float height, float length, const Color& color) override;
	void DrawGrid(int slices, float spacing) override;
	void EndMode3D() override;
	
	void EndRender() override;
	};

}
