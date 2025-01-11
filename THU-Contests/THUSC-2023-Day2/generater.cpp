#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;

auto pArgs(auto x){
    return format("{}",x);
}
auto pArgs(auto x,auto...args){
    return format("{},",x)+pArgs(args...);
}

auto pStr(auto str){
    auto res=string();
    for(auto&i:str) res+=format("{},",i);
    res.pop_back();
    return res;
}

// Basic Operations
auto AND(auto...args){
    return format("{}({})",__FUNCTION__,pArgs(args...));
}
auto OR(auto...args){
    return format("{}({})",__FUNCTION__,pArgs(args...));
}
auto XOR(auto...args){
    return format("{}({})",__FUNCTION__,pArgs(args...));
}
auto NAND(auto...args){
    return format("{}({})",__FUNCTION__,pArgs(args...));
}
auto NOR(auto...args){
    return format("{}({})",__FUNCTION__,pArgs(args...));
}
auto NXOR(auto...args){
    return format("{}({})",__FUNCTION__,pArgs(args...));
}
auto NOT(auto args){
    return format("{}({})",__FUNCTION__,pArgs(args));
}
template<typename _Ty>
auto AND(vector<_Ty> args){
    return format("{}({})",__FUNCTION__,pStr(args));
}
template<typename _Ty>
auto OR(vector<_Ty> args){
    return format("{}({})",__FUNCTION__,pStr(args));
}
template<typename _Ty>
auto XOR(vector<_Ty> args){
    return format("{}({})",__FUNCTION__,pStr(args));
}
template<typename _Ty>
auto NAND(vector<_Ty> args){
    return format("{}({})",__FUNCTION__,pStr(args));
}
template<typename _Ty>
auto NOR(vector<_Ty> args){
    return format("{}({})",__FUNCTION__,pStr(args));
}
template<typename _Ty>
auto NXOR(vector<_Ty> args){
    return format("{}({})",__FUNCTION__,pStr(args));
}
auto COMMAND(auto reg,auto str){
    cout<<format("{}={};",reg,str)<<'\n';
}

// Tools
template<const int N>
auto Iota(const int S){
    array<int,N> res;
    iota(res.begin(),res.end(),S);
    return res;
}

// Additonal Operations
auto VOTER(auto OUT,auto A,auto B,auto C){
    COMMAND(OUT,OR(AND(A,B),AND(B,C),AND(A,C)));
}
template<const int INC,typename _Ty>
auto DECODER(array<_Ty,(1<<INC)> B,auto E,array<_Ty,INC> A,int&TMP){
    cir(i,0,(1<<INC)){
        vector<_Ty> ok,nok;
        cir(x,0,INC) ((i&(1<<x))?ok:nok).emplace_back(A[x]);
        if((!ok.empty())&&(!nok.empty())){
            COMMAND(++TMP,AND(ok));
            COMMAND(++TMP,NOR(nok));
            COMMAND(B[i],AND(TMP-1,TMP,E));
        }else if(!ok.empty()){
            COMMAND(++TMP,AND(ok));
            COMMAND(B[i],AND(TMP,E));
        }else{
            COMMAND(++TMP,NOR(nok));
            COMMAND(B[i],AND(TMP,E));
        }
    }
}
template<const int INC,typename _Ty>
auto SELECTOR(int R,auto E,array<_Ty,INC> A,array<_Ty,(1<<INC)> D,int&TMP){
    auto S=Iota<(1<<INC)>(TMP);
    TMP=S.back()+1;
    DECODER<INC>(S,E,A,TMP);
    vector<int> pos;
    cir(i,0,(1<<INC)){
        COMMAND(++TMP,AND(S[i],D[i]));
        pos.emplace_back(TMP);
    }
    COMMAND(R,OR(pos));
}

auto Task1(){
    VOTER(4,1,2,3);
}
auto Task2(){
    auto TMP=50000;
    DECODER<5>(Iota<32>(7),1,Iota<5>(2),TMP);
}
auto Task3(){
    auto TMP=50000;
    SELECTOR<5>(39,1,Iota<5>(2),Iota<32>(7),TMP);
}

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    // Task1();
    // Task2();
    Task3();
    return 0;
}
