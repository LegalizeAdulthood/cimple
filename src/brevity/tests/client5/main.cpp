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

#include <brevity/brevity.h>
#include "Employee_Hnd.h"

using namespace cimple;

int main()
{
    Client client;

    try
    {
        client.connect("http://localhost:5989/cimxml");

        Instance_Name_Enum e = 
            client.enum_instance_names("root/cimv2", Employee_Ref());

        while (e.more())
        {
            Employee_Ref ref(e.next());
            ref.print();
        }
    }
    catch (Exception& e)
    {
        printf("Exception: %s\n", e.message().c_str());
    }

    return 0;
}

//
// Program output:
// 
//     Employee
//     {
//         uint32 Id = 4001;
//     }
//     Employee
//     {
//         uint32 Id = 4002;
//     }
//     Employee
//     {
//         uint32 Id = 4003;
//     }
//     Employee
//     {
//         uint32 Id = 1001;
//     }
//
