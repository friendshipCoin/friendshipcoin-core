// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds array into usable address objects.
static void convertSeeds(std::vector<CAddress> &vSeedsOut, const unsigned int *data, unsigned int count, int port) {
  // It'll only connect to one or two seed nodes because once it connects,
  // it'll get a pile of addresses with newer timestamps.
  // Seed nodes are given a random 'last seen time' of between one and two
  // weeks ago.
  const int64_t nOneWeek = 7*24*60*60;
  for (unsigned int k = 0; k < count; ++k)
  {
    struct in_addr ip;
    unsigned int i = data[k], t;

    // -- convert to big endian
    t =   (i & 0x000000ff) << 24u
      | (i & 0x0000ff00) << 8u
      | (i & 0x00ff0000) >> 8u
      | (i & 0xff000000) >> 24u;

    memcpy(&ip, &t, sizeof(ip));

    CAddress addr(CService(ip, port));
    addr.nTime = GetTime()-GetRand(nOneWeek)-nOneWeek;
    vSeedsOut.push_back(addr);
  }
}

class CMainParams : public CChainParams {
public:
  CMainParams() {
    // The message start string is designed to be unlikely to occur in normal data.
    // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
    // a large 4-byte int at any alignment.
    pchMessageStart[0] = 0x11;
    pchMessageStart[1] = 0xc3;
    pchMessageStart[2] = 0xb1;
    pchMessageStart[3] = 0xde;
    vAlertPubKey = ParseHex("0323740193a8560083f057e3bf354ce8b5739d4242cd9992d1fb95ebe9d0c626cd");
    nDefaultPort = 58008;
    nRPCPort = 58009;
    bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);

    const char* pszTimestamp = "It's time to get friendly!";

    std::vector<CTxIn> vin;
    vin.resize(1);
    vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    std::vector<CTxOut> vout;
    vout.resize(1);
    vout[0].SetEmpty();
    CTransaction txNew(1, 1517569200, vin, vout, 0);

    genesis.vtx.push_back(txNew);
    genesis.hashPrevBlock = 0;
    genesis.hashMerkleRoot = genesis.BuildMerkleTree();
    genesis.nVersion = 1;
    genesis.nTime    = 1519845939;
    genesis.nBits    = 0x1e0fffff;
    genesis.nNonce   = 587523;

    hashGenesisBlock = genesis.GetHash();

    assert(hashGenesisBlock == uint256("0x000001b5480fd285a0d85a6cdbd79e59e95ca9d4d5666eb08511063a4d43aa4d"));
    assert(genesis.hashMerkleRoot == uint256("0x73493cadda0b9042bae383208bccc06c47c46892ba8feea5d831d358eb1626d4"));

    base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,95);
    base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,35);
    base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,153);
    base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,75);
    base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
    base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

    vSeeds.push_back(CDNSSeedData("0","54.172.62.103"));
    vSeeds.push_back(CDNSSeedData("1","node.friendshipcoin.com"));

    convertSeeds(vFixedSeeds, pnSeed, ARRAYLEN(pnSeed), nDefaultPort);

    nPoolMaxTransactions = 3;
    strDarksendPoolDummyAddress = "f25gtaAQYBUNjYrxzZqNdyADSmwPPpWoLC";
    nLastPOWBlock = 20000;
    nPOSStartBlock = 1;
    nMasternodePaymentStartBlock = 50;
  }

  virtual const CBlock& GenesisBlock() const { return genesis; }
  virtual Network NetworkID() const { return CChainParams::MAIN; }

  virtual const vector<CAddress>& FixedSeeds() const {
    return vFixedSeeds;
  }
protected:
  CBlock genesis;
  vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
  CTestNetParams() {
    // The message start string is designed to be unlikely to occur in normal data.
    // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
    // a large 4-byte int at any alignment.
    pchMessageStart[0] = 0x11;
    pchMessageStart[1] = 0xc3;
    pchMessageStart[2] = 0xb1;
    pchMessageStart[3] = 0xdf;
    bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
    vAlertPubKey = ParseHex("0323740193a8560083f057e3bf354ce8b5739d4242cd9992d1fb95ebe9d0c626cd");
    nDefaultPort = 68008;
    nRPCPort = 68009;
    strDataDir = "testnet";

    // Modify the testnet genesis block so the timestamp is valid for a later start.
    //genesis.nBits  = 1505200027;
    //genesis.nNonce = 158232;

    //assert(hashGenesisBlock == uint256("0x0000f8525e103590ede75bf8b95a703c133e151c0de458c0b565eeaa6d2b7be5"));

    vFixedSeeds.clear();
    vSeeds.clear();

    base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,215);
    base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
    base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1,239);
    base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,40);
    base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
    base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

    convertSeeds(vFixedSeeds, pnTestnetSeed, ARRAYLEN(pnTestnetSeed), nDefaultPort);

    nLastPOWBlock = 0x7fffffff;
  }
  virtual Network NetworkID() const { return CChainParams::TESTNET; }
};

static CTestNetParams testNetParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
  assert(pCurrentParams);
  return *pCurrentParams;
}

CChainParams& Params(const std::string& chain) {
  if (chain == CBaseChainParams::MAIN) {
    return mainParams;
  } else if (chain == CBaseChainParams::TESTNET) {
    return testNetParams;
  //} else if (chain == CBaseChainParams::REGTEST) {
  //  return regTestParams;
  } else {
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
  }
}

void SelectParams(const std::string &network) {
  SelectBaseParams(network);
  pCurrentParams = &Params(network);
}
