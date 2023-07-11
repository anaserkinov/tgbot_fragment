#ifndef FRAGMENT_MANAGER_HPP
#define FRAGMENT_MANAGER_HPP

#include <vector>

#include "Api.h"
#include "Bot.h"
#include "Fragment.hpp"
#include "FragmentStateController.hpp"

using namespace TgBot;

class Fragment;

class FragmentManager {
private:
    Bot* bot = nullptr;
    FragmentStateController fragmentStateController;
    // std::vector<Fragment*> fragments;
    std::function<std::shared_ptr<Fragment>(int)> createFragment;

    std::shared_ptr<Fragment> getFragment(int64_t userId);

public:
    FragmentManager(Bot* bot);

    void setFragmentFactory(const std::function<std::shared_ptr<Fragment>(int)>& createFragment);

    inline Bot& getBot();

    inline const Api& getApi();

    std::shared_ptr<Fragment> presentFragment(int id);

    void onAnyMessage(const Message::Ptr& message);

    void onNonCommandMessage(const Message::Ptr& message);

    void onCommand(const Message::Ptr& message);

    ~FragmentManager();
};

#endif