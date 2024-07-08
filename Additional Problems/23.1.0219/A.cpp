#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
using lint=long long;
const int pw3=1e6+7;
vector<int> p,isp;
void prime(){
    isp.resize(pw3,true);
    isp[0]=isp[1]=false;
    cir(i,2,pw3){
        if(!isp[i]) continue;
        p.push_back(i);
        for(auto j=1LL*i*i;j<pw3;j+=i)
            isp[j]=false;
    }
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    lint x,cnt=0,k=1;cin>>x;
    prime();
    vector<int> pwx=[&](){
        vector<int> res(pw3);
        cir(i,1,pw3) res[i]=res[i-1]+isp[i];
        return res;
    }();
    while(k*k*k*k<x){
        auto vx=x/k;
        if(!isp[k]) goto ad;
        cnt+=pwx[lint(pow<long double>(vx,1.0L/3))]-pwx[k];
        ad:++k;
    }
    cout<<cnt<<'\n';
    return 0;
}
