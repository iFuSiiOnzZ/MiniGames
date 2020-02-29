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
#include <dlfcn.h>

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
        void *m_ProcPtr;

    public:
        explicit ProcPtr(void *ptr) : m_ProcPtr(ptr)
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
        void *m_hDLLModule;

    public:
        explicit DLLHelper(const char *dllName) : m_hDLLModule(dlopen(dllName, RTLD_NOW))
        {
        }

        ~DLLHelper()
        {
            dlclose(m_hDLLModule);
        }

        ProcPtr operator[](const char *fncName)
        {
            return ProcPtr(dlsym(m_hDLLModule, fncName));
        }
};
