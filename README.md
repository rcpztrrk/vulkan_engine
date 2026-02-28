# Vulkan Engine

A modular 3D graphics and physics engine built with C++ and Vulkan API.

## Project Overview

This project focuses on developing a high-performance graphics and physics engine. The current implementation uses an Entity Component System (ECS) architecture for efficient object management and a custom physics engine for dynamic simulations.

## Features

### Phase 5.5: Animation-to-Bake Bridge (In Progress)
- Animation pipeline preparation for deterministic playback.
- Shot authoring foundations (camera/light presets + scene snapshots).
- Bake-ready stylization preparation (pixel snap + palette preview workflow).

### Phase 5: Physics Engine (Completed)
- **Collision Shapes:** AABB and Sphere colliders integration (`ColliderComponent`).
- **Narrowphase Detection:** Mathematical intersection tests (`Sphere-Sphere`, `AABB-AABB`, `Sphere-AABB`).
- **Collision Response:** Prevent object sinking using Positional Correction (Linear Projection).
- **Impulse Resolution:** Instantaneous velocity changes to calculate realistic bouncy impacts.
- **Dynamic & Static Bodies:** Physics Engine correctly ignores collisions between static (infinite mass) objects while resolving dynamic ones.

### Phase 4: UI, Camera & Interaction (Completed)
- **ImGui Integration:** Debug and control panels for real-time engine monitoring.
- **Fly Camera:** Advanced 3D camera with mouse-look and WASD controls.
- **Input System:** Dedicated input manager with support for key-press events and state transitions.
- **Profiler:** Real-time performance monitoring (FPS and Frame Time) with graphical feedback.
- **Entity Inspector:** Interactive GUI to inspect and modify entity components (Transform, RigidBody, Tag) at runtime.
- **Sprint Mode:** Camera movement speed boosters.

### Phase 3: Textures and Model Loading
- **Depth Buffering:** Proper 3D depth perception.
- **Texture Mapping:** STB Image integration for texture support.
- **Model Loading:** TinyOBJLoader for .obj file parsing.
- **Indexed Drawing:** Optimized memory usage via index buffers.

### Phase 2: Transformations & Vertex Data
- Vertex and index buffer abstractions.
- Staging buffers for GPU memory transfers.
- Uniform Buffer Objects (UBO) for camera matrices.
- 3D Transformations using GLM.

### Phase 1: Core Infrastructure
- Vulkan 1.3 Instance and Device initialization.
- Validation Layers for debugging.
- Swapchain, Render Pass, and Framebuffer configuration.

## Requirements

- C++20 compatible compiler (e.g., MSVC 2022)
- Vulkan SDK (1.4+)
- CMake (3.20+)
- vcpkg for dependency management

## Dependencies

- GLFW (Windowing and Input)
- GLM (Mathematics)
- spdlog (Logging)
- EnTT (ECS)
- stb_image (Texture Loading)
- tinyobjloader (OBJ Parsing)

## Building the Project

1. Clone the repository.
2. Ensure vcpkg is installed and integrated.
3. Run the following commands:

```bash
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=[path-to-vcpkg]/scripts/buildsystems/vcpkg.cmake
cmake --build build --config Debug
```

## License

This project is licensed under the MIT License.
