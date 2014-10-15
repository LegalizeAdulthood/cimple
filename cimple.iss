[Setup]
AppName=CIMPLE
AppVerName=CIMPLE 1.0.1
AppPublisher=Inova Development
AppPublisherURL=http://www.cimple.org
AppSupportURL=http://www.cimple.org
AppUpdatesURL=http://www.cimple.org
DefaultDirName={pf}\CIMPLE
DefaultGroupName=CIMPLE
DisableProgramGroupPage=yes
LicenseFile=C:\home\mbrasher\cimple\license.txt
OutputBaseFilename=cimple-1.0.1-setup
Compression=lzma
SolidCompression=yes
InfoAfterFile=infoafter.txt
InfoBeforeFile=infobefore.txt

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

;[Types]
;Name: "core"; Description: "Standalone Mode"
;Name: "cmpi"; Description: "CMPI Support"
;Name: "pegasus"; Description: "OpenPegasus Support"

;[Components]
;Name: "core"; Description: "Core Components"; Types: core; Flags: fixed
;Name: "CMPI"; Description: "CMPI Components"; Types: cmpi
;Name: "OpenPegasus"; Description: "OpenPegasus Components"; Types: pegasus

[Dirs]
Name: "{app}\data"
Name: "{app}\bin"
Name: "{app}\lib"
Name: "{app}\include"
Name: "{app}\include\cimple"
Name: "{app}\data"
Name: "{app}\data\schema\cim214"

[Files]
; Programs
Source: "bin\GENCLASS.EXE"; DestDir: "{app}\bin"
Source: "bin\GENPROV.EXE"; DestDir: "{app}\bin"
Source: "bin\GENMOD.EXE"; DestDir: "{app}\bin"
Source: "bin\GENPROJ.EXE"; DestDir: "{app}\bin"
Source: "bin\REGMOD.EXE"; DestDir: "{app}\bin"
; Libraries
Source: "bin\CIMPLE.DLL"; DestDir: "{app}\bin"
Source: "lib\CIMPLE.LIB"; DestDir: "{app}\lib"
Source: "bin\CIMPLEPEGADAP.DLL"; DestDir: "{app}\bin"
Source: "lib\CIMPLEPEGADAP.LIB"; DestDir: "{app}\lib"
Source: "bin\CIMPLECMPIADAP.DLL"; DestDir: "{app}\bin"
Source: "lib\CIMPLECMPIADAP.LIB"; DestDir: "{app}\lib"
; Headers
Source: "src\cimple\*.h"; DestDir: "{app}\include\cimple"
; CIM214:
Source: "schema\cim214\*.*"; DestDir: "{app}\data\schema\cim214"
Source: "schema\cim214\Application\*.*"; DestDir: "{app}\data\schema\cim214\Application"
Source: "schema\cim214\Core\*.*"; DestDir: "{app}\data\schema\cim214\Core"
Source: "schema\cim214\Database\*.*"; DestDir: "{app}\data\schema\cim214\Database"
Source: "schema\cim214\Device\*.*"; DestDir: "{app}\data\schema\cim214\Device"
Source: "schema\cim214\Event\*.*"; DestDir: "{app}\data\schema\cim214\Event"
Source: "schema\cim214\Interop\*.*"; DestDir: "{app}\data\schema\cim214\Interop"
Source: "schema\cim214\IPsecPolicy\*.*"; DestDir: "{app}\data\schema\cim214\IPsecPolicy"
Source: "schema\cim214\Metrics\*.*"; DestDir: "{app}\data\schema\cim214\Metrics"
Source: "schema\cim214\Network\*.*"; DestDir: "{app}\data\schema\cim214\Network"
Source: "schema\cim214\Physical\*.*"; DestDir: "{app}\data\schema\cim214\Physical"
Source: "schema\cim214\Policy\*.*"; DestDir: "{app}\data\schema\cim214\Policy"
Source: "schema\cim214\Support\*.*"; DestDir: "{app}\data\schema\cim214\Support"
Source: "schema\cim214\System\*.*"; DestDir: "{app}\data\schema\cim214\System"
Source: "schema\cim214\User\*.*"; DestDir: "{app}\data\schema\cim214\User"


; CIM213:
Source: "schema\cim2131\*.*"; DestDir: "{app}\data\schema\cim2131"
Source: "schema\cim2131\Application\*.*"; DestDir: "{app}\data\schema\cim2131\Application"
Source: "schema\cim2131\Core\*.*"; DestDir: "{app}\data\schema\cim2131\Core"
Source: "schema\cim2131\Database\*.*"; DestDir: "{app}\data\schema\cim2131\Database"
Source: "schema\cim2131\Device\*.*"; DestDir: "{app}\data\schema\cim2131\Device"
Source: "schema\cim2131\Event\*.*"; DestDir: "{app}\data\schema\cim2131\Event"
Source: "schema\cim2131\Interop\*.*"; DestDir: "{app}\data\schema\cim2131\Interop"
Source: "schema\cim2131\IPsecPolicy\*.*"; DestDir: "{app}\data\schema\cim2131\IPsecPolicy"
Source: "schema\cim2131\Metrics\*.*"; DestDir: "{app}\data\schema\cim2131\Metrics"
Source: "schema\cim2131\Network\*.*"; DestDir: "{app}\data\schema\cim2131\Network"
Source: "schema\cim2131\Physical\*.*"; DestDir: "{app}\data\schema\cim2131\Physical"
Source: "schema\cim2131\Policy\*.*"; DestDir: "{app}\data\schema\cim2131\Policy"
Source: "schema\cim2131\Support\*.*"; DestDir: "{app}\data\schema\cim2131\Support"
Source: "schema\cim2131\System\*.*"; DestDir: "{app}\data\schema\cim2131\System"
Source: "schema\cim2131\User\*.*"; DestDir: "{app}\data\schema\cim2131\User"

