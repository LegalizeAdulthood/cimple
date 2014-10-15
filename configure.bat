@echo off

set arg0=%0

::==============================================================================
::
:: Process options.
::
::==============================================================================

set prev=

::
::  Loop for all input parameters
::

:loop

  set found=

  ::
  :: Get option argument based on prev variable set 
  :: when option found
  ::

  if "%prev%" == "prefix" (
    set prefix=%1
    set found=1
    set prev=
  )

  if "%prev%" == "bindir" (
    set bindir=%1
    set found=1
    set prev=
  )

  if "%prev%" == "libdir" (
    set libdir=%1
    set found=1
    set prev=
  )

  if "%prev%" == "includedir" (
    set includedir=%1
    set found=1
    set prev=
  )

  if "%prev%" == "datadir" (
    set datadir=%1
    set found=1
    set prev=
  )


  if "%prev%" == "cimplehome-envvar" (
    set cimplehome_envvar=%1
    set found=1
    set prev=
  )

  if "%prev%" == "with-pegasus" (
    set with_pegasus=%1
    set found=1
    set prev=
  )

  if "%prev%" == "with-pegasus-libdir" (
    set with_pegasus_libdir=%1
    set found=1
    set prev=
  )

  if "%prev%" == "with-pegasus-includes" (
    set with_pegasus_includes=%1
    set found=1
    set prev=
  )

  if "%prev%" == "with-cmpi" (
    set with_cmpi=%1
    set found=1
    set prev=
  )

  if "%prev%" == "with-openwbem" (
    set with_openwbem=%1
    set found=1
    set prev=
  )

  if "%prev%" == "with-schema" (
    set with_schema=%1
    set found=1
    set prev=
  )

  if "%prev%" == "with-namespace" (
    set with_namespace=%1
    set found=1
    set prev=
  )

  if "%prev%" == "host" (
    set __host=%1
    set found=1
    set prev=
  )

  ::
  :: Get option
  ::

  if "%1" == "--help" (
    set help=1
    set found=1
  )
  if "%1" == "-h" (
    set help=1
    set found=1
  )

  if "%1" == "--prefix" (
    set prev=prefix
    set found=1
  )

  if "%1" == "--bindir" (
    set prev=bindir
    set found=1
  )

  if "%1" == "--libdir" (
    set prev=libdir
    set found=1
  )

  if "%1" == "--includedir" (
    set prev=includedir
    set found=1
  )

  if "%1" == "--datadir" (
    set prev=datadir
    set found=1
  )

  if "%1" == "--cimplehome-envvar" (
    set prev=cimplehome-envvar
    set found=1
  )

  if "%1" == "--with-pegasus" (
    set prev=with-pegasus
    set found=1
  )

  if "%1" == "--with-pegasus-libdir" (
    set prev=with-pegasus-libdir
    set found=1
  )

  if "%1" == "--with-pegasus-includes" (
    set prev=with-pegasus-includes
    set found=1
  )

  if "%1" == "--with-pegasus-env" (
    set with_pegasus_env=1
    set found=1
  )

  if "%1" == "--with-cmpi" (
    set prev=with-cmpi
    set found=1
  )

  if "%1" == "--with-openwbem" (
    set prev=with-openwbem
    set found=1
  )

  if "%1" == "--with-cmpi" (
    set prev=with-cmpi
    set found=1
  )

  if "%1" == "--with-schema" (
    set prev=with-schema
    set found=1
  )

  if "%1" == "--with-namespace" (
    set prev=with-namespace
    set found=1
  )

  if "%1" == "--enable-debug" (
    set enable_debug=1
    set found=1
  )

  if "%1" == "--enable-wmi" (
    set enable_wmi=1
    set found=1
  )

  if "%1" == "--enable-static" (
    set enable_static=1
    set found=1
  )

  if "%1" == "--enable-adapter-trace" (
    set enable-adapter-trace-opt=1
    set found=1
  )

  if "%1" == "--enable-embedded-instances" (
    set enable_embedded_instances=1
    set found=1
  )

  if "%1" == "--disable-log-macros" (
    set disable_log_macros=1
    set found=1
  )


  if "%1" == "--enable-adapter-trace" (
    set enable_adapter_trace=1
    set found=1
  )

  if "%1" == "--enable-scheduler" (
    set enable_scheduler=1
    set found=1
  )

  if "%1" == "--host" (
    echo --host found.
    set prev=host
    set found=1
  )

  if "%1" == "" (
    set found=1
  )

  if "%found%" == "" (
      echo %arg0%: unknown option: %1
      goto done
  )
  
  shift

