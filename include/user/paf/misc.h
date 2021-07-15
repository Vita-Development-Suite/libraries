/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_USER_PAF_MISC_H
#define _VDSUITE_USER_PAF_MISC_H

#include <libsha1.h>
#include <kernel.h>
#include <rtc.h>
#include <paf/common.h>

namespace paf {

	namespace graphics {
		class Texture;
	}

	class Allocator;

	namespace datetime {

		class DateTime
		{
		public:

			DateTime
			(
				SceUInt16 year,
				SceUInt16 month,
				SceUInt16 day,
				SceUInt16 hour,
				SceUInt16 minute,
				SceUInt16 second,
				SceUInt32 microsecond
			);

			DateTime() { };

			~DateTime();

			static SceInt32 IsLeapYear(SceInt32 year);

			static SceInt32 GetDaysInMonth(SceInt32 year, SceInt32 month);

			static SceInt32 GetCurrentTick(SceRtcTick *tick);

			static SceInt32 ConvertUtcToLoacalTime(const SceRtcTick *utc, SceRtcTick *localTime);

			static SceInt32 GetCurrentTickLocalTime(SceRtcTick *tick);

			static SceInt32 GetCurrentNetworkTick(SceRtcTick *tick);

			static SceInt32 ConvertLocalTimeToUtc(const SceRtcTick *localTime, SceRtcTick *utc);

			static SceInt32 FormatRFC3339(char *pszDateTime, SceRtcTick *tick, SceInt32 iTimeZoneMinutes);

			static SceInt32 FormatRFC3339LocalTime(char *pszDateTime, SceRtcTick *tick);

			static SceInt32 ParseRFC3339(SceRtcTick *tick, const char *pszDateTime);

			SceVoid SetFromTick(SceRtcTick *tick);

			SceVoid SetFromRFC3339(const char *pszDateTime);

			SceVoid GetCurrentClockUtc();

			SceVoid GetCurrentClockLocalTime();

			SceVoid GetCurrentNetworkClock();

			SceRtcTick ToRtcTick();

			SceVoid ToRtcTick(SceRtcTick *tick);

			SceVoid Sum(const DateTime *s1, const DateTime *s2);

			SceBool operator<(const DateTime *pDt);

			SceUInt16 year;
			SceUInt16 month;
			SceUInt16 day;
			SceUInt16 hour;
			SceUInt16 minute;
			SceUInt16 second;
			SceUInt32 microsecond;
			SceUInt32 unk_10;
			SceUInt8 unk_14;

		};

	}

	class Http
	{
	public:

		Http();

		~Http() {};

		SceVoid SetUrl(const char *url);

		SceVoid SetUrl(paf::String *url);

		SceInt32 SetUnk(SceInt32 a1, SceInt32 a2);

	private:

		SceUChar8 m_work[0xB4];

	};

	namespace io {

		enum Error
		{
			SCE_PAF_ERROR_MISC_IO_INVALID_POINTER = 0x80AF5901,
			SCE_PAF_ERROR_MISC_IO_INVALID_ARGUMENT = 0x80AF5002,
			SCE_PAF_ERROR_MISC_IO_OUT_OF_MEMORY = 0x80AF5003,
			SCE_PAF_ERROR_MISC_IO_HTTP_NOT_SUPPORTED = 0x80AF5004,
			SCE_PAF_ERROR_MISC_IO_MEM_NOT_SUPPORTED = 0x80AF5005,
			SCE_PAF_ERROR_MISC_IO_FILE_NOT_FOUND = 0x80AF5022
		};

		enum Type
		{
			Type_Dir,
			Type_File,
			Type_Reg,
			Type_Lnk
		};

		class AsyncResult
		{
		public:

			SceInt32 result;
			SceInt32 unk_04;
		};

		class File
		{
		public:

			File();

			virtual ~File();

