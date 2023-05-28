#include <tgbot/tgbot.h>

#include <iostream>

#include "Database.hpp"
#include "Fragment.hpp"

int main() {
    try {
        Database database("ddd.db");
        database.executeFast("CREATE TABLE IF NOT EXISTS 'product'(id TEXT PRIMARY KEY)")->stepThis().dispose();
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    TgBot::Bot bot("5830213755:AAEWKtp0mHKxcNSyDL0MYps8YgI2k12lSME");

    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Hi!");
    });
    
    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
        printf("User wrote %s\n", message->text.c_str());
        if (StringTools::startsWith(message->text, "/start")) {
            return;
        }
        bot.getApi().sendMessage(message->chat->id, "Your message is: " + message->text);
    });

    try {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            printf("Long poll started\n");
            longPoll.start();
        }
    } catch (TgBot::TgException& e) {
        printf("error: %s\n", e.what());
    }

    return 0;
}