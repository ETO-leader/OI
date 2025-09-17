#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("perm.in");
ofstream ouf("perm.out");
class bit{
private:
    vector<int> a;
    constexpr auto lowbit(auto u) const{return u&(-u);}
public:
    auto update(int u,int x){
        for(++u;u<(int)(a.size());u+=lowbit(u)) a[u]+=x;
    }
    auto query(int u){
        auto res=0;
        for(++u;u;u-=lowbit(u)) res+=a[u];
        return res;
    }
    auto clear(){
        fill(a.begin(),a.end(),0);
    }
    bit(int _n):a(_n+1){}
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int c,T;inf>>c>>T;
    while(T--) []{
        int n;inf>>n;vector<int> a(1<<n);
        for(auto&x:a) inf>>x;
        vector<int> ord(1<<n);
        bit qwq(1<<n);
        auto ans=numeric_limits<int64_t>::max();
        auto cnt=0;
        cir(s,0,(1<<n)) cir(b,0,n){
            auto x=s;
            const auto w=((s>>b)&1)?((1<<n)-(1<<b)):(1<<b);
            const auto nw=(b!=n-1?(w<<1):(((s>>b)&1)?((1<<n)-1):1));
            for(auto i=0;i<(1<<(n-1));i+=2){
                ord[i]=x;
                ord[i+1]=(x+w)&((1<<n)-1);
                (x+=nw)&=((1<<n)-1);
            }
            cir(i,(1<<(n-1)),(1<<n)) ord[i]=(1<<n)-1-ord[(1<<n)-i-1];
            qwq.clear();
            auto uans=(int64_t)(0);
            cir(i,0,(1<<n)){
                uans+=qwq.query(a[ord[i]]);
                qwq.update(a[ord[i]],1);
            }
            // if(!(set<int>(ord.begin(),ord.end()).size()==n)){
            //     cerr<<s<<' '<<b<<'\n';
            //     for(auto&x:ord) cerr<<x<<' ';
            //     cerr<<'\n';
            // }
            // assert(set<int>(ord.begin(),ord.end()).size()==(1<<n));
            ans=min(ans,uans);
            (cnt+=(uans==ans));
        }
        // clog<<"cnt = "<<cnt<<'\n';
        ouf<<ans<<'\n';
    }();
    return 0;
}
