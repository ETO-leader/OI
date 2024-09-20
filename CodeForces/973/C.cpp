#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
map<string,int> cans;
auto ask(string s){
    if(cans.count(s)) return cans[s];
    cout<<format("? {}",s)<<'\n';
    cout.flush();
    int x;cin>>x;
    return cans[s]=x;
}
auto answer(string s){
    cout<<format("! {}",s)<<'\n';
    cout.flush();
}
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int n;cin>>n;cans.clear();
        auto curs=string("");
        while((int)(curs.size())<n){
            curs+='0';
            if(ask(curs)) continue;
            curs.pop_back();
            curs+='1';
            if(ask(curs)) continue;
            curs.pop_back();
            break;
        }
        if((int)(curs.size())==n) return answer(curs);
        while((int)(curs.size())<n){
            curs='0'+curs;
            if(ask(curs)) continue;
            curs.erase(curs.begin());
            curs='1'+curs;
        }
        answer(curs);
    }();
    return 0;
}
