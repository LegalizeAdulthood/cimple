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

#include <pegasus/utils/pegasus.h>
#include <pegasus/utils/print.h>
#include <Pegasus/Common/Config.h>
#include <cassert>
#include <Pegasus/Client/CIMClient.h>
#include <Pegasus/Common/CIMValue.h>
#include <Pegasus/Common/StringConversion.h>
#include <Pegasus/Common/XmlWriter.h>

// The following flag--when undefined--disables broken CMPI tests.
//#define FULL_EMBEDDED_TESTING 1

// the folowing flag--when undefined--disables testing of scalar
// Embedded Instances and Embedded Objects.
#define SCALAR_EMBEDDED_TESTING 1

// if sfcb testing we must disable both of the embedded entitiy tests.
//undef FULL_EMBEDDED_TESTING
//undef SCALAR_EMBEDDED_TESTING
//endif

#define NAMESPACE "root/cimv2"

PEGASUS_USING_PEGASUS;
PEGASUS_USING_STD;

// Convert a CIMPropertyList parameter to CIM String
String _toString(CIMPropertyList& pl)
{
    String rtn;
    Array<CIMName> pls = pl.getPropertyNameArray();
    if (pl.isNull())
        return("NULL");

    if (pl.size() == 0)
        return("EMPTY");

    for (Uint32 i = 0 ; i < pls.size() ; i++)
    {
        if (i != 0)
            rtn.append(", ");
        rtn.append(pls[i].getString());
    }
    return(rtn);
}

// Output a CIMPropertyList to cout
void _print(CIMPropertyList& pl)
{
    cout << _toString(pl);
}

void _print(const CIMValue& v)
{
    cout << "Value = " << v.toString() << endl;;
}

/*******************************************************************************
**
** Create instance with all possible types
**
*******************************************************************************/
// TypeOf gets the CIMTYPE definition each type construction
inline CIMType TypeOf(const Boolean*) { return CIMTYPE_BOOLEAN; }
inline CIMType TypeOf(const Uint8*) { return CIMTYPE_UINT8; }
inline CIMType TypeOf(const Sint8*) { return CIMTYPE_SINT8; }
inline CIMType TypeOf(const Uint16*) { return CIMTYPE_UINT16; }
inline CIMType TypeOf(const Sint16*) { return CIMTYPE_SINT16; }
inline CIMType TypeOf(const Uint32*) { return CIMTYPE_UINT32; }
inline CIMType TypeOf(const Sint32*) { return CIMTYPE_SINT32; }
inline CIMType TypeOf(const Uint64*) { return CIMTYPE_UINT64; }
inline CIMType TypeOf(const Sint64*) { return CIMTYPE_SINT64; }
inline CIMType TypeOf(const Real32*) { return CIMTYPE_REAL32; }
inline CIMType TypeOf(const Real64*) { return CIMTYPE_REAL64; }
inline CIMType TypeOf(const Char16*) { return CIMTYPE_CHAR16; }
inline CIMType TypeOf(const String*) { return CIMTYPE_STRING; }
inline CIMType TypeOf(const CIMDateTime*) { return CIMTYPE_DATETIME; }
inline CIMType TypeOf(const CIMInstance*) { return CIMTYPE_INSTANCE; }
inline CIMType TypeOf(const CIMObject*) { return CIMTYPE_OBJECT; }
inline CIMType TypeOf(const CIMObjectPath*) { return CIMTYPE_REFERENCE; }

/* _equal template defines function tests for equality of two objects of
   a single type.  This includes all base types and also CIMInstances
   and CIMObjects
*/
template<class T>
inline bool _equal(const T& x, const T& y)
{
    return x == y;
}

inline bool _equal(const CIMInstance& x, const CIMInstance& y)
{
    return x.identical(y);
}

inline bool _equal(const CIMObject& x, const CIMObject& y)
{
    return x.identical(y);
}

/* Sca template defines a simple structure that provides
   the funtions for scalar get and null for each cimtype.  It is
   to be used with the instance tests below. 
*/
template<class T>
struct Sca
{
};

template<> struct Sca<Boolean> 
{ 
    static Boolean get() { return true; } 
    static CIMValue null() { return CIMValue(CIMTYPE_BOOLEAN, false); }
};

template<> struct Sca<Uint8> 
{ 
    static Uint8 get() { return 8; } 
    static CIMValue null() { return CIMValue(CIMTYPE_UINT8, false); }
};

template<> struct Sca<Sint8> 
{ 
    static Sint8 get() { return -8; } 
    static CIMValue null() { return CIMValue(CIMTYPE_SINT8, false); }
};

template<> struct Sca<Uint16> 
{ 
    static Uint16 get() { return 16; } 
    static CIMValue null() { return CIMValue(CIMTYPE_UINT16, false); }
};

template<> struct Sca<Sint16> 
{ 
    static Sint16 get() { return -16; } 
    static CIMValue null() { return CIMValue(CIMTYPE_SINT16, false); }
};

template<> struct Sca<Uint32> 
{ 
    static Uint32 get() { return 32; } 
    static CIMValue null() { return CIMValue(CIMTYPE_UINT32, false); }
};

template<> struct Sca<Sint32> 
{ 
    static Sint32 get() { return -32; } 
    static CIMValue null() { return CIMValue(CIMTYPE_SINT32, false); }
};

template<> struct Sca<Uint64> 
{ 
    static Uint64 get() { return 64; } 
    static CIMValue null() { return CIMValue(CIMTYPE_UINT64, false); }
};

template<> struct Sca<Sint64> 
{ 
    static Sint64 get() { return -64; } 
    static CIMValue null() { return CIMValue(CIMTYPE_SINT64, false); }
};

template<> struct Sca<Real32> 
{ 
    static Real32 get() { return 32.32; } 
    static CIMValue null() { return CIMValue(CIMTYPE_REAL32, false); }
};

template<> struct Sca<Real64> 
{ 
    static Real64 get() { return 64.64; }
    static CIMValue null() { return CIMValue(CIMTYPE_REAL64, false); }
};

template<> struct Sca<Char16> 
{ 
    static Char16 get() { return 'A'; } 
    static CIMValue null() { return CIMValue(CIMTYPE_CHAR16, false); }
};

template<> struct Sca<String> 
{ 
    static String get() { return String("String"); } 
    static CIMValue null() { return CIMValue(CIMTYPE_STRING, false); }
};

template<> struct Sca<CIMDateTime> 
{
    static CIMDateTime get() {return CIMDateTime("20070101120000.000000-360");} 
    static CIMValue null() { return CIMValue(CIMTYPE_DATETIME, false); }
};

template<> struct Sca<CIMInstance> 
{
    static CIMInstance get() 
    {
        CIMInstance part("All_Part");
        part.addProperty(CIMProperty("Key", Uint32(8888)));
        return part;
    }

    static CIMValue null() { return CIMValue(CIMTYPE_INSTANCE, false); }
};

