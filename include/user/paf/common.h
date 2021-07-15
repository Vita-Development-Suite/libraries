/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_USER_PAF_COMMON_H
#define _VDSUITE_USER_PAF_COMMON_H

#include <scetypes.h>
#include <paf/stdc.h>

namespace paf {

	namespace widget {
		class Widget;
	}

	class String;
	class WString;

	class String
	{
	public:

		String(const char *str);

		String(const char *str, SceSize strLength);

		String(String *src);

		String();

		~String()
		{
			if (length != 0 && data != &null)
				delete data;
		}

		static SceSSize ToWString(const char *src, paf::WString *dst);

		static SceSSize ToWString(const char *src, paf::WString *dst, SceUInt32 flags);

		static String *WCharToNewString(const SceWChar16 *src, String *dst);

		SceSSize ToWString(paf::WString *dst);

		SceSSize ToWString(paf::WString *dst, SceUInt32 flags);

		SceVoid MemsizeFormat(SceSize memsize);

		SceVoid Setf(const char *format, ...);

		SceVoid Set(const char* c, SceInt32 len)
		{
			Clear();

			if (!len)
			{
				SetEmpty();

				return;
			}

			Copy(c, len);
		}

		SceVoid Set(const char* c)
		{
			SceInt32 len = sce_paf_strlen(c);

			Clear();

			if (!len)
			{
				SetEmpty();

				return;
			}

			Copy(c, len);
		}

		SceVoid Clear()
		{
			if (IsEmpty())
			{
				return;
			}

			delete data;

			SetEmpty();
		}

		String *operator=(const char* c)
		{
			Clear();

			Copy(c, sce_paf_strlen(c));
			return this;
		}

		String *operator=(const String *s)
		{
			Clear();

			Copy(s->data, s->length);
			return this;
		}

		String operator+(const String *s) const
		{
			SceInt32 len1 = length;
			SceInt32 len2 = s->length;

			if (!len1 && !len2)
			{
				String ret;
				return ret;
			}

			char* newptr = new char[len1 + len2 + 1];

			if (newptr == SCE_NULL)
			{
				String ret;
				return ret;
			}

			sce_paf_memcpy(newptr, data, sizeof(char) * len1);
			sce_paf_memcpy(&newptr[len1], s->data, sizeof(char) * (s->length + 1));

			String ret(newptr, len1 + len2);
			delete newptr;

			return ret;
		}

		String operator+(const char* c) const
		{
			SceInt32 len1 = length;
			SceInt32 len2 = sce_paf_strlen(c);

			char* newptr = new char[len1 + len2 + 1];

			if (newptr == SCE_NULL)
			{
				String ret;
				return ret;
			}

			sce_paf_memcpy(newptr, data, sizeof(char) * len1);
			sce_paf_memcpy(&newptr[len1], c, sizeof(char) * (len2 + 1));

			String ret(newptr, len1 + len2);
			delete newptr;

			return ret;
		}

		String *operator+=(const String *s)
		{
			char* newptr = SCE_NULL;
			SceInt32 len1 = length;

			newptr = new char[length + s->length + 1];

			sce_paf_memcpy(newptr, data, len1);
			sce_paf_memcpy(&newptr[len1], s->data, s->length + 1);

			Clear();
			Set(newptr, len1 + s->length);
			delete newptr;

			return this;
		}

		String *operator+=(const char* c)
		{
			SceInt32 len1 = length;
			SceInt32 len2 = sce_paf_strlen(c);

			char* newptr = new char[len1 + len2 + 1];

			sce_paf_memcpy(newptr, data, len1);
			sce_paf_memcpy(&newptr[len1], c, len2 + 1);

			Clear();
			Set(newptr, len1 + len2);
			delete newptr;

			return this;
		}

		SceBool operator==(const String *s) const
		{
			if (s->length != length)
				return SCE_FALSE;

			if (sce_paf_strncmp(data, s->data, length))
				return SCE_FALSE;

			return SCE_TRUE;
		}

		SceBool operator==(const char* rc) const
		{
			if (sce_paf_strlen(rc) != length)
				return SCE_FALSE;

			if (sce_paf_strncmp(data, rc, length))
				return SCE_FALSE;

			return SCE_TRUE;
		}

		SceBool operator<(const String *s) const
		{
			return sce_paf_strcmp(data, s->data) < 0;
		}

		SceBool operator<(const char* c) const
		{
			return sce_paf_strcmp(data, c) < 0;
		}

		SceBool operator>(const String *s) const
		{
			return sce_paf_strcmp(data, s->data) > 0;
		}

		SceBool operator>(const char* c) const
		{
			return sce_paf_strcmp(data, c) > 0;
		}

		String *Append(const char* c, SceInt32 len2)
		{
			SceInt32 len1 = length;

			char *newptr = new char[len1 + len2 + 1];

			sce_paf_memcpy(newptr, data, len1);
			sce_paf_memcpy(&newptr[len1], c, len2);

			Clear();
			Set(newptr, len1 + len2);
			delete newptr;

			return this;
		}

		SceVoid Copy(const char* c, SceInt32 cLength)
		{
			if (!cLength)
			{
				return;
			}

			length = cLength;

			data = new char[length + 1];

			sce_paf_memcpy(data, c, cLength);
			data[cLength] = 0;
		}

		SceBool IsEmpty() const
		{
			if (data == &null && length == 0)
				return SCE_TRUE;
			else
				return SCE_FALSE;
		}

