#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
const int _inf=1e9+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<int> a(n);
    for(auto&i:a) cin>>i;
    vector<int> D(n,-1),C(n,_inf);
    vector<int> fd(n,-1),fc(n,-1),
        pd(n,-1),pc(n,-1);
    D[0]=_inf;C[0]=-1;
    cir(i,1,n){
        if(a[i]>a[i-1]){
            D[i]=D[i-1];pd[i]=pd[i-1];
            fd[i]=i-1;
        }
        if(a[i]>C[i-1]&&a[i-1]>D[i]){
            D[i]=a[i-1];pd[i]=i-1;
            fd[i]=pc[i-1];
        }
        if(a[i]<a[i-1]){
            C[i]=C[i-1];pc[i]=pc[i-1];
            fc[i]=i-1;
        }
        if(a[i]<D[i-1]&&a[i-1]<C[i]){
            C[i]=a[i-1];pc[i]=i-1;
            fc[i]=pd[i-1];
        }
    }
    auto print=[&](auto f,int w){
        vector<int> ans(n);
        fill(ans.begin(),ans.end(),(!w));
        int u=n-1;
        while(u>-1) (ans[u]=w),(u=f[u]);
        for(auto&i:ans) cout<<i<<' ';
        cout<<'\n';
    };
    cout<<((D[n-1]>-1||C[n-1]<_inf)?
        "YES":"NO")<<'\n';
    if(D[n-1]>-1) print(fd,0);
    else if(C[n-1]<_inf) print(fc,1);
    return 0;
}
