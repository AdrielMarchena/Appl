#pragma once
#include <webgpu.h>
#include <memory>
#include "WebGPUInstance.h"
#include "WebGPUSurface.h"

class WebGPUPipeline {
public:
    WebGPUPipeline(const std::shared_ptr<WebGPUInstance>& instance,
        const std::shared_ptr<WebGPUSurface>& surface);
    ~WebGPUPipeline();

    void Create();
    void Clear();

    WGPURenderPipeline GetPipeline() const { return pipeline; }

private:
    std::shared_ptr<WebGPUInstance> m_Instance;
    std::shared_ptr<WebGPUSurface> m_Surface;
    WGPURenderPipeline pipeline = nullptr;
};
