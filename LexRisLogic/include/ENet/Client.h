/* Client.h -- Client ENet Header - LexRis Logic Headers

    Copyright (c) 2016 LexRisLogic

    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
    documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
    rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
    permit persons to whom the Software is furnished to do so.

    The above copyright notice and this permission notice shall be included in all copies or substantial portions of
    the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
    THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
    TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#ifndef INCLUDED_LL_ENET_CLIENT_H
#define INCLUDED_LL_ENET_CLIENT_H

#include "ENet.h"

#include <sstream>
#include <string>
#include <queue>

namespace LL_ENet
{
    class Client
    {
        private:
            unsigned int _V_test_time=5000;
            ENetAddress _V_address;
            ENetHost* _V_client_host=nullptr;
            ENetPeer* _V_client_connection=nullptr;
            ENetEvent _V_event;
            bool _V_is_running=false;
            bool _V_status_connected=false;
            std::string _V_ip;
            int _V_time=1000;
            std::queue<std::string> _V_message_queue;
            bool _F_reset_connection();
            bool _F_test_connection();
        public:
            bool set_ip(std::string new_ip);
            std::string get_ip();
            bool set_port(unsigned int new_port);
            unsigned int get_port();
            bool set_test_time(unsigned int new_test_time);
            unsigned int get_test_time();
            void set_wait_time(unsigned int wait_time);
            unsigned int get_wait_time();
            bool start_client();
            bool connect_to_server();
            bool disconnect_from_server();
            bool get_connection_status();
            bool get_event();
            std::string get_message_received();
            bool remove_message_received();
            void clear();
            bool empty();
            bool send(std::string message);
            bool stop_client();
            ~Client();
    };
}

#endif // INCLUDED_LL_ENET_CLIENT_H
