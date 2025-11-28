#pragma once
#include <webgpu.h>
#include <memory>
#include "WebGPUInstance.h"
#include "WebGPUSurface.h"
#include "WebGPUPipeline.h"

class WebGPUFramebuffer {
public:
    WebGPUFramebuffer(const std::shared_ptr<WebGPUInstance>& instance,
        const std::shared_ptr<WebGPUSurface>& surface,
        const std::shared_ptr<WebGPUPipeline>& pipeline);
    ~WebGPUFramebuffer();

    void Create();
    void Clear();
    void RenderFrame();

private:
    std::shared_ptr<WebGPUInstance> m_Instance;
    std::shared_ptr<WebGPUSurface> m_Surface;
    std::shared_ptr<WebGPUPipeline> m_Pipeline;
};
