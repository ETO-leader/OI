#include <iostream>
#include <cstdint>

int main() {
    int64_t arr[] = {1, 2, 3, 4, 5};
    int64_t n = sizeof(arr) / sizeof(arr[0]);
    int64_t sum = 0;

    asm volatile (
        "xor %%rax, %%rax\n\t"        // sum = 0
        "mov %1, %%rcx\n\t"           // rcx = n
        "mov %2, %%rsi\n\t"           // rsi = arr (指针)
        "1:\n\t"
        "add (%%rsi), %%rax\n\t"      // sum += *rsi
        "add $8, %%rsi\n\t"           // rsi += 8 (int64_t 占 8 字节)
        "loop 1b\n\t"                 // rcx--, 若非0跳回 1
        "mov %%rax, %0\n\t"           // sum -> 输出变量
        : "=r"(sum)                   // 输出
        : "r"(n), "r"(arr)            // 输入
        : "%rax", "%rcx", "%rsi", "memory"  // 被修改的寄存器
    );

    std::cout << "Sum = " << sum << '\n';
}
