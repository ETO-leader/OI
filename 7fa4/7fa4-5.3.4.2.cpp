#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
static constexpr int maxsiz=3e4+7;
class ac_automaton{
private:
    vector<VI> tr;VI fx,cx;
    int cnt,rt;
    auto allocm(){return ++cnt;}
public:
    auto insert(const VI a){
        int u=rt;
        for(auto&i:a){
            if(!tr[u][i]) tr[u][i]=allocm();
            u=tr[u][i];
        }
        ++cx[u];
    }
    auto init(){
        queue<int> q;q.push(rt);
        while(!q.empty()){
            auto u=q.front();q.pop();
            cx[u]+=cx[fx[u]];
            int cnt=-1;
            for(auto&i:tr[u]) if(((++cnt)+1)&&i){
                if(!u){
                    fx[i]=u;q.push(i);
                }else{
                    int v=fx[u];
                    while(v&&(!tr[v][cnt])) v=fx[v];
                    fx[i]=tr[v][cnt];q.push(i);
                }
            }
        }
    }
    auto getst(){
        return tuple(tr,fx,cx);
    }
    auto size(){return cnt+1;}
    ac_automaton(int siz,int alp):rt(0),
        tr(siz,VI(alp)),fx(siz),cx(siz),cnt(0){}
};
auto binstrvec(const string s){
    VI res;res.reserve(s.size());
    for(auto&i:s) res.push_back(i-'0');
    return res;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;ac_automaton ac(maxsiz,2);
    cir(i,0,n){
        string s;cin>>s;
        ac.insert(binstrvec(s));
    }
    ac.init();
    auto[tr,fx,cx]=ac.getst();
    vector<bool> vis(maxsiz),inq(maxsiz);
    function<void(int)> dfs=[&](int u){
        if(vis[u]) return;
        inq[u]=true;vis[u]=true;
        cir(x,0,2){
            int v=u;
            while(v&&(!tr[v][x]))
                v=fx[v];
            if(u&&((!tr[v][x])||(cx[tr[v][x]])))
                continue;
            if(inq[tr[v][x]])
                throw (string)("succeed");
            dfs(tr[v][x]);
        }
        inq[u]=false;
    };
    try{
        dfs(0);
        cout<<"NIE\n";
    }catch(string){
        cout<<"TAK\n";
    }
    return 0;
}
