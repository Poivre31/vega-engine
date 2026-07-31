#include <console/console.h>

int main() {
    auto console = console::create("Vulkan");
    console->info("Launched Vulkan app");
}