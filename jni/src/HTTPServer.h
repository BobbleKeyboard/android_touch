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

#ifndef PROJECT_SERVER_H_H
#define PROJECT_SERVER_H_H

#include <string>
#include "Logging.h"
#include "TouchInput.h"
#include "../vendor/httplib/httplib.h"
#include "../vendor/jsoncpp/json.h"

namespace android_touch {
    class HTTPServer {
    private:
        std::string mHost = "";
        int mPort;
        httplib::Server mServer;

    public:
        HTTPServer(const std::string &host, int port);
        void run();
    };
}

#endif //PROJECT_SERVER_H_H
