/*
**==============================================================================
**
** Copyright (c) 2009, Michael Brasher, Karl Schopmeyer
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

/* Display information from the Pegasus provider registration
    Note that this requires a live Pegasus server and only work with
    Pegasus because provider registration is proprietary with the
    current DMTF schemas
*/
/*
    TODO
        add regex for module name matching.
        Add verbose mode with more detailed information
*/
#define TR printf("TRACE %s\n", __LINE__);
#include <cimple/config.h>
#include <pegasus/utils/pegasus.h>
#include <Pegasus/Client/CIMClient.h>
#include <Pegasus/Common/CIMPropertyList.h>
#include <Pegasus/Common/StringConversion.h>
#include <string>
#include <sys/types.h>
#include <dlfcn.h>
#include <sys/stat.h>
#include <getopt.h>
#include <cstdarg>
#include <vector>
#include <cstdio>
#include <dirent.h>
#include <unistd.h>
#include <cimple/cimple.h>
#include <cimple/Provider_Handle.h>
#include <pegasus/utils/Str.h>
#include <util/util.h>
#include "usage.h"

#define INTEROP_NAMESPACE "root/PG_InterOp"
#define DEFAULT_PROVIDING_NAMESPACE "root/cimv2"
#define PROVIDER_MODULE_CLASSNAME "PG_PROVIDER_MODULE";
#define PROVIDER_CLASSNAME "PG_Provider"
#define CAPABILITIES_CLASSNAME "PG_ProviderCapabilities"

#define TRX printf("TRACE %u\n", __LINE__)

using namespace std;
using namespace Pegasus;

//------------------------------------------------------------------------------
//
// Options:
//
//------------------------------------------------------------------------------

bool class_opt = false;
bool module_opt = false;
String module_to_display;
bool verbose_opt = false;
bool help_opt = false;
bool summary_opt = false;
bool null_opt = false;
Array<String> target_classlist;

//------------------------------------------------------------------------------
//
// print() - Print an instance or its elements. Note that this is incomplete
// and only prints DateTime, boolean, and String data types specifically.
// All others are driven by the template
//
//------------------------------------------------------------------------------

template<class T>
static void _print_elem( T x )
{
    cout << x;
}

static void _print_elem(const String& x)
{
    cout << '"' << x << '"';
}

static void _print_elem(Boolean x)
{
    cout << x ? "true" : "false";
}
static void _print_elem(CIMObjectPath& x)
{
    cout << x.toString();
}
static void _print_elem(const CIMDateTime& x)
{
    cout << x.toString();
}

/*
    Print a CIMValue output. Template to be generated for every
    used CIMType.
*/
template<class T>
static void _print_cimValue(const CIMValue& v, T*)
{
    if (v.isNull())
    {
        cout << "NULL;";
        return;
    }

    if (v.isArray())
    {
        Array<T> x;
        v.get(x);

        cout << "{";

        for (Uint32 i = 0; i < x.size(); i++)
        {
            _print_elem(x[i]);

            if (i + 1 != x.size())
                cout << ",";
        }

        cout << "};";
    }
    else
    {
        T x;
        v.get(x);
        _print_elem(x);
        cout << ';';
    }
}

// print a complete instance out

void print(CIMInstance& inst, bool showNullValues = true)
{
    cout << "instance of " << inst.getClassName().getString() << endl;
    cout << "{" << endl;

    for (Uint32 i = 0; i < inst.getPropertyCount(); i++)
    {
        CIMProperty prop = inst.getProperty(i);

        // Output the name:

        cout << "    " << prop.getName().getString() << " = ";

        const CIMValue& v = prop.getValue();

        if (v.isNull() && !showNullValues)
            continue;

        switch (prop.getType())
        {
            case CIMTYPE_STRING:
                _print_cimValue(v, (String*)0);
                break;
            case CIMTYPE_CHAR16:
                _print_cimValue(v, (Char16*)0);
                break;
            case CIMTYPE_UINT8:
                _print_cimValue(v, (Uint8*)0);
                break;
            case CIMTYPE_SINT8:
                _print_cimValue(v, (Uint8*)0);
                break;
            case CIMTYPE_UINT16:
                _print_cimValue(v, (Uint16*)0);
                break;
            case CIMTYPE_SINT16:
                _print_cimValue(v, (Uint16*)0);
                break;
            case CIMTYPE_UINT32:
                _print_cimValue(v, (Uint32*)0);
                break;
            case CIMTYPE_SINT32:
                _print_cimValue(v, (Uint32*)0);
                break;
            case CIMTYPE_UINT64:
                _print_cimValue(v, (Uint64*)0);
                break;
            case CIMTYPE_SINT64:
                _print_cimValue(v, (Uint64*)0);
                break;
            case CIMTYPE_REAL32:
                _print_cimValue(v, (Real32*)0);
                break;
            case CIMTYPE_REAL64:
                _print_cimValue(v, (Real64*)0);
                break;
            case CIMTYPE_BOOLEAN:
                _print_cimValue(v, (Boolean*)0);
                break;
            case CIMTYPE_REFERENCE:
                _print_cimValue(v, (CIMObjectPath*)0);
                break;
            case CIMTYPE_DATETIME:
                _print_cimValue(v, (CIMDateTime*)0);
                break;

            default:
                ;
        }

        cout << endl;
    }

    cout << "};\n" << endl;
}

