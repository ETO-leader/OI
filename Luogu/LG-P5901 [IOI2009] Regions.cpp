#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<int>;
using VL=vector<lint>;
vector<VI> G;vector<VL> cx,ck;
VI tin,tout,w,col;
void dfs(int u,int&cnx,int f=0){
    tin[u]=++cnx;
    for(auto&i:G[u]) if(i!=f) dfs(i,cnx,u);
    tout[u]=cnx;
}
bool isancestor(int u,int v){
    return tin[u]<=tin[v]&&tout[v]<=tout[u];
}
void dfsx(int u,int ci,int wx=0,int f=0){
    w[u]=(wx+=(col[u]==ci));
    for(auto&i:G[u]) if(i!=f) dfsx(i,ci,wx,u);
}
void init(int n){
    G.resize(n+1);tin.resize(n+1);col.resize(n+1);
    tout.resize(n+1);w.resize(n+1);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,r,q;cin>>n>>r>>q;init(n);
    const int sqr=sqrt(n*log2(n)*4)+1;
    VL cnx(r+1),idx(n+1);
    vector<VI> ci(r+1),ex(r+1);
    cin>>col[1];cnx[col[1]]++;ci[col[1]].push_back(1);
    cir(i,2,n+1){
        int f;cin>>f>>col[i];cnx[col[i]]++;
        G[f].push_back(i);G[i].push_back(f);
        ci[col[i]].push_back(i);
    }
    [&](){int ncnx=0;dfs(1,ncnx);}();
    cir(i,1,r+1){
        if(cnx[i]>sqr){
            idx[i]=cx.size();cx.push_back(VL(r+1));
            fill(w.begin(),w.end(),0);
            dfsx(1,i);
            cir(j,1,n+1) cx[idx[i]][col[j]]+=w[j];
            ck.push_back(VL(r+1));
            VI cw(n+7);
            for(auto&j:ci[i]) cw[tin[j]]++;
            cir(i,1,n+1) cw[i]+=cw[i-1];
            cir(j,1,n+1)
                ck[idx[i]][col[j]]+=cw[tout[j]]-cw[tin[j]-1];
        }else{
            for(auto&j:ci[i]){
                ex[i].push_back(tin[j]);
                ex[i].push_back(-tout[j]-1);
            }
            sort(ex[i].begin(),ex[i].end(),
                [&](int a,int b){return abs(a)<abs(b);});
            sort(ci[i].begin(),ci[i].end(),
                [&](int a,int b){return tin[a]<tin[b];});
        }
    }
    auto bfdis=[&](int c1,int c2){
        lint res=0,pre=0,p=0;
        for(auto&i:ci[c2]){
            while(p<ex[c1].size()){
                const int vx=ex[c1][p];
                if(abs(vx)>tin[i]) break;
                pre+=(vx<0?-1:1);++p;
            }
            res+=pre;
        }
        return res;
    };
    cir(i,0,q){
        int r1,r2;cin>>r1>>r2;
        if(cnx[r1]>sqr) cout<<cx[idx[r1]][r2]<<'\n';
        else if(cnx[r2]>sqr) cout<<ck[idx[r2]][r1]<<'\n';
        else cout<<bfdis(r1,r2)<<'\n';
        cout.flush();
    }
    return 0;
}
