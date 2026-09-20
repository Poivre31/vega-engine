// arget_include_directories(vendor INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/stb-image")

// target_compile_definitions(vendor INTERFACE STB_IMAGE_IMPLEMENTATION)
// # END STB

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#define VMA_IMPLEMENTATION
#include "vk_mem_alloc.h"