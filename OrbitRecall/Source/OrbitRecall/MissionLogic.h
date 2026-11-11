#pragma once
#include <array>
// Engine-independent mission rules. A mistake preserves the sequence for a retry.
struct FMissionLogic {
 int Stage=0, Cursor=0, Mistakes=0;
 std::array<int,5> Sequence{{0,1,2,0,0}};
 bool Complete() const { return Stage>=3; }
 int Length() const { return 3+Stage; }
 template<class Random> void Generate(Random Rand) {
  Cursor=0;
  for(int i=0;i<5;++i) Sequence[i]=Rand();
 }
 // -1 = incorrect, 0 = next symbol, 1 = stage passed, 2 = all systems ready.
 int Submit(int Symbol) {
  if(Complete() || Symbol<0 || Symbol>3) return 0;
  if(Symbol!=Sequence[Cursor]) { ++Mistakes; Cursor=0; return -1; }
  if(++Cursor<Length()) return 0;
  ++Stage; Cursor=0; return Complete()?2:1;
 }
 void Reset() { *this=FMissionLogic(); }
};
