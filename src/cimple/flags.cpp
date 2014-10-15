#include "flags.h"
#include "io.h"

CIMPLE_NAMESPACE_BEGIN

const char* flag_names[] =
{
    "Property", /* 0 */
    "Reference", /* 1 */
    "Method", /* 2 */
    "Class", /* 3 */
    "Abstract", /* 4 */
    "Aggregate", /* 5 */
    "Aggregation", /* 6 */
    "Association", /* 7 */
    "Composition", /* 8 */
    "Counter", /* 9 */
    "Delete", /* 10 */
    "DN", /* 11 */
    "EmbeddedObject", /* 12 */
    "Exception", /* 13 */
    "Expensive", /* 14 */
    "Experimental", /* 15 */
    "Gauge", /* 16 */
    "IfDeleted", /* 17 */
    "In", /* 18 */
    "Indication", /* 19 */
    "Invisible", /* 20 */
    "Key", /* 21 */
    "Large", /* 22 */
    "OctetString", /* 23 */
    "Out", /* 24 */
    "Read", /* 25 */
    "Required", /* 26 */
    "Static", /* 27 */
    "Terminal", /* 28 */
    "Weak", /* 29 */
    "Write", /* 30 */
    "EmbeddedInstance", /* 31 */
};

const size_t num_flag_names = sizeof(flag_names) / sizeof(flag_names[0]);

size_t flag_name_to_index(const char* flag_name)
{
    for (uint32 i = 0; i < num_flag_names; i++)
    {
        if (strcasecmp(flag_names[i], flag_name) == 0)
            return i;
    }

    // Not found!
    return size_t(-1);
}

CIMPLE_NAMESPACE_END

