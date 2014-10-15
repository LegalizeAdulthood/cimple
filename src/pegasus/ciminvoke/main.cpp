/*
**==============================================================================
**
** Copyright (c) 2003, 2004, 2005, 2006, Michael Brasher, Karl Schopmeyer
** 
** Permission is hereby granted, free of charge, to any person obtaining a
** copy of this software and associated documentation files (the "Software"),
** to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense,
** and/or sell copies of the Software, and to permit persons to whom the
** Software is furnished to do so, subject to the following conditions:
** 
** The above copyright notice and this permission notice shall be included in
** all copies or substantial portions of the Software.
** 
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
** SOFTWARE.
**
**==============================================================================
*/

#include <cassert>
#include <cstdarg>
#include <cstdio>
#include <getopt.h>
#include <cimple/config.h>
#include <Pegasus/Common/Config.h>
#include <Pegasus/Client/CIMClient.h>

#define ARG0 "ciminvoke"

PEGASUS_USING_PEGASUS;
PEGASUS_USING_STD;

bool help_opt = false;
bool print_opt = false;
String name_space_opt = "root/cimv2";

const char USAGE[] = "\
\n\
Usage: %s [OPTIONS] object-path method-name [param=VALUE]...\n\
\n\
OPTIONS:\n\
    -V              Print CIMPLE version.\n\
    -h              Print this help message.\n\
    -p              Print method signature and quit (do not call method).\n\
    -n  NAMESPACE   Call method in this namespace.\n\
\n";

class Str
{
public:

    Str(const String& s) : _cstr(s.getCString()) { }
    Str(const CIMName& n) : _cstr(n.getString().getCString()) { }
    Str(const CIMNamespaceName& n) : _cstr(n.getString().getCString()) { }
    Str(const Exception& e) : _cstr(e.getMessage().getCString()) { }
    Str(const CIMDateTime& x) : _cstr(x.toString().getCString()) { }
    ~Str() { }
    const char* operator*() const { return (const char*)_cstr; }
    operator const char*() const { return (const char*)_cstr; }
private:
    CString _cstr;
};

static
CIMPLE_PRINTF_ATTR(1, 2)
void err(const char* format, ...)
{
    fputc('\n', stderr);
    va_list ap;
    fprintf(stderr, "%s[%s]: ", ARG0, CIMPLE_VERSION_STRING);
    va_start(ap, format);
    vfprintf(stderr, format, ap);
    va_end(ap);
    fputc('\n', stderr);
    fputc('\n', stderr);
    exit(1);
}

bool test_in(const CIMConstParameter& param)
{
    Uint32 pos = param.findQualifier("In");

    if (pos == PEG_NOT_FOUND)
        return true;

    CIMConstQualifier qual = param.getQualifier(pos);
    CIMValue value = qual.getValue();

    if (value.getType() == CIMTYPE_BOOLEAN)
    {
        bool in;
        value.get(in);
        return in;
    }

    return true;
}

bool test_out(const CIMConstParameter& param)
{
    Uint32 pos = param.findQualifier("Out");

    if (pos == PEG_NOT_FOUND)
        return false;

    CIMConstQualifier qual = param.getQualifier(pos);
    CIMValue value = qual.getValue();

    if (value.getType() == CIMTYPE_BOOLEAN)
    {
        bool out;
        value.get(out);
        return out;
    }

    return false;
}

void print_method(
    const CIMMethod& method)
{
    CIMType type = method.getType();

    printf("\n");
    printf("%s %s(\n", cimTypeToString(type), *Str(method.getName()));

    for (Uint32 i = 0; i < method.getParameterCount(); i++)
    {
        CIMConstParameter p = method.getParameter(i);
        CIMType type = p.getType();

        printf("    ");

        // Qualifiers.

        bool in = test_in(p);

        if (in)
            printf("[In(true), ");
        else
            printf("[In(false), ");

        bool out = test_out(p);

        if (out)
            printf("Out(true)] ");
        else
            printf("Out(false)] ");

        // Type and value.

        if (type == CIMTYPE_REFERENCE)
        {
            CIMName cn = p.getReferenceClassName();
            printf("%s REF %s", *Str(cn), *Str(p.getName()));
        }
        else
            printf("%s %s", cimTypeToString(type), *Str(p.getName()));

        if (p.isArray())
            printf("[]");

        if (i + 1 == method.getParameterCount())
            printf(");");
        else
            printf(",");

        printf("\n");
    }

    printf("\n");
}

