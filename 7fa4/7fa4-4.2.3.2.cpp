#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
vector<lint> initlnum(lint x){
    vector<lint> res;
    cir(len,0,10){
        cir(s,0,(1<<(len+1))){
            lint wi=0;
            cir(i,0,len+1){
                wi*=10;
                wi+=(s&(1<<i)?8:6); 
            }
            for(auto&i:res) if(!(wi%i)) goto fail;
            if(wi<=x) res.push_back(wi);
            fail:;
        }
    }
    return res;
}
lint lcm(lint a,lint b){return a/__gcd(a,b)*b;}
bool cktrue(lint a,lint b,lint mx){
    return mx/(a/__gcd(a,b))>=b;}
vector<lint> lky;
lint dfs(lint a,lint b,int pos=0,lint l=1,
    bool tag_1=false,bool chtag=false){
    if(l>b) return 0;
    lint res=(chtag?(b/l-(a-1)/l)*(tag_1?1:-1):0);
    if(pos>=lky.size()) return res;
    if(cktrue(l,lky[pos],b))
        res+=dfs(a,b,pos+1,lcm(l,lky[pos]),!tag_1,true);
    res+=dfs(a,b,pos+1,l,tag_1,false);
    return res;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    lint a,b;cin>>a>>b;
    lky=initlnum(b);
    reverse(lky.begin(),lky.end());
    cout<<dfs(a,b)<<'\n';
    return 0;
}
