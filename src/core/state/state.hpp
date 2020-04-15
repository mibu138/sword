#ifndef STATE_HPP_
#define STATE_HPP_

#include <command/commandtypes.hpp>
#include <state/report.hpp>
#include <state/editstack.hpp>
#include <types/stack.hpp>
#include <types/map.hpp>
#include <functional>
#include <bitset>
#include <event/event.hpp>
#include <command/vocab.hpp>

#define STATE_BASE(name) \
    void handleEvent(Event* event) override;\
    virtual const char* getName() const override {return name;}

namespace sword { namespace state { class State; }; };

namespace sword
{

//namespace event{ class Event;}
    
namespace state
{

using ReportCallbackFn = std::function<void(Report*)>;
using ExitCallbackFn = std::function<void()>;
using OptionMask = std::bitset<32>;
using Option = uint8_t;
using Optional = std::optional<Option>;

//constexpr bool isCommandLine(event::Event* event) { return event->getCategory() == event::Category::CommandLine;}
constexpr event::CommandLine* toCommandLine(event::Event* event) { return static_cast<event::CommandLine*>(event);}

class Vocab
{
public:
    void clear() { words.clear(); }
    void push_back(std::string word) { words.push_back(word); }
    void set( std::vector<std::string> strings) { words = strings; }
    void setMaskPtr( OptionMask* ptr ) { mask = ptr; }
    std::vector<std::string> getWords() const 
    {
        if (mask)
        {
            std::vector<std::string> wordsReturn;
            for (int i = 0; i < words.size(); i++) 
                if ((*mask)[i])
                    wordsReturn.push_back(words.at(i));
            return wordsReturn;
        }
        return words;
    }
    void print()
    {
        if (mask)
        {
            for (int i = 0; i < words.size(); i++) 
                if ((*mask)[i])
                    std::cout << words.at(i) << " ";
        }
        else
        {
            for (int i = 0; i < words.size(); i++) 
                std::cout << words.at(i) << " ";
        }
        std::cout << std::endl;
    }
private:
    OptionMask* mask;
    std::vector<std::string> words;
};

class State
{
public:
    virtual void handleEvent(event::Event* event) = 0;
    virtual const char* getName() const = 0;
    virtual ~State() = default;
    void onEnter();
    void onExit();
//    virtual std::vector<const Report*> getReports() const {return {};};
protected:
    State(CommandStack& cs) : cmdStack{cs} {}
    State(CommandStack& cs, ExitCallbackFn callback) : cmdStack{cs}, onExitCallback{callback} {}
//    State(CommandStack& cs, ReportCallbackFn callback) : cmdStack{cs}, reportCallback{callback} {}
//    State(EditStack& editStack, CommandStack& cmdStack) : stateEdits{editStack}, cmdStack{cmdStack}, vocab{cmdStack} {}
//    State(EditStack& editStack, CommandStack& cmdStack, ReportCallbackFn callback) : 
//        stateEdits{editStack}, cmdStack{cmdStack}, vocab{cmdStack}, reportCallback{callback} {}
    void pushCmd(CmdPtr ptr);
    void setVocab(std::vector<std::string> strings);
    void clearVocab() { vocab.clear(); }
    void addToVocab(std::string word) { vocab.push_back(word); }
    void updateVocab();
    void printVocab();
    void setVocabMask(OptionMask* mask) { vocab.setMaskPtr(mask); }
    std::vector<std::string> getVocab();
//    inline static Command::Pool<Command::RefreshState> refreshPool{10};
private:
    CommandPool<command::UpdateVocab> uvPool{1};
    CommandPool<command::PopVocab> pvPool{1};
    CommandPool<command::AddVocab> avPool{1};
    Vocab vocab;
    CommandStack& cmdStack;
    ExitCallbackFn onExitCallback{nullptr};
    virtual void onEnterImp();
    virtual void onExitImp();
    virtual void onEnterExt() {}
    virtual void onExitExt() {}
};

//TODO: we need to make leaf state all consuming of events and all silencing
class LeafState : public State
{
public:
    ~LeafState() = default;
protected:
    LeafState(EditStack& es, CommandStack& cs) :
        State{cs}, editStack{es} {}
    LeafState(EditStack& es, CommandStack& cs, ReportCallbackFn callback) :
        State{cs}, editStack{es}, reportCallback{callback} {}
    void popSelf() { editStack.popState(); }
    ReportCallbackFn reportCallback{nullptr};

    template<typename R>
    R* findReport(const std::string& name, const std::vector<std::unique_ptr<R>>& reports)
    {
        for (const auto& r : reports) 
        {
            if (r->getObjectName() == name)
                return r.get();
        }
        return nullptr;
    }
private:
    CommandPool<command::SetVocab> svPool{1};
    void onExitImp() override final;
    void onEnterImp() override final;
    virtual void onEnterExt() override {}
    virtual void onExitExt() override {}
    EditStack& editStack;
};

//TODO: make the exit callback a requirement for branch states
//      and make Director a special state that does not require it (or just make it null)
class BranchState : public State
{
friend class Director;
public:
    ~BranchState() = default;
    template<typename R>
    void addReport(Report* ptr, std::vector<std::unique_ptr<R>>* derivedReports)
    {
        auto derivedPtr = dynamic_cast<R*>(ptr); 
        if (derivedPtr)
            derivedReports->emplace_back(derivedPtr);
        else
        {
            std::cout << "Bad report pointer passed." << std::endl;
            delete ptr;
        }
    }
protected:
    using Element = std::pair<std::string, Option>;
    BranchState(EditStack& es, CommandStack& cs,
            std::initializer_list<Element> ops) :
        State{cs}, editStack{es}, options{ops} 
    { 
        setVocab(options.getStrings());
        setVocabMask(&topMask); 
    }
    BranchState(EditStack& es, CommandStack& cs, ExitCallbackFn cb,
            std::initializer_list<Element> ops) :
        State{cs, cb}, editStack{es}, options{ops} 
    {
        setVocab(options.getStrings());
        setVocabMask(&topMask);
    }
    void pushState(State* state);
    Optional extractCommand(event::Event*);
    void activate(Option op) { topMask.set(op); }
    void deactivate(Option op) { topMask.reset(op); }
    void updateActiveVocab();
//    void deactivateVocal(Option op) { deactivate(op); setActiveVocab(); }
//    void activateVocal(Option op) { activate(op); updateActiveVocab(); }

private:
//    void onEnterExt() override { setActiveVocab(); }
//    void setActiveVocab();
//    void filterOutVocab();
    OptionMask topMask;
    std::vector<const Report*> reports;
    SmallMap<std::string, Option> options;
    EditStack& editStack;
};

}; //state

}; //sword

#endif /* end of include guard: STATE_HPP_ */
