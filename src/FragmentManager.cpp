#include "FragmentManager.hpp"

#include "Fragment.hpp"

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

std::shared_ptr<Fragment> FragmentManager::presentFragment(int id) {
    // int count = fragments.size();
    // for (int i = 0; i < count; i++) {
    //     if (id == fragments.at(i)->fragmentId) {
    //         return fragments.at(i);
    //         break;
    //     }
    // }

    std::shared_ptr<Fragment> f = createFragment(id);
    f->setFragmentManager(this);
    f->onCreate();

    // fragments.push_back(f);
    return f;
}

std::shared_ptr<Fragment> FragmentManager::getFragment(int64_t userId) {
    auto fragmentState = fragmentStateController.getState(userId);
    std::shared_ptr<Fragment> f = createFragment(fragmentState.id);
    f->setFragmentManager(this);
    return f;
}

void FragmentManager::onAnyMessage(const Message::Ptr& message) {
    getFragment(message->from->id)->onAnyMessage(message);
}

void FragmentManager::onNonCommandMessage(const Message::Ptr& message) {
    getFragment(message->from->id)->onAnyMessage(message);
}

void FragmentManager::onCommand(const Message::Ptr& message) {
    
    getFragment(message->from->id)->onCommand(message);
}

FragmentManager::~FragmentManager() {
    // int count = fragments.size();
    // for (size_t i = 0; i < count; i++){
    //     delete fragments.at(i);
    // }

    // fragments.clear();
}