#ifndef __MODSLIST_H
#define __MODSLIST_H

#include <vector>
#include <mod/amlmod.h>

typedef void (*OnInterfaceAddedFn)(const char*, const void*);
typedef const char* (*GetUpdaterURLFn)();
typedef void (*OnModLoadFn)();
typedef ModInfoDependency* (*GetDependenciesListFn)();
struct ModDesc
{
    ModInfo*            m_pInfo;
    void*               m_pHandle;
    char                m_szLibPath[256];

    OnModLoadFn         m_fnOnModLoaded;
    OnModLoadFn         m_fnOnModUnloaded;
    OnModLoadFn         m_fnOnAllModsLoaded;
    GetUpdaterURLFn     m_fnRequestUpdaterURL;
    OnInterfaceAddedFn  m_fnInterfaceAddedCB;

    ModDesc()
    {
        m_szLibPath[0] = 0;
        m_fnOnModLoaded = NULL;
        m_fnOnModUnloaded = NULL;
        m_fnOnAllModsLoaded = NULL;
        m_fnRequestUpdaterURL = NULL;
        m_fnInterfaceAddedCB = NULL;
    }
};

class ModsList
{
// Functions
public:
    bool AddMod(ModInfo* modinfo, void* modhandle, const char* path);
    bool RemoveMod(ModInfo* modinfo);
    bool RemoveMod(const char* szGUID);
    bool HasMod(const char* szGUID);
    bool HasModOfVersion(const char* szGUID, const char* szVersion);
    bool HasModOfBiggerVersion(const char* szGUID, const char* szVersion);
    void ProcessDependencies();
    void ProcessPreLoading();
    void ProcessLoading();
    void ProcessUnloading();
    void ProcessUpdater();
    inline int GetModsNum() { return m_vecModInfo.size(); }

// Callbacks
public:
    void OnInterfaceAdded(const char* name, const void* ptr);
    void OnAllModsLoaded();

private:
    std::vector<ModDesc*> m_vecModInfo;
};

extern ModsList* modlist;

#endif // __MODSLIST_H
