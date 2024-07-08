#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
const int MOD=998244353;
bool ck(int&st){
    return !(st&(st>>1)||st&(st<<1));
}
bool check(int&a,int&b){
    return !(a&b||(a>>1)&b||(a<<1)&b);
}
using VI=vector<int>;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k;cin>>n>>k;VI s;
    cir(i,0,(1<<k)) if(ck(i)) s.push_back(i);
    vector<VI> mp(n,VI(k));
    for(auto&i:mp) for(auto&j:i){
        char c;cin>>c;j=c-'0';
    }
    auto numck=[&](int x,int p){
        cir(i,0,k) if(mp[x][i]&&(p&(1<<i)))
            return false;
        return true;
    };
    const int _sz=s.size();
    vector<VI> D(n,VI(_sz));
    int st=0;D[st][0]=1;
    cir(i,0,n){
        st^=1;
        cir(j,0,_sz){
            D[st][j]=0;
            auto&sj=s[j];
            if(!numck(i,sj)) continue;
            cir(p,0,_sz){
                if(check(sj,s[p]))
                    (D[st][j]+=D[st^1][p])%=MOD;
            }
        }
    }
    cout<<[&](){
        int ans=0;
        for(auto&i:D[st]) (ans+=i)%=MOD;
        return ans;
    }()<<'\n';
    return 0;
}