int convert_scalar(
    CIMType type,
    const String& value,
    CIMValue& v)
{
    Str str(value);
    const char* s = str;

    switch (type)
    {
        case CIMTYPE_BOOLEAN:
        {
            if (strcasecmp(s, "true") == 0)
                v = CIMValue(true);
            else if (strcasecmp(s, "false") == 0)
                v = CIMValue(false);
            else
                return -1;
            return 0;
        }

        case CIMTYPE_UINT8:
        {
            char* end;
            unsigned long x = strtoul(s, &end, 0);

            if (*end != '\0')
                return -1;

            v = CIMValue(Uint8(x));
            return 0;
        }

        case CIMTYPE_UINT16:
        {
            char* end;
            unsigned long x = strtoul(s, &end, 0);

            if (*end != '\0')
                return -1;

            v = CIMValue(Uint16(x));
            return 0;
        }

        case CIMTYPE_SINT16:
        {
            char* end;
            long x = strtol(s, &end, 0);

            if (*end != '\0')
                return -1;

            v = CIMValue(Sint16(x));
            return 0;
        }

        case CIMTYPE_UINT32:
        {
            char* end;
            unsigned long x = strtoul(s, &end, 0);

            if (*end != '\0')
            {
                return -1;
            }

            v = CIMValue(Uint32(x));
            return 0;
        }

        case CIMTYPE_SINT32:
        {
            char* end;
            long x = strtol(s, &end, 0);

            if (*end != '\0')
                return -1;

            v = CIMValue(Sint32(x));
            return 0;
        }

        case CIMTYPE_UINT64:
        {
            char* end;
            unsigned long x = strtoul(s, &end, 0);

            if (*end != '\0')
                return -1;

            v = CIMValue(Uint64(x));
            return 0;
        }

        case CIMTYPE_SINT64:
        {
            char* end;
            long x = strtol(s, &end, 0);

            if (*end != '\0')
                return -1;

            v = CIMValue(Sint64(x));
            return 0;
        }

        case CIMTYPE_REAL32:
        {
            char* end;
            double x = strtod(s, &end);

            if (*end != '\0')
                return -1;

            v = CIMValue(Real32(x));
            return 0;
        }

        case CIMTYPE_REAL64:
        {
            char* end;
            double x = strtod(s, &end);

            if (*end != '\0')
                return -1;

            v = CIMValue(Real64(x));
            return 0;
        }

        case CIMTYPE_CHAR16:
        {
            if (value.size() != 1)
                return -1;

            v = CIMValue(value[0]);
            return 0;
        }

        case CIMTYPE_STRING:
            v = CIMValue(value);
            return 0;

        case CIMTYPE_DATETIME:
        {
            CIMDateTime x;

            try
            {
                x = CIMDateTime(value);
            }
            catch (...)
            {
                return -1;
            }
            v = CIMValue(x);
            return 0;
        }

        case CIMTYPE_REFERENCE:
        {
            CIMObjectPath x;

            try
            {
                x = CIMObjectPath(value);
            }
            catch (...)
            {
                return -1;
            }
            v = CIMValue(x);
            return 0;
        }

        default:
            return -1;
    }

    // Unreachable!
    return 0;
}

template<class T>
int append_array_value_aux(CIMValue& acv, const CIMValue& cv, T* tag)
{
    try
    {
        Array<T> array;
        acv.get(array);

        T scalar;
        cv.get(scalar);

        array.append(scalar);
        acv.set(array);
        return 0;
    }
    catch (...)
    {
        return -1;
    }

    return 0;
}

