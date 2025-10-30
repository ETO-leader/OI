#include<string.h>
#include<stdint.h>
#include<iostream>

int main(){
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int T;std::cin>>T;
    while(T--) []{
        uint64_t x,y;std::cin>>x>>y;--x;--y;
        std::string s;std::cin>>s;
        auto ans=new int[32*32];
        auto pos=ans;
        memset(ans,0,sizeof(int)*32*32);
        asm volatile(
            "mov $0, %%rax\n"
            "mov %0, %%rbx\n"
            "1:\n"
                "cmp $69, %4\n"
                "jne 11f\n"
                    "sub $1, %3\n"
                    "jmp 15f\n"
                "11:\n"

                "cmp $87, %4\n"
                "jne 12f\n"
                    "add $1, %3\n"
                    "jmp 15f\n"
                "12:\n"
                
                "cmp $78, %4\n"
                "jne 13f\n"
                    "sub $1, %2\n"
                    "sub $128, %%rbx\n"
                    "jmp 15f\n"
                "13:\n"

                "cmp $83, %4\n"
                "jne 14f\n"
                    "add $1, %2\n"
                    "add $128, %%rbx\n"
                    "jmp 15f\n"
                "14:\n"

                "15:\n"

                "cmp $32, %3\n"
                "jge 151f\n"
                    "cmp $0, %3\n"
                    "jl 151f\n"
                        "cmp $32, %4\n"
                        "jge 151f\n"
                            "cmp $0, %4\n"
                            "jl 151f\n"
                                "add $1, (%%rbx, %3, 4)\n"
                "151:\n"
                "add $1, %4\n"
                "add $1, %%rax\n"
                "cmp %1, %%rax\n"
                "jl 1b\n"
            : "+r"(ans)
            : "+r"(s.size()), "+r"(x), "+r"(y), "+r"(s.data())
            : "rax", "rbx", "memory", "rdi"
        );
        for(auto i=0;i<32;++i){
            for(auto j=0;j<32;++j){
                if(pos[i*32+j]) std::cout<<pos[i*32+j]<<' ';
                else std::cout<<'.';
            }
            std::cout<<'\n';
        }
        delete[] pos;
    }();
}
