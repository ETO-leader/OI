#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,k;lint l;cin>>n>>k>>l;
    l*=2;
    vector<tuple<lint,int,char>> info(n);
    for(auto&[p,col,dir]:info) cin>>p>>col>>dir,p*=2;
    sort(info.begin(),info.end());
    vector<lint> ans(k);
    vector<lint> gap(k);
    auto first_r=-1ll,last_r=-1ll;
    auto sum=0ll;
    for(auto&[p,col,dir]:info){
        if(dir=='L'){
            if(first_r<0){
                ans[col]+=p;
            }else{
                const auto t=(p-first_r)/2;
                ans[(col+sum)%k]+=first_r+t;
                cir(i,0,k) ans[(col+i)%k]+=gap[i];
                const auto tr=(p-last_r)/2;
                ans[col]+=tr;
            }
        }else{
            ans[col]+=l-p;
            if(first_r>-1){
                gap[0]+=(p-last_r)/2;
                const auto g=gap;
                cir(i,0,k) gap[(i+col)%k]=g[i];
            }else{
                first_r=p;
            }
            last_r=p;
            (sum+=col)%=k;
        }
    }
    for(auto&x:ans) cout<<x/2<<(x&1?".5":".0")<<'\n';
    return 0;
}
