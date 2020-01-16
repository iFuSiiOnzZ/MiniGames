#pragma once

//
// Project includes
//

//
// Lib includes
//

//
// C/C++ includes
//

//
// Platfrom includes
//
#include <Windows.h>

//
// Defines/Constants
//

//
// Enums/Strucsts
//

// https://blog.benoitblanchon.fr/getprocaddress-like-a-boss/
///////////////////////////////////////////////////////////////////////////////

class ProcPtr
{
    private:
        FARPROC m_ProcPtr;

    public:
        explicit ProcPtr(FARPROC ptr) : m_ProcPtr(ptr)
        {
        }

        template <typename T> operator T *() const
        {
            return reinterpret_cast<T *>(m_ProcPtr);
        }
};

class DLLHelper
{
    private:
        HMODULE m_hDLLModule;

    public:
        explicit DLLHelper(const char *dllName) : m_hDLLModule(LoadLibraryA(dllName))
        {
        }

        ~DLLHelper()
        {
            FreeLibrary(m_hDLLModule);
        }

        ProcPtr operator[](const char *fncName)
        {
            return ProcPtr(GetProcAddress(m_hDLLModule, fncName));
        }
};
