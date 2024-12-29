#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n,m,k;cin>>n>>m>>k;vector a(n,vector<lint>(m));
        for(auto&x:a) for(auto&i:x){
            cin>>i;
            if(i>-1) --i;
        }
        vector<unordered_set<int>> col(n);
        vector<unordered_map<int,lint>> cntl(n);
        cir(i,0,n) for(auto&w:a[i]) if(w>-1) ++cntl[i][w],col[i].emplace(w);
        vector<lint> cx(n);
        cir(i,0,n) cx[i]=ranges::count(a[i],-1);
        vector<lint> f(k);
        cir(i,1,n){
            vector<lint> dff(k);
            cir(c,0,k) if(cntl[i].count(c)){
                dff[c]=cx[i-1]*cntl[i][c];
            }
            cir(c,0,k) dff[c]+=f[c];
            auto pmx=dff,smx=dff;
            cir(c,1,k) pmx[c]=max(pmx[c-1],pmx[c]);
            for(auto c=k-2;~c;--c) smx[c]=max(smx[c+1],smx[c]);
            auto ad=0ll;
            for(auto&c:col[i]) ad+=cntl[i-1][c]*cntl[i][c];
            cir(c,0,k){
                const auto mx=max((c?pmx[c-1]:0),(c+1<k?smx[c+1]:0));
                f[c]+=(ad+cx[i-1]*(cntl[i].count(c)?cntl[i][c]:0)+cx[i-1]*cx[i]+(cntl[i-1].count(c)?cntl[i-1][c]:0)*cx[i]);
                f[c]=max(f[c],mx+ad+(cntl[i-1].count(c)?cntl[i-1][c]:0)*cx[i]);
            }
        }
        cout<<*ranges::max_element(f)<<'\n';
    }();
    return 0;
}
