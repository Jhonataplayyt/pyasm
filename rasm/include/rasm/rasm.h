#include <keystone/keystone.h>
#include <iostream>
#include <vector>
#include <cstring>

#if defined(_WIN32)
#include <windows.h>
#else
#include <sys/mman.h>
#endif

void* alloc_exec_mem(std::size_t size) {
#if defined(_WIN32)
    return VirtualAlloc(nullptr, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
#else
    void* mem = mmap(nullptr, size, PROT_READ | PROT_WRITE | PROT_EXEC,
                     MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    return mem == MAP_FAILED ? nullptr : mem;
#endif
}

ks_arch detect_arch() {
#if defined(__x86_64__) || defined(_M_X64)
    return KS_ARCH_X86;
#elif defined(__i386__) || defined(_M_IX86)
    return KS_ARCH_X86;
#elif defined(__aarch64__) || defined(_M_ARM64)
    return KS_ARCH_ARM64;
#elif defined(__arm__) || defined(_M_ARM)
    return KS_ARCH_ARM;
#elif defined(__riscv) || defined(__riscv__)
    return KS_ARCH_RISCV;
#elif defined(__mips__) || defined(__mips) || defined(_M_MRX000)
    return KS_ARCH_MIPS;
#elif defined(__powerpc64__) || defined(__ppc64__) || defined(__PPC64__)
    return KS_ARCH_PPC;
#elif defined(__powerpc__) || defined(__ppc__) || defined(__PPC__)
    return KS_ARCH_PPC;
#else
    #error "Unsupported architecture automatically"
#endif
}

int detect_mode() {
#if defined(__x86_64__) || defined(_M_X64)
    return KS_MODE_64;
#elif defined(__i386__) || defined(_M_IX86)
    return KS_MODE_32;
#elif defined(__aarch64__) || defined(_M_ARM64)
    return KS_MODE_LITTLE_ENDIAN;
#elif defined(__arm__) || defined(_M_ARM)
    return KS_MODE_ARM;
#elif defined(__riscv) || defined(__riscv__)
    #if __riscv_xlen == 64
        return KS_MODE_RISCV64;
    #elif __riscv_xlen == 32
        return KS_MODE_RISCV32;
    #else
        return KS_MODE_RISCV128;
    #endif
#elif defined(__mips__) || defined(__mips) || defined(_M_MRX000)
    #if defined(__mips64) || defined(__mips64__)
        return KS_MODE_MIPS64;
    #else
        return KS_MODE_MIPS32;
    #endif
#elif defined(__powerpc64__) || defined(__ppc64__) || defined(__PPC64__)
    return KS_MODE_PPC64;
#elif defined(__powerpc__) || defined(__ppc__) || defined(__PPC__)
    return KS_MODE_PPC32;
#else
    #error "Unsupported mode automatically"
#endif
}

#if defined(_WIN32)

__declspec(dllexport) long _asm(const char *code) {
    ks_engine *ks;
    ks_err err = ks_open(detect_arch(), detect_mode(), &ks);
    if (err != KS_ERR_OK) {
        std::cerr << "Error starting Keystone\n";
        return -1;
    }
     
    unsigned char *encode;
    std::size_t size, count;

    if (ks_asm(ks, code, 0, &encode, &size, &count) != KS_ERR_OK) {
        std::cerr << "Error while mounting code\n";
        ks_close(ks);
        return -1;
    }

    void* mem = alloc_exec_mem(size);
    if (!mem) {
        std::cerr << "Failed to allocate executable memory\n";
        ks_free(encode);
        ks_close(ks);
        return -1;
    }

    std::memcpy(mem, encode, size);

    auto func = (long(*)())mem;
    long result = func();

    ks_free(encode);
    ks_close(ks);

    return result;
}

#else

long _asm(const char *code) {
    ks_engine *ks;
    ks_err err = ks_open(detect_arch(), detect_mode(), &ks);
    if (err != KS_ERR_OK) {
        std::cerr << "Error starting Keystone\n";
        return -1;
    }
     
    unsigned char *encode;
    std::size_t size, count;

    if (ks_asm(ks, code, 0, &encode, &size, &count) != KS_ERR_OK) {
        std::cerr << "Error while mounting code\n";
        ks_close(ks);
        return -1;
    }

    void* mem = alloc_exec_mem(size);
    if (!mem) {
        std::cerr << "Failed to allocate executable memory\n";
        ks_free(encode);
        ks_close(ks);
        return -1;
    }

    std::memcpy(mem, encode, size);

    auto func = (long(*)())mem;
    long result = func();

    ks_free(encode);
    ks_close(ks);

    return result;
}

#endif
