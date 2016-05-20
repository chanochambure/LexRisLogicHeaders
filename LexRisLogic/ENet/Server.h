#ifndef INCLUDED_LL_ENET_SERVER_H
#define INCLUDED_LL_ENET_SERVER_H

#include <sstream>
#include <string>
#include <queue>

namespace LL_ENet
{
    class Server
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
            bool set_max_peers_connections(unsigned int max_peers_connections)
            {
                if(!_V_is_running)
                {
                    _V_max_connections=max_peers_connections;
                    return true;
                }
                return false;
            }
            unsigned int get_max_peers_connections()
            {
                return _V_max_connections;
            }
            void set_wait_time(unsigned int wait_time)
            {
                _V_time=wait_time;
            }
            unsigned int get_wait_time()
            {
                return _V_time;
            }
            bool start_server()
            {
                if(!_V_is_running)
                {
                    _V_server_host = enet_host_create(&_V_address, _V_max_connections, 2, 0, 0);
                    _V_is_running=_V_server_host;
                    return _V_is_running;
                }
                return false;
            }
            bool get_event()
            {
                if(enet_host_service(_V_server_host,&_V_event,_V_time)>0)
                {
                    switch(_V_event.type)
                    {
                        case ENET_EVENT_TYPE_CONNECT:
                            {
                                _V_event_new_connection=true;
                                _V_event_disconnection=false;
                            }
                            break;
                        case ENET_EVENT_TYPE_RECEIVE:
                            {
                                _V_event_new_connection=false;
                                _V_event_disconnection=false;
                                _V_message_queue.push(_T_Type_enet_client(_V_event.peer,
                                                                          (const char*)(_V_event.packet->data)));
                            }
                            break;
                        case ENET_EVENT_TYPE_DISCONNECT:
                            {
                                _V_event_new_connection=false;
                                _V_event_disconnection=true;
                                _V_event.peer->data=NULL;
                            }
                            break;
                        case ENET_EVENT_TYPE_NONE:
                            {
                                _V_event_new_connection=false;
                                _V_event_disconnection=false;
                                return false;
                            }
                            break;
                    }
                    return true;
                }
                return false;
            }
            bool get_new_connection()
            {
                return _V_event_new_connection;
            }
            bool get_disconnection()
            {
                return _V_event_disconnection;
            }
            ENetPeer* get_peer_connected()
            {
                if(_V_event_new_connection)
                    return _V_event.peer;
                return nullptr;
            }
            ENetPeer* get_peer_disconnected()
            {
                if(_V_event_disconnection)
                    return _V_event.peer;
                return nullptr;
            }
            ENetPeer* get_issuer_peer()
            {
                if(!_V_message_queue.empty())
                    return _V_message_queue.front().first;
                return nullptr;
            }
            std::string get_message_received()
            {
                if(!_V_message_queue.empty())
                    return _V_message_queue.front().second;
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
            bool send(ENetPeer* receiver,std::string message)
            {
                if(_V_is_running and message.size())
                {
                    ENetPacket* packet=enet_packet_create(message.c_str(),message.size()+1,ENET_PACKET_FLAG_RELIABLE);
                    if(packet)
                        return (!enet_peer_send(receiver,0,packet));
                }
                return false;
            }
            bool broadcast(std::string message)
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
            bool stop_server()
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
            ~Server()
            {
                stop_server();
            }
    };
}

#endif // INCLUDED_LL_ENET_SERVER_H
