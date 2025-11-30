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
		void DrawText(const char* text, int posX, int posY, int fontSize, const Color& color) override;
		void EndRender() override;
	};

}