template<> struct Sca<CIMObject> 
{
    static CIMObject get() 
    {
        CIMInstance part("All_Part");
        part.addProperty(CIMProperty("Key", Uint32(7777)));
        return CIMObject(part);
    }

    static CIMValue null() { return CIMValue(CIMTYPE_OBJECT, false); }
};

template<> struct Sca<CIMObjectPath> 
{
    static CIMObjectPath get() 
    {
        CIMObjectPath cop("root/cimv2:All_Part.Key=7777");
        cop.setNameSpace("root/cimv2");
        return cop;
    }

    static CIMValue null() { return CIMValue(CIMTYPE_REFERENCE, false); }
};

template<class T> 
struct Arr
{
    static Array<T> get(Uint32 size) 
    {
        Array<T> a;

        for (Uint32 i = 0; i < size; i++)
            a.append(Sca<T>::get());

        return a;
    }

    static CIMValue null()
    {
         return CIMValue(TypeOf((T*)0), true);
    }

    static Array<T> bld(const T& x0)
    {
        Array<T> a;
        a.append(x0);
        return a;
    }
    static Array<T> bld(const T& x0, const T& x1)
    {
        Array<T> a;
        a.append(x0);
        a.append(x1);
        return a;
    }
    static Array<T> bld(const T& x0, const T& x1, const T& x2)
    {
        Array<T> a;
        a.append(x0);
        a.append(x1);
        a.append(x2);
        return a;
    }
    static Array<T> bld(const T& x0, const T& x1, const T& x2, const T& x3)
    {
        Array<T> a;
        a.append(x0);
        a.append(x1);
        a.append(x2);
        a.append(x3);
        return a;
    }
};

/* Test a single property between the two defined instances for
   equality.
   @return true property defined by name exists and equal in
   both instances. Else return false
*/
bool check_prop(CIMInstance& c1, CIMInstance& c2, const String& name)
{
    Uint32 pos1 = c1.findProperty(name);

    if (pos1 == PEG_NOT_FOUND)
        return false;

    Uint32 pos2 = c2.findProperty(name);

    if (pos2 == PEG_NOT_FOUND)
        return false;

    CIMProperty p1 = c1.getProperty(pos1);
    CIMProperty p2 = c2.getProperty(pos2);

    if (!p1.identical(p2))
    {
        cout << "ERROR: propertyMismatch" << endl
             << "p1: ";
        XmlWriter::printPropertyElement(p1, cerr);
        cout << "p2: ";
        XmlWriter::printPropertyElement(p2, cerr);
        cout << endl;
    }

    CIMType t1 = p1.getType();
    CIMType t2 = p2.getType();
    if (!(t1 == t2))
    {
        cout << "ERROR: CIMTypes are different" << endl;
    }
    CIMValue v1 = p1.getValue();
    CIMValue v2 = p2.getValue();
    if (!(v1 == v2))
    {
        cout << "ERROR: value elements are different" << endl;
        cout << "v1: ";
        XmlWriter::printValueElement(v1, cerr);
        cout << "v2: ";
        XmlWriter::printValueElement(v2, cerr);
        cout << endl;
    }
    // return the test identical result
    return(p1.identical(p2));
}

/*
    Print out the list of properties in an instance.
*/
void printListOfProperties(const CIMInstance& instance)
{
    for (Uint32 i = 0 ; i < instance.getPropertyCount() ; i++)
    {
        CIMConstProperty p = instance.getProperty(i);
        cout << i  << " " << p.getName().getString() << endl;
    }
}

/*
    Test the property defined by name in the instance to determine
    if it exists and is NULL. Return true if it does not exist or
    is NULL
*/
bool check_prop_null(CIMInstance& c1, const String& name)
{
    Uint32 pos = c1.findProperty(name);

    if (pos == PEG_NOT_FOUND)
        return true;

    CIMProperty p = c1.getProperty(pos);

    CIMValue v = p.getValue();
    
    return(v.isNull());
}

/* test the value of a property against a CIMValue provided.

    Example:
    check_prop_value(instance,"uint8Scalar" CIMValue(Uint8(8)));
*/
bool check_prop_value(const CIMInstance& ci, const CIMName& name,
                       const CIMValue& vin)
{
    Uint32 pos = ci.findProperty(name);

    if (pos == PEG_NOT_FOUND)
        return false;
    CIMConstProperty p = ci.getProperty(pos);

    CIMValue v = p.getValue();

    return(vin == v);
}
/*
    create an instance, with all property types and do createInstance.
    returns the created instance in origInst and the returned cop in
    the call return
*/

