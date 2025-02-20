#include<vector>
#include<iostream>
#include<assert.h>

class interactor{
private:
    std::vector<int> p;
    std::vector<long long> a;
    int cnt;
public:
    auto getn(){
        return (int)(p.size());
    }
    auto ask(int u,int v){
        assert(u!=v);
        ++cnt;
        auto res=0ll;
        for(auto i=std::min(p[u],p[v]);i<std::max(p[u],p[v])+1;++i) res+=a[i];
        std::cerr<<"? "<<u<<' '<<v<<" --> "<<p[u]<<' '<<p[v]<<' '<<res<<'\n';
        return res;
    }
    auto answer(std::vector<int> _p,std::vector<long long> _a){
        std::cerr<<" T = "<<cnt<<'\n';
        using std::cout;
        cout<<"-----------------------\n";
        cout<<"! ";
        for(auto&i:p) cout<<i+1<<' ';
        for(auto&i:a) cout<<i<<' ';
        cout<<'\n';
        cout.flush();
        cout<<"-----------------------\n";
        for(std::cerr<<"_a = ";auto&i:_a) std::cerr<<i<<' ';
        std::cerr<<'\n';
        if(p==_p&&a==_a){
            std::cerr<<"ac\n";
        }else{
            std::cerr<<"p = ";
            for(auto&i:p) std::cerr<<i<<' ';
            std::cerr<<'\n';
            std::cerr<<"_p = ";
            for(auto&i:_p) std::cerr<<i<<' ';
            std::cerr<<'\n';
            std::cerr<<"a = ";
            for(auto&i:a) std::cerr<<i<<' ';
            std::cerr<<'\n';
            std::cerr<<"_a = ";
            for(auto&i:_a) std::cerr<<i<<' ';
            std::cerr<<'\n';
            std::cerr<<"wa\n";
        }
    }
    interactor():cnt(0){
        int n;std::cin>>n;
        p.resize(n);
        a.resize(n);
        for(auto&i:p) std::cin>>i,--i;
        for(auto&i:a) std::cin>>i;
    }
} interact;