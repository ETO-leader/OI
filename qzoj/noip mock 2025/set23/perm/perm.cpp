#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("perm.in");
ofstream ouf("perm.out");
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
constexpr auto choose_pair(lint x){
    return x*(x-1)%MOD;
}
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n,l;inf>>n>>l;
    const auto sqr=(int)(floorl(sqrt(l)));
    vector<int> a(n);
    for(auto&i:a) inf>>i;
    vector<pair<int,int>> ql,qr;
    for(auto&x:a){
        if(x>0){
            if(x>sqr) ql.emplace_back(l/x,1);
            else ql.emplace_back(x,0); 
        }else{
            if(-x>sqr) qr.emplace_back(l/(-x),1);
            else qr.emplace_back(-x,0);
        }
    }
    auto calc=[&](vector<pair<int,int>> q){
        sort(q.begin(),q.end(),greater<>());
        vector<vector<array<array<lint,2>,2>>> f(2,vector<array<array<lint,2>,2>>(n+7));
        auto cur=0;
        f[cur][0][0][0]=1;
        auto cnt=0;
        for(auto&[v,t]:q){
            ++cnt;
            cir(c,0,n+1) cir(rl,0,2) cir(rr,0,2) if(f[cur][c][rl][rr]){
                if(!t){
                    // Insert @ left
                    (f[cur^1][c][false][rr]+=f[cur][c][rl][rr])%=MOD;
                    // Insert @ right
                    (f[cur^1][c+1][rr][false]+=f[cur][c][rl][rr])%=MOD;
                }else{
                    // Insert @ left
                    f[cur^1][c+1][true][cnt==1]=f[cur][c][rl][rr];
                    // Insert @ right
                    f[cur^1][c][cnt==1][true]=f[cur][c][rl][rr];
                }
            }
        }
    };
    const auto fp=calc(ql);
    const auto fn=calc(qr);
    // clog<<fp[1][1][1]<<' '<<fn[0][0][0]<<'\n';
    auto ans=0ll;
    cir(i,0,n+1) cir(vl,0,2) cir(vr,0,2){
        const auto vcnt=((vl&&vr)?(i-1):((!(vl||vr)?(i+1):i)));
        if(vcnt>-1) clog<<i<<' '<<vl<<' '<<vr<<' '<<vcnt<<" --> "<<fp[i][vl][vr]<<' '<<fn[vcnt][!vl][!vr]<<'\n';
        if(vcnt>-1) (ans+=fp[i][vl][vr]*fn[vcnt][!vl][!vr])%=MOD;
    }
    ouf<<ans<<'\n';
    return 0;
}
