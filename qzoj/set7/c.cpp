#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class trie{
private:
    static constexpr auto ups=21;
    vector<unordered_map<int,int>> ch,chv;
    vector<vector<int>> up;
    vector<int> dep;
    int cnt;
public:
    auto compare(int u,int v)->bool{
        if(dep[u]<dep[v]) return !compare(v,u);
        cir(i,0,ups) if((dep[u]-dep[v])&(1<<i)) u=up[i][u];
        if(u==v) return false;
        for(auto i=ups-1;~i;--i) if(up[i][u]!=up[i][v]){
            u=up[i][u];v=up[i][v];
        }
        const auto f=up[0][u];
        return chv[f][u]<chv[f][v];
    }
    auto nodeafter(int u,int w){
        if(ch[u].contains(w)) return ch[u][w];
        ch[u][w]=++cnt;
        chv[u][cnt]=w;
        dep[cnt]=dep[u]+1;
        up[0][cnt]=u;
        cir(i,1,ups) up[i][cnt]=up[i-1][up[i-1][cnt]];
        return cnt;
    }
    trie(int _n):ch(_n),chv(_n),up(ups,vector<int>(_n)),dep(_n),cnt(0){}
};
static constexpr auto maxv=(int)(1e5+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,k;cin>>n>>k;
    lint b,m;cin>>b>>m;
    vector<int> a(n);
    for(auto&i:a) cin>>i;
    a.emplace(a.begin(),0);
    ++n;
    vector<vector<int>> w(maxv+1);
    cir(i,0,n) w[a[i]].emplace_back(i);
    vector<set<int>> ux(n);
    set<int> pos;
    for(auto i=n-1;~i;--i){
        ux[i]=pos;
        pos.emplace(a[i]);
        const auto lim=(i+500>n?n:20);
        while((int)(pos.size())>lim) pos.erase(prev(pos.end()));
    }
    vector<pair<int,int>> sta(k+7,{-1,-1});
    trie tr(k*2+7);
    vector<lint> ans;
    auto cnt=0;
    // trie node id, node-pos, father-id, hash-value
    vector<tuple<int,int,int,lint>> hp;
    vector<tuple<int,int,lint>> idlas(k+7);
    auto comp=[&](tuple<int,int,int,lint>&a,tuple<int,int,int,lint>&b){
        return tr.compare(get<0>(b),get<0>(a));
    };
    auto emplace=[&](tuple<int,int,int,lint> x){
        hp.emplace_back(x);
        push_heap(hp.begin(),hp.end(),comp);
    };
    auto top=[&]{
        return hp[0];
    };
    auto pop=[&]{
        pop_heap(hp.begin(),hp.end(),comp);
        hp.pop_back();
    };
    emplace({0,0,0,0});
    auto next_pos=[&](int uid){
        const auto[u,pos,curw]=idlas[uid];
        const auto[nxtv,nxtp]=sta[uid];
        if(nxtv<0){
            if(ux[pos].empty()) return;
            const auto x=*ux[pos].begin();
            const auto p=upper_bound(w[x].begin(),w[x].end(),pos)-w[x].begin();
            emplace({tr.nodeafter(u,x),w[x][p],uid,(curw*b+x)%m});
            sta[uid]={x,p};
        }else if(nxtp==(int)(w[nxtv].size())-1){
            if(*ux[pos].rbegin()<nxtv+1) return;
            const auto x=*ux[pos].upper_bound(nxtv);
            const auto p=upper_bound(w[x].begin(),w[x].end(),pos)-w[x].begin();
            emplace({tr.nodeafter(u,x),w[x][p],uid,(curw*b+x)%m});
            sta[uid]={x,p};
        }else{
            const auto x=nxtv;
            const auto p=nxtp+1;
            emplace({tr.nodeafter(u,x),w[x][p],uid,(curw*b+x)%m});
            sta[uid]={x,p};
        }
    };
    cir(i,0,k+1){
        const auto[u,pos,fid,curw]=top();pop();
        const auto uid=++cnt;
        if(i) ans.emplace_back(curw);
        idlas[uid]={u,pos,curw};
        if(i) next_pos(fid);
        next_pos(uid);
    }
    for(auto&i:ans) cout<<i<<'\n';
    return 0;
}