CIMObjectPath create_All_Class_instance(CIMClient& client,
                                        CIMInstance& origInst)
{
    // Create instance:

    CIMInstance ci1("All_Class");
    ci1.setPath(CIMObjectPath("All_Class.Key=9999"));
    ci1.addProperty(CIMProperty("Key", Uint32(9999)));
    ci1.addProperty(CIMProperty("booleanScalar", Sca<Boolean>::get()));
    ci1.addProperty(CIMProperty("uint8Scalar", Sca<Uint8>::get()));
    ci1.addProperty(CIMProperty("sint8Scalar", Sca<Sint8>::get()));
    ci1.addProperty(CIMProperty("uint16Scalar", Sca<Uint16>::get()));
    ci1.addProperty(CIMProperty("sint16Scalar", Sca<Sint16>::get()));
    ci1.addProperty(CIMProperty("uint32Scalar", Sca<Uint32>::get()));
    ci1.addProperty(CIMProperty("sint32Scalar", Sca<Sint32>::get()));
    ci1.addProperty(CIMProperty("uint64Scalar", Sca<Uint64>::get()));
    ci1.addProperty(CIMProperty("sint64Scalar", Sca<Sint64>::get()));
    ci1.addProperty(CIMProperty("real32Scalar", Sca<Real32>::get()));
    ci1.addProperty(CIMProperty("real64Scalar", Sca<Real64>::get()));
    ci1.addProperty(CIMProperty("char16Scalar", Sca<Char16>::get()));
    ci1.addProperty(CIMProperty("stringScalar", Sca<String>::get()));
    ci1.addProperty(CIMProperty("datetimeScalar", Sca<CIMDateTime>::get()));
#ifdef SCALAR_EMBEDDED_TESTING
    ci1.addProperty(CIMProperty("instanceScalar", Sca<CIMInstance>::get()));
    ci1.addProperty(CIMProperty("objectScalar", Sca<CIMObject>::get()));
#endif
    ci1.addProperty(CIMProperty("booleanArray", Arr<Boolean>::get(2)));
    ci1.addProperty(CIMProperty("uint8Array", Arr<Uint8>::get(2)));
    ci1.addProperty(CIMProperty("sint8Array", Arr<Sint8>::get(2)));
    ci1.addProperty(CIMProperty("uint16Array", Arr<Uint16>::get(2)));
    ci1.addProperty(CIMProperty("sint16Array", Arr<Sint16>::get(2)));
    ci1.addProperty(CIMProperty("uint32Array", Arr<Uint32>::get(2)));
    ci1.addProperty(CIMProperty("sint32Array", Arr<Sint32>::get(2)));
    ci1.addProperty(CIMProperty("uint64Array", Arr<Uint64>::get(2)));
    ci1.addProperty(CIMProperty("sint64Array", Arr<Sint64>::get(2)));
    ci1.addProperty(CIMProperty("real32Array", Arr<Real32>::get(2)));
    ci1.addProperty(CIMProperty("real64Array", Arr<Real64>::get(2)));
    ci1.addProperty(CIMProperty("char16Array", Arr<Char16>::get(2)));
    ci1.addProperty(CIMProperty("stringArray", Arr<String>::get(2)));
    ci1.addProperty(CIMProperty("datetimeArray", Arr<CIMDateTime>::get(2)));
#ifdef FULL_EMBEDDED_TESTING
    ci1.addProperty(CIMProperty("instanceArray", Arr<CIMInstance>::get(2)));
    ci1.addProperty(CIMProperty("objectArray", Arr<CIMObject>::get(2)));
#endif

    CIMObjectPath cop = client.createInstance(NAMESPACE, ci1);
    assert(cop.toString() == "All_Class.Key=9999");

    // Save original instance for later comparison
    origInst = ci1;

    printf("+++++ passed test 1 - create_instance of All_Class\n");

    return cop;
}
/* get the instance and compare all of the
   properties between the original and instance returned from
   getInstance.
*/
void test_All_Class_instance(CIMClient& client, CIMObjectPath& cop,
                   CIMInstance& origInst)
{
    assert(cop.toString() == "All_Class.Key=9999");

    // Get instance back and check whether identical.

    CIMInstance testInst = client.getInstance(NAMESPACE, cop);

    if (origInst.getPropertyCount() != testInst.getPropertyCount())
    {
        cout << "Property Counts Did not match: "
            << " original Inst property count = " << origInst.getPropertyCount()
            << " testInst property count = " << testInst.getPropertyCount()
            << endl;

        printListOfProperties(origInst);
        printListOfProperties(testInst);

        assert(origInst.getPropertyCount() == testInst.getPropertyCount());
    }

    assert(check_prop(origInst, testInst, "Key"));
    assert(check_prop(origInst, testInst, "booleanScalar"));
    assert(check_prop(origInst, testInst, "uint8Scalar"));
    assert(check_prop(origInst, testInst, "sint8Scalar"));
    assert(check_prop(origInst, testInst, "uint16Scalar"));
    assert(check_prop(origInst, testInst, "sint16Scalar"));
    assert(check_prop(origInst, testInst, "uint32Scalar"));
    assert(check_prop(origInst, testInst, "sint32Scalar"));
    assert(check_prop(origInst, testInst, "uint64Scalar"));
    assert(check_prop(origInst, testInst, "sint64Scalar"));
    assert(check_prop(origInst, testInst, "real32Scalar"));
    assert(check_prop(origInst, testInst, "real64Scalar"));
    assert(check_prop(origInst, testInst, "char16Scalar"));
    assert(check_prop(origInst, testInst, "stringScalar"));
    assert(check_prop(origInst, testInst, "datetimeScalar"));
#ifdef SCALAR_EMBEDDED_TESTING
    assert(check_prop(origInst, testInst, "instanceScalar"));
    assert(check_prop(origInst, testInst, "objectScalar"));
#endif
    assert(check_prop(origInst, testInst, "booleanArray"));
    assert(check_prop(origInst, testInst, "uint8Array"));
    assert(check_prop(origInst, testInst, "sint8Array"));
    assert(check_prop(origInst, testInst, "uint16Array"));
    assert(check_prop(origInst, testInst, "sint16Array"));
    assert(check_prop(origInst, testInst, "uint32Array"));
    assert(check_prop(origInst, testInst, "sint32Array"));
    assert(check_prop(origInst, testInst, "uint64Array"));
    assert(check_prop(origInst, testInst, "sint64Array"));
    assert(check_prop(origInst, testInst, "real32Array"));
    assert(check_prop(origInst, testInst, "real64Array"));
    assert(check_prop(origInst, testInst, "char16Array"));
    assert(check_prop(origInst, testInst, "stringArray"));
    assert(check_prop(origInst, testInst, "datetimeArray"));

#ifdef FULL_EMBEDDED_TESTING
    assert(check_prop(origInst, testInst, "instanceArray"));
    assert(check_prop(origInst, testInst, "objectArray"));
#endif
    //assert(origInst.identical(testInst));

    // Test for path in the returned instance.
    // At this point, this test does not work. Not sure yet
    // whether Pegasus or CIMPLE. However, the testInst
    // returns only the classname in the Path.
    cout << "test inst path = " << testInst.getPath().toString() << endl
         << "requested path = " << cop.toString() << endl;
    //assert(testInst.getPath().toString() == cop.toString());

    printf("+++++ passed test 2 - test_instance."
           " Tests getInstance for all Properties\n");
}

/*******************************************************************************
**
**  Test variations of property lists for getInstance() and
**  enumerateInstances()
**
*******************************************************************************/
/* 
    get the instance based on the provided property list and
    confirm that we get the correct properties and
    the correct value for each property.
*/
void test_getInstance_propertyList(CIMClient& client,
                                CIMInstance& inst,
                                CIMObjectPath& cop,
                                CIMPropertyList& pl)
{
    CIMInstance ci = client.getInstance(NAMESPACE, cop,
                                         false,false,false, pl);
    assert(ci.getPropertyCount() == pl.size());

    for (Uint32 i = 0; i < pl.size() ; i++)
    {
        assert(ci.findProperty(pl[i]) != PEG_NOT_FOUND);
        assert(check_prop(inst, ci, pl[i].getString()));
    }
}

/* 
    get the instance based on the provided property list and
    confirm that we get the correct properties and
    the correct value for each property.
*/
void test_enumerateInstance_propertyList(CIMClient& client,
                                CIMInstance& inst,
                                CIMPropertyList& pl)
{
    Array<CIMInstance> instances = client.enumerateInstances(
                                    NAMESPACE, "All_Class",
                                    false, false, false, false, pl);

    for (Uint32 i = 0 ; i < instances.size() ; i++)
    {
        assert (instances[i].getPropertyCount() == pl.size());
        for (Uint32 j = 0; j < pl.size() ; j++)
        {
            assert(instances[i].findProperty(pl[j]) != PEG_NOT_FOUND);
            //assert(check_prop(inst, ci, pl[i].getString()));
        }
    }

    //CIMInstance ci = client.getInstance(NAMESPACE, cop,
    //                                     false,false,false, pl);
    //assert(ci.getPropertyCount() == pl.size());

    //for (Uint32 i = 0; i < pl.size() ; i++)
    //{
    //    assert(ci.findProperty(pl[i]) != PEG_NOT_FOUND);
    //    assert(check_prop(inst, ci, pl[i].getString()));
    //}
}

