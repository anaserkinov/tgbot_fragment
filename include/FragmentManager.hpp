#ifndef FRAGMENT_MANAGER_HPP
#define FRAGMENT_MANAGER_HPP

#include <vector>

#include "Api.h"
#include "Bot.h"
#include "Fragment.hpp"

using namespace TgBot;

class Fragment;

class FragmentManager {
private:
    Bot* bot = nullptr;
    std::vector<Fragment*> fragments;
    std::function<Fragment*(int)> createFragment;

public:
    FragmentManager(Bot* bot);

    void setFragmentFactory(const std::function<Fragment*(int)>& createFragment);

    inline const Bot& getBot();

    inline const Api& getApi();

    Fragment* presentFragment(int id);

    void onAnyMessage(int fragmentId, const Message::Ptr& message);

    void onCommand(int fragmentId, const Message::Ptr& message);

    ~FragmentManager();
};

#endif
