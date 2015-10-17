#ifndef LL_CLIENT_H_INCLUDED
#define LL_CLIENT_H_INCLUDED

#include <iostream>
#include <string>
#include <queue>

using namespace std;

class Client
{
    private:
        ENetAddress address;
        bool _init=0;
        ENetHost *client=nullptr;
        ENetPeer *peer=nullptr;
        ENetEvent event;
        bool _connected=0;
        string IP;
        int port=0;
        bool _reset(){if(peer){enet_peer_reset(peer);return 1;}return 0;}
        bool _test();
        int _service=1000;
        queue<pair<ENetPeer*,string>> _mess_;
    public:
        Client(){}
        void SetServiceTime(int ms){_service=ms;}
        int GetServiceTime(){return _service;}
        bool StartClient(){if(!_init){client = enet_host_create(NULL, 1, 2, 57600/8, 14400/8);_init=client;return _init;}return 0;}
        bool StopClient(){if(_init){CleanQueue();enet_host_destroy(client);client=nullptr;_init=0;return 1;}return 0;}
        bool GetConnection(string _IP,int _port);
        bool GetStatus(){return _connected;}
        bool Reconnect(){_reset();peer=enet_host_connect(client, &address, 2, 0);if(!peer)return false;return (_connected=_test());}
        bool remove(){if(!_mess_.empty()){_mess_.pop();return 1;}return 0;}
        string first(){return _mess_.front().second;}
        string last(){return _mess_.back().second;}
        bool empty(){return _mess_.empty();}
        void CleanQueue(){while(!_mess_.empty())_mess_.pop();}
        bool SendMessage(string to_send){if(_init and _connected){if(to_send.size()>0){ENetPacket* packet=enet_packet_create(to_send.c_str(),to_send.size()+1,ENET_PACKET_FLAG_RELIABLE);if(packet)return (!enet_peer_send(peer,0,packet));}}return 0;}
        bool operator () ();
        ~Client(){StopClient();}
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

bool Client::GetConnection(string _IP,int _port)
{
    enet_address_set_host(&address,_IP.c_str());
    address.port=_port;
    _reset();
    peer=enet_host_connect(client, &address, 2, 0);
    if(!peer)
        return false;
    return (_connected=_test());
}

bool Client::operator() ()
{
    bool a=0;
    while(enet_host_service(client,&event,_service)>0)
    {
        a=1;
        switch(event.type)
        {
            case ENET_EVENT_TYPE_CONNECT:
                _connected=1;
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                _mess_.push(pair<ENetPeer*,string>(event.peer,to_string(event.packet->data)));
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                _connected=0;
                event.peer->data=NULL;
                break;
            case ENET_EVENT_TYPE_NONE:
                return 0;
        }
    }
    if(a)
        return 1;
    return 0;
}

#endif // LL_CLIENT_H_INCLUDED
