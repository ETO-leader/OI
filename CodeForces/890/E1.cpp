#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
vector<VI> G;
VI siz;
lint dfs(int u,int f=0){
    VI sizx;lint res=0;
    for(auto&i:G[u]) if(i!=f){
        res+=dfs(i,u);
        sizx.push_back(siz[i]);
        siz[u]+=siz[i];
    }
    VI D(siz[u]);
    lint cnx=0;
    for(auto&s:sizx){
        for(lint i=cnx+s;~i;--i){
            for(int w=min(i,cnx);
                w>max<lint>(0,i-s)-1;--w){
                auto j=i-w;
                D[i]=max(D[i],
                    D[w]+j*(cnx-w)+w*(s-j));
            }
        }
        cnx+=s;
    }
    return res+
        *max_element(D.begin(),D.end());
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;G.resize(n+1);
    siz.resize(n+1,1);
    cir(i,2,n+1){
        int f;cin>>f;
        G[f].push_back(i);
        G[i].push_back(f);
    }
    cout<<dfs(1)<<'\n';
    return 0;
}
