#include "WebGPUPipeline.h"

static const char* vShader = R"(
@vertex
fn main(@builtin(vertex_index) VertexIndex : u32)
     -> @builtin(position) vec4f {
    var pos = array<vec2f, 3>(
        vec2f(0.0, 0.5),
        vec2f(-0.5, -0.5),
        vec2f(0.5, -0.5)
    );
    return vec4f(pos[VertexIndex], 0.0, 1.0);
}
)";
static const char* fShader = R"(
@fragment
fn main() -> @location(0) vec4f {
    return vec4f(1.0, 0.0, 0.0, 1.0);
}
)";

WebGPUPipeline::WebGPUPipeline(const std::shared_ptr<WebGPUInstance>& instance,
    const std::shared_ptr<WebGPUSurface>& surface)
    : m_Instance(instance), m_Surface(surface) {
    Create();
}

WebGPUPipeline::~WebGPUPipeline() { Clear(); }

void WebGPUPipeline::Create() {
    WGPUShaderModuleWGSLDescriptor vdesc = {};
    vdesc.chain.sType = WGPUSType_ShaderModuleWGSLDescriptor;
    vdesc.source = vShader;
    WGPUShaderModuleDescriptor vertDesc = {};
    vertDesc.nextInChain = reinterpret_cast<WGPUChainedStruct*>(&vdesc);
    WGPUShaderModule vmod = wgpuDeviceCreateShaderModule(m_Instance->GetDevice(), &vertDesc);

    WGPUShaderModuleWGSLDescriptor fdesc = {};
    fdesc.chain.sType = WGPUSType_ShaderModuleWGSLDescriptor;
    fdesc.source = fShader;
    WGPUShaderModuleDescriptor fragDesc = {};
    fragDesc.nextInChain = reinterpret_cast<WGPUChainedStruct*>(&fdesc);
    WGPUShaderModule fmod = wgpuDeviceCreateShaderModule(m_Instance->GetDevice(), &fragDesc);

    WGPUColorTargetState colorTarget = {};
    colorTarget.format = m_Surface->GetConfig().format;

    WGPUFragmentState frag = {};
    frag.module = fmod;
    frag.entryPoint = "main";
    frag.targetCount = 1;
    frag.targets = &colorTarget;

    WGPUVertexState vert = {};
    vert.module = vmod;
    vert.entryPoint = "main";

    WGPUPipelineLayoutDescriptor layoutDesc = {};
    WGPUPipelineLayout layout = wgpuDeviceCreatePipelineLayout(m_Instance->GetDevice(), &layoutDesc);

    WGPURenderPipelineDescriptor desc = {};
    desc.layout = layout;
    desc.vertex = vert;
    desc.fragment = &frag;
    desc.primitive.topology = WGPUPrimitiveTopology_TriangleList;

    pipeline = wgpuDeviceCreateRenderPipeline(m_Instance->GetDevice(), &desc);

    wgpuPipelineLayoutRelease(layout);
    wgpuShaderModuleRelease(vmod);
    wgpuShaderModuleRelease(fmod);
}

void WebGPUPipeline::Clear() {
    if (pipeline) {
        wgpuRenderPipelineRelease(pipeline);
        pipeline = nullptr;
    }
}
