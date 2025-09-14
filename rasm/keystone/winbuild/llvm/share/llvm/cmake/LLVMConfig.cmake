# This file provides information and services to the final user.


# LLVM_BUILD_* values available only from LLVM build tree.
set(LLVM_BUILD_BINARY_DIR "/workspaces/codespaces-blank/pyasm/rasm/keystone/winbuild/llvm")
set(LLVM_BUILD_LIBRARY_DIR "/workspaces/codespaces-blank/pyasm/rasm/keystone/winbuild/llvm/./lib")
set(LLVM_BUILD_MAIN_INCLUDE_DIR "/workspaces/codespaces-blank/pyasm/rasm/keystone/llvm/include")
set(LLVM_BUILD_MAIN_SRC_DIR "/workspaces/codespaces-blank/pyasm/rasm/keystone/llvm")


set(LLVM_VERSION_MAJOR 3)
set(LLVM_VERSION_MINOR 9)
set(LLVM_VERSION_PATCH 0)
set(LLVM_PACKAGE_VERSION 3.9.0svn)

set(LLVM_COMMON_DEPENDS )

set(LLVM_AVAILABLE_LIBS )

set(LLVM_ALL_TARGETS AArch64;ARM;Hexagon;Mips;PowerPC;Sparc;SystemZ;X86;RISCV)

set(LLVM_TARGETS_TO_BUILD AArch64;ARM;Hexagon;Mips;PowerPC;Sparc;SystemZ;X86;RISCV)

set(LLVM_TARGETS_WITH_JIT )



set(TARGET_TRIPLE "x86_64-w64-mingw32")

set(LLVM_ABI_BREAKING_CHECKS WITH_ASSERTS)

set(LLVM_ENABLE_ASSERTIONS ON)

set(LLVM_ENABLE_EH OFF)

set(LLVM_ENABLE_RTTI OFF)

set(LLVM_ENABLE_TERMINFO ON)

set(LLVM_ENABLE_THREADS ON)

set(LLVM_ENABLE_ZLIB 0)

set(LLVM_NATIVE_ARCH X86)

set(LLVM_ENABLE_PIC ON)

set(LLVM_ENABLE_PLUGINS ON)
set(LLVM_PLUGIN_EXT .dll)

set(LLVM_ON_UNIX 0)
set(LLVM_ON_WIN32 1)

set(LLVM_LIBDIR_SUFFIX )

set(LLVM_INCLUDE_DIRS "/workspaces/codespaces-blank/pyasm/rasm/keystone/llvm/include;/workspaces/codespaces-blank/pyasm/rasm/keystone/winbuild/llvm/include")
set(LLVM_LIBRARY_DIRS "/workspaces/codespaces-blank/pyasm/rasm/keystone/winbuild/llvm/./lib")
set(LLVM_DEFINITIONS "-D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS")
set(LLVM_CMAKE_DIR "/workspaces/codespaces-blank/pyasm/rasm/keystone/llvm/cmake/modules")
set(LLVM_TOOLS_BINARY_DIR "/workspaces/codespaces-blank/pyasm/rasm/keystone/winbuild/llvm/./bin")

if(NOT TARGET LLVMSupport)
  include("/workspaces/codespaces-blank/pyasm/rasm/keystone/winbuild/llvm/share/llvm/cmake/LLVMExports.cmake")
endif()

include(${LLVM_CMAKE_DIR}/LLVM-Config.cmake)
