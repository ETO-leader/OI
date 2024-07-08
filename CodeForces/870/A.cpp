#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;vector<int> v(n);
        for(auto&i:v) cin>>i;
        sort(v.begin(),v.end());
        cout<<[&](){
            unordered_map<int,int> cnx;
            cir(i,0,n){
                cnx[v[i]]++;
                // A probability lier
                if(n-i-1<v[i]){
                    if(n-i-1+cnx[v[i]]>=v[i])
                        return -1;
                    return n-i;
                }
            }
            return 0;
        }()<<'\n';
    }
    return 0;
}
