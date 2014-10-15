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

#ifndef _Adapter_h
#define _Adapter_h

#include <cimple/config.h>
#include <cimple/cimple.h>
#include "cmpi.h"
#include <cimple/Provider_Handle.h>
#include <cimple/Mutex.h>
#include <cimple/Magic.h>
#include <cimple/Thread.h>
#include "CMPI_Thread_Context.h"

//==============================================================================
//
// Definitions to fix the "CMPI-void-return bug".
//
//==============================================================================

#ifdef CIMPLE_HAVE_CMPI_VOID_RETURN_BUG
# define FIX_RETURN_TYPE void
# define FIX_RETURN(X) return
#else
# define FIX_RETURN_TYPE CMPIStatus
# define FIX_RETURN(X) CMReturn(X)
#endif

CIMPLE_NAMESPACE_BEGIN

//==============================================================================
//
// struct Name_Space_Entry
//
//     This structure keeps track of how many subscriptions there are on the
//     given namespace.
//
//==============================================================================

struct Name_Space_Entry
{
    String name;
    size_t count;

    Name_Space_Entry() : count(0)
    {
    }

    Name_Space_Entry(const Name_Space_Entry& x) : name(x.name), count(x.count)
    {
    }

    Name_Space_Entry(const String& n, size_t c) : name(n), count(c)
    {
    }

    Name_Space_Entry& operator=(const Name_Space_Entry& x)
    {
        if (this != &x)
        {
            name = x.name;
            count = x.count;
        }
        return *this;
    }
};

inline bool operator==(const Name_Space_Entry& x, const Name_Space_Entry& y)
{
    return x.name == y.name;
}

//==============================================================================
//
// struct CMPI_Static_Data
//
//     This structure overlays the __CMPI_Static_Data structure defined by the
//     CIMPLE_CMPI_<TYPE>_PROVIDER family of macros. CMPI accesses this memory
//     even after the provider's cleanup() method is called (so we cannot use
//     heap memory).
//
//==============================================================================

#define MI_NAME_SIZE 256

struct CMPI_Static_Data
{
    // Magic number.
    uint32 magic;

    // Pointer to adapter.
    CMPI_Adapter* adapter;

    // CMPI Function tables.
    CMPIInstanceMIFT instance_ft;
    CMPIMethodMIFT method_ft;
    CMPIIndicationMIFT indication_ft;
    CMPIAssociationMIFT association_ft;

    // CMPI Management interfaces.
    CMPIInstanceMI instance_mi;
    CMPIMethodMI method_mi;
    CMPIAssociationMI association_mi;
    CMPIIndicationMI indication_mi;

    // Used for miName member of MIFT structures.
    char inst_mi_name[MI_NAME_SIZE];
    char meth_mi_name[MI_NAME_SIZE];
    char indic_mi_name[MI_NAME_SIZE];
    char assoc_mi_name[MI_NAME_SIZE];
};

//==============================================================================
//
// class CMPI_Adapter
//
//==============================================================================

class CMPI_Adapter : public Provider_Handle
{
public:

    CMPI_Adapter(
        const CMPIBroker* broker_, 
        const CMPIContext* context,
        const char* prov_name,
        const Registration* registration,
        CMPI_Static_Data* sd);

    ~CMPI_Adapter();

    static CMPIStatus instanceCleanup(
        CMPIInstanceMI* mi, 
        const CMPIContext* context,
        CMPIBoolean terminating);

    static CMPIStatus enumInstanceNames(
        CMPIInstanceMI* mi, 
        const CMPIContext* context, 
        const CMPIResult* result,
        const CMPIObjectPath* cmpi_op);

    static CMPIStatus enumInstances(
        CMPIInstanceMI* mi, 
        const CMPIContext* context, 
        const CMPIResult* result,
        const CMPIObjectPath* cmpi_op, 
        const char** properties);

    static CMPIStatus getInstance(
        CMPIInstanceMI* mi, 
        const CMPIContext* context, 
        const CMPIResult* result,
        const CMPIObjectPath* cmpi_op, 
        const char** properties);

    static CMPIStatus createInstance(
        CMPIInstanceMI* mi, 
        const CMPIContext* context, 
        const CMPIResult* result,
        const CMPIObjectPath* cmpi_op, 
        const CMPIInstance* cmpi_inst);

    static CMPIStatus modifyInstance(
        CMPIInstanceMI* mi, 
        const CMPIContext* context, 
        const CMPIResult* result,
        const CMPIObjectPath* ref, 
        const CMPIInstance* inst,
        const char** properties);

    static CMPIStatus deleteInstance(
        CMPIInstanceMI* mi, 
        const CMPIContext* context, 
        const CMPIResult* result,
        const CMPIObjectPath* cmpi_op);

