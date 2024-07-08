#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr lint _inf=1e18+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;
        string s;cin>>s;
        auto calc=[&](){
            vector<pair<lint,lint>> px;
            [&](){
                lint suml=0,cntl=0;
                cir(i,0,n){
                    px.push_back({suml,cntl});
                    suml+=(s[i]=='>')*(i+1);
                    cntl+=(s[i]=='>');
                }
            }();
            deque<lint> stc(1);lint psum=0;
            vector<lint> ans(n,_inf);
            for(int i=n-1;~i;--i){
                [&](){
                    const auto[suml,cntl](px[i]);
                    if(s[i]=='<'){
                        if(cntl>stc.size()-1) return;
                        ans[i]=(i*cntl-suml+psum-i*(cntl)-stc[cntl]+cntl)*2+(i+1);
                    }else{
                        if(cntl+1>stc.size()-1) return;
                        ans[i]=(i*cntl-suml+psum-i*(cntl+1)-stc[cntl+1]+cntl)*2+(i+1);
                    }
                }();
                if(s[i]=='<'){
                    stc.push_front(psum+=i);
                }
            }
            return ans;
        };
        auto ansa=calc();
        for(auto&i:s) i=(i=='<'?'>':'<');
        reverse(s.begin(),s.end());
        auto ansb=calc();
        reverse(ansb.begin(),ansb.end());
        cir(i,0,n) cout<<min(ansa[i],ansb[i])<<' ';
        cout<<'\n';
    }
    return 0;
}
