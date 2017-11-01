/**
 *                  _           _     _   _                   _
 *  __ _ _ __   __| |_ __ ___ (_) __| | | |_ ___  _   _  ___| |__
 * / _` | '_ \ / _` | '__/ _ \| |/ _` | | __/ _ \| | | |/ __| '_ \
 *| (_| | | | | (_| | | | (_) | | (_| | | || (_) | |_| | (__| | | |
 * \__,_|_| |_|\__,_|_|  \___/|_|\__,_|  \__\___/ \__,_|\___|_| |_|
 *
 * Copyright (c) 2017 Kunal Dawn <kunal.dawn@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 3 as published by
 * the Free Software Foundation.
 */

#include "TouchInput.h"
#include "Logging.h"
#include "../vendor/httplib/httplib.h"
#include "../vendor/jsoncpp/json.h"

int main() {
    android_touch::Logging::setMode(android_touch::Logging::Mode::Verbose);
    auto touchInput = android_touch::TouchInput::getNewInstance();

    if (touchInput == nullptr) {
        android_touch::Logging::info("Server", "No supported touch input found...");
        return 0;
    }

    android_touch::Logging::info("Server", "Using input device : " + touchInput->getDevicePath());

    httplib::Server server;
    server.post("/", [&touchInput](const httplib::Request& req, httplib::Response& res) {
        try {
            Json::Value root;
            Json::Reader reader;
            reader.parse(req.body, root, false);

            for (Json::Value &command : root) {
                if (command.isMember("type")) {
                    std::string commandType = command.get("type", Json::stringValue).asString();
                    if (commandType == "down" && command.isMember("x") && command.isMember("y") && command.isMember("contact") && command.isMember("pressure")) {
                        int x = command.get("x", Json::intValue).asInt();
                        int y = command.get("y", Json::intValue).asInt();
                        int contact = command.get("contact", Json::intValue).asInt();
                        int pressure = command.get("pressure", Json::intValue).asInt();

                        touchInput->down(contact, x, y, pressure);
                    } else if (commandType == "move" && command.isMember("x") && command.isMember("y") && command.isMember("contact") && command.isMember("pressure")) {
                        int x = command.get("x", Json::intValue).asInt();
                        int y = command.get("y", Json::intValue).asInt();
                        int contact = command.get("contact", Json::intValue).asInt();
                        int pressure = command.get("pressure", Json::intValue).asInt();

                        touchInput->move(contact, x, y, pressure);
                    } else if (commandType == "up" && command.isMember("contact")) {
                        int contact = command.get("contact", Json::intValue).asInt();

                        touchInput->up(contact);
                    } else if (commandType == "commit") {
                        touchInput->commit();
                    } else if (commandType == "delay" && command.isMember("value")) {
                        int value = command.get("value", Json::intValue).asInt();

                        touchInput->delay(value);
                    }
                }
            }
        } catch (std::exception &ex) {
            std::cout << ex.what() << std::endl;
        }
    });

    android_touch::Logging::info("Server", "Starting server on port : 8080");
    server.listen("0.0.0.0", 8080);
}
