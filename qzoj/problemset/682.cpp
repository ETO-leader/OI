#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    string s;
    vector<int> tr;
    auto c=0;
    while(cin>>s){
        if(s=="GET"){
            ++c;
            if(c>(int)(tr.size())) cout<<0<<' ',--c;
            else cout<<tr[c-1]<<' ';
        }else{
            const auto v=atoi(string(s.begin()+4,s.end()-1).data());
            tr.emplace(upper_bound(tr.begin(),tr.end(),v),v);
        }
    }
    cout<<'\n';
    return 0;
}
