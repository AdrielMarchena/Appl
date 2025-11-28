#pragma once

#include <string>
#include <vector>

#include <vulkan/vulkan_core.h>
#include <memory>

#include "Core/VulkanRender/VulkanDevices.h"

namespace Core::Vulkan {
	class VulkanGraphicsPipeline
	{
	public:
		VulkanGraphicsPipeline(std::shared_ptr<VulkanDevices>& devices);
		~VulkanGraphicsPipeline();

		void CleanUp();

		VkRenderPass GetRenderPass() const { return m_RenderPass; }
		VkPipeline GetGraphicsPipeline() const { return m_GraphicsPipeline; }
	private:
		void CreateRenderPass();
		void CreateGraphicsPipeline();

		VkShaderModule CreateShaderModule(const std::vector<char>& code);

		VkShaderModule m_VertShaderModule = VK_NULL_HANDLE;
		VkShaderModule m_FragShaderModule = VK_NULL_HANDLE;

		VkPipelineLayout m_PipelineLayout = VK_NULL_HANDLE;

		VkRenderPass m_RenderPass = VK_NULL_HANDLE;

		VkPipeline m_GraphicsPipeline = VK_NULL_HANDLE;

		std::vector<char> ReadFile(const std::string& filename);
		std::shared_ptr<VulkanDevices> m_Devices = nullptr;
	};
}


