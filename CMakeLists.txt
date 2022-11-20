
project(lachrymose)

add_library(lachrymose src/lms.c src/window.c src/renderer.c src/mesh.c src/shader.c src/texture.c src/framebuffer.c)

add_subdirectory(lib/glfw)
target_link_libraries(lachrymose glfw)

add_subdirectory(lib/glew)
target_link_libraries(lachrymose libglew_static)

add_subdirectory(lib/cglm)
target_link_libraries(lachrymose cglm)
