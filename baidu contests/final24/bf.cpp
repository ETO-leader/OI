#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) [&](){
        int n,q;cin>>n>>q;
        string s;cin>>s;
        vector<int> w(n);
        for(auto&i:w) cin>>i;
        cir(c,0,q){
            stack<int> stc,ws;
            map<int,int> cnt;
            int x,l,r;cin>>x>>l>>r;--l;--r;
            if(x==1) w[l]=++r;
            if(x==1) continue;
            for(auto i=l;i!=r;(++i)%=n){
                if(cnt[s[i]]&1){
                    while(s[stc.top()]!=s[i]) cnt[s[stc.top()]]^=1,stc.pop(),ws.pop();
                    stc.pop();ws.pop();
                }else{
                    stc.push(i);ws.push(w[i]);
                }
                cnt[s[i]]^=1;
            }
            if(cnt[s[r]]&1){
                while(s[stc.top()]!=s[r]) cnt[s[stc.top()]]^=1,stc.pop(),ws.pop();
                stc.pop();ws.pop();
            }else{
                stc.push(r);ws.push(w[r]);
            }
            cnt[s[r]]^=1;
            auto ans=0ll;
            while(!ws.empty()) /*clog<<(char)(s[stc.top()])<<' '<<ws.top()<<'\n',*/ans+=ws.top(),ws.pop(),stc.pop();
            cout<<ans<<'\n';
        }
    }();
    return 0;
}
