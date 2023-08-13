#ifndef FRAGMENT
#define FRAGMENT

#include "Api.h"
#include "math.h"
#include "types/Message.h"
#include "vector"

using namespace TgBot;

class FragmentManager;

class Fragment {
    FragmentManager* fragmentManager = nullptr;

   protected:
    void placeKeyboards(
        const std::vector<std::string>& source,
        std::vector<std::vector<std::string>>& output,
        size_t column) {
        size_t sSize = source.size();
        size_t index = 0;

        while (index != sSize) {
            size_t c = std::min(sSize - index, column);
            std::vector<std::string> v;
            for (size_t i = 0; i < c; i++) {
                v.push_back(source[index + i]);
            }
            output.push_back(v);
            index += c;
        }
    }

    ReplyKeyboardMarkup::Ptr& createKeyboard(const std::vector<std::vector<std::string>>& buttonLayout, ReplyKeyboardMarkup::Ptr& kb) {
        for (size_t i = 0; i < buttonLayout.size(); ++i) {
            std::vector<KeyboardButton::Ptr> row;
            for (size_t j = 0; j < buttonLayout[i].size(); ++j) {
                auto button = std::make_shared<KeyboardButton>();
                button->text = buttonLayout[i][j];
                row.push_back(button);
            }
            kb->keyboard.push_back(row);
        }
        return kb;
    }

    ReplyKeyboardMarkup::Ptr& createKeyboard(
        const std::string& buttonLayout,
        ReplyKeyboardMarkup::Ptr& kb) {
        std::vector<KeyboardButton::Ptr> row;
        auto button = std::make_shared<KeyboardButton>();
        button->text = buttonLayout;
        row.push_back(button);
        kb->resizeKeyboard = true;
        kb->keyboard.push_back(row);
        return kb;
    }

    ReplyKeyboardMarkup::Ptr& addButton(
        ReplyKeyboardMarkup::Ptr& kb,
        KeyboardButton::Ptr& button) {
        std::vector<KeyboardButton::Ptr> row;
        row.push_back(button);
        kb->keyboard.push_back(row);
        return kb;
    }

   public:
    int fragmentId;

    Fragment(int id);

    Bot& getBot();
    const Api& getApi();

    void setFragmentManager(FragmentManager* fm);

    std::shared_ptr<Fragment> presentFragment(int id, const Message::Ptr lastMessage) const;

    virtual void onCreate(const Message::Ptr& lastMessage){};

    Message::Ptr sendMessage(boost::variant<std::int64_t, std::string> chatId,
                             const std::string& text,
                             bool disableWebPagePreview = false,
                             std::int32_t replyToMessageId = 0,
                             GenericReply::Ptr replyMarkup = nullptr,
                             const std::string& parseMode = "",
                             bool disableNotification = false,
                             const std::vector<MessageEntity::Ptr>& entities = std::vector<MessageEntity::Ptr>(),
                             bool allowSendingWithoutReply = false,
                             bool protectContent = false,
                             std::int32_t messageThreadId = 0);

    virtual void onAnyMessage(const Message::Ptr& message){};

    virtual void onNonCommandMessage(const Message::Ptr& message){};

    virtual void onCommand(const Message::Ptr& message){};

    ~Fragment();
};

#endif