if not "%1" == "" goto loop

::==============================================================================
::
:: Check for option with missing option argument.
::
::==============================================================================

if not "%prev%" == "" (
    echo %arg0%: missing option argument for --%prev%
    goto done
)
::==============================================================================
::
:: help - display help and exit
::
::==============================================================================

if "%help%" == "1" (
    type config.help
    goto done
)

::==============================================================================
::
:: Deduce options
::
::==============================================================================

if "%with_pegasus_env%" == "1" (

  if "%PEGASUS_PLATFORM%" == "" (
    echo %arg0%: --with-pegasus-env needs PEGASUS_PLATFORM environment variable.
    goto done
  )

  if NOT "%PEGASUS_PLATFORM%" == "" (
    set __host=%PEGASUS_PLATFORM%
  )

  if "%PEGASUS_HOME%" == "" (
    echo %arg0%: --with-pegasus-env needs PEGASUS_HOME environment variable.
    goto done
  )

  if "%PEGASUS_ROOT%" == "" (
    echo %arg0%: --with-pegasus-env needs PEGASUS_ROOT environment variable.
    goto done
  )

  if not "%PEGASUS_DEBUG%" == "" (
    if "%enable_debug%" == "" (
       echo Enable CIMPLE debug because PEGASUS_DEBUG set
       set enable_debug=2
    )
  )

  set prefix=%PEGASUS_HOME%
  set libdir=%PEGASUS_HOME%/lib
  set with_pegasus=%PEGASUS_HOME%
  set with_pegasus_libdir=%PEGASUS_HOME%/lib
  set with_pegasus_includes=%PEGASUS_ROOT%/src
  set with_cmpi=%PEGASUS_ROOT%/src/Pegasus/Provider/CMPI

)

if "%prefix%" == "" (
  set prefix=c:/cimple
)

if "%bindir%" == "" (
  set bindir=%prefix%/bin
)

if "%libdir%" == "" (
  set libdir=%prefix%/lib
)

if "%includedir%" == "" (
  set includedir=%prefix%/include
)

if "%datadir%" == "" (
  set datadir=%prefix%/share
)

if "%cimplehome_envvar%" == "" (
  set cimplehome_envvar=CIMPLE_HOME
)

if "%with_schema%" == "" (
  set with_schema=%datadir%/cimple/schema/cim214
)


::==============================================================================
::
:: if no host parameter input, guess host
::
::==============================================================================
if NOT "%__host%" == "" GOTO HOSTFROMPARAM

if NOT defined PROCESSOR_ARCHITECTURE (
    echo %arg0% Error: Env var PROCESSOR_ARCHITECTURE not found
    goto done
)

if "%PROCESSOR_ARCHITECTURE%" == "x86" ( 
  set __host=WIN32_IX86_MSVC
  goto HOSTFOUND
)
if "%PROCESSOR_ARCHITECTURE%" == "AMD64" (
  set __host=WIN64_X86_64_MSVC
  goto HOSTFOUND
)
if "%PROCESSOR_ARCHITECTURE%" == "IA64" (
  set __host=WIN32_IA64_MSVC
  goto HOSTFOUND
)

echo %arg0%: Error: No Valid Host detected or input
goto done

:HOSTFOUND

:HOSTFROMPARAM

::==============================================================================
::
:: Test correct compiler: Only allows Microsoft compiler today
::
::==============================================================================

:: determine if the compiler exists. i.e. execute cl
::
cl
if ERRORLEVEL 1 GOTO NO_COMPILER
goto TEST64

:NO_COMPILER
echo Error: Microsoft compiler (cl) not found. Terminating %arg0%
goto done

:: Test if compiler matches platform definition.  This executes a test compile
:: to determine if 64 bin predefined macro exists.
::
:TEST64
echo "cl -c -D%__host% src\configTests\compilerWordSizeTest\compilerWordSizeTest.cpp"
cl -c -D%__host% src\configTests\compilerWordSizeTest\compilerWordSizeTest.cpp
if ERRORLEVEL 1 goto WORD_SIZE_ERROR
goto WORD_SIZE_OK

:WORD_SIZE_ERROR
echo Error: MicrososftCompiler word size does not match platform definition %__host%%
erase compilerWordSizeTest.obj
goto done

:WORD_SIZE_OK
erase compilerWordSizeTest.obj

::==============================================================================
::
:: Echo options to the console. This is diagnostic. uncomment first line to
:: use
::
::==============================================================================

