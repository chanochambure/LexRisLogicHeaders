/* Server.cpp -- Server ENet Source - LexRis Logic Headers

    Copyright (c) 2017-2018 LexRisLogic

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

#include "../../include/LexRisLogic/ENet/Server.h"

namespace LL_ENet
{
    Server::Server()
    {
    }
    bool Server::set_ip(std::string new_ip)
    {
        if(!_V_is_running and !enet_address_set_host(&_V_address,new_ip.c_str()))
        {
            _V_ip=new_ip;
            return true;
        }
        return false;
    }
    std::string Server::get_ip()
    {
        return _V_ip;
    }
    bool Server::set_port(unsigned int new_port)
    {
        if(!_V_is_running)
        {
            _V_address.port=new_port;
            return true;
        }
        return false;
    }
    unsigned int Server::get_port()
    {
        return _V_address.port;
    }
    bool Server::set_max_peers_connections(unsigned int max_peers_connections)
    {
        if(!_V_is_running)
        {
            _V_max_connections=max_peers_connections;
            return true;
        }
        return false;
    }
    unsigned int Server::get_max_peers_connections()
    {
        return _V_max_connections;
    }
    void Server::set_wait_time(unsigned int wait_time)
    {
        _V_time=wait_time;
    }
    unsigned int Server::get_wait_time()
    {
        return _V_time;
    }
    bool Server::start_server()
    {
        if(!_V_is_running)
        {
            _V_server_host = enet_host_create(&_V_address, _V_max_connections, 2, 0, 0);
            _V_is_running=_V_server_host;
            return _V_is_running;
        }
        return false;
    }
    bool Server::get_event()
    {
        if(enet_host_service(_V_server_host,&_V_event,_V_time)>0)
        {
            switch(_V_event.type)
            {
                case ENET_EVENT_TYPE_CONNECT:
                {
                    _V_event_new_connection=true;
                    _V_event_disconnection=false;
                    break;
                }
                case ENET_EVENT_TYPE_RECEIVE:
                {
                    _V_event_new_connection=false;
                    _V_event_disconnection=false;
                    _V_message_queue.push(_T_Type_enet_client(_V_event.peer,
                                                            (const char*)(_V_event.packet->data)));
                    break;
                }
                case ENET_EVENT_TYPE_DISCONNECT:
                {
                    _V_event_new_connection=false;
                    _V_event_disconnection=true;
                    _V_event.peer->data=NULL;
                    break;
                }
                case ENET_EVENT_TYPE_NONE:
                {
                    _V_event_new_connection=false;
                    _V_event_disconnection=false;
                    return false;
                }
            }
            return true;
        }
        return false;
    }
    bool Server::get_new_connection()
    {
        return _V_event_new_connection;
    }
    bool Server::get_disconnection()
    {
        return _V_event_disconnection;
    }
    ENetPeer* Server::get_peer_connected()
    {
        if(_V_event_new_connection)
            return _V_event.peer;
        return nullptr;
    }
    ENetPeer* Server::get_peer_disconnected()
    {
        if(_V_event_disconnection)
            return _V_event.peer;
        return nullptr;
    }
    ENetPeer* Server::get_issuer_peer()
    {
        if(!_V_message_queue.empty())
            return _V_message_queue.front().first;
        return nullptr;
    }
    std::string Server::get_message_received()
    {
        if(!_V_message_queue.empty())
            return _V_message_queue.front().second;
        return std::string();
    }
    bool Server::remove_message_received()
    {
        if(!_V_message_queue.empty())
        {
            _V_message_queue.pop();
            return true;
        }
        return false;
    }
    void Server::clear()
    {
        while(!_V_message_queue.empty())
            _V_message_queue.pop();
    }
    bool Server::empty()
    {
        return _V_message_queue.empty();
    }
    bool Server::send(ENetPeer* receiver,std::string message)
    {
        if(_V_is_running and message.size())
        {
            ENetPacket* packet=enet_packet_create(message.c_str(),message.size()+1,ENET_PACKET_FLAG_RELIABLE);
            if(packet)
                return (!enet_peer_send(receiver,0,packet));
        }
        return false;
    }
    bool Server::broadcast(std::string message)
    {
        if(_V_is_running and message.size())
        {
            ENetPacket* packet=enet_packet_create(message.c_str(),message.size()+1,ENET_PACKET_FLAG_RELIABLE);
            if(packet)
            {
                enet_host_broadcast(_V_server_host,0,packet);
                return true;
            }
        }
        return false;
    }
    bool Server::stop_server()
    {
        if(_V_is_running)
        {
            clear();
            enet_host_destroy(_V_server_host);
            _V_server_host=nullptr;
            _V_is_running=false;
            return true;
        }
        return false;
    }
    Server::~Server()
    {
        stop_server();
    }
}
