#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <windows.h>
#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/utime.h>
#include <fcntl.h>

#pragma warning(disable : 4996)

const char* arg0;

void echo_command(int argc, char** argv)
{
    // Carry out operation:

    for (int i = 1; i < argc; i++)
    {
        const char* p = argv[i];

        for (; *p; p++)
        {
            if (*p == '\\')
            {
                p++;

                switch (*p)
                {
                    case 'a': 
                        putchar('\a'); 
                        break;
                    case 'b': 
                        putchar('\b'); 
                        break;
                    case 'n': 
                        putchar('\n'); 
                        break;
                    case 'r': 
                        putchar('\r'); 
                        break;
                    case 't': 
                        putchar('\t'); 
                        break;
                    case 'c': 
                        // Circumvent newline below.
                        return;
                    case '\0': 
                        return;
                    default: 
                        putchar('\\');
                        putchar(*p);
                        break;
                }
            }
            else
                putchar(*p);
        }

        if (i + 1 != argc)
            putchar(' ');
    }

    putchar('\n');
}

void pwd_command(int argc, char** argv)
{
    // Check usage:

    if (argc != 1)
    {
        fprintf(stderr, "Usage: %s %s\n", arg0, argv[0]);
        exit(1);
    }

    // Carry out operation:

    char buffer[1024];

    DWORD r = GetCurrentDirectory(sizeof(buffer), buffer);

    for (size_t i = 0; i < r; i++)
    {
        if (buffer[i] == '\\')
            buffer[i] = '/';
    }

    printf("%s\n", buffer);
}

void mkdirhier_command(int argc, char** argv)
{
    // Check usage:

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s %s path\n", arg0, argv[0]);
        exit(1);
    }

    char* path = argv[1];

    // Add drive letter as first component (e.g., "C:/")

    const size_t MAX_DIRS = 128;
    const char* dirs[MAX_DIRS];
    size_t num_dirs = 0;
    char dir[4];

    if (isalpha(path[0]) && path[1] == ':' && path[2] == '/')
    {
        dir[0] = path[0];
        dir[1] = ':';
        dir[2] = '/';
        dir[3] = '\0';
        path += 3;

        dirs[num_dirs++] = dir;
    }
    else if (*path == '/')
    {
        dirs[num_dirs++] = "/";
        path++;
    }

    for (char* p = strtok(path, "/"); p; p = strtok(NULL, "/"))
    {
        assert(num_dirs < MAX_DIRS);
        dirs[num_dirs++] = p;
    }

    // Create directories along path that do not exist.

    for (size_t i = 0; i < num_dirs; i++)
    {
        const char* dir = dirs[i];

        if (!SetCurrentDirectory(dir))
        {
            if (!CreateDirectory(dir, NULL))
            {
                fprintf(stderr, "%s %s: 1failed", arg0, argv[0]);
                exit(1);
            }

            if (!SetCurrentDirectory(dir))
            {
                fprintf(stderr, "%s %s: 2failed", arg0, argv[0]);
                exit(1);
            }
        }
    }

}

void rm_command(int argc, char** argv)
{
    // Check usage:

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s %s path...\n", arg0, argv[0]);
        exit(1);
    }

    // Remove all those files:

    for (int i = 1; i < argc; i++)
        DeleteFile(argv[i]);
}

bool is_dir(const char* path)
{
    struct stat st;
    return stat(path, &st) == 0 && (_S_IFDIR & st.st_mode);
}

void touch_command(int argc, char** argv)
{
    // Check usage:

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s %s path...\n", arg0, argv[0]);
        exit(1);
    }

    // Touch all those files:

    for (int i = 1; i < argc; i++)
    {
        const char* path = argv[i];

        if (is_dir(path))
        {
            fprintf(stderr, "%s %s: attempt to touch directory: %s", 
                arg0, argv[0], path);
            exit(1);
        }

        // If file does not exist:

        struct stat st;

        if (stat(path, &st) != 0)
        {
            int fd = open(path, O_WRONLY | O_CREAT, 0666);

            if (fd < 0)
            {
                fprintf(stderr, "%s %s: failed to create %s", 
                    arg0, argv[0], path);
                exit(1);
            }

            close(fd);
        }

        // Set file's time to current time (use NULL).
        // to be used.

        if (_utime(path, NULL) != 0)
        {
            fprintf(stderr, "%s %s: failed to set time on %s", 
                arg0, argv[0], path);
            exit(1);
        }
    }
}

void full_command(int argc, char** argv)
{
    // Check usage:

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s %s path\n", arg0, argv[0]);
        exit(1);
    }

    char path[1024];
    char* name = 0;

    DWORD r = GetFullPathName(argv[1], sizeof(path), path, NULL);

    if (r == 0)
    {
        fprintf(stderr, "%s %s: failed: %s", arg0, argv[0], argv[1]);
        exit(1);
    }

    for (size_t i = 0; i < r; i++)
    {
        if (path[i] == '\\')
            path[i] = '/';
    }

    printf("%s\n", path);

}

int main(int argc, char** argv)
{
    arg0 = argv[0];

    // Check arguments.

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s command arguments...\n", arg0);
        fprintf(stderr, "\n");
        fprintf(stderr, "Where command is one of these:\n");
        fprintf(stderr, "    echo\n");
        fprintf(stderr, "    pwd\n");
        fprintf(stderr, "    rm\n");
        fprintf(stderr, "    mkdirhier\n");
        fprintf(stderr, "    touch\n");
        exit(1);
    }

    // Dispatch command:

    if (strcmp(argv[1], "echo") == 0)
        echo_command(argc - 1, argv + 1);
    else if (strcmp(argv[1], "pwd") == 0)
        pwd_command(argc - 1, argv + 1);
    else if (strcmp(argv[1], "rm") == 0)
        rm_command(argc - 1, argv + 1);
    else if (strcmp(argv[1], "mkdirhier") == 0)
        mkdirhier_command(argc - 1, argv + 1);
    else if (strcmp(argv[1], "touch") == 0)
        touch_command(argc - 1, argv + 1);
    else if (strcmp(argv[1], "full") == 0)
        full_command(argc - 1, argv + 1);

    return 0;
}
