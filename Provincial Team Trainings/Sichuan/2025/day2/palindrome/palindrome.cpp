#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("palindrome.in");
ofstream ouf("palindrome.out");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;
using lint=long long;
static constexpr auto MOD=998244353;
class mathbase{
public:
    constexpr auto qpow(lint a,auto b) const{
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(auto x) const{
        return qpow(x,MOD-2);
    }
} math;
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n,m;cin>>n>>m;vector<int> a(n);
    for(auto&i:a) cin>>i;
    vector<lint> mpow(m+7,1);
    cir(i,1,m+7) mpow[i]=mpow[i-1]*m%MOD;
    vector<int> ns;
    for(auto&i:a) ns.emplace_back(i),ns.emplace_back(m);
    auto l=0,r=-1;
    vector<vector<int>> posx(m+7);
    cir(i,0,n) posx[a[i]].emplace_back(i);
    auto check=[&](int l,int r,int w){
        const auto upb=ranges::lower_bound(posx[w],l);
        if(upb==posx[w].end()||*upb>r) return optional<int>(nullopt);
        return optional(*upb);
    };
    vector<int> len(n*2);
    cir(i,0,n*2){
        if(i>r){
            auto pl=i,pr=i;
            [&]{
                while(pl&&pr<n-1){
                    const auto u=a[--pl],v=a[++pr];
                    if(auto val=check(pl+1,pr-1,u)){
                        if(a[i*2-val.value()]!=v) return;
                    }
                    if(auto val=check(pl+1,pr-1,v)){
                        if(a[i*2-val.value()]!=u) return;
                    }
                }
            }();
            len[i]=pr-pl+1;
            if(pr>r) l=pl,r=pr;
        }else{
            
        }
    }
    return 0;
}