    static CMPIStatus execQuery(
        CMPIInstanceMI* mi, 
        const CMPIContext* context, 
        const CMPIResult* result,
        const CMPIObjectPath* ref, 
        const char* lang, 
        const char* query);

    static CMPIStatus methodCleanup(
        CMPIMethodMI* mi, 
        const CMPIContext* context,
        CMPIBoolean terminating);

    static CMPIStatus invokeMethod(
        CMPIMethodMI* mi, 
        const CMPIContext* context, 
        const CMPIResult* result,
        const CMPIObjectPath* ref, 
        const char* method, 
        const CMPIArgs* in,
        CMPIArgs* out);

    static CMPIStatus indicationCleanup(
        CMPIIndicationMI* mi, 
        const CMPIContext* context,
        CMPIBoolean terminating);

     static CMPIStatus authorizeFilter(
         CMPIIndicationMI* mi, 
         const CMPIContext* ctx,
         const CMPISelectExp* se, 
         const char* ns, 
         const CMPIObjectPath* op,
         const char* user);

    static CMPIStatus mustPoll(
        CMPIIndicationMI* mi, 
        const CMPIContext* context,
        const CMPISelectExp* filter, 
        const char* indication_type,
        const CMPIObjectPath* class_path);

    static CMPIStatus activateFilter(
        CMPIIndicationMI* mi, 
        const CMPIContext* context,
        const CMPISelectExp* select_expr, 
        const char* indication_type,
        const CMPIObjectPath* class_path, 
        CMPIBoolean first_activation);

    static CMPIStatus deactivateFilter(
        CMPIIndicationMI* mi, 
        const CMPIContext* context,
        const CMPISelectExp* select_expr, 
        const  char* indication_type,
        const CMPIObjectPath* class_path, 
        CMPIBoolean last);

    static FIX_RETURN_TYPE enableIndications(
        CMPIIndicationMI* mi, 
        const CMPIContext* context);

    static FIX_RETURN_TYPE disableIndications(
        CMPIIndicationMI* mi, 
        const CMPIContext* context);

    static CMPIStatus associationCleanup(
        CMPIAssociationMI* mi, 
        const CMPIContext* context,
        CMPIBoolean terminating);

    static CMPIStatus associators( 
        CMPIAssociationMI* mi, 
        const CMPIContext* context, 
        const CMPIResult* result,
        const CMPIObjectPath* cmpi_op, 
        const char* assoc_class, 
        const char* result_class,
        const char* role, 
        const char* result_role, 
        const char** properties);

    static CMPIStatus associatorNames(
        CMPIAssociationMI* mi, 
        const CMPIContext* context, 
        const CMPIResult* result,
        const CMPIObjectPath* cmpi_op, 
        const char* assoc_class, 
        const char* result_class,
        const char* role, 
        const char* result_role);

    static CMPIStatus references(
        CMPIAssociationMI* mi, 
        const CMPIContext* context, 
        const CMPIResult* result,
        const CMPIObjectPath* cmpi_op, 
        const char* result_class, 
        const char* role ,
        const char** properties);

    static CMPIStatus referenceNames(
        CMPIAssociationMI* mi, 
        const CMPIContext* context, 
        const CMPIResult* result,
        const CMPIObjectPath* cmpi_op, 
        const char* result_class, 
        const char* role);

    static const Meta_Class* find_meta_class_callback(
        const char* class_name, void* client_data);

    static CMPIStatus cleanup(
        CMPI_Adapter* adapter,
        const CMPIContext* context,
        CMPIBoolean terminating);

    const Meta_Class* find_meta_class(const char* class_name);

    const Meta_Class* find_model_meta_class(const char* class_name);

    void ent(const char* file, int line, const char* func);

    void ret(const char* file, int line, const char* func);

    void ret(const char* file, int line, const char* func, CMPIrc rc);

    void ret(const char* file, int line, const char* func, CMPIrc rc,
        const char* msg);

    CIMPLE_PRINTF_ATTR(5, 6)
    void trc(
        const char* file, int line, const char* func, const char* fmt, ...);

public:

    // Magic number.
    Magic<0x2301490A> magic;

    // Backpointer to broker.
    const CMPIBroker* broker;

    // Backpointer to static data.
    CMPI_Static_Data* sd;

    // Number of times this provider has been loaded due to CMPI entry points
    // for different provider types (instance, method, indication, association).
    size_t load_count;

    // Allow provider to be unloaded when this flag is true.
    bool allow_unload;

    // List of namespaces there are currently subscriptions for (and a count
    // of the number of such active subscriptions on that namespace).
    Array<Name_Space_Entry> name_spaces;

    const Meta_Class* mc;

    // This flag indicates whether indications are enabled.
    bool indications_enabled;

    // Synchronizes access to adapter methods from different threads:
    Mutex lock;
};

CIMPLE_NAMESPACE_END

#endif /* _Adapter_h */
