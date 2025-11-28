#pragma once

#include <vulkan/vulkan_core.h>

#include "Core/VulkanRender/VulkanInstance.h"
#include <memory>

namespace Core::Vulkan {
	class VulkanWindowSurface
	{
	public:
		VulkanWindowSurface(std::shared_ptr<VulkanInstance>& instance);
		~VulkanWindowSurface();

		void CleanUp();
		VkSurfaceKHR GetSurfaceHandler() const { return m_Surface; }
	private:
		void CreateWindowSurface();

		VkSurfaceKHR m_Surface = VK_NULL_HANDLE;
		std::shared_ptr<VulkanInstance> m_VulkanInstance;
	};
}


