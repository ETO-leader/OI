#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;

namespace Registers{
    array<int,4> R;
    array<int,4> E;
    int Flag,Val,Ret,Line;
};

namespace runtimeVars{
    int line;
    stack<pair<int,int>> sAddr;
};

namespace memorySizes{
    constexpr auto operator""_B(unsigned long long num){
        return num;
    }
    constexpr auto operator""_KiB(unsigned long long num){
        return num<<10;
    }
    constexpr auto operator""_MiB(unsigned long long num){
        return num<<20;
    }
}
using namespace memorySizes;

static constexpr auto memorySize=64_MiB;

// Virtual Memory
class virtualMemory{
private:
    array<int,memorySize/4_B> mem;
public:
    void access(size_t,int);
    int&location(size_t);
};

// Split Operations
class fillDefaultArgs{
public:
    static vector<string> defaultArgs(string);
};

class lineProcessor{
public:
    void process(string);
};

// Storage a function
class Function{
private:
    vector<string> operations;
public:
    void callfunc();
};

class controlOperations{
private:
    void UDEF();
    void HLT();
    void NOP();
    void SET(int&,int);
    void JMP(int);
    void JIF(int,int);
    void RET();
    void RET(int);
public:
    void checkType(string);
    void processLine(vector<string>);
};

class calculateOperations{
private:
    void INV(int,int&);
    void ADD(int,int,int&);
    void SUB(int,int,int&);
    void MULT(int,int,int&);
    void IDIV(int,int,int&);
    void MOD(int,int,int&);
    void LSFT(int,int,int&);
    void RSFT(int,int,int&);
    void BAND(int,int,int&);
    void BOR(int,int,int&);
    void BXOR(int,int,int&);
public:
    void checkType(string);
    void processLine(vector<string>);
};

class calculateOperations{
private:
    void LGR(int,int,int&);
    void LLS(int,int,int&);
    void LGE(int,int,int&);
    void LLE(int,int,int&);
    void LEQL(int,int,int&);
    void LAND(int,int,int&);
    void LOR(int,int,int&);
public:
    void checkType(string);
    void processLine(vector<string>);
};

class IO_Operations{
private:
    void RINT(int);
    void RCH(int);
    void WINT(int);
    void WCH(int);
public:
    void checkType(string);
    void processLine(vector<string>);
};

// Let Lines Easier
class Compiler{
private:
    
    string formatter(string);
    void funcJump(string,int);

};


