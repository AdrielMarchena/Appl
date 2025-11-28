#pragma once

#include <cstdint>
#include <vulkan/vulkan_core.h>
#include <optional>

#include "VulkanInstance.h"
#include "VulkanWindowSurface.h"
#include <memory>
#include <vector>

namespace Core::Vulkan
{
	struct QueueFamilyIndices {
		std::optional<uint32_t> GraphicsFamily;
		std::optional<uint32_t> PresentFamily;

		bool IsComplete() const {
			return this->GraphicsFamily.has_value() && this->PresentFamily.has_value();
		}
	};

	struct SwapChainSupportDetails {
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};

	class VulkanDevices
	{
	public:
		VulkanDevices(std::shared_ptr<VulkanInstance>& instance, std::shared_ptr<VulkanWindowSurface>& surface);
		~VulkanDevices();

		VkPhysicalDevice GetPhysicalDevice() const { return m_PhysicalDevice; }
		VkDevice GetDevice() const { return m_Device; }
		void CleanUp();

		VkExtent2D GetSwapChainExtent() const { return m_SwapChainExtent; }
		VkFormat GetSwapChainImageFormat() const { return m_SwapChainImageFormat; }
		const std::vector<VkImageView>& GetSwapChainImageViews() const { return m_SwapChainImageViews; }
		VkSwapchainKHR GetSwapChain() const { return m_SwapChain; }

		VkQueue GetGraphicsQueue() const {	return m_GraphicsQueue;	}
		VkQueue GetPresentQueue() const {	return m_PresentQueue;	}

		QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
	private:
		void CreatePhysicalDevice();
		void CreateLogicalDevice();
		void CreateGraphicsQueue();
		std::vector<VkDeviceQueueCreateInfo> GetPresentQueueCreationInfo();
		bool IsPhysicalDeviceSuitable(VkPhysicalDevice device);
		bool CheckDeviceExtensionSupport(VkPhysicalDevice device);

		const std::vector<const char*> m_DeviceExtensions = {
			VK_KHR_SWAPCHAIN_EXTENSION_NAME,
		};

		std::shared_ptr<VulkanInstance> m_VulkanInstance;
		std::shared_ptr<VulkanWindowSurface> m_VulkanWindowSurface;
		VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;
		VkDevice m_Device = VK_NULL_HANDLE;
		VkQueue m_GraphicsQueue = VK_NULL_HANDLE;
		VkQueue m_PresentQueue = VK_NULL_HANDLE;

	private:
		// TODO: Could be its on class?
		void CreateSwapChain();
		SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);
		VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
		
		VkSwapchainKHR m_SwapChain;
		std::vector<VkImage> m_SwapChainImages;
		VkFormat m_SwapChainImageFormat;
		VkExtent2D m_SwapChainExtent;

	private:
		void CreateImageViews();
		std::vector<VkImageView> m_SwapChainImageViews;
	};
}