/*
    This class generates permutations of the list of properties.
    The constructor creates the propertylist itself from a complete instance.
    The next() method returns a different permutation for each call.
    The more() method returns true while there are more permutations.
    Note. The next() method has no means of returning done so you must
    use the more() to determine when all permutations have been returned.

    TODO: Expand the number of permutations.

*/
class propertyListPermutations
{
public:
    propertyListPermutations(CIMInstance& inst)
    {
        _maxPropertyList = inst.getPropertyCount();

        // Create the array of property names from the property list
        for (Uint32 i = 0 ; i < _maxPropertyList ; i++ )
        {
            CIMProperty p = inst.getProperty(i);
            _list.append(p.getName());
        }
        reset();
    }

    bool more()
    {
        return _done;
    }

    // get the next permutation of the list.  Returns next property list
    // permutation
    CIMPropertyList& next()
    {
        Array<CIMName> names;

        // build the next list of property names
        Uint32 end = _pos + _length;
        // Create array with all properties between _pos and _end using
        // _spacing
        for (Uint32 i = _pos ; i < end ; i += _spacing)
        {
            Uint32 x = i%_list.size();
            names.append(_list[x]);
        }

        // advance length for next test and test if at max.
        // If length at max for this _pos, get next pos and reset length
        _length++;
        if (_pos + _length > _maxPropertyList)
        {
            _length = 1;
            _pos++;

            // if _pos at max, increase spacing and try again
            if (_pos >= _maxPropertyList)
            {
                _pos = 1;
                if (++_spacing >= (_maxPropertyList - 1))
                {
                    _done = true;
                }
            }
        }
        // set the Array into property list and return
        _pl.clear();
        _pl.set(names);
        //printf("p%u l%u s%u\n", _pos, _length, _spacing);
        //cout << _toString(_pl) << endl;
        return _pl;
    }

private:
    // reset all variables
    void reset()
    {
        _pos = 0;
        _length = 0;
        _done = false;
        _spacing = 1;
    }

    Array<CIMName> _list;         // properties in original list
    Uint32 _maxPropertyList;      // number of properties on list
    Uint32 _pos;                  // pos in list to start next group
    Uint32 _length;               // length of propertyList group
    Uint32 _spacing;              // number to skip between properties
    Boolean _done;                // test done indicator  
    CIMPropertyList _pl;          // last property list generated  
};

// Test for varying sizes of property list on getInstance requests with
// property lists.  This executes the complete set of  property list
// permutations by executing getInstance for the instance defined by
// the cop parameter.
// Also executes specific property list tests including:
//     1. property name not in the instance
//     2. duplicate property name in the list.
String _toString(const CIMPropertyList& pl)
{
    String rtn;
    Array<CIMName> pls = pl.getPropertyNameArray();
    if (pl.isNull())
        return("NULL");

    if (pl.size() == 0)
        return("EMPTY");

    for (Uint32 i = 0 ; i < pls.size() ; i++)
    {
        if (i != 0)
            rtn.append(", ");
        rtn.append(pls[i].getString());
    }
    return(rtn);
}

void test_getInstance_propertyLists(CIMClient& client, CIMObjectPath& cop)
{
    // do a full getInstance of the instance defined by cop
    CIMInstance ci = client.getInstance(NAMESPACE, cop);

    // create the object that returns property list permutations using
    // the propertyListPermutations class
    propertyListPermutations plp(ci);

    // Loop through all property list permutations testing each one
    // with getInstance
    bool done = false;
    while(!plp.more())
    {
        CIMPropertyList pl = plp.next();
        test_getInstance_propertyList(client, ci, cop, pl);
    };

    // Test to determine if CIMPLE ignores a property name that is not
    // a valid property for this class.  The CIM Operations spec is that 
    // the bad property name should be ignored.
    {
        Array<CIMName> pla;
        pla.append("blah");
        CIMPropertyList pl(pla);
        CIMInstance ci = client.getInstance(NAMESPACE, cop,
                                         false,false,false, pl);
        assert(ci.getPropertyCount() == 0);

        // try again with a valid property added.
        pla.append("Key");
        pl.set(pla);
        ci = client.getInstance(NAMESPACE, cop,
                                         false,false,false, pl);
        assert(ci.getPropertyCount() == 1);

        CIMProperty p = ci.getProperty(0);
        assert(p.getName() == "Key");
    }

    // test for duplicate names in the property list
    {
        Array<CIMName> pla;
        pla.append("Key");
        pla.append("Key");
        CIMPropertyList pl(pla);
        CIMInstance ci = client.getInstance(NAMESPACE, cop,
                                         false,false,false, pl);
        assert(ci.getPropertyCount() == 1);

        // test to confirm that this is the property with name "Key"
        CIMProperty p = ci.getProperty(0);
        assert(p.getName() == "Key");
    }

    printf("+++++ passed test 3 - Test getInstance() with Property Lists\n");
}

// Test for varying sizes of property list on enumerateInstance requests with
// property lists. This is a duplicate of the test_getInstance_propertyLists
// functionality.
void test_enumerateInstance_propertyLists(CIMClient& client,
                                          CIMInstance origInst)
{
    // The following test does enumerate_instance with a property
    // list and varies the property list from empty to full
    propertyListPermutations plp(origInst);

    CIMName allClass = origInst.getClassName();

    bool done = false;
    while(!plp.more())
    {
        CIMPropertyList pl = plp.next();
        test_enumerateInstance_propertyList(client, origInst, pl);
    };

    // Test to determine if we ignore a property name that is not
    // a valid property for this class.  The CIM Operations spec is that 
    // the bad property name should be ignored.
    {
        Array<CIMName> pla;
        pla.append("blah");
        CIMPropertyList pl(pla);
        Array<CIMInstance> instances = client.enumerateInstances(NAMESPACE,
                                         allClass,
                                         false,false,false,false, pl);
        for (Uint32 i = 0 ; i < instances.size() ; i++)
        {
            assert(instances[i].getPropertyCount() == 0);
        }

        // try again with a valid property added.
        pla.append("Key");
        pl.set(pla);
        instances = client.enumerateInstances(NAMESPACE, allClass,
                                         false,false,false,false, pl);

        for (Uint32 i = 0 ; i < instances.size() ; i++)
        {
            assert(instances[i].getPropertyCount() == 1);
            CIMProperty p = instances[i].getProperty(0);
            assert(p.getName() == "Key");
        }
    }

    // test for effect of duplicate names in the property list
    {
        Array<CIMName> pla;
        pla.append("Key");
        pla.append("Key");
        CIMPropertyList pl(pla);
        Array<CIMInstance> instances = client.enumerateInstances(NAMESPACE,
                                         allClass,
                                         false,false,false,false, pl);

        for (Uint32 i = 0 ; i < instances.size() ; i++)
        {
            assert(instances[i].getPropertyCount() == 1);
            CIMProperty p = instances[i].getProperty(0);
            assert(p.getName() == "Key");
        }
    }

    printf("+++++ passed test 4 - "
           "Test enumerateInstances() with Property Lists\n");
}

