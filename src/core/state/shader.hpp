#ifndef STATE_SHADER_HPP
#define STATE_SHADER_HPP

#include <state/state.hpp>
#include <command/rendercommands.hpp>

namespace sword
{

namespace state
{

constexpr const char* SHADER_DIR = "/home/michaelb/dev/sword/build/shaders/";

class LoadFragShaders : public LeafState
{
public:
    const char* getName() const override { return "load_frag_shaders"; }
    void handleEvent(event::Event*) override;
    virtual ~LoadFragShaders() = default;   
    LoadFragShaders(EditStack& es, CommandStack& cs, ReportCallbackFn callback) :
        LeafState{es, cs, callback} 
    {}
private:
    CommandPool<command::LoadFragShader> lfPool;
    void onEnterExt() override;
};

class LoadVertShaders : public LeafState
{
public:
    const char* getName() const override { return "load_vert_shaders"; }
    void handleEvent(event::Event*) override;
    virtual ~LoadVertShaders() = default;   
    LoadVertShaders(EditStack& es, CommandStack& cs, ReportCallbackFn callback) :
        LeafState{es, cs, callback} 
    {}
private:
    CommandPool<command::LoadVertShader> lvPool;
    void onEnterExt() override;
};

class ShaderManager final : public BranchState
{
public:
    enum class Op : Option {loadFrag, loadVert, printReports};
    constexpr Option opcast(Op op) {return static_cast<Option>(op);}
    constexpr Op opcast(Option op) {return static_cast<Op>(op);}
    const char* getName() const override { return "shader_manager"; }
    void handleEvent(event::Event*) override;
    virtual ~ShaderManager() = default;
    ShaderManager(EditStack& es, CommandStack& cs);
private:
    void printReports();
    LoadFragShaders loadFragShaders;
    LoadVertShaders loadVertShaders;

    std::vector<std::unique_ptr<ShaderReport>> shaderReports;
};

}; // namespace state

}; // namespace sword

#endif /* end of include guard: STATE_SHADER_HPP */
