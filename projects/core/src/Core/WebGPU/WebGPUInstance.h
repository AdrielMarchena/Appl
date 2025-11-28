#pragma once
#include <webgpu.h>
#include <memory>
#include <iostream>

class WebGPUInstance {
public:
    WebGPUInstance() { Create(); }
    ~WebGPUInstance() { Clear(); }

    void Create();
    void Clear();

    WGPUInstance GetInstance() const { return instance; }
    WGPUDevice GetDevice() const { return device; }
    WGPUQueue GetQueue() const { return queue; }
    WGPUAdapter GetAdapter() const { return adapter; }

private:
    WGPUInstance instance = nullptr;
    WGPUAdapter adapter = nullptr;
    WGPUDevice device = nullptr;
    WGPUQueue queue = nullptr;
};
