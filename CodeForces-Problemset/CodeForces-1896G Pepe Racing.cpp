#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class interactor{
public:
    static auto casesum(){
        int T;cin>>T;
        return T;
    }
    static auto init(int&n){
        cin>>n;
    }
    static auto ask(vector<int> a){
        cout<<"? ";
        for(auto&i:a) cout<<i+1<<' ';
        cout<<'\n';
        cout.flush();
        int r;cin>>r;--r;
        return r;
    }
    static auto answer(vector<int> a){
        cout<<"! ";
        for(auto&i:a) cout<<i+1<<' ';
        cout<<'\n';
        cout.flush();
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    auto T=interactor::casesum();
    while(T--) []{
        int n;interactor::init(n);
        vector<int> ans;
        set<int> nmx,umx;
        vector<int> vis(n*n),bid(n*n);
        auto initblc=[&](int b){
            const auto l=b*n,r=(b+1)*n-1;
            vector<int> q;
            cir(i,l,r+1) if(!vis[i]){
                q.emplace_back(i);
                if(nmx.contains(i)) nmx.extract(i);
            }
            while((int)(q.size())<n) q.emplace_back(*nmx.begin()),nmx.extract(nmx.begin());
            const auto p=interactor::ask(q);
            for(auto&x:q) if(x!=p) nmx.emplace(x);
            bid[p]=b;
            vis[p]=true;
            return p;
        };
        cir(i,0,n) umx.emplace(initblc(i));
        while(n*n-(int)(ans.size())>n*2-1){
            const auto x=interactor::ask(vector(umx.begin(),umx.end()));
            umx.extract(x);
            ans.emplace_back(x);
            const auto xb=bid[x];
            umx.emplace(initblc(xb));
        }
        vector<int> q;
        cir(i,0,n*n) if(!vis[i]) q.emplace_back(i);
        auto lumx=umx;
        cir(i,0,n-1){
            const auto x=interactor::ask(vector(umx.begin(),umx.end()));
            lumx.extract(x);
            umx.extract(x);
            ans.emplace_back(x);
            if(!q.empty()){
                umx.emplace(q.back());
                q.pop_back();
            }
        }
        ans.emplace_back(*lumx.begin());
        interactor::answer(ans);
    }();
    return 0;
}
