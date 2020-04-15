#ifndef RENDER_COMMAND_HPP
#define RENDER_COMMAND_HPP

#include <vulkan/vulkan.hpp>

namespace sword
{

namespace render
{

class CommandBuffer; //forward declaratiohn

class CommandPool
{
friend class CommandBuffer;
public:
    CommandPool(
        const vk::Device&, 
        const vk::Queue&,
        uint32_t queueFamilyIndex, 
        vk::CommandPoolCreateFlags = {}); //empty flags by default
    virtual ~CommandPool();
    CommandPool(CommandPool&&);
    CommandPool(const CommandPool&) = delete;
    CommandPool& operator=(CommandPool&&) = delete;
    CommandPool& operator=(const CommandPool&) = delete;
    CommandBuffer& requestCommandBuffer(
    vk::CommandBufferLevel = vk::CommandBufferLevel::ePrimary);
    void resetPool();

private:
    const vk::Device& device;
    const vk::Queue& queue;
    vk::CommandPool handle;
    std::vector<std::unique_ptr<CommandBuffer>> primaryCommandBuffers;
    uint32_t activePrimaryCommandBufferCount;
};

class CommandBuffer
{
public: 
    CommandBuffer(
        CommandPool& pool, 
        vk::CommandBufferLevel level = vk::CommandBufferLevel::ePrimary);
    virtual ~CommandBuffer();
    CommandBuffer(const CommandBuffer&) = delete;
    CommandBuffer& operator=(CommandBuffer&) = delete;
    CommandBuffer& operator=(CommandBuffer&&) = delete;
    CommandBuffer(CommandBuffer&&);
    
    void begin();
    void beginRenderPass(vk::RenderPassBeginInfo&);
    void bindGraphicsPipeline(const vk::Pipeline& pipeline);
    void bindDescriptorSets(
    const vk::PipelineLayout& layout, 
    const std::vector<vk::DescriptorSet>& sets, 
    const std::vector<uint32_t>& offsets);
    void drawVerts(uint32_t vertCount, uint32_t firstVertex);
    void insertImageMemoryBarrier(
    vk::PipelineStageFlags srcStageMask,
    vk::PipelineStageFlags dstStageMask,
    vk::ImageMemoryBarrier imb);
    void copyImageToBuffer(vk::Image&, vk::Buffer&, vk::BufferImageCopy);
    void endRenderPass();
    void end();
    vk::Semaphore submit(vk::Semaphore& waitSemaphore, vk::PipelineStageFlags);
    void submit();
    bool isRecorded() const;
    void waitForFence() const;
    void reset();
private:
    CommandPool& pool;
    const vk::Device& device;
    const vk::Queue& queue;
    std::vector<vk::CommandBuffer> buffers;
    vk::CommandBuffer handle;
    vk::Semaphore signalSemaphore;
    vk::Fence fence;
    bool recordingComplete{false};
};

}; // namespace render

}; // namespace sword
	 
#endif /* end of include guard: RENDER_COMMAND_HPP */

