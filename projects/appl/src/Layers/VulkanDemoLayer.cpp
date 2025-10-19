#include "VulkanDemoLayer.h"
#include <memory>
#include <Core/VulkanRender/VulkanInstance.h>
#include <Core/VulkanRender/VulkanDevices.h>
#include <Core/VulkanRender/VulkanWindowSurface.h>

VulkanDemoLayer::VulkanDemoLayer()
{
	m_VulkanInstance = std::make_shared<Core::Vulkan::VulkanInstance>();
	m_VulkanInstance->CreateInstance();
	m_VulkanInstance->PrintExtensions();

	m_VulkanWindowSurface = std::make_shared<Core::Vulkan::VulkanWindowSurface>(m_VulkanInstance);

	m_VulkanDevices = std::make_shared<Core::Vulkan::VulkanDevices>(m_VulkanInstance, m_VulkanWindowSurface);
}

VulkanDemoLayer::~VulkanDemoLayer()
{
	m_VulkanInstance->CleanUp();
	m_VulkanDevices->CleanUp();
}

void VulkanDemoLayer::OnEvent(Core::Event& event)
{
}

void VulkanDemoLayer::OnUpdate(float ts)
{
}

void VulkanDemoLayer::OnRender()
{
}
