#ifndef LL_ENET_H_INCLUDED
#define LL_ENET_H_INCLUDED

//Enet
#include <enet/enet.h>

//Functions

bool install_enet(){return !(enet_initialize());}

void uninstall_enet(){enet_deinitialize();}

//Library
#include "LL_Server.h"
#include "LL_Client.h"

#endif // LL_ENET_H_INCLUDED
