#include<stdint.h>
#include<iostream>

int main() {
    uint64_t a[10];
    for(int i=0;i<10;i++) std::cin>>a[i];
    uint64_t h;
    std::cin>>h;
    uint64_t ans=0;
    const uint64_t n=10;
    asm volatile(
        "xor %%rax, %%rax\n"
        "xor %%rcx, %%rcx\n"
        "mov %1, %%rdi\n"
        "add $30, %2\n"
        "1:\n"
        "mov %2, %%rbx\n"
        "mov (%%rdi), %%rbx\n"
        "cmp %2, %%rbx\n"
        "jg 2f\n"
        "inc %%rax\n"
        "2:\n"
        "inc %%rcx\n"
        "add $8, %%rdi\n"
        "cmp %3, %%rcx\n"
        "jl 1b\n"
        "mov %%rax, %0\n"
        : "=r"(ans)
        : "r"(a), "r"(h), "r"(n)
        : "%rax", "%rbx", "%rcx", "%rdi", "%memory"
    );
    std::cout<<ans<<'\n';
}
