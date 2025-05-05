#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=__int128_t;
istream&operator>>(istream&is,lint&x){
    x=0;string s;is>>s;
    for(auto&i:s) (x*=10)+=(i-'0');
    return is;
}
ostream&operator<<(ostream&os,lint x){
    if(x<0) os<<'-',x=-x;
    if(x>9) os<<(x/10);
    return os<<(int)(x%10);
}
constexpr auto exgcd(lint a,lint b){
    if(!b) return pair<lint,lint>(1ll,0ll);
    auto[x,y]=exgcd(b,a%b);
    const auto k=x;
    x=y;y=k-(a/b)*y;
    return pair(x,y);
}
constexpr auto ugcd(__int128_t x,__int128_t y){
    if(!y) return x;
    return ugcd(y,x%y);
}
auto solve(lint x,lint k,lint y){
    const auto g=((x&&y)?ugcd(x,y):1);
    // clog<<x<<' '<<k<<' '<<y<<' '<<"!! "<<g<<'\n';
    if(!x&&(k%y)) return optional<pair<lint,lint>>(nullopt);
    if(k%g) return optional<pair<lint,lint>>(nullopt);
    x/=g,y/=g;
    auto[a,b]=exgcd(x,y);
    a*=(k/g);b*=(k/g);
    auto w=a;
    ((w%=y)+=y)%=y;
    return optional(pair(y,w));
}
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        lint n,x,y,vx,vy;cin>>n>>x>>y>>vx>>vy;
        x%=n;y%=n;
        // c vy = n
        // c = n / vy
        const auto uc=n/ugcd(vy,n),dc=vy/ugcd(vy,n);
        const auto utc=(n-y)/ugcd(n-y,n),dtc=n/ugcd(y,n);
        const auto a=vx*uc/ugcd(vx*uc,dc),b=dc/ugcd(vx*uc,dc);
        // x + (a/b) * utc / dtc
        const auto c=((__int128_t)(x)*dtc*b+a*utc)/ugcd((__int128_t)(x)*dtc*b+a*utc,dtc*b),d=dtc*b/ugcd((__int128_t)(x)*dtc*b+a*utc,dtc*b);
        // (a/b) t + (c/d) = kn * bd
        // ad t = -bc + kn
        // 6t = k * 6 + 24
        const auto nx=n*b*d;
        // clog<<uc<<' '<<dc<<"   "<<utc<<' '<<dtc<<" --> "<<a<<' '<<b<<": "<<c<<' '<<d<<' '<<a*d<<' '<<-b*c<<"\n";
        if(auto ans=solve(a*d%nx,(nx-b*c%nx)%nx,nx)){
            const auto[x,t]=ans.value();
            // clog<<"! "<<a*d*t+b*c<<' '<<x<<' '<<t<<'\n';
            const auto cy=t+1;
            const auto cx=(lint)(roundl(((long double)(c)/d+t*(long double)(a)/b)/n));
            // clog<<"??? "<<"t = "<<t<<' '<<((long double)(c)/d+t*(long double)(a)/b)<<' '<<cx<<' '<<cy<<'\n';
            cout<<cx-1+cy-1+(cx+cy)/2+abs<int64_t>(cx-cy)/2<<'\n';
        }else{
            cout<<-1<<'\n';
        }
    }();
    return 0;
}
