#pragma once

#include "Core/VulkanRender/VulkanDevices.h"
#include "Core/VulkanRender/VulkanGraphicsPipeline.h"
#include <memory>
#include <vulkan/vulkan_core.h>
#include <vector>

namespace Core::Vulkan {
	class VulkanFramebuffers
	{
	public:
		VulkanFramebuffers(std::shared_ptr<VulkanDevices>& devices, std::shared_ptr<VulkanGraphicsPipeline>& pipeline);
		~VulkanFramebuffers();

		void CleanUp();

		const std::vector<VkFramebuffer>& GetSwapChainFramebuffers() const { return m_SwapChainFramebuffers; }
	private:
		void CreateFramebuffers();

		std::shared_ptr<VulkanDevices> m_Devices = nullptr;
		std::shared_ptr<VulkanGraphicsPipeline> m_Pipeline = nullptr;

		std::vector<VkFramebuffer> m_SwapChainFramebuffers;
	};
}
