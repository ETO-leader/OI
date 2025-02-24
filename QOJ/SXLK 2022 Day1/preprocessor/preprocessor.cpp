#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
enum info_type{word,character};
struct unit{
    string info;
    info_type type;
    unit(auto _info,auto _type):info(_info),type(_type){}
};
const auto accepts=(string)("QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm_1234567890");
auto split(string s){
    vector<unit> ures;
    unordered_set<char> accept;
    for(auto&i:accepts) accept.emplace(i);
    auto word_right_it=[&](auto it){
        string res;
        while(it<s.end()&&accept.count(*it)) res+=*it,++it;
        if(!res.empty()) ures.emplace_back(res,word);
        return it;
    };
    auto character_right_it=[&](auto it){
        string res;
        while(it<s.end()&&(!accept.count(*it))) res+=*it,++it;
        if(!res.empty()) ures.emplace_back(res,character);
        return it;
    };
    auto p=s.begin();
    while(p<s.end()) p=character_right_it(word_right_it(p));
    return ures;
}
unordered_map<string,string> symbols;
unordered_set<string> in_stack;
auto expand_s(string s)->string{
    const auto data=split(s);
    string res;
    for(auto&[info,type]:data) if(type==character){
        res+=info;
    }else if(in_stack.count(info)||(!symbols.count(info))){
        res+=info;
    }else{
        in_stack.emplace(info);
        res+=expand_s(symbols[info]);
        in_stack.erase(info);
    }
    return res;
}
auto check_target(string s,const string target){
    stringstream is(s);
    string arg;
    if(!(is>>arg)) return false;
    return arg==target;
}
auto define_info(string s){
    string cur;
    auto it=s.begin();
    auto cntsp=0;
    while(cntsp<1){
        cntsp+=(*it==' ');
        ++it;
    }
    const auto itx=it;
    while(cntsp<2){
        cntsp+=(*it==' ');
        ++it;
    }
    return make_pair(string(itx,it-1),string(it,s.end()));
}
auto undef_info(string s){
    stringstream is(s);
    string x;is>>x>>x;
    return x;
}
auto readints(stringstream&is,auto&args){
    is>>args;
}
auto readints(stringstream&is,auto&...args){
    (readints(is,args),...);
}
auto readints(auto&...args){
    string s;getline(cin,s);
    stringstream is(s);
    readints(is,args...);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;readints(n);
    cir(i,0,n){
        string line;getline(cin,line);
        if(check_target(line,"#define")){
            const auto[name,str]=define_info(line);
            symbols[name]=str;
            cout<<'\n';
        }else if(check_target(line,"#undef")){
            const auto name=undef_info(line);
            symbols.erase(name);
            cout<<'\n';
        }else{
            cout<<expand_s(line)<<'\n';
        }
    }
    return 0;
}
