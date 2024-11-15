#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
// ifstream fcin("game.in");
ofstream fcout("game.out");
class fileio{
public:
    ~fileio(){
        /*fcin.close();*/fcout.close();
    }
} use_fileio;
namespace flash_man{
    static array<char,10000000> buf;
    auto p1 = buf.begin(), p2 = buf.begin();
    #define getchar() p1 == p2 && (p2 = (p1 = buf.begin()) + fread(buf.begin(), 1, 1000000, __FILEI), p1 == p2) ? EOF : *p1++
    template <typename type>
    inline void read(type &x,FILE*__FILEI) {
        x = 0;
        char c = getchar();
        while (!isdigit(c)) {
            c = getchar();
        }
        while (isdigit(c)) {
            x = (x << 1) + (x << 3) + (c ^ 48);
            c = getchar();
        }
    }
    #undef getchar
}
class qistream{
public:
    FILE*__FILEI;
    template<typename _Ty>
    qistream&operator>>(_Ty&a){
        flash_man::read(a,__FILEI);
        return*this;
    }
    qistream(const char*file){
        __FILEI=fopen(file,"r");
    }
};
qistream fcin("game.in");
static constexpr auto maxmem=(int)(1.5e7+7);
template<const size_t allocmem>
class stalin_tree{
private:
    struct node{
        int ls,rs,mn;
        // auto maintain(){
        //     mn=numeric_limits<int>::max();
        //     mn=ls?min(mn,ls->mn):-1;
        //     mn=rs?min(mn,rs->mn):-1;
        // }
        node():ls(0),rs(0),mn(-1){}
    };
    array<node,allocmem> tr;
    int cnt;
    auto copy(int u){
        if(!u) return (tr[++cnt]=node()),cnt;
        return (tr[++cnt]=tr[u]),cnt;
    }
    auto maintain(int u){
        tr[u].mn=min(tr[tr[u].ls].mn,tr[tr[u].rs].mn);
    }
    auto update(int&u,int l,int r,int p,int cur){
        u=copy(u);
        if(l==r) return tr[u].mn=cur,void();
        const auto mid=(l+r)>>1;
        p-1<mid?update(tr[u].ls,l,mid,p,cur):update(tr[u].rs,mid+1,r,p,cur);
        maintain(u);
    }
    auto query(int u,int l,int r,int q)->int{
        while(u&&tr[u].ls){
            const auto mid=(l+r)>>1;
            tr[tr[u].ls].mn<q?(u=tr[u].ls,r=mid):(u=tr[u].rs,l=mid+1);
        }
        return l;
    }
    vector<int> ver;
    int n;
public:
    auto append(int x){
        ver.push_back(ver.back());
        update(ver.back(),0,n-1,x,ver.size()-2);
    }
    auto mex(int l,int r){
        if(l>r) return numeric_limits<int>::min();
        if(r+1>(int)(ver.size())-1) return numeric_limits<int>::min();
        return query(ver[r+1],0,n-1,l);
    }
    stalin_tree(int _n):n(_n),ver({0}),cnt(0){
        tr[0].mn=-1;
    }
};
int main(){
    ios::sync_with_stdio(false);//,fcin.tie(nullptr);
    int n,q;fcin>>n>>q;vector<int> a(n);
    for(auto&i:a) fcin>>i;
    stalin_tree<maxmem> tr(n+7);
    for(auto&i:a) tr.append(i);
    auto mkminmax=[](auto a,auto b){
        if(a>b) return pair(a,b);
        return pair(b,a);
    };
    cir(i,0,q) [&](){
        int pl,pr;fcin>>pl>>pr;--pl;--pr;
        auto l=pl,r=pr;
        while(r-l>3){
            const auto lmid=(l+r)/2,rmid=lmid+1;
            auto ma=0,mb=0,mc=0,md=0;
            const auto wl=mkminmax(ma=tr.mex(pl,lmid),mb=tr.mex(lmid+1,pr));
            const auto wr=mkminmax(mc=tr.mex(pl,rmid),md=tr.mex(rmid+1,pr));
            if(wl.first==wr.first){
                if(min(ma,mc)>min(mb,md)) r=rmid;
                else l=lmid;
            }else{
                if(wl>wr) l=lmid;
                else r=rmid;
            }
        }
        auto ans=numeric_limits<int>::max();
        cir(i,l,r+1) ans=min(ans,max(tr.mex(pl,i),tr.mex(i+1,pr)));
        fcout<<ans<<'\n';
    }();
    return 0;
}
