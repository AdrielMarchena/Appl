#include "WebGPUInstance.h"
#include <cassert>
#include <webgpu.h>

void WebGPUInstance::Create() {
    WGPUInstanceDescriptor desc = {};
    instance = wgpuCreateInstance(&desc);
    assert(instance);

    // Request adapter
    struct AdapterData { bool done = false; WGPUAdapter adapter = nullptr; } adapterData;
    auto onAdapter = [](WGPURequestAdapterStatus status, WGPUAdapter adapter, const char*, void* ud) {
        auto& d = *reinterpret_cast<AdapterData*>(ud);
        if (status == WGPURequestAdapterStatus_Success) d.adapter = adapter;
        d.done = true;
        };
    wgpuInstanceRequestAdapter(instance, nullptr, onAdapter, &adapterData);
    while (!adapterData.done) {}
    adapter = adapterData.adapter;

    // Request device
    struct DeviceData { bool done = false; WGPUDevice device = nullptr; } deviceData;
    auto onDevice = [](WGPURequestDeviceStatus status, WGPUDevice device, const char*, void* ud) {
        auto& d = *reinterpret_cast<DeviceData*>(ud);
        if (status == WGPURequestDeviceStatus_Success) d.device = device;
        d.done = true;
        };
    wgpuAdapterRequestDevice(adapter, nullptr, onDevice, &deviceData);
    while (!deviceData.done) {}

    device = deviceData.device;
    queue = wgpuDeviceGetQueue(device);
}

void WebGPUInstance::Clear() {
    if (device) { wgpuDeviceDestroy(device); device = nullptr; }
    if (adapter) { wgpuAdapterRelease(adapter); adapter = nullptr; }
    if (instance) { wgpuInstanceRelease(instance); instance = nullptr; }
}
