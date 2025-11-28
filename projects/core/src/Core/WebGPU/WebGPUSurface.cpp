#include "WebGPUSurface.h"
#include <webgpu.h>

WebGPUSurface::WebGPUSurface(const std::shared_ptr<WebGPUInstance>& instance, GLFWwindow* window)
    : m_Instance(instance), m_Window(window) {
    Create();
}

WebGPUSurface::~WebGPUSurface() { Clear(); }

void WebGPUSurface::Create() {
#ifdef _WIN32
    WGPUSurfaceDescriptorFromWindowsHWND hwndDesc = {};
    hwndDesc.chain.sType = WGPUSType_SurfaceDescriptorFromWindowsHWND;
    hwndDesc.hinstance = GetModuleHandle(nullptr);
    hwndDesc.hwnd = glfwGetWin32Window(m_Window);

    WGPUSurfaceDescriptor surfaceDesc = {};
    surfaceDesc.nextInChain = reinterpret_cast<WGPUChainedStruct*>(&hwndDesc);
    surface = wgpuInstanceCreateSurface(m_Instance->GetInstance(), &surfaceDesc);
#else
#error "Implement surface creation for other platforms"
#endif

    int w, h;
    glfwGetFramebufferSize(m_Window, &w, &h);

    config.width = w;
    config.height = h;
    config.device = m_Instance->GetDevice();
    config.format = wgpuSurfaceGetPreferredFormat(surface, m_Instance->GetAdapter());
    config.usage = WGPUTextureUsage_RenderAttachment;
    config.presentMode = WGPUPresentMode_Fifo;

    wgpuSurfaceConfigure(surface, &config);
}

void WebGPUSurface::Clear() {
    if (surface) {
        wgpuSurfaceUnconfigure(surface);
        wgpuSurfaceRelease(surface);
        surface = nullptr;
    }
}
