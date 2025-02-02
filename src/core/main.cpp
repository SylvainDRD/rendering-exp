#include <core/utils.h>
#include <renderer/vulkan/renderer.h>
#include <core/window/window.h>

int main(int argc, char **argv) {
    std::cout << "YAY" << std::endl;

    // TODO: refactor into an engine class that manages subsystems lifetime
    Window::Init();
    Renderer::Init();

    while(!Window::IsClosing()) {
        Window::Update();

        // TODO: game loop :)
    }

    // Cleanup
    Window::Release();
    Renderer::Release();

    return 0;
}