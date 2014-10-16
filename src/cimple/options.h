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

#ifndef _cimple_options_h
#define _cimple_options_h

//------------------------------------------------------------------------------
//
// CIMPLE_HAVE_PROPERTY_PADDING
//
//     Controls whether Property<> objects are padded so that that their size
//     is 16 bytes.
//
//------------------------------------------------------------------------------

//#define CIMPLE_HAVE_PROPERTY_PADDING

//------------------------------------------------------------------------------
//
// CIMPLE_ENABLE_SUBCLASS_PROVIDERS
//
//     Controls whether providers can provide subclasses of the class for
//     which they were generated.
//
//------------------------------------------------------------------------------

#define CIMPLE_ENABLE_SUBCLASS_PROVIDERS

//------------------------------------------------------------------------------
//
// CIMPLE_HAVE_CMPI_VOID_RETURN_BUG
//
//     Whether CMPI has faulty prototypes for enableIndications() and
//     disableIndications(), which return "void" instead of "CMPIStatus".
//
//------------------------------------------------------------------------------

// #define CIMPLE_HAVE_CMPI_VOID_RETURN_BUG

#endif /* _cimple_options_h */
