#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
struct cnx{
    int w,cx;
    cnx&operator+=(const int p){
        (p>w?w=p,cx=1:(p==w?++cx:cx=cx));
        return *this;
    }
};
class vector_int_trie{
private:
    struct node{
        bool endtag;
        unordered_map<int,node*> s;
        node():endtag(false){}
    };
    node*root;
    node*gowith(node*nx){
        return (nx==nullptr?new node():nx);
    }
public:
    bool insert(vector<int>&v){
        auto u=root;
        for(auto&i:v) u=gowith(u->s[i]);
        return u->endtag?false:(u->endtag=true);
    }
    vector_int_trie(){root=new node();}
};
struct quary{vector<int> p,c;};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;unordered_map<int,cnx> cnt;
    vector<quary> qr(n);
    for(auto&[p,c]:qr){
        int mi;cin>>mi;
        cir(i,0,mi){
            int pi,ci;cin>>pi>>ci;
            p.push_back(pi),c.push_back(ci);
            cnt[pi]+=ci;
        }
    }
    int ans=0;
    vector_int_trie tr;
    for(auto&[p,c]:qr){
        vector<int> ins;
        cir(i,0,p.size()){
            if(!(c[i]<cnt[p[i]].w||cnt[p[i]].cx>1))
                ins.push_back(p[i]);
        }
        ans+=tr.insert(ins);
    }
    cout<<ans<<'\n';
    return 0;
}
