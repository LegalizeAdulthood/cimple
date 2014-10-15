/*
**==============================================================================
**
** Copyright (c) 2003, 2004, 2005, 2006, Michael Brasher, Karl Schopmeyer
** Copyright (c) 2007 Novell, Inc.
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

#ifndef _cimple_OpenWBEM_Adapter_h
#define _cimple_OpenWBEM_Adapter_h

#include <cimple/cimple.h>
#include <openwbem/OW_config.h>
#include <openwbem/OW_CppInstanceProviderIFC.hpp>
#include <openwbem/OW_CppMethodProviderIFC.hpp>
#include <openwbem/OW_CppAssociatorProviderIFC.hpp>
#include <openwbem/OW_CppIndicationProviderIFC.hpp>
#include <openwbem/OW_CIMObjectPath.hpp>
#include <cimple/Provider_Handle.h>


CIMPLE_NAMESPACE_BEGIN

class CIMPLE_HIDE OpenWBEM_Adapter : 
    public OpenWBEM::CppMethodProviderIFC, 
    public OpenWBEM::CppAssociatorProviderIFC,
    public OpenWBEM::CppIndicationProviderIFC
// we inherit from instance through the assoc provider IFC
{
public:

    OpenWBEM_Adapter(Provider_Handle* handle);

    virtual ~OpenWBEM_Adapter();

    virtual void initialize(const OpenWBEM::ProviderEnvironmentIFCRef& env);

    virtual void shuttingDown(const OpenWBEM::ProviderEnvironmentIFCRef& env);


    /**
     * This method enumerates all names of instances of the class which is
     * specified in cop.
     *
     * @param cop The object path specifies the class that must be enumerated.
     * @param cimClass The class reference
     *
     * @returns An array of CIMObjectPath containing names of the
     *  enumerated instances.
     * @throws CIMException - throws if the CIMObjectPath is incorrect
     *  or does not exist.
     */
    virtual void enumInstanceNames(
        const OpenWBEM::ProviderEnvironmentIFCRef& env,
        const OpenWBEM::String& ns,
        const OpenWBEM::String& className,
        OpenWBEM::CIMObjectPathResultHandlerIFC& result,
        const OpenWBEM::CIMClass& cimClass );

    /**
     * This method enumerates
     * all instances of the class which is specified in className.  The entire
     * instances and not just the names are returned.  If you don't override
     * this method, the default implementation will be used which utilizes
     * enumInstanceNames() and getInstance()
     *
     * @param cop The object path specifies the class that must be
     *  enumerated.
     *
     * @param cimClass The class reference.
     *
     * @param localOnly If true, only the non-inherited properties are to be
     *  returned, otherwise all properties are required.
     *
     * @returns An array of CIMInstance containing names of the enumerated
     *  instances.
     *
     * @throws CIMException - thrown if cop is incorrect or does not exist.
     */
    virtual void enumInstances(
        const OpenWBEM::ProviderEnvironmentIFCRef& env,
        const OpenWBEM::String& ns,
        const OpenWBEM::String& className,
        OpenWBEM::CIMInstanceResultHandlerIFC& result,
        OpenWBEM::WBEMFlags::ELocalOnlyFlag localOnly,
        OpenWBEM::WBEMFlags::EDeepFlag deep,
        OpenWBEM::WBEMFlags::EIncludeQualifiersFlag includeQualifiers,
        OpenWBEM::WBEMFlags::EIncludeClassOriginFlag includeClassOrigin,
        const OpenWBEM::StringArray* propertyList,
        const OpenWBEM::CIMClass& requestedClass,
        const OpenWBEM::CIMClass& cimClass );

    /**
     * This method retrieves the instance specified in the object path.
     *
     * @param cop The name of the instance to be retrieved.
     *
     * @param cimClass The class to which the instance belongs.  This is
     *  useful for providers which do not want to create instances from
     *  scratch.  They can call the class newInstance() routine to create
     *  a template for the new instance.
     *
     * @param localOnly If true, only the non-inherited properties are to be
     *  returned, otherwise all properties are required.
     *
     * @returns The retrieved instance
     *
     * @throws CIMException - thrown if cop is incorrect or does not exist
     */
    virtual OpenWBEM::CIMInstance getInstance(
        const OpenWBEM::ProviderEnvironmentIFCRef& env,
        const OpenWBEM::String& ns,
        const OpenWBEM::CIMObjectPath& instanceName,
        OpenWBEM::WBEMFlags::ELocalOnlyFlag localOnly,
        OpenWBEM::WBEMFlags::EIncludeQualifiersFlag includeQualifiers,
        OpenWBEM::WBEMFlags::EIncludeClassOriginFlag includeClassOrigin,
        const OpenWBEM::StringArray* propertyList,
        const OpenWBEM::CIMClass& cimClass );

