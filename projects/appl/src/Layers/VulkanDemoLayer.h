#pragma once

#include <memory>

#include "Core/application/Layer.h"
#include "Core/application/Event.h"

#include "Core/VulkanRender/VulkanInstance.h"
#include "Core/VulkanRender/VulkanWindowSurface.h"
#include "Core/VulkanRender/VulkanDevices.h"
#include "Core/VulkanRender/VulkanGraphicsPipeline.h"
#include "Core/VulkanRender/VulkanFramebuffers.h"
#include "Core/VulkanRender/VulkanCommanBuffers.h"
#include <vulkan/vulkan_core.h>

class VulkanDemoLayer : public Core::Layer
{
public:
	VulkanDemoLayer();
	virtual ~VulkanDemoLayer() override;

	virtual void OnEvent(Core::Event& event) override;

	virtual void OnUpdate(float ts) override;
	virtual void OnRender() override;
	virtual void OnEndLoop() override;
private:
	void CreateSyncObjects();

	std::shared_ptr<Core::Vulkan::VulkanInstance> m_VulkanInstance = nullptr;
	std::shared_ptr< Core::Vulkan::VulkanWindowSurface> m_VulkanWindowSurface = nullptr;
	std::shared_ptr<Core::Vulkan::VulkanDevices> m_VulkanDevices = nullptr;
	std::shared_ptr<Core::Vulkan::VulkanGraphicsPipeline> m_VulkanGraphicsPipeline = nullptr;
	std::shared_ptr<Core::Vulkan::VulkanFramebuffers> m_VulkanFramebuffers = nullptr;
	std::shared_ptr<Core::Vulkan::VulkanCommanBuffers> m_VulkanCommanBuffers = nullptr;

	VkSemaphore m_ImageAvailableSemaphore = VK_NULL_HANDLE;
	VkSemaphore m_RenderFinishedSemaphore = VK_NULL_HANDLE;
	VkFence m_InFlightFence = VK_NULL_HANDLE;
};