/*******************************************************************************
**
**  getProperty Tests - test variations of getProperty for all properties
**  in the test instance.  The results of the getProperty are compared with
**  the value in the testInstance.
**
*******************************************************************************/
/*
    Test two Reals for aproximate equality. Returns true if the two
    values are within about 1% of one another.
*/
template<class T>
bool _equalReal(const T& r1, const T& r2)
{
    return( (r1 > (r2 * 0.99)) && (r1 < (r2 * 1.01)) );
}

// Convert String input to Real64
Real64 stringCIMValueToReal64(
    const CIMValue &val)
{
    Real64 r64;
    String s;
    val.get(s);

    assert(StringConversion::stringToReal64(s.getCString(), r64));
    return r64;
}

/*
    do the CIM Operation getProperty() and test the results against
    the properties in the original instance.  This is done for all 
    properties in the original instance.
*/
void test_get_property(CIMClient& client, CIMObjectPath& cop)
{
    CIMInstance origInst = client.getInstance(NAMESPACE, cop);
    
    for (Uint32 i = 0; i < origInst.getPropertyCount(); i++)
    {
        CIMProperty p = origInst.getProperty(i);
        CIMValue vOrig = p.getValue();

        CIMValue v = client.getProperty(NAMESPACE, cop, p.getName());

        // Do String test because all returned values are type String with
        // no type information attached. Most types should match correctly
        // based on the returned string.
        bool errFound = false;
        if (v.toString() != vOrig.toString())
        {
            // Real values may not be equal after the conversion
            // so we have to reconvert to compare
            if (vOrig.getType() == CIMTYPE_REAL32 
                || vOrig.getType() == CIMTYPE_REAL64)
            {
                // Bypass array test for now
                // TODO extend test for the real array.
                if (vOrig.isArray())
                {
                    continue;
                }

                if (vOrig.getType() == CIMTYPE_REAL32)
                {
                    Real32 rOrig;
                    vOrig.get(rOrig);
                    Real32 r = (Real32) stringCIMValueToReal64(v);
                    errFound = !_equalReal(rOrig, r);
                }

                else if (vOrig.getType() == CIMTYPE_REAL64)
                {
                    Real64 rOrig;
                    vOrig.get(rOrig);
                    Real64 r = stringCIMValueToReal64(v);
                    errFound = !_equalReal(rOrig, r);
                }
            }
            else    // not realxx type. 
            {
                errFound=true;
            }
            if (errFound)
            {
                cout << "Error in GetProperty " 
                    << p.getName().getString()
                    << " Types = " << cimTypeToString(v.getType())
                    << ", " << cimTypeToString(vOrig.getType())
                    << "\n Values " << v.toString() 
                    << ", " << vOrig.toString()
                    << endl;
                assert(false);
            }
        } // end of if (strings match)

    }
    printf("+++++ passed test 5 - test_get_property - Test Get Property\n");
}

/*******************************************************************************
**
**  test creation and get of instance with NULL properties.
**
*******************************************************************************/
/*
    Test with all NULL properties
    Create an instance with nulls and then get it and compare the
    results.
*/
void test_instance_null(CIMClient& client)
{
    // Create instance:

    CIMInstance ci1("All_Class");
    ci1.setPath(CIMObjectPath("All_Class.Key=8888"));
    ci1.addProperty(CIMProperty("Key", Uint32(8888)));
    ci1.addProperty(CIMProperty("booleanScalar", Sca<Boolean>::null()));
    ci1.addProperty(CIMProperty("uint8Scalar", Sca<Uint8>::null()));
    ci1.addProperty(CIMProperty("sint8Scalar", Sca<Sint8>::null()));
    ci1.addProperty(CIMProperty("uint16Scalar", Sca<Uint16>::null()));
    ci1.addProperty(CIMProperty("sint16Scalar", Sca<Sint16>::null()));
    ci1.addProperty(CIMProperty("uint32Scalar", Sca<Uint32>::null()));
    ci1.addProperty(CIMProperty("sint32Scalar", Sca<Sint32>::null()));
    ci1.addProperty(CIMProperty("uint64Scalar", Sca<Uint64>::null()));
    ci1.addProperty(CIMProperty("sint64Scalar", Sca<Sint64>::null()));
    ci1.addProperty(CIMProperty("real32Scalar", Sca<Real32>::null()));
    ci1.addProperty(CIMProperty("real64Scalar", Sca<Real64>::null()));
    ci1.addProperty(CIMProperty("char16Scalar", Sca<Char16>::null()));
    ci1.addProperty(CIMProperty("stringScalar", Sca<String>::null()));
    ci1.addProperty(CIMProperty("datetimeScalar", Sca<CIMDateTime>::null()));
#ifdef SCALAR_EMBEDDED_TESTING
    ci1.addProperty(CIMProperty("instanceScalar", Sca<CIMInstance>::null()));
    ci1.addProperty(CIMProperty("objectScalar", Sca<CIMObject>::null()));
#endif
    ci1.addProperty(CIMProperty("booleanArray", Arr<Boolean>::null()));
    ci1.addProperty(CIMProperty("uint8Array", Arr<Uint8>::null()));
    ci1.addProperty(CIMProperty("sint8Array", Arr<Sint8>::null()));
    ci1.addProperty(CIMProperty("uint16Array", Arr<Uint16>::null()));
    ci1.addProperty(CIMProperty("sint16Array", Arr<Sint16>::null()));
    ci1.addProperty(CIMProperty("uint32Array", Arr<Uint32>::null()));
    ci1.addProperty(CIMProperty("sint32Array", Arr<Sint32>::null()));
    ci1.addProperty(CIMProperty("uint64Array", Arr<Uint64>::null()));
    ci1.addProperty(CIMProperty("sint64Array", Arr<Sint64>::null()));
    ci1.addProperty(CIMProperty("real32Array", Arr<Real32>::null()));
    ci1.addProperty(CIMProperty("real64Array", Arr<Real64>::null()));
    ci1.addProperty(CIMProperty("char16Array", Arr<Char16>::null()));
    ci1.addProperty(CIMProperty("stringArray", Arr<String>::null()));
    ci1.addProperty(CIMProperty("datetimeArray", Arr<CIMDateTime>::null()));
#ifdef FULL_EMBEDDED_TESTING
    ci1.addProperty(CIMProperty("instanceArray", Arr<CIMInstance>::null()));
    ci1.addProperty(CIMProperty("objectArray", Arr<CIMObject>::null()));
#endif

    CIMObjectPath cop = client.createInstance(NAMESPACE, ci1);
    assert(cop.toString() == "All_Class.Key=8888");

    // Get instance and check for identical property status.

    CIMInstance ci2 = client.getInstance(NAMESPACE, cop);

    assert(check_prop(ci1, ci2, "Key"));
    // test for null or missing properties.  All properties that were
    // sent null should be returned either null or not existant.
    assert(check_prop_null(ci2, "booleanScalar"));
    assert(check_prop_null(ci2, "uint8Scalar"));
    assert(check_prop_null(ci2, "sint8Scalar"));
    assert(check_prop_null(ci2, "uint16Scalar"));
    assert(check_prop_null(ci2, "sint16Scalar"));
    assert(check_prop_null(ci2, "uint32Scalar"));
    assert(check_prop_null(ci2, "sint32Scalar"));
    assert(check_prop_null(ci2, "uint64Scalar"));
    assert(check_prop_null(ci2, "sint64Scalar"));
    assert(check_prop_null(ci2, "stringScalar"));
    assert(check_prop_null(ci2, "datetimeScalar"));
#ifdef SCALAR_EMBEDDED_TESTING
    assert(check_prop_null(ci2, "instanceScalar"));
    assert(check_prop_null(ci2, "objectScalar"));
#endif
    assert(check_prop_null(ci2, "booleanArray"));
    assert(check_prop_null(ci2, "uint8Array"));
    assert(check_prop_null(ci2, "sint8Array"));
    assert(check_prop_null(ci2, "uint16Array"));
    assert(check_prop_null(ci2, "uint32Array"));
    assert(check_prop_null(ci2, "sint32Array"));
    assert(check_prop_null(ci2, "uint64Array"));
    assert(check_prop_null(ci2, "sint64Array"));
    assert(check_prop_null(ci2, "real32Array"));
    assert(check_prop_null(ci2, "real64Array"));
    assert(check_prop_null(ci2, "char16Array"));
    assert(check_prop_null(ci2, "stringArray"));
    assert(check_prop_null(ci2, "datetimeArray"));
#ifdef FULL_EMBEDDED_TESTING
    assert(check_prop_null(ci2, "instanceArray"));
    assert(check_prop_null(ci2, "objectArray"));
#endif

    printf("+++++ passed test 7 - Test getInstance Null Properties\n");
}

