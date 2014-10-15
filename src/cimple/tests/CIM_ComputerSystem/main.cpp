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

#include "CIM_ComputerSystem.h"

using namespace cimple;

int main(int argc, char** argv)
{
    CIM_ComputerSystem* inst = CIM_ComputerSystem::create();

    printf("inst->meta_class->name[%s]\n", inst->meta_class->name);


    inst->PrimaryOwnerContact.value = "PrimaryOwnerContact";

    Array<String> Roles;
    Roles.append("passive");
    Roles.append("aggressive");
    inst->Roles.value = Roles;

    Array<uint16> Dedicated;
    Dedicated.append(inst->Dedicated.enum_Unknown);
    Dedicated.append(inst->Dedicated.enum_Other);
    Dedicated.append(inst->Dedicated.enum_Gateway);
    inst->Dedicated.value = Dedicated;

    Array<String> OtherDedicatedDescriptions;
    OtherDedicatedDescriptions.append("red");
    OtherDedicatedDescriptions.append("green");
    OtherDedicatedDescriptions.append("blue");
    inst->OtherDedicatedDescriptions.value = OtherDedicatedDescriptions;

    print(inst);

    return 0;
}

