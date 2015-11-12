#ifndef LL_CLIENT_H_INCLUDED
#define LL_CLIENT_H_INCLUDED

#include <iostream>
#include <sstream>
#include <string>
#include <queue>

using namespace std;

class Client
{
    private:
        template<typename T>
        string __to_string__(T data){stringstream st;st<<data;return st.str();}
        ENetAddress address;
        bool _init=0;
        ENetHost* client=nullptr;
        ENetPeer* peer=nullptr;
        ENetEvent event;
        bool _connected=0;
        string Ip;
        bool _reset(){if(peer){enet_peer_reset(peer);return 1;}return 0;}
        bool _test();
        int _service=1000;
        queue<string> _mess_;
    public:
        bool set_ip(string IP){if(!_init){Ip=IP;enet_address_set_host(&address,Ip.c_str());return 1;}return 0;}
        string get_ip(){return Ip;}
        bool set_port(unsigned int Port){if(!_init){address.port=Port;return 1;}return 0;}
        unsigned int get_port(){return address.port;}
        void set_service_time(int ms){_service=ms;}
        int get_service_time(){return _service;}
        bool start_client(){if(!_init){client = enet_host_create(NULL, 1, 2, 57600/8, 14400/8);_init=client;return _init;}return 0;}
        bool connect_to_server();
        bool get_status(){return _connected;}
        bool operator () ();
        string get_message_received(){if(!_mess_.empty())return _mess_.front();return string();}
        bool remove_message_received(){if(!_mess_.empty()){_mess_.pop();return 1;}return 0;}
        void clear(){while(!_mess_.empty())_mess_.pop();}
        bool empty(){return _mess_.empty();}
        bool send_message_to_the_server(string to_send){if(_init and _connected){if(to_send.size()>0){ENetPacket* packet=enet_packet_create(to_send.c_str(),to_send.size()+1,ENET_PACKET_FLAG_RELIABLE);if(packet)return (!enet_peer_send(peer,0,packet));}}return 0;}
        bool stop_client(){if(_init){clear();enet_host_destroy(client);client=nullptr;_init=0;return 1;}return 0;}
        ~Client(){stop_client();}
};

bool Client::_test()
{
    while(1)
    {
        enet_host_service(client,&event,_service);
        switch(event.type)
        {
            case ENET_EVENT_TYPE_CONNECT:
                return 1;
            case ENET_EVENT_TYPE_RECEIVE:
                return 1;
            case ENET_EVENT_TYPE_DISCONNECT:
                return 0;
            case ENET_EVENT_TYPE_NONE:
                return 0;
        }
    }
}

bool Client::connect_to_server()
{
    _reset();
    peer=enet_host_connect(client, &address, 2, 0);
    if(!peer)
        return false;
    return (_connected=_test());
}

bool Client::operator() ()
{
    if(enet_host_service(client,&event,_service)>0)
    {
        switch(event.type)
        {
            case ENET_EVENT_TYPE_CONNECT:
                _connected=1;
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                _mess_.push(__to_string__(event.packet->data));
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                _connected=0;
                event.peer->data=NULL;
                break;
            case ENET_EVENT_TYPE_NONE:
                return 0;
        }
        return 1;
    }
    return 0;
}

#endif // LL_CLIENT_H_INCLUDED
