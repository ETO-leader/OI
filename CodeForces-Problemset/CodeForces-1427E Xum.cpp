#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using ull=unsigned long long;
const ull nmax=1e18;
struct oper{ull x,y;char op;};
ostream&operator<<(ostream&os,oper op){
    return os<<op.x<<' '<<op.op<<' '<<op.y;
}
vector<oper> opl;
unordered_set<ull> ins;
void newoper(ull x,ull y,bool isx){
    if(isx){
        if(ins.count(x^y)) return;
        ins.insert(x^y);
        opl.push_back({x,y,'^'});
    }else{
        if(ins.count(x+y)) return;
        ins.insert(x+y);
        opl.push_back({x,y,'+'});
    }
}
class xorbase{
private:
    vector<ull> bse;
public:
    void insert(ull x){
        for(int i=63;~i;--i){
            if(!(x&(1ULL<<i))) continue;
            if(!bse[i]){
                bse[i]=x;break;
            }
            newoper(x,bse[i],true);
            x^=bse[i];
        }
    }
    ull&operator()(int p){return bse[p];}
    xorbase():bse(64){}
};
mt19937 rnd(time(NULL));
const int rndx(){return rnd()%62;}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    ull x;cin>>x;xorbase bse;
    bse.insert(x);
    while(!ins.count(1)){
        int x=rndx(),y=rndx();
        while((!bse(x))||(!bse(y)))
            x=rndx(),y=rndx();
        if(bse(x)+bse(y)>nmax) continue;
        newoper(bse(x),bse(y),false);
        bse.insert(bse(x)+bse(y));
    }
    cout<<opl.size()<<'\n';
    for(auto&i:opl) cout<<i<<'\n';
    return 0;
}
