#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    auto T=1;
    while(T--) [&]{
        int n,m;cin>>n>>m;
        vector vx(n,vector<int>(n));
        vector<int> sv(n);
        cir(i,0,m){
            int u,v;cin>>u>>v;--u;--v;
            vx[u][v]=vx[v][u]=true;
            sv[u]|=1<<v;
            sv[v]|=1<<u;
        }
        vector<int> circ;
        vector vis(n,vector<int>(1<<n));
        cir(p,0,n) if([&](this auto&&__self,int s,int u,int fs){
            vis[u][s]=true;
            if(fs==(1<<n)-1&&vx[u][p]) return circ.emplace_back(u),true;
            cir(i,p+1,n) if((!((s>>i)&1))&&vx[u][i]&&(!vis[i][s|(1<<i)])){
                if(__self(s|(1<<i),i,fs|sv[i])) return circ.emplace_back(u),true;
            }
            return false;
        }(1<<p,p,sv[p])) break;
        if(circ.empty()){
            cout<<"No"<<'\n';
        }else{
            cout<<"Yes"<<'\n';
            vector<int> ans(n);
            cir(i,0,(int)(circ.size())) ans[circ[i]]=circ[(i+1)%(int)(circ.size())];
            cir(i,0,n) if(!ranges::count(circ,i)){
                cir(j,0,n) if(vx[i][j]&&ranges::count(circ,j)){
                    ans[i]=j;break;
                }
            }
            for(auto&i:ans) cout<<i+1<<' ';
            cout<<'\n';
        }
    }();
    return 0;
}
