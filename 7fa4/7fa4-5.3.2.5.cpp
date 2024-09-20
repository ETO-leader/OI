#include<bits/stdc++.h>
using namespace std;
using ulint=unsigned long long;
static constexpr auto maxn=(int)(1e5+7);
template<const size_t siz>
class bitst{
private:
    array<ulint,(siz>>6)+1> ar;
public:
    auto st(size_t p){
        ar[p>>6]|=(1ull<<(p&63));
    }
    auto operator&(bitst<siz> x) const{
        auto res=*this;
        for(int i=0;i<(int)(ar.size());++i) res.ar[i]&=x.ar[i];
        return res;
    }
    auto count() const{
        auto res=0;
        for(auto&i:ar) res+=__builtin_popcountll(i);
        return res;
    }
    bitst(){fill(ar.begin(),ar.end(),0);}
    bitst(auto x){fill(ar.begin(),ar.end(),0);}
};
using bst=bitst<maxn>;
template<typename Key,typename _Ty,class func=hash<Key>>
class cc_hash_table{
private:
    static constexpr auto mem=(size_t)(5e6+7);
    array<list<pair<Key,_Ty>>,mem> ht;
    vector<Key> vaild;
    func f;
public:
    auto count(Key x){
        const auto p=f(x)%mem;
        for(auto&[k,t]:ht[p]) if(k==x) return true;
        return false;
    }
    auto&operator[](Key x){
        const auto p=f(x)%mem;
        for(auto&[k,t]:ht[p]) if(k==x) return t;
        ht[p].push_back({x,_Ty(0)});
        vaild.push_back(x);
        return ht[p].back().second;
    }
    auto elements(){return vaild;}
};
class hashing{
private:
    static constexpr auto hashc=251ull;
    ulint x;
public:
    auto append(char c){(x*=hashc)+=c;}
    auto operator()(){return x;}
    auto clear(){x=0;}
    hashing():x(0){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,q;cin>>n>>q;
    vector<string> qs(n);
    vector<pair<string,int>> as(q);
    for(auto&i:qs) cin>>i;
    for(auto c=-1;auto&[s,id]:as) cin>>s,id=++c;
    sort(qs.begin(),qs.end(),[&](auto&a,auto&b){
        return a.size()>b.size();
    });
    sort(as.begin(),as.end(),[&](auto&a,auto&b){
        return a.first.size()>b.first.size();
    });
    static constexpr auto sqr=200;
    cc_hash_table<ulint,vector<int>> apsl,apsr;
    cc_hash_table<ulint,bst> lgl,lgr;
    auto buildbst=[&](auto&ar,ulint i){
        bst b;
        const auto&x=ar[i];
        for(auto&w:x) b.st(w);
        return b;
    };
    const auto inspre=[&](ulint x,int id){
        if(lgl.count(x)){
            lgl[x].st(id);
        }else{
            apsl[x].push_back(id);
            if(apsl[x].size()>sqr) lgl[x]=buildbst(apsl,x);
        }
    };
    const auto inssuf=[&](ulint x,int id){
        if(lgr.count(x)){
            lgr[x].st(id);
        }else{
            apsr[x].push_back(id);
            if(apsr[x].size()>sqr) lgr[x]=buildbst(apsr,x);
        }
    };
    vector<int> ans(q);
    auto it=qs.begin();
    for(auto&[s,id]:as){
        while(it!=qs.end()&&it->size()+2>s.size()){
            hashing hx;
            const auto ix=it-qs.begin();
            inspre(0,ix);inssuf(0,ix);
            for(auto&c:*it) hx.append(c),inspre(hx(),ix);
            hx.clear();
            reverse(it->begin(),it->end());
            for(auto&c:*it) hx.append(c),inssuf(hx(),ix);
            ++it;
        }
        hashing pre,suf;
        for(auto&c:s){
            if(c=='*') break;
            pre.append(c);
        }
        reverse(s.begin(),s.end());
        for(auto&c:s){
            if(c=='*') break;
            suf.append(c);
        }
        const auto sl=lgl.count(pre())?lgl[pre()]:buildbst(apsl,pre());
        const auto sr=lgr.count(suf())?lgr[suf()]:buildbst(apsr,suf());
        ans[id]=(sl&sr).count();
    }
    copy(ans.begin(),ans.end(),ostream_iterator<int>(cout,"\n"));
    return 0;
}
