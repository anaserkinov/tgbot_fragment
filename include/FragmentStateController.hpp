#ifndef FRAGMENT_STATE_CONTROLLER
#define FRAGMENT_STATE_CONTROLLER

#include <string>

struct FragmentState {
    int id;
};

class FragmentStateController {
public:
    void setState(int64_t userId, int fragmentId);
    FragmentState getState(int64_t userId);
};

#endif