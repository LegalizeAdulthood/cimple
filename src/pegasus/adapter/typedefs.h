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

#ifndef _pegadapter_typedefs_h
#define _pegadapter_typedefs_h

#include <Pegasus/Common/Config.h>
#include <Pegasus/Common/CIMInstance.h>
#include <Pegasus/Common/CIMObjectPath.h>
#include <Pegasus/Common/CIMParamValue.h>
#include <Pegasus/Provider/CIMMethodProvider.h>
#include <Pegasus/Provider/CIMInstanceProvider.h>
#include <Pegasus/Provider/CIMAssociationProvider.h>
#include <Pegasus/Provider/CIMIndicationProvider.h>
#include <Pegasus/Common/CIMStatusCode.h>

typedef Pegasus::String P_String;
typedef Pegasus::CIMValue P_CIMValue;
typedef Pegasus::CIMKeyBinding P_CIMKeyBinding;
typedef Pegasus::CIMNamespaceName P_CIMNamespaceName;
typedef Pegasus::Boolean P_Boolean;
typedef Pegasus::Char16 P_Char16;
typedef Pegasus::CIMAssociationProvider P_CIMAssociationProvider;
typedef Pegasus::CIMDateTime P_CIMDateTime;
typedef Pegasus::CIMException P_CIMException;
typedef Pegasus::CIMIndicationProvider P_CIMIndicationProvider;
typedef Pegasus::CIMInstance P_CIMInstance;
typedef Pegasus::CIMInstanceProvider P_CIMInstanceProvider;
typedef Pegasus::CIMKeyBinding P_CIMKeyBinding;
typedef Pegasus::CIMMethodProvider P_CIMMethodProvider;
typedef Pegasus::CIMName P_CIMName;
typedef Pegasus::CIMNamespaceName P_CIMNamespaceName;
typedef Pegasus::CIMObject P_CIMObject;
typedef Pegasus::CIMObjectPath P_CIMObjectPath;
typedef Pegasus::CIMOMHandle P_CIMOMHandle;
typedef Pegasus::CIMParamValue P_CIMParamValue;
typedef Pegasus::CIMProperty P_CIMProperty;
typedef Pegasus::CIMPropertyList P_CIMPropertyList;
typedef Pegasus::CIMProvider P_CIMProvider;
typedef Pegasus::CIMStatusCode P_CIMStatusCode;
typedef Pegasus::CIMType P_CIMType;
typedef Pegasus::CIMValue P_CIMValue;
typedef Pegasus::CString P_CString;
typedef Pegasus::Exception P_Exception;
typedef Pegasus::IdentityContainer P_IdentityContainer;
typedef Pegasus::IndicationResponseHandler P_IndicationResponseHandler;
typedef Pegasus::InstanceResponseHandler P_InstanceResponseHandler;
typedef Pegasus::MethodResultResponseHandler P_MethodResultResponseHandler;
typedef Pegasus::ObjectPathResponseHandler P_ObjectPathResponseHandler;
typedef Pegasus::ObjectResponseHandler P_ObjectResponseHandler;
typedef Pegasus::OperationContext P_OperationContext;
typedef Pegasus::Real32 P_Real32;
typedef Pegasus::Real64 P_Real64;
typedef Pegasus::ResponseHandler P_ResponseHandler;
typedef Pegasus::Sint16 P_Sint16;
typedef Pegasus::Sint32 P_Sint32;
typedef Pegasus::Sint64 P_Sint64;
typedef Pegasus::Sint8 P_Sint8;
typedef Pegasus::String P_String;
typedef Pegasus::SubscriptionFilterQueryContainer 
    P_SubscriptionFilterQueryContainer;
typedef Pegasus::Uint16 P_Uint16;
typedef Pegasus::Uint32 P_Uint32;
typedef Pegasus::Uint64 P_Uint64;
typedef Pegasus::Uint8 P_Uint8;

#endif /* _pegadapter_typedefs_h */
