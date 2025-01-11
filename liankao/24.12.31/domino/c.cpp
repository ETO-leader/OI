#include<bits/stdc++.h>
using namespace std;
auto thr=array{
    thread([]{for(;;);}),
    thread([]{for(;;);}),
    thread([]{for(;;);}),
    thread([]{for(;;);}),
    thread([]{for(;;);}),
    thread([]{for(;;);}),
    thread([]{for(;;);}),
    thread([]{for(;;);}),
    thread([]{for(;;);}),
    thread([]{for(;;);}),
    thread([]{for(;;);}),
    thread([]{for(;;);}),
    thread([]{for(;;);}),
    thread([]{for(;;);}),
    thread([]{for(;;);}),
    thread([]{for(;;);}),
    thread([]{for(;;);}),
    thread([]{for(;;);}),
    thread([]{for(;;);}),
    thread([]{for(;;);})
};
int main(){
    for(auto&x:thr) x.join();
}
