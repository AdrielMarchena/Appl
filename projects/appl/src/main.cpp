#include <new>

#include <string>
#include "Core/application/Application.h"

#include "Layers/VulkanDemoLayer.h"
#include <Core/GraphicApiEnum.h>

int main(int argc, char** argv)
{
	Core::ApplicationSpecification appSpecifications;

	appSpecifications.Name = "Vulkan";

	appSpecifications.WindowSpec.Title = "Titulo da minha janela";
	appSpecifications.WindowSpec.IsResizeable = true;
	appSpecifications.WindowSpec.VSync = false;
	appSpecifications.WindowSpec.Width = 1920;
	appSpecifications.WindowSpec.Height = 1080;
	appSpecifications.WindowSpec.GraphicApi = Core::GraphicApi::VULKAN;

	Core::Application* app = new Core::Application(appSpecifications);
	app->PushLayer<VulkanDemoLayer>();
	app->Run();
	delete app;
}