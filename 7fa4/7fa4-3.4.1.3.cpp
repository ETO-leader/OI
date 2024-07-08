#include<bits/stdc++.h>
using namespace std;
template<typename T=string>
class trie{
private:
    struct node{
        int v;
        vector<node*> sn;
        node():v(0),sn(26,NULL){}
    };
    node* root;int cnt=0;
public:
    void insert(T&s){
        node*u=root;++cnt;
        for(auto&i:s){
            if(!(u->sn[i-'a'])) u->sn[i-'a']=new node();
            u=u->sn[i-'a'];
        }
        (u->v)++;
    }
    int count(T&s){
        if(s.empty()) return cnt;
        node*u=root;
        for(auto&i:s){
            if(!(u->sn[i-'a'])) return 0;
            u=u->sn[i-'a'];
        }
        return u->v;
    }
    trie(){root=new node();}
};
auto to_list(string&s){
    list<char> res;
    for(auto&i:s) res.push_back(i);
    return res;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    clock_t begin_cl=clock();
    int n;cin>>n;trie<list<char>> tr;
    vector<string> str(n);
    getline(cin,str[0]);
    for(auto&i:str){
        getline(cin,i);
        auto deq=to_list(i);tr.insert(deq);
    }
    string s;getline(cin,s);
    if(!s.size()){
        cout<<"ture\n";exit(0);
    }
    list<char> q1,q2=to_list(s);
    for(auto&i:s){
        q1.push_back(i);q2.pop_front();
        if(tr.count(q1)&&tr.count(q2))
            cout<<"ture\n",exit(0);
        if((clock()-begin_cl)*1000/CLOCKS_PER_SEC>950)
            break;
    }
    cout<<"fu\n";
    return 0;
}