#ifndef OW_DISABLE_INSTANCE_MANIPULATION
    /**
     * This method creates the instance specified in the object path.  If the
     * instance does exist an CIMException with ID CIM_ERR_ALREADY_EXISTS
     * must be thrown.  The parameter should be the instance name.
     *
     * @param cop The path to the instance to be set.  The import part in
     *  this parameter is the namespace component.
     *
     * @param cimInstance The instance to be set
     *
     * @returns A CIM ObjectPath of the instance that was created.
     *
     * @throws CIMException
     */
    virtual OpenWBEM::CIMObjectPath createInstance(
        const OpenWBEM::ProviderEnvironmentIFCRef& env,
        const OpenWBEM::String& ns,
        const OpenWBEM::CIMInstance& cimInstance );
    /**
     * This method sets the instance specified in the object path.  If the
     * instance does not exist an CIMException with ID CIM_ERR_NOT_FOUND
     * must be thrown.  The parameter should be the instance name.
     *
     * @param cop The path of the instance to be set.  The important part in
     *  this parameter is the namespace component.
     *
     * @param cimInstance The instance to be set.
     *
     * @throws CIMException
     */
    virtual void modifyInstance(
        const OpenWBEM::ProviderEnvironmentIFCRef& env,
        const OpenWBEM::String& ns,
        const OpenWBEM::CIMInstance& modifiedInstance,
        const OpenWBEM::CIMInstance& previousInstance,
        OpenWBEM::WBEMFlags::EIncludeQualifiersFlag includeQualifiers,
        const OpenWBEM::StringArray* propertyList,
        const OpenWBEM::CIMClass& theClass);
    /**
     * This method deletes the instance specified in the object path
     *
     * @param cop The instance to be deleted
     *
     * @throws CIMException
     */
    virtual void deleteInstance(
        const OpenWBEM::ProviderEnvironmentIFCRef& env,
        const OpenWBEM::String& ns,
        const OpenWBEM::CIMObjectPath& cop);
