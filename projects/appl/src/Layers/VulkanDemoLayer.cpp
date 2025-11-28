#include "VulkanDemoLayer.h"
#include <memory>
#include <Core/VulkanRender/VulkanInstance.h>
#include <Core/VulkanRender/VulkanDevices.h>
#include <Core/VulkanRender/VulkanWindowSurface.h>
#include <Core/VulkanRender/VulkanGraphicsPipeline.h>
#include <Core/application/Event.h>
#include <Core/VulkanRender/VulkanFramebuffers.h>
#include <Core/VulkanRender/VulkanCommanBuffers.h>
#include <vulkan/vulkan_core.h>

#include <stdexcept>
#include <cstdint>

VulkanDemoLayer::VulkanDemoLayer()
{
	m_VulkanInstance = std::make_shared<Core::Vulkan::VulkanInstance>();
	m_VulkanInstance->CreateInstance();
	m_VulkanInstance->PrintExtensions();

	m_VulkanWindowSurface = std::make_shared<Core::Vulkan::VulkanWindowSurface>(m_VulkanInstance);

	m_VulkanDevices = std::make_shared<Core::Vulkan::VulkanDevices>(m_VulkanInstance, m_VulkanWindowSurface);
	
	m_VulkanGraphicsPipeline = std::make_shared<Core::Vulkan::VulkanGraphicsPipeline>(m_VulkanDevices);

	m_VulkanFramebuffers = std::make_shared<Core::Vulkan::VulkanFramebuffers>(m_VulkanDevices, m_VulkanGraphicsPipeline);

	m_VulkanCommanBuffers = std::make_shared<Core::Vulkan::VulkanCommanBuffers>(m_VulkanDevices, m_VulkanFramebuffers,m_VulkanGraphicsPipeline);

	CreateSyncObjects();
}

VulkanDemoLayer::~VulkanDemoLayer()
{
	m_VulkanCommanBuffers->CleanUp();
	m_VulkanFramebuffers->CleanUp();
	m_VulkanGraphicsPipeline->CleanUp();

	vkDestroySemaphore(m_VulkanDevices->GetDevice(), m_ImageAvailableSemaphore, nullptr);
	vkDestroySemaphore(m_VulkanDevices->GetDevice(), m_RenderFinishedSemaphore, nullptr);
	vkDestroyFence(m_VulkanDevices->GetDevice(), m_InFlightFence, nullptr);
	
	m_VulkanDevices->CleanUp();
	m_VulkanWindowSurface->CleanUp();
	m_VulkanInstance->CleanUp();
}

void VulkanDemoLayer::OnEvent(Core::Event& event)
{
}

void VulkanDemoLayer::OnUpdate(float ts)
{
}

void VulkanDemoLayer::OnRender()
{
	auto* commandBuffer = m_VulkanCommanBuffers->GetCommandBufferRef();
	
	vkWaitForFences(m_VulkanDevices->GetDevice(), 1, &m_InFlightFence, VK_TRUE, UINT64_MAX);
	vkResetFences(m_VulkanDevices->GetDevice(), 1, &m_InFlightFence);

	uint32_t imageIndex;
	vkAcquireNextImageKHR(m_VulkanDevices->GetDevice(), m_VulkanDevices->GetSwapChain(), UINT64_MAX, m_ImageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);

	vkResetCommandBuffer(m_VulkanCommanBuffers->GetCommandBuffer(), 0);
	m_VulkanCommanBuffers->RecordCommandBuffer(m_VulkanCommanBuffers->GetCommandBuffer(), imageIndex);

	VkSubmitInfo submitInfo{};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	VkSemaphore waitSemaphores[] = { m_ImageAvailableSemaphore };
	VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = waitSemaphores;
	submitInfo.pWaitDstStageMask = waitStages;

	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = commandBuffer;

	VkSemaphore signalSemaphores[] = { m_RenderFinishedSemaphore };
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphores;

	if (vkQueueSubmit(m_VulkanDevices->GetGraphicsQueue(), 1, &submitInfo, m_InFlightFence) != VK_SUCCESS) {
		throw std::runtime_error("failed to submit draw command buffer!");
	}

	VkPresentInfoKHR presentInfo{};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = signalSemaphores;

	VkSwapchainKHR swapChains[] = { m_VulkanDevices->GetSwapChain() };
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapChains;
	presentInfo.pImageIndices = &imageIndex;

	presentInfo.pResults = nullptr; // Optional

	vkQueuePresentKHR(m_VulkanDevices->GetPresentQueue(), &presentInfo);
}

void VulkanDemoLayer::OnEndLoop()
{
	vkDeviceWaitIdle(m_VulkanDevices->GetDevice());
}

void VulkanDemoLayer::CreateSyncObjects()
{
	VkSemaphoreCreateInfo semaphoreInfo{};
	semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	VkFenceCreateInfo fenceInfo{};
	fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

	if (vkCreateSemaphore(m_VulkanDevices->GetDevice(), &semaphoreInfo, nullptr, &m_ImageAvailableSemaphore) != VK_SUCCESS ||
		vkCreateSemaphore(m_VulkanDevices->GetDevice(), &semaphoreInfo, nullptr, &m_RenderFinishedSemaphore) != VK_SUCCESS ||
		vkCreateFence(m_VulkanDevices->GetDevice(), &fenceInfo, nullptr, &m_InFlightFence) != VK_SUCCESS) {
		throw std::runtime_error("failed to create semaphores!");
	}
}