			virtual SceInt32 Open(const char *filename, SceInt32 flag, SceIoMode mode);
			virtual SceInt32 Close();
			virtual SceInt32 Read(ScePVoid buf, SceSize nbyte);
			virtual SceInt32 Write(const ScePVoid buf, SceSize nbyte);
			virtual SceOff   Lseek(SceOff offset, SceInt32 whence, SceIoAsyncParam* asyncParam = SCE_NULL);
			virtual SceInt32 Sync();
			virtual SceInt32 OpenAsync(const char *filename, SceInt32 flag, SceMode mode);
			virtual SceInt32 CloseAsync();
			virtual SceInt32 ReadAsync(ScePVoid buf, SceSize nbyte);
			virtual SceInt32 WriteAsync(const ScePVoid buf, SceSize nbyte);
			virtual SceInt32 LseekAsync(SceOff offset, SceInt32 whence, SceIoAsyncParam* asyncParam);
			virtual SceInt32 SyncAsync();
			virtual SceInt32 WaitAsync(AsyncResult *pResult);
			virtual SceInt32 PollAsync(AsyncResult *pResult);
			virtual SceBool  IsOpened();
			virtual SceBool unkFun_44();
			virtual SceInt32 CancelAsync();
			virtual SceOff   GetSize();
			virtual SceInt32 GetStat(SceIoStat *stat);
			virtual SceInt32 SetPriority(SceUInt32 ioPriority);

			static SceInt32 Rename(const char *oldname, const char *newname);

			static SceInt32 Remove(const char *path);

			static SceOff GetSize(const char *path);

		private:

			SceUChar8 m_work[0x2C];

		};

		class Dir
		{
		public:

			class Dirent
			{
			public:

				Type type;
				paf::String name;
				SceInt32 size;
				SceUInt32 creationYear;
			};

			Dir() : uid(SCE_UID_INVALID_UID) { };

			~Dir() { };

			SceInt32 Open(const char *dirname);

			SceInt32 Close();

			SceInt32 Read(Dirent *stat);

			SceUID uid;

		};

		class Mem
		{
		public:

			virtual SceInt32 unkFun_00();
			virtual ScePVoid GetMembase();
			virtual SceSize GetSize();

			virtual ~Mem();

		private:

			Mem();

			SceUChar8 m_work[0x0C];
		};

		class Stat
		{
		public:

			static SceInt32 GetStat(const char *path, Stat *buf);

			static SceBool IsFileOrDir(const char *path);

			static SceBool IsFile(const char *path);

			static SceBool IsDir(const char *path);

			SceIoMode			st_mode;
			SceUInt32			st_attr;
			SceOff				st_size;
			datetime::DateTime	ctime;
			SceUChar8			pad1[3];
			datetime::DateTime	atime;
			SceUChar8			pad2[3];
			datetime::DateTime	mtime;
		};

		class Misc
		{
		public:

			static SceInt32 SetDefaultPriority(SceUInt32 ioPriority);

			static SceBool Exists(const char *path);

			static SceBool IsDir(const char *path);

			static SceOff GetSize(const char *path);

			static SceInt32 Rename(const char *oldname, const char *newname);

			static SceInt32 Remove(const char *path);

			static SceInt32 RemoveAny(const char *path);

			static SceInt32 RemoveRecursive(const char *path);

			static SceInt32 Mkdir(const char *dirname, SceIoMode mode);

			static SceInt32 MkdirRWSYS(const char *dirname);

			//dot-separated path list
			static SceInt32 CreateRecursive(const char *dirnameList, SceIoMode mode);

			static SceInt32 CreateRecursiveRWSYS(const char *dirnameList);
		};
	}

	class LocalFile
	{
	public:

		class OpenParam
		{
		public:

			SceUInt32 ioType;
			char *filename;
			SceInt32 flag;
			SceIoMode mode;
		};

		LocalFile();

		LocalFile(paf::Allocator *allocator);

		virtual SceInt32 GetType();
		virtual SceInt32 unkFun_04();
		virtual SceInt32 GetSize();
		virtual SceInt32 Open(OpenParam *param);
		virtual SceInt32 OpenAsync(OpenParam *param);
		virtual SceInt32 Close();
		virtual SceInt32 CloseAsync();
		virtual SceBool  IsOpened();
		virtual SceBool  unkFun_20();
		virtual SceInt32 CancelAsync();
		virtual SceInt32 Read(ScePVoid buf, SceSize nbyte);
		virtual SceInt32 ReadAsync(ScePVoid buf, SceSize nbyte);
		virtual SceInt32 Write(const ScePVoid buf, SceSize nbyte);
		virtual SceInt32 WriteAsync(const ScePVoid buf, SceSize nbyte);
		virtual SceOff   Lseek(SceOff offset, SceInt32 whence, SceIoAsyncParam* asyncParam = SCE_NULL);
		virtual SceInt32 LseekAsync(SceOff offset, SceInt32 whence, SceIoAsyncParam* asyncParam);
		virtual SceInt32 Sync();
		virtual SceInt32 SyncAsync();
		virtual SceInt32 WaitAsync(io::AsyncResult *pResult);
		virtual SceInt32 PollAsync(io::AsyncResult *pResult);
		virtual SceInt32 GetStat(SceIoStat *stat);
		virtual SceInt32 SetPriority(SceUInt32 ioPriority);

