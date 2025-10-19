#pragma once

#include "Core/Renderer/GLUtils.h"
#include "Core/GraphicApiEnum.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

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
		GraphicApi GraphicApi = GraphicApi::OPENGL;
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

		GLFWwindow* GetHandle() const { return m_Handle; }

	private:
		void CreateVulkan();
		void CreateOpenGl();
	private:
		WindowSpecification m_Specification;
		GLFWwindow* m_Handle = nullptr;
	};

}