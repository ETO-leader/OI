#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;n*=2;
    vector<int> p(n),q(n);
    for(auto&x:p) cin>>x,--x;
    for(auto&x:q) cin>>x,--x;
    auto ans=string(n,'?');
    auto lcnt=-1,rcnt=n;
    cir(i,0,n){
        if(ans[p[i]]=='?'){
            ans[p[i]]='(';
            cir(x,lcnt+1,p[i]) ans[x]=')';
            lcnt=p[i];
        }
        if(ans[q[i]]=='?'){
            ans[q[i]]='(';
            cir(x,q[i]+1,rcnt) ans[x]=')';
            rcnt=q[i];
        }
        if(ans[p[n-i-1]]=='?'){
            ans[p[n-i-1]]=')';
            cir(x,p[n-i-1]+1,rcnt) ans[x]='(';
            rcnt=p[n-i-1];
        }
        if(ans[q[n-i-1]]=='?'){
            ans[q[n-i-1]]=')';
            cir(x,lcnt+1,q[n-i-1]) ans[x]='(';
            lcnt=q[n-i-1];
        }
    }
    if(ranges::count(ans,'(')!=n/2){
        cout<<-1<<'\n';
    }else{
        const auto rp=[&]{
            vector<int> rp(n);
            priority_queue<int,vector<int>,greater<int>> ql;
            priority_queue<int,vector<int>,greater<int>> qr;
            cir(i,0,n) (ans[i]=='('?ql:qr).emplace(i);
            auto cnt=0;
            cir(i,0,n){
                if(!cnt){
                    ++cnt;
                    rp[i]=ql.top();ql.pop();
                }else{
                    if((!ql.empty())&&ql.top()<qr.top()){
                        ++cnt;
                        rp[i]=ql.top();ql.pop();
                    }else{
                        --cnt;
                        rp[i]=qr.top();qr.pop();
                    }
                }
            }
            return rp;
        }();
        const auto rq=[&]{
            vector<int> rq(n);
            priority_queue<int> ql;
            priority_queue<int> qr;
            cir(i,0,n) (ans[i]=='('?ql:qr).emplace(i);
            auto cnt=0;
            cir(i,0,n){
                if(!cnt){
                    ++cnt;
                    rq[i]=ql.top();ql.pop();
                }else{
                    if((!ql.empty())&&ql.top()>qr.top()){
                        ++cnt;
                        rq[i]=ql.top();ql.pop();
                    }else{
                        --cnt;
                        rq[i]=qr.top();qr.pop();
                    }
                }
            }
            return rq;
        }();
        if(rp==p&&rq==q){
            cout<<ans<<'\n';
        }else{
            cout<<-1<<'\n';
        }
    }
    return 0;
}
