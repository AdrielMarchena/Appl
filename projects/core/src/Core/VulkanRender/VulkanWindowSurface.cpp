#include "VulkanWindowSurface.h"

#include "Core/application/Application.h"

#include <memory>
#include <stdexcept>

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <vulkan/vulkan_win32.h>
#include "VulkanInstance.h"
#include <vulkan/vulkan_core.h>

namespace Core::Vulkan {
	VulkanWindowSurface::VulkanWindowSurface(std::shared_ptr<VulkanInstance>& instance)
		:m_VulkanInstance(instance)
	{
		CreateWindowSurface();
	}

	VulkanWindowSurface::~VulkanWindowSurface()
	{
		CleanUp();
	}

	void VulkanWindowSurface::CleanUp()
	{
		if (m_VulkanInstance && m_Surface) {
			vkDestroySurfaceKHR(m_VulkanInstance->GetInstance(), m_Surface, nullptr);
			m_Surface = VK_NULL_HANDLE;
		}
	}

	void VulkanWindowSurface::CreateWindowSurface()
	{
		auto& app = Application::Get();
		auto windowHandle = app.GetWindow()->GetHandle();

		VkWin32SurfaceCreateInfoKHR createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
		createInfo.hwnd = glfwGetWin32Window(windowHandle);
		createInfo.hinstance = GetModuleHandle(nullptr);

		if (vkCreateWin32SurfaceKHR(m_VulkanInstance->GetInstance(), &createInfo, nullptr, &m_Surface) != VK_SUCCESS) {
			throw std::runtime_error("failed to create window surface! vkCreateWin32SurfaceKHR");
		}

		if (glfwCreateWindowSurface(m_VulkanInstance->GetInstance(), windowHandle, nullptr, &m_Surface) != VK_SUCCESS) {
			throw std::runtime_error("failed to create window surface! glfwCreateWindowSurface");
		}
	}
}
