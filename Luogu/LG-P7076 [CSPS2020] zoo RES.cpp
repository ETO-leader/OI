#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using ull=unsigned long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    ull n,m,c,k;cin>>n>>m>>c>>k;
    set<char> Ap,Er;
    cir(i,0,n){
        ull x;cin>>x;
        cir(j,0,k) if(x&(1ULL<<j)) Ap.insert(j);
    }
    cir(i,0,k) Er.insert(i);
    cir(i,0,m){
        ull p,q;cin>>p>>q;
        if(!Ap.count(p)) Er.erase(p);
    }
    if(Er.size()==64&&(!n)) cout<<"18446744073709551616"<<endl;
    else cout<<(1ULL<<Er.size())-n<<endl;
    return 0;
}
