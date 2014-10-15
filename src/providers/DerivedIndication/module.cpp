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

#include "DerivedIndication_Provider.h"

using namespace cimple;

CIMPLE_MODULE(DerivedIndication_Module);
CIMPLE_PROVIDER(DerivedIndication_Provider);

/* Support for CMPI entry points */
// CIMPLE_CMPI_INDICATION_PROVIDER(DerivedIndication_Provider);

/* Support for Pegasus C++ Interface */
CIMPLE_PEGASUS_PROVIDER_ENTRY_POINT;

CIMPLE_ID("$Header: /home/cvs/cimple/src/providers/DerivedIndication/module.cpp,v 1.6 2007/03/07 20:25:24 mbrasher-public Exp $");
