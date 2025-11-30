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

	class IRayLibRenderer
	{
	public:
		virtual ~IRayLibRenderer() = default;

		virtual void BeginRender() = 0;
		virtual void ClearScreen(const Color& color) = 0;
		virtual void DrawText(const char* text, int posX, int posY, int fontSize, const Color& color) = 0;
		virtual void EndRender() = 0;
	};

}
