#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    mt19937 eng(251);
    while(T--) [&]{
        int n;cin>>n;vector<uint64_t> a(1<<(n+1));
        for(auto&i:a) cin>>i;
        cir(i,1,(1<<(n+1))) a[i]^=a[i-1];
        while(true){
            set<int> p;
            while(p.size()<2) p.emplace(uniform_int_distribution<int>(0,(1<<(n+1))-1)(eng));
            const auto ar=*p.begin(),bl=*p.rbegin();
            map<uint64_t,int> pl;
            pl[0]=0;
            cir(i,0,ar) pl[a[i]]=i+1;
            cir(i,bl,(1<<(n+1))){
                const auto w=a[i]^a[bl-1]^a[ar];
                if(pl.contains(w)) return cout<<pl[w]+1<<' '<<ar+1<<' '<<bl+1<<' '<<i+1<<'\n',void();
            }
        }
    }();
    return 0;
}
