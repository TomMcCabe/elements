// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "hash.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>
#include <boost/scoped_ptr.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */
static Checkpoints::MapCheckpoints mapCheckpoints;
static const Checkpoints::CCheckpointData data = {
        &mapCheckpoints,
        0, // * UNIX timestamp of last checkpoint block
        0, // * total number of transactions between genesis and last checkpoint
                    //   (the tx=... number in the SetBestChain debug.log lines)
        0  // * estimated number of transactions per day after checkpoint
    };

static Checkpoints::MapCheckpoints mapCheckpointsTestnet;
static const Checkpoints::CCheckpointData dataTestnet = {
        &mapCheckpointsTestnet,
        0,
        0,
        0
    };

static Checkpoints::MapCheckpoints mapCheckpointsRegtest;
static const Checkpoints::CCheckpointData dataRegtest = {
        &mapCheckpointsRegtest,
        0,
        0,
        0
    };

class CMainParams : public CChainParams {
public:
    CMainParams(CScript scriptDestination) {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /** 
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xf9;
        pchMessageStart[1] = 0xbe;
        pchMessageStart[2] = 0xb4;
        pchMessageStart[3] = 0xd9;
        scriptAlert = CScript() << CScript::EncodeOP_N(2) << ParseHex("02174eda07d3dc89145f4b217702250d76d753229f11b380ecbb1f7c5c5c342ae0") << ParseHex("02a01aaa27b468ec3fb2ae0c2a9fa1d5dce9b79b35062178f479156d8daa6c0e50") << ParseHex("02519b8fb02f3c44f9912eda3da8651a7d63a8232479fbe880ded1b092aa14da63") << CScript::EncodeOP_N(3) << OP_CHECKMULTISIG;
        nDefaultPort = 8333;
        bnProofOfWorkLimit = ~uint256(0) >> 32;
        nSubsidyHalvingInterval = 210000;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 14 * 24 * 60 * 60; // two weeks
        nTargetSpacing = 10 * 60;

        /**
         * Build the genesis block.
         * 
         * CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1231006505, nBits=1d00ffff, nNonce=2083236893, vtx=1)
         *   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
         *   vMerkleTree: 4a5e1e
         */
        const char* pszTimestamp = "The Times 03/Jan/2009 Chancellor on brink of second bailout for banks";
        CMutableTransaction txNew;
        txNew.nVersion = 1;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = MAX_MONEY;
        uint256 bitcoinGenesisHash = uint256("0x000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f");
        uint160 bitcoinSecondSPKHash = Hash160(CScript() << OP_DROP << CScriptNum(144) << OP_LESSTHANOREQUAL);
        txNew.vout[0].scriptPubKey = CScript() << std::vector<unsigned char>(bitcoinGenesisHash.begin(), bitcoinGenesisHash.end()) << std::vector<unsigned char>(bitcoinSecondSPKHash.begin(), bitcoinSecondSPKHash.end()) << OP_WITHDRAWPROOFVERIFY;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1231006505;
        if (scriptDestination.empty()) {
            scriptDestination = CScript() << OP_2 << ParseHex("02174eda07d3dc89145f4b217702250d76d753229f11b380ecbb1f7c5c5c342ae0") << ParseHex("02a01aaa27b468ec3fb2ae0c2a9fa1d5dce9b79b35062178f479156d8daa6c0e50") << ParseHex("02519b8fb02f3c44f9912eda3da8651a7d63a8232479fbe880ded1b092aa14da63") << OP_3 << OP_CHECKMULTISIG;
        }
        genesis.proof = CProof(scriptDestination, CScript()); // genesis block gets a PoW pass

        hashGenesisBlock = genesis.GetHash();
        mapCheckpoints[0] = hashGenesisBlock;

        base58Prefixes[PUBKEY_ADDRESS] = list_of(0);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(5);
        base58Prefixes[BLINDED_ADDRESS]= list_of(10);
        base58Prefixes[SECRET_KEY] =     list_of(128);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4);

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        return data;
    }
};

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams {
public:
    CTestNetParams(CScript scriptDestination) : CMainParams(scriptDestination) {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xee;
        pchMessageStart[1] = 0xa1;
        pchMessageStart[2] = 0x1f;
        pchMessageStart[3] = 0xfa;
        nDefaultPort = 4250;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 14 * 24 * 60 * 60; //! two weeks
        nTargetSpacing = 10 * 60;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1296688602;

        hashGenesisBlock = genesis.GetHash();
        mapCheckpointsTestnet[0] = hashGenesisBlock;

        vFixedSeeds.clear();
        //vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("our_ip", "173.31.39.168"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(111);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(196);
        base58Prefixes[BLINDED_ADDRESS]= list_of(25);
        base58Prefixes[SECRET_KEY]     = list_of(239);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94);

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        return dataTestnet;
    }
};

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams(CScript scriptDestination) : CTestNetParams(scriptDestination) {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0xbf;
        pchMessageStart[2] = 0xb5;
        pchMessageStart[3] = 0xda;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 14 * 24 * 60 * 60; //! two weeks
        nTargetSpacing = 10 * 60;
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1296688602;
        nDefaultPort = 18444;

        CMutableTransaction txNew(genesis.vtx[0]);
        txNew.vout.resize(2);
        txNew.vout[0].nValue = MAX_MONEY / 2;
        txNew.vout[1].nValue = MAX_MONEY / 2;
        txNew.vout[1].scriptPubKey = CScript() << OP_TRUE;
        genesis.vtx[0] = CTransaction(txNew);

        if (scriptDestination.empty()) {
            scriptDestination = CScript() << OP_TRUE;
        }
        genesis.proof = CProof(scriptDestination, CScript()); // genesis block gets a PoW pass
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();

        hashGenesisBlock = genesis.GetHash();
        mapCheckpointsRegtest[0] = hashGenesisBlock;

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Regtest mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        return dataRegtest;
    }
};

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams {
public:
    CUnitTestParams(CScript scriptDestination) : CMainParams(scriptDestination) {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 18445;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval)  { nSubsidyHalvingInterval=anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority)  { nEnforceBlockUpgradeMajority=anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority)  { nRejectBlockOutdatedMajority=anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority)  { nToCheckBlockUpgradeMajority=anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks)  { fDefaultConsistencyChecks=afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) {  fAllowMinDifficultyBlocks=afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};

static boost::scoped_ptr<CChainParams> globalChainParams;
static boost::scoped_ptr<CChainParams> globalSwitchingChainParams;

const CChainParams &Params() {
    assert(globalChainParams.get());
    return *globalChainParams;
}

CChainParams* CChainParams::Factory(CBaseChainParams::Network network, CScript scriptDestination) {
    switch (network) {
        case CBaseChainParams::MAIN:
            return new CMainParams(scriptDestination);
        case CBaseChainParams::TESTNET:
            return new CTestNetParams(scriptDestination);
        case CBaseChainParams::REGTEST:
            return new CRegTestParams(scriptDestination);
        case CBaseChainParams::UNITTEST:
            return new CUnitTestParams(scriptDestination);
        default:
            assert(false && "Unimplemented network");
            return NULL;
    }
}

const CChainParams& Params(CBaseChainParams::Network network)
{
    globalSwitchingChainParams.reset(CChainParams::Factory(network, CScript()));
    return *globalSwitchingChainParams;
}

void SelectParams(CBaseChainParams::Network network, CScript scriptDestination) {
    SelectBaseParams(network);
    globalChainParams.reset(CChainParams::Factory(network, scriptDestination));
}

void SelectParams(CBaseChainParams::Network network) {
    SelectParams(network, CScript());
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    CScript scriptDestination = ScriptDestinationFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network, scriptDestination);
    return true;
}
