#include "FragmentManager.hpp"

#include "Fragment.hpp"
#include "iostream"

FragmentManager::FragmentManager(Bot* bot) {
    this->bot = bot;
}

void FragmentManager::setFragmentFactory(const std::function<std::shared_ptr<Fragment>(int)>& createFragment) {
    this->createFragment = createFragment;
}

Bot& FragmentManager::getBot() {
    return *bot;
}

const Api& FragmentManager::getApi() {
    return bot->getApi();
}

std::shared_ptr<Fragment> FragmentManager::presentFragment(int id, int16_t type, const std::shared_ptr<void>& data) {
    std::shared_ptr<Fragment> f = createFragment(id);
    f->setFragmentManager(this);
    f->onCreate(type, data);
    return f;
}

std::shared_ptr<Fragment> FragmentManager::getFragment(int64_t userId) {
    auto fragmentState = stateController.getState(userId);
    std::cout << "fragmentState: " << fragmentState.id << "\n";
    std::shared_ptr<Fragment> f = createFragment(fragmentState.id);
    f->setFragmentManager(this);
    return f;
}

void FragmentManager::onAnyMessage(const Message::Ptr& message) {
    getFragment(message->from->id)->onAnyMessage(message);
}

void FragmentManager::onNonCommandMessage(const Message::Ptr& message) {
    getFragment(message->from->id)->onNonCommandMessage(message);
}

void FragmentManager::onCommand(const Message::Ptr& message) {
    getFragment(message->from->id)->onCommand(message);
}

void FragmentManager::onCallbackQuery(const CallbackQuery::Ptr& callbackQuery) {
    getFragment(callbackQuery->from->id)->onCallbackQuery(callbackQuery);
}

FragmentManager::~FragmentManager() {
}