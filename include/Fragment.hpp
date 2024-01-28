#ifndef FRAGMENT
#define FRAGMENT

#include "Api.h"
#include "iostream"
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

    ReplyKeyboardMarkup::Ptr& createKeyboard(
        const std::vector<std::string>& source,
        ReplyKeyboardMarkup::Ptr& kb,
        size_t column) {
        size_t sSize = source.size();
        size_t index = 0;

        while (index != sSize) {
            size_t c = std::min(sSize - index, column);
            std::vector<KeyboardButton::Ptr> row;
            for (size_t i = 0; i < c; i++) {
                auto button = std::make_shared<KeyboardButton>();
                button->text = source[index + i];
                row.push_back(button);
            }
            kb->keyboard.push_back(row);
            index += c;
        }
        return kb;
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

    InlineKeyboardMarkup::Ptr& createInlineKeyboard(const std::vector<std::vector<std::string>>& buttonLayout, InlineKeyboardMarkup::Ptr& kb) {
        for (size_t i = 0; i < buttonLayout.size(); ++i) {
            std::vector<InlineKeyboardButton::Ptr> row;
            for (size_t j = 0; j < buttonLayout[i].size(); j += 2) {
                auto button = std::make_shared<InlineKeyboardButton>();
                button->text = buttonLayout[i][j];
                button->callbackData = buttonLayout[i][j + 1];
                row.push_back(button);
            }
            kb->inlineKeyboard.push_back(row);
        }
        return kb;
    }

    InlineKeyboardMarkup::Ptr& createInlineKeyboard(
        const std::string& buttonLayout,
        const std::string& buttonCallbackData,
        InlineKeyboardMarkup::Ptr& kb) {
        std::vector<InlineKeyboardButton::Ptr> row;
        auto button = std::make_shared<InlineKeyboardButton>();
        button->text = buttonLayout;
        button->callbackData = buttonCallbackData;
        row.push_back(button);
        kb->inlineKeyboard.push_back(row);
        return kb;
    }

    InlineKeyboardMarkup::Ptr& addInlineButton(
        InlineKeyboardMarkup::Ptr& kb,
        InlineKeyboardButton::Ptr& button) {
        std::vector<InlineKeyboardButton::Ptr> row;
        row.push_back(button);
        kb->inlineKeyboard.push_back(row);
        return kb;
    }

   public:
    static const int16_t MESSAGE = 0;
    static const int16_t CALLBACK_QUERY = 1;

    int fragmentId;

    Fragment(int id);

    Bot& getBot();
    const Api& getApi();

    void setFragmentManager(FragmentManager* fm);

    std::shared_ptr<Fragment> presentFragment(int id, int16_t type, const std::shared_ptr<void>& data) const;

    virtual void onCreate(int16_t type, const std::shared_ptr<void>& data);

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

    Message::Ptr editMessageText(const std::string& text,
                                 boost::variant<std::int64_t, std::string> chatId = 0,
                                 std::int32_t messageId = 0,
                                 const std::string& inlineMessageId = "",
                                 const std::string& parseMode = "",
                                 bool disableWebPagePreview = false,
                                 GenericReply::Ptr replyMarkup = nullptr,
                                 const std::vector<MessageEntity::Ptr>& entities = std::vector<MessageEntity::Ptr>()) const;

    bool deleteMessage(
        boost::variant<std::int64_t, std::string> chatId,
        std::int32_t messageId);

    bool answerCallbackQuery(const std::string& callbackQueryId,
                             const std::string& text = "",
                             bool showAlert = false,
                             const std::string& url = "",
                             std::int32_t cacheTime = 0);

    virtual void onAnyMessage(const Message::Ptr& message){};

    virtual void onNonCommandMessage(const Message::Ptr& message){};

    virtual void onCommand(const Message::Ptr& message){};

    virtual void onCallbackQuery(const CallbackQuery::Ptr& callbackQuery){};

    ~Fragment();
};

#endif