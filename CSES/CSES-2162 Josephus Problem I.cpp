#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;list<int> st;
    if(!(n-1)){cout<<1<<'\n';exit(0);}
    cir(i,1,n+1) st.push_back(i);
    auto fs=++st.begin(),nw=st.begin();
    ++fs,++nw;
    cir(i,0,n){
        st.erase(nw);cout<<*nw<<' ';
        if(st.empty()) break;
        if((++fs)==st.end()) fs=st.begin();
        nw=fs;
        if((++fs)==st.end()) fs=st.begin();
    }
    cout<<'\n';
    return 0;
}