int append_array_value(CIMValue& acv, const CIMValue& cv)
{
    if (acv.getType() != cv.getType())
        return -1;

    if (!acv.isArray())
        return -1;

    if (cv.isArray())
        return -1;

    switch (acv.getType())
    {
        case CIMTYPE_BOOLEAN:
            return append_array_value_aux(acv, cv, (Boolean*)0);

        case CIMTYPE_UINT8:
            return append_array_value_aux(acv, cv, (Uint8*)0);

        case CIMTYPE_SINT8:
            return append_array_value_aux(acv, cv, (Sint8*)0);

        case CIMTYPE_UINT16:
            return append_array_value_aux(acv, cv, (Uint16*)0);

        case CIMTYPE_SINT16:
            return append_array_value_aux(acv, cv, (Sint16*)0);

        case CIMTYPE_UINT32:
            return append_array_value_aux(acv, cv, (Uint32*)0);

        case CIMTYPE_SINT32:
            return append_array_value_aux(acv, cv, (Sint32*)0);

        case CIMTYPE_UINT64:
            return append_array_value_aux(acv, cv, (Uint64*)0);

        case CIMTYPE_SINT64:
            return append_array_value_aux(acv, cv, (Sint64*)0);

        case CIMTYPE_REAL32:
            return append_array_value_aux(acv, cv, (Real32*)0);

        case CIMTYPE_REAL64:
            return append_array_value_aux(acv, cv, (Real64*)0);

        case CIMTYPE_CHAR16:
            return append_array_value_aux(acv, cv, (Char16*)0);

        case CIMTYPE_STRING:
            return append_array_value_aux(acv, cv, (String*)0);

        case CIMTYPE_DATETIME:
            return append_array_value_aux(acv, cv, (CIMDateTime*)0);

        case CIMTYPE_REFERENCE:
            return append_array_value_aux(acv, cv, (CIMObjectPath*)0);

        default:
            return -1;
    }

    // Unreachable!
    return 0;
}

void convert_params(
    int argc, 
    char** argv, 
    const CIMMethod& method,
    Array<CIMParamValue>& params)
{
    params.clear();

    for (int i = 0; i < argc; i++)
    {
        // Split into name-value.

        const char* arg = argv[i];
        const char* eq = strchr(arg, '=');

        if (!eq)
            err("malformed argument: %s\n", arg);

        String name(arg, eq - arg);
        String value(eq + 1);

        try
        {
            CIMName tmp(name);
        }
        catch (...)
        {
            err("invalid parameter name: %s\n", *Str(name));
        }

        // Find the corresponding parameter.

        Uint32 pos = method.findParameter(name);

        if (pos == PEG_NOT_FOUND)
            err("no such parameter: %s\n", *Str(name));

        CIMConstParameter param = method.getParameter(pos);

        // Be sure it is an input parameter.

        if (!test_in(param))
            err("not an input parameter: %s\n", *Str(name));

        // Convert to a param value.

        CIMValue cv;

        if (convert_scalar(param.getType(), value, cv) != 0)
            err("bad value for parameter: %s\n", *Str(name));

        if (param.isArray())
        {
            Uint32 pos = PEG_NOT_FOUND;

            for (Uint32 i = 0; i < params.size(); i++)
            {
                if (params[i].getParameterName() == name)
                {
                    pos = i;
                    break;
                }
            }

            if (pos == PEG_NOT_FOUND)
            {
                CIMValue acv(param.getType(), true);

                if (append_array_value(acv, cv) != 0)
                    err("bad array parameter: %s\n", *Str(name));

                params.append(CIMParamValue(name, acv));
            }
            else
            {
                CIMValue acv = params[pos].getValue();

                if (append_array_value(acv, cv) != 0)
                    err("bad array parameter: %s\n", *Str(name));

                params[pos] = CIMParamValue(name, acv);
            }
        }
        else
        {
            for (Uint32 i = 0; i < params.size(); i++)
            {
                if (params[i].getParameterName() == name)
                    err("duplicate parameter: %s\n", *Str(name));
            }

            params.append(CIMParamValue(name, cv));
        }
    }
}

