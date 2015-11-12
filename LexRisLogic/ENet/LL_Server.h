#ifndef LL_SERVER_H_INCLUDED
#define LL_SERVER_H_INCLUDED

#include <iostream>
#include <string>
#include <queue>

using namespace std;

class Server
{
    private:
        template<typename T>
        string __to_string__(T data){stringstream st;st<<data;return st.str();}
        ENetAddress address;
        ENetHost* server;
        ENetEvent event;
        string Ip;
        bool _init=0;
        unsigned int _service=1000;
        queue<pair<ENetPeer*,string>> _mess_;
        bool c=0;
        bool d=0;
        unsigned int max_peer=32;
    public:
        bool set_ip(string IP){if(!_init){Ip=IP;enet_address_set_host(&address,IP.c_str());return 1;}return 0;}
        string get_ip(){return Ip;}
        bool set_port(unsigned int Port){if(!_init){address.port=Port;return 1;}return 0;}
        unsigned int get_port(){return address.port;}
        void set_peer_count(unsigned int peers){max_peer=peers;}
        unsigned int get_peer_count(){return max_peer;}
        void set_service_time(unsigned int ms){_service=ms;}
        unsigned int get_service_time(){return _service;}
        bool start_server(){if(!_init){server = enet_host_create(&address, max_peer, 2, 0, 0);_init=server;return _init;}return 0;}
        bool operator () ();
        bool event_connected(){return c;}
        bool event_disconnected(){return d;}
        ENetPeer* get_peer_connected(){if(c)return event.peer;return nullptr;}
        ENetPeer* get_peer_disconnected(){if(d)return event.peer;return nullptr;}
        ENetPeer* get_peer_received(){if(!_mess_.empty())return _mess_.front().first;return nullptr;}
        string get_message_received(){if(!_mess_.empty())return _mess_.front().second;return string();}
        bool remove_message_received(){if(!_mess_.empty()){_mess_.pop();return 1;}return 0;}
        void clear(){while(!_mess_.empty())_mess_.pop();}
        bool empty(){return _mess_.empty();}
        bool send_message_to_a_client(ENetPeer* Peer,string to_send){if(_init){if(to_send.size()>0){ENetPacket* packet=enet_packet_create(to_send.c_str(),to_send.size()+1,ENET_PACKET_FLAG_RELIABLE);if(packet)return (!enet_peer_send(Peer,0,packet));}}return 0;}
        bool send_message_to_all_clients(string to_send){if(_init){if(to_send.size()>0){ENetPacket* packet=enet_packet_create(to_send.c_str(),to_send.size()+1,ENET_PACKET_FLAG_RELIABLE);if(packet){enet_host_broadcast(server,0,packet);return 1;}}}return 0;}
        bool stop_server(){if(_init){clear();enet_host_destroy(server);server=nullptr;_init=0;return 1;}return 0;}
        ~Server(){stop_server();}
};

bool Server::operator () ()
{
    if(enet_host_service(server,&event,_service)>0)
    {
        switch(event.type)
        {
            case ENET_EVENT_TYPE_CONNECT:
                c=1;
                d=0;
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                c=0;
                d=0;
                _mess_.push(pair<ENetPeer*,string>(event.peer,__to_string__(event.packet->data)));
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                c=0;
                d=1;
                event.peer->data=NULL;
                break;
            case ENET_EVENT_TYPE_NONE:
                c=0;
                d=0;
                return 0;
        }
        return 1;
    }
    return 0;
}

#endif // LL_SERVER_H_INCLUDED
