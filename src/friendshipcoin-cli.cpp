// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2013 The friendshipcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "util.h"
#include "init.h"
#include "rpc/client.h"
#include "ui_interface.h" /* for _(...) */
#include "chainparamsbase.h"

#include <boost/filesystem/operations.hpp>

//////////////////////////////////////////////////////////////////////////////
//
// Start
//
static bool AppInitRPC(int argc, char* argv[])
{
    //
    // Parameters
    //
    ParseParameters(argc, argv);
    if (!boost::filesystem::is_directory(GetDataDir(false)))
    {
        fprintf(stderr, "Error: Specified data directory \"%s\" does not exist.\n", mapArgs["-datadir"].c_str());
        return false;
    }
    ReadConfigFile(mapArgs, mapMultiArgs);
    // Check for -testnet or -regtest parameter (TestNet() calls are only valid after this clause)
    
    try {
      SelectBaseParams(ChainNameFromCommandLine());
    } catch (...) {
      fprintf(stderr, "Error: Invalid combination of -regtest and -testnet.\n");
      return false;
    }

    if (argc<2 || mapArgs.count("-?") || mapArgs.count("--help"))
    {
        // First part of help message is specific to RPC client
        std::string strUsage = _("friendshipcoin RPC client version") + " " + FormatFullVersion() + "\n\n" +
            _("Usage:") + "\n" +
              "  friendshipcoin-cli [options] <command> [params]  " + _("Send command to Bitcoin server") + "\n" +
              "  friendshipcoin-cli [options] help                " + _("List commands") + "\n" +
              "  friendshipcoin-cli [options] help <command>      " + _("Get help for a command") + "\n";

        strUsage += "\n" + HelpMessage(HMM_FRIENDSHIPCOIN_CLI);

        fprintf(stdout, "%s", strUsage.c_str());
        return false;
    }
    return true;
}

int main(int argc, char* argv[])
{
    try
    {
        if(!AppInitRPC(argc, argv))
            return 1;
    }
    catch (std::exception& e) {
        PrintExceptionContinue(&e, "AppInitRPC()");
    } catch (...) {
        PrintExceptionContinue(NULL, "AppInitRPC()");
    }

    try
    {
        if(!CommandLineRPC(argc, argv))
            return 1;
    }
    catch (std::exception& e) {
        PrintExceptionContinue(&e, "CommandLineRPC()");
    } catch (...) {
        PrintExceptionContinue(NULL, "CommandLineRPC()");
    }
    return 0;
}
