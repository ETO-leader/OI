#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class method:public vector<int>{
public:
    using vector<int>::vector;
    auto init(auto&eng){
        ranges::iota(*this,0);
        ranges::shuffle(*this,eng);
    }
    auto mate(method nxt,auto&eng) const{
        const auto n=(int)(this->size());
        auto res=method();
        vector<int> chs(n);
        const auto p=uniform_int_distribution<int>(1,n-1)(eng);
        cir(i,0,p) chs[n-1-i]=true;
        cir(i,0,n) if(!chs[(*this)[i]]) res.emplace_back((*this)[i]);
        cir(i,0,n) if(chs[nxt[i]]) res.emplace_back(nxt[i]);
        return res;
    }
    auto mutate(auto&eng) const{
        auto mutated=*this;
        const int n=(int)(this->size());
        uniform_int_distribution<int> dist(0,n-1);
        auto i=dist(eng),j=dist(eng);
        while(i==j) j=dist(eng);
        std::swap(mutated[i],mutated[j]);
        return mutated;
    }
};
int main(int argc,char*argv[]){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    if(argc!=5){
        cerr<<"There should be exactly 4 arguments.\n";
        assert(argc==5);
    }
    int n;cin>>n;vector f(n,vector<lint>(n));
    cir(i,0,n){
        cir(j,i+1,n){
            lint w;cin>>w;
            w*=1000000;w+=1;
            f[i][j]=f[j][i]=w;
        }
    }
    const auto a=f;
    cir(k,0,n) cir(i,0,n) cir(j,0,n){
        f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
    }
    auto path=[&](int u,int v){
        vector<int> res{u};
        while(u!=v){
            cir(p,0,n) if(p!=u&&a[u][p]+f[p][v]==f[u][v]){
                assert(res.size()<1000);
                res.emplace_back(p);
                u=p;
                break;
            }
        }
        return res;
    };
    auto cost=[&](method l){
        auto ans=0ll;
        cir(i,1,n) ans+=f[l[i-1]][l[i]];
        return ans;
    };
    auto write=[&](lint w,method x){
        cout<<w/1000000<<'\n';
        cir(i,1,n){
            auto c=path(x[i-1],x[i]);
            c.pop_back();
            for(auto&i:c) cout<<i+1<<'\n';
        }
        cout<<x[n-1]+1<<'\n';
        cout.flush();
    };
    const auto alive_count=atoi(argv[1]);
    const auto mate_count=atoi(argv[2]);
    const auto round_count=atoi(argv[3]);
    const auto __SEED__=atoi(argv[4]);
    vector<pair<lint,method>> cnt;
    auto eng=mt19937_64(__SEED__);
    cir(i,0,alive_count){
        auto u=method(n);
        u.init(eng);
        cnt.emplace_back(cost(u),u);
    }
    ranges::sort(cnt);
    cir(i,0,round_count){
        cir(i,0,mate_count*0.7){
            const auto x=cnt[uniform_int_distribution<int>(0,(int)(cnt.size())-1)(eng)];
            const auto y=cnt[uniform_int_distribution<int>(0,(int)(cnt.size())-1)(eng)];
            const auto nx=x.second.mate(y.second,eng);
            cnt.emplace_back(cost(nx),nx);
            const auto nxm=nx.mutate(eng);
            cnt.emplace_back(cost(nxm),nxm);
        }
        ranges::sort(cnt);
        shuffle(cnt.begin()+alive_count,cnt.end(),eng);
        cnt.resize(alive_count+alive_count/5);
        cir(i,0,alive_count/5){
            auto nx=method(n);
            nx.init(eng);
            cnt.emplace_back(cost(nx),nx);
        }
        ranges::sort(cnt);
    }
    write(cnt[0].first,cnt[0].second);
    cerr<<"done.\n";
    return 0;
}

