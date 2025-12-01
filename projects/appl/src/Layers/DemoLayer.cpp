#include "DemoLayer.h"

#include "Core/application/Application.h"
#include "Core/RayLibRender/RayLibRenderer.h"

#include <imgui.h>
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
	m_Rotation += ts * m_RotationSpeed;
}

void DemoLayer::OnRender()
{
	// Clear screen with a nice blue color
	Core::Color clearColor = { 100, 149, 237, 255 }; // Cornflower blue
	m_Renderer->ClearScreen(clearColor);
	
	// Draw some rectangles
	Core::Color redColor = { 255, 0, 0, 255 };
	m_Renderer->DrawRectangle(50, 50, 100, 80, redColor);
	
	Core::Color greenColor = { 0, 255, 0, 255 };
	m_Renderer->DrawRectangleLines(200, 50, 100, 80, greenColor);
	
	// Draw circles
	Core::Color yellowColor = { 255, 255, 0, 255 };
	m_Renderer->DrawCircle(100, 250, 40, yellowColor);
	
	Core::Color magentaColor = { 255, 0, 255, 255 };
	m_Renderer->DrawCircleLines(250, 250, 40, magentaColor);
	
	// Draw lines
	Core::Color whiteColor = { 255, 255, 255, 255 };
	m_Renderer->DrawLine(400, 50, 500, 150, whiteColor);
	m_Renderer->DrawLine(500, 50, 400, 150, whiteColor);
	
	// Draw triangle
	Core::Color cyanColor = { 0, 255, 255, 255 };
	m_Renderer->DrawTriangle(450, 200, 400, 300, 500, 300, cyanColor);
	
	// Draw 3D cube with rotating camera
	float radius = 10.0f;
	float camX = sin(glm::radians(m_Rotation)) * radius;
	float camZ = cos(glm::radians(m_Rotation)) * radius;
	
	Core::Camera3D camera;
	camera.position = Core::Vector3(camX, 10.0f, camZ);
	camera.target = Core::Vector3(0.0f, 1.0f, 0.0f);
	camera.up = Core::Vector3(0.0f, 1.0f, 0.0f);
	camera.fovy = 45.0f;
	camera.projection = 0; // Perspective
	
	m_Renderer->BeginMode3D(camera);
	
	// Draw grid
	m_Renderer->DrawGrid(10, 1.0f);
	
	// Draw cube at position
	Core::Vector3 cubePos(0.0f, 1.0f, 0.0f);
	Core::Color cubeColor = { 255, 100, 100, 255 };
	m_Renderer->DrawCube(cubePos, 2.0f, 2.0f, 2.0f, cubeColor);
	
	Core::Color wireColor = { 50, 50, 50, 255 };
	m_Renderer->DrawCubeWires(cubePos, 2.0f, 2.0f, 2.0f, wireColor);
	
	m_Renderer->EndMode3D();
	
	// Draw some text
	Core::Color textColor = { 200, 200, 200, 255 }; // Light gray
	m_Renderer->DrawText("RayLib 2D + 3D Demo!", 150, 10, 20, textColor);
}

void DemoLayer::OnImGui()
{
	ImGui::Begin("Demo Controls");
	ImGui::SliderFloat("Rotation Speed", &m_RotationSpeed, 0.0f, 200.0f);
	ImGui::Text("Current Rotation: %.1f degrees", m_Rotation);
	ImGui::End();
}