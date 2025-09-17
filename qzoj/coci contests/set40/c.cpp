#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m,k;cin>>n>>m>>k;
    vector<string> a(n);
    for(auto&x:a) cin>>x;
    vector<vector<int>> vx(n*m),succ(n,vector<int>(m,-1));
    auto dfs=[&](auto __self,int x,int y)->int {
        if(y==m-1) return succ[x][y]=true;
        if(succ[x][y]>-1) return succ[x][y];
        if(succ[x][y]==-2) return false;
        succ[x][y]=-2;
        const auto nx=x+(a[x][y]=='U'?-1:(a[x][y]=='D'?1:0));
        const auto ny=y+(a[x][y]=='L'?-1:(a[x][y]=='R'?1:0));
        const auto res=__self(__self,nx,ny);
        if(res) vx[nx*m+ny].emplace_back(x*m+y);
        return succ[x][y]=res;
    };
    cir(i,0,n) dfs(dfs,i,0);
    vector<pair<int,int>> nvalid;
    cir(i,0,n) cir(j,0,m-1) if(succ[i][j]<1) nvalid.emplace_back(i,j);
    vector<uint64_t> f(n*m);
    auto merge=[&](uint64_t a,uint64_t b){
        auto res=(uint64_t)(0);
        cir(i,0,k+1) if((a>>i)&1) res|=(b<<i);
        return res;
    };
    auto calc=[&](auto __self,int u){
        if(!(u%m)) return f[u]=2;
        f[u]=1;
        for(auto&i:vx[u]) f[u]=merge(f[u],__self(__self,i));
        return (f[u]|=2);
    };
    vector<int> ans;
    auto generate=[&](auto __self,int u,int req){
        if(req==1&&(u%m!=m-1)) return ans.emplace_back(u),void();
        auto w=(uint64_t)(1);
        vector<uint64_t> pv;
        for(auto&i:vx[u]){
            pv.emplace_back(w);
            w=merge(w,f[i]);
        }
        auto pcnt=0;
        for(auto i=(int)(vx[u].size())-1;~i;--i){
            cir(uw,0,k+1) if((req-pcnt-uw>-1)&&((f[vx[u][i]]>>uw)&1)&&(pv[i]>>(req-(pcnt+uw)))&1){
                __self(__self,vx[u][i],uw);
                pcnt+=uw;
                break;
            }
        }
    };
    auto w=(uint64_t)(1);
    vector<uint64_t> pv;
    vector<int> ux;
    cir(i,0,n) if(succ[i][m-1]==1){
        pv.emplace_back(w);
        w=merge(w,calc(calc,i*m+(m-1)));
        ux.emplace_back(i*m+(m-1));
    }
    auto v=-1;
    cir(i,0,k+1) if(((w>>i)&1)&&((int)(nvalid.size())>k-i-1)) v=i;
    if(v>-1){
        cir(i,0,k-v) cout<<nvalid[i].first+1<<' '<<nvalid[i].second+1<<'\n';
        auto pcnt=0;
        for(auto i=(int)(ux.size())-1;~i;--i){
            cir(uw,0,k+1) if((v-pcnt-uw>-1)&&((f[ux[i]]>>uw)&1)&&(pv[i]>>(v-(pcnt+uw)))){
                generate(generate,ux[i],uw);
                pcnt+=uw;
                break;
            }
        }
        for(auto&x:ans){
            cout<<(x/m)+1<<' '<<(x%m)+1<<'\n';
        }
    }else{
        cout<<-1<<'\n';
    }
    return 0;
}

