#pragma once

#include <memory>

#include "Core/application/Layer.h"

namespace Core {
	class RayLibRenderer;
}

class DemoLayer : public Core::Layer
{
public:
	DemoLayer();
	virtual ~DemoLayer();

	virtual void OnUpdate(float ts) override;
	virtual void OnRender() override;
	virtual void OnImGui() override;
private:
	std::unique_ptr<Core::RayLibRenderer> m_Renderer;
	float m_Rotation = 0.0f;
	float m_RotationSpeed = 50.0f;
};
