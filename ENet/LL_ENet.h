#ifndef LL_ENET_H_INCLUDED
#define LL_ENET_H_INCLUDED

//Enet
#include <enet/enet.h>
#include <LexRisLogic/LL_Convert.h>

//Functions

bool install_enet(){return !(enet_initialize());}

void uninstall_enet(){enet_deinitialize();}

//Library
#include <LexRisLogic/ENet/LL_Server.h>
#include <LexRisLogic/ENet/LL_Client.h>

#endif // LL_ENET_H_INCLUDED
