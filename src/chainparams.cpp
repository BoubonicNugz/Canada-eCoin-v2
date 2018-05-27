
// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

#include "chainparamsseeds.h"

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(txNew);
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 * CBlock(hash=4e9b54001f9976049830128ec0331515eaabe35a70970d79971da1539a400ba1, PoW=000001a16729477595c7247e1b49b4ec93acca8345037177cabbe898ce8a5783, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000,
 *     hashMerkleRoot=0317d32e01a2adf6f2ac6f58c7cdaab6c656edc6fdb45986c739290053275200,
 *     nTime=1405164774, nBits=1e01ffff, nNonce=4016033, vtx=1)
 *   CTransaction(hash=0317d32e01, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *   CTxIn(COutPoint(0000000000, 4294967295), coinbase 04ffff001d01044c4e426c6f636b20233331303337393a30303030303030303030303030303030323431323532613762623237626539376265666539323138633132393064666633366331666631323965633732313161)
 *   CTxOut(nValue=0.00000000, scriptPubKey=0459934a6a228ce9716fa0b13aa1cd)
 * vMerkleTree: 0317d32e01a2adf6f2ac6f58c7cdaab6c656edc6fdb45986c739290053275200
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "Joseph Wright Jr. was born on this day 1906";
    const CScript genesisOutputScript = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
**********************************************************************************************************8
**********************************************************************************************************8
**********************************************************************************************************8
**********************************************************************************************************8
**********************************************************************************************************8
**********************************************************************************************************8
**********************************************************************************************************8
**********************************************************************************************************8
**********************************************************************************************************8
**********************************************************************************************************8
**********************************************************************************************************8
**********************************************************************************************************8
**********************************************************************************************************8
**********************************************************************************************************8
**********************************************************************************************************8
**********************************************************************************************************8
**********************************************************************************************************8
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 500000;
        consensus.nMajorityEnforceBlockUpgrade = 15000;
        consensus.nMajorityRejectBlockOutdated = 19000;
        consensus.nMajorityWindow = 20000;
        consensus.BIP34Height = 10000000;
        consensus.BIP34Hash = uint256S("0x4e9b54001f9976049830128ee0331515eaabe35a70970d79971da1539a400ba1");


// TODO: WTF Do you think you are doing here?  dang, do more research.
        consensus.powLimit = uint256S("0x00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); // ~uint25(0) >> 23
        consensus.nPowTargetTimespan = 1 * 24 * 60 * 60; // 1 day
        consensus.nPowTargetSpacing = 1 * 30; // 30 Seconds


        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 8100; // 75% of nMinerConfirmationWindow
        consensus.nMinerConfirmationWindow = 30 * 24 * 60 * 2; // 3 days
        consensus.nCLTVStartBlock = -1;
        consensus.nBIP66MinStartBlock = 10000000;
        consensus.nAuxPowStartHeight = 0;  // AuxPow::START_MAINNET;
        consensus.nWitnessStartHeight = 10000000;

        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 6;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1232032894; // start + (1year/25)

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1530230400; // June 28, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1630230400;   // June 28, 2018

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1530230400; // June 28, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1630230400;   // June 28, 2018

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */

        // Canada eCoin: increase each by adding 2 to bitcoin's value.
        pchMessageStart[0] = 0xfd;
        pchMessageStart[1] = 0xc4;
        pchMessageStart[2] = 0xb9;
        pchMessageStart[3] = 0xde;
        nDefaultPort = 34339;
        nPruneAfterHeight = 100000;

        genesis = CreateGenesisBlock(1396006396, 800327, 0x1e0ffff0, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();





        // Canada eCoin


        printf("genesis.nNonce: %i\n", genesis.nNonce);
        printf("hashGenesisBlock: 0x%s\n", consensus.hashGenesisBlock.ToString().c_str());
        printf("genesis.hashMerkleRoot: 0x%s\n--\n", genesis.hashMerkleRoot.ToString().c_str());
        // Canada eCoin


        assert(consensus.hashGenesisBlock == uint256S("0x863626dadaef221e2e2f30ff3dacae44cabdae9e0028058072181b3fb675d94a"));
        assert(genesis.hashMerkleRoot == uint256S("0x8e4c0ff7bfebb1169080fac2206d0abc75dc66b717df750e3798bed0823ab82f"));

        // Note that of those with the service bits flag, most only support a subset of possible options
        // TODO - LED - Check which canadaecoin nodes support service bits and add the 'true' flag
        vSeeds.push_back(CDNSSeedData("bootstrap.canadaecoin.net", "196.53.35.176"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,28);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,5);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,199);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        // vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;

	checkpointData = (CCheckpointData) {
		boost::assign::map_list_of
            (       0, uint256S("0x863626dadaef221e2e2f30ff3dacae44cabdae9e0028058072181b3fb675d94a"))
            (  500000, uint256S("0xebf29329a443d7fed6050dbffd64a95c4c3b028e71ddc789cde3cb85867d9f17"))
            ( 1000000, uint256S("0x4847a1c1344a8c70d79885b964bf7503bfe17bd46e772c3f615d9f53a6a06c18"))
            ( 1500000, uint256S("0x83a86be024fc26dc81740fc0d91e90098094313817c37be9cc01921ddc9576a4"))
            ( 2000000, uint256S("0x93d6ec46f921a6d59703de394ad78c1df9dbdb6df5c20f40123fdf8fe3ba751a"))
            ( 2500000, uint256S("0x4ead1a31cd4e8b7125188151d38deb6faa2d3d70e8ff5ed512e9e1b06dccab83"))
            ( 3000000, uint256S("0x0894d23725f7d76a4a71fca85e6691f0179d9dd2d1ea95a7f0b0295ceb1b463f"))
            ( 3500000, uint256S("0xf6232ab89820642662715ddc300ed6e2a1efe965c5718c36d6ab388cf9d0b039")),
            // ( 1000, uint256S("0xd560450623f70e65aa2c7327a497cdccbcf46265fe6c42d22061d569e40a0f5d")),
            1396044482, // * UNIX timestamp of last checkpoint block
            10000,   // * total number of transactions between genesis and last checkpoint
			//   (the tx=... number in the SetBestChain debug.log lines)
			2000.0     // * estimated number of transactions per day after checkpoint
	};

    }
};
static CMainParams mainParams;

