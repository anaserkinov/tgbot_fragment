#include "Fragment.hpp"

#include "FragmentManager.hpp"

Fragment::Fragment(int id) {
}

Bot& Fragment::getBot() {
    return fragmentManager->getBot();
}

const Api& Fragment::getApi() {
    return fragmentManager->getApi();
}

std::shared_ptr<Fragment> Fragment::presentFragment(int id) const {
    return fragmentManager->presentFragment(id);
}

void Fragment::setFragmentManager(FragmentManager* fm) {
    fragmentManager = fm;
}

Fragment::~Fragment() {
}