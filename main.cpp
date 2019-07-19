#include "swapchain.hpp"
#include "commander.hpp"
#include "painter.hpp"
#include <thread>
#include <chrono>

void paintLoop(
	Window window, 
	Painter painter, 
	Commander commander,
	Swapchain swapchain)
{
	while (true)
	{
		window.waitForEvent();
		painter.paint(window.mouseX, window.mouseY);
		commander.renderFrame(swapchain);
	}
}

int main(int argc, char *argv[])
{
	Context context;

	context.printDeviceMemoryTypeInfo();
	context.printDeviceMemoryHeapInfo();

	Window window;
	window.open();
	window.waitForEvent();

	Swapchain swapchain(context, window);

	Painter painter(swapchain);

	Commander commander(context);

	painter.prepare();

	swapchain.prepareForRender();
	commander.initializeCommandBuffers(swapchain, painter);
	
	paintLoop(window, painter, commander, swapchain);

	commander.renderFrame(swapchain);
	window.waitForEvent();

	commander.cleanUp();
	
	std::cout << std::bitset<32>(UINT32_MAX) << std::endl;
	return 0;
}
