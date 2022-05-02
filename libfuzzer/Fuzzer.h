#pragma once
#include <iostream>
#include <vector>
#include <liboracle/Common.h>
#include "ContractABI.h"
#include "Util.h"
#include "FuzzItem.h"
#include "Mutation.h"
#include "../libcfg/CFG/contract/Contract.h"

using namespace dev;
using namespace eth;
using namespace std;

namespace fuzzer {
  enum FuzzMode { AFL };
  enum Reporter { TERMINAL, JSON, BOTH };
  struct ContractInfo {
    string abiJson;
    string bin;
    string binRuntime;
    string contractName;
    string srcmap;
    string srcmapRuntime;
    string source;
    vector<string> constantFunctionSrcmap;
    bool isMain;
  };
  struct FuzzParam {
    vector<ContractInfo> contractInfo;
    FuzzMode mode;
    Reporter reporter;
    int duration;
    int analyzingInterval;
    string attackerName;
  };
  struct FuzzStat {
    int idx = 0;
    uint64_t maxdepth = 0;
    bool clearScreen = false;
    int totalExecs = 0;
    int queueCycle = 0;
    int stageFinds[32];
    double lastNewPath = 0;
  };
  struct Leader {
    FuzzItem item;
    float dt = 0;
    Leader(FuzzItem _item, float _dt): item(_item) {
      dt = _dt;
    }
  };
  class Fuzzer {
    vector<bool> vulnerabilities;
    vector<string> queues;
    unordered_set<string> tracebits;
    unordered_set<string> predicates;
    unordered_set<string> criticalTracebits;
    unordered_set<string> criticalPredicates;
    unordered_map<string, Leader> leaders;
    unordered_map<uint64_t, string> snippets;
    unordered_set<string> uniqExceptions;
    float maxD = -1;
    float minD = -1;
    int cfun = 0;
    int funs = 0;
    Timer timer;
    FuzzParam fuzzParam;
    FuzzStat fuzzStat;
    void writeStats(const Mutation &mutation, const tuple<unordered_set<uint64_t>, unordered_set<uint64_t>> &validJumpis);
    ContractInfo mainContract();
    Contract* fuzzedContract;
    public:
      Fuzzer(FuzzParam fuzzParam);
      FuzzItem saveIfInterest(TargetExecutive& te, bytes data, uint64_t depth, const tuple<unordered_set<uint64_t>, unordered_set<uint64_t>> &validJumpis, vector<pair<int, bool>> _realLen, vector<bool> _areCritical);
      void showStats(const Mutation &mutation, const tuple<unordered_set<uint64_t>, unordered_set<uint64_t>> &validJumpis);
      void updateTracebits(unordered_set<string> tracebits);
      void updatePredicates(unordered_map<string, u256> predicates);
      void updateCriticalTracebits(unordered_set<string> criticalTracebits);
      void updateCriticalPredicates(unordered_map<string, u256> criticalPredicates);
      void updateExceptions(unordered_set<string> uniqExceptions);
      void determineCriticism(ContractABI* mainCA);
      void start();
      void stop();
  };
}
