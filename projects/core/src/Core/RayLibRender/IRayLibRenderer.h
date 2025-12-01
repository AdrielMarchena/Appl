#pragma once

#include <cstdint>

namespace Core {

	struct Color
	{
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;

		Color(uint8_t red = 0, uint8_t green = 0, uint8_t blue = 0, uint8_t alpha = 255)
			: r(red), g(green), b(blue), a(alpha) {}
	};

	struct Vector3
	{
		float x, y, z;
		Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z) {}
	};

	struct Camera3D
	{
		Vector3 position;
		Vector3 target;
		Vector3 up;
		float fovy;
		int projection; // 0 = PERSPECTIVE, 1 = ORTHOGRAPHIC

		Camera3D()
			: position(0, 10, 10), target(0, 0, 0), up(0, 1, 0), fovy(45.0f), projection(0) {}
	};

	class IRayLibRenderer
	{
	public:
		virtual ~IRayLibRenderer() = default;

	virtual void BeginRender() = 0;
	virtual void ClearScreen(const Color& color) = 0;
	
	// Text
	virtual void DrawText(const char* text, int posX, int posY, int fontSize, const Color& color) = 0;
	
	// Basic shapes
	virtual void DrawRectangle(int posX, int posY, int width, int height, const Color& color) = 0;
	virtual void DrawRectangleLines(int posX, int posY, int width, int height, const Color& color) = 0;
	virtual void DrawCircle(int centerX, int centerY, float radius, const Color& color) = 0;
	virtual void DrawCircleLines(int centerX, int centerY, float radius, const Color& color) = 0;
	virtual void DrawLine(int startX, int startY, int endX, int endY, const Color& color) = 0;
	virtual void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, const Color& color) = 0;
	
	// 3D drawing
	virtual void BeginMode3D(const Camera3D& camera) = 0;
	virtual void DrawCube(const Vector3& position, float width, float height, float length, const Color& color) = 0;
	virtual void DrawCubeWires(const Vector3& position, float width, float height, float length, const Color& color) = 0;
	virtual void DrawCubeRotated(const Vector3& position, const Vector3& rotationAxis, float rotationAngle, float width, float height, float length, const Color& color) = 0;
	virtual void DrawCubeWiresRotated(const Vector3& position, const Vector3& rotationAxis, float rotationAngle, float width, float height, float length, const Color& color) = 0;
	virtual void DrawGrid(int slices, float spacing) = 0;
	virtual void EndMode3D() = 0;
	
	virtual void EndRender() = 0;
	};

}
