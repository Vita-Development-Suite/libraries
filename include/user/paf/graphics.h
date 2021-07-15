/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_USER_PAF_GRAPHICS_H
#define _VDSUITE_USER_PAF_GRAPHICS_H

#include <kernel.h>
#include <gxm.h>
#include <scetypes.h>
#include <paf/misc.h>

namespace paf {

	namespace graphics {

		class TextObj
		{
		public:

			//ScePafGraphics_F201F98D c1
			//ScePafGraphics_29013890 c2
			TextObj(SceInt32 *flags);

			//ScePafGraphics_FA7B17C2 d2
			//ScePafGraphics_8021A2B3 d0
			//ScePafGraphics_919B8983 d1
			virtual ~TextObj();

			virtual SceBool ContainsType(const char *pTypeName);
			virtual char *GetType();
			virtual SceInt32 unkFun_08();
			virtual SceInt32 unkFun_0C(); // D0, why is it here?
			virtual SceInt32 unkFun_10();
			virtual SceInt32 unkFun_14();
			virtual SceInt32 unkFun_18(); // test
			virtual SceInt32 unkFun_1C();
			virtual SceInt32 unkFun_20();
			virtual SceInt32 unkFun_24();
			virtual SceInt32 unkFun_28();
			virtual SceInt32 unkFun_2C();
			virtual SceInt32 unkFun_30();
			virtual SceInt32 unkFun_34();
			virtual SceInt32 unkFun_38(); // test
			virtual SceInt32 unkFun_3C(); // test
			virtual SceInt32 unkFun_40();
			virtual SceInt32 unkFun_44();

			//ScePafGraphics_1BDA4425
			SceInt32 GetLabel(WString *pText);

			//ScePafGraphics_AE415C90
			SceInt32 SetLabel(WString *pText);

			//ScePafGraphics_DC2C405E
			SceInt32 SetPlaceholderLabel(WString *pText);

			//ScePafGraphics_D3BEDF03
			SceInt32 GetPlaceholderLabel(WString *pText);

			SceInt32 GetLength(SceUInt32 *pLength);

			//ScePafGraphics_67094D42
			SceInt32 GetDataAndLength(SceWChar16 **ppData, SceUInt32 *pLength);

			static SceInt32 *s_defaultTextObjFlags;

		private:

			SceUChar8 unk_00[0x58];

		};

		class MemoryPool
		{
		public:

			enum MemoryType
			{
				MemoryType_UserNC,
				MemoryType_CDRAM,
				MemoryType_Shared,
			};

			class InitParam
			{
			public:

				ScePVoid pMemory;
				SceSize size;
				char *pName;
				paf::Allocator::Opt *pAllocatorOpt;
				ScePVoid pUnkAllocatorOpt;
				SceUInt32 memoryType;
			};

			MemoryPool(InitParam *pInitParam);

			MemoryPool(ScePVoid pMemory, SceSize size, const char *pName, paf::Allocator::Opt *pAllocatorOpt = SCE_NULL, SceUInt32 memoryType = 0);

			virtual ~MemoryPool();

			virtual int unkf1();
			virtual int unkf2();
			virtual int unkf3();

			enum MemoryTypeSpecial
			{
				MemoryTypeSpecial_Unused,
				MemoryTypeSpecial_Tool,
				MemoryTypeSpecial_Phycont
			};

			enum GpuMapType
			{
				GpuMapType_Normal,
				GpuMapType_VertexUsse,
				GpuMapType_FragmentUsse,
				GpuMapType_NoMap
			};

			class MemBlockOptParam
			{
			public:

				MemoryTypeSpecial memoryTypeSpecial;
				SceKernelAllocMemBlockOpt *memBlockOpt;
				GpuMapType gpuMapType;
				SceUInt32 mapAttribs;
				SceUInt32 usseOffset;
				SceUInt32 unused;
			};

			static ScePVoid AllocMemBlock(MemoryType memoryType, SceSize size, const char *pName, ScePVoid pOptParam = SCE_NULL);

			static SceVoid FreeMemBlock(MemoryType memoryType, ScePVoid pMemory);

			static MemoryPool *GetDefaultMemoryPool();

		private:

			SceUChar8 m_work[0x48];

		};

		class Surface
		{
		public:

			class GxmTexture
			{
			public:

				SceGxmTexture *texture;
				SceInt32 unk_04;
			};

			class Base
			{
			public:

				Base *prev;
				Base *next;
				SceInt32 lock;
				SceUInt16 width;
				SceUInt16 height;
				SceInt32 texType; // linear/swizzled/tiled
				SceInt32 unk_14;
				SceInt32 unk_18;
				SceUInt16 widthAligned;
				SceUInt16 heightAligned;
				SceFloat32 xScale;
				SceFloat32 yScale;
				SceInt32 pixels;
				SceUInt16 width3;
				SceUInt16 unk_3e;
				SceInt32 unk_30;
				GxmTexture *texture;
				SceGxmTextureFilter magFilter;
				SceGxmTextureFilter minFilter;
				SceGxmTextureFilter mipFilter;
				SceGxmTextureAddrMode uaddrMode;
				SceGxmTextureAddrMode vaddrMode;
				SceUInt32 lodBias;
				SceInt32 unk_50;
				SceInt32 unk_54;
				SceInt32 unk_58;
				ScePVoid gxmData;
			};

