// dllmain.h: 模块类的声明。


class Clwsoft1Module : public ATL::CAtlDllModuleT< Clwsoft1Module >
{
public :
	DECLARE_LIBID(LIBID_lwsoft1Lib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_LWSOFT1, "{25b4ca0e-260f-4fe8-bf12-b09b4952b5e2}")
};

extern class Clwsoft1Module _AtlModule;
