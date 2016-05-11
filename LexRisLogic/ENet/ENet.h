#ifndef INCLUDED_LL_ENET_H
#define INCLUDED_LL_ENET_H

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

#endif // INCLUDED_LL_ENET_H
