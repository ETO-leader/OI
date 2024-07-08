#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n,m,d;cin>>n>>m>>d;
        deque<int> s(m);
        for(auto&i:s) cin>>i;
        bool is1=true;
        if(s.front()!=1)
            s.push_front(1),is1=false;
        s.push_back(n+1);
        int sum=0;
        m=s.size()-1;
        cir(i,0,m+1){
            sum+=(s[i]-(i?s[i-1]:0)-1)/d+(i!=m);
        }
        int mx=0,cnx=0;
        cir(i,1,m){
            const int mxi=(s[i+1]-s[i]-1)/d+
                (s[i]-(i?s[i-1]:0)-1)/d+1
                -(s[i+1]-s[i-1]-1)/d;
            if(mxi>mx) mx=mxi,cnx=0;
            if(mxi==mx) ++cnx;
        }
        cout<<sum-mx<<' '<<cnx+(is1&&(!mx))<<'\n';
    }
    return 0;
}
