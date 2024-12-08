#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
class casereader{
private:
    union datatype{
        int i32;
        datatype(int x):i32(x){}
    };
    vector<datatype> ax;
    int cur=0;
    auto readint(){
        int x;cin>>x;ax.emplace_back(x);
        return x;
    }
public:
    auto init(){
        auto q=readint();
        cerr<<"Q = "<<q<<'\n';
        cir(i,0,q){
            auto op=readint();
            cir(c,0,op*3) readint();
        }
        cur=0;
    }
    auto readargs(int&x){
        x=ax[cur].i32;++cur;
    }
    auto readargs(auto&x,auto&...args){
        readargs(x);readargs(args...);
    }
};
static constexpr auto maxn=(int)(5e4+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        casereader inf;inf.init();
        int n;inf.readargs(n);
        cerr<<n<<'\n';
        vector<pair<int,int>> qx,qy,qz,qi;
        vector<array<int,4>> nd;
        vector<array<int,8>> q;
        auto qcnt=0;
        cir(i,0,n){
            int op;inf.readargs(op);
            if(op==1){
                int x,y,z;inf.readargs(x,y,z);
                nd.emplace_back(array{x,y,z,i});
                qx.emplace_back(x,i);
                qy.emplace_back(y,i);
                qz.emplace_back(z,i);
                qi.emplace_back(i,i);
            }else{
                int x,y,z,u,v,w;inf.readargs(x,y,z,u,v,w);
                q.emplace_back(array{x,y,z,u,v,w,i,qcnt});
                ++qcnt;
            }
        }
        vector<bitset<maxn>> ans(qcnt);
        for(auto&x:ans) x.set();
        auto chk=[&](vector<pair<int,int>>&a,vector<array<int,3>> q){
            sort(a.begin(),a.end());
            const auto qc=(int)(a.size());
            vector<bitset<maxn>> pre(qc);
            bitset<maxn> cur;cur.reset();
            cir(i,0,qc) cur.set(a[i].second),pre[i]=cur;
            for(auto[ax,bx,id]:q){
                ax=lower_bound(a.begin(),a.end(),pair(ax,0))-a.begin();
                auto cur=(ax?pre[ax-1]:bitset<maxn>(0));
                bx=upper_bound(a.begin(),a.end(),pair(bx,_inf))-a.begin();
                if(bx) cur^=pre[bx-1];
                ans[id]&=cur;
            }
        };
        chk(qx,[&]{
            vector<array<int,3>> ax;
            for(auto&[x,y,z,u,v,w,i,id]:q) ax.emplace_back(array{x,u,id});
            return ax;
        }());
        chk(qy,[&]{
            vector<array<int,3>> ax;
            for(auto&[x,y,z,u,v,w,i,id]:q) ax.emplace_back(array{y,v,id});
            return ax;
        }());
        chk(qz,[&]{
            vector<array<int,3>> ax;
            for(auto&[x,y,z,u,v,w,i,id]:q) ax.emplace_back(array{z,w,id});
            return ax;
        }());
        chk(qi,[&]{
            vector<array<int,3>> ax;
            for(auto&[x,y,z,u,v,w,i,id]:q) ax.emplace_back(array{-1,i,id});
            return ax;
        }());
        for(auto&x:ans) cout<<x.count()<<'\n';
    }();
    return 0;
}
