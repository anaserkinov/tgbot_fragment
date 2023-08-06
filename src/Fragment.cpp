#include "Fragment.hpp"

#include "FragmentManager.hpp"
#include "iostream"

Fragment::Fragment(int id) {
    std::cout<<"Fragment create: "<<id<<"\n";
    fragmentId = id;
}

Bot& Fragment::getBot() {
    return fragmentManager->getBot();
}

const Api& Fragment::getApi() {
    return fragmentManager->getApi();
}

std::shared_ptr<Fragment> Fragment::presentFragment(int id, const Message::Ptr lastMessage) const {
    return fragmentManager->presentFragment(id, lastMessage);
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

Fragment::~Fragment() {
}