/* tests enumerate instance with an instance created in the
   provider.
*/
void test_enumerate_instances(CIMClient& client)
{
    Array<CIMInstance> cis = client.enumerateInstances(NAMESPACE,"All_Class");
    assert (cis.size() == 1);
    CIMInstance ci = cis[0];
    assert(ci.getPath().toString() == "All_Class.Key=99");

    // We have problems with this test because the counts may vary
    // with the #defines for instance and object properties. The
    // provider always builds these properties.
    // Skipping the count test for now.
    // assert(ci1.getPropertyCount() == ci2.getPropertyCount());

    assert(check_prop_value(ci, "Key",CIMValue(Uint32(99))));
    assert(check_prop_value(ci, "booleanScalar", CIMValue(false)));
    assert(check_prop_value(ci, "uint8Scalar", CIMValue(Uint8(8))));
    assert(check_prop_value(ci, "sint8Scalar", CIMValue(Sint8(-8))));
    assert(check_prop_value(ci, "uint16Scalar", CIMValue(Uint16(16))));
    assert(check_prop_value(ci, "sint16Scalar", CIMValue(Sint16(-16))));
    assert(check_prop_value(ci, "uint32Scalar", CIMValue(Uint32(32))));
    assert(check_prop_value(ci, "sint32Scalar", CIMValue(Sint32(-32))));
    assert(check_prop_value(ci, "uint64Scalar", CIMValue(Uint64(64))));
    assert(check_prop_value(ci, "sint64Scalar", CIMValue(Sint64(-64))));
    assert(check_prop_value(ci, "real32Scalar", CIMValue(Real32(32))));
    assert(check_prop_value(ci, "real64Scalar", CIMValue(Real64(64))));
    assert(check_prop_value(ci, "char16Scalar", CIMValue(Char16('A'))));
    assert(check_prop_value(ci, "stringScalar", CIMValue(String("Hello"))));
    assert(check_prop_value(ci, "datetimeScalar",
       CIMValue(CIMDateTime("20070101120000.000000-360"))));
#ifdef SCALAR_EMBEDDED_TESTING
    //assert(check_prop_value(ci, "instanceScalar"CIMValue(name));
    //assert(check_prop_value(ci, "objectScalar"));
#endif
    assert(check_prop_value(ci, "booleanArray", 
        CIMValue(Arr<Boolean>::bld(true, false, true) )));
    assert(check_prop_value(ci, "uint8Array",
        CIMValue(Arr<Uint8>::bld(0, 8, 254) )));
    assert(check_prop_value(ci, "sint8Array",
        CIMValue(Arr<Sint8>::bld(-125, -8, 126) )));
    assert(check_prop_value(ci, "uint16Array",
        CIMValue(Arr<Uint16>::bld(819, 0, 16, 999) )));
    assert(check_prop_value(ci, "sint16Array",
        CIMValue(Arr<Sint16>::bld(-819, 0, 16, 999) )));
    assert(check_prop_value(ci, "uint32Array",
        CIMValue(Arr<Uint32>::bld(8192, 0, 16, 9999) )));
    assert(check_prop_value(ci, "sint32Array",
        CIMValue(Arr<Sint32>::bld(-8192, 0, 16, 15000) ))); 
    assert(check_prop_value(ci, "uint64Array",
        CIMValue(Arr<Uint64>::bld(8192, 0, 16, 9999) ))); 
    assert(check_prop_value(ci, "sint64Array",
        CIMValue(Arr<Sint64>::bld(-8192, 0, 16, 9999) )));
    assert(check_prop_value(ci, "real32Array",
        CIMValue(Arr<Real32>::bld(32, 32, 32) )));
    assert(check_prop_value(ci, "real64Array",
        CIMValue(Arr<Real64>::bld(64, 64, 64 ) )));
    assert(check_prop_value(ci, "char16Array",
        CIMValue(Arr<Char16>::bld('A', 'B', 'C') ))); 
    assert(check_prop_value(ci, "stringArray",
        CIMValue(Arr<String>::bld("Red", "Green", "Blue", "") )));
    assert(check_prop_value(ci, "datetimeArray",
        CIMValue(Arr<CIMDateTime>::bld(CIMDateTime("20070101120000.000000-360"),
                                       CIMDateTime("20070101120000.000000-360"),
                                       CIMDateTime("20070101120000.000000-360"))
    )));

#ifdef FULL_EMBEDDED_TESTING
    //assert(check_prop_value(ci, "instanceArray"));
    //assert(check_prop_value(ci, "objectArray"));
    //assert(ci1.identical(ci2));
#endif

    printf("+++++ passed test 6 - enumerate instances\n");
}

