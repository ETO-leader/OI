#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
const int MOD=998244353;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;valarray<lint> val(n);
    for(auto&i:val) cin>>i;
    int m;cin>>m;
    vector<int> Tp(m),P(m),V(m);
    vector<vector<int>> Call(m);
    cir(i,0,m){
        cin>>Tp[i];int k,c;
        switch(Tp[i]){
            case 1:cin>>P[i]>>V[i];break;
            case 2:cin>>V[i];break;
            default:
                cin>>k;
                while(k--) cin>>c,Call[i].push_back(c-1);
                break;
        }
    }
    function<void(int)> Calls=[&](int x){
        if(Tp[x]==1){(val[P[x]-1]+=V[x])%=MOD;return;}
        if(Tp[x]==2){(val*=V[x])%=MOD;return;}
        function<void(int)> CallSelf=[&](int gx){
            Calls(gx);
        };
        for(auto&i:Call[x]) CallSelf(i);
    };
    int q,x;cin>>q;
    while(q--) cin>>x,Calls(x-1);
    for(auto&i:val) cout<<i%MOD<<' ';
    cout<<endl;
    return 0;
}