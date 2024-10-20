#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto maxd=12;
class dsu{
private:
    vector<int> f;
public:
    auto findset(int u)->int{
        return f[u]==u?u:(f[u]=findset(f[u]));
    }
    auto merge(int u,int v){
        f[findset(u)]=findset(v);
    }
    dsu(int n):f(n){ranges::iota(f,0);}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int n,m;cin>>n>>m;
        vector st(maxd,vector<int>(n));
        cir(i,0,m){
            int a,d,k;cin>>a>>d>>k;--a;
            ++st[d][a];--st[d][a+d*k];
        }
        dsu ds(n);
        cir(d,1,maxd){
            vector<int> vaild(d);
            cir(i,0,n){
                if(vaild[i%d]) ds.merge(i-d,i);
                vaild[i%d]+=st[d][i];
            }
        }
        set<int> ans;
        cir(i,0,n) ans.insert(ds.findset(i));
        println("{}",ans.size());
    }();
    return 0;
}
