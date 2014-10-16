#include <platform.h>
#define CIMPLE_NO_VERSION_SYMBOL
#include <cimple/config.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define MAX_BUFFER_SIZE 4096

#ifdef _WIN32
# define PATH_DELIMITER_CHAR ';'
# define X_OK 00
# include <windows.h>
# include <io.h>
# include <direct.h>
# define unlink _unlink
# define access _access
# define getcwd _getcwd
# define chdir _chdir
#else
# define PATH_DELIMITER_CHAR ':'
# include <unistd.h>
#endif

const char REVISION[] =
    "$Revision: 1.21 $";

const char CIMPLE_INFO[] = "cimpleinfo.out";
const char CIMPLE_INFO_TMP[] = "cimpleinfo.tmp";

static void put_rcs_log(FILE* os)
{
    fprintf(os, "REVISION=%s\n", REVISION);
    fputc('\n', os);
}

static void put_cimple_version(FILE* os)
{
    fprintf(os, "CIMPLE_VERSION_STRING=%s\n", CIMPLE_VERSION_STRING);
    fputc('\n', os);
}

static void put_platform(FILE* os)
{
    fprintf(os, "CIMPLE_PLATFORM_ID=%s\n", CIMPLE_PLATFORM_ID);
    fputc('\n', os);
}

static int execute(FILE* os, const char* command)
{
    int c;
    char buffer[MAX_BUFFER_SIZE];
    FILE* is;

    fprintf(os, "%s: ", command);

    sprintf(buffer, "%s > %s", command, CIMPLE_INFO_TMP);

    if (system(buffer) == -1)
        return -1;

    is = fopen(CIMPLE_INFO_TMP, "r");

    if (!is)
        return -1;

    while ((c = fgetc(is)) != EOF)
        fputc(c, os);

    fclose(is);

    unlink(CIMPLE_INFO_TMP);

    fputc('\n', os);
    fputc('\n', os);

    return 0;
}

static void put_uname(FILE* os)
{
    execute(os, "uname -a");
}

static void put_cimserver_version(FILE* os)
{
    execute(os, "cimserver -v");
}

static void put_env_var(FILE* os, const char* var)
{
    const char* env = getenv(var);

    if (env)
        fprintf(os, "%s=%s\n", var, env);
    else
        fprintf(os, "%s=(null)\n", var);

    fputc('\n', os);
}

static void put_env_vars(FILE* os)
{
    put_env_var(os, "PEGASUS_ROOT");
    put_env_var(os, "PEGASUS_PLATFORM");
    put_env_var(os, "PEGASUS_HOME");
    put_env_var(os, "PEGASUS_DEBUG");
    put_env_var(os, "PEGASUS_DEFAULT_ENABLE_OOP");
    put_env_var(os, "PEGASUS_DISABLE_PROV_USERCTXT");
    put_env_var(os, "PEGASUS_ENABLE_PRIVILEGE_SEPARATION");
    put_env_var(os, "PEGASUS_ROOT");
    put_env_var(os, "CIMPLE_MOF_PATH");
    put_env_var(os, "CIMPLE_ROOT");
    put_env_var(os, "PATH");
    put_env_var(os, "LD_LIBRARY_PATH");
}

static int _which_helper(
    const char* program,
    char path[MAX_BUFFER_SIZE])
{
    const char* p;

    /* Get the PATH environment variable. */

    p = getenv("PATH");

    if (p == NULL)
        return -1;

    /* Search each component of the path. */

    for (;;)
    {
        /* Set 'path' to next PATH compoment. */

        const char* q = strchr(p, PATH_DELIMITER_CHAR);

        *path = '\0';

        if (q)
            strncat(path, p, q - p);
        else
            strcat(path, p);

        /* Translate slashes */
        {
            char* p;

            for (p = path; *p; p++)
            {
                if (*p == '\\')
                    *p = '/';
            }
        }

        /* Change to current PATH component. */

        if (chdir(path) == 0)
        {
            /* Concatenate program name to current PATH compoment. */

            if (*path && path[strlen(path)-1] != '/')
                strcat(path, "/");

            strcat(path, program);

#ifdef _WIN32
            strcat(path, ".exe");
#endif

            /* Return with this path if executable. */

            if (access(path, X_OK) == 0)
                return 0;
        }

        if (!q)
            break;

        p = q + 1;
    }

    return -1;
}

static int _which(
    const char* program,
    char path[MAX_BUFFER_SIZE])
{
    char cwd[MAX_BUFFER_SIZE];
    int result;

    if (getcwd(cwd, sizeof(cwd)) == NULL)
        return -1;

    result = _which_helper(program, path);

    if (chdir(cwd) != 0)
        return -1;

    return result;
}

static void put_program_place(FILE* os, const char* program)
{
    char path[MAX_BUFFER_SIZE];

    if (_which(program, path) == 0)
        fprintf(os, "%s: %s\n", program, path);
    else
        fprintf(os, "%s: (null)\n", program);

    fputc('\n', os);
}

static void put_program_places(FILE* os)
{
    put_program_place(os, "cimserver");
    put_program_place(os, "CLI");
    put_program_place(os, "cimcli");
    put_program_place(os, "genclass");
    put_program_place(os, "genprov");
    put_program_place(os, "regmod");
    put_program_place(os, "cimpleinfo");
}

int main(int argc, char** argv)
{
    FILE* os;

    /* Usage: */

    if (argc != 1)
    {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        exit(1);
    }

    /* Open file. */

    os = fopen(CIMPLE_INFO, "w");

    if (!os)
    {
        fprintf(stderr, "%s: failed to open \"%s\"\n", argv[0], CIMPLE_INFO);
        exit(1);
    }

    /* Capture info. */

    put_rcs_log(os);
    put_cimple_version(os);
    put_platform(os);
#ifndef _WIN32
    put_uname(os);
#endif
    put_env_vars(os);
    put_program_places(os);
    put_cimserver_version(os);

    /* Close file. */

    fclose(os);

    printf("Created %s\n", CIMPLE_INFO);

    return 0;
}

CIMPLE_ID("$Header: /home/cvs/cimple/src/tools/cimpleinfo/main.cpp,v 1.21 2007/03/07 18:49:10 mbrasher-public Exp $");
