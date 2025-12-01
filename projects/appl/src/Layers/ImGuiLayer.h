#pragma once

#include "Core/application/Layer.h"

class ImGuiLayer : public Core::Layer
{
public:
	ImGuiLayer();
	virtual ~ImGuiLayer();

	virtual void OnImGui() override;
};
