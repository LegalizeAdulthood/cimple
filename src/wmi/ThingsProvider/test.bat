:: tests of Things using the Microsoft tool WMIC

wmic /NAMESPACE:\\root\default path Thing1
wmic /NAMESPACE:\\root\default path Thing2

REM wmic /NAMESPACE:\\root\default path Person get SSN
REM wmic /NAMESPACE:\\root\default path Person call foo
REM wmic /NAMESPACE:\\root\default path Person call foo1

