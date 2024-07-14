#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
struct arrab{int a,b;};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;vector<arrab> ar(n);
        const int sqr=sqrt(n*2);
        for(auto&[a,b]:ar) cin>>a;
        for(auto&[a,b]:ar) cin>>b;
        ranges::sort(ar,[](arrab&a,arrab&b){return a.a<b.a;});
        vector<unordered_map<int,int>> cnx(n+1);
        lint ans=0;
        for(auto&[a,b]:ar){
            cir(i,0,sqr+1){
                if(i*a>2*n) break;
                if(cnx[i].count(i*a-b)) ans+=cnx[i][i*a-b];
            }
            if(a<=sqr) cnx[a][b]++;
        }
        cout<<ans<<'\n';
    }
    return 0;
}