// Return a variable number of spaces in a String
String _spaces(Uint32 count = 1)
{
    String s;
    while (count-- > 0)
    {
        s.append(" ");
    }
    return(s);
}

// Generate newline and indent spaces per input parameter.
String _indentNewline(Uint32 indent)
{
    String s = "\n";
    while (indent-- > 0)
    {
        s.append(" ");
    }
    return(s);

}

/*
    Functions to generate a string from a single CIM Type value
*/
//template<class T>
//String _toString( T x )
//{
//    return(x);
//}

String _toString(Boolean x)
{
    return(x ? "true" : "false");
}
String _toString(const Array<String> in)
{
    String s;
    for (Uint32 i = 0 ; i < in.size() ; i++)
    {
        if (i > 0)
        {
            s.append(",");
        }
        s.append(in[i]);
    }
    return s;
}

String _toString(Uint16 in)
{
    String s;
    char temp[22];
    Uint32 size;
    const char* x  = Uint16ToString(temp, in, size);
    s.append(x);
    return s;
}

String _toString(const Array<Uint16> in)
{
    String s;
    for (Uint32 i = 0 ; i < in.size() ; i++)
    {
        if (i > 0)
        {
            s.append(",");
        }
        s.append(_toString(in[i]));
    }
    return s;
}

//------------------------------------------------------------------------------
//
// get the value of a property from an instance
// 
// -----------------------------------------------------------------------------

// Find a property in an instance. Returns the findPropery position and if
// it is not found, sets return to PEG_NOT_FOUND and issues an error message.
Uint32 findProperty(const CIMInstance& inst, const String& name)
{
    Uint32 pos;
    if ((pos = inst.findProperty(name)) == PEG_NOT_FOUND)
    {
        printf("ERROR: property %s not found in instance of class %s\n",
               (const char *) name.getCString(),
               (const char *)inst.getClassName().getString().getCString());
    }
//  else
//  {
//      printf("property %s isfound in instance of class %s\n",
//             (const char *) name.getCString(),
//             (const char *)inst.getClassName().getString().getCString());
//  }
    return pos;
}

// Get the value of a single property.  Returns the value in the rtn
// parameter. If property not found, outpus an eeeor message.

