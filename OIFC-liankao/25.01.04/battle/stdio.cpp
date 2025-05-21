#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class mathbase{
public:
    auto initfp(const auto n){
        vector<int> qwq(n+1,1),isp(n+1,true);
        vector<vector<int>> tat(n+1);
        vector<int> pf(n+1);
        cir(i,2,n+1) if(isp[i]){
            auto w=1ll;
            while((w*=i)<n+1){
                for(auto j=w;j<n+1;j+=w) isp[j]=false,++pf[j],qwq[j]=max(qwq[j],i),tat[j].emplace_back(i);
            }
        }
        return make_tuple(pf,qwq,tat);
    }
} math;
class sparsetable{
private:
    static constexpr auto ups=21;
    vector<vector<int>> mx;
    vector<int> _lg;
    auto init(vector<int> ax){
        const auto n=(int)(ax.size());
        mx.resize(ups,vector<int>(n));
        mx[0]=ax;
        cir(i,1,ups) cir(p,0,n-(1<<i)+1){
            mx[i][p]=max(mx[i-1][p],mx[i-1][p+(1<<(i-1))]);
        }
        _lg.resize(n+7);
        cir(i,2,n+7) _lg[i]=_lg[i>>1]+1;
    }
public:
    auto query(int l,int r){
        const auto lx=_lg[r-l+1];
        return max(mx[lx][l],mx[lx][r-(1<<lx)+1]);
    }
    sparsetable(vector<int> x){init(x);}
};
class bit{
private:
    vector<int> ax;
    static constexpr auto lowbit(auto x){return x&(-x);}
public:
    auto update(int p){
        for(++p;p<(int)(ax.size());p+=lowbit(p)) ++ax[p];
    }
    auto query(int p){
        auto res=0ll;
        for(++p;p;p-=lowbit(p)) res+=ax[p];
        return res;
    }
    bit(int _n):ax(_n+1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;vector<int> k(n);
    for(auto&i:k) cin>>i;
    const auto maxk=*max_element(k.begin(),k.end());
    auto ans=0ll;
    const auto[cpf,qwq,tat]=math.initfp(maxk);
    auto fpf=cpf;
    cir(i,2,maxk+1) fpf[i]+=fpf[i-1];
    sparsetable qaq(qwq);
    for(auto&i:k) ans+=fpf[i];
    const auto rtcnt=ans;
    // 在关键点上
    [&]{
        unordered_map<int,int> pw2;
        for(auto x=4,cnt=2;x<maxk+1;(x<<=1),++cnt) pw2[x]=cnt;
        vector<int> f(maxk+1),fw(maxk+1);
        cir(i,2,maxk+1) f[i]=((!pw2.count(i))?1:i-1),fw[i]=((!pw2.count(i))?fpf[i]:pw2[i]);
        vector<lint> sumfpf(maxk+1),subsum(maxk+1),subcnt(maxk+1);
        for(auto&x:k){
            auto w=x;
            auto pre=0ll;
            while(w){
                sumfpf[w]+=fpf[x];
                subsum[w]+=pre;
                ++subcnt[w];
                pre+=fw[w];w=f[w];
            }
        }
        cir(i,2,maxk+1) ans=min(ans,rtcnt-sumfpf[i]+fw[i]*(n-subcnt[i])+subsum[i]);
    }();
    // 在虚点上
    [&]{
        auto maxm=0ll,sum=0ll;
        bit ax(maxk+7);
        vector<int> cntx(maxk+1);
        for(auto&i:k) ++cntx[i];
        cir(i,1,maxk+1) cntx[i]+=cntx[i-1];
        auto maxqwq=0ll;
        cir(i,2,maxk+1){
            auto cntmx=0;
            for(auto&x:tat[i]) ++sum;
            const auto mxp=qwq[i];
            const auto dep=ax.query(maxk+6)-ax.query(mxp-1);
            for(auto&x:tat[i]) ax.update(x);
            const auto lrange=[&]{
                auto l=2,r=i-1,ans=i;
                while(l<r+1){
                    const auto mid=(l+r)/2;
                    qaq.query(mid,i-1)<mxp?((ans=mid),(r=mid-1)):(l=mid+1);
                }
                --ans;
                return ans;
            }();
            const auto rrange=[&]{
                auto l=i+1,r=maxk,ans=i;
                while(l<r+1){
                    const auto mid=(l+r)/2;
                    qaq.query(i+1,mid)<mxp+1?((ans=mid),(l=mid+1)):(r=mid-1);
                }
                return ans;
            }();
            const auto cnt=cntx[rrange]-cntx[lrange-1];
            ans=min(ans,rtcnt-(cnt-(n-cnt))*dep);
        }
    }();
    cout<<ans<<'\n';
    return 0;
}
