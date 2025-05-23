#include"game.h"
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;

int _n;

vector<pair<int,int>> init(vector<pair<int,int>> qwq,int n,int m,int k,int q,int qlim){
    return vector{
        pair(0,1),
        pair(1,2),
        pair(2,3),
        pair(3,0),
        pair(0,4),
        pair(5,6),
        pair(5,7),
        pair(5,8),
        pair(5,9),
        pair(6,7),
        pair(6,8),
        pair(6,9),
        pair(7,8),
        pair(7,9),
        pair(8,9)
    };
}

int ask(){
    cerr<<"!!\n";
    cerr<<"\\emptySet: "<<play({})<<'\n';
    cir(i,0,10) cerr<<play({i})<<' ';
    cerr<<'\n';
    return 1;
}

