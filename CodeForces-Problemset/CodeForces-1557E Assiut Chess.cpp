#include<bits/stdc++.h>

#if not defined(ONLINE_JUDGE)

#include"grader.h"

#else

std::string lasMove;

extern void initPos(int r,int c){
    std::cout<<r<<' '<<c<<'\n';
    std::cout.flush();
    std::cin>>lasMove;
}

extern std::string kingMove(){
    return lasMove;
}

extern void queenMove(int r,int c){
    std::cout<<r<<' '<<c<<'\n';
    std::cout.flush();
    std::cin>>lasMove;
}

extern void playChess();

int main(){
    std::ios::sync_with_stdio(false),std::cin.tie(0);
    int T;std::cin>>T;
    while(T--) playChess();
    return 0;
}

#endif

#define cir(i,a,b) for(int i=a;i<b;++i)

class Machine{
private:
    int pos;
    static constexpr auto csiz=8;
    auto checkLine(int lineid){
        for(pos=(pos==1?2:1)-1;pos<csiz;){
            queenMove(lineid,++pos);
            if(kingMove()=="Done") return true;
            if(kingMove()[0]=='D') return false;
            if(kingMove()[0]=='U') return checkLine(lineid);
        }
        return false;
    }
public:
    auto play(){
        cir(i,1,csiz+1){
            if(i>1) queenMove(i,pos);
            if(kingMove()=="Done") return true;
            if(checkLine(i)) return true;
        }
        return false;
    }
    Machine():pos(1){}
};

extern void playChess(){
    initPos(1,1);
    assert(Machine().play());
}

#undef cir
