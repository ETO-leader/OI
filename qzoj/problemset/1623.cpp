#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=(a);i<(b);++i)
using namespace std;
static constexpr auto ups=21;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m;cin>>n>>m;
    vector<array<int,3>> a;
    cir(i,0,n){
        int l,r;cin>>l>>r;
        if(l>r) r+=m;
        a.emplace_back(array<int,3>{l,r,i});
    }
    sort(a.begin(),a.end());
    cir(i,0,n) a.emplace_back(array<int,3>{a[i][0]+m,a[i][1]+m,a[i][2]});
    const auto k=n*2;
    vector<vector<int>> st(ups,vector<int>(k,-1));
    auto j=0;
    cir(i,0,k){
        while(j<k&&a[j][0]-1<a[i][1]) ++j;
        st[0][i]=j-1;
    }
    cir(v,1,ups) cir(i,0,k){
        const auto nxt=st[v-1][i];
        st[v][i]=(nxt==-1?-1:st[v-1][nxt]);
    }
    vector<int> answ(n);
    cir(i,0,n){
        const auto up=a[i][0]+m;
        auto ans=0,p=i;
        for(int v=ups-1;~v;--v){
            auto vx=st[v][p];
            if(vx!=-1&&a[vx][1]<up) ans+=(1<<v),p=vx;
        }
        answ[a[i][2]]=ans+2;
    }
    for(auto&x:answ) cout<<x<<' ';
    cout<<'\n';
    return 0;
}
