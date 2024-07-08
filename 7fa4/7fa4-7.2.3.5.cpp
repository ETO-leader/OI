#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<int> a(n);
    for(auto&i:a) cin>>i;
    cout<<n<<'\n';
    cir(i,0,n){
        string cmv(n,'1');
        for(auto p=(i&1);p+1<n;p+=2){
            if(a[p]>a[p+1]){
                swap(a[p],a[p+1]);
                cmv[(p+1+i)%n]='0';
            }
        }
        for(const auto x:cmv) cout<<x;
        cout<<'\n';
    }
    return 0;
}
