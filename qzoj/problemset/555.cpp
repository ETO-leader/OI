#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    vector<int> a(10);
    iota(a.begin(),a.end(),1);
    vector<int> isp(20);
    for(auto x:{2,3,5,7,11,13,17,19}) isp[x]=true;
    do{
        auto ok=true;
        cir(i,0,10) ok&=isp[a[i]+a[(i+1)%10]];
        if(ok){
            for(auto&x:a) cout<<x<<' ';
            cout<<'\n';
        }
        if(a[0]>1) break;
    }while(next_permutation(a.begin(),a.end()));
    return 0;
}