goto skip
echo host=%__host%
echo prefix=%prefix%
echo bindir=%bindir%
echo libdir=%libdir%
echo includedir=%includedir%
echo datadir=%datadir%
echo with_pegasus=%with_pegasus%
echo with_pegasus_includes=%with_pegasus_includes%
echo with_pegasus_libdir=%with_pegasus_libdir%
echo with_pegasus_env=%with_pegasus_env%
echo with_cmpi=%with_cmpi%
echo with_openwbem=%with_openwbem%
echo with_schema=%with_schema%
echo with_namespace=%with_namespace%
echo enable_debug=%enable_debug%
echo enable_wmi=%enable_wmi%
echo enable_static=%enable_static%
echo enable-adapter-trace-opt=%enable-adapter-trace-opt%
echo enable_embedded_instances=%enable_embedded_instances%
echo enable_scheduler=%enable_scheduler%
echo cimplehome-envvar=%cimplehome_envvar%
echo enable-adapter-trace=%enable_adapter_trace%
echo disable_log_macros=%disable_log_macros%
:skip

::==============================================================================
::
:: Create config.options output file.  If there is an existing config file
:: rename it to config.options.bak
::
::==============================================================================

if EXIST config.options (
    if EXIST config.options.bak (
        del /q config.options.bak
    )
    copy config.options config.options.bak
    echo config.options copied to config.options.bak
)

echo ## This file was generated by %arg0%> config.options
echo ## Input: %arg0% %*>> config.options
echo PLATFORM=%__host%>> config.options
echo PREFIX_OPT=%prefix%>> config.options
echo BINDIR_OPT=%bindir%>> config.options
echo LIBDIR_OPT=%libdir%>> config.options
echo INCLUDEDIR_OPT=%includedir%>> config.options
echo DATADIR_OPT=%datadir%>> config.options
echo WITH_PEGASUS_OPT=%with_pegasus%>> config.options
echo WITH_PEGASUS_LIBDIR_OPT=%with_pegasus_libdir%>> config.options
echo WITH_PEGASUS_INCLUDES_OPT=%with_pegasus_includes%>> config.options
echo WITH_CMPI_OPT=%with_cmpi%>> config.options
echo WITH_OPENWBEM_OPT=%with_openwbem%>> config.options
echo WITH_SCHEMA_OPT=%with_schema%>> config.options
echo LIBBASE_OPT=lib>> config.options
echo CIMPLEHOME_ENVVAR_OPT=%cimplehome_envvar%>> config.options

:: Issue warning if debug set because PEGASUS_DEBUG set
if not "%enable_debug%" == "" (
    if "%enable_debug%" == "2" (
        echo ## DEBUG mode set because PEGASUS_DEBUG set>> config.options
    )
    echo WIN_ENABLE_DEBUG_OPT=TRUE>> config.options
)

if not "%enable_wmi%" == "" (
    echo ENABLE_WMI_OPT=TRUE>> config.options
)

if not "%enable_static%" == "" (
    echo WIN_ENABLE_STATIC_OPT=TRUE>> config.options
)

if not "%enable_adapter_trace_opt%" == "" (
    echo WIN_ENABLE_ADAPTER_TRACE_OPT=TRUE>> config.options
)

if not "%enable_embedded_instances%" == "" (
    echo WIN_ENABLE_EMBEDDED_INSTANCES_OPT=TRUE>> config.options
)

if not "%enable_scheduler%" == "" (
    echo WIN_ENABLE_SCHEDULER_OPT=TRUE>> config.options
)

if not "%enable_adapter_trace%" == "" (
    echo ENABLE_ADAPTER_TRACE_OPT=TRUE>> config.options
)

if not "%disable_log_macros%" == "" (
    echo DISABLE_LOG_MACROS_OPT=TRUE>> config.options
)

if not "%with_namespace%" == "" (
    echo WITH_NAMESPACE_OPT=%with_namespace%>> config.options
)

:: set end of file mark
echo ## End_Of_File>> config.options


echo Created config.options
echo Configured for Windows

::==============================================================================
::
:: Clear options - Required because cmd sets all internals
::                 as env variables
::
::==============================================================================

:done
set prefix=
set bindir=
set libdir=
set includedir=
set datadir=
set cimplehome_envvar=
set with_pegasus=
set with_pegasus_includes=
set with_pegasus_libdir=
set with_pegasus_env=
set with_cmpi=
set with_openwbem=
set with_schema=
set enable_debug=
set enable_wmi=
set enable_static=
set enable_embedded_instances=
set enable_scheduler=
set enable_adapter_trace=
set disable_log_macros=
set help=
set host=
set __host=
set enable_adapter_trace_opt=

set arg0=
set prev=
set optarg=
set found=
