#include "ImGuiContext.h"

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>

#include <raylib.h>

namespace Core {

	static bool s_Initialized = false;

	void ImGuiContext::Init(void* windowHandle)
	{
		if (s_Initialized) return;

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

		ImGui::StyleColorsDark();

		// Initialize OpenGL3 backend
		ImGui_ImplOpenGL3_Init("#version 330");

		s_Initialized = true;
	}

	void ImGuiContext::Shutdown()
	{
		if (!s_Initialized) return;

		ImGui_ImplOpenGL3_Shutdown();
		ImGui::DestroyContext();
		s_Initialized = false;
	}

	void ImGuiContext::NewFrame()
	{
		if (!s_Initialized) return;

		ImGui_ImplOpenGL3_NewFrame();
		
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2((float)GetScreenWidth(), (float)GetScreenHeight());
		io.DeltaTime = GetFrameTime();

		// Update mouse position
		io.MousePos = ImVec2((float)GetMouseX(), (float)GetMouseY());

		// Update mouse buttons
		io.MouseDown[0] = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
		io.MouseDown[1] = IsMouseButtonDown(MOUSE_BUTTON_RIGHT);
		io.MouseDown[2] = IsMouseButtonDown(MOUSE_BUTTON_MIDDLE);

		// Update mouse wheel
		io.MouseWheel = GetMouseWheelMove();

		// Update keyboard modifiers
		io.AddKeyEvent(ImGuiMod_Ctrl, IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL));
		io.AddKeyEvent(ImGuiMod_Shift, IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT));
		io.AddKeyEvent(ImGuiMod_Alt, IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT));
		io.AddKeyEvent(ImGuiMod_Super, IsKeyDown(KEY_LEFT_SUPER) || IsKeyDown(KEY_RIGHT_SUPER));

		// Get text input
		int ch = GetCharPressed();
		while (ch > 0)
		{
			io.AddInputCharacter(ch);
			ch = GetCharPressed();
		}

		ImGui::NewFrame();
	}

	void ImGuiContext::Render()
	{
		if (!s_Initialized) return;

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

}
