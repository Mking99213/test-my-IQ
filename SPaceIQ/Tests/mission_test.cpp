#include "../Source/SPaceIQ/MissionLogic.h"
#include <cassert>
int main() {
 FMissionLogic M;
 for(int stage=0;stage<3;++stage) {
  int n=0; M.Generate([&](){return n++%4;});
  assert(M.Length()==3+stage);
  assert(M.Submit(3)==-1); assert(M.Cursor==0);
  for(int i=0;i<3+stage;++i) {
   int r=M.Submit(i%4);
   assert(r==(i==2+stage?(stage==2?2:1):0));
  }
 }
 assert(M.Complete()); assert(M.Mistakes==3);
 assert(M.Submit(0)==0);
 M.Reset(); assert(!M.Complete() && M.Mistakes==0 && M.Stage==0);
 M.Generate([](){return 2;});
 assert(M.Submit(-1)==0 && M.Cursor==0);
 assert(M.Submit(2)==0); assert(M.Submit(2)==0); assert(M.Submit(2)==1);
}
