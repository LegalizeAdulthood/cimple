:: tests of Person using the Microsoft tool WMIC

wmic /NAMESPACE:\\root\default path Person
wmic /NAMESPACE:\\root\default path Person get SSN
wmic /NAMESPACE:\\root\default path Person call foo
wmic /NAMESPACE:\\root\default path Person call foo1

