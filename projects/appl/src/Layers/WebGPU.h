#pragma once

#include "Core/application/Layer.h"

class WebGPU : public Core::Layer
{
public:
	WebGPU();
	virtual ~WebGPU();

	virtual void OnUpdate(float ts) override;
	virtual void OnRender() override;
private:
};
