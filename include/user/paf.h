/*
	Vita Development Suite Libraries
*/

#ifndef _VDSUITE_USER_PAF_H
#define _VDSUITE_USER_PAF_H

//Class forward declarations

namespace paf {

	class Framework;
	class Plugin;

	class Resource;

	class String;
	class WString;

	namespace widget {

		class Widget;
		class BusyIndicator;
		class Text;
		class TextBox;
		class Plane;
		class SpeechBalloon;
		class Box;
		class AppIcon2D;
		class Button;
		class CornerButton;
		class Dialog;
		class ImageButton;
		class ImageSlidebar;
		class CompositeDrawer;
		class SlidingDrawer;
		class ScrollViewParent;
		class ScrollBar2D;
		class ScrollBarTouch;
		class ScrollBar;
		class SlideBar;
		class RichText;
		class PageTurn;
		class ProgressBar;
		class ProgressBarTouch;
		class ListItem;
		class ListView;
		class FileList;
		class RadioBox;
		class RadioButton;
		class ItemSpin;
		class NumSpin;
		class PlaneButton;
		class CheckBox;
		class CompositeButton;
		class SpinBase;
		class AppIconBase;
	}

	namespace graphics {

		class TextObj;
		class MemoryPool;
		class Surface;
		class Texture;
		class DrawQueue;
	}

	namespace datetime {

		class DateTime;
	}

	namespace io {

		class File;
		class Dir;
	}

	class Module;
	class Sha1;
	class Allocator;

	namespace thread {

		class DefaultThreadPriority;
		class Thread;
		class Sema;
		class Mutex;
		class Mutex2;
		class Cond;
		class RWLock;
		class Queue;
		class SyncCall;
		class JobQueue;
	}
}

#include <paf/stdc.h>
#include <paf/widget.h>
#include <paf/common.h>
#include <paf/graphics.h>
#include <paf/toplevel.h>
#include <paf/misc.h>
#include <paf/resource.h>
#include <paf/thread.h>
#include <paf/lowlayer.h>

#endif /* _VDSUITE_USER_PAF_H */

