#pragma once

namespace m3l::net
{
    enum Protocol
    {
        TCP,
        UDP
    };

    enum RecvStrat
    {
        All = MSG_OOB,
        Peek = MSG_PEEK,
        WaitAll = MSG_WAITALL
    };
}