void print_method_names(const CIMClass& clss)
{
    for (Uint32 i = 0; i < clss.getMethodCount(); i++)
    {
        CIMConstMethod m = clss.getMethod(i);
        printf("%s()\n", *Str(m.getName()));
    }
}

void print_scalar(const String& name, const CIMValue& v)
{
    printf("%s=", *Str(name));

    switch (v.getType())
    {
        case CIMTYPE_BOOLEAN:
        {
            Boolean x;
            v.get(x);
            if (x)
                printf("true");
            else
                printf("false");
            break;
        }

        case CIMTYPE_UINT8:
        {
            Uint8 x;
            v.get(x);
            printf("%d", x);
            break;
        }

        case CIMTYPE_SINT8:
        {
            Sint8 x;
            v.get(x);
            printf("%u", x);
            break;
        }

        case CIMTYPE_UINT16:
        {
            Uint16 x;
            v.get(x);
            printf("%d", x);
            break;
        }

        case CIMTYPE_SINT16:
        {
            Sint16 x;
            v.get(x);
            printf("%u", x);
            break;
        }

        case CIMTYPE_UINT32:
        {
            Uint32 x;
            v.get(x);
            printf("%d", x);
            break;
        }

        case CIMTYPE_SINT32:
        {
            Sint32 x;
            v.get(x);
            printf("%u", x);
            break;
        }

        case CIMTYPE_UINT64:
        {
            Uint64 x;
            v.get(x);
            printf(CIMPLE_LLU, x);
            break;
        }

        case CIMTYPE_SINT64:
        {
            Sint64 x;
            v.get(x);
            printf(CIMPLE_LLD, x);
            break;
        }

        case CIMTYPE_REAL32:
        {
            Real32 x;
            v.get(x);
            printf("%f", x);
            break;
        }

        case CIMTYPE_REAL64:
        {
            Real64 x;
            v.get(x);
            printf("%lf", x);
            break;
        }

        case CIMTYPE_CHAR16:
        {
            Char16 x;
            v.get(x);
            printf("%d", Uint32(x));
            break;
        }

        case CIMTYPE_STRING:
        {
            String x;
            v.get(x);
            printf("%s", *Str(x));
            break;
        }

        case CIMTYPE_DATETIME:
        {
            CIMDateTime x;
            v.get(x);
            printf("%s", *Str(x.toString()));
            break;
        }

        case CIMTYPE_REFERENCE:
        {
            CIMObjectPath x;
            v.get(x);
            printf("%s", *Str(x.toString()));
            break;
        }

        default:
            break;
    }

    printf("\n");
}

template<class T>
void print_array_aux(const String& name, const CIMValue& v, T* tag)
{
    Array<T> x;
    v.get(x);

    for (Uint32 i = 0; i < x.size(); i++)
        print_scalar(name, CIMValue(x[i]));
}

void print_array(const String& name, const CIMValue& v)
{
    switch (v.getType())
    {
        case CIMTYPE_BOOLEAN:
            print_array_aux(name, v, (Boolean*)0);
            break;

        case CIMTYPE_UINT8:
            print_array_aux(name, v, (Uint8*)0);
            break;

        case CIMTYPE_SINT8:
            print_array_aux(name, v, (Sint8*)0);
            break;

        case CIMTYPE_UINT16:
            print_array_aux(name, v, (Uint16*)0);
            break;

        case CIMTYPE_SINT16:
            print_array_aux(name, v, (Sint16*)0);
            break;

        case CIMTYPE_UINT32:
            print_array_aux(name, v, (Uint32*)0);
            break;

        case CIMTYPE_SINT32:
            print_array_aux(name, v, (Sint32*)0);
            break;

        case CIMTYPE_UINT64:
            print_array_aux(name, v, (Uint64*)0);
            break;

        case CIMTYPE_SINT64:
            print_array_aux(name, v, (Sint64*)0);
            break;

        case CIMTYPE_REAL32:
            print_array_aux(name, v, (Real32*)0);
            break;

        case CIMTYPE_REAL64:
            print_array_aux(name, v, (Real64*)0);
            break;

        case CIMTYPE_CHAR16:
            print_array_aux(name, v, (Char16*)0);
            break;

        case CIMTYPE_STRING:
            print_array_aux(name, v, (String*)0);
            break;

        case CIMTYPE_DATETIME:
            print_array_aux(name, v, (CIMDateTime*)0);
            break;

        case CIMTYPE_REFERENCE:
            print_array_aux(name, v, (CIMObjectPath*)0);
            break;

        default:
            break;
    }
}

