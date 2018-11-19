/* Client.cpp -- Client ENet Source - LexRis Logic Headers

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

#include "../../include/LexRisLogic/ENet/Client.h"

namespace LL_ENet
{
    Client::Client()
    {
    }
    bool Client::_F_reset_connection()
    {
        if(_V_client_connection)
        {
            enet_peer_reset(_V_client_connection);
            return true;
        }
        return false;
    }
    bool Client::_F_test_connection()
    {
        unsigned int elapsed_time=0;
        while(elapsed_time<_V_test_time)
        {
            if(enet_host_service(_V_client_host,&_V_event,_V_time)>0)
            {
                switch(_V_event.type)
                {
                    case ENET_EVENT_TYPE_CONNECT:
                        return true;
                    case ENET_EVENT_TYPE_RECEIVE:
                        return true;
                    default:
                        break;
                }
            }
            elapsed_time+=_V_time;
        }
        return false;
    }
    bool Client::set_ip(std::string new_ip)
    {
        if(!_V_is_running && !enet_address_set_host(&_V_address,new_ip.c_str()))
        {
            _V_ip=new_ip;
            return true;
        }
        return false;
    }
    std::string Client::get_ip()
    {
        return _V_ip;
    }
    bool Client::set_port(unsigned int new_port)
    {
        if(!_V_is_running)
        {
            _V_address.port=new_port;
            return true;
        }
        return false;
    }
    unsigned int Client::get_port()
    {
        return _V_address.port;
    }
    bool Client::set_test_time(unsigned int new_test_time)
    {
        if(!_V_is_running && new_test_time>0)
        {
            _V_test_time=new_test_time;
            return true;
        }
        return false;
    }
    unsigned int Client::get_test_time()
    {
        return _V_test_time;
    }
    void Client::set_wait_time(unsigned int wait_time)
    {
        _V_time=wait_time;
    }
    unsigned int Client::get_wait_time()
    {
        return _V_time;
    }
    bool Client::start_client()
    {
        if(!_V_is_running)
        {
            _V_client_host=enet_host_create(NULL,1,2,57600/8,14400/8);
            _V_is_running=_V_client_host;
            return _V_is_running;
        }
        return false;
    }
    bool Client::connect_to_server()
    {
        _F_reset_connection();
        _V_client_connection=enet_host_connect(_V_client_host,&_V_address,2,0);
        if(!_V_client_connection)
            return false;
        return (_V_status_connected=_F_test_connection());
    }
    bool Client::disconnect_from_server()
    {
        if(_V_status_connected && _V_client_connection)
        {
            enet_peer_disconnect(_V_client_connection,0);
            while(enet_host_service(_V_client_host,&_V_event,_V_time)>0)
            {
                switch (_V_event.type)
                {
                    case ENET_EVENT_TYPE_RECEIVE:
                    {
                        enet_packet_destroy(_V_event.packet);
                        break;
                    }
                    case ENET_EVENT_TYPE_DISCONNECT:
                        return true;
                    default:
                        break;
                }
            }
            _V_client_connection=nullptr;
            return true;
        }
        return false;
    }
    bool Client::get_connection_status()
    {
        return _V_status_connected;
    }
    bool Client::get_event()
    {
        if(enet_host_service(_V_client_host,&_V_event,_V_time)>0)
        {
            switch(_V_event.type)
            {
                case ENET_EVENT_TYPE_CONNECT:
                {
                    _V_status_connected=true;
                    break;
                }
                case ENET_EVENT_TYPE_RECEIVE:
                {
                    _V_message_queue.push((const char*)(_V_event.packet->data));
                    break;
                }
                case ENET_EVENT_TYPE_DISCONNECT:
                {
                    _V_status_connected=false;
                    _V_event.peer->data=NULL;
                    break;
                }
                case ENET_EVENT_TYPE_NONE:
                    return false;
            }
            return true;
        }
        return false;
    }
    std::string Client::get_message_received()
    {
        if(!_V_message_queue.empty())
            return _V_message_queue.front();
        return std::string();
    }
    bool Client::remove_message_received()
    {
        if(!_V_message_queue.empty())
        {
            _V_message_queue.pop();
            return true;
        }
        return false;
    }
    void Client::clear()
    {
        while(!_V_message_queue.empty())
            _V_message_queue.pop();
    }
    bool Client::empty()
    {
        return _V_message_queue.empty();
    }
    bool Client::send(std::string message)
    {
        if(_V_is_running && _V_status_connected && message.size())
        {
            ENetPacket* packet=enet_packet_create(message.c_str(),message.size()+1,ENET_PACKET_FLAG_RELIABLE);
            if(packet)
                return (!enet_peer_send(_V_client_connection,0,packet));
        }
        return false;
    }
    bool Client::stop_client()
    {
        if(_V_is_running)
        {
            disconnect_from_server();
            clear();
            enet_host_destroy(_V_client_host);
            _V_client_host=nullptr;
            _V_is_running=false;
            return true;
        }
        return false;
    }
    Client::~Client()
    {
        stop_client();
    }
}
