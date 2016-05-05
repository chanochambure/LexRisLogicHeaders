#ifndef LL_ENET_H_INCLUDED
#define LL_ENET_H_INCLUDED

#include <enet/enet.h>

namespace LL_ENet
{
    bool install_enet()
    {
        return !(enet_initialize());
    }
    void uninstall_enet()
    {
        enet_deinitialize();
    }
}

#include "Server.h"
#include "Client.h"

#endif // LL_ENET_H_INCLUDED
