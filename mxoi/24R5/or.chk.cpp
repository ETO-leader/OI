#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ifstream fcin("or.in");
    int T;fcin>>T;
    // assert(T==1);
    lint l,r;fcin>>l>>r;
    const auto chk=r-l+1;
    unordered_set<lint> ans;
    cir(s,1,(1<<chk)){
        auto x=0ll;
        cir(i,0,chk) if(s&(1<<i)){
            x|=(l+i);
        }
        ans.insert(x);
    }
    cout<<ans.size()<<'\n';
}
