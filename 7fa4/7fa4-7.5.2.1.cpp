#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using complf=complex<double>;
namespace poly{
    static constexpr auto pi=acos(-1);
    auto change(vector<complf>&a,const int n){
        vector<int> rev(n);
        cir(i,0,n){
            rev[i]=(rev[i>>1]>>1)|((n>>1)*(i&1));
        }
        cir(i,0,n) if(i<rev[i]) swap(a[i],a[rev[i]]);
    }
    template<const int type>
    auto fft(vector<complf>&a,const int n){
        change(a,n);
        for(auto h=2;h<n+1;h<<=1){
            const auto wx=complf(cos(pi*2/h),sin(pi*2*type/h));
            const auto midh=h/2;
            for(auto i=0;i<n;i+=h){
                auto u=complf(1,0);
                cir(k,i,i+midh){
                    const auto wy=u*a[k+midh];
                    a[k+midh]=a[k]-wy;a[k]+=wy;
                    u*=wx;
                }
            }
        }
        if(type==-1) for(auto&i:a) i/=n;
    }
    auto mul(vector<int> a,vector<int> b){
        const auto n=1<<((int)(log2(a.size()+b.size()))+1);
        vector<complf> fx(n);
        cir(i,0,(int)(a.size())) fx[i]+=complf(a[i],0);
        cir(i,0,(int)(b.size())) fx[i]+=complf(0,b[i]);
        fft<1>(fx,n);
        for(auto&i:fx) i*=i;
        fft<-1>(fx,n);
        vector<long long> ans(n);
        cir(i,0,n) ans[i]=roundl(fx[i].imag()/2);
        return ans;
    }
}
namespace flash_man{
    static array<char,5000000> buf;
    auto p1 = buf.begin(), p2 = buf.begin();
    #define getchar() p1 == p2 && (p2 = (p1 = buf.begin()) + fread(buf.begin(), 1, 1000000, stdin), p1 == p2) ? EOF : *p1++
    template <typename type>
    inline auto read(type &x) {
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
    inline auto read(){
        int x;read(x);
        return x;
    }
    array<char,100> stc;
    template<typename _Ty>
    inline auto write(_Ty x,char c){
        if(x<0) putchar('-'),x=-x;
        auto tp=0;
        if(!x) stc[tp++]=0;
        while(x) stc[tp++]=x%10,x/=10;
        while((--tp)>-1) putchar(stc[tp]+'0');
        putchar(c);
    }
    #undef getchar
}
int main(){
    //ios::sync_with_stdio(false),cin.tie(0);
    int n,m;
    flash_man::read(n);flash_man::read(m);
    //cin>>n>>m;
    vector<int> a(n),b(m);
    for(auto&i:a) flash_man::read(i);//cin>>i;
    for(auto&i:b) flash_man::read(i);//cin>>i;
    const auto ans=poly::mul(a,b);
    cir(i,0,n+m-1) flash_man::write(ans[i],' ');//cout<<ans[i]<<' ';
    putchar('\n');
    //cout<<'\n';
    return 0;
}
