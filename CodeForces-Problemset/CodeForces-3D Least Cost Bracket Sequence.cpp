#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
struct heapnode{
    int vi,pos;
    bool operator<(const heapnode&hp) const{
        return vi>hp.vi;
    }
};
struct cst{lint ca,cb;};
void stringerror(){
    cout<<"-1\n";exit(0);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    string s,ansstr;cin>>s;
    ansstr=s;
    [&ansstr](){
        for(auto&i:ansstr) if(i=='?') i=')';
    }();
    priority_queue<heapnode> hp;
    vector<cst> vc(s.size());
    for(auto&[ca,cb]:vc) cin>>ca>>cb;
    lint ans=0;
    [&](){
        int qrycnt=-1,cnx=0,p=0;
        for(auto&i:s){
            if(i=='?'){
                qrycnt++;
                hp.push({vc[qrycnt].ca-vc[qrycnt].cb,p});
                ans+=vc[qrycnt].cb;
                --cnx;
            }else{
                cnx+=(i=='('?1:-1);
            }
            while(cnx<0){
                if(hp.empty()) stringerror();
                auto [w,ix]=hp.top();hp.pop();
                ans+=w;ansstr[ix]='(';cnx+=2;
            }
            ++p;
        }
        if(cnx) stringerror();
    }();
    cout<<ans<<'\n'<<ansstr<<'\n';
    return 0;
}