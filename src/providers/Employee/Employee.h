/*NOCHKSRC*/
//==============================================================================
//
// PLEASE DO NOT EDIT THIS FILE; IT WAS AUTOMATICALLY GENERATED BY GENCLASS.
//
//==============================================================================

#ifndef _cimple_Employee_h
#define _cimple_Employee_h

#include <cimple/cimple.h>

CIMPLE_NAMESPACE_BEGIN

// Employee keys:
//     Id

class Employee : public Instance
{
public:
    // Employee features:
    Property<uint32> Id;
    Property<String> First;
    Property<String> Last;
    Property<uint32> Gender;
    Property<boolean> Active;
    Property<boolean> OutOfOffice;

    CIMPLE_CLASS(Employee)
};

class Employee_SetOutOfOfficeState_method : public Instance
{
public:
    Property<boolean> OutOfOfficeState;
    Property<boolean> PreviousOutOfOfficeState;
    Property<uint32> return_value;
    CIMPLE_METHOD(Employee_SetOutOfOfficeState_method)
};

class Employee_GetEmployeeCount_method : public Instance
{
public:
    Property<uint32> return_value;
    CIMPLE_METHOD(Employee_GetEmployeeCount_method)
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_Employee_h */
