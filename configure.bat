@echo off

echo CIMPLE_PLATFORM=WIN32_IX86_MSVC>./mak/platform.mak
echo Created ./mak/platform.mak

echo #define CIMPLE_PLATFORM_WIN32_IX86_MSVC>./src/platform.h
echo Created ./src/platform.h

echo Configured for WIN32_IX86_MSVC
echo Type "make" to build CIMPLE
