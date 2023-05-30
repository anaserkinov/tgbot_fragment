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

    void onAnyMessage(const Message message);

    void onCommand(const std::string& commandName);


    ~Fragment();
};

#endif