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
private:
	std::unique_ptr<Core::RayLibRenderer> m_Renderer;
};
