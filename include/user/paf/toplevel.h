/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_USER_PAF_TOPLEVEL_H
#define _VDSUITE_USER_PAF_TOPLEVEL_H

#include <kernel.h>
#include <paf/graphics.h>
#include <paf/resource.h>
#include <paf/widget.h>

namespace paf {

	class Plugin
	{
	public:

		typedef void(*PluginCB)(Plugin *plugin);

		Plugin() {};

		~Plugin() {};

		class SceneInitParam
		{
		public:

			SceneInitParam();

			~SceneInitParam() { };

			SceInt32 unk_00;
			SceInt32 unk_04;
			SceInt32 priority;
			SceUChar8 unk_0C[0x20];
		};

		class TemplateInitParam
		{
		public:

			TemplateInitParam();

			~TemplateInitParam() { };

			SceInt32 unk_00;
			SceInt32 unk_04;
		};

		static Plugin *GetByName(const char *pluginName);

		static SceVoid LoadTexture(paf::graphics::Texture *tex, Plugin *plugin, paf::Resource::Element *textureSearchParam);

		//6F7E804D
		//SceInt32 AddTextureFromFile(paf::String *unk, const char *filePath, const char *a3);

		paf::widget::Widget *CreateScene(paf::Resource::Element *widgetInfo, SceneInitParam *initParam);

		paf::widget::Widget *CreateWidgetWithStyle(paf::widget::Widget *parent, const char *widgetType, paf::Resource::Element *widgetInfo, paf::Resource::Element *styleInfo);

		paf::widget::Widget *GetSceneByHash(paf::Resource::Element *widgetInfo);

		paf::widget::Widget *GetWidgetByNum(SceUInt32 num);

		SceInt32 AddWidgetFromTemplate(paf::widget::Widget *targetRoot, paf::Resource::Element *templateSearchParam, paf::Plugin::TemplateInitParam *param);

		SceWChar16 *GetString(paf::Resource::Element *stringInfo);

		SceUInt32 unk_00;
		char *name;
		SceUChar8 unk_08[0xA8];
		Resource *resource;
		SceUChar8 unk_B4[0x20];
		graphics::MemoryPool *memoryPool;

	private:

		SceUChar8 m_unk_B8[0x4]; //size is unknown

	};

	class Framework
	{
	public:

		enum ApplicationMode
		{
			Mode_ApplicationDefault,
			Mode_Application,
			Mode_ApplicationA,
			Mode_ApplicationB,
			Mode_ApplicationC,
			Mode_ApplicationD
		};

		static Framework *s_frameworkInstance;

		class InitParam
		{
		public:

			enum FeatureFlags
			{
				FeatureFlag_UseFwUpdateSync = 1,
				FeatureFlag_DisableInternalCallbackChecks = 2,
				FeatureFlag_4 = 4,
				FeatureFlag_8 = 8
			};

			InitParam();

			~InitParam() { };

			InitParam *LoadDefaultParams();

			SceUInt32 gxmRingBufferSize;
			SceUInt32 gxmParameterBufferSize;

			SceUInt32 unk_08;
			SceUInt32 defaultSurfacePoolSize;
			SceUInt32 graphMemSystemHeapSize;

			SceUInt32 graphMemVideoHeapSize;

			SceUInt32 textSurfaceCacheSize;
			SceUInt32 unk_1C;
			SceUInt32 unk_20;

			SceUChar8 unk_24[0x30];

			SceUInt32 fontRasterizerFlags;
			SceUInt32 fontRasterizerHeapSize;
			SceUInt32 decodeHeapSize;
			SceUInt32 defaultPluginHeapSize;
			SceUInt32 unkSize_64;
			SceInt32 screenWidth;
			SceInt32 sceenHeight;
			ApplicationMode applicationMode;
			SceUInt32 optionalFeatureFlags;
			SceInt32 language;
			SceInt32 enterButtonAssign;
			SceUInt8 allowControlWithButtons;
			SceUInt8 unkOptFlag1;
			SceUInt8 unkOptFlag2;
			SceUInt8 unkOptFlag3;
			ScePVoid unk_84;
			SceInt32 unused_88;
			SceInt32 graphicsFlags;

