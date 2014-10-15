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

#include <objbase.h>
#include <initguid.h>
#include <strsafe.h>
#include "GadgetProviderFactory.h"
#include "GadgetProvider.h"
#include "log.h"


//==============================================================================
//
// Local definitions:
//
//==============================================================================

// {23CB8761-914A-11cf-B705-00AA0062CBBB}
DEFINE_GUID(CLSID_instprovider,
    0x23cb8761, 0x914a,
    0x11cf, 0xb7, 0x5,
    0x0, 0xaa, 0x0, 0x62,
    0xcb, 0xbb);

static void _formatGUID(REFGUID guid, char str[128])
{
    WCHAR wstr[128];
    memset(wstr, NULL, sizeof(wstr));

    StringFromGUID2(guid, wstr, sizeof(wstr) / sizeof(wstr[0]));

    memset(str, 0, 128);
    wcstombs(str, wstr, 128);
}

static void _formatCLSID(REFGUID guid, char clsid[128])
{
    char str[128];

    _formatGUID(guid, str);
    StringCbCopy(clsid, 128, "Software\\classes\\CLSID\\");
    StringCbCat(clsid, 128, (LPCTSTR)str);
}

static HRESULT _registerServer(
    HMODULE mod,
    const char* serverName,
    const char* threadingModel)
{
    char clsid[128];
    char module[MAX_PATH + 1];
    HKEY key1;
    HKEY key2;
    LONG r;

    // Format CLSID path: "Software\\classes\\CLSID\{GUID}"

    _formatCLSID(CLSID_instprovider, clsid);

    // Create "Software\\classes\\CLSID\{GUID}\InprocServer32"

    r = RegCreateKeyEx(HKEY_LOCAL_MACHINE, clsid, 0, NULL,
        REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &key1, NULL );

    if (r != ERROR_SUCCESS)
        return E_FAIL;

    r = RegSetValueEx(key1, NULL, 0, REG_SZ, (BYTE*)serverName,
        strlen(serverName) + 1);

    if (r != ERROR_SUCCESS)
    {
        RegCloseKey(key1);
        return E_FAIL;
    }

    r = RegCreateKeyEx(key1, "InprocServer32", 0, NULL,
        REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &key2, NULL );

    if (r != ERROR_SUCCESS)
    {
        RegCloseKey(key1);
        return E_FAIL;
    }

    memset(&module, NULL, sizeof(module));
    GetModuleFileName(mod, module, sizeof(module) / sizeof(char) - 1);

    r = RegSetValueEx(key2, NULL, 0, REG_SZ, (BYTE *)module, strlen(module)+1);

    if (r != ERROR_SUCCESS)
    {
        RegCloseKey(key2);
        RegCloseKey(key1);
        return E_FAIL;
    }

    // Create "Software\\classes\\CLSID\{GUID}\InprocServer32\ThreadingModel"
    
    r = RegSetValueEx(key2, "ThreadingModel", 0, REG_SZ, (BYTE*)threadingModel,
        strlen(threadingModel)+1);

    if (r != ERROR_SUCCESS)
    {
        RegCloseKey(key2);
        RegCloseKey(key1);
        return E_FAIL;
    }

    RegCloseKey(key1);
    RegCloseKey(key2);

    return NOERROR;
}

static HRESULT _unregisterServer()
{
    char clsid[128];
    char guid[128];
    HKEY key;
    DWORD r;

    // Format GUID path:

    _formatGUID(CLSID_instprovider, guid);

    // Format CLSID path: "Software\\classes\\CLSID\{GUID}"

    _formatCLSID(CLSID_instprovider, clsid);

    // Delete "Software\\classes\\CLSID\{GUID}\InProcServer32 key.

    r = RegOpenKeyEx(HKEY_LOCAL_MACHINE, clsid, 0, KEY_WRITE, &key);

    if (r == NO_ERROR)
    {
        RegDeleteKey(key, "InProcServer32");
        RegCloseKey(key);
    }

    // Delete "Software\\classes\\CLSID\{GUID} key.

    r = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
        "Software\\classes\\CLSID", 0, KEY_WRITE, &key);

    if (r == NO_ERROR)
    {
        RegDeleteKey(key, guid);
        RegCloseKey(key);
    }

    return NOERROR;
}

//==============================================================================
//
// Public definitions:
//
//==============================================================================

static HMODULE _module;

BOOL WINAPI DllMain(HINSTANCE instance, ULONG reason, LPVOID reserved)
{
    if (DLL_PROCESS_ATTACH == reason)
        _module = instance;

    return TRUE;
}

STDAPI DllGetClassObject(REFCLSID clsid, REFIID iid, LPVOID* ptr)
{
    GadgetProviderFactory* gadgetProviderFactory;

    if (clsid != CLSID_instprovider)
        return E_FAIL;

    gadgetProviderFactory = new GadgetProviderFactory();

    if (!gadgetProviderFactory)
        return E_OUTOFMEMORY;

    HRESULT hr= gadgetProviderFactory->QueryInterface(iid, ptr);

    if (FAILED(hr))
        delete gadgetProviderFactory;

    return hr;
}

STDAPI DllCanUnloadNow()
{
    if (GadgetProvider::numInstances == 0 && GadgetProvider::lock == 0)
        return S_OK;
    else
        return S_FALSE;
}

STDAPI DllRegisterServer()
{
    return _registerServer(_module, "Gadget Provider", "Both");
}

STDAPI DllUnregisterServer()
{
    return _unregisterServer();
}
