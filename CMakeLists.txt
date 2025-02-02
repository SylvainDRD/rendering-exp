cmake_minimum_required(VERSION 3.24)
project(rendering-exp VERSION 0.1.0 DESCRIPTION "Experimenting with rendering stuff")

set(source_files src/core/main.cpp 
                 src/renderer/vulkan/renderer.cpp
                 src/renderer/vulkan/texture/texture.cpp
                 src/renderer/vulkan/texture/texture_view.cpp
                 src/core/window/window.cpp)

set(binary rendering-exp)

find_package(Vulkan REQUIRED)
add_executable(${binary} ${source_files})

add_subdirectory(thirdparty/vk-bootstrap)
add_subdirectory(thirdparty/glfw)

target_include_directories(${binary} PRIVATE src
                                             ${Vulkan_INCLUDE_DIR}
                                             thirdparty/vk-bootstrap/src
                                             thirdparty/glfw/include)
target_link_libraries(${binary} PRIVATE ${Vulkan_LIBRARIES} 
                                        vk-bootstrap::vk-bootstrap
                                        glfw)

target_compile_features(${binary} PRIVATE cxx_std_20) 