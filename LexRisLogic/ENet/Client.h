#ifndef LL_ENET_CLIENT_H_INCLUDED
#define LL_ENET_CLIENT_H_INCLUDED

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
            bool _F_reset_connection()
            {
                if(_V_client_connection)
                {
                    enet_peer_reset(_V_client_connection);
                    return true;
                }
                return false;
            }
            bool _F_test_connection()
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
        public:
            bool set_ip(std::string new_ip)
            {
                if(!_V_is_running and !enet_address_set_host(&_V_address,new_ip.c_str()))
                {
                    _V_ip=new_ip;
                    return true;
                }
                return false;
            }
            std::string get_ip()
            {
                return _V_ip;
            }
            bool set_port(unsigned int new_port)
            {
                if(!_V_is_running)
                {
                    _V_address.port=new_port;
                    return true;
                }
                return false;
            }
            unsigned int get_port()
            {
                return _V_address.port;
            }
            bool set_test_time(unsigned int new_test_time)
            {
                if(!_V_is_running and new_test_time>0)
                {
                    _V_test_time=new_test_time;
                    return true;
                }
                return false;
            }
            unsigned int get_test_time()
            {
                return _V_test_time;
            }
            void set_wait_time(unsigned int wait_time)
            {
                _V_time=wait_time;
            }
            unsigned int get_wait_time()
            {
                return _V_time;
            }
            bool start_client()
            {
                if(!_V_is_running)
                {
                    _V_client_host=enet_host_create(NULL, 1, 2, 57600/8, 14400/8);
                    _V_is_running=_V_client_host;
                    return _V_is_running;
                }
                return false;
            }
            bool connect_to_server()
            {
                if(_F_reset_connection())
                    return true;
                _V_client_connection=enet_host_connect(_V_client_host, &_V_address, 2, 0);
                if(!_V_client_connection)
                    return false;
                return (_V_status_connected=_F_test_connection());
            }
            bool disconnect_from_server()
            {
                if(_V_status_connected and _V_client_connection)
                {
                    enet_peer_disconnect(_V_client_connection,0);
                    while(enet_host_service(_V_client_host,&_V_event,_V_time)>0)
                    {
                        switch (_V_event.type)
                        {
                            case ENET_EVENT_TYPE_RECEIVE:
                                enet_packet_destroy(_V_event.packet);
                                break;
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
            bool get_connection_status()
            {
                return _V_status_connected;
            }
            bool have_an_event()
            {
                if(enet_host_service(_V_client_host,&_V_event,_V_time)>0)
                {
                    switch(_V_event.type)
                    {
                        case ENET_EVENT_TYPE_CONNECT:
                            _V_status_connected=true;
                            break;
                        case ENET_EVENT_TYPE_RECEIVE:
                            _V_message_queue.push((const char*)(_V_event.packet->data));
                            break;
                        case ENET_EVENT_TYPE_DISCONNECT:
                            _V_status_connected=false;
                            _V_event.peer->data=NULL;
                            break;
                        case ENET_EVENT_TYPE_NONE:
                            return false;
                    }
                    return true;
                }
                return false;
            }
            std::string get_message_received()
            {
                if(!_V_message_queue.empty())
                    return _V_message_queue.front();
                return std::string();
            }
            bool remove_message_received()
            {
                if(!_V_message_queue.empty())
                {
                    _V_message_queue.pop();
                    return true;
                }
                return false;
            }
            void clear()
            {
                while(!_V_message_queue.empty())
                    _V_message_queue.pop();
            }
            bool empty()
            {
                return _V_message_queue.empty();
            }
            bool send(std::string message)
            {
                if(_V_is_running and _V_status_connected and message.size())
                {
                    ENetPacket* packet=enet_packet_create(message.c_str(),message.size()+1,ENET_PACKET_FLAG_RELIABLE);
                    if(packet)
                        return (!enet_peer_send(_V_client_connection,0,packet));
                }
                return false;
            }
            bool stop_client()
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
            ~Client()
            {
                stop_client();
            }
    };
}

#endif // LL_ENET_CLIENT_H_INCLUDED
