#include "FragmentManager.hpp"

#include "Fragment.hpp"

FragmentManager::FragmentManager(Bot* bot) {
    this->bot = bot;
}

void FragmentManager::setFragmentFactory(const std::function<Fragment*(int)>& createFragment) {
    this->createFragment = createFragment;
}

inline const Bot& FragmentManager::getBot() const {
    return *bot;
}

inline const Api& FragmentManager::getApi() const {
    return bot->getApi();
}

Fragment FragmentManager::presentFragment(int id) const {
    Fragment* fragment = nullptr;

    for (int i = 0; i < 20; i++) {
        if (fragments[i] != nullptr && id == fragments[i]->fragmentId) {
            fragment = fragments[i];
            if (i != 0) {
                Fragment* f = fragments[0];
                fragments[0] = fragment;
                fragments[i] = f;
            }
            break;
        }
    }

    if (fragment == nullptr) {
        fragment = createFragment(id);

        for (int i = 0; i < 20; i++) {
            if (fragments[i] == nullptr) {
                fragments[i] = fragment;
                if (i != 0) {
                    Fragment* f = fragments[0];
                    fragments[0] = fragment;
                    fragments[i] = f;
                }
                break;
            }
        }
    }

    return *fragment;
}

FragmentManager::~FragmentManager() {
    for (int i = 0; i < 20; ++i) {
        if (fragments[i] != nullptr) {
            delete fragments[i];
            fragments[i] = nullptr;
        }
    }
    delete[] fragments;
}