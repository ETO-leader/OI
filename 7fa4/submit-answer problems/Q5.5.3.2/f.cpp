#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto maxn=1088;
class randomfunc{
private:
    mt19937_64 eng;
public:
    auto randint(int l,int r){
        return uniform_int_distribution<int>(l,r)(eng);
    }
    randomfunc():eng(random_device().operator()()){}
} rnd;
template<const int limit>
class environment{
private:
    int n,l,u,m,uplimit;
    vector<bitset<maxn>> pi;
    class species{
    private:
        bitset<maxn> ch;
        bool valued;
        int val;
    public:
        auto value(const environment*x){
            if(valued) return val;
            valued=true;
            auto ans=0;
            for(auto&i:x->pi){
                const auto w=(ch&i).count();
                ans+=(x->l-1<w&&w-1<x->u);
            }
            return val=ans;
        }
        auto change(const environment*th){
            auto cnt=rnd.randint(0,10);
            cir(i,0,cnt){
                const auto rd=rnd.randint(0,th->n-1);
                ch[rd]=false;
            }
            init(th);
        }
        auto cross(const species&x,const environment*th) const{
            auto st=ch|x.ch;
            auto cnt=st.count();
            while(cnt>th->m){
                const auto px=rnd.randint(0,th->n-1);
                if(!st[px]) continue;
                --cnt;st[px]=false;
            }
            auto res=species(st);
            res.change(th);
            return res;
        }
        auto init(const environment*th){
            auto cnt=ch.count();
            while(cnt<th->m){
                const auto px=rnd.randint(0,th->n-1);
                if(ch[px]) continue;
                ch[px]=true;++cnt;
            }
            (*this)=species(ch);
        }
        species():valued(false),val(0){}
        species(bitset<maxn> x):ch(x),valued(false),val(0){}
        friend class environment;
    };
    vector<species> sp;
    auto judge(){
        const auto w=sp[0].value(this);
        const auto percent=w*1.0/limit;
        const auto score=pow(percent,200);
        for(auto c=0.0;c<1.0;c+=0.02){
            cerr<<(c<score?'#':'.');
        }
        cerr<<'\n';
        cerr<<"Current Score = "<<score*100<<", Current count = "<<w<<'\n';
        return score;
    }
public:
    auto evolve(){
        sp.resize(500);
        for(auto&x:sp) x.init(this);
        ranges::sort(sp,[&](auto&a,auto&b){
            return a.value(this)>b.value(this);
        });
        auto cnt=0;
        while(judge()<100.0){
            cerr<<"Generation = "<<++cnt<<'\n';
            vector<species> mx;
            cir(i,0,180) mx.push_back(sp[i]);
            while(mx.size()<800){
                auto u=rnd.randint(0,799);
                auto v=rnd.randint(0,799);
                mx.push_back(sp[u].cross(sp[v],this));
            }
            while(mx.size()<2000){
                auto u=rnd.randint(0,mx.size());
                auto v=rnd.randint(0,mx.size());
                mx.push_back(mx[u].cross(mx[v],this));
            }
            sp=mx;
            ranges::sort(sp,[&](auto&a,auto&b){
                return a.value(this)>b.value(this);
            });
            sp.resize(700);
            cir(i,0,100){
                species psh;psh.init(this);
                mx.push_back(psh);
            }
            ranges::sort(sp,[&](auto&a,auto&b){
                return a.value(this)>b.value(this);
            });
        }
        vector<int> ans;
        cir(i,0,n) if(sp[0].ch[i]) ans.push_back(i+1);
        return ans;
    }
    auto registerenv(int _n,int _m,int _l,int _u,vector<bitset<maxn>> px){
        pi=px;
        n=_n;m=_m;l=_l;u=_u;
        return evolve();
    }
    friend class species;
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m,p,l,u;cin>>n>>m>>p>>l>>u;
    vector<bitset<maxn>> px(n);
    cir(i,0,n){
        cir(x,0,p){
            int ix;cin>>ix;px[i][ix-1]=true;
        }
    }
    environment<1040> ans;
    const auto ansarr=ans.registerenv(n,m,l,u,px);
    for(auto&i:ansarr) cout<<i<<' ';
    cout<<'\n';
    return 0;
}