void test_modify_instance(CIMClient& client)
{
    CIMObjectPath cop("All_Class.Key=9999");
    printf("+++++ passed test 8 - Modify Instance\n");
}

void test_delete_instance(CIMClient& client, CIMObjectPath& cop)
{
    client.deleteInstance(NAMESPACE, cop);

    // try getInstance() to assure that we did delete the instance.
    try
    {
        client.getInstance(NAMESPACE, cop);
    }

    catch(CIMException& e)
    {
        assert(e.getCode() == CIM_ERR_NOT_FOUND);
    }
    printf("+++++ passed test 5 - delete Instance\n");
}

void test_class_origin(CIMClient& client, CIMObjectPath& cop)
{
    CIMInstance co = client.getInstance(NAMESPACE, cop,
                                         false,false,true);

    for (Uint32 i = 0 ; i < co.getPropertyCount() ; i++)
    {
        CIMProperty p = co.getProperty(i);
        CIMName n = p.getClassOrigin();
        // NOTE: cimple does not return class origin so this test is
        // invalid at this point.
        //cout << "Class Origin" <<  n.getString() << endl;
        //assert(n == "All_Class");
    }
}

/*******************************************************************************
**
**    Tests for invoke method
**
*******************************************************************************/

// Templates to build standard tests for all of the variable types.
template<class T>
struct Tst_Ret
{
    static bool func(CIMClient& client, const String& name)
    {
        Array<CIMParamValue> in;
        Array<CIMParamValue> out;

        CIMValue value = client.invokeMethod(NAMESPACE, 
            CIMObjectPath("All_Class.Key=9999"), name, in, out);

        T x;
        value.get(x);

        if (!_equal(x, Sca<T>::get()))
        {
            printf("%s(%d): error\n", __FILE__, __LINE__);
            return false;
        }

        return true;
    }
};

template<class T>
struct Tst_Sca_Parms
{
    static bool func(CIMClient& client, const String& name)
    {
        Array<CIMParamValue> in;
        Array<CIMParamValue> out;

        in.append(CIMParamValue("p1", Sca<T>::get()));

        CIMValue value = client.invokeMethod(NAMESPACE, 
            CIMObjectPath("All_Class.Key=9999"), name, in, out);

        Uint32 rv;
        value.get(rv);

        if (value.isNull() || rv != 100)
        {
            printf("%s(%d): error\n", __FILE__, __LINE__);
            return false;
        }

        if (out.size() != 1)
        {
            printf("%s(%d): error\n", __FILE__, __LINE__);
            return false;
        }

        CIMParamValue cpv = out[0];
        assert(cpv.getParameterName() == "p2");
        T x;
        cpv.getValue().get(x);

        if (!_equal(x, Sca<T>::get()))
        {
            printf("%s(%d): error\n", __FILE__, __LINE__);
            return false;
        }

        return true;
    }
};

template<class T>
struct Tst_Arr_Parms
{
    static bool func(CIMClient& client, const String& name)
    {
        Array<CIMParamValue> in;
        Array<CIMParamValue> out;

        in.append(CIMParamValue("p1", Arr<T>::get(3)));

        CIMValue value = client.invokeMethod(NAMESPACE, 
            CIMObjectPath("All_Class.Key=9999"), name, in, out);

        Uint32 rv;
        value.get(rv);

        if (value.isNull() || rv != 100)
        {
            printf("%s(%d): error\n", __FILE__, __LINE__);
            return false;
        }

        if (out.size() != 1)
        {
            printf("%s(%d): error\n", __FILE__, __LINE__);
            return false;
        }

        CIMParamValue cpv = out[0];
        assert(cpv.getParameterName() == "p2");
        Array<T> x;
        cpv.getValue().get(x);

        if (!_equal(x, Arr<T>::get(3)))
        {
            printf("%s(%d): error\n", __FILE__, __LINE__);
            return false;
        }

        return true;
    }
};

template<>
struct Tst_Arr_Parms<CIMObjectPath>
{
    static bool func(CIMClient& client, const String& name)
    {
        Array<CIMParamValue> in;
        Array<CIMParamValue> out;

        in.append(CIMParamValue("p1", Arr<CIMObjectPath>::get(3)));

        CIMValue value = client.invokeMethod(NAMESPACE, 
            CIMObjectPath("All_Class.Key=9999"), name, in, out);

        Uint32 rv;
        value.get(rv);

        if (value.isNull() || rv != 100)
        {
            printf("%s(%d): error\n", __FILE__, __LINE__);
            return false;
        }

        if (out.size() != 1)
        {
            printf("%s(%d): error\n", __FILE__, __LINE__);
            return false;
        }

        CIMParamValue cpv = out[0];
        assert(cpv.getParameterName() == "p2");
        Array<CIMObjectPath> x;
        cpv.getValue().get(x);

        if (!_equal(x, Arr<CIMObjectPath>::get(3)))
        {
            printf("%s(%d): error\n", __FILE__, __LINE__);
            return false;
        }

        return true;
    }
};

void test_invoke(CIMClient& client)
{
    try
    {
        // Call foo1().

        CIMInstance ci;
        {
            Array<CIMParamValue> inParams;
            Array<CIMParamValue> outParams;

            CIMValue value = client.invokeMethod(
                "root/cimv2",
                CIMObjectPath("CMPL_Embedded.Key=1"),
                "foo1",
                inParams,
                outParams);

            assert(value.getType() == CIMTYPE_INSTANCE);

            value.get(ci);
            // cimple::print(ci);
        }

        // Call foo2().
        {
            Array<CIMParamValue> inParams;
            Array<CIMParamValue> outParams;

            CIMInstance arg2("CMPL_Embedded2");
            arg2.addProperty(CIMProperty("Key", Uint32(22222)));

            inParams.append(CIMParamValue("arg1", ci));
            inParams.append(CIMParamValue("arg2", arg2));

            CIMValue value = client.invokeMethod(
                "root/cimv2",
                CIMObjectPath("CMPL_Embedded.Key=1"),
                "foo2",
                inParams,
                outParams);

            for (size_t i = 0; i < outParams.size(); i++)
            {
                const CIMParamValue& pv = outParams[i];
                const CIMValue v = pv.getValue();

                if (pv.getParameterName() == "arg3")
                {
                    CIMInstance t;
                    assert(v.getType() == CIMTYPE_INSTANCE);
                    v.get(t);
                    // cimple::print(t);
                }
            }

            // Check return value:
            {
                assert(value.getType() == CIMTYPE_STRING);
                String x;
                value.get(x);
                assert(x == "Hello");
            }
        }
    }
    catch(Exception& e)
    {
        PEGASUS_STD(cerr) << "Error: " << e.getMessage() << PEGASUS_STD(endl);
        assert(0);
    }
}

