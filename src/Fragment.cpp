#include "Fragment.hpp"

#include "FragmentManager.hpp"
#include "iostream"

Fragment::Fragment(int id) {
    fragmentId = id;
}

void Fragment::onCreate(int16_t type, const std::shared_ptr<void>& data) {
    if (type == Fragment::MESSAGE) {
        auto message = std::reinterpret_pointer_cast<Message>(data);
        fragmentManager->stateController.setState(
            message->from->id,
            fragmentId);
    } else if (type == Fragment::CALLBACK_QUERY) {
        auto callbackQuery = std::reinterpret_pointer_cast<CallbackQuery>(data);
        fragmentManager->stateController.setState(
            callbackQuery->from->id,
            fragmentId);
    }
}

Bot& Fragment::getBot() {
    return fragmentManager->getBot();
}

const Api& Fragment::getApi() {
    return fragmentManager->getApi();
}

std::shared_ptr<Fragment> Fragment::presentFragment(int id, int16_t type, const std::shared_ptr<void>& data) const {
    return fragmentManager->presentFragment(id, type, data);
}

void Fragment::setFragmentManager(FragmentManager* fm) {
    fragmentManager = fm;
}

Message::Ptr Fragment::sendMessage(boost::variant<std::int64_t, std::string> chatId,
                                   const std::string& text,
                                   bool disableWebPagePreview,
                                   std::int32_t replyToMessageId,
                                   GenericReply::Ptr replyMarkup,
                                   const std::string& parseMode,
                                   bool disableNotification,
                                   const std::vector<MessageEntity::Ptr>& entities,
                                   bool allowSendingWithoutReply,
                                   bool protectContent,
                                   std::int32_t messageThreadId) {
    return fragmentManager->getApi().sendMessage(chatId,
                                                 text,
                                                 disableWebPagePreview,
                                                 replyToMessageId,
                                                 replyMarkup,
                                                 parseMode,
                                                 disableNotification,
                                                 entities,
                                                 allowSendingWithoutReply,
                                                 protectContent,
                                                 messageThreadId);
}

Message::Ptr Fragment::editMessageText(const std::string& text,
                                       boost::variant<std::int64_t, std::string> chatId,
                                       std::int32_t messageId,
                                       const std::string& inlineMessageId,
                                       const std::string& parseMode,
                                       bool disableWebPagePreview,
                                       GenericReply::Ptr replyMarkup,
                                       const std::vector<MessageEntity::Ptr>& entities) const {
    return fragmentManager->getApi().editMessageText(
        text,
        chatId,
        messageId,
        inlineMessageId,
        parseMode,
        disableWebPagePreview,
        replyMarkup,
        entities
    );
}

bool Fragment::deleteMessage(
    boost::variant<std::int64_t, std::string> chatId,
    std::int32_t messageId) {
    return fragmentManager->getApi().deleteMessage(chatId, messageId);
}

bool Fragment::answerCallbackQuery(const std::string& callbackQueryId,
                                   const std::string& text,
                                   bool showAlert,
                                   const std::string& url,
                                   std::int32_t cacheTime) {
    return fragmentManager->getApi().answerCallbackQuery(
        callbackQueryId,
        text,
        showAlert,
        url,
        cacheTime);
}

Fragment::~Fragment() {
}