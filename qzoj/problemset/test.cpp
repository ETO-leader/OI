#include<iostream>

int main(){
    int v;std::cin>>v;
    auto f=new uint64_t[v+1];
    int n;std::cin>>n;
    auto a=new int64_t[n];
    for(auto i=0;i<n;i++) cin>>a[i];
    uint64_t ans=0;
    asm volatile(
        "mov $1, [%1]\n"
        "mov %3, %%rdi\n"
        "1:\n"
            "mov %2, %%rax\n"
            "2:\n"
                "mov %1, %%r11\n"
                "add "
                "or []"

        : "=r"(ans)
        : "r"(f), "m"(n), "m"(a)
        : "rax", "rbx", "r11", "r12", "rdi", "memory"
    );
}
