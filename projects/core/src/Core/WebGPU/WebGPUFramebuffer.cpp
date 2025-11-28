#include "WebGPUFramebuffer.h"
#include <GLFW/glfw3.h>

WebGPUFramebuffer::WebGPUFramebuffer(const std::shared_ptr<WebGPUInstance>& instance,
    const std::shared_ptr<WebGPUSurface>& surface,
    const std::shared_ptr<WebGPUPipeline>& pipeline)
    : m_Instance(instance), m_Surface(surface), m_Pipeline(pipeline) {
    Create();
}

WebGPUFramebuffer::~WebGPUFramebuffer() { Clear(); }

void WebGPUFramebuffer::Create() {}
void WebGPUFramebuffer::Clear() {}

void WebGPUFramebuffer::RenderFrame() {
    WGPUSurfaceTexture surfaceTex;
    wgpuSurfaceGetCurrentTexture(m_Surface->GetSurface(), &surfaceTex);
    if (surfaceTex.status != WGPUSurfaceGetCurrentTextureStatus_Success)
        return;

    WGPUTextureView view = wgpuTextureCreateView(surfaceTex.texture, nullptr);

    WGPURenderPassColorAttachment color = {};
    color.view = view;
    color.loadOp = WGPULoadOp_Clear;
    color.storeOp = WGPUStoreOp_Store;
    color.clearValue = { 0.1, 0.1, 0.1, 1.0 };

    WGPURenderPassDescriptor pass = {};
    pass.colorAttachmentCount = 1;
    pass.colorAttachments = &color;

    WGPUCommandEncoder enc = wgpuDeviceCreateCommandEncoder(m_Instance->GetDevice(), nullptr);
    WGPURenderPassEncoder rp = wgpuCommandEncoderBeginRenderPass(enc, &pass);
    wgpuRenderPassEncoderSetPipeline(rp, m_Pipeline->GetPipeline());
    wgpuRenderPassEncoderDraw(rp, 3, 1, 0, 0);
    wgpuRenderPassEncoderEnd(rp);

    WGPUCommandBuffer cmd = wgpuCommandEncoderFinish(enc, nullptr);
    wgpuQueueSubmit(m_Instance->GetQueue(), 1, &cmd);

    wgpuSurfacePresent(m_Surface->GetSurface());
    wgpuTextureViewRelease(view);
}
