#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("battle.in");
ofstream ouf("battle.ans");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;
using lint=long long;
class mathbase{
public:
    auto initfp(const auto n){
        vector<bool> isp(n+1,true);
        vector<int> pf(n+1);
        cir(i,2,n+1) if(isp[i]){
            auto w=1ll;
            while((w*=i)<n+1){
                for(auto j=w;j<n+1;j+=w) isp[j]=false,++pf[j];
            }
        }
        return pf;
    }
} math;
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n;inf>>n;vector<int> k(n);
    for(auto&i:k) inf>>i;
    const auto maxk=*max_element(k.begin(),k.end());
    const auto cpf=math.initfp(maxk);
    unordered_map<int,int> pw2;
    for(auto x=4,cnt=2;x<maxk+1;(x<<=1),++cnt) pw2[x]=cnt;
    auto fpf=cpf;
    cir(i,2,maxk+1) fpf[i]+=fpf[i-1];
    vector<int> f(maxk+1),fw(maxk+1);
    cir(i,2,maxk+1) f[i]=((!pw2.count(i))?1:i-1),fw[i]=((!pw2.count(i))?fpf[i]:pw2[i]);
    auto ans=0ll;
    for(auto&i:k) ans+=fpf[i];
    const auto rtcnt=ans;
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
    ouf<<ans<<'\n';
    return 0;
}
