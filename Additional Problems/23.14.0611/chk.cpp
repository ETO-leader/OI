#include"testlib.h"
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
const int MOD=1e9+7;
int main(int argc,char*argv[]){
    registerTestlibCmd(argc,argv);
	int n=inf.readInt();
	auto arra=ouf.readLongs(n,0LL,MOD);
	auto arrb=ans.readLongs(n,0LL,MOD);
	if(arra!=arrb)
		quitf(_wa,"Wrong Answer\n");
	quitf(_ok,"Accepted\n");
	return 0;
}