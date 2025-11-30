#include "DemoLayer.h"

#include "Core/application/Application.h"
#include "Core/RayLibRender/RayLibRenderer.h"

#include <glm/glm.hpp>

DemoLayer::DemoLayer()
{
	m_Renderer = std::make_unique<Core::RayLibRenderer>();
}

DemoLayer::~DemoLayer()
{
}

void DemoLayer::OnUpdate(float ts)
{
}

void DemoLayer::OnRender()
{
	m_Renderer->BeginRender();
	
	// Clear screen with a nice blue color
	Core::Color clearColor = { 100, 149, 237, 255 }; // Cornflower blue
	m_Renderer->ClearScreen(clearColor);
	
	// Draw some text
	Core::Color textColor = { 200, 200, 200, 255 }; // Light gray
	m_Renderer->DrawText("Hello RayLib!", 190, 200, 20, textColor);
	
	m_Renderer->EndRender();
}