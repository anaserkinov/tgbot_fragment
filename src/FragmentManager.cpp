#include "Fragment.hpp"
#include "FragmentManager.hpp"

FragmentManager::FragmentManager(Bot* bot) {
    this->bot = bot;
}

void FragmentManager::setFragmentFactory(const std::function<Fragment (int)>& createFragment) {
    this->createFragment = createFragment;
}

inline const Bot& FragmentManager::getBot() const {
    return *bot;
}

inline const Api& FragmentManager::getApi() const {
    return bot->getApi();
}

FragmentManager::~FragmentManager() {
}