		SceVoid SetEmpty()
		{
			data = &null;
			length = 0;
		}

		static char null;

		char *data;
		SceSize length;

	private:

		SceUInt32 m_work;

	};

	class WString
	{
	public:

		WString() : data(&null), length(0)
		{

		}

		WString(const SceWChar16 *s, SceSize srcLength) : data(&null), length(0)
		{
			if (srcLength == 0 || s == SCE_NULL || s[0] == 0) {
				return;
			}

			data = new SceWChar16[srcLength + 1];
			length = srcLength;
			sce_paf_wmemcpy((wchar_t*)data, (wchar_t*)s, length);
			data[length] = 0;

			return;
		}

		WString(const SceWChar16 *s) : data(&null), length(0)
		{
			SceSize srcLength = sce_paf_wcslen((wchar_t*)s);

			if (srcLength == 0 || s == SCE_NULL || s[0] == 0) {
				return;
			}

			data = new SceWChar16[srcLength + 1];
			length = srcLength;
			sce_paf_wmemcpy((wchar_t*)data, (wchar_t*)s, length);
			data[length] = 0;

			return;
		}

		~WString()
		{
			if (length != 0 && data != &null)
				delete data;
		}

		static SceSSize ToString(const SceWChar16 *src, String *dst);

		static SceSSize ToString(const SceWChar16 *src, String *dst, SceUInt32 flags);

		static WString *CharToNewWString(const char *src, WString *dst);

		SceSSize ToString(String *dst);

		SceSSize ToString(String *dst, SceUInt32 flags);

		WString *Set(const SceWChar16 *s, SceSize srcLength)
		{
			if (data == s)
				return this;

			if (data != &null)
				delete data;

			if (srcLength == 0 || s == SCE_NULL || s[0] == 0) {
				data = &null;
				length = 0;
				return this;
			}

			data = new SceWChar16[srcLength + 1];
			length = srcLength;
			sce_paf_wmemcpy((wchar_t*)data, (wchar_t*)s, length);
			data[length] = 0;

			return this;
		};

		WString *Set(const SceWChar16 *s)
		{
			Set(s, sce_paf_wcslen((wchar_t *)s));
			return this;
		};

		WString *Append(const SceWChar16 *c, SceInt32 len2)
		{
			SceInt32 len1 = length;

			SceWChar16 *newptr = new SceWChar16[len1 + len2 + 1];

			sce_paf_wmemcpy((wchar_t *)newptr, (wchar_t *)data, len1);
			sce_paf_wmemcpy((wchar_t *)&newptr[len1], (wchar_t *)c, len2);

			Clear();
			Set(newptr, len1 + len2);
			delete newptr;

			return this;
		}

		WString *operator=(const WString *s)
		{
			if (data == s->data)
				return this;

			if (s->length == 0) {
				data = &null;
				length = 0;
				return this;
			}

			data = new SceWChar16[s->length + 1];
			length = s->length;
			sce_paf_wmemcpy((wchar_t*)data, (wchar_t*)s->data, s->length + 1);

			return this;
		}

		WString *operator+(const String *s) const
		{
			WString *newStr = new WString;

			if (!length && !s->length)
			{
				return newStr;
			}

			newStr->data = new SceWChar16[s->length + length + 1];
			newStr->length = s->length + length;
			sce_paf_wmemcpy((wchar_t*)newStr->data, (wchar_t*)data, length);
			sce_paf_wmemcpy((wchar_t*)&newStr->data[length], (wchar_t*)s->data, s->length + 1);
			newStr->data[newStr->length] = 0;
			return newStr;
		}

		SceBool operator==(const WString *s) const
		{
			if (s->length != length)
				return SCE_FALSE;

			if (!sce_paf_wcsncmp((wchar_t*)s->data, (wchar_t*)data, length))
				return SCE_TRUE;
			else
				return SCE_FALSE;
		}

		SceVoid Clear()
		{
			if (length != 0 && data != &null) {
				delete data;
				length = 0;
				data = &null;
			}
		}

		static SceWChar16 null;

		SceWChar16 *data;
		SceSize length;

	private:

		SceUInt32 m_work;
	};

	class SWString
	{
	public:

		SWString();

		SWString(const char *str);

		SWString(const SceWChar16 *str);

		SWString(String *src);

		SWString(WString *src);

		~SWString();

		String string;
		WString wstring;
	};

	namespace common {

		class Utils
		{
		public:

			enum CesFlags
			{
				AllowIllegalCode = 0x2,
				AllowOutOfCodeRange = 0x4,
				AllowInvalidEncode = 0x8,
				AllowSrcBufferEnd = 0x10
			};

			typedef void(*MainThreadTaskEntryFunction)(void *pArgBlock);

			static SceVoid AddMainThreadTask(MainThreadTaskEntryFunction entry, ScePVoid pArgBlock);

			static SceVoid RemoveMainThreadTask(MainThreadTaskEntryFunction entry, ScePVoid pArgBlock);

			static paf::widget::Widget *WidgetStateTransition(SceFloat32 animationSpeed, paf::widget::Widget *widget, SceUInt32 animationId, SceBool disableOnEnd, SceBool skipAnimation);

			static paf::widget::Widget *WidgetStateTransitionReverse(SceFloat32 animationSpeed, paf::widget::Widget *widget, SceUInt32 animationId, SceBool disableOnEnd, SceBool skipAnimation);
		};

	}
}

#endif /* _VDSUITE_USER_PAF_COMMON_H */
