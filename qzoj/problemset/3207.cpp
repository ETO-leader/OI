#include<bits/stdc++.h>
#define cir(i,a,b) for(uint i=a;i<b;++i)
using namespace std;
static constexpr auto mxv=(int)(4e6+7);
#define getchar()p1==p2&&(p2=(p1=buf)+fread(buf,1,5000000,stdin),p1==p2)?EOF:*p1++
#define putchar(x)(p3-obuf<5000000)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x)
namespace flash_man{static char buf[5000000],*p1=buf,*p2=buf,obuf[5000000],*p3=obuf;struct Quick_IO_Suf{~Quick_IO_Suf(){fwrite(obuf,p3-obuf,1,stdout);}}quick_io_suf;namespace Quick_IO{static char cc[20];template<typename type>void read(type&x){x=0;char c=getchar();while(c<'0'||c>'9'){c=getchar();}while(c>='0'&&c<='9'){x=x*10+(c^48);c=getchar();}}template<typename type>inline void write(type x,char c){if(x==0)putchar(48);int len=0;while(x){cc[len++]=x%10+'0';x/=10;}while(len--)putchar(cc[len]);putchar(c);}}using namespace Quick_IO;}using namespace flash_man;
int main(){
    // ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;read(T);
    vector<uint> mnp(mxv);
    iota(mnp.begin(),mnp.end(),0);
    cir(i,2,mxv) if(mnp[i]==i){
        for(auto j=(int64_t)(i)*i;j<mxv;j+=i) mnp[j]=min(mnp[j],i);
    }
    vector<uint> mu(mxv);
    mu[1]=1;
    cir(i,2,mxv) mu[i]=(((i/mnp[i])%mnp[i]))?-mu[i/mnp[i]]:0;
    vector<uint> pf(mxv);
    cir(i,1,mxv) if(mu[i]){
        for(auto v=i,c=1u;v<mxv;v+=i,++c) pf[v]+=(mu[c]!=0)*mu[i]*i;
    }
    cir(i,1,mxv) (pf[i]*=i)+=pf[i-1];
    auto f=[&](uint n,uint m){
        auto res=0u;
        for(auto i=1u,r=0u;i<min(n,m)+1;i=r+1){
            r=min(n/(n/i),m/(m/i));
            res+=(pf[r]-pf[i-1])*((n/i)+1)*(n/i)*((m/i)+1)*(m/i);
        }
        return res;
    };
    while(T--) [&]{
        uint n,m;read(n);read(m);
        write(f(n,m)>>2,'\n');
    }();
    return 0;
}
