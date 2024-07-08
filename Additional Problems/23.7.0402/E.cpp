#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,d;cin>>n>>m>>d;
    vector<lint> r(m+1),w(m);
    for(auto&i:r) cin>>i;
    r.erase(r.begin());
    for(auto&i:w) cin>>i;
    cir(i,0,m-1) w[i]-=w[i+1];
    auto calc=[&](int p){
        vector<lint> res(d+1);
        res[0]=[&](){
            lint cnx=0;
            cir(i,0,m) cnx+=min<lint>(p,r[i]/d+1)*w[i];
            return cnx;
        }();
        cir(i,0,m) if(r[i]/d+1<=p)
            res[r[i]%d+1]-=w[i];
        cir(i,1,d+1) res[i]+=res[i-1];
        return res;
    };
    auto as1=calc(n/2),as2=calc((n+1)/2);
    cout<<[&](){
        lint res=0;
        cir(i,0,d+1) res=max(res,as1[i]+as2[d-i]);
        return res;
    }()<<'\n';
    return 0;
}
