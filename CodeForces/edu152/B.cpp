#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
struct qry{int x,id;};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n,k;cin>>n>>k;
        vector<qry> a(n);
        cir(i,0,n){
            cin>>a[i].x;a[i].id=i+1;
            (--a[i].x)%=k;
        }
        sort(a.begin(),a.end(),[](qry&a,qry&b){
            const int wa=a.x,wb=b.x;
            return wa==wb?a.id<b.id:wa>wb;
        });
        for(auto&[x,id]:a) cout<<id<<' ';
        cout<<'\n';
    }
    return 0;
}
