// Copyright (c) 2018 The FriendshipCoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "pos.h"
#include "main.h"
#include "kernel.h"

double GetDifficulty(const CBlockIndex* blockindex) {
    // Floating point number that is a multiple of the minimum difficulty,
    // minimum difficulty = 1.0.
    if (blockindex == NULL) {
        if (pindexBest == NULL) {
            return 1.0;
        } else {
            blockindex = GetLastBlockIndex(pindexBest, false);
        }
    }

    int nShift = (blockindex->nBits >> 24) & 0xff;

    double dDiff =
        (double)0x0000ffff / (double)(blockindex->nBits & 0x00ffffff);

    while (nShift < 29) {
        dDiff *= 256.0;
        nShift++;
    }
    while (nShift > 29) {
        dDiff /= 256.0;
        nShift--;
    }

    return dDiff;
}

double GetPoSKernelPS() {
    int nPoSInterval = 72;
    double dStakeKernelsTriedAvg = 0;
    int nStakesHandled = 0, nStakesTime = 0;

    CBlockIndex* pindex = pindexBest;;
    CBlockIndex* pindexPrevStake = NULL;

    while (pindex && nStakesHandled < nPoSInterval) {
        if (pindex->IsProofOfStake()) {
            if (pindexPrevStake) {
                dStakeKernelsTriedAvg += GetDifficulty(pindexPrevStake) * 4294967296.0;
                nStakesTime += pindexPrevStake->nTime - pindex->nTime;
                nStakesHandled++;
            }
            pindexPrevStake = pindex;
        }

        pindex = pindex->pprev;
    }

    double result = 0;

    if (nStakesTime) {
        result = dStakeKernelsTriedAvg / nStakesTime;
    }

    result *= STAKE_TIMESTAMP_MASK + 1;

    return result;
}

double GetPoWMHashPS() {
    if (pindexBest->nHeight >= Params().LastPOWBlock()) {
        return 0;
    }

    int nPoWInterval = 72;
    int64_t nTargetSpacingWorkMin = 30, nTargetSpacingWork = 30;

    CBlockIndex* pindex = pindexGenesisBlock;
    CBlockIndex* pindexPrevWork = pindexGenesisBlock;

    while (pindex) {
        if (pindex->IsProofOfWork()) {
            int64_t nActualSpacingWork = pindex->GetBlockTime() - pindexPrevWork->GetBlockTime();
            nTargetSpacingWork = ((nPoWInterval - 1) * nTargetSpacingWork + nActualSpacingWork + nActualSpacingWork) / (nPoWInterval + 1);
            nTargetSpacingWork = max(nTargetSpacingWork, nTargetSpacingWorkMin);
            pindexPrevWork = pindex;
        }

        pindex = pindex->pnext;
    }

    return GetDifficulty() * 4294.967296 / nTargetSpacingWork;
}

// miner's coin stake reward
int64_t GetProofOfStakeReward(const CBlockIndex* pindexPrev, int64_t nCoinAge,
                              int64_t nFees) {
  int64_t nSubsidy = 0 * COIN;

  const int height = pindexBest->nHeight + 1;

  if (height > 1 && height <= 5040) {
    nSubsidy = 25 * COIN;
  } else if (height > 10080 && height <= 100000) {
    nSubsidy = 120 * COIN;
  } else if (height > 100000 && height <= 362800) {
    nSubsidy = 60 * COIN;
  } else if (height > 362800 && height <= 625600) {
    nSubsidy = 30 * COIN;
  } else if (height > 625600 && height <= 888400) {
    nSubsidy = 15 * COIN;
  } else if (height > 888400 && height <= 1151200) {
    nSubsidy = 3.75 * COIN;
  } else {
    nSubsidy = 1.85 * COIN;
  }

  return nSubsidy + nFees;
}