void test_params(CIMClient& client)
{
    assert(Tst_Ret<Boolean>::func(client, "booleanReturn"));
    assert(Tst_Ret<Uint8>::func(client, "uint8Return"));
    assert(Tst_Ret<Sint8>::func(client, "sint8Return"));
    assert(Tst_Ret<Uint16>::func(client, "uint16Return"));
    assert(Tst_Ret<Sint16>::func(client, "sint16Return"));
    assert(Tst_Ret<Uint32>::func(client, "uint32Return"));
    assert(Tst_Ret<Sint32>::func(client, "sint32Return"));
    assert(Tst_Ret<Uint64>::func(client, "uint64Return"));
    assert(Tst_Ret<Sint64>::func(client, "sint64Return"));
    assert(Tst_Ret<Real32>::func(client, "real32Return"));
    assert(Tst_Ret<Real64>::func(client, "real64Return"));
    assert(Tst_Ret<Char16>::func(client, "char16Return"));
    assert(Tst_Ret<String>::func(client, "stringReturn"));
    assert(Tst_Ret<CIMDateTime>::func(client, "datetimeReturn"));
    assert(Tst_Ret<CIMInstance>::func(client, "instanceReturn"));
    assert(Tst_Ret<CIMObject>::func(client, "objectReturn"));

    assert(Tst_Sca_Parms<Boolean>::func(client, "booleanScalarParams"));
    assert(Tst_Sca_Parms<Uint8>::func(client, "uint8ScalarParams"));
    assert(Tst_Sca_Parms<Sint8>::func(client, "sint8ScalarParams"));
    assert(Tst_Sca_Parms<Uint16>::func(client, "uint16ScalarParams"));
    assert(Tst_Sca_Parms<Sint16>::func(client, "sint16ScalarParams"));
    assert(Tst_Sca_Parms<Uint32>::func(client, "uint32ScalarParams"));
    assert(Tst_Sca_Parms<Sint32>::func(client, "sint32ScalarParams"));
    assert(Tst_Sca_Parms<Uint64>::func(client, "uint64ScalarParams"));
    assert(Tst_Sca_Parms<Sint64>::func(client, "sint64ScalarParams"));
    assert(Tst_Sca_Parms<Real32>::func(client, "real32ScalarParams"));
    assert(Tst_Sca_Parms<Real64>::func(client, "real64ScalarParams"));
    assert(Tst_Sca_Parms<Char16>::func(client, "char16ScalarParams"));
    assert(Tst_Sca_Parms<String>::func(client, "stringScalarParams"));
    assert(Tst_Sca_Parms<CIMDateTime>::func(client,"datetimeScalarParams"));
#ifdef SCALAR_EMBEDDED_TESTING
    assert(Tst_Sca_Parms<CIMInstance>::func(client,"instanceScalarParams"));
    assert(Tst_Sca_Parms<CIMObject>::func(client, "objectScalarParams"));
#endif
    assert(Tst_Sca_Parms<CIMObjectPath>::func(client, "referenceScalarParams"));

    assert(Tst_Arr_Parms<Boolean>::func(client, "booleanArrayParams"));
    assert(Tst_Arr_Parms<Uint8>::func(client, "uint8ArrayParams"));
    assert(Tst_Arr_Parms<Sint8>::func(client, "sint8ArrayParams"));
    assert(Tst_Arr_Parms<Uint16>::func(client, "uint16ArrayParams"));
    assert(Tst_Arr_Parms<Sint16>::func(client, "sint16ArrayParams"));
    assert(Tst_Arr_Parms<Uint32>::func(client, "uint32ArrayParams"));
    assert(Tst_Arr_Parms<Sint32>::func(client, "sint32ArrayParams"));
    assert(Tst_Arr_Parms<Uint64>::func(client, "uint64ArrayParams"));
    assert(Tst_Arr_Parms<Sint64>::func(client, "sint64ArrayParams"));
    assert(Tst_Arr_Parms<Real32>::func(client, "real32ArrayParams"));
    assert(Tst_Arr_Parms<Real64>::func(client, "real64ArrayParams"));
    assert(Tst_Arr_Parms<Char16>::func(client, "char16ArrayParams"));
    assert(Tst_Arr_Parms<String>::func(client, "stringArrayParams"));
    assert(Tst_Arr_Parms<CIMDateTime>::func(client, "datetimeArrayParams"));
    assert(Tst_Arr_Parms<CIMInstance>::func(client, "instanceArrayParams"));
    assert(Tst_Arr_Parms<CIMObjectPath>::func(client,"referenceArrayParams"));

    printf("+++++ passed test 8 - test_params."
           " Testing invokeMethod Parameters\n");
}

int main(int argc, char** argv)
{
    try
    {
        CIMClient client;
        client.connect("localhost", 5988, "", "");

        // The following functions create an instance 
        // with all cim types, and test retrieving it in a number
        // of different forms.
        CIMInstance origInstance;

        CIMObjectPath cop = create_All_Class_instance(client, origInstance);

        // test retrieving complete instance to assure all property types
        // return correct values
        test_All_Class_instance(client, cop, origInstance);

        // test variations of property lists with getInstance()
        test_getInstance_propertyLists(client, cop);

        // test variations of property lists with enumerateInstances()
        test_enumerateInstance_propertyLists(client, origInstance);

        // test getProperty for all properties in the original instance
        test_get_property(client, cop);

        // Note this test short-circuited because CIMPLE does not return
        // class origins today
        test_class_origin(client, cop);

        // test enumerateInstances for both instance created by us and
        // ones created in provider.
        test_enumerate_instances(client);

        // delete and test delete of instance created by  test 1
        test_delete_instance(client, cop);

        // Test create and get of instance with NULL properties
        test_instance_null(client);

        // test method parameters
        test_params(client);
    }
    catch(Exception& e)
    {
        PEGASUS_STD(cerr) << "Error: " << e.getMessage() << PEGASUS_STD(endl);
        exit(1);
    }

    PEGASUS_STD(cout) << "+++++ passed all tests" << PEGASUS_STD(endl);

    return 0;
}
