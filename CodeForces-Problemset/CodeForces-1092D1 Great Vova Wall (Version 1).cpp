#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,w;cin>>n;stack<int> st;
    cir(i,0,n){
        cin>>w;
        if(!st.empty()&&(st.top()&1)==(w&1))
            st.pop();
        else st.push(w);
    }
    cout<<(st.size()<2?"YES":"NO")<<'\n';
    return 0;
}
