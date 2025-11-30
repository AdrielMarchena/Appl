#include <new>

#include <string>
#include "Core/application/Application.h"

#include "Layers/DemoLayer.h"
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
	appSpecifications.WindowSpec.Api = Core::GraphicApi::RAYLIB;

	Core::Application* app = new Core::Application(appSpecifications);
	app->PushLayer<DemoLayer>();
	app->Run();
	delete app;
}