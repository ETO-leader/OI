#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class Cache{
private:
    static constexpr auto _inf=(int)(1e9+7);
    enum{
        Invalid,
        Exclusive,
        Shared,
        Modified
    };
    vector<int> statu;
    int n;
    auto BusRd(){
        auto res=_inf;
        cir(i,0,n){
            if(statu[i]==Exclusive||statu[i]==Shared){
                statu[i]=Shared;
                res=min(res,i);
            }else if(statu[i]==Modified){
                statu[i]=Shared;
                cout<<"FlushOpt "<<i+1<<'\n';
                cout<<"MemoryWr "<<i+1<<'\n';
                res=-(i+1);
            }
        }
        if(res<_inf&&res>-1){
            cout<<"FlushOpt "<<res+1<<'\n';
        }
        return abs(res);
    }
    auto BusRdX(){
        auto res=_inf;
        cir(i,0,n){
            if(statu[i]==Exclusive||statu[i]==Shared){
                statu[i]=Invalid;
                res=min(res,i);
            }else if(statu[i]==Modified){
                statu[i]=Invalid;
                cout<<"FlushOpt "<<i+1<<'\n';
                cout<<"MemoryWr "<<i+1<<'\n';
                res=-(i+1);
            }
        }
        if(res<_inf&&res>-1){
            cout<<"FlushOpt "<<res+1<<'\n';
        }
        return abs(res);
    }
    auto BusUpgr(){
        cir(i,0,n) if(statu[i]==Shared) statu[i]=Invalid;
    }
    auto __builtin_Flush(){
        cir(i,0,n) if(statu[i]==Modified){
            cout<<"MemoryWr "<<i+1<<'\n';
            statu[i]=Exclusive;
        }
    }
public:
    auto PrRd(int i){
        if(statu[i]==Invalid){
            cout<<"BusRd "<<i+1<<'\n';
            auto askans=BusRd();
            if(askans<_inf){
                statu[i]=Shared;
            }else{
                cout<<"MemoryRd "<<i+1<<'\n';
                statu[i]=Exclusive;
            }
        }
    }
    auto PrWr(int i){
        if(statu[i]==Invalid){
            cout<<"BusRdX "<<i+1<<'\n';
            auto askans=BusRdX();
            if(askans==_inf) cout<<"MemoryRd "<<i+1<<'\n';
        }else if(statu[i]==Shared){
            cout<<"BusUpgr "<<i+1<<'\n';
            BusUpgr();
        }
        statu[i]=Modified;
    }
    auto GetStatu(int u){
        if(statu[u]==Invalid) return "Invalid";
        if(statu[u]==Exclusive) return "Exclusive";
        if(statu[u]==Shared) return "Shared";
        return "Modified";
    }
    auto Flush(){
        __builtin_Flush();
    }
    Cache(int _n):n(_n),statu(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;Cache cache(n);
    cir(i,0,q){
        string op;cin>>op;
        if(op=="R"){
            int u;cin>>u;--u;
            cache.PrRd(u);
        }else if(op=="W"){
            int u;cin>>u;--u;
            cache.PrWr(u);
        }else if(op=="F"){
            cache.Flush();
        }else{
            int u;cin>>u;--u;
            cout<<cache.GetStatu(u)<<'\n';
        }
    }
    return 0;
}
