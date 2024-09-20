#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("c.in");
ofstream fcout("c.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
using lint=long long;
class base{
private:
    static constexpr auto lim=62;
    vector<lint> a;
public:
    auto insert(lint x){
        for(auto i=lim;~i;--i) if((x>>i)&1){
            if(!a[i]) return a[i]=x,void();
            x^=a[i];
        }
    }
    auto kth(lint x,lint q){
        vector<int> vaild;
        cir(i,0,lim+1) if(a[i]) vaild.push_back(i);
        auto res=0ll;
        for(auto i=(int)(vaild.size())-1;~i;--i) if(x>(1ll<<i)-1){
            if(!(((res^q)>>vaild[i])&1)) res^=a[vaild[i]];
            x-=(1ll<<i);
        }else{
            if(((res^q)>>vaild[i])&1) res^=a[vaild[i]];
        }
        return res^q;
    }
    auto larger(lint x,lint q){
        auto l=0ll,r=(lint)(2e18l),ans=numeric_limits<lint>::max();
        while(l-1<r){
            const auto mid=(l+r)/2;
            const auto val=kth(mid,q);
            (val>x)?((r=mid-1),(ans=val)):(l=mid+1);
        }
        return ans;
    }
    base():a(lim+1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;fcin>>n;vector<lint> a(n);
    for(auto&i:a) fcin>>i;
    vector f(n+1,vector(n+1,numeric_limits<lint>::max()));
    f[0][0]=-1;
    base bs;
    cir(i,0,n){
        cir(x,0,n+1){
            f[i+1][x]=f[i][x];
            if(x) cir(las,0,i+1){
                const auto nw=bs.larger(f[las][x-1],a[i]);
                if(nw<numeric_limits<lint>::max()) f[i+1][x]=min(f[i+1][x],nw);
            }
        }
        bs.insert(a[i]);
    }
    auto ans=0;
    cir(x,1,n+1) if(f[n][x]<numeric_limits<lint>::max()) ans=x;
    fcout<<ans<<'\n';
    return 0;
}
