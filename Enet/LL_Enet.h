#ifndef LL_ALLEGRO_H_INCLUDED
#define LL_ALLEGRO_H_INCLUDED

//Enet
#include <enet/enet.h>
#include <LexRisLogic/LL_Convert.h>

//Functions

bool net_addon(){return !(enet_initialize());}

void unistall_enet(){enet_deinitialize();}

//Library
#include "LL_Server.h"
#include "LL_Client.h"

#endif // LL_ALLEGRO_H_INCLUDED