template<class T>
bool getPropertyValue(const CIMInstance& instance,
                          const String& name,
                          T& rtn)
{
    Uint32 pos;
    if ((pos = findProperty(instance,name)) != PEG_NOT_FOUND)
    {
        CIMConstProperty p = instance.getProperty(pos);
        CIMValue v = p.getValue();
        v.get(rtn);
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
//
// get the value of a property with name from instance.  Must be a 
// String property.
//
//------------------------------------------------------------------------------
//

String get_property_value_string(const CIMInstance& instance, const String& name)
{
    Uint32 pos;
    String s = String::EMPTY;
    if ((pos = instance.findProperty(name)) != PEG_NOT_FOUND)
    {
        CIMConstProperty p = instance.getProperty(pos);
        CIMValue v = p.getValue();
        v.get(s);
        return s;
    }
    else
        printf("property %s not found\n", (const char *) name.getCString());
    return s;
}




/******************************************************************************
**
**  Generate String values for properties.  Uses the same algorithms as the
**  instance print above but generates strings at the property level.
**
*******************************************************************************/
static void _toString_elem(String& s, const String& x)
{
    s.append(x);
}

static void _toString_elem(String& s, Uint16 x)
{
    s.append(_toString(x));
}

static void _toString_elem(String& s, const CIMDateTime& x)
{
    s.append(x.toString());
}

template<class T>
String _tostring_cimvalue(const CIMValue& v, T*)
{
    String s = String::EMPTY;
    if (v.isNull())
    {
        s.append("NULL");
    }
    else
    {
        if (v.isArray())
        {
            Array<T> x;
            v.get(x);
    
            for (Uint32 i = 0; i < x.size(); i++)
            {
                _toString_elem(s, x[i]);
    
                if (i + 1 != x.size())
                    s.append(",");
            }
        }
        else
        {
            T x;
            v.get(x);
            _toString_elem(s,x);
        }
    }
    return(s);
}

/*
    Return a string that represents the value of a property in the
    instance.
    propName - Name of property in the instance
    display - display name - Alternate name to be displayed. This defines
        what is displayed.  Since it is optional, the default is to not
        display the name surrounded by the [ ]
    showNull - If true, Null values are displayed. Default is to not
    display properties that have NULL value.
*/
String dispPropertyValueString(CIMInstance& inst, const String& propName,
                          const String& display = String::EMPTY,
                          Boolean showNull = null_opt)
{
    Uint32 pos;
    String rtn = String::EMPTY;
    if (display != String::EMPTY)
    {
        rtn.append(display);
        rtn.append("[");
    }
    
    if ((pos = inst.findProperty(propName)) != PEG_NOT_FOUND)
    {
        CIMConstProperty p = inst.getProperty(pos);
        CIMValue v = p.getValue();
        if (v.isNull() && !showNull)
        {
            return(String::EMPTY);
        }
        switch (p.getType())
        {
            case CIMTYPE_STRING:
                rtn.append(_tostring_cimvalue(v, (String*)0));
                break;

            case CIMTYPE_UINT16:
                rtn.append(_tostring_cimvalue(v, (Uint16*)0));
                break;

            case CIMTYPE_DATETIME:
                rtn.append(_tostring_cimvalue(v, (CIMDateTime*)0));
                break;

            default:
                printf("ERROR. Code does not support CIMTYpe %s\n",
                       cimTypeToString(p.getType()));

        }
    }
    else
        printf("property %s not found in instance %s\n",
               (const char *) propName.getCString(),
               (const char *) inst.getPath().toString().getCString());

    if (display != String::EMPTY)
    {
        rtn.append("]");
    }
    return(rtn);
}

// match the target against the list of entries defined by argc and
// argv.  If there are no entries in the list to match, return true.
// If an entry in the list matches the target, return true.
// The match is string insensitive.
bool match_args(const Array<String>& list, const String& target)
{
    if (list.size() != 0)
    {
        for (Uint32 i = 0; i < list.size(); i++)
        {
            if (String::compareNoCase(target, list[i]) == 0)
            {
                return(true);
            }
        }
        return(false);
    }
    return(true);
}

//
// The following method is used to translate a string based on the
// Value/ValueMap qualifiers of a property. Note that the method is written
// in such a way that the translation could be done in either direction
// (from Value value to ValueMap value or vice versa) or with another pair
// of qualifiers with a relationship similar to the Value/ValueMap pair.
//
String mapValue(
    const String & value,
    const CIMName & propName,
    const CIMName & sourceQualifier,
    const CIMName & targetQualifier,
    const CIMClass & classDef)
{
    String mappedValue;
    Uint32 index = classDef.findProperty(propName);
    if(index != PEG_NOT_FOUND)
    {
        CIMConstProperty prop = classDef.getProperty(index);
        index = prop.findQualifier(sourceQualifier);
        if(index != PEG_NOT_FOUND)
        {
            Array<String> sourceQualValues;
            prop.getQualifier(index).getValue().get(sourceQualValues);
            for(Uint32 i = 0, n = sourceQualValues.size(); i < n; ++i)
            {
                // If we have a match in the Source qualifier, then get the
                // related string from the Target qualifier
                if(sourceQualValues[i] == value)
                {
                    index = prop.findQualifier(targetQualifier);
                    if(index != PEG_NOT_FOUND)
                    {
                        Array<String> targetQualValues;
                        prop.getQualifier(index).getValue().get(
                            targetQualValues);
                        mappedValue = targetQualValues[i];
                    }
                    break;
                }
            }
        }
    }
    return mappedValue;
}

//
// Same as above, but converts an integral value into a string first so that
// it can be found when searching the Values qualifier (or some similar
// qualifier).
//
String mapValue(Uint16 value,
    const CIMName & propName,
    const CIMName & sourceQualifier,
    const CIMName & targetQualifier,
    const CIMClass & classDef)
{
    return mapValue(CIMValue(value).toString(), propName,
      sourceQualifier, targetQualifier, classDef);
}

// translate all of the values in an array into a comma separated
// return string.
String mapValues(const Array<Uint16> values,
    const CIMName & propName,
    const CIMName & sourceQualifier,
    const CIMName & targetQualifier,
    const CIMClass & classDef)
{
    String s;
    for (Uint32 i = 0 ; i < values.size() ; i++)
    {
        if (s.size() != 0)
            s.append(",");

        s.append(mapValue(values[i], propName,
          sourceQualifier, targetQualifier, classDef));
    }
    return s;
}
/*
    get a string representing the property value mapped by the
    value and valueMap qualifiers. If the property does not exist,
    the only indication is a ERROR output to the user.
    TODO: Right now we do not use the showNull or displayName options.
*/
String getMappedPropertyValue(const CIMClass& c,
    const CIMInstance& inst,
    const String& propName,
    const String& displayName = String(),
    Boolean showNull = null_opt)
{
    String s;
    // Add test for existence of the qualifiers in the class
    Uint32 pos;
    if ((pos = inst.findProperty(propName)) != PEG_NOT_FOUND)
    {
        CIMConstProperty p = inst.getProperty(pos);
        CIMValue v = p.getValue();
        if (v.isNull() && !showNull)
        {
            return(String::EMPTY);
        }
        if (p.isArray())
        {
            Array<Uint16> values;
            // following returns a bool
            if(getPropertyValue(inst, String(propName), values))    
            {
                    s.append(mapValues(values, propName,"ValueMap",
                                    "Values", c));
            }
        }
        else
        {
            Uint16 value;
            if(getPropertyValue(inst, String(propName), value))
            {
                   s.append(mapValue(value, propName,"ValueMap",
                                    "Values", c));
            }
        }
    }
    else
    {
        printf("ERROR: property %s not found in instance of class %s\n",
              (const char *) propName.getCString(),
              (const char *)c.getClassName().getString().getCString());
    }
    return s;

}
//------------------------------------------------------------------------------
//
// get_class()
//
//------------------------------------------------------------------------------

bool get_class(
    CIMClient& client,
    const String& name_space,
    const char* class_name,
    CIMClass& cim_class)
{
    try
    {
        const bool local_only = false;
        const bool include_qualifiers = true;
        cim_class = client.getClass(
            name_space, class_name, local_only, include_qualifiers);
        return true;
    }
    catch (CIMException& e)
    {
        err("CIMException: failed to getClass %s:%s. Msg %s",
            *cimple::Str(name_space),
            class_name,
            *cimple::Str(e.getMessage()));
        return false;
    }
    catch (...)
    {
        err("Exception: failed to getClass %s:%s",
            *cimple::Str(name_space),
            class_name);
        return false;
    }
    return true;
}

//------------------------------------------------------------------------------
//
// enumerateInstances()
//
//------------------------------------------------------------------------------

bool enumerateInstances(
    CIMClient& client,
    const String& name_space,
    const char* class_name,
    Array<CIMInstance>& instances)
{
    try
    {
        const bool deep_inheritance = false;
        const bool local_only = false;
        const bool include_qualifiers = false;
        const bool include_class_origin = false;
        instances = client.enumerateInstances(
            name_space, class_name, deep_inheritance, local_only,
            include_qualifiers, include_class_origin, CIMPropertyList());
        return true;
    }
    catch (CIMException& e)
    {
        CString msg = e.getMessage().getCString();
        err("CIMException: failed to enumerate %s:%s. Msg %s",
            (const char *)name_space.getCString(),
            class_name,
            (const char*)msg);
        return false;
    }
    catch (...)
    {
        err("Exception: failed to enumerate %s:%s",
            (const char *)name_space.getCString(),
            class_name);
        return false;
    }
    return true;
}
//------------------------------------------------------------------------------
//
// find_capabilities(name) - Find capabilities instances for this provider name
// The key properties are ProviderModuleName and ProviderName. 
// NOTE: This would be simpler with a get_instance but that does not work
// because one of the keys of capabilities is CapabilityId which is not
// part of either the provider or providermodule instances. 
// 
// Returns the instance and return = 0 if found.
//
//------------------------------------------------------------------------------


int find_capabilities(CIMClient& client,
    const String& targetProviderName,
    const String& targetProviderModuleName,
    Array<CIMInstance>& capabilities)
{
    // Enumerate the class and find matching provider name and
    // provider module name instance.
    
    Array<CIMInstance> instances;
    
    if (!enumerateInstances(client, INTEROP_NAMESPACE, CAPABILITIES_CLASSNAME,
                           instances))
    {
        err("failed to enumerate capabilities class");
        exit(1);
    }
    
    // filter out all provider instances where ProviderModuleName does not
    // match the target provider module.
    
    for (Uint32 i = 0 ; i < instances.size() ; i++)
    {
        String thisProviderModuleName =
            get_property_value_string(instances[i], String("ProviderModuleName"));
        String thisProviderName =
            get_property_value_string(instances[i], String("ProviderName"));

        if (thisProviderName == targetProviderName &&
            thisProviderModuleName == targetProviderModuleName)
        {
            capabilities.append(instances[i]);
        }
    }
    
    if (capabilities.size() == 0)
    {
        printf("Warning: No capability instance found for %s %s\n",
               *cimple::Str(targetProviderName),
               *cimple::Str(targetProviderModuleName));
        return(-1);
    }
    return(0);
}

//------------------------------------------------------------------------------
//
// find_provider_modules() 
//     Find the provider modules for a particular class definition.
//     Searches the capabilities class 
//     returns the list of provider module names that correspond to 
//     the class defined in the input targetClass. 
//
//------------------------------------------------------------------------------

int find_providerModules(CIMClient& client,
    const String& targetClass,
    Array<String>& providerModuleList)
{
    // Enumerate the capabilities instances and find matching provider name and
    // get provider module name for any capabilities that has this classname.

    Array<CIMInstance> instances;
    if (!enumerateInstances(client, INTEROP_NAMESPACE, CAPABILITIES_CLASSNAME,
                           instances))
    {
        err("Error: failed to enumerate capabilities class");
        exit(1);
    }
    
    // filter out all instances that do not match this classname
    
    for (Uint32 i = 0 ; i < instances.size() ; i++)
    {
        if (String::compareNoCase(targetClass,
            get_property_value_string(instances[i], "ClassName")) == 0)
        {
            String thisProviderModuleName =
                get_property_value_string(instances[i], String("ProviderModuleName"));
            providerModuleList.append(thisProviderModuleName);
        }
    }
    return(0);
}
//------------------------------------------------------------------------------
//
// find_providers(name) - Find all instances of Provider class that match
// the input providerModuleName
//
//------------------------------------------------------------------------------

Array<CIMInstance> find_providers(CIMClient& client,
    const String& name)
{
    Array<CIMInstance> providers;

    if (!enumerateInstances(client, INTEROP_NAMESPACE, PROVIDER_CLASSNAME,
                            providers))
    {
        err("Error: failed to enumerate provider class");
        exit(1);
    }

    // filter out all provider instances where ProviderModuleName does not match
    // the target provider module.

    Array<CIMInstance> rtn;
    for (Uint32 i = 0 ; i < providers.size() ; i++)
    {
        String providerModuleName = 
            get_property_value_string(providers[i], String("ProviderModuleName"));
        if (providerModuleName == name)
        {
            rtn.append(providers[i]);
        }
    }
    return rtn;
}

//------------------------------------------------------------------------------
//
// connect() Connect to localhost
//
//------------------------------------------------------------------------------

bool connect(CIMClient& client)
{
    try
    {
        // Connect to CIM serer.
        client.connectLocal();
    }
    catch (CIMException& e)
    {
        CString msg = e.getMessage().getCString();
        err("Error: failed to connect to local CIM server %s", (const char*)msg);
        return false;
    }
    catch (...)
    {
        err("Error: failed to connect to local CIM server");
        return false;
    }
    return true;
}
//------------------------------------------------------------------------------
//
// main()
//
//------------------------------------------------------------------------------

static const char* arg0;

int main(int argc, char** argv)
{
    arg0 = argv[0];

    // Setup arg0 for warn() and err().

    set_arg0(argv[0]);

    int opt;

    while ((opt = getopt(argc, argv, "cC:vVhmns")) != -1)
    {
        switch (opt)
        {
            case 'c':
                class_opt = true;
                break;

            case 'C':
                target_classlist.append(optarg);
                break;

            case 'v':
                verbose_opt = true;
                break;

            case 'V':
                printf("%s\n", CIMPLE_VERSION_STRING);
                exit(0);
                break;

            case 'h':
                help_opt = true;
                break;

            case 'm':
                module_opt = true;
                break;

            case 'n':
                null_opt = true;
                break;

            case 's':
                summary_opt = true;
                break;

            default:
            {
                err("unknown option: -%c\n", opt);
                break;
            }
        }
    }

    argc -= optind;
    argv += optind;

    if (argc < 0 || help_opt)
    {
        fprintf(stderr, (const char*)USAGE, arg0);
        exit(1);
    }

    // Put any remaining arguments into a string array
    // for use in matching provider module names
    Array<String> arg_list;
    if (argc > 0)
    {
        for (int i = 0 ; i < argc ; i++)
        {
            arg_list.append(argv[i]);
        }
    }

    // Step 1 - Connect to server

    CIMClient client;
    if(!connect(client))
       err("Could not connect to host");

    // Step 2 - enumerate the providerModule class

    Array<CIMInstance> providerModules;
    if (!enumerateInstances(client, INTEROP_NAMESPACE, "PG_ProviderModule",
                            providerModules))
    {
        err("failed to enumerate ProviderModule class");
        exit(1);
    }

    // Add any entries from the -c option to the list of potential 
    // provider modules by calling the find_provider_modules function
    // to map from capabilities back to provider module name.

    for (Uint32 i = 0 ; i < target_classlist.size() ; i++)
    {
        Array<String> pml;
        if (find_providerModules(client, target_classlist[i], pml) == 0)
        {
            for (Uint32 j = 0 ; j < pml.size() ; j++)
            {
                arg_list.append(pml[j]);
            }
        }
    }

    // Step 3 -  For each provider module, find providers

    for(Uint32 i = 0 ; i < providerModules.size() ; i++)
    {
        String providerModuleName;

        providerModuleName =
            get_property_value_string(providerModules[i],String("Name"));

        // find if any of the remaining arguments matches the current
        // provider module name
        if (!match_args(arg_list, providerModuleName))
        {
            continue;
        }

        // get the properties from this providerModule instance and 
        // display

        Uint16 user_context;
        getPropertyValue(providerModules[i], "UserContext", user_context);

        ///// THE FOLLOWING CAUSES OUT_OF_BOUNDS
//      CIMDateTime install_date;
//      get_property_value(providerModules[i],String("InstallDate"),
//                         install_date);
//      String designated_user_context =
//          get_property_value(providerModules[i],
//             String("DesignatedUserContext"));
//
//      Array<Uint16> module_operational_status;
//      get_property_value(providerModules[i],String("OperationalStatus"),
//                                 module_operational_status);

        // if there is a arg list and the module name does not match
        // any entries in this list, bypass

        // display module information
        if (class_opt)
        {
            print(providerModules[i]);
        }
        else
        {
            cout << providerModuleName;
            cout << "[#" << i << "]";
            if (!module_opt && !summary_opt)
            {
                cout << ": "
                     << dispPropertyValueString(providerModules[i], "InterfaceType")
                     << _spaces()
                     << dispPropertyValueString(providerModules[i], "InterfaceVersion",
                                         "Ver")
                     << _spaces()
                     << dispPropertyValueString(providerModules[i], "Vendor", "Vendor")
                     << _spaces()
                     << dispPropertyValueString(providerModules[i], "Location", "Loc");
            }
    
            if (verbose_opt)
            {
                cout << _spaces()
                << dispPropertyValueString(providerModules[i], "UserContext",
                                    "UserContext")
                << dispPropertyValueString(providerModules[i],"InstallDate",
                                   "InstallDate")
//              << dispPropertyValueString(providerModules[i],"OperationalStatus",
//                                 "OperationalStatus")
                ;
                //printVariable("Installed", install_date.toString());

//              if (health_state != CIMDateTime())
//                  _printVariable("HealthState", _toString(health_state));
//              _printVariable("OperationalStatus",
//                       _toString(operational_status));
            }
            cout << endl;
        }
        // if module_option set, display only the module level
        if (module_opt)
        {
            continue;
        }

        // Processing of the providers for this module

        // Get the providers for this provider module from
        // the provider class.
        
        Array<CIMInstance> providers;
        if (providerModuleName != String::EMPTY)
        {
            providers = find_providers(client, providerModuleName);
        }
        else
        {
            printf("Error, providerModule Name property not found\n");
            continue;
        }
            // get the providercapabilities class to support output
            // formatting
            CIMClass providerClass;
            if (!get_class(client,INTEROP_NAMESPACE,
                          PROVIDER_CLASSNAME,providerClass))
            {
                err("error: get_class %s %s",INTEROP_NAMESPACE,
                    PROVIDER_CLASSNAME);
                exit(1);
            }
        // For each Provider Object
        for (Uint32 j = 0 ; j < providers.size() ; j++)
        {
            String providerName =
                get_property_value_string(providers[j],String("Name"));

            // TODO move this one into the output definition
            // These are in error.  They should be the string form under
            // the rule that this is generalized. Right now the work
            // only because these properties are String CIMTypes.
            Array<String> status_descriptions;
            getPropertyValue(providers[j], String("StatusDescriptions"),
                               status_descriptions);

            String this_provider_module_name = 
            get_property_value_string(providers[j], String("ProviderModuleName"));

            // test to be sure we have good linkage to instance
            // of provider module name.  This is probably not needed.
            
            if (this_provider_module_name != providerModuleName)
            {
                cout << "Error in instance linkage "
                     << providerModuleName << " "
                     << this_provider_module_name << endl;
                continue;
            }

            // Display the Provider information

            if (class_opt)
            {
                cout << "ProviderModule = " << providerModuleName 
                    << "[#" << j << "]" << endl;
                print(providers[j]);
            }
            else
            {
                // output the provider name
                cout << _spaces(4)
                     << providerName << "[#" << j << "]";
                // if not summary output the provider basic information
                if (!summary_opt)
                {
                    cout << ":" 
                         << dispPropertyValueString(providers[j], "Status", "Status")
                         << dispPropertyValueString(providers[j], "HealthState",
                                            "HealthState")
                         << dispPropertyValueString(providers[j], "OperationalStatus",
                                            "OperationalStatus")
                    ;
                }
                if (verbose_opt)
                {
                    cout << _indentNewline(16)
                         << dispPropertyValueString(providers[j], "Status", "Status")
                    ;
                }
                cout << endl;
            }

            // get capabilities instances for this provider and module

            Array<CIMInstance> caps;
            // if summary only do not output the capabilities.
            if (summary_opt)
            {
                continue;
            }
            if(find_capabilities(client, providerName, providerModuleName, caps)
               != 0)
            {
                continue;
            }
            // get the class capabilities class to support output
            // formatting
            CIMClass capabilitiesClass;
            if (!get_class(client,INTEROP_NAMESPACE,
                          CAPABILITIES_CLASSNAME,capabilitiesClass))
            {
                err("error: get_class %s %s",INTEROP_NAMESPACE,
                    CAPABILITIES_CLASSNAME);
                exit(1);
            }
            // for each capability object return print out the capabilities
            for (Uint32 k = 0 ; k < caps.size(); k++)
            {
                if (class_opt)
                {
                    cout << "ProviderModule:Provider = " 
                        << providerModuleName 
                        << ":" << providerName << endl;
                    print(caps[k]);
                }
                else
                {
                    // get the Provider type and map the value and value map
                    // qualifiers to produce the providerTypeString
    
                    Array<Uint16> provider_types;
                    getPropertyValue(caps[k], String("ProviderType"),
                                       provider_types);
                    // Display the capabilities information
                    cout << _spaces(8)
                        << dispPropertyValueString(caps[k], "ClassName") << ":"
                        << _spaces(1)
                        << getMappedPropertyValue(capabilitiesClass, caps[k],
                                            "ProviderType")
                        << "[" << _toString(provider_types) << "]"
                        << _spaces(1)
                        << dispPropertyValueString(caps[k],
                                "NameSpaces", "NameSpaces")
                        << dispPropertyValueString(caps[k],
                                "supportedProperties",
                                "Properties")
                        << dispPropertyValueString(caps[k], "supportedMethods",
                                            "Methods")
                        << endl;
                }
            }
        }
    }
    return 0;
}

