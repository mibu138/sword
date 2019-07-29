#include "io.hpp"
#include "lib/lodepng.h"
#include "commander.hpp"
#include "swapchain.hpp"
#include "mem.hpp"

void saveSwapImage(
		MemoryManager& mm,
		Commander& commander,
		Swapchain& swapchain)
{
	int index = mm.createBuffer(
			swapchain.extent.width *
			swapchain.extent.height * 4,
			vk::BufferUsageFlagBits::eTransferDst);
	commander.copyImageToBuffer(
			swapchain.images[0],
			mm.bufferBlocks[index].buffer,
			swapchain.extent.width,
			swapchain.extent.height,
			1);
	std::cout << "Copied swap image to buffer" << std::endl;
	std::vector<u_int8_t> pngBuffer;
	lodepng::encode(
			pngBuffer, 
			static_cast<const unsigned char*>(mm.bufferBlocks[index].pHostMemory), 
			swapchain.extent.width, 
			swapchain.extent.height);
	std::cout << "Please give the image a name." << std::endl;
	std::string name = requestUserInput();
	std::string path = "out/" + name + ".png";
	lodepng::save_file(pngBuffer, path);
	std::cout << "Image saved to " << path << std::endl;
}

std::string requestUserInput()
{
	std::string word;
	std::cin >> word;
	return word;
}