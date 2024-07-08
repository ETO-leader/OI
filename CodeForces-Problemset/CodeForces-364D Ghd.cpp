#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
constexpr int cks=10;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;VI a(n);
    mt19937 rnd(time(NULL));
    for(auto&i:a) cin>>i;
    lint ans=1;
    unordered_set<lint> cked;
    cir(i,0,cks){
        lint p=rnd()%n,&px=a[p];
        VI ps;
        for(lint x=1;x*x<px+1;++x){
            if(!(px%x)){
                const lint ix=px/x;
                if(x>ans) ps.push_back(x);
                if(ix>ans&&x!=ix) ps.push_back(ix);
            }
        }
        sort(ps.begin(),ps.end());
        VI cnx(ps.size());
        for(auto&i:a) if(gcd(px,i)>ans){
            ++cnx[lower_bound(ps.begin(),
                ps.end(),gcd(px,i))-ps.begin()];
        }
        cir(i,0,ps.size()) cir(j,0,ps.size()){
            if(i!=j&&(!(ps[j]%ps[i])))
                cnx[i]+=cnx[j];
        }
        for(int i=ps.size()-1;~i;--i){
            if(cnx[i]*2>n-1){
                ans=ps[i];break;
            }
        }
    }
    cout<<ans<<'\n';
    return 0;
}
