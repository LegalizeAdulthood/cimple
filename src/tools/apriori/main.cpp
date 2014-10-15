#define CIMPLE_NO_VERSION_SYMBOL
#include <cimple/config.h>
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cassert>

using namespace std;

static const char* argv0;
static char separator = ':';
static bool ignore_case = false;
static size_t hash_algorithm = 5;


//
// Spec loaded from file consisting of a string followed by an identifier.
//

struct Spec
{
    string str;
    string ident;

    friend bool operator<(const Spec& x, const Spec& y)
    {
        return 0;
    }
};

//
//  Information about a hash entry.
//

struct Info
{
    string str;
    string ident;
    size_t id;
    size_t code;

    friend bool operator<(const Info& x, const Info& y)
    {
        return x.code < y.code;
    }
};

//
// Hash function used to generate switch value.
//

#define HASH1 "n"
size_t hash1(const char* p, size_t n) { return n; }

#define HASH2 "p[0]"
size_t hash2(const char* p, size_t n) { return p[0]; }

#define HASH3 "p[n-1]"
size_t hash3(const char* p, size_t n) { return p[n-1]; }

#define HASH4 "n + p[0]"
size_t hash4(const char* p, size_t n) { return n + p[0]; }

#define HASH5 "n + p[0] + p[n-1]"
size_t hash5(const char* p, size_t n) { return n + p[0] + p[n-1]; }

#define HASH6 "n ^ p[0] ^ p[n-1]"
size_t hash6(const char* p, size_t n) { return n ^ p[0] ^ p[n-1]; }


//
// Emits the code for the string lookup function.
//

void emit_code(vector<Info>& v)
{
    size_t code = (size_t)-1;

    //
    // Generate enumerated type:
    //
    //     enum 
    //     {
    //        ...
    //     };
    //

    printf("enum\n");
    printf("{\n");

    for (size_t i = 0; i < v.size(); i++)
    {
        printf("    %s = %d,\n", v[i].ident.c_str(), int(v[i].id));
    }

    printf("};\n\n");

    //
    // Generate lookup function:
    //
    //     int lookup(const char* p, size_t n)
    //

    sort(v.begin(), v.end());

    printf("int lookup(const char* p, size_t n)\n");
    printf("{\n");

    const char* hash_str;

    switch (hash_algorithm)
    {
        case 1: hash_str = HASH1; break;
        case 2: hash_str = HASH2; break;
        case 3: hash_str = HASH3; break;
        case 4: hash_str = HASH4; break;
        case 5: hash_str = HASH5; break;
        case 6: hash_str = HASH6; break;
        default: assert(0);
    }; 
        
    printf("    size_t code = %s;\n", hash_str);

    printf("\n");
    printf("    switch(code)\n");
    printf("    {\n");

    for (size_t i = 0; i < v.size(); i++)
    {
        const Info& info = v[i];

        if (info.code != code)
        {
            code = info.code;
            printf("        ");
            printf("case %d:\n", int(code));
        }
        printf("            ");

        const char* str = info.str.c_str();
        size_t length = info.str.size();

        const char* func = ignore_case ? "equali" : "equal";

        printf("if (%s(\"%s\", %u, p, n))\n", func, str, int(length));
        printf("                ");
        printf("return %s;\n", info.ident.c_str());

        if (i + 1 == v.size() || info.code != v[i+1].code)
            printf("            break;\n");
    }

    printf("    }\n");
    printf("    return -1;\n");
    printf("}\n");
}

bool valid_ident(const char* ident)
{
    if (!isalpha(*ident) && *ident != '_')
        return false;

    while (isalnum(*ident) || *ident == '_')
        ident++;

    return *ident == '\0' ? true : false;
}

