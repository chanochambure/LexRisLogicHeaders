/* Server.h -- Server ENet Header - LexRis Logic Headers

    Copyright (c) 2017 LexRisLogic

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

#ifndef INCLUDED_LL_ENET_SERVER_H
#define INCLUDED_LL_ENET_SERVER_H

#include "../LL_Shared.h"

#include "ENet.h"

#include <sstream>
#include <string>
#include <queue>

namespace LL_ENet
{
    class LL_SHARED Server
    {
        private:
            typedef std::pair<ENetPeer*,std::string> _T_Type_enet_client;
            ENetAddress _V_address;
            ENetHost* _V_server_host;
            ENetEvent _V_event;
            std::string _V_ip;
            bool _V_is_running=false;
            unsigned int _V_time=1000;
            std::queue<_T_Type_enet_client> _V_message_queue;
            bool _V_event_new_connection=false;
            bool _V_event_disconnection=false;
            unsigned int _V_max_connections=32;
        public:
            bool set_ip(std::string new_ip);
            std::string get_ip();
            bool set_port(unsigned int new_port);
            unsigned int get_port();
            bool set_max_peers_connections(unsigned int max_peers_connections);
            unsigned int get_max_peers_connections();
            void set_wait_time(unsigned int wait_time);
            unsigned int get_wait_time();
            bool start_server();
            bool get_event();
            bool get_new_connection();
            bool get_disconnection();
            ENetPeer* get_peer_connected();
            ENetPeer* get_peer_disconnected();
            ENetPeer* get_issuer_peer();
            std::string get_message_received();
            bool remove_message_received();
            void clear();
            bool empty();
            bool send(ENetPeer* receiver,std::string message);
            bool broadcast(std::string message);
            bool stop_server();
            ~Server();
    };
}

#endif // INCLUDED_LL_ENET_SERVER_H
