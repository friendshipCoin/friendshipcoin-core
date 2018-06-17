// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef FRIENDSHIPCOIN_INIT_H
#define FRIENDSHIPCOIN_INIT_H

#include "wallet.h"

namespace boost {
    class thread_group;
} // namespace boost

extern CWallet* pwalletMain;
void StartShutdown();
bool ShutdownRequested();
void Shutdown();
bool AppInit2(boost::thread_group& threadGroup);

/* The help message mode determines what help message to show */
enum HelpMessageMode
{
    HMM_FRIENDSHIPCOIND,
    HMM_FRIENDSHIPCOIN_QT,
    HMM_FRIENDSHIPCOIN_CLI
};

std::string HelpMessage(HelpMessageMode mode);

extern bool fOnlyTor;

#endif