		virtual ~LocalFile();

	private:

		SceUChar8 m_work[0x2C];
	};

	class MemFile
	{
	public:

		class OpenParam
		{
		public:

			SceUInt32 ioType;
			ScePVoid ptr;
			SceSize size;
		};

		MemFile();

		virtual SceInt32 GetType();
		virtual SceInt32 unkFun_04();
		virtual SceUInt64 GetSize();
		virtual SceInt32 Open(OpenParam *param);
		virtual SceInt32 OpenAsync(OpenParam *param);
		virtual SceInt32 Close();
		virtual SceInt32 CloseAsync();
		virtual SceBool  IsOpened();
		virtual SceBool  unkFun_20();
		virtual SceInt32 CancelAsync();
		virtual SceInt32 Read(ScePVoid buf, SceSize nbyte);
		virtual SceInt32 ReadAsync(ScePVoid buf, SceSize nbyte);
		virtual SceInt32 Write(const ScePVoid buf, SceSize nbyte);
		virtual SceInt32 WriteAsync(const ScePVoid buf, SceSize nbyte);
		virtual SceInt32 Lseek(SceOff offset, SceInt32 whence, SceIoAsyncParam* asyncParam = SCE_NULL);
		virtual SceInt32 LseekAsync(SceOff offset, SceInt32 whence, SceIoAsyncParam* asyncParam);
		virtual SceInt32 Sync();
		virtual SceInt32 SyncAsync();
		virtual SceInt32 WaitAsync(io::AsyncResult *pResult);
		virtual SceInt32 PollAsync(io::AsyncResult *pResult);
		virtual SceInt32 GetStat(SceIoStat *stat); // not supported
		virtual SceInt32 SetPriority(SceUInt32 ioPriority); // not supported

		virtual ~MemFile();

	private:

		SceUChar8 m_work[0x4C];
	};

	class HttpFile
	{
	public:

		HttpFile();

		virtual SceInt32 GetType();
		virtual SceInt32 unkFun_04();
		virtual SceUInt64 GetSize();
		virtual SceInt32 Open(Http *param);
		virtual SceInt32 OpenAsync(Http *param);
		virtual SceInt32 Close();
		virtual SceInt32 CloseAsync();
		virtual SceBool  IsOpened();
		virtual SceBool  unkFun_20();
		virtual SceInt32 CancelAsync();
		virtual SceInt32 Read(ScePVoid buf, SceSize nbyte);
		virtual SceInt32 ReadAsync(ScePVoid buf, SceSize nbyte);
		virtual SceInt32 Write(const ScePVoid buf, SceSize nbyte); // not supported
		virtual SceInt32 WriteAsync(const ScePVoid buf, SceSize nbyte); // not supported
		virtual SceInt32 Lseek(SceOff offset, SceInt32 whence, SceIoAsyncParam* asyncParam = SCE_NULL);
		virtual SceInt32 LseekAsync(SceOff offset, SceInt32 whence, SceIoAsyncParam* asyncParam);
		virtual SceInt32 Sync();
		virtual SceInt32 SyncAsync();
		virtual SceInt32 WaitAsync(io::AsyncResult *pResult);
		virtual SceInt32 PollAsync(io::AsyncResult *pResult);
		virtual SceInt32 GetStat(SceIoStat *stat);
		virtual SceInt32 SetPriority(SceUInt32 ioPriority);

		virtual ~HttpFile();

		static SceInt32 GetStat(const char *url, SceIoStat *stat);

	private:

		SceUChar8 m_work[0x4C];
	};

	class Module
	{
	public:

		Module(const char *pPath, SceInt32 unused_a2, SceUInt32 flags, SceInt32 unused_a4);

		~Module();

	private:

		SceUChar8 m_work[0x4];

	};

	class Sha1
	{
	public:

		Sha1();

		~Sha1() { };

		SceInt32 BlockUpdate(const ScePVoid plain, SceUInt32 len);

		SceInt32 BlockResult(SceUChar8 *digest);

	private:

		SceSha1Context m_sha;

	};

