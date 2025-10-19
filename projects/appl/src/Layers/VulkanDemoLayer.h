#pragma once

#include <memory>

#include "Core/application/Layer.h"
#include "Core/application/Event.h"

#include "Core/VulkanRender/VulkanInstance.h"
#include "Core/VulkanRender/VulkanWindowSurface.h"
#include "Core/VulkanRender/VulkanDevices.h"

class VulkanDemoLayer : public Core::Layer
{
public:
	VulkanDemoLayer();
	virtual ~VulkanDemoLayer() override;

	virtual void OnEvent(Core::Event& event) override;

	virtual void OnUpdate(float ts) override;
	virtual void OnRender() override;
private:
	std::shared_ptr<Core::Vulkan::VulkanInstance> m_VulkanInstance = nullptr;
	std::shared_ptr< Core::Vulkan::VulkanWindowSurface> m_VulkanWindowSurface = nullptr;
	std::shared_ptr<Core::Vulkan::VulkanDevices> m_VulkanDevices = nullptr;
};
