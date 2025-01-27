#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto alpha=26;
static constexpr auto max_len_t=(int)(4e5+7);
class bit{
private:
    vector<int> w;
    constexpr auto lowbit(auto u) const{return u&(-u);}
public:
    auto update(int u,int wx){
        for(++u;u<(int)(w.size());u+=lowbit(u)) w[u]+=wx;
    }
    auto query(int u){
        auto res=0;
        for(++u;u;u-=lowbit(u)) res+=w[u];
        return res;
    }
    bit(int _n):w(_n+7){}
};
class acam{
private:
    vector<array<int,alpha>> ch,gfail;
    vector<int> fail,cntw,dfn,rdfn;
    vector<vector<int>> gr;
    bit bx;
    int cnt;
    auto dfs(int u,auto&cnt)->void{
        dfn[u]=++cnt;
        for(auto&i:gr[u]) dfs(i,cnt);
        rdfn[u]=cnt;
    }
public:
    auto init(){
        queue<int> q;q.emplace(0);
        while(!q.empty()){
            const auto u=q.front();q.pop();
            if(u) gr[fail[u]].emplace_back(u);
            cir(c,0,alpha) if(ch[u][c]){
                auto ux=fail[u];
                while(ux&&(!ch[ux][c])) ux=fail[ux];
                if(u) fail[ch[u][c]]=ch[ux][c];
                q.emplace(ch[u][c]);
            }
        }
        auto cnt=-1;
        dfs(0,cnt);
    }
    auto emplace(string s){
        auto u=0;
        for(auto&x:s){
            if(!ch[u][x-'a']) ch[u][x-'a']=++cnt;
            u=ch[u][x-'a'];
        }
        return u;
    }
    auto move(int u,char c){
        if((!u)||ch[u][c-'a']) return ch[u][c-'a'];
        if(gfail[u][c-'a']>-1) return gfail[u][c-'a'];
        return gfail[u][c-'a']=move(fail[u],c);
    }
    auto check(int u,int w){
        bx.update(dfn[u],w);
    }
    auto checksum(int u){return bx.query(rdfn[u])-bx.query(dfn[u]-1);}
    acam(int _n):ch(_n+7),fail(_n+7),cntw(_n+7),dfn(_n+7),rdfn(_n+7),bx(_n+7),gr(_n+7),cnt(0),gfail(_n+7,[]{
        array<int,alpha> res;
        fill(res.begin(),res.end(),-1);
        return res;
    }()){}
};
class tree{
private:
    vector<vector<pair<int,char>>> gr;
    vector<vector<pair<int,int>>> q;
    vector<int>*ans;
    acam*ac;
    auto dfs(int u,int acn)->void{
        assert(ans&&ac);
        ac->check(acn,1);
        for(auto&[qid,nid]:q[u]) (*ans)[qid]=ac->checksum(nid);
        for(auto&[v,c]:gr[u]) dfs(v,ac->move(acn,c));
        ac->check(acn,-1);
    }
public:
    auto setf(int u,int f,char fc){
        gr[f].emplace_back(u,fc);
    }
    auto emplace_q(int u,int qid,int nid){
        q[u].emplace_back(qid,nid);
    }
    auto check(auto _ans,auto _ac){
        ans=_ans;ac=_ac;dfs(0,0);
    }
    tree(int _n):gr(_n),q(_n),ans(nullptr),ac(nullptr){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;tree tr(n+1);
    cir(u,1,n+1){
        int op,f;char c;cin>>op;
        if(op==1) f=0,cin>>c;
        else cin>>f>>c;
        tr.setf(u,f,c);
    }
    int q;cin>>q;acam ac(max_len_t);
    cir(i,0,q){
        int u;string s;cin>>u>>s;
        const auto nid=ac.emplace(s);
        tr.emplace_q(u,i,nid);
    }
    ac.init();
    vector<int> ans(q);
    tr.check(&ans,&ac);
    for(auto&i:ans) println("{}",i);
    return 0;
}
