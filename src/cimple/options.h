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
// CIMPLE_USE_SYNCHRONOUS_DISPATCHER_METHODS
//
//     Controls whether the synchronous Dispatcher methods are defined. These
//     include:
//
//         Dispatcher::enum_instance()
//         Dispatcher::enum_associator_name()
//         Dispatcher::enum_reference_name()
//
//     Their total object size is around 2.5 kilobytes.
//
//------------------------------------------------------------------------------

// #define CIMPLE_USE_SYNCHRONOUS_DISPATCHER_METHODS

//------------------------------------------------------------------------------
//
// CIMPLE_USE_FACADE
//
//     Controls whether the Facade class is defined (Facade.h and Facade.cpp).
//
//------------------------------------------------------------------------------

// #define CIMPLE_USE_FACADE

//------------------------------------------------------------------------------
//
// CIMPLE_USE_CLIENT
//
//     Controls whether source needed by clients is included.
//
//------------------------------------------------------------------------------

#define CIMPLE_USE_CLIENT

//------------------------------------------------------------------------------
//
// CIMPLE_NEED_RANDOM_INITIALIZE
//
//     Controls whether the random_initialize() function is compiled.
//
//------------------------------------------------------------------------------

//#define CIMPLE_NEED_RANDOM_INITIALIZE

#endif /* _cimple_options_h */
