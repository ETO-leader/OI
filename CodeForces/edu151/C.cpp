#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
vector<set<int>> vst;
vector<vector<int>> vis;
string s,l,r;
bool dfs(int p,int sp){
    if(p==(int)(l.size())) return false;
    if(vis[p][sp+1]) return false;
    cir(i,l[p]-'0',r[p]-'0'+1){
        auto upb=vst[i].upper_bound(sp);
        if(upb==vst[i].end()) return true;
        if(dfs(p+1,*upb)) return true;
    }
    vis[p][sp+1]=true;
    return false;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        lint m;cin>>s>>m>>l>>r;
        vst.clear();vst.resize(10);
        cir(i,0,s.size()) vst[s[i]-'0'].insert(i);
        vis.clear();
        vis.assign(m,vector<int>(s.size()+1));
        cout<<(dfs(0,-1)?"YES\n":"NO\n");
    }
    return 0;
}
