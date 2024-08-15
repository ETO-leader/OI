#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("or.in");
ofstream fcout("or.ans");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;fcin>>T;
    while(T--) [&](){
        lint l,r;fcin>>l>>r;
        fcout<<[&](){
            for(auto p=62;~p;--p){
                if((l>>p)!=(r>>p)){
                    const auto pw=1ll<<p,x=pw-l,y=[&](lint w){
                        auto res=1ll;
                        for(;res<w;res<<=1);
                        return res;
                    }(r-pw+1);
                    return x+min(x+y,pw);
                }
                (l|=(1ll<<p))^=(1ll<<p);
                (r|=(1ll<<p))^=(1ll<<p);
            }
            return 1ll;
        }()<<'\n';
    }();
    return 0;
}
