#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("bracket.in");
ofstream ouf("bracket.out");
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int c,T;inf>>c>>T;
    while(T--) []{
        string s;inf>>s;
        const auto n=(int)(s.size());
        vector<int> pre(n);
        auto w=0;
        cir(i,0,n) pre[i]=(w+=(s[i]=='('?1:-1));
        stack<int> pos,cnt;
        pos.emplace(-1);
        cnt.emplace(1);
        auto ans=0ll;
        cir(i,0,n){
            while((!pos.empty())&&((pos.top()<0?0:pre[pos.top()]))>pre[i]){
                pos.pop();
                cnt.pop();
            }
            if(pos.empty()||(pos.top()<0?0:pre[pos.top()])!=pre[i]){
                cnt.emplace(0);
                pos.emplace(i);
            }
            if(!cnt.empty()) ans+=cnt.top();
            ++cnt.top();
        }
        ouf<<ans<<'\n';
    }();
    return 0;
}

