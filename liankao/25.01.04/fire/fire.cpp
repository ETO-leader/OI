#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("fire.in");
ofstream fcout("fire.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
using lint=long long;
constexpr auto f(lint a,lint b,lint c){
    return a*(a-1)*2+b*(b-1)+c*(c-1)*3+a*b*4+a*c*6+b*c*6+2;
}
int main(){
    ios::sync_with_stdio(false),fcin.tie(nullptr);
    int T;fcin>>T;
    while(T--) []{
        lint x,a,b,c;fcin>>x>>a>>b>>c;
        if(x==1) return fcout<<0<<' '<<0<<' '<<0<<"\n---\n",void();
        vector<tuple<lint,lint,lint>> ansa;
        cir(_a,0,a) cir(_c,0,c){
            auto l=(_a||_c?0ll:1ll),r=b-1,ans=-1ll;
            while(l-1<r){
                const auto mid=(l+r)/2;
                f(_a,mid,_c)<x?(l=mid+1):((ans=mid),(r=mid-1));
            }
            if(ans>-1&&(_a||ans||_c)&&f(_a,ans,_c)==x) ansa.emplace_back(_a,ans,_c);
        }
        sort(ansa.begin(),ansa.end());
        for(auto&[_a,_b,_c]:ansa) fcout<<_a<<' '<<_b<<' '<<_c<<'\n';
        fcout<<"---\n";
    }();
    return 0;
}