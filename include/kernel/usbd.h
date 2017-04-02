#ifndef _PSP2_KERNEL_USBD_H_
#define _PSP2_KERNEL_USBD_H_

#include <psp2kern/kernel/threadmgr.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SCE_USBD_ERROR_ACCESS 0x80240003
#define SCE_USBD_ERROR_BUSY 0x80240006
#define SCE_USBD_ERROR_FATAL 0x802400ff
#define SCE_USBD_ERROR_INTERRUPTED 0x8024000a
#define SCE_USBD_ERROR_INVALID_ARG 0x80240002
#define SCE_USBD_ERROR_IO 0x80240001
#define SCE_USBD_ERROR_NO_DEVICE 0x80240004
#define SCE_USBD_ERROR_NO_MEM 0x8024000b
#define SCE_USBD_ERROR_NOT_FOUND 0x80240005
#define SCE_USBD_ERROR_NOT_SUPPORTED 0x8024000c
#define SCE_USBD_ERROR_OVERFLOW 0x80240008
#define SCE_USBD_ERROR_PIPE 0x80240009
#define SCE_USBD_ERROR_TIMEOUT 0x80240007

typedef struct SceUsbdDeviceDescriptor {
	unsigned char  bLength;
	unsigned char  bDescriptorType;
	unsigned short bcdUSB;
	unsigned char  bDeviceClass;
	unsigned char  bDeviceSubClass;
	unsigned char  bDeviceProtocol;
	unsigned char  bMaxPacketSize0;
	unsigned short idVendor;
	unsigned short idProduct;
	unsigned short bcdDevice;
	unsigned char  iManufacturer;
	unsigned char  iProduct;
	unsigned char  iSerialNumber;
	unsigned char  bNumConfigurations;
} SceUsbdDeviceDescriptor; /* size = 20 */

struct SceUsbdEndpointDescriptor {
	unsigned char  bLength;
	unsigned char  bDescriptorType;
	unsigned char  bEndpointAddress;
	unsigned char  bmAttributes;
	unsigned short wMaxPacketSize;
	unsigned char  bInterval;

	unsigned char *extra;   /* Extra descriptors */
	int extraLength;
} SceUsbdEndpointDescriptor; /* size 16 */

typedef struct SceUsbdDeviceAddress {
	unsigned int unk0;
	unsigned short unk1;
} SceUsbdDeviceAddress; /* size = 0x6 */

typedef struct SceUsbdDriver {
	const char *name;
	int (*probe)(int device_id);
	int (*attach)(int device_id);
	int (*detach)(int device_id);
	struct SceUsbdDriver *next;
} SceUsbdDriver; /* size = 0x14 */

typedef struct SceUsbdControlTransferRequest {
	unsigned char bmRequestType;
	unsigned char bRequest;
	unsigned short wValue;
	unsigned short wIndex;
	unsigned short wLength;
} SceUsbdControlTransferRequest; /* size = 0x08 */

int sceUsbdRegisterDriver(const SceUsbdDriver *driver);
int sceUsbdRegisterCompositeLdd(const SceUsbdDriver *driver);
int sceUsbdUnregisterDriver(const SceUsbdDriver *driver);
void *sceUsbdGetDescriptor(int device_id, int index, unsigned char bDescriptorType);
int sceUsbdGetEndpointId(int device_id, SceUsbdEndpointDescriptor *endpoint);
int sceUsbdControlTransfer(int endpoint_id,
	const SceUsbdControlTransferRequest *req,
	unsigned char *buffer,
	int (*cb)(int, int, int),
	void *user_data);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_KERNEL_USBD_H_ */