/**
**********************************************************************************************************8
**********************************************************************************************************8
**********************************************************************************************************8
**********************************************************************************************************8
**********************************************************************************************************8
**********************************************************************************************************8
**********************************************************************************************************8
**********************************************************************************************************8
**********************************************************************************************************8
**********************************************************************************************************8
**********************************************************************************************************8
**********************************************************************************************************8
**********************************************************************************************************8
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 657000;
        consensus.nMajorityEnforceBlockUpgrade = 510;
        consensus.nMajorityRejectBlockOutdated = 750;
        consensus.nMajorityWindow = 1000;
        consensus.BIP34Height = -1;
        consensus.BIP34Hash = uint256S("0x0");
        consensus.powLimit = uint256S("0x00ffff0000000000000000000000000000000000000000000000000000"); // ~uint25(0) >> 19
        consensus.nPowTargetTimespan = 1 * 24 * 60 * 60; // 1 day
        consensus.nPowTargetSpacing = 1 * 30;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 2700; // 75% of nMinerConfirmationWindow
        consensus.nMinerConfirmationWindow = 3600; // nPowTargetTimespan / nPowTargetSpacing
        consensus.nCLTVStartBlock = 502664;
        consensus.nBIP66MinStartBlock = 800000;
        consensus.nAuxPowStartHeight = AuxPow::START_TESTNET;
        consensus.nWitnessStartHeight = 4040000;

        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 6;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1232032894; // start + (1year/25)

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1494547200; // May 12, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1526083200; // May 12, 2018

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1494547200; // May 12, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1526083200; // May 12, 2018

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00000000000000000000000000000000000000000000000000006fce5d67766e");
        // consensus.nMinimumChainWork = uint256S("0x0");

        pchMessageStart[0] = 0xfc;
        pchMessageStart[1] = 0xc1;
        pchMessageStart[2] = 0xb7;
        pchMessageStart[3] = 0xdc;
        nDefaultPort = 41331;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1395301765, 0, 0x1e0ffff0, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();




        // Canada eCoin
        printf("genesis.nNonce: %i\n", genesis.nNonce);
        printf("hashGenesisBlock: 0x%s\n", consensus.hashGenesisBlock.ToString().c_str());
        printf("genesis.hashMerkleRoot: 0x%s\n--\n", genesis.hashMerkleRoot.ToString().c_str());

//TODO verfity this mofocks
        assert(consensus.hashGenesisBlock == uint256S("0x63b9549fd0a58b6a10d95389374221c8c2fa3c97615df68aa14a22f2e26bc7d4"));
        assert(genesis.hashMerkleRoot == uint256S("0x8e4c0ff7bfebb1169080fac2206d0abc75dc66b717df750e3798bed0823ab82f"));
        // Canada eCoin

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("testnet.root.canadaecoin.net", "testnet.root.canadaecoin.net"));
        vSeeds.push_back(CDNSSeedData("testnet.dnsseed.canadaecoin.net", "testnet.dnsseed.canadaecoin.net"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,87);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,255);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = true;


        checkpointData = (CCheckpointData) {
                boost::assign::map_list_of
                ( 4230, uint256S("0x15a29dde01cbad777180c089bc8fcf0d7b4bd18993b47d8c301c41fc90ce8c8f")),
                1405625749,
                4440,
                5000
        };

    }
};
static CTestNetParams testNetParams;

/**
**********************************************************************************************************8
**********************************************************************************************************8
**********************************************************************************************************8
**********************************************************************************************************8
**********************************************************************************************************8
**********************************************************************************************************8
**********************************************************************************************************8
**********************************************************************************************************8
**********************************************************************************************************8
**********************************************************************************************************8
**********************************************************************************************************8
**********************************************************************************************************8
**********************************************************************************************************8
**********************************************************************************************************8
**********************************************************************************************************8
**********************************************************************************************************8
**********************************************************************************************************8
**********************************************************************************************************8
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 150;
        consensus.nMajorityEnforceBlockUpgrade = 7500;
        consensus.nMajorityRejectBlockOutdated = 9500;
        consensus.nMajorityWindow = 10000;
        consensus.BIP34Height = -1;
        consensus.BIP34Hash = uint256();
        consensus.powLimit = uint256S("0x00FFFF0000000000000000000000000000000000000000000000000000"); // ~uint25(0) >> 1
        consensus.nPowTargetTimespan = 14 * 24 * 60 * 60; // !  two weeks
        consensus.nPowTargetSpacing = 1 * 24;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
        consensus.nCLTVStartBlock = 1;
        consensus.nBIP66MinStartBlock = 1;
        consensus.nAuxPowStartHeight = AuxPow::START_REGTEST;
        consensus.nWitnessStartHeight = 20000;

        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 6;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 999999999999ULL;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        pchMessageStart[0] = 0x2d;
        pchMessageStart[1] = 0x97;
        pchMessageStart[2] = 0x7b;
        pchMessageStart[3] = 0x37;
        nDefaultPort = 15224;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1405166035, 0, 0x207fffff, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();





        // Canada eCoin
       
        printf("genesis.nNonce: %i\n", genesis.nNonce);
        printf("hashGenesisBlock: 0x%s\n", consensus.hashGenesisBlock.ToString().c_str());
        printf("genesis.hashMerkleRoot: 0x%s\n--\n", genesis.hashMerkleRoot.ToString().c_str());

        assert(consensus.hashGenesisBlock == uint256S("0x87205f7199133e0586390bf6d315dd913ec50fe71831b4324bfb3a926a21c948"));
        assert(genesis.hashMerkleRoot == uint256S("0x8e4c0ff7bfebb1169080fac2206d0abc75dc66b717df750e3798bed0823ab82f"));
        // Canada eCoin

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;

	checkpointData = (CCheckpointData){
         boost::assign::map_list_of
            ( 0, uint256S("0xf0dae070f24fbc35311533a22aa85c0a616c84a1f22881612304d802acda286f")),
            1405166035,
			0,
			0
	};

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
    }

    void UpdateBIP9Parameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
    {
        consensus.vDeployments[d].nStartTime = nStartTime;
        consensus.vDeployments[d].nTimeout = nTimeout;
    }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = 0;

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
            return mainParams;
    else if (chain == CBaseChainParams::TESTNET)
            return testNetParams;
    else if (chain == CBaseChainParams::REGTEST)
            return regTestParams;
    else
        throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

void UpdateRegtestBIP9Parameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    regTestParams.UpdateBIP9Parameters(d, nStartTime, nTimeout);
}
