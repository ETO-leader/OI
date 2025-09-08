#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("memory.in");
ofstream ouf("memory.out");
class sparsetable{
private:
    static constexpr auto ups=21;
    vector<vector<uint64_t>> a;
    vector<int> lgx;
    auto init(vector<uint64_t> x){
        const auto n=(int)(x.size());
        a.resize(ups,vector<uint64_t>(n));
        a[0]=x;
        cir(i,1,ups) cir(p,0,n-(1<<i)+1){
            a[i][p]=max(a[i-1][p],a[i-1][p+(1<<(i-1))]);
        }
    }
public:
    auto query(int l,int r){
        const auto ql=__lg(r-l+1);
        return max(a[ql][l],a[ql][r-(1<<ql)+1]);
    }
    sparsetable(vector<uint64_t> x){init(x);}
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n,q;inf>>n>>q;
    static const auto v=(int)(1e5+7);
    vector<uint32_t> a(n);
    for(auto&i:a) inf>>i;
    vector<uint64_t> cnt(v);
    array<uint32_t,v*2> fpopcnt;
    cir(i,0,v*2) fpopcnt[i]=__builtin_popcount(i);
    cir(i,0,v){
        auto&uc=cnt[i];
        auto p=0;
        for(;p+4<n;p+=4) uc+=fpopcnt[a[p]+i]+fpopcnt[a[p+1]+i]+fpopcnt[a[p+2]+i]+fpopcnt[a[p+3]+i];
        for(;p<n;++p) uc+=fpopcnt[a[p]+i];
    }
    sparsetable st(cnt);
    cir(i,0,q){
        int l,r;inf>>l>>r;
        ouf<<st.query(l,r)<<'\n';
    }
    return 0;
}
