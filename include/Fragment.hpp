#ifndef FRAGMENT
#define FRAGMENT

#include "Api.h"
#include "types/Message.h"
#include "vector"

using namespace TgBot;

class FragmentManager;

class Fragment {
    FragmentManager* fragmentManager = nullptr;

protected:

    void createKeyboard(const std::vector<std::vector<std::string>>& buttonLayout, ReplyKeyboardMarkup::Ptr& kb) {
        for (size_t i = 0; i < buttonLayout.size(); ++i) {
            std::vector<KeyboardButton::Ptr> row;
            for (size_t j = 0; j < buttonLayout[i].size(); ++j) {
                KeyboardButton::Ptr button(new KeyboardButton);
                button->text = buttonLayout[i][j];
                row.push_back(button);
            }
            kb->keyboard.push_back(row);
        }
    }

    void createKeyboard(
            const std::vector<std::string>& buttonLayout,
            ReplyKeyboardMarkup::Ptr& kb) {
        std::vector<KeyboardButton::Ptr> row;
        for (size_t j = 0; j < buttonLayout.size(); ++j) {
            KeyboardButton::Ptr button(new KeyboardButton);
            button->text = buttonLayout[j];
            row.push_back(button);
        }
        kb->keyboard.push_back(row);
    }

    void createKeyboard(
            const std::string& buttonLayout,
            ReplyKeyboardMarkup::Ptr& kb) {
        std::vector<KeyboardButton::Ptr> row;
        KeyboardButton::Ptr button(new KeyboardButton);
        button->text = buttonLayout;
        row.push_back(button);
        kb->keyboard.push_back(row);
    }

public:
    int fragmentId;

    Fragment(int id);

    Bot& getBot();
    const Api& getApi();

    void setFragmentManager(FragmentManager* fm);

    std::shared_ptr<Fragment> presentFragment(int id) const;

    virtual void onCreate(){};

    virtual void onAnyMessage(const Message::Ptr& message){};

    virtual void onNonCommandMessage(const Message::Ptr& message){};

    virtual void onCommand(const Message::Ptr& message){};

    ~Fragment();
};

#endif