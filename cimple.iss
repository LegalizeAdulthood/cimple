[Setup]
AppName=CIMPLE
AppVerName=CIMPLE 1.1.2
AppPublisher=Inova Development
AppPublisherURL=http://www.cimple.org
AppSupportURL=http://www.cimple.org
AppUpdatesURL=http://www.cimple.org
DefaultDirName={pf}\CIMPLE
DefaultGroupName=CIMPLE
DisableProgramGroupPage=yes
LicenseFile=license.txt
OutputBaseFilename=cimple-1.1.2-setup
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
Name: "{app}\bin"
Name: "{app}\lib"
Name: "{app}\include"
Name: "{app}\include\cimple"
Name: "{app}\doc"
;Name: "{app}\data"
;Name: "{app}\data\schema\cim214"

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

; Documentation:
Source: "doc\Using_CIMPLE.pdf"; DestDir: "{app}\doc"

; License:
Source: "license.txt"; DestDir: "{app}"

; CIM214:
;Source: "schema\cim214\*.*"; DestDir: "{app}\data\schema\cim214"; Flags: recursesubdirs

; CIM213:
;Source: "schema\cim2131\*.*"; DestDir: "{app}\data\schema\cim2131"; Flags: recursesubdirs
