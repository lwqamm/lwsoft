// dllmain.h: 模块类的声明。

class ClwsoftpulsModule : public ATL::CAtlDllModuleT< ClwsoftpulsModule >
{
public :
	DECLARE_LIBID(LIBID_lwsoftpulsLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_LWSOFTPULS, "{a68fa3bb-d77c-4470-a29e-a9f75d2ff56e}")
};

extern class ClwsoftpulsModule _AtlModule;
