#ifndef FRAGMENT_MANAGER_HPP
#define FRAGMENT_MANAGER_HPP

#include "Api.h"
#include "Bot.h"
#include "Fragment.hpp"

using namespace TgBot;

class Fragment;

class FragmentManager {
private:
    Bot* bot = nullptr;
    std::function<Fragment (int)> createFragment;

public:

    FragmentManager(Bot* bot);

    void setFragmentFactory(const std::function<Fragment (int)>& createFragment);

    inline const Bot& getBot() const;

    inline const Api& getApi() const;

    ~FragmentManager();
};

#endif
