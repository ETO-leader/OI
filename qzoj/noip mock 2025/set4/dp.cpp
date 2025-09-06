#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("dp.in");
ofstream ouf("dp.out");
using lint=long long;
class dsu{
private:
    vector<int> f;
public:
    auto findset(int u)->int{
        return f[u]==u?u:f[u]=findset(f[u]);
    }
    auto merge(int u,int v){
        f[findset(u)]=findset(v);
    }
    dsu(int _n):f(_n){iota(f.begin(),f.end(),0);}
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n,m,x;inf>>n>>m>>x;
    ++x;
    vector<lint> a(n),b(m);
    for(auto&c:a) inf>>c;
    for(auto&c:b) inf>>c;
    auto ans=0;
    if(*max_element(b.begin(),b.end())){
        dsu qwq(n*m);
        cir(i,0,n) cir(j,0,m) if(a[i]+b[j]<x){
            if(i&&a[i-1]+b[j]<x) qwq.merge((i-1)*m+j,i*m+j);
            if(i+1<n&&a[i+1]+b[j]<x) qwq.merge((i+1)*m+j,i*m+j);
            if(j&&a[i]+b[j-1]<x) qwq.merge(i*m+j-1,i*m+j);
            if(j+1<m&&a[i]+b[j+1]<x) qwq.merge(i*m+j+1,i*m+j);
        }
        cir(i,0,n) cir(j,0,m) if(a[i]+b[j]<x) ans+=(qwq.findset(i*m+j)==i*m+j);
    }else{
        cir(i,0,n) if(a[i]<x){
            ++ans;
            auto p=i;
            while(p+1<n&&a[p+1]<x) ++p;
            i=p;
        }
    }
    ouf<<ans<<'\n';
    return 0;
}
