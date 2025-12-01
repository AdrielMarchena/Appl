#include "ImGuiLayer.h"

#include <imgui.h>

ImGuiLayer::ImGuiLayer()
{
}

ImGuiLayer::~ImGuiLayer()
{
}

void ImGuiLayer::OnImGui()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit"))
			{
				// TODO: Add exit functionality
			}
			ImGui::EndMenu();
		}
		
		if (ImGui::BeginMenu("View"))
		{
			if (ImGui::MenuItem("Demo Window"))
			{
				// TODO: Toggle demo window
			}
			ImGui::EndMenu();
		}
		
		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("About"))
			{
				// TODO: Show about dialog
			}
			ImGui::EndMenu();
		}
		
		ImGui::EndMainMenuBar();
	}
}
