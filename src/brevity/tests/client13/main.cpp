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
#include "CIM_IndicationSubscription_Hnd.h"
#include "CIM_IndicationFilter_Hnd.h"
#include "CIM_IndicationHandlerCIMXML_Hnd.h"

using namespace cimple;

void test(Client& c)
{
    const char NS[] = "root/cimv2";
    const char NAME[] = "E6F0D70B233E46668EC64BD2671D07A2";
    const char DESTINATION[] = "http://localhost:9999";

    // Create filter:

    CIM_IndicationFilter_Hnd filter;
    filter.Name_value(NAME);
    filter.Query_value("select * from CIM_Indication");
    filter.QueryLanguage_value("WQL");
    filter.SourceNamespace_value(NS);
    filter.print();
    CIM_IndicationFilter_Ref filter_ref(c.create_instance(NS, filter));

    // Create handler:

    CIM_IndicationHandlerCIMXML_Hnd handler;
    handler.Name_value(NAME);
    handler.Destination_value(DESTINATION);
    handler.print();
    CIM_IndicationHandlerCIMXML_Ref handler_ref(c.create_instance(NS, handler));

    // Create sub:

    CIM_IndicationSubscription_Hnd sub;
    sub.Filter_value(filter_ref);
    sub.Handler_value(handler_ref);
    sub.print();
    CIM_IndicationSubscription_Ref subscription_ref(c.create_instance(NS, sub));
    subscription_ref.print();
}

int main()
{
    Client client;

    try
    {
        client.connect("http://localhost:5989/cimxml");
        test(client);
    }
    catch (Exception& e)
    {
        printf("Exception: %s\n", e.message().c_str());
    }

    return 0;
}

/*  Program output:

    CIM_IndicationFilter
    {
        string Caption = NULL;
        string Description = NULL;
        string ElementName = NULL;
        string SystemCreationClassName = NULL;
        string SystemName = NULL;
        string CreationClassName = NULL;
        string Name = "E6F0D70B233E46668EC64BD2671D07A2";
        string SourceNamespace = "root/cimv2";
        string Query = "select * from CIM_Indication";
        string QueryLanguage = "WQL";
    }
    CIM_IndicationHandlerCIMXML
    {
        string Caption = NULL;
        string Description = NULL;
        string ElementName = NULL;
        string SystemCreationClassName = NULL;
        string SystemName = NULL;
        string CreationClassName = NULL;
        string Name = "E6F0D70B233E46668EC64BD2671D07A2";
        uint16 PersistenceType = NULL;
        string OtherPersistenceType = NULL;
        string Owner = NULL;
        string Destination = "http://localhost:9999";
    }
    CIM_IndicationSubscription
    {
        CIM_IndicationFilter Filter =
        {
            string __name_space = "root/cimv2";
            string SystemCreationClassName = "CIM_ComputerSystem";
            string SystemName = "localhost.localdomain";
            string CreationClassName = "CIM_IndicationFilter";
            string Name = "E6F0D70B233E46668EC64BD2671D07A2";
        }
        CIM_IndicationHandlerCIMXML Handler =
        {
            string __name_space = "root/cimv2";
            string SystemCreationClassName = "CIM_ComputerSystem";
            string SystemName = "localhost.localdomain";
            string CreationClassName = "CIM_IndicationHandlerCIMXML";
            string Name = "E6F0D70B233E46668EC64BD2671D07A2";
        }
        uint16 OnFatalErrorPolicy = NULL;
        string OtherOnFatalErrorPolicy = NULL;
        uint64 FailureTriggerTimeInterval = NULL;
        uint16 SubscriptionState = NULL;
        string OtherSubscriptionState = NULL;
        datetime TimeOfLastStateChange = NULL;
        uint64 SubscriptionDuration = NULL;
        datetime SubscriptionStartTime = NULL;
        uint64 SubscriptionTimeRemaining = NULL;
        uint16 RepeatNotificationPolicy = NULL;
        string OtherRepeatNotificationPolicy = NULL;
        uint64 RepeatNotificationInterval = NULL;
        uint64 RepeatNotificationGap = NULL;
        uint16 RepeatNotificationCount = NULL;
    }
*/
