#include "FragmentManager.hpp"

#include "Fragment.hpp"

FragmentManager::FragmentManager(Bot* bot) {
    this->bot = bot;
}

void FragmentManager::setFragmentFactory(const std::function<Fragment*(int)>& createFragment) {
    this->createFragment = createFragment;
}

inline const Bot& FragmentManager::getBot() {
    return *bot;
}

inline const Api& FragmentManager::getApi() {
    return bot->getApi();
}

Fragment* FragmentManager::presentFragment(int id) {
    int count = fragments.size();
    for (int i = 0; i < count; i++) {
        if (id == fragments.at(i)->fragmentId) {
            return fragments.at(i);
            break;
        }
    }

    Fragment* f = createFragment(id);
    f->setFragmentManager(this);
    fragments.push_back(f);
    return f;
}

void FragmentManager::onAnyMessage(int fragmentId, const Message::Ptr& message) {
    presentFragment(fragmentId)->onAnyMessage(message);
}

void FragmentManager::onCommand(int fragmentId, const Message::Ptr& message) {
    presentFragment(fragmentId)->onCommand(message);
}

FragmentManager::~FragmentManager() {
    int count = fragments.size();
    for (size_t i = 0; i < count; i++){
        delete fragments.at(i);
    }
    
    fragments.clear();
}