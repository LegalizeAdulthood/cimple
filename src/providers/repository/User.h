//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#ifndef _cimple_User_h
#define _cimple_User_h

#include <cimple/cimple.h>

CIMPLE_NAMESPACE_BEGIN

class CIMPLE_LINKAGE User : public Instance
{
public:
    // User features:
    Property<String> name;
    Property<String> password;
    Property<uint32> uid;
    Property<uint32> gid;
    Property<String> fullName;
    Property<String> homeDir;
    Property<String> shellProgram;

    CIMPLE_CLASS(User)
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_User_h */
