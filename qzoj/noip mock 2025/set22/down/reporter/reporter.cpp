#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("reporter.in");
ofstream ouf("reporter.out");
static constexpr auto maxn=(int)(1e5+7);
static constexpr auto _inf=(int)(1e9+7);
template<const int maxn>
class ext_bitset{
private:
    static constexpr auto xmaxn=(maxn>>6)+7;
    static constexpr auto full=numeric_limits<uint64_t>::max();
    array<uint64_t,xmaxn> a;
public:
    auto set(int l,int r){
        const auto pl=l>>6,pr=r>>6,lb=l&63,rb=r&63;
        if(pl==pr){
            const auto lm=full<<lb;
            const auto rm=full>>(63-rb);
            const auto um=lm&rm;
            a[pl]|=um;
        } else {
            a[pl]|=(full<<lb);
            cir(i,pl+1,pr) a[i]|=full;
            a[pr]|=(full>>(63-rb));
        }
    }
    static auto andcount(ext_bitset<maxn> ax,ext_bitset<maxn> bx,ext_bitset<maxn> cx,ext_bitset<maxn> dx){
        auto res=0;
        cir(i,0,xmaxn) res+=__builtin_popcountll(ax.a[i]&bx.a[i]&cx.a[i]&dx.a[i]);
        return res;
    }
    ext_bitset(){memset(a.data(),0,sizeof(a));}
};
class segment{
private:
    vector<vector<vector<pair<int,int>>>> tag;
    vector<vector<ext_bitset<maxn>>> stk;
    vector<ext_bitset<maxn>> cur;
    constexpr auto ls(auto u) const{return u*2;}
    constexpr auto rs(auto u) const{return u*2+1;}
    template<const int t>
    auto make_tag(int u,int l,int r,int ql,int qr,int tl,int tr){
        if(r<ql||qr<l) return;
        if(ql-1<l&&r-1<qr) return tag[t][u].emplace_back(tl,tr),void();
        const auto mid=(l+r)/2;
        make_tag<t>(ls(u),l,mid,ql,qr,tl,tr);
        make_tag<t>(rs(u),mid+1,r,ql,qr,tl,tr);
    }
    auto calc(int u,int dep,int l,int r)->int64_t{
        auto res=(int64_t)(0);
        stk[dep]=cur;
        cir(t,0,4) for(auto&[ql,qr]:tag[t][u]) cur[t].set(ql,qr);
        const auto mid=(l+r)/2;
        if(l!=r) res+=calc(ls(u),dep+1,l,mid);
        if(l!=r) res+=calc(rs(u),dep+1,mid+1,r);
        if(l==r) res=ext_bitset<maxn>::andcount(cur[0],cur[1],cur[2],cur[3]);
        cur=stk[dep];
        return res;
    }
    const int n;
public:
    template<const int t>
    auto make_tag(int l,int r,int tl,int tr){
        make_tag<t>(1,0,n-1,l,r,tl,tr);
    }
    auto calc(){
        return calc(1,0,0,n-1);
    }
    segment(int _n):n(_n),
        tag(4,vector<vector<pair<int,int>>>(_n<<4)),
        stk(__lg(_n)+3,vector<ext_bitset<maxn>>(4)),
        cur(4){}
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n,k;inf>>n>>k;
    vector<int> a(n);
    for(auto&x:a) inf>>x,--x;
    vector<vector<int>> pos(n);
    cir(i,0,n) pos[a[i]].emplace_back(i);
    segment sg(n);
    if(k>0){
        for(auto&x:pos){
            auto nx=x;
            nx.emplace(nx.begin(),-1);
            nx.emplace_back(n);
            cir(i,1,(int)(nx.size())-1){
                sg.make_tag<0>(nx[i],nx[i+1]-1,nx[i-1]+1,nx[i]);
            }
        }
    }else{
        cir(i,0,n) sg.make_tag<0>(i,n-1,i,i);
    }
    if(k>1){
        for(auto&x:pos){
            auto nx=x;
            nx.emplace(nx.begin(),-1);
            nx.emplace_back(n);
            cir(i,2,(int)(nx.size())-1){
                sg.make_tag<1>(nx[i],nx[i+1]-1,nx[i-2]+1,nx[i-1]);
            }
        }
    }else{
        cir(i,0,n) sg.make_tag<1>(i,n-1,i,i);
    }
    if(k>2){
        for(auto&x:pos){
            auto nx=x;
            nx.emplace(nx.begin(),-1);
            nx.emplace_back(n);
            cir(i,3,(int)(nx.size())-1){
                sg.make_tag<2>(nx[i],nx[i+1]-1,nx[i-3]+1,nx[i-2]);
            }
        }
    }else{
        cir(i,0,n) sg.make_tag<2>(i,n-1,i,i);
    }
    if(k>3){
        for(auto&x:pos){
            auto nx=x;
            nx.emplace(nx.begin(),-1);
            nx.emplace_back(n);
            cir(i,4,(int)(nx.size())-1){
                sg.make_tag<3>(nx[i],nx[i+1]-1,nx[i-4]+1,nx[i-3]);
            }
        }
    }else{
        cir(i,0,n) sg.make_tag<3>(i,n-1,i,i);
    }
    ouf<<sg.calc()<<'\n';
    return 0;
}

