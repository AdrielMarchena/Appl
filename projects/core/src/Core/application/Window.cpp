#include "Window.h"

#include <iostream>
#include <assert.h>

#define GRAPHICS_API_OPENGL_33
#define RAYLIB_SUPPORT_MODULE_RSHAPES
#define RAYLIB_SUPPORT_MODULE_RTEXTURES
#define RAYLIB_SUPPORT_MODULE_RMODELS
#define RAYLIB_SUPPORT_MODULE_RTEXT
#include <raylib.h>

namespace Core {

	Window::Window(const WindowSpecification& specification)
		: m_Specification(specification)
	{
	}

	Window::~Window()
	{
		Destroy();
	}

	void Window::Create()
	{
		CreateRayLib();
	}

	void Window::Destroy()
	{
		CloseWindow();
	}

	void Window::Update()
	{
		// RayLib handles buffer swapping in EndDrawing()
	}

	glm::vec2 Window::GetFramebufferSize()
	{
		return { (float)GetScreenWidth(), (float)GetScreenHeight() };
	}

	bool Window::ShouldClose() const
	{
		return WindowShouldClose();
	}

	void Window::CreateRayLib()
	{
		InitWindow(m_Specification.Width, m_Specification.Height, m_Specification.Title.c_str());
		
		if (m_Specification.VSync)
		{
			SetTargetFPS(60);
		}
	}
}
