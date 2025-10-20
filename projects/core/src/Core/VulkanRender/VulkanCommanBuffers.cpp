#include "VulkanCommanBuffers.h"
#include <memory>
#include "VulkanDevices.h"
#include "VulkanFramebuffers.h"
#include <vulkan/vulkan_core.h>

#include <stdexcept>
#include <cstdint>

namespace Core::Vulkan {
	VulkanCommanBuffers::VulkanCommanBuffers(std::shared_ptr<VulkanDevices>& devices, std::shared_ptr<VulkanFramebuffers>& framebuffers, std::shared_ptr<VulkanGraphicsPipeline>& pipeline)
		:m_Devices(devices), m_Framebuffers(framebuffers), m_Pipeline(pipeline)
	{
		CreateCommandPool();
		CreateCommandBuffers();
	}

	VulkanCommanBuffers::~VulkanCommanBuffers()
	{
		CleanUp();
	}

	void VulkanCommanBuffers::CleanUp()
	{
		if (!m_Devices) return;

		if (m_CommandPool) {
			vkDestroyCommandPool(m_Devices->GetDevice(), m_CommandPool, nullptr);
			m_CommandPool = VK_NULL_HANDLE;
		}
	}

	void VulkanCommanBuffers::CreateCommandPool()
	{
		QueueFamilyIndices queueFamilyIndices = m_Devices->FindQueueFamilies(m_Devices->GetPhysicalDevice());

		VkCommandPoolCreateInfo poolInfo{};
		poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
		poolInfo.queueFamilyIndex = queueFamilyIndices.GraphicsFamily.value();

		if (vkCreateCommandPool(m_Devices->GetDevice(), &poolInfo, nullptr, &m_CommandPool) != VK_SUCCESS) {
			throw std::runtime_error("failed to create command pool!");
		}
	}

	void VulkanCommanBuffers::CreateCommandBuffers()
	{
		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.commandPool = m_CommandPool;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandBufferCount = 1;

		if (vkAllocateCommandBuffers(m_Devices->GetDevice(), &allocInfo, &m_CommandBuffer) != VK_SUCCESS) {
			throw std::runtime_error("failed to allocate command buffers!");
		}
	}

	void VulkanCommanBuffers::RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex)
	{
		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = 0; // Optional
		beginInfo.pInheritanceInfo = nullptr; // Optional

		if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
			throw std::runtime_error("failed to begin recording command buffer!");
		}

		auto swapChainExtent = m_Devices->GetSwapChainExtent();

		VkRenderPassBeginInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = m_Pipeline->GetRenderPass();
		renderPassInfo.framebuffer = m_Framebuffers->GetSwapChainFramebuffers()[imageIndex];

		renderPassInfo.renderArea.offset = { 0, 0 };
		renderPassInfo.renderArea.extent = swapChainExtent;

		VkClearValue clearColor = { {{0.0f, 0.0f, 0.0f, 1.0f}} };
		renderPassInfo.clearValueCount = 1;
		renderPassInfo.pClearValues = &clearColor;

		vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

		vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_Pipeline->GetGraphicsPipeline());
	
		VkViewport viewport{};
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = static_cast<float>(swapChainExtent.width);
		viewport.height = static_cast<float>(swapChainExtent.height);
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;
		vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

		VkRect2D scissor{};
		scissor.offset = { 0, 0 };
		scissor.extent = swapChainExtent;
		vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

		vkCmdDraw(commandBuffer, 3, 1, 0, 0);

		vkCmdEndRenderPass(commandBuffer);

		if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
			throw std::runtime_error("failed to record command buffer!");
		}
	}

}
