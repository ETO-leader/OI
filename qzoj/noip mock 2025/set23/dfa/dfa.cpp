#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
ifstream inf("dfa.in");
ofstream ouf("dfa.out");
using lint=long long;
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int T;inf>>T;
    while(T--) []{
        int n;inf>>n;
        vector<int> mi(n),mf(n);
        for(auto&x:mi) inf>>x,--x;
        for(auto&x:mf) inf>>x,--x;
        vector<int> c(n);
        for(auto&i:c) inf>>i;
        int u,v;inf>>u>>v;--u;--v;
        if(n<(int)(6e4)){
            vector<vector<bool>> vis(n,vector<bool>(n));
            queue<tuple<int,int,int>> q;
            q.emplace(u,v,0);
            auto ans=-1;
            while(!q.empty()){
                const auto[x,y,d]=q.front();q.pop();
                // use 'i'
                if(!vis[mi[x]][mi[y]]){
                    if(c[mi[x]]!=c[mi[y]]){
                        ans=d+1;
                        break;
                    }
                    vis[mi[x]][mi[y]]=true;
                    q.emplace(mi[x],mi[y],d+1);
                }
                // use 'f'
                if(!vis[mf[x]][mf[y]]){
                    if(c[mf[x]]!=c[mf[y]]){
                        ans=d+1;
                        break;
                    }
                    vis[mf[x]][mf[y]]=true;
                    q.emplace(mf[x],mf[y],d+1);
                }
            }
            if(ans<0) ouf<<"Impossible"<<'\n';
            else ouf<<ans<<'\n';
        }else{
            unordered_map<int,unordered_map<int,int>> vis;
            queue<tuple<int,int,int>> q;
            q.emplace(u,v,0);
            auto ans=-1;
            while(!q.empty()){
                const auto[x,y,d]=q.front();q.pop();
                // use 'i'
                if(!vis[mi[x]][mi[y]]){
                    if(c[mi[x]]!=c[mi[y]]){
                        ans=d+1;
                        break;
                    }
                    vis[mi[x]][mi[y]]=true;
                    q.emplace(mi[x],mi[y],d+1);
                }
                // use 'f'
                if(!vis[mf[x]][mf[y]]){
                    if(c[mf[x]]!=c[mf[y]]){
                        ans=d+1;
                        break;
                    }
                    vis[mf[x]][mf[y]]=true;
                    q.emplace(mf[x],mf[y],d+1);
                }
            }
            if(ans<0) ouf<<"Impossible"<<'\n';
            else ouf<<ans<<'\n';
        }
    }();
    return 0;
}
