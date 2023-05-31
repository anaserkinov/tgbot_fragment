#ifndef FRAGMENT
#define FRAGMENT

#include "Api.h"
#include "types/Message.h"

using namespace TgBot;

class FragmentManager;

class Fragment {
    FragmentManager* fragmentManager = nullptr;

protected:
    inline const Bot& getBot() const ;
    inline const Api& getApi() const;

public:
    int fragmentId;

    Fragment(int id);

    void setFragmentManager(FragmentManager* fm);

    Fragment presentFragment(int id) const;

    virtual void onAnyMessage(const Message::Ptr& message){};

    virtual void onCommand(const Message::Ptr& message){};

    ~Fragment();
};

#endif