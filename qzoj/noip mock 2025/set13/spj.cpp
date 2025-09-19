#include"testlib.h"
#include"jurys.h"

int main(int argc,char*argv[]){
    registerTestlibCmd(argc,argv);
    const auto pans=ouf.readLong();
    const auto jans=ans.readLong();
    if(pans!=jans){
        quitf(_wa,"expected %lld, found %lld.\n",jans,pans);
    }
    const auto lines=count_lines(inf);
    vector<pair<int,int>> pa,ja;
    cir(i,0,lines){
        auto u=ouf.readInt(),v=ouf.readInt();
        pa.emplace_back(u,v);
    }
    cir(i,0,lines){
        auto u=ans.readInt(),v=ans.readInt();
        ja.emplace_back(u,v);
    }
    sort(pa.begin(),pa.end());
    sort(ja.begin(),ja.end());
    if(pa!=ja){
        quitf(_wa,"edges do not match.\n");
    }
    quitf(_ok,"correct answer with %d lines.\n",lines);
}
