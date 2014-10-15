This provider tests the generation of an indications that includes
an embedded object.

It is only a method and indication provider and not an instance
provider.

The provider generates an indication each time the method

DeliverIndications is called.


Note that this is a peculiar form for an indication defintion in that
the indication class actually includes the method that initiates the
delivery of the indication.

Note also that the method delivers the indication only if
subscriptions are enabled for the provider.  However, it does not
provide any alternate return to the method if indications are not
enabled.


