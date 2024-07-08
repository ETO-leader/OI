#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("fire.in");
ofstream fcout("fire.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
using lint=long long;
using llint=__int128;
static constexpr int MOD=998244353;
struct squ{int x,y;};
vector<squ> sq;
class scanner{
private:
    static auto init_t(int t,set<int>&oks){
        map<int,vector<int>> qs;
        for(auto&[x,y]:sq){
            qs[x-t];qs[x+t+1];
            oks.insert(y-t);oks.insert(y+t+1);
        }
        for(auto&[x,y]:qs) y.resize(oks.size());
        return qs;
    }
public:
    static auto scan(int t){
        set<int> oks;
        auto mps=init_t(t,oks);
        lint lastl=-1,ans=0,lans=0;
        map<int,int> id;int c=0;
        for(auto&i:oks) id[i]=c++;
        for(auto&[x,y]:sq){
            ++mps[x-t][id[y-t]];
            --mps[x-t][id[y+t+1]];
            --mps[x+t+1][id[y-t]];
            ++mps[x+t+1][id[y+t+1]];
        }
        vector<int> sum(id.size());
        vector<int> aps(oks.begin(),oks.end());
        for(auto&[x,y]:mps){
            lint prec=0,ansi=0;
            for(auto&k:aps) sum[id[k]]+=(prec+=y[id[k]]);
            cir(i,0,(int)(aps.size())-1){
                ansi+=(bool)(sum[i])*
                    (aps[i+1]-aps[i]);
            }
            ans+=lans*(x-lastl);
            lastl=x;lans=ansi;
        }
        return ans;
    }
};
lint qpow(lint a,lint b){
    lint res=1;
    while(b){
        if(b&1) (res*=a)%=MOD;
        (a*=a)%=MOD;b>>=1;
    }
    return res;
}
lint inv(lint p){return qpow(p,MOD-2);}
class func{
private:
    lint a,b,c;
    lint times(lint x,lint k,lint c=1){
        return x*k%MOD*inv(c)%MOD;
    }
    lint prefsum(lint x){
        return (times((x*(x+1)%MOD*(2*x+1)
            %MOD*inv(6))%MOD,a,2)
            +times(x*(x+1)%MOD*inv(2)%MOD,b)%MOD+
            x*c)%MOD;
    }
public:
    auto&init(lint x,lint f0,lint f1,lint f2){
        a=(f2-f1*2+f0);
        b=(f2-f1)-(x*2+3)*a/2;
        c=f0-x*x*a/2-b*x;
        a%=MOD;b%=MOD;c%=MOD;
        return *this;
    }
    lint rngsum(lint l,lint r){
        return (prefsum(r)+MOD-
            prefsum(l-1))%MOD;
    }
};
auto split(){
    set<int> ans{0};
    for(auto&i:sq) for(auto&j:sq){
        if(i.x==j.x&&i.y==j.y) continue;
        int inst=max(abs(i.x-j.x),
            abs(i.y-j.y));
        ans.insert(inst/2+(inst&1));
    }
    return ans;
}
int main(){
    ios::sync_with_stdio(false),fcin.tie(0);
    int n,t;fcin>>n>>t;sq.resize(n);
    for(auto&[x,y]:sq) fcin>>x>>y;
    auto tl=split();
    vector<int> rst(tl.begin(),tl.end());
    while((!rst.empty())&&rst.back()>t-1)
        rst.pop_back();
    rst.push_back(t);
    lint ans=0,lans=(llint)(scanner::scan(t))*t%MOD;
    cir(i,0,(int)(rst.size())-1){
        scanner scn;
        if(rst[i+1]-rst[i]<5){
            cir(x,rst[i],rst[i+1]){
                ans+=scn.scan(x);
            }
        }else{
            ans+=func().init(rst[i],scn.scan(rst[i]),
                scn.scan(rst[i]+1),scn.scan(rst[i]+2)
                ).rngsum(rst[i],rst[i+1]-1);
        }
        ans%=MOD;
    }
    fcout<<(lans-ans+MOD)%MOD<<'\n';
    return 0;
}
