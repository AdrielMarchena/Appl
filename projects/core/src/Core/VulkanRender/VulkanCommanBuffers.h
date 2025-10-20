#pragma once

#include "Core/VulkanRender/VulkanDevices.h"
#include "Core/VulkanRender/VulkanFramebuffers.h"
#include "Core/VulkanRender/VulkanGraphicsPipeline.h"
#include <memory>
#include <vulkan/vulkan_core.h>
#include <cstdint>

namespace Core::Vulkan {
	class VulkanCommanBuffers
	{
	public:
		VulkanCommanBuffers(std::shared_ptr<VulkanDevices>& devices, std::shared_ptr<VulkanFramebuffers>& framebuffers, std::shared_ptr<VulkanGraphicsPipeline>& pipeline);
	
		~VulkanCommanBuffers();

		void CleanUp();

		void RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

		VkCommandBuffer GetCommandBuffer() const { return m_CommandBuffer; }
		VkCommandBuffer* GetCommandBufferRef() { return &m_CommandBuffer; }
	private:
		void CreateCommandPool();
		void CreateCommandBuffers();


		VkCommandPool m_CommandPool = VK_NULL_HANDLE;
		VkCommandBuffer m_CommandBuffer = VK_NULL_HANDLE;

		std::shared_ptr<VulkanDevices> m_Devices;
		std::shared_ptr<VulkanFramebuffers> m_Framebuffers;
		std::shared_ptr<VulkanGraphicsPipeline> m_Pipeline;
	};
}

