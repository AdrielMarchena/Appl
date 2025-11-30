#pragma once

#include "Core/GraphicApiEnum.h"

#include <glm/glm.hpp>
#include <string>

namespace Core {
	struct WindowSpecification
	{
		std::string Title;
		uint32_t Width = 1280;
		uint32_t Height = 720;
		bool IsResizeable = true;
		bool VSync = true;
		GraphicApi Api = GraphicApi::RAYLIB;
	};

	class Window
	{
	public:
		Window(const WindowSpecification& specification = WindowSpecification());
		~Window();

		void Create();
		void Destroy();

		void Update();

		glm::vec2 GetFramebufferSize();

		bool ShouldClose() const;

	private:
		void CreateRayLib();
	private:
		WindowSpecification m_Specification;
	};

}