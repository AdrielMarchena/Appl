#include "VulkanFramebuffers.h"
#include <memory>
#include "VulkanDevices.h"
#include <vulkan/vulkan_core.h>
#include "VulkanGraphicsPipeline.h"
#include <stdexcept>

namespace Core::Vulkan {
	VulkanFramebuffers::VulkanFramebuffers(std::shared_ptr<VulkanDevices>& devices, std::shared_ptr<VulkanGraphicsPipeline>& pipeline)
		:m_Devices(devices), m_Pipeline(pipeline)
	{
		CreateFramebuffers();
	}

	VulkanFramebuffers::~VulkanFramebuffers()
	{
		CleanUp();
	}

	void VulkanFramebuffers::CleanUp()
	{
		if (!m_Devices && m_Devices->GetDevice()) return;

		for (auto framebuffer : m_SwapChainFramebuffers) {
			vkDestroyFramebuffer(m_Devices->GetDevice(), framebuffer, nullptr);
		}
	}

	void VulkanFramebuffers::CreateFramebuffers()
	{
		auto& swapChainImageViews = m_Devices->GetSwapChainImageViews();
		m_SwapChainFramebuffers.resize(swapChainImageViews.size());

		auto swapChainExtent = m_Devices->GetSwapChainExtent();

		for (size_t i = 0; i < swapChainImageViews.size(); i++) {
			VkImageView attachments[] = {
				swapChainImageViews[i]
			};

			VkFramebufferCreateInfo framebufferInfo{};
			framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
			framebufferInfo.renderPass = m_Pipeline->GetRenderPass();
			framebufferInfo.attachmentCount = 1;
			framebufferInfo.pAttachments = attachments;
			framebufferInfo.width = swapChainExtent.width;
			framebufferInfo.height = swapChainExtent.height;
			framebufferInfo.layers = 1;

			if (vkCreateFramebuffer(m_Devices->GetDevice(), &framebufferInfo, nullptr, &m_SwapChainFramebuffers[i]) != VK_SUCCESS) {
				throw std::runtime_error("failed to create framebuffer!");
			}
		}
	}
}
