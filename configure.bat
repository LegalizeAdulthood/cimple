@echo off

set arg0=%0

::==============================================================================
::
:: Process options.
::
::==============================================================================

set prev=

:loop

  set found=

  ::
  :: Get option argument
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

  ::
  :: Get option
  ::

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

  if "%1" == "--enable-embedded-instances" (
    set enable_embedded_instances=1
    set found=1
  )

  if "%1" == "--enable-scheduler" (
    set enable_scheduler=1
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
:: Deduce options
::
::==============================================================================

if "%with_pegasus_env%" == "1" (

  if "%PEGASUS_PLATFORM%" == "" (
    echo %arg0%: --with-pegasus-env needs PEGASUS_PLATFORM environment variable.
    goto done
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
    set enable_debug=1
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

if "%with_schema%" == "" (
  set with_schema=%datadir%/cimple/schema/cim214
)

::==============================================================================
::
:: Echo options
::
::==============================================================================

goto skip
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
echo enable_embedded_instances=%enable_embedded_instances%
echo enable_scheduler=%enable_scheduler%
:skip

::==============================================================================
::
:: Create config.options
::
::==============================================================================

echo PLATFORM=WIN32_IX86_MSVC> config.options
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

if not "%enable_debug%" == "" (
    echo WIN_ENABLE_DEBUG_OPT=TRUE>> config.options
)

if not "%enable_wmi%" == "" (
    echo ENABLE_WMI_OPT=TRUE>> config.options
)

if not "%enable_static%" == "" (
    echo WIN_ENABLE_STATIC_OPT=TRUE>> config.options
)

if not "%enable_embedded_instances%" == "" (
    echo WIN_ENABLE_EMBEDDED_INSTANCES_OPT=TRUE>> config.options
)

if not "%enable_scheduler%" == "" (
    echo WIN_ENABLE_SCHEDULER_OPT=TRUE>> config.options
)

if not "%with_namespace%" == "" (
    echo WITH_NAMESPACE_OPT=%with_namespace%>> config.options
)

echo Created config.options
echo Configured for Windows

::==============================================================================
::
:: Clear options
::
::==============================================================================

:done
set prefix=
set bindir=
set libdir=
set includedir=
set datadir=
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

set arg0=
set prev=
set optarg=
set found=
