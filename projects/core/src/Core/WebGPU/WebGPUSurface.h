#pragma once
#include <webgpu.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <memory>
#include "WebGPUInstance.h"

class WebGPUSurface {
public:
    WebGPUSurface(const std::shared_ptr<WebGPUInstance>& instance, GLFWwindow* window);
    ~WebGPUSurface();

    void Create();
    void Clear();

    WGPUSurface GetSurface() const { return surface; }
    WGPUSurfaceConfiguration GetConfig() const { return config; }

private:
    std::shared_ptr<WebGPUInstance> m_Instance;
    GLFWwindow* m_Window = nullptr;
    WGPUSurface surface = nullptr;
    WGPUSurfaceConfiguration config = {};
};