#endif // #ifndef OW_DISABLE_INSTANCE_MANIPULATION

    /**
     * The CIMOM calls this method when the method specified in the parameters
     * is to be invoked.
     *
     * @param cop Contains the path to the instance whose method must be
     *  invoked.
     * @param methodName The name of the method.
     * @param inParams An array of CIMValues which are the input parameters
     *  for this method.
     * @param outParams An array of CIMValues which are the output
     *  parameters for this method.
     *
     * @returns CIMValue - The return value of the method.  Must be a
     *    valid CIMValue.
     *
     * @throws CIMException
     */
    virtual OpenWBEM::CIMValue invokeMethod(
        const OpenWBEM::ProviderEnvironmentIFCRef& env,
        const OpenWBEM::String& ns,
        const OpenWBEM::CIMObjectPath& path,
        const OpenWBEM::String& methodName,
        const OpenWBEM::CIMParamValueArray& in,
        OpenWBEM::CIMParamValueArray& out );

    /**
     * This method is invoked in order to do the Associators operation as
     * defined by the CIM operations over HTTP spec at
     * http://www.dmtf.org/download/spec/xmls/
     *     CIM_HTTP_Mapping10.htm#SecAssociators
     * This operation is used to enumerate CIM
     * Instances that are associated to a particular source CIM Object.
     *
     * @param assocClass Defines the association that the objectName
     *  object should be associated to. The provider uses this
     *  information to identify which association must be
     *  traversed in case it supports more than one
     *  association.
     *  
     * @param objectName Defines the source CIM Object whose associated
     *  Objects are to be returned.  This is an instance name.
     *  Instance name (modelpath).
     *
     * @param resultClass The resultClass input parameter, if not empty (""),
     *  MUST be a valid CIM Class name.  It acts as a filter on the
     *  returned set of Objects by mandating that each returned Object
     *  MUST be either an Instance of this Class (or one of its subclasses)
     *  or be this Class (or one of its subclasses).
     *
     * @param role The role input parameter, if not empty (""), MUST be a
     *  valid Property name.  It acts as a filter on the returned set of
     *  Objects by mandating that each returned Object MUST be associated
     *  to the source Object via an Association in which the source Object
     *  plays the specified role (i.e. the name of the Property in the
     *  Association Class that refers to the source Object MUST match the
     *  value of this parameter).
     *  
     * @param resultRole The resultRole input parameter if not empty (""),
     *  MUST be a valid Property name.  It acts as a filter on the returned
     *  set of Objects by mandating that each returned Object MUST be
     *  associated to the source Object via an Association in which the
     *  returned Object plays the specified role (i.e. the name of the
     *  Property in the Association Class that refers to the returned
     *  Object MUST match the value of this parameter).
     *
     * @param includeQualifiers If the includeQualifiers input parameter
     *  is true this specifies that all Qualifiers for each Object
     *  (including Qualifiers on the Object and on any returned Properties)
     *  MUST be included as elements in the response.   If false no
     *  elements are present in each returned Object.
     *
     * @param includeClassOrigin If the includeClassOrigin input parameter
     *  is true, this specifies that the CLASSORIGIN attribute MUST be
     *  present on all appropriate elements in each returned Object. If
     *  false, no CLASSORIGIN attributes are present in each returned
     *  Object.
     *
     * @param propertyList If the propertyList input parameter is not NULL
     *  the members of the array define one or more Property names.
     *  Each returned Object MUST NOT include elements for any Properties
     *  missing from this list.  Note that if localOnly is specified as
     *  true (or deepInheritance is specified as false) this acts as an
     *  additional filter on the set or Properties returned (for example,
     *  if Property A is included in the propertyList but localOnly is set
     *  to true and A is not local to a returned Instance, then it will
     *  not be included in that Instance).  If the propertyList input
     *  parameter is an empty array this signifies that no Properties are
     *  included in each returned Object.  If the propertyList parameter
     *  is omitted this specifies that all Properties (subject to the
     *  conditions expressed by the other parameters) are included in each
     *  returned Object.  If the propertyList contains duplicate elements,
     *  the Server ignores the duplicates but otherwise processes the
     *  request normally.  If the propertyList contains elements which are
     *  invalid Property names for any target Object, the Server ignores
     *  such entries but should otherwise process the request normally.
     *  Clients SHOULD NOT explicitly specify properties in the propertyList
     *  parameter unless they have specified a non-empty value for the
     *  resultClass parameter.
     *
     * @returns If successful, the method returns zero or more CIM Instances
     *  meeting the requested criteria.
     *
     * @throws CIMException. - The following IDs can be expected.
     *  CIM_ERR_ACCESS_DENIED
     *  CIM_ERR_NOT_SUPPORTED
     *  CIM_ERR_INVALID_NAMESPACE
     *  CIM_ERR_INVALID_PARAMETER (including missing, duplicate,
     *  unrecognized or otherwise incorrect parameters)
     *  CIM_ERR_FAILED (some other unspecifed error occurred)
     */
    virtual void associators(
        const OpenWBEM::ProviderEnvironmentIFCRef& env,
        OpenWBEM::CIMInstanceResultHandlerIFC& result,
        const OpenWBEM::String& ns,
        const OpenWBEM::CIMObjectPath& objectName,
        const OpenWBEM::String& assocClass,
        const OpenWBEM::String& resultClass,
        const OpenWBEM::String& role,
        const OpenWBEM::String& resultRole,
        OpenWBEM::WBEMFlags::EIncludeQualifiersFlag includeQualifiers,
        OpenWBEM::WBEMFlags::EIncludeClassOriginFlag includeClassOrigin,
        const OpenWBEM::StringArray* propertyList);

    /**
     * For the definition of this operation, refer to
     * http://www.dmtf.org/download/spec/xmls/
     *     CIM_HTTP_Mapping10.htm#SecAssociatorNames
     * This operation is used to enumerate the names of CIM
     * Instances that are associated to a particular source CIM
     * Instance.
     *
     * @param assocClass see associator parameter assocClass
     * @param objectName see associator parameter objectName
     * @param resultClass see associator parameter resultClass
     * @param role see associator parameter role
     * @param resultRole see associator parameter resultRole
     * @returns If successful, the method returns zero or more full CIM
     *  Instance of Objects meeting the requested criteria.
     * @throws CIMException - as defined in the associator method
     */
    virtual void associatorNames(
        const OpenWBEM::ProviderEnvironmentIFCRef& env,
        OpenWBEM::CIMObjectPathResultHandlerIFC& result,
        const OpenWBEM::String& ns,
        const OpenWBEM::CIMObjectPath& objectName,
        const OpenWBEM::String& assocClass,
        const OpenWBEM::String& resultClass,
        const OpenWBEM::String& role,
        const OpenWBEM::String& resultRole );

    /**
     * For definition of this operation, refer to
     * http://www.dmtf.org/download/spec/xmls/
     *     CIM_HTTP_Mapping10.htm#SecReferencesMethod
     * This operation is used to enumerate the association objects
     * that refer to a particular target CIM Instance.
     *
     * @param resultClass Defines the association that the objectName object
     *  should be associated to.  The provider uses this information to
     *  identify which association must be traversed in case it supports
     *  more than one association.
     *
     * @param objectName The objectName input parameter defines the target
     *  CIM Object whose referring Objects are to be returned.  This is an
     *  Instance name (model path).
     *
     * @param role The role input parameter, if not empty (""), MUST be a
     *  valid Property name.  It acts as a filter on the returned set of
     *  Objects by mandating that each returned Object MUST refer to the
     *  target Object via a Property whose name matches the value of this
     *  parameter.
     *
     * @param includeQualifiers see the includeQualifiers for associators.
     * @param includeClassOrigin see the includeClassOrigin for associators.
     * @param propertyList see the propertyList for associators
     *
     * @returns If successful, the method returns zero or more CIM Instances
     *  meeting the requested criteria.
     *
     * @throws CIMException - as defined for the associators method.
     */
    virtual void references(
        const OpenWBEM::ProviderEnvironmentIFCRef& env,
        OpenWBEM::CIMInstanceResultHandlerIFC& result,
        const OpenWBEM::String& ns,
        const OpenWBEM::CIMObjectPath& objectName,
        const OpenWBEM::String& resultClass,
        const OpenWBEM::String& role,
        OpenWBEM::WBEMFlags::EIncludeQualifiersFlag includeQualifiers,
        OpenWBEM::WBEMFlags::EIncludeClassOriginFlag includeClassOrigin,
        const OpenWBEM::StringArray* propertyList);

    /**
     * For definition of this operation, refer to
     * http://www.dmtf.org/download/spec/xmls/
     *     CIM_HTTP_Mapping10.htm#SecReferenceNames
     * This operation is used to enumerate the association objects
     * that refer to a particular target CIM Instance.
     *
     * @param resultClass see the reference method.
     * @param objectName see the reference method.
     * @param role see the reference method
     *
     * @returns If successful, the method returns the names of zero or more
     * full CIM Instance paths of Objects meeting the requested criteria.
     * @throws CIMException - as defined for associators method.
     */
    virtual void referenceNames(
        const OpenWBEM::ProviderEnvironmentIFCRef& env,
        OpenWBEM::CIMObjectPathResultHandlerIFC& result,
        const OpenWBEM::String& ns,
        const OpenWBEM::CIMObjectPath& objectName,
        const OpenWBEM::String& resultClass,
        const OpenWBEM::String& role);

    virtual void activateFilter(
        const OpenWBEM::ProviderEnvironmentIFCRef& env,
        const OpenWBEM::WQLSelectStatement& filter, 
        const OpenWBEM::String& eventType, 
        const OpenWBEM::String& nameSpace,
        const OpenWBEM::StringArray& classes, 
        bool firstActivation);

    virtual void authorizeFilter(
        const OpenWBEM::ProviderEnvironmentIFCRef& env,
        const OpenWBEM::WQLSelectStatement& filter, 
        const OpenWBEM::String& eventType, 
        const OpenWBEM::String& nameSpace,
        const OpenWBEM::StringArray& classes, 
        const OpenWBEM::String& owner);

    virtual void deActivateFilter(
        const OpenWBEM::ProviderEnvironmentIFCRef& env,
        const OpenWBEM::WQLSelectStatement& filter, 
        const OpenWBEM::String& eventType, 
        const OpenWBEM::String& nameSpace,
        const OpenWBEM::StringArray& classes, 
        bool lastActivation);

    /**
     * If a provider wishes to be polled, it must return a positive number.
     * The int returned will be the number of seconds between polls.
     * The cimom performs polling by calling enumInstances() each polling
     * cycle and comparing the results with the previous cycle.  It will
     * generate CIM_Inst{Creation,Modification,Deletion} indications based
     * on the difference in the instances.
     * The namespace/classname that will be passed into enumInstances is
     * the same one that is passed as the classPath parameter to mustPoll().
     * If an event provider does not want to be polled, it should return 0.
     * If the provider is going to start a thread that will wait for some
     * external event, it should do it the first time activateFilter is called
     * firstActivation will == true.
     * If a provider may take a long time to generate all instances in 
     * enumInstances, it should either not be polled or it should have a large
     * poll interval.
     * Also, a provider that is polled can only do lifecycle indications.
     * If the provider doesn't do lifecycle indications, then it must return
     * 0 from mustPoll, and has to generate indications by another means.
     * @param env 
     */
    virtual int mustPoll(
        const OpenWBEM::ProviderEnvironmentIFCRef& env,
        const OpenWBEM::WQLSelectStatement& filter, 
        const OpenWBEM::String& eventType, 
        const OpenWBEM::String& nameSpace,
        const OpenWBEM::StringArray& classes);

private:

    Provider_Handle* _provider;
    OpenWBEM::CIMOMHandleIFCRef _handle;
    OpenWBEM::CIMOMHandleIFCRef _cimom_handle;
    const Meta_Class* _mc;

    const Meta_Class* find_meta_class(
        const OpenWBEM::CIMObjectPath& objectPath) const;

    const Meta_Class* find_model_meta_class(
        const OpenWBEM::CIMObjectPath& objectPath) const;
};

CIMPLE_NAMESPACE_END

#endif /* _cimple_OpenWBEM_Adapter_h */
