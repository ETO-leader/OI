#include<bits/stdc++.h>
using namespace std;
class trie{
private:
    struct node{
        int v;
        vector<node*> sn;
        node():v(0),sn(127,NULL){}
    };
    node* root;int cnt=0;
public:
    void insert(string&s){
        node*u=root;++cnt;
        for(auto&i:s){
            if(!(u->sn[i])) u->sn[i]=new node();
            u=u->sn[i];(u->v)++;
        }
    }
    int count_prefix(string&s){
        if(s.empty()) return cnt;
        node*u=root;
        for(auto&i:s){
            if(!(u->sn[i])) return 0;
            u=u->sn[i];
        }
        return u->v;
    }
    trie(){root=new node();}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;trie tr;
    vector<string> str(n);
    getline(cin,str[0]);
    for(auto&i:str)
        getline(cin,i),tr.insert(i);
    for(auto&i:str)
        cout<<tr.count_prefix(i)-1<<'\n';
    return 0;
}
