#include<bits/stdc++.h>
#define cir(i,a,b,v) for(int i=a;i<b;i+=v)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<int> v(n);
    for(auto&i:v) cin>>i;
    if(!((n&1)||!accumulate(v.begin(),v.end(),
        0,[](int a,int b){return a^b;
        }))) [](){cout<<"NO\n";exit(0);}();
    [&](){
        int cnx=0;
        cout<<"YES\n";
        stringstream ss;
        cir(i,0,n-2,2)
            ss<<i+1<<' '<<i+2<<' '<<i+3<<'\n',++cnx;
        cir(i,0,n-4,2)
            ss<<i+1<<' '<<i+2<<' '<<n<<'\n',++cnx;
        cout<<cnx<<'\n'<<ss.str()<<'\n';
    }();
    return 0;
}