			Surface(MemoryPool *pMemPool, SceUInt32 width, SceUInt32 height, SceUInt32 format, SceUInt32 orderType, SceInt32 a7, SceUInt32 numLevel, SceInt32 a9);

			virtual ~Surface();

			virtual int unkf1();
			virtual int unkf2();
			virtual int unkf3();
			virtual int unkf4();
			virtual int unkf5();
			virtual int unkf6();
			virtual int unkf7();
			virtual int unkf8();
			virtual int unkf9();
			virtual int unkf10();

			void* operator new(size_t size);

			void operator delete(void*);

			//ScePafGraphics_E57728C4
			static SceInt32 Copy(Surface *dst, SceInt32 a2, Surface *src, SceUInt32 srcOrderType, SceSize copySize, SceInt32 a6 = -1);

			SceInt32 GetLock();

			//ScePafGraphics_879B135D
			ScePVoid GetGxmData();

			//ScePafGraphics_D075A824
			SceInt32 ReplaceData(SceGxmTexture **tex, const ScePVoid data);

			//ScePafGraphics_3B5327DF
			SceUInt32 GetPixelCount();

			//ScePafGraphics_804E92B1
			SceInt32 ApplyFilters();

			SceInt32 texFormat;
			SceInt32 unk_08;
			SceInt32 unk_0C;
			Base base;

		private:

			SceUChar8 m_work[0x24];

		};

		class Texture
		{
		public:

			Texture() { };

			~Texture() { };

			static SceVoid CreateFromFile(Texture *tex, MemoryPool *memPool, paf::Misc::OpenResult *file, ScePVoid fwOpt = SCE_NULL);

			static SceVoid CreateFromMemory(Texture *tex, MemoryPool *memPool, ScePVoid ptr, SceInt32 unused_1, SceSize size, SceInt32 unused_2 = 0, ScePVoid fwOpt = SCE_NULL);

			Surface *texSurface;

			ScePVoid unk;
		};

		class FwGraphicsContext
		{
		public:

			class ShaderPatcher {
			public:

				SceGxmShaderPatcher *shaderPatcher;

				//more?
			};

			enum Target
			{
				Target_None,
				Target_Front,
				Target_Back
			};

			static FwGraphicsContext *GetFwGraphicsContext();

			//ScePafGraphics_E4B3B1D2
			SceVoid Finish();

			//ScePafGraphics_751FC8E6
			SceInt32 BeginScene(const SceGxmRenderTarget *renderTarget, SceGxmSyncObject *fragmentSyncObject, const SceGxmColorSurface *colorSurface, const SceGxmDepthStencilSurface *depthStencilSurface, SceUInt32 flags);

			//ScePafGraphics_D5E30C64
			SceInt32 EndScene(const SceGxmNotification *vertexNotification, const SceGxmNotification *fragmentNotification);

			//ScePafGraphics_6E7B77AC
			SceVoid SetWClampValue(float clampValue);

			//ScePafGraphics_84619C66
			SceVoid SetPolygonMode(SceGxmPolygonMode mode, SceUInt32 target);

			//ScePafGraphics_D9EA2729
			SceVoid SetPointLineWidth(SceFloat32 width, SceUInt32 target);

			//ScePafGraphics_9EAD43B5
			SceVoid SetPointLineWidth2(SceFloat32 width, SceUInt32 target);

			//ScePafGraphics_DAC195AC
			SceVoid SetStencilFunc(SceGxmStencilFunc func, SceGxmStencilOp stencilFail, SceGxmStencilOp depthFail, SceGxmStencilOp depthPass, uint8_t compareMask, uint8_t writeMask, SceUInt32 target);

			//ScePafGraphics_722A4987
			SceVoid SetCullMode(SceGxmCullMode mode);

			//ScePafGraphics_7EC1D482
			SceVoid SetDepthFunc(SceGxmDepthFunc depthFunc, SceUInt32 target);

			//ScePafGraphics_2AE23377
			SceVoid SetDepthWriteEnable(SceGxmDepthWriteMode enable, SceUInt32 target);

			//ScePafGraphics_5F8FDEC7
			SceVoid ResetParam(SceUInt32 targetParam);

			SceUChar8 unk_000[0x61C];

			ShaderPatcher *shaderPatcher;

			SceUChar8 unk_620[0x6C];

			SceGxmContext *gxmContext;

			SceUChar8 unk_690[0xD4];

			SceUInt8 frontDepthWriteEnabled;
			SceUInt8 backDepthWriteEnabled;

			SceUInt16 unk_766;

			SceGxmCullMode cullMode;
		};

		class DrawQueue
		{
		public:

			class Item;

			class Request
			{
			public:

				typedef void(*RequestEntryFunction)(Item *job);

				Item *job;
				SceInt32 unk_04;
				SceInt32 unk_08;
				RequestEntryFunction entry;

			};

			class Item
			{
			public:

				Item() { };

				virtual ~Item() { };

				virtual SceVoid DrawCB() = 0;

				virtual SceVoid UnkCB2() = 0;

				virtual SceVoid UnkCB3() = 0;

				Request *req;

			private:

				SceUChar8 m_work[0x0C];

			};

			class ItemParam
			{
			public:

				Item *item;
				Request *request;
			};

			DrawQueue() { };

			~DrawQueue() { };

			SceInt32 SetDrawJob(ItemParam *queueItemParam);
		};
	}
}

#endif /* _VDSUITE_USER_PAF_GRAPHICS_H */
