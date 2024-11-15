#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e16l);
class bit{
private:
    vector<vector<lint>> a;
    constexpr auto lowbit(auto x){return x&(-x);}
public:
    auto update(int x,int y,lint w){
        for(++x;x<(int)(a.size());x+=lowbit(x)){
            for(auto p=y+1;p<(int)(a[x].size());p+=lowbit(p)) a[x][p]=max(a[x][p],w);
        }
    }
    auto query(int x,int y){
        auto res=0ll;
        for(++x;x;x-=lowbit(x)){
            for(auto p=y+1;p;p-=lowbit(p)) res=max(res,a[x][p]);
        }
        return res;
    }
    bit(int _n):a(_n+1,vector(_n+1,-_infl)){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int n,m,v;cin>>n>>m>>v;
        const auto[a,b]=[&](){
            vector<lint> b(n);
            for(auto&i:b) cin>>i;
            vector<int> arr(n);
            cir(i,0,m){
                char c;int p;cin>>c>>p;--p;
                if(c=='L'){
                    ++arr[0];
                    if(p+1<n) --arr[p+1];
                }else{
                    ++arr[p];
                }
            }
            cir(i,1,n) arr[i]+=arr[i-1];
            vector<lint> ra,rb;
            for(auto i=n-1;i;--i) if(arr[i-1]==arr[i]) b[i-1]+=b[i];
            cir(i,0,n) if((arr[i]<v+1)&&((!i)||(arr[i-1]!=arr[i]))) ra.push_back(arr[i]),rb.push_back(b[i]);
            return pair(ra,rb);
        }();
        const auto rn=(int)(a.size()); 
        bit fb(v+1);
        fb.update(0,0,0);
        cir(i,0,rn){
            vector<lint> fx(v+1);
            for(auto p=0;p+a[i]<v+1;++p) fx[p]=fb.query(p,p+a[i])+b[i];
            for(auto p=0;p+a[i]<v+1;++p) fb.update(p,p+a[i],fx[p]);
        }
        cir(i,1,v+1){
            print("{} ",fb.query(i,i));
        }
        println("");
    }();
    return 0;
}
