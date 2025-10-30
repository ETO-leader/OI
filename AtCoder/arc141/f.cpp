#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
template<const int alpha>
class acam{
private:
    vector<array<int,alpha>> ch,failk;
    vector<int> fail,val;
    int cnt;
public:
    auto emplace(vector<int> s){
        auto u=0;
        for(auto&x:s){
            if(!ch[u][x]) ch[u][x]=++cnt;
            u=ch[u][x];
        }
        val[u]=(int)(s.size());
    }
    auto init(){
        queue<int> q;q.emplace(0);
        while(!q.empty()){
            const auto u=q.front();q.pop();
            cir(c,0,alpha) if(ch[u][c]){
                failk[u][c]=ch[u][c];
                if(u){
                    auto x=fail[u];
                    while(x&&(!ch[x][c])) x=fail[x];
                    fail[ch[u][c]]=ch[x][c];
                    failk[ch[u][c]]=failk[fail[ch[u][c]]];
                }
                q.emplace(ch[u][c]);
            }
        };
        cir(u,0,cnt+1) val[u]=max(val[u],val[fail[u]]);
    }
    auto ensure(vector<int> s){
        vector<int> a{0};
        auto cnt=0;
        for(auto&x:s){
            auto u=failk[a.back()][x];
            a.emplace_back(u);
            cnt+=(bool)(val[u]);
            cir(c,0,val[u]) a.pop_back();
        }
        if(a.size()==1) return (int)(cnt==1);
        return -1;
    }
    acam(int _n):ch(_n),failk(_n),fail(_n),val(_n),cnt(0){}
};
static constexpr auto c=251ull;
static constexpr auto maxs=(int)(2e6+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;acam<4> ac(maxs);
    vector<vector<int>> ns;
    cir(i,0,n){
        string s;cin>>s;
        vector<int> a;
        for(auto&x:s) a.emplace_back(x-'A');
        ns.emplace_back(a);
        ac.emplace(a);
    }
    ac.init();
    vector<vector<int>> ins;
    map<pair<uint64_t,uint64_t>,int> vals;
    map<uint64_t,int> sufs,full;
    auto ok=true;
    for(auto&s:ns){
        const auto ens=ac.ensure(s);
        if(ens==-1) ok=false;
        if(ens!=1) continue;
        vector<uint64_t> upre,usuf;
        auto wpre=0ull;
        for(auto&x:s){
            (wpre*=c)+=(x+1);
            upre.emplace_back(wpre);
        }
        auto wsuf=0ull,wcur=1ull;
        for(auto&x:views::reverse(s)){
            wsuf+=(x+1)*wcur;
            wcur*=c;
            usuf.emplace_back(wsuf);
            if(usuf.size()<s.size()) ++sufs[wsuf];
        }
        ++full[wsuf];
        ranges::reverse(usuf);
        cir(i,0,(int)(s.size())-1) ++vals[{upre[i],usuf[i+1]}];
        ins.emplace_back(s);
    }
    [&]{
        mt19937 eng(251);
        ranges::shuffle(ins,eng);
        for(auto&s:ins){
            vector<uint64_t> upre,usuf;
            auto wpre=0ull;
            for(auto&x:s){
                (wpre*=c)+=(x+1);
                upre.emplace_back(wpre);
            }
            auto wsuf=0ull,wcur=1ull;
            for(auto&x:views::reverse(s)){
                wsuf+=(x+1)*wcur;
                wcur*=c;
                usuf.emplace_back(wsuf);
                if(usuf.size()<s.size()&&full.contains(wsuf)) ok=false;
            }
            ranges::reverse(usuf);
            cir(i,0,(int)(s.size())-1){
                if(sufs.contains(upre[i])&&vals.contains({usuf[i+1],upre[i]})) ok&=(!(sufs[upre[i]]-1));
                else if(sufs.contains(upre[i])) ok=false;
                if(!ok) return;
            }
        }
    }();
    cout<<(ok?"No":"Yes")<<'\n';
    return 0;
}
