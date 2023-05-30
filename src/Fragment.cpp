#include "Fragment.hpp"

#include "FragmentManager.hpp"

Fragment::Fragment(int id) {
}

inline const Bot& Fragment::getBot() const {
    return fragmentManager->getBot();
}

inline const Api& Fragment::getApi() const {
    return fragmentManager->getApi();
}

Fragment Fragment::presentFragment(int id) const {
    return fragmentManager->presentFragment(id);
}

void Fragment::setFragmentManager(FragmentManager* fm) {
    fragmentManager = fm;
}

void Fragment::onAnyMessage(const Message message) {
}

void Fragment::onCommand(const std::string& commandName) {
}

Fragment::~Fragment() {
}