void load_spec_file(const char* filename, vector<Spec>& v)
{
    //
    // Open file.
    //

    ifstream is(filename);

    if (!is)
    {
        cerr << argv0 << ": error: ";
        cerr << "cannot open file: \"" << filename << "\"" << endl;
        exit(1);
    }

    //
    // Load the lines.
    //

    string line;

    for (size_t line_num = 1; getline(is, line); line_num++)
    {
        size_t pos = line.find(separator);

        if (pos == (size_t)-1)
        {
            cerr << argv0 << ": error: ";
            cerr << filename << "(" << line_num << "): ";
            cerr << "separator missing" << endl;
            exit(1);
        }

        string str = line.substr(0, pos);
        string ident = line.substr(pos + 1);

        if (str.size() < 1)
        {
            cerr << argv0 << ": error: ";
            cerr << filename << "(" << line_num << "): ";
            cerr << "separator missing" << endl;
            exit(1);
        }

        if (!valid_ident(ident.c_str()))
        {
            cerr << argv0 << ": error: ";
            cerr << filename << "(" << line_num << "): ";
            cerr << "illegal identifier: \"" << ident << "\"" << endl;
            exit(1);
        }

        Spec spec;
        spec.str = str;
        spec.ident = ident;
        v.push_back(spec);
    }
}

int get_opt(
    int& argc,
    char**& argv,
    const char* opt_name,
    char*& opt_value)
{
    opt_value = NULL;

    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], opt_name) == 0) 
        {
            if (i + 1 == argc)
                return -1;

            opt_value = argv[i+1];

            memmove(&argv[i], &argv[i+2], (argc - i - 1) * sizeof(char*));
            argc  -= 2;
            return 0;
        }
    }

    return 0;
}

int get_switch_opt(
    int& argc,
    char**& argv,
    const char* opt_name)
{
    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], opt_name) == 0) 
        {
            memmove(&argv[i], &argv[i+1], (argc - i) * sizeof(char*));
            argc--;
            return 0;
        }
    }

    return -1;
}

int main(int argc, char** argv)
{
    argv0 = argv[0];

    char* value = 0;

    if (get_opt(argc, argv, "-s", value) == -1)
    {
        cerr << argv0 << ": error: missing option argument" << endl;
        exit(1);
    }

    if (get_switch_opt(argc, argv, "-i") == 0)
        ignore_case = true;

    if (get_switch_opt(argc, argv, "-1") == 0)
        hash_algorithm = 1;

    if (get_switch_opt(argc, argv, "-2") == 0)
        hash_algorithm = 2;

    if (get_switch_opt(argc, argv, "-3") == 0)
        hash_algorithm = 3;

    if (get_switch_opt(argc, argv, "-4") == 0)
        hash_algorithm = 4;

    if (get_switch_opt(argc, argv, "-5") == 0)
        hash_algorithm = 5;

    if (get_switch_opt(argc, argv, "-6") == 0)
        hash_algorithm = 6;

    if (value)
    {
        if (strlen(value) != 1)
        {
            cerr << argv0 << ": error: bad argument for -s option" << endl;
            exit(1);
        }
        separator = value[0];
    }

    //
    // Check arguments.
    //

    if (argc != 2)
    {
        cerr << "usage: " << argv0 << " [options] spec-file" << endl;
        cerr << "options:" << endl;
        cerr << "   -s char -- use character as spec file separator" << endl;
        cerr << "   -i -- ignore case" << endl;
        cerr << "   -1 -- use hash algorithm 1" << endl;
        cerr << "   -2 -- use hash algorithm 2" << endl;
        cerr << "   -3 -- use hash algorithm 3" << endl;
        cerr << "   -4 -- use hash algorithm 4" << endl;
        cerr << "   -5 -- use hash algorithm 5 (default)" << endl;
        cerr << "   -6 -- use hash algorithm 6" << endl;
        cerr << endl;
        exit(1);
    }

    //
    // Load the specificationf file.
    //

    vector<Spec> specs;
    load_spec_file(argv[1], specs);

    //
    // Build an info vector.
    //

    vector<Info> v;

    for (size_t i = 0; i < specs.size(); i++)
    {
        const Spec& spec = specs[i];
        Info info;
        info.str = spec.str;
        info.ident = spec.ident;
        info.id = i;

        const char* p = spec.str.c_str();
        size_t n = spec.str.size();

        switch (hash_algorithm)
        {
            case 1: info.code = hash1(p,n);; break;
            case 2: info.code = hash2(p,n); break;
            case 3: info.code = hash3(p,n); break;
            case 4: info.code = hash4(p,n); break;
            case 5: info.code = hash5(p,n); break;
            case 6: info.code = hash6(p,n); break;
        }
        v.push_back(info);
    }

    //
    // Emit the code.
    //

    emit_code(v);

    return 0;
}

