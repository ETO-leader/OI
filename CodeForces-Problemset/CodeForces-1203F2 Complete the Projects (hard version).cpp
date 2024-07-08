#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
struct prog{int a,b;};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,r;cin>>n>>r;
    vector<prog> a,b;
    cir(i,0,n){
        int ai,bi;cin>>ai>>bi;
        if(bi>0) a.push_back({ai,bi});
        else b.push_back({ai,bi});
    }
    sort(a.begin(),a.end(),[](prog&x,prog&y){
        return x.a==y.a?x.b<y.b:x.a<y.a;
    });
    sort(b.begin(),b.end(),[](prog&x,prog&y){
        return x.a+x.b>y.a+y.b;
    });
    int cnx=0;
    for(auto&[ai,bi]:a){
        if(ai<r+1) r+=bi,++cnx;
    }
    vector<int> D(r+1);D[r]=cnx;
    for(auto&[ai,bi]:b) if(ai<r+1){
        for(int i=max(-bi,ai);i<r+1;++i){
            D[i+bi]=max(D[i+bi],D[i]+1);
        }
    }
    cout<<*max_element(
        D.begin(),D.end())<<'\n';
    return 0;
}
