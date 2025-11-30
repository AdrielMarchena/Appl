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

	void RayLibRenderer::EndRender()
	{
		EndDrawing();
	}

}
