asm(R"(        .set    __gnu_cxx::__ops::_Iter_less_val::_Iter_less_val(__gnu_cxx::__ops::_Iter_less_iter) [complete object constructor],_ZN9__gnu_cxx5__ops14_Iter_less_valC2ENS0_15_Iter_less_iterE
inf:
        .zero   520
ouf:
        .zero   512
        .set    std::_Vector_base<long long, std::allocator<long long>>::_Vector_impl::~_Vector_impl() [complete object destructor],_ZNSt12_Vector_baseIxSaIxEE12_Vector_implD2Ev
        .set    std::_Vector_base<long long, std::allocator<long long>>::_Vector_base() [complete object constructor],_ZNSt12_Vector_baseIxSaIxEEC2Ev
        .set    std::vector<long long, std::allocator<long long>>::vector() [complete object constructor],_ZNSt6vectorIxSaIxEEC2Ev
mathbase::mathbase() [base object constructor]:
        push    rbp
        mov     rbp, rsp
        sub     rsp, 16
        mov     QWORD PTR [rbp-8], rdi
        mov     rax, QWORD PTR [rbp-8]
        mov     rdi, rax
        call    std::vector<long long, std::allocator<long long>>::vector() [complete object constructor]
        mov     rax, QWORD PTR [rbp-8]
        add     rax, 24
        mov     rdi, rax
        call    std::vector<long long, std::allocator<long long>>::vector() [complete object constructor]
        nop
        leave
        ret
        .set    mathbase::mathbase() [complete object constructor],mathbase::mathbase() [base object constructor]
math:
        .zero   48
auto mathbase::qpow<int>(long long, int) const:
        push    rbp
        mov     rbp, rsp
        mov     QWORD PTR [rbp-24], rdi
        mov     QWORD PTR [rbp-32], rsi
        mov     DWORD PTR [rbp-36], edx
        mov     QWORD PTR [rbp-8], 1
        jmp     .L19
.L21:
        mov     eax, DWORD PTR [rbp-36]
        and     eax, 1
        test    eax, eax
        je      .L20
        mov     rdx, QWORD PTR [rbp-8]
        mov     rax, QWORD PTR [rbp-32]
        imul    rax, rdx
        mov     QWORD PTR [rbp-8], rax
        lea     rsi, [rbp-8]
        mov     rcx, QWORD PTR [rsi]
        movabs  rdx, 155014655926305585
        mov     rax, rcx
        imul    rdx
        mov     rax, rdx
        sar     rax, 23
        mov     rdx, rcx
        sar     rdx, 63
        sub     rax, rdx
        imul    rdx, rax, 998244353
        mov     rax, rcx
        sub     rax, rdx
        mov     QWORD PTR [rsi], rax
.L20:
        mov     rdx, QWORD PTR [rbp-32]
        mov     rax, QWORD PTR [rbp-32]
        imul    rax, rdx
        mov     QWORD PTR [rbp-32], rax
        lea     rsi, [rbp-32]
        mov     rcx, QWORD PTR [rsi]
        movabs  rdx, 155014655926305585
        mov     rax, rcx
        imul    rdx
        mov     rax, rdx
        sar     rax, 23
        mov     rdx, rcx
        sar     rdx, 63
        sub     rax, rdx
        imul    rdx, rax, 998244353
        mov     rax, rcx
        sub     rax, rdx
        mov     QWORD PTR [rsi], rax
        sar     DWORD PTR [rbp-36]
.L19:
        cmp     DWORD PTR [rbp-36], 0
        jne     .L21
        mov     rax, QWORD PTR [rbp-8]
        pop     rbp
        ret
auto mathbase::inv<long long>(long long) const:
        push    rbp
        mov     rbp, rsp
        sub     rsp, 16
        mov     QWORD PTR [rbp-8], rdi
        mov     QWORD PTR [rbp-16], rsi
        mov     rcx, QWORD PTR [rbp-16]
        mov     rax, QWORD PTR [rbp-8]
        mov     edx, 998244351
        mov     rsi, rcx
        mov     rdi, rax
        call    auto mathbase::qpow<int>(long long, int) const
        leave
        ret
auto mathbase::init<int>(int):
        push    rbp
        mov     rbp, rsp
        push    rbx
        sub     rsp, 40
        mov     QWORD PTR [rbp-40], rdi
        mov     DWORD PTR [rbp-44], esi
        mov     rax, QWORD PTR [rbp-40]
        mov     QWORD PTR [rbp-32], 1
        mov     edx, DWORD PTR [rbp-44]
        movsx   rcx, edx
        lea     rdx, [rbp-32]
        mov     rsi, rcx
        mov     rdi, rax
        call    std::vector<long long, std::allocator<long long>>::resize(unsigned long, long long const&)
        mov     DWORD PTR [rbp-20], 1
        jmp     .L26
.L27:
        mov     rax, QWORD PTR [rbp-40]
        mov     edx, DWORD PTR [rbp-20]
        sub     edx, 1
        movsx   rdx, edx
        mov     rsi, rdx
        mov     rdi, rax
        call    std::vector<long long, std::allocator<long long>>::operator[](unsigned long)
        mov     rdx, QWORD PTR [rax]
        mov     eax, DWORD PTR [rbp-20]
        cdqe
        mov     rcx, rdx
        imul    rcx, rax
        movabs  rdx, 155014655926305585
        mov     rax, rcx
        imul    rdx
        sar     rdx, 23
        mov     rax, rcx
        sar     rax, 63
        mov     rbx, rdx
        sub     rbx, rax
        imul    rax, rbx, 998244353
        sub     rcx, rax
        mov     rbx, rcx
        mov     rax, QWORD PTR [rbp-40]
        mov     edx, DWORD PTR [rbp-20]
        movsx   rdx, edx
        mov     rsi, rdx
        mov     rdi, rax
        call    std::vector<long long, std::allocator<long long>>::operator[](unsigned long)
        mov     QWORD PTR [rax], rbx
        add     DWORD PTR [rbp-20], 1
.L26:
        mov     eax, DWORD PTR [rbp-20]
        cmp     eax, DWORD PTR [rbp-44]
        jl      .L27
        mov     rax, QWORD PTR [rbp-40]
        mov     rdx, QWORD PTR [rbp-40]
        add     rdx, 24
        mov     rsi, rax
        mov     rdi, rdx
        call    std::vector<long long, std::allocator<long long>>::operator=(std::vector<long long, std::allocator<long long>> const&)
        mov     rax, QWORD PTR [rbp-40]
        mov     edx, DWORD PTR [rbp-44]
        sub     edx, 1
        movsx   rdx, edx
        mov     rsi, rdx
        mov     rdi, rax
        call    std::vector<long long, std::allocator<long long>>::operator[](unsigned long)
        mov     rdx, QWORD PTR [rax]
        mov     rax, QWORD PTR [rbp-40]
        mov     rsi, rdx
        mov     rdi, rax
        call    auto mathbase::inv<long long>(long long) const
        mov     rbx, rax
        mov     rax, QWORD PTR [rbp-40]
        lea     rdx, [rax+24]
        mov     eax, DWORD PTR [rbp-44]
        sub     eax, 1
        cdqe
        mov     rsi, rax
        mov     rdi, rdx
        call    std::vector<long long, std::allocator<long long>>::operator[](unsigned long)
        mov     QWORD PTR [rax], rbx
        mov     eax, DWORD PTR [rbp-44]
        sub     eax, 2
        mov     DWORD PTR [rbp-24], eax
        jmp     .L28
.L29:
        mov     rax, QWORD PTR [rbp-40]
        lea     rdx, [rax+24]
        mov     eax, DWORD PTR [rbp-24]
        add     eax, 1
        cdqe
        mov     rsi, rax
        mov     rdi, rdx
        call    std::vector<long long, std::allocator<long long>>::operator[](unsigned long)
        mov     rdx, QWORD PTR [rax]
        mov     eax, DWORD PTR [rbp-24]
        add     eax, 1
        cdqe
        mov     rcx, rdx
        imul    rcx, rax
        movabs  rdx, 155014655926305585
        mov     rax, rcx
        imul    rdx
        sar     rdx, 23
        mov     rax, rcx
        sar     rax, 63
        mov     rbx, rdx
        sub     rbx, rax
        imul    rax, rbx, 998244353
        mov     rbx, rcx
        sub     rbx, rax
        mov     rax, QWORD PTR [rbp-40]
        lea     rdx, [rax+24]
        mov     eax, DWORD PTR [rbp-24]
        cdqe
        mov     rsi, rax
        mov     rdi, rdx
        call    std::vector<long long, std::allocator<long long>>::operator[](unsigned long)
        mov     QWORD PTR [rax], rbx
        sub     DWORD PTR [rbp-24], 1
.L28:
        cmp     DWORD PTR [rbp-24], -1
        jne     .L29
        nop
        nop
        mov     rbx, QWORD PTR [rbp-8]
        leave
        ret
auto mathbase::C<int, int>(int, int) const:
        push    rbp
        mov     rbp, rsp
        push    rbx
        sub     rsp, 24
        mov     QWORD PTR [rbp-24], rdi
        mov     DWORD PTR [rbp-28], esi
        mov     DWORD PTR [rbp-32], edx
        mov     eax, DWORD PTR [rbp-32]
        cmp     eax, DWORD PTR [rbp-28]
        jle     .L39
        cmp     DWORD PTR [rbp-32], 0
        jns     .L40
.L39:
        mov     rax, QWORD PTR [rbp-24]
        mov     edx, DWORD PTR [rbp-28]
        movsx   rdx, edx
        mov     rsi, rdx
        mov     rdi, rax
        call    std::vector<long long, std::allocator<long long>>::operator[](unsigned long) const
        mov     rbx, QWORD PTR [rax]
        mov     rax, QWORD PTR [rbp-24]
        lea     rdx, [rax+24]
        mov     eax, DWORD PTR [rbp-32]
        cdqe
        mov     rsi, rax
        mov     rdi, rdx
        call    std::vector<long long, std::allocator<long long>>::operator[](unsigned long) const
        mov     rax, QWORD PTR [rax]
        imul    rbx, rax
        mov     rcx, rbx
        movabs  rdx, 155014655926305585
        mov     rax, rcx
        imul    rdx
        sar     rdx, 23
        mov     rax, rcx
        sar     rax, 63
        mov     rbx, rdx
        sub     rbx, rax
        imul    rax, rbx, 998244353
        sub     rcx, rax
        mov     rbx, rcx
        mov     rax, QWORD PTR [rbp-24]
        lea     rdx, [rax+24]
        mov     eax, DWORD PTR [rbp-28]
        sub     eax, DWORD PTR [rbp-32]
        cdqe
        mov     rsi, rax
        mov     rdi, rdx
        call    std::vector<long long, std::allocator<long long>>::operator[](unsigned long) const
        mov     rax, QWORD PTR [rax]
        mov     rcx, rbx
        imul    rcx, rax
        movabs  rdx, 155014655926305585
        mov     rax, rcx
        imul    rdx
        mov     rax, rdx
        sar     rax, 23
        mov     rdx, rcx
        sar     rdx, 63
        sub     rax, rdx
        imul    rdx, rax, 998244353
        mov     rax, rcx
        sub     rax, rdx
        jmp     .L42
.L40:
        mov     eax, 0
.L42:
        mov     rbx, QWORD PTR [rbp-8]
        leave
        ret
        .set    std::_Vector_base<std::vector<long long, std::allocator<long long>>, std::allocator<std::vector<long long, std::allocator<long long>>>>::_Vector_impl::~_Vector_impl() [complete object destructor],_ZNSt12_Vector_baseISt6vectorIxSaIxEESaIS2_EE12_Vector_implD2Ev
        .set    std::_Vector_base<std::vector<long long, std::allocator<long long>>, std::allocator<std::vector<long long, std::allocator<long long>>>>::_Vector_base() [complete object constructor],_ZNSt12_Vector_baseISt6vectorIxSaIxEESaIS2_EEC2Ev
        .set    std::vector<std::vector<long long, std::allocator<long long>>, std::allocator<std::vector<long long, std::allocator<long long>>>>::vector() [complete object constructor],_ZNSt6vectorIS_IxSaIxEESaIS1_EEC2Ev
main:
        push    rbp
        mov     rbp, rsp
        push    r12
        push    rbx
        sub     rsp, 720
        mov     edi, 0
        call    std::ios_base::sync_with_stdio(bool)
        mov     esi, 0
        mov     edi, OFFSET FLAT:inf+256
        call    std::basic_ios<char, std::char_traits<char>>::tie(std::ostream*)
        lea     rax, [rbp-436]
        mov     rsi, rax
        mov     edi, OFFSET FLAT:inf
        call    std::istream::operator>>(int&)
        lea     rax, [rbp-440]
        mov     rsi, rax
        mov     edi, OFFSET FLAT:inf
        call    std::istream::operator>>(int&)
        mov     rdx, rax
        lea     rax, [rbp-444]
        mov     rsi, rax
        mov     rdi, rdx
        call    std::istream::operator>>(int&)
        mov     rdx, rax
        lea     rax, [rbp-448]
        mov     rsi, rax
        mov     rdi, rdx
        call    std::istream::operator>>(int&)
        mov     edx, DWORD PTR [rbp-440]
        mov     eax, DWORD PTR [rbp-444]
        add     eax, edx
        add     eax, 7
        mov     esi, eax
        mov     edi, OFFSET FLAT:math
        call    auto mathbase::init<int>(int)
        lea     rax, [rbp-429]
        mov     QWORD PTR [rbp-208], rax
        nop
        nop
        mov     eax, DWORD PTR [rbp-448]
        movsx   rcx, eax
        lea     rdx, [rbp-429]
        lea     rax, [rbp-480]
        mov     rsi, rcx
        mov     rdi, rax
        call    std::vector<std::pair<int, int>, std::allocator<std::pair<int, int>>>::vector(unsigned long, std::allocator<std::pair<int, int>> const&) [complete object constructor]
        lea     rax, [rbp-429]
        mov     rdi, rax
        call    std::__new_allocator<std::pair<int, int>>::~__new_allocator() [base object destructor]
        nop
        lea     rax, [rbp-480]
        mov     QWORD PTR [rbp-64], rax
        mov     rax, QWORD PTR [rbp-64]
        mov     rdi, rax
        call    std::vector<std::pair<int, int>, std::allocator<std::pair<int, int>>>::begin()
        mov     QWORD PTR [rbp-488], rax
        mov     rax, QWORD PTR [rbp-64]
        mov     rdi, rax
        call    std::vector<std::pair<int, int>, std::allocator<std::pair<int, int>>>::end()
        mov     QWORD PTR [rbp-496], rax
        jmp     .L47
.L53:
        mov     rax, QWORD PTR [rbp-488]
        mov     QWORD PTR [rbp-184], rax
        mov     rax, QWORD PTR [rbp-184]
        mov     rdi, rax
        call    std::tuple_element<0ul, std::pair<int, int>>::type& std::get<0ul, int, int>(std::pair<int, int>&)
        mov     QWORD PTR [rbp-192], rax
        mov     rax, QWORD PTR [rbp-184]
        mov     rdi, rax
        call    std::tuple_element<1ul, std::pair<int, int>>::type& std::get<1ul, int, int>(std::pair<int, int>&)
        mov     QWORD PTR [rbp-200], rax
        mov     rax, QWORD PTR [rbp-192]
        mov     rsi, rax
        mov     edi, OFFSET FLAT:inf
        call    std::istream::operator>>(int&)
        mov     rdx, rax
        mov     rax, QWORD PTR [rbp-200]
        mov     rsi, rax
        mov     rdi, rdx
        call    std::istream::operator>>(int&)
        mov     rax, QWORD PTR [rbp-488]
        add     rax, 8
        mov     QWORD PTR [rbp-488], rax
        nop
.L47:
        lea     rax, [rbp-488]
        mov     QWORD PTR [rbp-216], rax
        mov     rax, QWORD PTR [rbp-216]
        mov     rdx, QWORD PTR [rax]
        lea     rax, [rbp-496]
        mov     QWORD PTR [rbp-224], rax
        mov     rax, QWORD PTR [rbp-224]
        mov     rax, QWORD PTR [rax]
        cmp     rdx, rax
        setne   al
        test    al, al
        jne     .L53
        mov     DWORD PTR [rbp-428], 1
        mov     DWORD PTR [rbp-424], 1
        lea     rdx, [rbp-428]
        lea     rcx, [rbp-424]
        lea     rax, [rbp-480]
        mov     rsi, rcx
        mov     rdi, rax
        call    std::pair<int, int>& std::vector<std::pair<int, int>, std::allocator<std::pair<int, int>>>::emplace_back<int, int>(int&&, int&&)
        lea     rdx, [rbp-444]
        lea     rcx, [rbp-440]
        lea     rax, [rbp-480]
        mov     rsi, rcx
        mov     rdi, rax
        call    std::pair<int, int>& std::vector<std::pair<int, int>, std::allocator<std::pair<int, int>>>::emplace_back<int&, int&>(int&, int&)
        lea     rax, [rbp-480]
        mov     rdi, rax
        call    std::vector<std::pair<int, int>, std::allocator<std::pair<int, int>>>::end()
        mov     rbx, rax
        lea     rax, [rbp-480]
        mov     rdi, rax
        call    std::vector<std::pair<int, int>, std::allocator<std::pair<int, int>>>::begin()
        mov     rsi, rbx
        mov     rdi, rax
        call    void std::sort<__gnu_cxx::__normal_iterator<std::pair<int, int>*, std::vector<std::pair<int, int>, std::allocator<std::pair<int, int>>>>>(__gnu_cxx::__normal_iterator<std::pair<int, int>*, std::vector<std::pair<int, int>, std::allocator<std::pair<int, int>>>>, __gnu_cxx::__normal_iterator<std::pair<int, int>*, std::vector<std::pair<int, int>, std::allocator<std::pair<int, int>>>>)
        lea     rax, [rbp-480]
        mov     QWORD PTR [rbp-72], rax
        mov     rax, QWORD PTR [rbp-72]
        mov     rdi, rax
        call    std::vector<std::pair<int, int>, std::allocator<std::pair<int, int>>>::begin()
        mov     QWORD PTR [rbp-504], rax
        mov     rax, QWORD PTR [rbp-72]
        mov     rdi, rax
        call    std::vector<std::pair<int, int>, std::allocator<std::pair<int, int>>>::end()
        mov     QWORD PTR [rbp-512], rax
        jmp     .L54
.L60:
        mov     rax, QWORD PTR [rbp-504]
        mov     QWORD PTR [rbp-160], rax
        mov     rax, QWORD PTR [rbp-160]
        mov     rdi, rax
        call    std::tuple_element<0ul, std::pair<int, int>>::type& std::get<0ul, int, int>(std::pair<int, int>&)
        mov     QWORD PTR [rbp-168], rax
        mov     rax, QWORD PTR [rbp-160]
        mov     rdi, rax
        call    std::tuple_element<1ul, std::pair<int, int>>::type& std::get<1ul, int, int>(std::pair<int, int>&)
        mov     QWORD PTR [rbp-176], rax
        mov     rax, QWORD PTR [rbp-168]
        mov     eax, DWORD PTR [rax]
        lea     edx, [rax-1]
        mov     rax, QWORD PTR [rbp-168]
        mov     DWORD PTR [rax], edx
        mov     rax, QWORD PTR [rbp-176]
        mov     eax, DWORD PTR [rax]
        lea     edx, [rax-1]
        mov     rax, QWORD PTR [rbp-176]
        mov     DWORD PTR [rax], edx
        mov     rax, QWORD PTR [rbp-504]
        add     rax, 8
        mov     QWORD PTR [rbp-504], rax
        nop
.L54:
        lea     rax, [rbp-504]
        mov     QWORD PTR [rbp-232], rax
        mov     rax, QWORD PTR [rbp-232]
        mov     rdx, QWORD PTR [rax]
        lea     rax, [rbp-512]
        mov     QWORD PTR [rbp-240], rax
        mov     rax, QWORD PTR [rbp-240]
        mov     rax, QWORD PTR [rax]
        cmp     rdx, rax
        setne   al
        test    al, al
        jne     .L60
        mov     eax, DWORD PTR [rbp-436]
        and     eax, 1
        test    eax, eax
        je      .L61
        lea     rax, [rbp-417]
        mov     QWORD PTR [rbp-256], rax
        nop
        nop
        lea     rax, [rbp-387]
        mov     QWORD PTR [rbp-248], rax
        nop
        nop
        mov     eax, DWORD PTR [rbp-448]
        add     eax, 2
        movsx   rcx, eax
        lea     rdx, [rbp-387]
        lea     rax, [rbp-416]
        mov     rsi, rcx
        mov     rdi, rax
        call    std::vector<long long, std::allocator<long long>>::vector(unsigned long, std::allocator<long long> const&) [complete object constructor]
        mov     eax, DWORD PTR [rbp-448]
        add     eax, 2
        movsx   rsi, eax
        lea     rcx, [rbp-417]
        lea     rdx, [rbp-416]
        lea     rax, [rbp-544]
        mov     rdi, rax
        call    std::vector<std::vector<long long, std::allocator<long long>>, std::allocator<std::vector<long long, std::allocator<long long>>>>::vector(unsigned long, std::vector<long long, std::allocator<long long>> const&, std::allocator<std::vector<long long, std::allocator<long long>>> const&) [complete object constructor]
        lea     rax, [rbp-416]
        mov     rdi, rax
        call    std::vector<long long, std::allocator<long long>>::~vector() [complete object destructor]
        lea     rax, [rbp-387]
        mov     rdi, rax
        call    std::__new_allocator<long long>::~__new_allocator() [base object destructor]
        nop
        lea     rax, [rbp-417]
        mov     rdi, rax
        call    std::__new_allocator<std::vector<long long, std::allocator<long long>>>::~__new_allocator() [base object destructor]
        nop
        lea     rax, [rbp-544]
        mov     esi, 0
        mov     rdi, rax
        call    std::vector<std::vector<long long, std::allocator<long long>>, std::allocator<std::vector<long long, std::allocator<long long>>>>::operator[](unsigned long)
        mov     esi, 0
        mov     rdi, rax
        call    std::vector<long long, std::allocator<long long>>::operator[](unsigned long)
        mov     QWORD PTR [rax], 1
        mov     DWORD PTR [rbp-20], 0
        jmp     .L62
.L65:
        mov     DWORD PTR [rbp-24], 0
        jmp     .L63
.L64:
        mov     eax, DWORD PTR [rbp-20]
        add     eax, 1
        movsx   rdx, eax
        lea     rax, [rbp-480]
        mov     rsi, rdx
        mov     rdi, rax
        call    std::vector<std::pair<int, int>, std::allocator<std::pair<int, int>>>::operator[](unsigned long)
        mov     ebx, DWORD PTR [rax]
        mov     eax, DWORD PTR [rbp-20]
        movsx   rdx, eax
        lea     rax, [rbp-480]
        mov     rsi, rdx
        mov     rdi, rax
        call    std::vector<std::pair<int, int>, std::allocator<std::pair<int, int>>>::operator[](unsigned long)
        mov     eax, DWORD PTR [rax]
        sub     ebx, eax
        mov     eax, DWORD PTR [rbp-20]
        add     eax, 1
        movsx   rdx, eax
        lea     rax, [rbp-480]
        mov     rsi, rdx
        mov     rdi, rax
        call    std::vector<std::pair<int, int>, std::allocator<std::pair<int, int>>>::operator[](unsigned long)
        mov     r12d, DWORD PTR [rax]
        mov     eax, DWORD PTR [rbp-20]
        movsx   rdx, eax
        lea     rax, [rbp-480]
        mov     rsi, rdx
        mov     rdi, rax
        call    std::vector<std::pair<int, int>, std::allocator<std::pair<int, int>>>::operator[](unsigned long)
        mov     eax, DWORD PTR [rax]
        sub     r12d, eax
        mov     eax, DWORD PTR [rbp-20]
        add     eax, 1
        movsx   rdx, eax
        lea     rax, [rbp-480]
        mov     rsi, rdx
        mov     rdi, rax
        call    std::vector<std::pair<int, int>, std::allocator<std::pair<int, int>>>::operator[](unsigned long)
        mov     eax, DWORD PTR [rax+4]
        add     r12d, eax
        mov     eax, DWORD PTR [rbp-20]
        movsx   rdx, eax
        lea     rax, [rbp-480]
        mov     rsi, rdx
        mov     rdi, rax
        call    std::vector<std::pair<int, int>, std::allocator<std::pair<int, int>>>::operator[](unsigned long)
        mov     edx, DWORD PTR [rax+4]
        mov     eax, r12d
        sub     eax, edx
        mov     edx, ebx
        mov     esi, eax
        mov     edi, OFFSET FLAT:math
        call    auto mathbase::C<int, int>(int, int) const
        mov     QWORD PTR [rbp-80], rax
        mov     eax, DWORD PTR [rbp-20]
        add     eax, 1
        movsx   rdx, eax
        lea     rax, [rbp-480]
        mov     rsi, rdx
        mov     rdi, rax
        call    std::vector<std::pair<int, int>, std::allocator<std::pair<int, int>>>::operator[](unsigned long)
        mov     ebx, DWORD PTR [rax]
        mov     eax, DWORD PTR [rbp-24]
        movsx   rdx, eax
        lea     rax, [rbp-480]
        mov     rsi, rdx
        mov     rdi, rax
        call    std::vector<std::pair<int, int>, std::allocator<std::pair<int, int>>>::operator[](unsigned long)
        mov     eax, DWORD PTR [rax]
        sub     ebx, eax
        mov     eax, DWORD PTR [rbp-20]
        add     eax, 1
        movsx   rdx, eax
        lea     rax, [rbp-480]
        mov     rsi, rdx
        mov     rdi, rax
        call    std::vector<std::pair<int, int>, std::allocator<std::pair<int, int>>>::operator[](unsigned long)
        mov     r12d, DWORD PTR [rax]
        mov     eax, DWORD PTR [rbp-24]
        movsx   rdx, eax
        lea     rax, [rbp-480]
        mov     rsi, rdx
        mov     rdi, rax
        call    std::vector<std::pair<int, int>, std::allocator<std::pair<int, int>>>::operator[](unsigned long)
        mov     eax, DWORD PTR [rax]
        sub     r12d, eax
        mov     eax, DWORD PTR [rbp-20]
        add     eax, 1
        movsx   rdx, eax
        lea     rax, [rbp-480]
        mov     rsi, rdx
        mov     rdi, rax
        call    std::vector<std::pair<int, int>, std::allocator<std::pair<int, int>>>::operator[](unsigned long)
        mov     eax, DWORD PTR [rax+4]
        add     r12d, eax
        mov     eax, DWORD PTR [rbp-24]
        movsx   rdx, eax
        lea     rax, [rbp-480]
        mov     rsi, rdx
        mov     rdi, rax
        call    std::vector<std::pair<int, int>, std::allocator<std::pair<int, int>>>::operator[](unsigned long)
        mov     edx, DWORD PTR [rax+4]
        mov     eax, r12d
        sub     eax, edx
        mov     edx, ebx
        mov     esi, eax
        mov     edi, OFFSET FLAT:math
        call    auto mathbase::C<int, int>(int, int) const
        mov     QWORD PTR [rbp-88], rax
        mov     eax, DWORD PTR [rbp-20]
        movsx   rdx, eax
        lea     rax, [rbp-544]
        mov     rsi, rdx
        mov     rdi, rax
        call    std::vector<std::vector<long long, std::allocator<long long>>, std::allocator<std::vector<long long, std::allocator<long long>>>>::operator[](unsigned long)
        mov     rdx, rax
        mov     eax, DWORD PTR [rbp-24]
        cdqe
        mov     rsi, rax
        mov     rdi, rdx
        call    std::vector<long long, std::allocator<long long>>::operator[](unsigned long)
        mov     rax, QWORD PTR [rax]
        imul    rax, QWORD PTR [rbp-80]
        mov     rbx, rax
        mov     eax, DWORD PTR [rbp-20]
        add     eax, 1
        movsx   rdx, eax
        lea     rax, [rbp-544]
        mov     rsi, rdx
        mov     rdi, rax
        call    std::vector<std::vector<long long, std::allocator<long long>>, std::allocator<std::vector<long long, std::allocator<long long>>>>::operator[](unsigned long)
        mov     rdx, rax
        mov     eax, DWORD PTR [rbp-24]
        cdqe
        mov     rsi, rax
        mov     rdi, rdx
        call    std::vector<long long, std::allocator<long long>>::operator[](unsigned long)
        mov     rcx, rax
        mov     rax, QWORD PTR [rcx]
        add     rax, rbx
        mov     QWORD PTR [rcx], rax
        mov     rsi, QWORD PTR [rcx]
        movabs  rdx, 155014655926305585
        mov     rax, rsi
        imul    rdx
        mov     rax, rdx
        sar     rax, 23
        mov     rdx, rsi
        sar     rdx, 63
        sub     rax, rdx
        imul    rdx, rax, 998244353
        mov     rax, rsi
        sub     rax, rdx
        mov     QWORD PTR [rcx], rax
        mov     eax, DWORD PTR [rbp-20]
        movsx   rdx, eax
        lea     rax, [rbp-544]
        mov     rsi, rdx
        mov     rdi, rax
        call    std::vector<std::vector<long long, std::allocator<long long>>, std::allocator<std::vector<long long, std::allocator<long long>>>>::operator[](unsigned long)
        mov     rdx, rax
        mov     eax, DWORD PTR [rbp-24]
        cdqe
        mov     rsi, rax
        mov     rdi, rdx
        call    std::vector<long long, std::allocator<long long>>::operator[](unsigned long)
        mov     rax, QWORD PTR [rax]
        imul    rax, QWORD PTR [rbp-88]
        mov     rbx, rax
        mov     eax, DWORD PTR [rbp-20]
        add     eax, 1
        movsx   rdx, eax
        lea     rax, [rbp-544]
        mov     rsi, rdx
        mov     rdi, rax
        call    std::vector<std::vector<long long, std::allocator<long long>>, std::allocator<std::vector<long long, std::allocator<long long>>>>::operator[](unsigned long)
        mov     rdx, rax
        mov     eax, DWORD PTR [rbp-20]
        cdqe
        mov     rsi, rax
        mov     rdi, rdx
        call    std::vector<long long, std::allocator<long long>>::operator[](unsigned long)
        mov     rcx, rax
        mov     rax, QWORD PTR [rcx]
        add     rax, rbx
        mov     QWORD PTR [rcx], rax
        mov     rsi, QWORD PTR [rcx]
        movabs  rdx, 155014655926305585
        mov     rax, rsi
        imul    rdx
        mov     rax, rdx
        sar     rax, 23
        mov     rdx, rsi
        sar     rdx, 63
        sub     rax, rdx
        imul    rdx, rax, 998244353
        mov     rax, rsi
        sub     rax, rdx
        mov     QWORD PTR [rcx], rax
        mov     eax, DWORD PTR [rbp-20]
        movsx   rdx, eax
        lea     rax, [rbp-544]
        mov     rsi, rdx
        mov     rdi, rax
        call    std::vector<std::vector<long long, std::allocator<long long>>, std::allocator<std::vector<long long, std::allocator<long long>>>>::operator[](unsigned long)
        mov     rdx, rax
        mov     eax, DWORD PTR [rbp-24]
        cdqe
        mov     rsi, rax
        mov     rdi, rdx
        call    std::vector<long long, std::allocator<long long>>::operator[](unsigned long)
        mov     rax, QWORD PTR [rax]
        imul    rax, QWORD PTR [rbp-80]
        mov     rcx, rax
        movabs  rdx, 155014655926305585
        mov     rax, rcx
        imul    rdx
        mov     rax, rdx
        sar     rax, 23
        mov     rdx, rcx
        sar     rdx, 63
        sub     rax, rdx
        imul    rdx, rax, 998244353
        mov     rax, rcx
        sub     rax, rdx
        imul    rax, QWORD PTR [rbp-88]
        mov     rcx, rax
        movabs  rdx, 155014655926305585
        mov     rax, rcx
        imul    rdx
        mov     rax, rdx
        sar     rax, 23
        mov     rdx, rcx
        sar     rdx, 63
        sub     rax, rdx
        imul    rdx, rax, 998244353
        mov     rax, rcx
        sub     rax, rdx
        mov     edx, 998244353
        mov     rbx, rdx
        sub     rbx, rax
        mov     eax, DWORD PTR [rbp-20]
        add     eax, 1
        movsx   rdx, eax
        lea     rax, [rbp-544]
        mov     rsi, rdx
        mov     rdi, rax
        call    std::vector<std::vector<long long, std::allocator<long long>>, std::allocator<std::vector<long long, std::allocator<long long>>>>::operator[](unsigned long)
        mov     rdx, rax
        mov     eax, DWORD PTR [rbp-20]
        add     eax, 1
        cdqe
        mov     rsi, rax
        mov     rdi, rdx
        call    std::vector<long long, std::allocator<long long>>::operator[](unsigned long)
        mov     rcx, rax
        mov     rax, QWORD PTR [rcx]
        add     rax, rbx
        mov     QWORD PTR [rcx], rax
        mov     rsi, QWORD PTR [rcx]
        movabs  rdx, 155014655926305585
        mov     rax, rsi
        imul    rdx
        mov     rax, rdx
        sar     rax, 23
        mov     rdx, rsi
        sar     rdx, 63
        sub     rax, rdx
        imul    rdx, rax, 998244353
        mov     rax, rsi
        sub     rax, rdx
        mov     QWORD PTR [rcx], rax
        add     DWORD PTR [rbp-24], 1
.L63:
        mov     eax, DWORD PTR [rbp-20]
        cmp     eax, DWORD PTR [rbp-24]
        jge     .L64
        add     DWORD PTR [rbp-20], 1
.L62:
        mov     eax, DWORD PTR [rbp-448]
        cmp     DWORD PTR [rbp-20], eax
        jle     .L65
        mov     eax, DWORD PTR [rbp-448]
        add     eax, 1
        movsx   rdx, eax
        lea     rax, [rbp-544]
        mov     rsi, rdx
        mov     rdi, rax
        call    std::vector<std::vector<long long, std::allocator<long long>>, std::allocator<std::vector<long long, std::allocator<long long>>>>::operator[](unsigned long)
        mov     rdx, rax
        mov     eax, DWORD PTR [rbp-448]
        add     eax, 1
        cdqe
        mov     rsi, rax
        mov     rdi, rdx
        call    std::vector<long long, std::allocator<long long>>::operator[](unsigned long)
        mov     rax, QWORD PTR [rax]
        mov     edx, 998244353
        mov     rcx, rdx
        sub     rcx, rax
        movabs  rdx, 155014655926305585
        mov     rax, rcx
        imul    rdx
        mov     rax, rdx
        sar     rax, 23
        mov     rdx, rcx
        sar     rdx, 63
        sub     rax, rdx
        imul    rdx, rax, 998244353
        mov     rax, rcx
        sub     rax, rdx
        mov     rsi, rax
        mov     edi, OFFSET FLAT:ouf
        call    std::ostream::operator<<(long long)
        mov     esi, 10
        mov     rdi, rax
        call    std::basic_ostream<char, std::char_traits<char>>& std::operator<<<std::char_traits<char>>(std::basic_ostream<char, std::char_traits<char>>&, char)
        lea     rax, [rbp-544]
        mov     rdi, rax
        call    std::vector<std::vector<long long, std::allocator<long long>>, std::allocator<std::vector<long long, std::allocator<long long>>>>::~vector() [complete object destructor]
.L61:
        mov     eax, DWORD PTR [rbp-436]
        and     eax, 2
        test    eax, eax
        je      .L66
        lea     rax, [rbp-386]
        mov     QWORD PTR [rbp-264], rax
        nop
        nop
        mov     eax, DWORD PTR [rbp-444]
        movsx   rcx, eax
        lea     rdx, [rbp-386]
        lea     rax, [rbp-576]
        mov     rsi, rcx
        mov     rdi, rax
        call    std::vector<std::vector<int, std::allocator<int>>, std::allocator<std::vector<int, std::allocator<int>>>>::vector(unsigned long, std::allocator<std::vector<int, std::allocator<int>>> const&) [complete object constructor]
        lea     rax, [rbp-386]
        mov     rdi, rax
        call    std::__new_allocator<std::vector<int, std::allocator<int>>>::~__new_allocator() [base object destructor]
        nop
        lea     rax, [rbp-480]
        mov     QWORD PTR [rbp-96], rax
        mov     rax, QWORD PTR [rbp-96]
        mov     rdi, rax
        call    std::vector<std::pair<int, int>, std::allocator<std::pair<int, int>>>::begin()
        mov     QWORD PTR [rbp-648], rax
        mov     rax, QWORD PTR [rbp-96]
        mov     rdi, rax
        call    std::vector<std::pair<int, int>, std::allocator<std::pair<int, int>>>::end()
        mov     QWORD PTR [rbp-656], rax
        jmp     .L67
.L73:
        mov     rax, QWORD PTR [rbp-648]
        mov     QWORD PTR [rbp-136], rax
        mov     rax, QWORD PTR [rbp-136]
        mov     rdi, rax
        call    std::tuple_element<0ul, std::pair<int, int>>::type& std::get<0ul, int, int>(std::pair<int, int>&)
        mov     QWORD PTR [rbp-144], rax
        mov     rax, QWORD PTR [rbp-136]
        mov     rdi, rax
        call    std::tuple_element<1ul, std::pair<int, int>>::type& std::get<1ul, int, int>(std::pair<int, int>&)
        mov     QWORD PTR [rbp-152], rax
        mov     rax, QWORD PTR [rbp-152]
        mov     eax, DWORD PTR [rax]
        movsx   rdx, eax
        lea     rax, [rbp-576]
        mov     rsi, rdx
        mov     rdi, rax
        call    std::vector<std::vector<int, std::allocator<int>>, std::allocator<std::vector<int, std::allocator<int>>>>::operator[](unsigned long)
        mov     rdx, rax
        mov     rax, QWORD PTR [rbp-144]
        mov     rsi, rax
        mov     rdi, rdx
        call    int& std::vector<int, std::allocator<int>>::emplace_back<int&>(int&)
        mov     rax, QWORD PTR [rbp-648]
        add     rax, 8
        mov     QWORD PTR [rbp-648], rax
        nop
.L67:
        lea     rax, [rbp-648]
        mov     QWORD PTR [rbp-272], rax
        mov     rax, QWORD PTR [rbp-272]
        mov     rdx, QWORD PTR [rax]
        lea     rax, [rbp-656]
        mov     QWORD PTR [rbp-280], rax
        mov     rax, QWORD PTR [rbp-280]
        mov     rax, QWORD PTR [rax]
        cmp     rdx, rax
        setne   al
        test    al, al
        jne     .L73
        lea     rax, [rbp-385]
        mov     QWORD PTR [rbp-296], rax
        nop
        nop
        lea     rax, [rbp-349]
        mov     QWORD PTR [rbp-288], rax
        nop
        nop
        mov     eax, DWORD PTR [rbp-440]
        movsx   rcx, eax
        lea     rdx, [rbp-349]
        lea     rax, [rbp-384]
        mov     rsi, rcx
        mov     rdi, rax
        call    std::vector<long long, std::allocator<long long>>::vector(unsigned long, std::allocator<long long> const&) [complete object constructor]
        mov     eax, DWORD PTR [rbp-440]
        movsx   rsi, eax
        lea     rcx, [rbp-385]
        lea     rdx, [rbp-384]
        lea     rax, [rbp-608]
        mov     rdi, rax
        call    std::vector<std::vector<long long, std::allocator<long long>>, std::allocator<std::vector<long long, std::allocator<long long>>>>::vector(unsigned long, std::vector<long long, std::allocator<long long>> const&, std::allocator<std::vector<long long, std::allocator<long long>>> const&) [complete object constructor]
        lea     rax, [rbp-384]
        mov     rdi, rax
        call    std::vector<long long, std::allocator<long long>>::~vector() [complete object destructor]
        lea     rax, [rbp-349]
        mov     rdi, rax
        call    std::__new_allocator<long long>::~__new_allocator() [base object destructor]
        nop
        lea     rax, [rbp-385]
        mov     rdi, rax
        call    std::__new_allocator<std::vector<long long, std::allocator<long long>>>::~__new_allocator() [base object destructor]
        nop
        lea     rax, [rbp-640]
        mov     rdi, rax
        call    std::vector<std::vector<long long, std::allocator<long long>>, std::allocator<std::vector<long long, std::allocator<long long>>>>::vector() [complete object constructor]
        lea     rax, [rbp-576]
        mov     esi, 0
        mov     rdi, rax
        call    std::vector<std::vector<int, std::allocator<int>>, std::allocator<std::vector<int, std::allocator<int>>>>::operator[](unsigned long)
        mov     rdi, rax
        call    std::vector<int, std::allocator<int>>::back()
        mov     eax, DWORD PTR [rax]
        mov     DWORD PTR [rbp-28], eax
        jmp     .L74
.L75:
        lea     rax, [rbp-608]
        mov     esi, 0
        mov     rdi, rax
        call    std::vector<std::vector<long long, std::allocator<long long>>, std::allocator<std::vector<long long, std::allocator<long long>>>>::operator[](unsigned long)
        mov     rdx, rax
        mov     eax, DWORD PTR [rbp-28]
        cdqe
        mov     rsi, rax
        mov     rdi, rdx
        call    std::vector<long long, std::allocator<long long>>::operator[](unsigned long)
        mov     QWORD PTR [rax], 1
        add     DWORD PTR [rbp-28], 1
.L74:
        mov     eax, DWORD PTR [rbp-440]
        cmp     DWORD PTR [rbp-28], eax
        jl      .L75
        mov     DWORD PTR [rbp-32], 1
        jmp     .L76
.L108:
        lea     rdx, [rbp-608]
        lea     rax, [rbp-640]
        mov     rsi, rdx
        mov     rdi, rax
        call    std::vector<std::vector<long long, std::allocator<long long>>, std::allocator<std::vector<long long, std::allocator<long long>>>>::operator=(std::vector<std::vector<long long, std::allocator<long long>>, std::allocator<std::vector<long long, std::allocator<long long>>>> const&)
        lea     rax, [rbp-608]
        mov     QWORD PTR [rbp-104], rax
        mov     rax, QWORD PTR [rbp-104]
        mov     rdi, rax
        call    std::vector<std::vector<long long, std::allocator<long long>>, std::allocator<std::vector<long long, std::allocator<long long>>>>::begin()
        mov     QWORD PTR [rbp-664], rax
        mov     rax, QWORD PTR [rbp-104]
        mov     rdi, rax
        call    std::vector<std::vector<long long, std::allocator<long long>>, std::allocator<std::vector<long long, std::allocator<long long>>>>::end()
        mov     QWORD PTR [rbp-672], rax
        jmp     .L77
.L85:
        mov     rax, QWORD PTR [rbp-664]
        mov     QWORD PTR [rbp-128], rax
        mov     DWORD PTR [rbp-348], 0
        mov     rax, QWORD PTR [rbp-128]
        mov     rdi, rax
        call    std::vector<long long, std::allocator<long long>>::end()
        mov     rbx, rax
        mov     rax, QWORD PTR [rbp-128]
        mov     rdi, rax
        call    std::vector<long long, std::allocator<long long>>::begin()
        mov     QWORD PTR [rbp-680], rax
        mov     QWORD PTR [rbp-688], rbx
        mov     rax, QWORD PTR [rbp-680]
        mov     QWORD PTR [rbp-696], rax
        mov     rax, QWORD PTR [rbp-688]
        mov     QWORD PTR [rbp-704], rax
        lea     rax, [rbp-348]
        mov     QWORD PTR [rbp-304], rax
        mov     rax, QWORD PTR [rbp-696]
        mov     QWORD PTR [rbp-712], rax
        mov     rax, QWORD PTR [rbp-704]
        mov     QWORD PTR [rbp-720], rax
        mov     rax, QWORD PTR [rbp-304]
        mov     QWORD PTR [rbp-312], rax
        lea     rax, [rbp-720]
        mov     rcx, QWORD PTR [rax]
        lea     rax, [rbp-712]
        mov     rax, QWORD PTR [rax]
        mov     rdx, QWORD PTR [rbp-312]
        mov     rsi, rcx
        mov     rdi, rax
        call    void std::__fill_a1<long long*, int>(long long*, long long*, int const&)
        nop
        nop
        nop
        mov     rax, QWORD PTR [rbp-664]
        add     rax, 24
        mov     QWORD PTR [rbp-664], rax
        nop
.L77:
        lea     rax, [rbp-664]
        mov     QWORD PTR [rbp-320], rax
        mov     rax, QWORD PTR [rbp-320]
        mov     rdx, QWORD PTR [rax]
        lea     rax, [rbp-672]
        mov     QWORD PTR [rbp-328], rax
        mov     rax, QWORD PTR [rbp-328]
        mov     rax, QWORD PTR [rax]
        cmp     rdx, rax
        setne   al
        test    al, al
        jne     .L85
        mov     DWORD PTR [rbp-36], 0
        jmp     .L86
.L107:
        mov     eax, DWORD PTR [rbp-36]
        add     eax, 1
        mov     DWORD PTR [rbp-40], eax
        jmp     .L87
.L106:
        mov     eax, DWORD PTR [rbp-36]
        mov     DWORD PTR [rbp-44], eax
        jmp     .L88
.L105:
        mov     eax, DWORD PTR [rbp-40]
        mov     DWORD PTR [rbp-48], eax
        jmp     .L89
.L102:
        mov     BYTE PTR [rbp-49], 1
        mov     eax, DWORD PTR [rbp-32]
        movsx   rdx, eax
        lea     rax, [rbp-576]
        mov     rsi, rdx
        mov     rdi, rax
        call    std::vector<std::vector<int, std::allocator<int>>, std::allocator<std::vector<int, std::allocator<int>>>>::operator[](unsigned long)
        mov     QWORD PTR [rbp-112], rax
        mov     rax, QWORD PTR [rbp-112]
        mov     rdi, rax
        call    std::vector<int, std::allocator<int>>::begin()
        mov     QWORD PTR [rbp-728], rax
        mov     rax, QWORD PTR [rbp-112]
        mov     rdi, rax
        call    std::vector<int, std::allocator<int>>::end()
        mov     QWORD PTR [rbp-736], rax
        jmp     .L90
.L100:
        mov     rax, QWORD PTR [rbp-728]
        mov     QWORD PTR [rbp-120], rax
        movzx   edx, BYTE PTR [rbp-49]
        mov     rax, QWORD PTR [rbp-120]
        mov     eax, DWORD PTR [rax]
        cmp     DWORD PTR [rbp-36], eax
        jg      .L92
        mov     rax, QWORD PTR [rbp-120]
        mov     eax, DWORD PTR [rax]
        cmp     DWORD PTR [rbp-44], eax
        jge     .L93
.L92:
        mov     rax, QWORD PTR [rbp-120]
        mov     eax, DWORD PTR [rax]
        cmp     DWORD PTR [rbp-40], eax
        jg      .L94
        mov     rax, QWORD PTR [rbp-120]
        mov     eax, DWORD PTR [rax]
        cmp     DWORD PTR [rbp-48], eax
        jl      .L94
.L93:
        mov     eax, 1
        jmp     .L95
.L94:
        mov     eax, 0
.L95:
        movzx   eax, al
        and     eax, edx
        test    eax, eax
        setne   al
        mov     BYTE PTR [rbp-49], al
        mov     rax, QWORD PTR [rbp-728]
        add     rax, 4
        mov     QWORD PTR [rbp-728], rax
        nop
.L90:
        lea     rax, [rbp-728]
        mov     QWORD PTR [rbp-336], rax
        mov     rax, QWORD PTR [rbp-336]
        mov     rdx, QWORD PTR [rax]
        lea     rax, [rbp-736]
        mov     QWORD PTR [rbp-344], rax
        mov     rax, QWORD PTR [rbp-344]
        mov     rax, QWORD PTR [rax]
        cmp     rdx, rax
        setne   al
        test    al, al
        jne     .L100
        cmp     BYTE PTR [rbp-49], 0
        je      .L101
        mov     eax, DWORD PTR [rbp-36]
        movsx   rdx, eax
        lea     rax, [rbp-640]
        mov     rsi, rdx
        mov     rdi, rax
        call    std::vector<std::vector<long long, std::allocator<long long>>, std::allocator<std::vector<long long, std::allocator<long long>>>>::operator[](unsigned long)
        mov     rdx, rax
        mov     eax, DWORD PTR [rbp-40]
        cdqe
        mov     rsi, rax
        mov     rdi, rdx
        call    std::vector<long long, std::allocator<long long>>::operator[](unsigned long)
        mov     rbx, QWORD PTR [rax]
        mov     eax, DWORD PTR [rbp-44]
        movsx   rdx, eax
        lea     rax, [rbp-608]
        mov     rsi, rdx
        mov     rdi, rax
        call    std::vector<std::vector<long long, std::allocator<long long>>, std::allocator<std::vector<long long, std::allocator<long long>>>>::operator[](unsigned long)
        mov     rdx, rax
        mov     eax, DWORD PTR [rbp-48]
        cdqe
        mov     rsi, rax
        mov     rdi, rdx
        call    std::vector<long long, std::allocator<long long>>::operator[](unsigned long)
        mov     rcx, rax
        mov     rax, QWORD PTR [rcx]
        add     rax, rbx
        mov     QWORD PTR [rcx], rax
        mov     rsi, QWORD PTR [rcx]
        movabs  rdx, 155014655926305585
        mov     rax, rsi
        imul    rdx
        mov     rax, rdx
        sar     rax, 23
        mov     rdx, rsi
        sar     rdx, 63
        sub     rax, rdx
        imul    rdx, rax, 998244353
        mov     rax, rsi
        sub     rax, rdx
        mov     QWORD PTR [rcx], rax
.L101:
        add     DWORD PTR [rbp-48], 1
.L89:
        mov     eax, DWORD PTR [rbp-440]
        cmp     DWORD PTR [rbp-48], eax
        jl      .L102
        add     DWORD PTR [rbp-44], 1
.L88:
        mov     eax, DWORD PTR [rbp-444]
        sub     eax, 1
        cmp     DWORD PTR [rbp-32], eax
        jne     .L103
        mov     eax, DWORD PTR [rbp-440]
        sub     eax, 1
        cmp     DWORD PTR [rbp-40], eax
        jne     .L103
        mov     eax, 1
        jmp     .L104
.L103:
        mov     eax, 0
.L104:
        movzx   edx, al
        mov     eax, DWORD PTR [rbp-40]
        add     eax, edx
        cmp     DWORD PTR [rbp-44], eax
        jl      .L105
        add     DWORD PTR [rbp-40], 1
.L87:
        mov     eax, DWORD PTR [rbp-440]
        cmp     DWORD PTR [rbp-40], eax
        jl      .L106
        add     DWORD PTR [rbp-36], 1
.L86:
        mov     eax, DWORD PTR [rbp-440]
        cmp     DWORD PTR [rbp-36], eax
        jl      .L107
        add     DWORD PTR [rbp-32], 1
.L76:
        mov     eax, DWORD PTR [rbp-444]
        cmp     DWORD PTR [rbp-32], eax
        jl      .L108
        mov     eax, DWORD PTR [rbp-440]
        sub     eax, 1
        movsx   rdx, eax
        lea     rax, [rbp-608]
        mov     rsi, rdx
        mov     rdi, rax
        call    std::vector<std::vector<long long, std::allocator<long long>>, std::allocator<std::vector<long long, std::allocator<long long>>>>::operator[](unsigned long)
        mov     rdx, rax
        mov     eax, DWORD PTR [rbp-440]
        sub     eax, 1
        cdqe
        mov     rsi, rax
        mov     rdi, rdx
        call    std::vector<long long, std::allocator<long long>>::operator[](unsigned long)
        mov     rax, QWORD PTR [rax]
        lea     rcx, [rax+rax]
        movabs  rdx, 155014655926305585
        mov     rax, rcx
        imul    rdx
        mov     rax, rdx
        sar     rax, 23
        mov     rdx, rcx
        sar     rdx, 63
        sub     rax, rdx
        imul    rdx, rax, 998244353
        mov     rax, rcx
        sub     rax, rdx
        mov     rsi, rax
        mov     edi, OFFSET FLAT:ouf
        call    std::ostream::operator<<(long long)
        mov     esi, 10
        mov     rdi, rax
        call    std::basic_ostream<char, std::char_traits<char>>& std::operator<<<std::char_traits<char>>(std::basic_ostream<char, std::char_traits<char>>&, char)
        lea     rax, [rbp-640]
        mov     rdi, rax
        call    std::vector<std::vector<long long, std::allocator<long long>>, std::allocator<std::vector<long long, std::allocator<long long>>>>::~vector() [complete object destructor]
        lea     rax, [rbp-608]
        mov     rdi, rax
        call    std::vector<std::vector<long long, std::allocator<long long>>, std::allocator<std::vector<long long, std::allocator<long long>>>>::~vector() [complete object destructor]
        lea     rax, [rbp-576]
        mov     rdi, rax
        call    std::vector<std::vector<int, std::allocator<int>>, std::allocator<std::vector<int, std::allocator<int>>>>::~vector() [complete object destructor]
.L66:
        mov     ebx, 0
        lea     rax, [rbp-480]
        mov     rdi, rax
        call    std::vector<std::pair<int, int>, std::allocator<std::pair<int, int>>>::~vector() [complete object destructor]
        mov     eax, ebx
        jmp     .L130
        mov     rbx, rax
        lea     rax, [rbp-429]
        mov     rdi, rax
        call    std::__new_allocator<std::pair<int, int>>::~__new_allocator() [base object destructor]
        nop
        mov     rax, rbx
        mov     rdi, rax
        call    _Unwind_Resume
        mov     rbx, rax
        lea     rax, [rbp-416]
        mov     rdi, rax
        call    std::vector<long long, std::allocator<long long>>::~vector() [complete object destructor]
        jmp     .L112
        mov     rbx, rax
.L112:
        lea     rax, [rbp-387]
        mov     rdi, rax
        call    std::__new_allocator<long long>::~__new_allocator() [base object destructor]
        nop
        lea     rax, [rbp-417]
        mov     rdi, rax
        call    std::__new_allocator<std::vector<long long, std::allocator<long long>>>::~__new_allocator() [base object destructor]
        nop
        jmp     .L113
        mov     rbx, rax
        lea     rax, [rbp-544]
        mov     rdi, rax
        call    std::vector<std::vector<long long, std::allocator<long long>>, std::allocator<std::vector<long long, std::allocator<long long>>>>::~vector() [complete object destructor]
        jmp     .L113
        mov     rbx, rax
        lea     rax, [rbp-386]
        mov     rdi, rax
        call    std::__new_allocator<std::vector<int, std::allocator<int>>>::~__new_allocator() [base object destructor]
        nop
        jmp     .L113
        mov     rbx, rax
        lea     rax, [rbp-384]
        mov     rdi, rax
        call    std::vector<long long, std::allocator<long long>>::~vector() [complete object destructor]
        jmp     .L117
        mov     rbx, rax
.L117:
        lea     rax, [rbp-349]
        mov     rdi, rax
        call    std::__new_allocator<long long>::~__new_allocator() [base object destructor]
        nop
        lea     rax, [rbp-385]
        mov     rdi, rax
        call    std::__new_allocator<std::vector<long long, std::allocator<long long>>>::~__new_allocator() [base object destructor]
        nop
        jmp     .L118
        mov     rbx, rax
        lea     rax, [rbp-640]
        mov     rdi, rax
        call    std::vector<std::vector<long long, std::allocator<long long>>, std::allocator<std::vector<long long, std::allocator<long long>>>>::~vector() [complete object destructor]
        lea     rax, [rbp-608]
        mov     rdi, rax
        call    std::vector<std::vector<long long, std::allocator<long long>>, std::allocator<std::vector<long long, std::allocator<long long>>>>::~vector() [complete object destructor]
        jmp     .L118
        mov     rbx, rax
.L118:
        lea     rax, [rbp-576]
        mov     rdi, rax
        call    std::vector<std::vector<int, std::allocator<int>>, std::allocator<std::vector<int, std::allocator<int>>>>::~vector() [complete object destructor]
        jmp     .L113
        mov     rbx, rax
.L113:
        lea     rax, [rbp-480]
        mov     rdi, rax
        call    std::vector<std::pair<int, int>, std::allocator<std::pair<int, int>>>::~vector() [complete object destructor]
        mov     rax, rbx
        mov     rdi, rax
        call    _Unwind_Resume
.L130:
        add     rsp, 720
        pop     rbx
        pop     r12
        pop     rbp
        ret
        .set    std::_Vector_base<long long, std::allocator<long long>>::_Vector_impl::_Vector_impl() [complete object constructor],_ZNSt12_Vector_baseIxSaIxEE12_Vector_implC2Ev
        .set    std::_Vector_base<long long, std::allocator<long long>>::~_Vector_base() [complete object destructor],_ZNSt12_Vector_baseIxSaIxEED2Ev
        .set    std::vector<long long, std::allocator<long long>>::~vector() [complete object destructor],_ZNSt6vectorIxSaIxEED2Ev
.LC0:
        .string "__n < this->size() "
.LC1:
        .string "std::vector<_Tp, _Alloc>::reference std::vector<_Tp, _Alloc>::operator[](size_type) [with _Tp = long long int; _Alloc = std::allocator<long long int>; reference = long long int&; size_type = long unsigned int]"
.LC2:
        .string "/opt/compiler-explorer/gcc-15.2.0/include/c++/15.2.0/bits/stl_vector.h"
        .set    std::vector<std::pair<int, int>, std::allocator<std::pair<int, int>>>::vector(unsigned long, std::allocator<std::pair<int, int>> const&) [complete object constructor],_ZNSt6vectorISt4pairIiiESaIS1_EEC2EmRKS2_
        .set    std::vector<std::pair<int, int>, std::allocator<std::pair<int, int>>>::~vector() [complete object destructor],_ZNSt6vectorISt4pairIiiESaIS1_EED2Ev
        .set    std::vector<long long, std::allocator<long long>>::vector(unsigned long, std::allocator<long long> const&) [complete object constructor],_ZNSt6vectorIxSaIxEEC2EmRKS0_
        .set    std::vector<std::vector<long long, std::allocator<long long>>, std::allocator<std::vector<long long, std::allocator<long long>>>>::vector(unsigned long, std::vector<long long, std::allocator<long long>> const&, std::allocator<std::vector<long long, std::allocator<long long>>> const&) [complete object constructor],_ZNSt6vectorIS_IxSaIxEESaIS1_EEC2EmRKS1_RKS2_
        .set    std::vector<std::vector<long long, std::allocator<long long>>, std::allocator<std::vector<long long, std::allocator<long long>>>>::~vector() [complete object destructor],_ZNSt6vectorIS_IxSaIxEESaIS1_EED2Ev
.LC3:
        .string "std::vector<_Tp, _Alloc>::reference std::vector<_Tp, _Alloc>::operator[](size_type) [with _Tp = std::vector<long long int>; _Alloc = std::allocator<std::vector<long long int> >; reference = std::vector<long long int>&; size_type = long unsigned int]"
.LC4:
        .string "std::vector<_Tp, _Alloc>::reference std::vector<_Tp, _Alloc>::operator[](size_type) [with _Tp = std::pair<int, int>; _Alloc = std::allocator<std::pair<int, int> >; reference = std::pair<int, int>&; size_type = long unsigned int]"
.LC5:
        .string "std::vector<_Tp, _Alloc>::const_reference std::vector<_Tp, _Alloc>::operator[](size_type) const [with _Tp = long long int; _Alloc = std::allocator<long long int>; const_reference = const long long int&; size_type = long unsigned int]"
        .set    std::vector<std::vector<int, std::allocator<int>>, std::allocator<std::vector<int, std::allocator<int>>>>::vector(unsigned long, std::allocator<std::vector<int, std::allocator<int>>> const&) [complete object constructor],_ZNSt6vectorIS_IiSaIiEESaIS1_EEC2EmRKS2_
        .set    std::vector<std::vector<int, std::allocator<int>>, std::allocator<std::vector<int, std::allocator<int>>>>::~vector() [complete object destructor],_ZNSt6vectorIS_IiSaIiEESaIS1_EED2Ev
.LC6:
        .string "std::vector<_Tp, _Alloc>::reference std::vector<_Tp, _Alloc>::operator[](size_type) [with _Tp = std::vector<int>; _Alloc = std::allocator<std::vector<int> >; reference = std::vector<int>&; size_type = long unsigned int]"
        .set    std::_Vector_base<std::vector<long long, std::allocator<long long>>, std::allocator<std::vector<long long, std::allocator<long long>>>>::_Vector_impl::_Vector_impl() [complete object constructor],_ZNSt12_Vector_baseISt6vectorIxSaIxEESaIS2_EE12_Vector_implC2Ev
        .set    std::_Vector_base<std::vector<long long, std::allocator<long long>>, std::allocator<std::vector<long long, std::allocator<long long>>>>::~_Vector_base() [complete object destructor],_ZNSt12_Vector_baseISt6vectorIxSaIxEESaIS2_EED2Ev
.LC7:
        .string "!this->empty() "
.LC8:
        .string "std::vector<_Tp, _Alloc>::reference std::vector<_Tp, _Alloc>::back() [with _Tp = int; _Alloc = std::allocator<int>; reference = int&]"
        .set    std::_Vector_base<long long, std::allocator<long long>>::_Vector_impl_data::_Vector_impl_data() [complete object constructor],_ZNSt12_Vector_baseIxSaIxEE17_Vector_impl_dataC2Ev
        .set    std::__new_allocator<long long>::~__new_allocator() [complete object destructor],std::__new_allocator<long long>::~__new_allocator() [base object destructor]
.LC9:
        .string "vector::_M_fill_insert"

        .set    std::__new_allocator<std::pair<int, int>>::~__new_allocator() [complete object destructor],std::__new_allocator<std::pair<int, int>>::~__new_allocator() [base object destructor]
.LC10:
        .string "cannot create std::vector larger than max_size() "
        .set    std::_Vector_base<std::pair<int, int>, std::allocator<std::pair<int, int>>>::_Vector_impl::~_Vector_impl() [complete object destructor],_ZNSt12_Vector_baseISt4pairIiiESaIS1_EE12_Vector_implD2Ev
        .set    std::_Vector_base<std::pair<int, int>, std::allocator<std::pair<int, int>>>::_Vector_base(unsigned long, std::allocator<std::pair<int, int>> const&) [complete object constructor],_ZNSt12_Vector_baseISt4pairIiiESaIS1_EEC2EmRKS2_
        .set    std::_Vector_base<std::pair<int, int>, std::allocator<std::pair<int, int>>>::~_Vector_base() [complete object destructor],_ZNSt12_Vector_baseISt4pairIiiESaIS1_EED2Ev
.LC11:
        .string "vector::_M_realloc_append"
.LC12:
        .string "std::vector<_Tp, _Alloc>::reference std::vector<_Tp, _Alloc>::back() [with _Tp = std::pair<int, int>; _Alloc = std::allocator<std::pair<int, int> >; reference = std::pair<int, int>&]"
        .set    std::_Vector_base<long long, std::allocator<long long>>::_Vector_base(unsigned long, std::allocator<long long> const&) [complete object constructor],_ZNSt12_Vector_baseIxSaIxEEC2EmRKS0_
        .set    std::__new_allocator<std::vector<long long, std::allocator<long long>>>::~__new_allocator() [complete object destructor],std::__new_allocator<std::vector<long long, std::allocator<long long>>>::~__new_allocator() [base object destructor]
        .set    std::_Vector_base<std::vector<long long, std::allocator<long long>>, std::allocator<std::vector<long long, std::allocator<long long>>>>::_Vector_base(unsigned long, std::allocator<std::vector<long long, std::allocator<long long>>> const&) [complete object constructor],_ZNSt12_Vector_baseISt6vectorIxSaIxEESaIS2_EEC2EmRKS3_
        .set    std::__new_allocator<std::vector<int, std::allocator<int>>>::~__new_allocator() [complete object destructor],std::__new_allocator<std::vector<int, std::allocator<int>>>::~__new_allocator() [base object destructor]
        .set    std::_Vector_base<std::vector<int, std::allocator<int>>, std::allocator<std::vector<int, std::allocator<int>>>>::_Vector_impl::~_Vector_impl() [complete object destructor],_ZNSt12_Vector_baseISt6vectorIiSaIiEESaIS2_EE12_Vector_implD2Ev
        .set    std::_Vector_base<std::vector<int, std::allocator<int>>, std::allocator<std::vector<int, std::allocator<int>>>>::_Vector_base(unsigned long, std::allocator<std::vector<int, std::allocator<int>>> const&) [complete object constructor],_ZNSt12_Vector_baseISt6vectorIiSaIiEESaIS2_EEC2EmRKS3_
        .set    std::_Vector_base<std::vector<int, std::allocator<int>>, std::allocator<std::vector<int, std::allocator<int>>>>::~_Vector_base() [complete object destructor],_ZNSt12_Vector_baseISt6vectorIiSaIiEESaIS2_EED2Ev
        .set    std::_Vector_base<std::vector<long long, std::allocator<long long>>, std::allocator<std::vector<long long, std::allocator<long long>>>>::_Vector_impl_data::_Vector_impl_data() [complete object constructor],_ZNSt12_Vector_baseISt6vectorIxSaIxEESaIS2_EE17_Vector_impl_dataC2Ev
        .set    std::vector<long long, std::allocator<long long>>::_Temporary_value::_Temporary_value<long long const&>(std::vector<long long, std::allocator<long long>>*, long long const&),_ZNSt6vectorIxSaIxEE16_Temporary_valueC2IJRKxEEEPS1_DpOT_
        .set    std::vector<long long, std::allocator<long long>>::_Temporary_value::~_Temporary_value() [complete object destructor],_ZNSt6vectorIxSaIxEE16_Temporary_valueD2Ev
        .set    std::vector<long long, std::allocator<long long>>::_Guard_alloc::_Guard_alloc(long long*, unsigned long, std::_Vector_base<long long, std::allocator<long long>>&) [complete object constructor],_ZNSt6vectorIxSaIxEE12_Guard_allocC2EPxmRSt12_Vector_baseIxS0_E
        .set    std::vector<long long, std::allocator<long long>>::_Guard_alloc::~_Guard_alloc() [complete object destructor],_ZNSt6vectorIxSaIxEE12_Guard_allocD2Ev
        .set    std::_Vector_base<std::pair<int, int>, std::allocator<std::pair<int, int>>>::_Vector_impl::_Vector_impl(std::allocator<std::pair<int, int>> const&) [complete object constructor],_ZNSt12_Vector_baseISt4pairIiiESaIS1_EE12_Vector_implC2ERKS2_
        .set    std::vector<std::pair<int, int>, std::allocator<std::pair<int, int>>>::_Guard_alloc::_Guard_alloc(std::pair<int, int>*, unsigned long, std::_Vector_base<std::pair<int, int>, std::allocator<std::pair<int, int>>>&) [complete object constructor],_ZNSt6vectorISt4pairIiiESaIS1_EE12_Guard_allocC2EPS1_mRSt12_Vector_baseIS1_S2_E
        .set    std::vector<std::pair<int, int>, std::allocator<std::pair<int, int>>>::_Guard_alloc::~_Guard_alloc() [complete object destructor],_ZNSt6vectorISt4pairIiiESaIS1_EE12_Guard_allocD2Ev
        .set    std::_Vector_base<long long, std::allocator<long long>>::_Vector_impl::_Vector_impl(std::allocator<long long> const&) [complete object constructor],_ZNSt12_Vector_baseIxSaIxEE12_Vector_implC2ERKS0_
        .set    std::_Vector_base<std::vector<long long, std::allocator<long long>>, std::allocator<std::vector<long long, std::allocator<long long>>>>::_Vector_impl::_Vector_impl(std::allocator<std::vector<long long, std::allocator<long long>>> const&) [complete object constructor],_ZNSt12_Vector_baseISt6vectorIxSaIxEESaIS2_EE12_Vector_implC2ERKS3_
        .set    std::_Vector_base<std::vector<int, std::allocator<int>>, std::allocator<std::vector<int, std::allocator<int>>>>::_Vector_impl::_Vector_impl(std::allocator<std::vector<int, std::allocator<int>>> const&) [complete object constructor],_ZNSt12_Vector_baseISt6vectorIiSaIiEESaIS2_EE12_Vector_implC2ERKS3_
        .set    std::vector<int, std::allocator<int>>::_Guard_alloc::_Guard_alloc(int*, unsigned long, std::_Vector_base<int, std::allocator<int>>&) [complete object constructor],_ZNSt6vectorIiSaIiEE12_Guard_allocC2EPimRSt12_Vector_baseIiS0_E
        .set    std::vector<int, std::allocator<int>>::_Guard_alloc::~_Guard_alloc() [complete object destructor],_ZNSt6vectorIiSaIiEE12_Guard_allocD2Ev
        .set    std::vector<std::vector<long long, std::allocator<long long>>, std::allocator<std::vector<long long, std::allocator<long long>>>>::_Guard_alloc::_Guard_alloc(std::vector<long long, std::allocator<long long>>*, unsigned long, std::_Vector_base<std::vector<long long, std::allocator<long long>>, std::allocator<std::vector<long long, std::allocator<long long>>>>&) [complete object constructor],_ZNSt6vectorIS_IxSaIxEESaIS1_EE12_Guard_allocC2EPS1_mRSt12_Vector_baseIS1_S2_E
        .set    std::vector<std::vector<long long, std::allocator<long long>>, std::allocator<std::vector<long long, std::allocator<long long>>>>::_Guard_alloc::~_Guard_alloc() [complete object destructor],_ZNSt6vectorIS_IxSaIxEESaIS1_EE12_Guard_allocD2Ev
        .set    std::vector<long long, std::allocator<long long>>::_Temporary_value::_Storage::_Storage() [complete object constructor],_ZNSt6vectorIxSaIxEE16_Temporary_value8_StorageC2Ev
        .set    std::vector<long long, std::allocator<long long>>::_Temporary_value::_Storage::~_Storage() [complete object destructor],_ZNSt6vectorIxSaIxEE16_Temporary_value8_StorageD2Ev
        .set    std::_Vector_base<std::pair<int, int>, std::allocator<std::pair<int, int>>>::_Vector_impl_data::_Vector_impl_data() [complete object constructor],_ZNSt12_Vector_baseISt4pairIiiESaIS1_EE17_Vector_impl_dataC2Ev
        .set    std::pair<int, int>::pair<int, int, true>(int&&, int&&),_ZNSt4pairIiiEC2IiiLb1EEEOT_OT0_
        .set    std::pair<int, int>::pair<int&, int&, true>(int&, int&),_ZNSt4pairIiiEC2IRiS2_Lb1EEEOT_OT0_
        .set    std::_Vector_base<std::vector<int, std::allocator<int>>, std::allocator<std::vector<int, std::allocator<int>>>>::_Vector_impl_data::_Vector_impl_data() [complete object constructor],_ZNSt12_Vector_baseISt6vectorIiSaIiEESaIS2_EE17_Vector_impl_dataC2Ev
        .set    std::move_iterator<long long*>::move_iterator(long long*) [complete object constructor],_ZNSt13move_iteratorIPxEC2ES0_
        .set    std::vector<int, std::allocator<int>>::~vector() [complete object destructor],_ZNSt6vectorIiSaIiEED2Ev
        .set    std::_UninitDestroyGuard<std::vector<long long, std::allocator<long long>>*, void>::_UninitDestroyGuard(std::vector<long long, std::allocator<long long>>*&) [complete object constructor],_ZNSt19_UninitDestroyGuardIPSt6vectorIxSaIxEEvEC2ERS3_
        .set    std::_UninitDestroyGuard<std::vector<long long, std::allocator<long long>>*, void>::~_UninitDestroyGuard() [complete object destructor],_ZNSt19_UninitDestroyGuardIPSt6vectorIxSaIxEEvED2Ev
        .set    std::_UninitDestroyGuard<long long*, void>::_UninitDestroyGuard(long long*&) [complete object constructor],_ZNSt19_UninitDestroyGuardIPxvEC2ERS0_
        .set    std::_UninitDestroyGuard<long long*, void>::~_UninitDestroyGuard() [complete object destructor],_ZNSt19_UninitDestroyGuardIPxvED2Ev
        .set    std::_UninitDestroyGuard<std::pair<int, int>*, void>::_UninitDestroyGuard(std::pair<int, int>*&) [complete object constructor],_ZNSt19_UninitDestroyGuardIPSt4pairIiiEvEC2ERS2_
        .set    std::_UninitDestroyGuard<std::pair<int, int>*, void>::~_UninitDestroyGuard() [complete object destructor],_ZNSt19_UninitDestroyGuardIPSt4pairIiiEvED2Ev
        .set    std::_UninitDestroyGuard<std::vector<int, std::allocator<int>>*, void>::_UninitDestroyGuard(std::vector<int, std::allocator<int>>*&) [complete object constructor],_ZNSt19_UninitDestroyGuardIPSt6vectorIiSaIiEEvEC2ERS3_
        .set    std::_UninitDestroyGuard<std::vector<int, std::allocator<int>>*, void>::~_UninitDestroyGuard() [complete object destructor],_ZNSt19_UninitDestroyGuardIPSt6vectorIiSaIiEEvED2Ev
        .set    std::_Vector_base<int, std::allocator<int>>::_Vector_impl::~_Vector_impl() [complete object destructor],_ZNSt12_Vector_baseIiSaIiEE12_Vector_implD2Ev
        .set    std::_Vector_base<int, std::allocator<int>>::_Vector_base() [complete object constructor],_ZNSt12_Vector_baseIiSaIiEEC2Ev
        .set    std::vector<int, std::allocator<int>>::vector() [complete object constructor],_ZNSt6vectorIiSaIiEEC2Ev
        .set    std::_Vector_base<int, std::allocator<int>>::~_Vector_base() [complete object destructor],_ZNSt12_Vector_baseIiSaIiEED2Ev
        .set    std::vector<long long, std::allocator<long long>>::vector(std::vector<long long, std::allocator<long long>> const&) [complete object constructor],_ZNSt6vectorIxSaIxEEC2ERKS1_
        .set    std::pair<int, int>::pair<int, int, true>(),_ZNSt4pairIiiEC2IiiLb1EEEv
        .set    std::_Vector_base<int, std::allocator<int>>::_Vector_impl::_Vector_impl() [complete object constructor],_ZNSt12_Vector_baseIiSaIiEE12_Vector_implC2Ev
        .set    std::_Vector_base<int, std::allocator<int>>::_Vector_impl_data::_Vector_impl_data() [complete object constructor],_ZNSt12_Vector_baseIiSaIiEE17_Vector_impl_dataC2Ev
        .set    std::__new_allocator<int>::~__new_allocator() [complete object destructor],_ZNSt15__new_allocatorIiED2Ev
mathbase::~mathbase() [base object destructor]:
        push    rbp
        mov     rbp, rsp
        sub     rsp, 16
        mov     QWORD PTR [rbp-8], rdi
        mov     rax, QWORD PTR [rbp-8]
        add     rax, 24
        mov     rdi, rax
        call    std::vector<long long, std::allocator<long long>>::~vector() [complete object destructor]
        mov     rax, QWORD PTR [rbp-8]
        mov     rdi, rax
        call    std::vector<long long, std::allocator<long long>>::~vector() [complete object destructor]
        nop
        leave
        ret
        .set    mathbase::~mathbase() [complete object destructor],mathbase::~mathbase() [base object destructor]
.LC13:
        .string "tour.in"
.LC14:
        .string "tour.out"
__static_initialization_and_destruction_0():
        push    rbp
        mov     rbp, rsp
        mov     edx, 8
        mov     esi, OFFSET FLAT:.LC13
        mov     edi, OFFSET FLAT:inf
        call    std::basic_ifstream<char, std::char_traits<char>>::basic_ifstream(char const*, std::_Ios_Openmode) [complete object constructor]
        mov     edx, OFFSET FLAT:__dso_handle
        mov     esi, OFFSET FLAT:inf
        mov     edi, OFFSET FLAT:std::basic_ifstream<char, std::char_traits<char>>::~basic_ifstream() [complete object destructor]
        call    __cxa_atexit
        mov     edx, 16
        mov     esi, OFFSET FLAT:.LC14
        mov     edi, OFFSET FLAT:ouf
        call    std::basic_ofstream<char, std::char_traits<char>>::basic_ofstream(char const*, std::_Ios_Openmode) [complete object constructor]
        mov     edx, OFFSET FLAT:__dso_handle
        mov     esi, OFFSET FLAT:ouf
        mov     edi, OFFSET FLAT:std::basic_ofstream<char, std::char_traits<char>>::~basic_ofstream() [complete object destructor]
        call    __cxa_atexit
        mov     edi, OFFSET FLAT:math
        call    mathbase::mathbase() [complete object constructor]
        mov     edx, OFFSET FLAT:__dso_handle
        mov     esi, OFFSET FLAT:math
        mov     edi, OFFSET FLAT:mathbase::~mathbase() [complete object destructor]
        call    __cxa_atexit
        nop
        pop     rbp
        ret
_GLOBAL__sub_I_inf:
        push    rbp
        mov     rbp, rsp
        call    __static_initialization_and_destruction_0()
        pop     rbp
        ret
)");