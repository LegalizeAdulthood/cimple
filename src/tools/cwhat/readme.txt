    This utility searches a file for strings that begin with the pattern
    \"@(%s)\" and end with a null character. These strings are printed to
    standard output. It is similar to the Unix \"what\" utility.\n\

    CIMPLE injects these strings into programs and libraries, so that useful
    information can be obtained in the field (e.g., version).

    Example:
    %% cimple_version libcimple.so\n\
    0.98-beta\n\
