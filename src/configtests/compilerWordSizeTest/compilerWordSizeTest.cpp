/*
    The purpose of this code is to test compile with 64 bit Microsoft compiler.
    It determines whether the platform variable is compatible with the selected 32 or
    64 bit compiler.  If they match, the compile completes normally.  If they are
    different, generates a compiler error.

    Note that this is expected to be called directly and the generated code is not used.
*/

int main(int argc, char** argv)
{

// If 64 bit windows platform defined, confirm that the compiler is 64 bit
#if defined(WIN64_X86_64_MSVC)
#    if defined(_WIN64)
#    else
#    error Expecting 64 bit compiler with _WIN64 defined
#    endif

#elif defined(WIN64_IA64_MSVC)
#    if defined(_WIN64)
#    else
#    error Expecting 64 bit compiler with _WIN64 defined
#    endif

#elif defined(WIN32_IX86_MSVC)
#    if defined(_WIN64)
#    error Expecting 32 bit compiler with _WIN64 NOT defined
#    else
#    endif

#else
#    error invalid windows platform definition
#endif
    return 0;
}