	class Allocator
	{
	public:

		class Opt
		{
		public:

			Opt() { };

			~Opt() { };

			int a1;
			int a2;
			SceUInt8 a3_0;
			SceUInt8 a3_1;
			SceUInt8 a3_2;
			SceUInt8 a3_3;
			SceBool useCdlgMemory;
			SceSize alignment;
		};

		Allocator(ScePVoid *membase, SceSize size, const char *name, Opt *pOpt = SCE_NULL);

		virtual SceInt32 GetType();
		virtual SceBool IsCdlgMemory();
		virtual char* GetName();
		virtual SceVoid GetInfo(ScePVoid **membase, SceSize *size);
		virtual SceSize GetFreeSize();

		virtual ~Allocator();

		static Allocator *GetGlobalAllocator();

		SceVoid Deallocate(ScePVoid ptr);

		ScePVoid Allocate(SceSize size);

		ScePVoid AllocateAligned(SceSize alignment, SceSize size);

	private:

		SceUChar8 m_work[0x5C];

	};

	class Image
	{
	public:

		Image();

		~Image();

		enum Type
		{
			Type_AutoDetect,
			Type_PNG,
			Type_JPEG,
			Type_TIFF,
			Type_GIF,
			Type_BMP,
			Type_GIM,
			Type_DDS
		};


		class LoadResult
		{
		public:

			Image *img;
			ScePVoid unk_04;
		};

		class Resolution
		{
		public:

			SceUInt32 width;
			SceUInt32 height;
		};

		//ScePafMisc_57AD1093
		static Type GetTypeFromFile(const char *pPath, SceInt32 unused, SceOff offset, SceIoAsyncParam* asyncIoParam);

		//ScePafMisc_D77AEA5F
		static Type GetTypeFromMem(ScePVoid imageBuf, SceSize imageSize);

		static SceVoid LoadFromFile(LoadResult *pRes, const char *pPath, paf::Allocator *allocator, Type type, SceOff offset, SceIoAsyncParam* asyncIoParam, SceSize sizeWithoutOffset);

		//ScePafMisc_C341D895
		static SceInt32 LoadFromMem(LoadResult *pRes, ScePVoid imageBuf, SceSize imageSize, paf::Allocator *allocator, Type type);

		//ScePafMisc_29E8BCA7
		static SceVoid Convert(LoadResult *pRes, Image *pSrc, SceUInt32 targetType, SceInt32 a4);

		//ScePafMisc_502BC2CF
		static SceVoid ToTexture(paf::graphics::Texture *pTex, Image *pImg, SceInt32 a3);

		static SceInt32 GetLastError();

		static SceBool SetLastError(SceInt32 errorCode);

		static SceVoid GetResolution(Resolution *pRes, Image *img);

		SceInt32 GetType();

		SceInt32 GetPaletteColorNum();

		//147115CE
		SceUInt32 GetFormat();

		//7B15112F
		SceUInt32 GetOrderType();
	};

	class Misc
	{
	public:

		class OpenResult
		{
		public:

			union
			{
				LocalFile *localFile;
				MemFile *memFile;
				HttpFile *httpFile;
				io::Mem *memory;
			};

			ScePVoid unk_04;
		};

		static SceVoid OpenMemDirect(OpenResult *res, ScePVoid ptr, SceSize size);

		static SceVoid OpenFile(OpenResult *res, const char *path, SceInt32 flag, SceIoMode mode, SceInt32 *error);

		static SceVoid OpenMem(OpenResult *res, ScePVoid ptr, SceSize size, SceInt32 *error);

		static SceVoid OpenMem(OpenResult *res, OpenResult *memory, SceInt32 *error);

		static SceVoid OpenHttp(OpenResult *res, const SceWChar16 *url, SceInt32 *error, SceInt32 timeout);

		static SceVoid OpenHttp(OpenResult *res, const char *url, SceInt32 *error, SceInt32 timeout);

		static SceBool IsDolce();

		static SceVoid SuspendTouchInput(SceUInt32 port);

		static SceVoid ResumeTouchInput(SceUInt32 port);

		//ScePafMisc_5E39FCE1
		static SceInt32 Decompress(ScePVoid memOut, SceSize origsize, ScePVoid memIn, SceSize size, SceInt32 libType = 1);

		static SceInt32 Test1(char *path);
	};
}

#endif /* _VDSUITE_USER_PAF_MISC_H */
