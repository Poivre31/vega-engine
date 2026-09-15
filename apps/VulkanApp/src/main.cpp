#include <console/console.hpp>

int main() {
  auto console = console::create("Vulkan");
  console->info("Launched Vulkan app");
}