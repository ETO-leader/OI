#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
class mathbase{
private:
    vector<lint> fct,ifct;
public:
    constexpr auto qpow(lint a,auto b) const{
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(auto x) const{return qpow(x,MOD-2);}
    auto init(const auto n){
        fct.resize(n,1);
        cir(i,1,n) fct[i]=fct[i-1]*i%MOD;
        ifct=fct;
        for(auto&x:ifct) x=inv(x);
    }
    auto C(auto a,auto b) const{
        return fct[a]*ifct[b]%MOD*ifct[a-b]%MOD;
    }
    auto fact(const auto x) const{return fct[x];}
    auto ifact(const auto x) const{return ifct[x];}
} math;
class dpAM{
private:
    class state{
    public:
        int i,hdr,cntx,cnti,val;
        // To Vector, for map compare
        auto vectorize() const{
            return vector{i,hdr,cntx,cnti,val};
        }
        auto transfer(int ucnt) const->vector<state>{
            vector<state> v;
            if(!hdr){
                const auto adx=min(cntx,ucnt);
                ucnt-=adx;
                v.emplace_back(i+1,false,min(ucnt-(ucnt>2)*3,cnti),ucnt-min(ucnt-(ucnt>2)*3,cnti),val+adx+(ucnt>2));
                if(ucnt>1) v.emplace_back(state(i,true,cntx,cnti,val).transfer(ucnt-2)[0]);
            }else{
                const auto adx=min(cntx,ucnt);
                ucnt-=adx;
                v.emplace_back(i+1,true,min(ucnt-(ucnt>2)*3,cnti),ucnt-min(ucnt-(ucnt>2)*3,cnti),val+adx+(ucnt>2));
            }
            return v;
        }
        auto win() const{return hdr&&val>2;}
        auto no_next(const auto n) const{return i>n-1;}
        state()=default;
        state(int _i,int _hdr,int _cntx,int _cnti,int _val):
            i(_i),hdr(_hdr),cntx(_cntx),cnti(_cnti),val(_val){}
    };
    class state_cmp{
    public:
        static auto operator()(const state&x,const state&y){
            return x.vectorize()<y.vectorize();
        }
    };
    map<state,int,state_cmp> id;
    vector<state> id_state;
public:
    auto buildAM(const auto n,vector<int> lb){
        queue<state> q;
        q.emplace(0,0,0,0,0);
        while(!q.empty()){
            const auto u=q.front();q.pop();
            if(u.win()||u.no_next(n)) continue;
            cir(x,lb[u.i],5){
                const auto v_arr=u.transfer(x);
                for(auto&v:v_arr) if(!id.contains(v)){
                    id.emplace(v,0);
                    q.emplace(v);
                }
            }
        }
        for(auto c=-1;auto&[a,b]:id) b=++c;
        id_state.resize(id.size());
        for(auto&[a,b]:id) id_state[b]=a;
    }
    auto calc(int x,vector<int> lb){
        const auto s=(int)(id.size());
        vector f(s,vector(x+1,vector<lint>(8)));
        f[id[{0,0,0,0,0}]][0][0]=1;
        queue<int> q;q.emplace(id[{0,0,0,0,0}]);
        vector<int> inq(s);
        auto res=0ll;
        while(!q.emplace()){
            const auto u=q.front();q.pop();
            const auto su=id_state[u];
            if(su.win()) continue;
            cir(c,0,7) (res+=f[u][x][c])%=MOD;
            cir(c,lb[su.i],5){
                const auto v_arr=su.transfer(c);
                for(auto&v:v_arr){
                    const auto vid=id[v];
                    if(!inq[vid]){
                        inq[vid]=true;
                        q.emplace(vid);
                    }
                    cir(s,0,x) cir(ns,0,min(x-s,4)+1) cir(ul,0,8){
                        if(ul+(c>1)>7) continue;
                        (f[vid][s+ns][ul+(c>1)]+=f[u][s][ul+(c>1)]*math.C(s+ns,ns))%=MOD;
                    }
                }
            }
        }
        return res;
    }
    dpAM()=default;
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;vector<int> cur;
    math.init(n*4+7);
    vector<int> scnt(n);
    cir(i,0,13){
        int x,id;cin>>x>>id;
        ++scnt[x-1];
    }
    auto am=dpAM();
    am.buildAM(n,scnt);
    auto ans=0ll;
    cir(c,1,n*4-12) (ans+=am.calc(c,scnt)*math.fact(c)%MOD*math.fact(n*4-13-c)%MOD*math.ifact(n*4-13))%=MOD;
    cout<<ans<<'\n';
    return 0;
}