			SceUInt32 unk_140;

			SceUChar8 unk2[0x20];
		};

		class CommonResourceInitParam
		{
		public:

			CommonResourceInitParam();

			~CommonResourceInitParam() { };

			paf::String resourcePath;
			SceUChar8 unk_08[0x1C];
		};

		class PluginInitParam //0x94
		{
		public:

			PluginInitParam();

			~PluginInitParam() { };

			paf::String pluginName;
			paf::String scopeName;
			paf::Plugin::PluginCB loadCB1;
			paf::Plugin::PluginCB loadCB2;
			paf::Plugin::PluginCB loadCB3;
			paf::Plugin::PluginCB unloadCB1;
			paf::Plugin::PluginCB unloadCB2;
			paf::String resourcePath;

			SceUChar8 unk_38[0xC];

			SceUInt32 pluginHeapSize;

			SceUChar8 unk_48[0x10];

			SceInt32 unk_58;

			SceUChar8 unk_5C[0xC];

			paf::String pluginPath;

			SceUChar8 unk_74[0x20];
		};

		typedef void(*LoadCRFinishCallback)();
		typedef void(*LoadPluginFinishCallback)(Plugin *plugin);
		typedef void(*UnloadPluginFinishCallback)(Plugin *plugin);

		Framework(InitParam *fwInitParam);

		~Framework();

		static SceVoid InitializeDefaultJobQueue();

		static SceUInt32 GetFwLangBySystemLang(SceUInt32 systemLanguage);

		static SceVoid LoadPluginAsync(PluginInitParam *initParam, LoadPluginFinishCallback finishCallback = SCE_NULL, UnloadPluginFinishCallback unloadFinishCallback = SCE_NULL);

		static SceVoid LoadPlugin(PluginInitParam *initParam, LoadPluginFinishCallback finishCallback = SCE_NULL, UnloadPluginFinishCallback unloadFinishCallback = SCE_NULL);

		static Framework *GetInstance();

		static paf::graphics::MemoryPool *GetDefaultGraphicsMemoryPool();

		static SceVoid LoadTextureCurrentPlugin(paf::graphics::Texture *tex, Framework *fw, paf::Resource::Element *searchParam);

		static SceVoid CreateTextureFromMemory(paf::graphics::Texture *tex, Plugin *plugin, ScePVoid ptr, SceSize size, paf::Image::Type type, SceBool isCompressed, SceSize origsize);

		SceVoid _LoadPluginAsync(PluginInitParam *initParam, LoadPluginFinishCallback finishCallback = SCE_NULL, UnloadPluginFinishCallback unloadFinishCallback = SCE_NULL);

		SceInt32 EnterRenderingLoop();

		SceVoid ExitRenderingLoop();

		SceVoid LoadCommonResourceAsync(LoadCRFinishCallback finishCallback = SCE_NULL);

		SceVoid LoadCommonResourceAsync(CommonResourceInitParam *initParam, LoadCRFinishCallback finishCallback = SCE_NULL);

		SceVoid LoadCommonResource(LoadCRFinishCallback finishCallback = SCE_NULL);

		SceVoid LoadCommonResource(CommonResourceInitParam *initParam, LoadCRFinishCallback finishCallback = SCE_NULL);

		Plugin *FindPluginByName(const char *pluginName, SceBool enableSomeCheck = SCE_FALSE);

		ApplicationMode GetApplicationMode();

		paf::widget::Widget *GetCurrentScene();

		SceWChar16 *GetCRString(paf::Resource::Element *stringInfo);

		SceUChar8 unk_00[0x18];

		SceUInt32 loadedPluginNum;

		Plugin *crPlugin;

		SceUChar8 unk_20[0x34];

		ApplicationMode applicationMode;

		SceUInt32 optionalFeatureFlags;

		SceUInt32 language;

		SceUChar8 unk_60[0x14];

		SceUID powerCallbackId;

		paf::Allocator *defaultAllocator;
	};
}

#endif /* _VDSUITE_USER_PAF_TOPLEVEL_H */
