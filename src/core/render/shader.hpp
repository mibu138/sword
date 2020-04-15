#ifndef RENDER_SHADER_HPP_
#define RENDER_SHADER_HPP_

#include <vulkan/vulkan.hpp>

namespace sword
{

namespace render
{

struct SpecData
{
    float windowWidth{256};
    float windowHeight{256};
    int integer0{0};
    int integer1{0};
};

class Shader
{
public:
    virtual ~Shader();
    Shader(const Shader&) = delete; //no copy construction
    Shader(Shader&& other) = delete;
    Shader& operator=(Shader& other) = delete; //no copy assignment
    Shader& operator=(Shader&& other) = delete; //no move assignment

    const vk::PipelineShaderStageCreateInfo& getStageInfo() const;
    void setWindowResolution(const uint32_t w, const uint32_t h);

    SpecData specData;

protected:
    Shader(const vk::Device&, std::string filepath);
    vk::PipelineShaderStageCreateInfo stageInfo;
    std::vector<vk::SpecializationMapEntry> mapEntries;
    vk::SpecializationInfo specInfo;

private:
    const vk::Device& device;
    std::vector<char> shaderCode;
    size_t codeSize;
    vk::ShaderModule module{nullptr};

    void loadFile(std::string filepath);
    void createModule();
};

class VertShader : public Shader
{
public:
    VertShader(const vk::Device&, std::string);
};

class FragShader : public Shader
{
public:
    FragShader(const vk::Device&, std::string);
};


}; // namespace render

}; // namespace sword

#endif /* end of include guard: SHADER_HPP_ */