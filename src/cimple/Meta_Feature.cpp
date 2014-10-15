#include "Meta_Feature.h"
#include "Meta_Property.h"
#include "Meta_Reference.h"
#include "Meta_Method.h"
#include "Meta_Qualifier.h"
#include "Meta_Class.h"
#include "io.h"
#include "ptr_array.h"

CIMPLE_NAMESPACE_BEGIN

void destroy(Meta_Feature* mf)
{
    if (mf->flags & CIMPLE_FLAG_PROPERTY)
        destroy((Meta_Property*)mf);
    else if (mf->flags & CIMPLE_FLAG_REFERENCE)
        destroy((Meta_Reference*)mf);
    else if (mf->flags & CIMPLE_FLAG_METHOD)
        destroy((Meta_Method*)mf);
}

void print(const Meta_Feature* mf, bool print_qualifiers, size_t level)
{
    if (print_qualifiers)
    {
        print(mf->meta_qualifiers, mf->num_meta_qualifiers, mf->flags, 
            false, level);
    }

    iprintf(level, "");

    if (mf->flags & CIMPLE_FLAG_PROPERTY)
        print((Meta_Property*)mf, false);

    if (mf->flags & CIMPLE_FLAG_REFERENCE)
        print((Meta_Reference*)mf);

    if (mf->flags & CIMPLE_FLAG_METHOD)
        print((Meta_Method*)mf, print_qualifiers, level);
}

Meta_Feature* clone(const Meta_Feature* x)
{
    Meta_Feature* mf = 0;

    if (x->flags & CIMPLE_FLAG_PROPERTY)
        mf = (Meta_Feature*)clone((const Meta_Property*)x);
    else if (x->flags & CIMPLE_FLAG_REFERENCE)
        mf = (Meta_Feature*)clone((const Meta_Reference*)x);
    else if (x->flags & CIMPLE_FLAG_METHOD)
        mf = (Meta_Feature*)clone((const Meta_Class*)x);

    mf->meta_qualifiers = clone(x->meta_qualifiers, x->num_meta_qualifiers);
    mf->num_meta_qualifiers = x->num_meta_qualifiers;

    return mf;
}

void append(
    const Meta_Feature* const*& meta_features,
    size_t& num_meta_features,
    const Meta_Feature* meta_feature)
{
    append_ptr_array(
        *((void***)&meta_features), 
        num_meta_features, 
        (void*)meta_feature);
}

CIMPLE_NAMESPACE_END