void print_value(const String& name, const CIMValue& v)
{
    if (v.isArray())
        print_array(name, v);
    else
        print_scalar(name, v);
}

int main(int argc, char** argv)
{
    // Options:

    int opt;

    while ((opt = getopt(argc, argv, "n:hVp")) != -1)
    {
        switch (opt)
        {
            case 'n':
                name_space_opt = optarg;
                break;

            case 'h':
                help_opt = true;
                break;

            case 'V':
                printf("%s\n", CIMPLE_VERSION_STRING);
                exit(0);
                break;

            case 'p':
                print_opt = true;
                break;

            default:
                err("unknown option: -%c\n", opt);
                break;
        }
    }

    argc -= optind - 1;
    argv += optind - 1;

    // check arguments.

    if (argc < 2 || help_opt)
    {
        fprintf(stderr, (const char*)USAGE, ARG0);
        exit(1);
    }

    // Connect to server.

    CIMClient client;

    try
    {
        client.connectLocal();
    }
    catch(Exception& e)
    {
        err("failed to connect to CIM server (%s)\n", *Str(e));
    }

    // Check object-path argument.

    CIMObjectPath object_path;

    try
    {
        object_path = CIMObjectPath(argv[1]);
    }
    catch (...)
    {
        err("malformed object-path argument: %s\n", argv[1]);
    }

    // Get class from server.

    CIMClass clss;

    try
    {
        clss = client.getClass(
            name_space_opt, object_path.getClassName(), false);
    }
    catch (Exception& e)
    {
        err("failed to get class from server (%s)\n", *Str(e));
    }

    // If no method, then echo the methods out.

    if (argc < 3 && print_opt)
    {
        print_method_names(clss);
        exit(0);
    }

    if (argc < 3)
    {
        fprintf(stderr, (const char*)USAGE, ARG0);
        exit(1);
    }

    // Check object-path argument.

    CIMName method_name;

    try
    {
        method_name = CIMName(argv[2]);
    }
    catch (...)
    {
        err("malformed method-name argument (%s)\n", argv[2]);
    }

    // Get method.

    CIMMethod method;
    {
        Uint32 pos = clss.findMethod(method_name);

        if (pos == PEG_NOT_FOUND)
        {
            err("no such method: %s\n", *Str(method_name));
        }

        method = clss.getMethod(pos);
    }
    
    // Print method?

    if (print_opt)
    {
        print_method(method);
        exit(0);
    }

    // Convert parameters.

    Array<CIMParamValue> in_params;

    convert_params(argc - 3, argv + 3, method, in_params);

    // Invoke.

    try
    {
        // Connect.

        CIMClient client;
        client.connectLocal();

        // Define input arguments:

        Array<CIMParamValue> out_params;

        // Invoke the method:

        CIMValue value = client.invokeMethod(
            name_space_opt,
            object_path,
            method_name,
            in_params,
            out_params);

        // Print result.

        print_value("return", value);

        for (Uint32 i = 0; i < out_params.size(); i++)
        {
            print_value(
                out_params[i].getParameterName(), out_params[i].getValue());
        }

        printf("\n");
    }
    catch(Exception& e)
    {
        PEGASUS_STD(cerr) << "Error: " << e.getMessage() << PEGASUS_STD(endl);
        exit(1);
    }

    return 0;
}
