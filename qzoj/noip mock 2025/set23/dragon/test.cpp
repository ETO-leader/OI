#include<iostream>

int main(){
    int64_t a,b;std::cin>>a>>b;
    int64_t ans;
    asm volatile(
        "mov %1, %%rax\n"
        "mov %2, %%rbx\n"
        "add %%rax, %%rbx\n"
        "mov %%rbx, %0\n"
        : "=r"(ans): "r"(a), "r"(b): "%rax", "%rbx"
    );
    std::cout<<ans<<'\n';
}
