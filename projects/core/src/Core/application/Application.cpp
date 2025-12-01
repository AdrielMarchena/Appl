#include "Application.h"

#include "Core/logger/logger.h"
#include "Core/ImGui/ImGuiContext.h"

#include <raylib.h>

#include <glm/glm.hpp>

#include <assert.h>
#include <iostream>

namespace Core {

	static Application* s_Application = nullptr;

	Application::Application(const ApplicationSpecification& specification)
		: m_Specification(specification)
	{
		s_Application = this;

		// Set window title to app name if empty
		if (m_Specification.WindowSpec.Title.empty())
			m_Specification.WindowSpec.Title = m_Specification.Name;

		m_Window = std::make_shared<Window>(m_Specification.WindowSpec);
		m_Window->Create();

		Core::Log::Init();
		ImGuiContext::Init(nullptr);
	}

	Application::~Application()
	{
		ImGuiContext::Shutdown();
		m_Window->Destroy();

		s_Application = nullptr;
	}

	void Application::Run()
	{
		m_Running = true;

		float lastTime = GetTime();

		// Main Application loop
		while (m_Running)
		{
			if (m_Window->ShouldClose())
			{
				Stop();
				break;
			}

			float currentTime = GetTime();
			float timestep = glm::clamp(currentTime - lastTime, 0.001f, 0.1f);
			lastTime = currentTime;

			// Main layer update here
			for (const std::unique_ptr<Layer>& layer : m_LayerStack)
				layer->OnUpdate(timestep);

			// Start frame
			BeginDrawing();

			// NOTE: rendering can be done elsewhere (eg. render thread)
			for (const std::unique_ptr<Layer>& layer : m_LayerStack)
				layer->OnRender();

			// ImGui rendering (must be before EndDrawing)
			ImGuiContext::NewFrame();
			for (const std::unique_ptr<Layer>& layer : m_LayerStack)
				layer->OnImGui();
			ImGuiContext::Render();

			// End frame
			EndDrawing();

			m_Window->Update();
		}

		for (const std::unique_ptr<Layer>& layer : m_LayerStack)
			layer->OnEndLoop();
	}

	void Application::Stop()
	{
		m_Running = false;
	}

	glm::vec2 Application::GetFramebufferSize() const
	{
		return m_Window->GetFramebufferSize();
	}

	Application& Application::Get()
	{
		assert(s_Application);
		return *s_Application;
	}

	float Application::GetTime()
	{
		return ::GetTime();
	}
}