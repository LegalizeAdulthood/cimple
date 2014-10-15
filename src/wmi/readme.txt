
This directory contains the CIMPLE WMI adapter implementation.

Directories:
    adapter -- contains the WMI adapter for CIMPLE.
    gadget -- an example provider.

Building CIMPLE with the WMI Adapter:
=====================================

From the root of the CIMPLE source distribution:

    C:\> configure.bat --bindir=c:/windows/system32 --enable-wmi
    C:\> make

Installing the WMI Adapter:
===========================

From the root of the CIMPLE source distribution:

    C:\> make install

This installs cimplewmiadap.dll under c:/windows/system32 (from example
above).

Writing a Provider:
===================

Write as ordinary CIMPLE provider but link with cimplewmiadap.dll. See
gadget example for details.
