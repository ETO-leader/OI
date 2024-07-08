#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;stack<int> st;vector<int> k(n);
    cir(i,0,n){
        cin>>k[i];
        while(!st.empty()&&k[i]<=k[st.top()]) st.pop();
        cout<<(st.empty()?0:st.top()+1)<<' ';
        st.push(i);
    }
    cout<<'\n';
    return 0;
}