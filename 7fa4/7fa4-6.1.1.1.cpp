#include<bits/stdc++.h>
using namespace std;
using lint=long long;
mt19937_64 rnd(time(NULL));
template<typename T>
class treap{
private:
    struct node{
        T ky;u_int64_t hp;
        size_t siz;
        array<node*,2> s;
        size_t ssz(int k){
            return s[k]?s[k]->siz:(size_t)(0);
        }
        void flush(){siz=ssz(0)+ssz(1)+1;}
        node(T k,size_t sz=1){
            auto r=rnd();
            ky=k;hp=(r+(!r))*sz;siz=sz;
            s[0]=nullptr;s[1]=nullptr;
        }
        ~node(){
            if(s[0]) delete s[0];
            if(s[1]) delete s[1];
        }
    };
    enum rotate_type{rrotate,lrotate};
    node*root;
    void rotate(node*&u,rotate_type r){
        node*ux=u->s[r];
        u->s[r]=ux->s[!r];
        ux->s[!r]=u;
        u->flush();ux->flush();
        u=ux;
    }
    void insert(node*&u,T w){
        if(!u->s[w>u->ky-1]){
            u->s[w>u->ky-1]=new node(w);
            u->flush();
            return;
        }
        insert(u->s[w>u->ky-1],w);
        u->flush();
        if((u->s[0])&&u->s[0]->hp>u->hp){
            rotate(u,rrotate);
        }else if((u->s[1])&&u->s[1]->hp>u->hp){
            rotate(u,lrotate);
        }
    }
public:
    void insert(T w){
        if(!root){
            return (root=new node(w)),void();
        } 
        insert(root,w);
    }
    size_t order_of_key(T w){
        size_t rnk=0,ans=0;
        node*u=root;
        while(u){
            rnk+=(u->ky<w+1)*(u->ssz(0)+1);
            if(u->ky<w+1) ans=rnk;
            u=u->s[u->ky<w+1];
        }
        return ans;
    }
    T find_by_order(size_t rnk){
        node*u=root;
        while(u){
            if(u->ssz(0)+1==rnk) return u->ky;
            if(rnk>u->ssz(0)){
                rnk-=(u->ssz(0)+1);u=u->s[1];
            }else{
                u=u->s[0];
            }
        }
        throw (string)("Error rank range.");
    }
    treap():root(nullptr){}
    ~treap(){if(root) delete root;}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int q;lint lastans=0;cin>>q;
    treap<lint> tr;
    while(q--){
        int op;lint x;cin>>op>>x;x^=lastans;
        if(op==1){
            tr.insert(x);
        }else if(op==2){
            cout<<(lastans=
                tr.order_of_key(x))<<'\n';
        }else{
            cout<<(lastans=
                tr.find_by_order(x))<<'\n';
        }
        cout.flush();
    }
    return 0;
}
