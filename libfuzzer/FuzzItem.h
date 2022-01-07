#pragma once
#include "TargetContainer.h"
#include "Common.h"

using namespace std;
using namespace dev;
using namespace eth;

namespace fuzzer {
  struct FuzzItem {
    bytes data;
    /* record the real length of each paramater in data for adaptive mutation */
    vector<pair<int, bool>> realLen;
    /* record if the paramater belongs to a critical function */
    vector<bool> areCritical;
    TargetContainerResult res;
    uint64_t fuzzedCount = 0;
    uint64_t depth = 0;
    FuzzItem(bytes _data, vector<pair<int, bool>> _realLen, vector<bool> _areCritical) {
      data = _data;
      realLen = _realLen;
      areCritical = _areCritical;
    }
  };
  using OnMutateFunc = function<FuzzItem (bytes b)>;
}
