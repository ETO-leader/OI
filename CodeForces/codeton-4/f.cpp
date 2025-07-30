#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class trygub{
private:
    map<int,int> x;
    const int c;
public:
    auto update(int b,int a){
        while(true){
            if(!a) break;
            auto&it=x[b];
            it+=a,a=it/c,it-=a*c;
            if(!it) x.extract(b);
            b++; 
        }
    }
    auto query(){
        auto it=prev(x.end());
        while(it!=x.begin()&&it->second<2){
            const auto w=prev(it);
            if(w->second>0) break;
            if(w->first!=it->first-1) return it->first;
            w->second+=c;
            x.erase(it);
            it=w;
        }
        return it->first+(it!=x.begin());
    }
    trygub(const auto _c):c(_c){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n,m,q;cin>>n>>m>>q;
        vector<int> a(n);
        trygub qwq(m);
        for(auto&i:a) cin>>i,qwq.update(i,1);
        cir(i,0,q){
            int x,y;cin>>x>>y;--x;
            qwq.update(a[x],-1);
            a[x]=y;
            qwq.update(a[x],1);
            cout<<qwq.query()<<' ';
        }
        cout<<'\n';
    }();
    return 0;
}
