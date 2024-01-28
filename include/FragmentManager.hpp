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
    std::function<std::shared_ptr<Fragment>(int)> createFragment;

    std::shared_ptr<Fragment> getFragment(int64_t userId);

   public:
    FragmentStateController stateController;

    FragmentManager(Bot* bot);

    void setFragmentFactory(const std::function<std::shared_ptr<Fragment>(int)>& createFragment);

    Bot& getBot();

    const Api& getApi();

    std::shared_ptr<Fragment> presentFragment(int id, int16_t type, const std::shared_ptr<void>& data);

    void onAnyMessage(const Message::Ptr& message);

    void onNonCommandMessage(const Message::Ptr& message);

    void onCommand(const Message::Ptr& message);

    void onCallbackQuery(const CallbackQuery::Ptr& callbackQuery);

    ~FragmentManager();
};

#endif