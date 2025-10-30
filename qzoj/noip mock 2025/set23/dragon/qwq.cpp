#include<iostream>

int main(){
    uint64_t n;
    while(std::cin>>n&&n){
        auto map=new uint64_t[n*n];
        for(uint64_t i=0;i<n;i++){
            for(uint64_t j=0;j<i;j++) std::cin>>map[i*n+j],map[j*n+i]=map[i*n+j];
        }
        uint64_t ans=0;
        uint64_t u0,u1,u2,u3,u4,u5,u6;
        asm volatile(
            "mov %2, %%rdi\n"
            "mov $0, %3\n"
            "mov $0, %0\n"
            "1:\n"
                "mov $0, %4\n"
                "2:\n"
                    "mov $8, %5\n"
                    "imul %1, %5\n"
                    "imul %3, %5\n"
                    "mov $8, %6\n"
                    "imul %4, %6\n"
                    "add %6, %5\n"
                    "mov [%%rdi + %5], %6\n"
                    "mov %6, %9\n"
                    "mov $0, %7\n"
                    "3:\n"
                        "mov $8, %5\n"
                        "imul %1, %5\n"
                        "imul %3, %5\n"
                        "mov $8, %6\n"
                        "imul %7, %6\n"
                        "add %6, %5\n"
                        "mov [%%rdi + %5], %8\n"
                        "mov $8, %5\n"
                        "imul %1, %5\n"
                        "imul %7, %5\n"
                        "mov $8, %6\n"
                        "imul %4, %6\n"
                        "mov [%%rdi + %5], %9\n"
                        "add %9, %8\n"
                        "cmp %6, %8\n"
                        "jne 4f\n"
                        "mov $0, %9\n"
                        "4:\n"
                    
                    "inc %7\n"
                    "cmp %1, %7\n"
                    "jl 3b\n"
                    "add %9, %0\n"    
                "inc %4\n"
                "cmp %2, %4\n"
                "jl 2b\n"
            "inc %3\n"
            "cmp %2, %3\n"
            "jl 1b\n"
            : "=r"(ans)
            : "m"(n), "m"(map), "r"(u0), "r"(u1), "r"(u2), "r"(u3), "r"(u4), "r"(u5), "r"(u6)
            : "rdx", "rdi", "memory"
        );
        std::cout<<ans<<'\n';
    }
}