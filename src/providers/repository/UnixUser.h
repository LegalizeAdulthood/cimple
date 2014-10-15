//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#ifndef _UnixUser_h
#define _UnixUser_h

#include <cimple/cimple.h>

CIMPLE_NAMESPACE_BEGIN

class CIMPLE_LINKAGE UnixUser : public Instance
{
public:
    // UnixUser features:
    Property<String> name;
    Property<String> password;
    Property<uint32> uid;
    Property<uint32> gid;
    Property<String> fullName;
    Property<String> homeDir;
    Property<String> shellProgram;

    CIMPLE_CLASS(UnixUser)
};

CIMPLE_NAMESPACE_END

#endif /* _UnixUser_h */
