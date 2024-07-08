#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int _inf=1e9+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,st=0;cin>>n;vector<int> v(n);
    for(auto&i:v) cin>>i;
    //计算区间 [l,r) 所需次数
    function<int(int,int)> sol=[&](int l,int r){
        int cnx=_inf,pl=l;
        if(r<=l) return 0;
        if(r-1==l) return min(v[l],1);
        cir(i,l,r){
            if(v[i]<cnx) cnx=v[i],pl=i;
        }
        cir(i,l,r) v[i]-=cnx;
        return min(r-l,sol(l,pl)+sol(pl+1,r)+cnx);
    };
    cout<<sol(0,n)<<'\n';
    return 0;
}
