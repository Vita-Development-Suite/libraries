/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_USER_PAF_LOWLAYER_H
#define _VDSUITE_USER_PAF_LOWLAYER_H

#include <libdeflt.h>
#include <kernel.h>
#include <paf/common.h>

namespace paf {
	namespace lowlayer {

		class Deflt
		{
		public:

			static SceInt32 Decompress(ScePVoid pDst, SceUInt32 uiBufSize, const ScePVoid pSrcDeflate, const ScePVoid *ppNext);
		};

	}
}

#endif /* _VDSUITE_USER_PAF_LOWLAYER_H */
