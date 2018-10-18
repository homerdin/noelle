#pragma once

#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instructions.h"

#include "SCC.hpp"
#include "SCCDAGPartition.hpp"
#include "InvocationLatency.hpp"

using namespace std;

namespace llvm {

  class PartitionCostAnalysis {
   public:
    PartitionCostAnalysis (InvocationLatency &IL, SCCDAGPartition &p);

    void traverseAllPartitionSubsets ();

    virtual void checkIfShouldMerge (int sA, int sB) = 0;

    void resetCandidateSubsetInfo ();

    bool mergeCandidateSubsets ();

   protected:
    InvocationLatency &IL;
    SCCDAGPartition &partition;

    uint64_t totalCost;
    uint64_t totalInstCount;
    std::unordered_map<int, uint64_t> subsetCost;
    std::unordered_map<int, uint64_t> subsetInstCount;

    int minSubsetA;
    int minSubsetB;
    uint64_t loweredCost;
    uint64_t instCount;
    uint64_t mergedSubsetCost;
  };

}