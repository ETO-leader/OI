#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
using lint=long long;
class casereader{
private:
    union datatype{
        int i32;
        datatype(int x):i32(x){}
    };
    vector<datatype> data;
    int pos;
    template<typename _Ty>
    auto readarg(){
        _Ty x;cin>>x;data.emplace_back(x);
        return x;
    }
public:
    auto init(){
        const auto n=readarg<int>();
        cir(i,0,n) readarg<int>();
        const auto q=readarg<int>();
        cir(i,0,q*2) readarg<int>();
    }
    auto readargs(int&x){x=data[pos++].i32;}
    auto readargs(auto&...args){
        (readargs(args),...);
    }
    casereader():pos(0){}
};
static constexpr auto MOD=(int)(1e9+7);
class mathbase{
public:
    constexpr auto qpow(lint a,auto b){
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(auto a){return qpow(a,MOD-2);}
    auto primes(int n){
        vector<int> p,isp(n,true);
        cir(i,2,n) if(isp[i]){
            p.push_back(i);
            for(int j=i*2;j<n;j+=i) isp[j]=false;
        }
        return p;
    }
} math;
class segment{
private:
    struct node{
        shared_ptr<node> ls,rs;
        lint prod;
        auto maintain(){
            prod=1;
            for(auto v:{ls,rs}) if(v) (prod*=v->prod)%=MOD;
        }
        node():ls(nullptr),rs(nullptr),prod(1){}
    };
    using pnode=shared_ptr<node>;
    auto copy(pnode u){
        if(!u) return make_shared<node>();
        auto res=make_shared<node>();
        return *res=*u,res;
    }
    auto update(pnode&u,int l,int r,int p,lint w){
        u=copy(u);
        if(l==r) return u->prod=w;
        const auto mid=(l+r)/2;
        p-1<mid?update(u->ls,l,mid,p,w):update(u->rs,mid+1,r,p,w);
        u->maintain();
    }
    auto query(pnode u,int l,int r,int ql,int qr){
        if((!u)||r<ql||qr<l) return 1ll;
        if(ql-1<l&&r-1<qr) return u->prod;
        const auto mid=(l+r)/2;
        return query(u->ls,l,mid,ql,qr)*query(u->rs,mid+1,r,ql,qr)%MOD;
    }
    int n;
    vector<pnode> vx;
public:
    auto update(int p,int w){
        update(vx.back(),0,n-1,p,w);
    }
    auto query(int _v,int l,int r){
        return query(vx[_v],0,n-1,l,r);
    }
    auto makecopy(){
        vx.push_back(copy(vx.back()));
    }
    segment(int _n):n(_n),vx({nullptr}){}
};
class sparsetable{
private:
    vector<int> lgx;
    vector<vector<int>> ax;
    static constexpr auto ups=21;
    auto init(const vector<int>&a){
        const auto n=(int)(a.size());
        ax.resize(ups,vector<int>(a.size()));
        ax[0]=a;
        cir(c,1,ups) cir(i,0,n-(1<<i)+1) ax[c][i]=max(ax[c-1][i],ax[c-1][i+(1<<(c-1))]);
        lgx.resize(n+7);
        cir(i,2,n+7) lgx[i]=lgx[i>>1]+1;
    }
public:
    auto query(int l,int r){
        const auto c=lgx[r-l+1];
        return max(ax[c][l],ax[c][r-(1<<c)+1]);
    }
    sparsetable(auto a){init(a);}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    casereader inf;inf.init();
    int n,q;inf.readargs(n,q);
    vector<int> a(n);
    for(auto&i:a) inf.readargs(i);
    const auto pr=math.primes((int)(sqrt(*max_element(a.begin(),a.end())))+7);
    const auto p=(int)(pr.size());
    vector<vector<int>> w(p,vector<int>(n));
    for(auto i=-1;auto&x:pr){区间 
𝑥
x 是好的当且仅当不存在一个与 
𝑥
x 相交的区间的颜色和 
𝑥
x 不同.
共 
𝑛
n 次修改，每次修改会把区间 
𝑖
i 的颜色设置为 
𝑗
j，每次修改过后你需要求出给剩下没有确定颜色的区间染色之后，最大的好的区间的数量.
        ++i;
        cir(p,0,n){
            auto cnt=0;
            while(!(a[p]%x)) a[p]/=x,++cnt;
            w[i][p]=cnt;
        }
    }
    vector<sparsetable> st;
    cir(i,0,p) st.emplace_back(w[i]);
    segment sg(n);
    vector<int> las(*max_element(a.begin(),a.end())+7,-1);
    return 0;
}
