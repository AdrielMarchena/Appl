#pragma once

namespace Core {

	class ImGuiContext
	{
	public:
		static void Init(void* windowHandle);
		static void Shutdown();
		static void NewFrame();
		static void Render();
	};

}
