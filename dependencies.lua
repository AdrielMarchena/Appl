IncludeDirectories = {}

IncludeDirectories["GLFW"] = "%{wks.location}/vendors/glfw/include"
IncludeDirectories["Core"] = "%{wks.location}/projects/core/src"
IncludeDirectories["spdlog"] = "%{wks.location}/vendors/spdlog/include"
IncludeDirectories["glm"] = "%{wks.location}/vendors/glm/"
IncludeDirectories["glad"] = "%{wks.location}/vendors/glad/include"
IncludeDirectories["vulkan"] = "C:/VulkanSDK/1.4.328.1/Include"
IncludeDirectories["imgui"] = "%{wks.location}/vendors/imgui"
IncludeDirectories["entt"] = "%{wks.location}/vendors/entt/single_include"
IncludeDirectories.webgpu = "%{wks.location}/vendor/wgpu/include"


LibraryDirectories = {}

LibraryDirectories["vulkan"] = "C:/VulkanSDK/1.4.328.1/Lib"
LibraryDirectories.webgpu = "%{wks.location}/vendor/wgpu/lib"