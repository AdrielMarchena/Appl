#pragma once

// Example usage of RayLib integration:
//
// #include "Core/application/Window.h"
// #include "Core/RayLibRender/RayLibRenderer.h"
//
// int main()
// {
//     // Create window with RayLib API
//     Core::WindowSpecification spec;
//     spec.Title = "RayLib Example";
//     spec.Width = 800;
//     spec.Height = 600;
//     spec.Api = Core::GraphicApi::RAYLIB;
//     spec.VSync = true;
//     
//     Core::Window window(spec);
//     window.Create();
//     
//     // Create renderer
//     Core::RayLibRenderer renderer;
//     
//     // Main loop
//     while (!window.ShouldClose())
//     {
//         renderer.BeginRender();
//         renderer.ClearScreen(Core::Color(100, 149, 237, 255)); // Cornflower blue
//         
//         // Your rendering code here...
//         
//         renderer.EndRender();
//         window.Update();
//     }
//     
//     return 0;
// }
