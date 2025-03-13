#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,x,y;cin>>n>>x>>y;
    string s;cin>>s;
    vector<lint> val(n);
    for(auto&i:val) cin>>i;
    // x_i = 0 : '('
    // x_i = 1 : ')'
    auto check=[&](const int x){
        auto cnt=0;
        cir(i,0,n*2){
            cnt+=((x>>i)&1?-1:1);
            if(cnt<0) return false;
        }
        return !cnt;
    };
    auto checkx=[&](const int x,const int l){
        auto cnt=0;
        cir(i,0,l){
            cnt+=((x>>i)&1?-1:1);
            if(cnt<0) return false;
        }
        return !cnt;
    };
    auto vals=0;
    cir(i,0,n*2) if(s[i]==')') vals|=(1<<i);
    auto target=0;
    cir(i,n,n*2) target|=(1<<i);
    auto to_integer10=[&](vector<int> x){
        auto res=0;
        for(auto&i:x) (res*=10)+=i;
        return res;
    };
    vector<unordered_set<int>> vis(1<<(n*2));
    vector<vector<tuple<int,int,int,int>>> spl(1<<(n*2));
    cir(s,0,(1<<(n*2))) if(check(s)){
        cir(i,0,n*2) cir(j,i,n*2) cir(k,j+1,n*2){
            const auto sx=(s>>i)&((1<<(j-i+1))-1);
            const auto sy=(s>>(j+1))&((1<<(k-j))-1);
            if(checkx(sx,j-i+1)&&checkx(sy,k-j)) spl[s].emplace_back(i,j,j+1,k);
        }
    }
    priority_queue<tuple<lint,int,vector<int>>,vector<tuple<lint,int,vector<int>>>,greater<tuple<lint,int,vector<int>>>> q;
    q.emplace(0,vals,[&]{
        vector<int> a(n);
        iota(a.begin(),a.end(),0);
        return a;
    }());
    auto to_seq=[&](int x){
        vector<int> a;
        cir(i,0,n*2) a.emplace_back((x>>i)&1);
        return a;
    };
    auto to_integer2=[&](vector<int> x){
        auto res=0;
        cir(i,0,n*2) res|=(x[i]<<i);
        return res;
    };
    auto ans=-1ll;
    while(!q.empty()){
        const auto[w,s,v]=q.top();q.pop();
        if(s==target){ans=w;break;}
        if(vis[s].count(to_integer10(v))) continue;
        vis[s].emplace(to_integer10(v));
        auto seq=to_seq(s);
        vector<int> id(n*2);
        auto cur=-1;
        cir(i,0,n*2) if(!seq[i]) id[i]=++cur;
        for(auto&[al,ar,bl,br]:spl[s]){
            auto ns=seq;
            auto nv=v;
            vector<int> pos;
            cir(i,bl,br+1) pos.emplace_back(seq[i]);
            cir(i,al,ar+1) pos.emplace_back(seq[i]);
            cir(i,al,bl+1) ns[i]=pos[i-al];
            pos.clear();
            cir(i,bl,br+1) if(!seq[i]) pos.emplace_back(v[id[i]]);
            cir(i,al,ar+1) if(!seq[i]) pos.emplace_back(v[id[i]]);
            cur=-1;
            cir(i,al,br+1) if(!seq[i]) nv[id[i]]=pos[++cur];
            if(!vis[to_integer2(ns)].count(to_integer10(nv))){
                q.emplace(w,to_integer2(ns),nv);
            }
        }
        for(auto&[al,ar,bl,br]:spl[s]){
            auto ns=seq;
            auto nv=v;
            auto nw=w;
            swap(ns[ar],ns[bl]);
            nw+=x*val[v[id[al]]]+y*val[v[id[bl]]];
            if(!vis[to_integer2(ns)].count(to_integer10(nv))){
                q.emplace(nw,to_integer2(ns),nv);
            }
        }
    }
    cout<<ans<<'\n';
    return 0;
}
