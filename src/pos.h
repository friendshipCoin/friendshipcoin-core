// Copyright (c) 2018 The FriendshipCoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef FRIENDSHIPCOIN_POS_H
#define FRIENDSHIPCOIN_POS_H

#include <stdint.h>

class CBlockIndex;

double GetDifficulty(const CBlockIndex* blockindex = nullptr);
double GetPoSKernelPS();
double GetPoWMHashPS();
int64_t GetProofOfStakeReward(const CBlockIndex* pindexPrev, int64_t nCoinAge, int64_t nFees);

extern int64_t nLastCoinStakeSearchInterval;

#endif
