#ifndef USB_DFU_DEFS_H
#define USB_DFU_DEFS_H

typedef enum {
	DFU_DETACH = 0,
	DFU_DNLOAD,
	DFU_UPLOAD,
	DFU_GETSTATUS,
	DFU_CLRSTATUS,
	DFU_GETSTATE,
	DFU_ABORT
}DFU_REQUEST;

typedef enum {
	DFU_STATUS_OK = 0x00,							//No error condition is present.
	DFU_STATUS_TARGET,								//File is not targeted for use by this device.
	DFU_STATUS_FILE,									//File is for this device but fails some vendor-specific verification test.
	DFU_STATUS_WRITE,									//Device is unable to write memory.
	DFU_STATUS_ERASE,									//Memory erase function failed.
	DFU_STATUS_CHECK_ERASED,						//Memory erase check failed.
	DFU_STATUS_PROG,									//Program memory function failed.
	DFU_STATUS_VERIFY,								//Programmed memory failed verification.
	DFU_STATUS_ADDRESS,								//Cannot program memory due to received address that is out of range.
	DFU_STATUS_NOTDONE,								//Received DFU_DNLOAD with wLength = 0, but device does not think it has all of the data yet.
	DFU_STATUS_FIRMWARE,								//Device’s firmware is corrupt. It cannot return to run-time (non-DFU) operations.
	DFU_STATUS_VENDOR,								//iString indicates a vendor-specific error.
	DFU_STATUS_USBR,									//Device detected unexpected USB reset signaling.
	DFU_STATUS_POR,									//Device detected unexpected power on reset.
	DFU_STATUS_UNKNOWN,								//Something went wrong, but the device does not know what it was.
	DFU_STATUS_STALLEDPKT							//Device stalled an unexpected request.
}DFU_STATUS;

typedef enum {
	DFU_STATE_APP_IDLE = 0,							//Device is running its normal application.
	DFU_STATE_APP_DETACH,							//Device is running its normal application, has received the DFU_DETACH request, and is waiting for a USB reset.
	DFU_STATE_IDLE,									//Device is operating in the DFU mode and is waiting for requests.
	DFU_STATE_DNLOAD_SYNC,							//Device has received a block and is waiting for the host to solicit the status via DFU_GETSTATUS.
	DFU_STATE_DNBUSY,									//Device is programming a control-write block into its nonvolatile memories.
	DFU_STATE_DNLOAD_IDLE,							//Device is processing a download operation. Expecting DFU_DNLOAD requests.
	DFU_STATE_MANIFEST_SYNC,						//Device has received the final block of firmware from the host and is waiting for receipt of DFU_GETSTATUS to begin the
															//Manifestation phase; or device has completed the Manifestation phase and is waiting for receipt of
															//DFU_GETSTATUS. (Devices that can enter this state after the Manifestation phase set bmAttributes bit
															//bitManifestationTolerant to 1.)
	DFU_STATE_MANIFEST,								//Device is in the Manifestation phase. (Not all devices will be able to respond to DFU_GETSTATUS when in this state.)
	DFU_STATE_MANIFEST_WAIT,						//Device has programmed its memories and is waiting for a RESET USB reset or a power on reset. (Devices that must enter this
															//state clear bitManifestationTolerant to 0.)
	DFU_STATE_UPLOAD_IDLE,							//The device is processing an upload operation. Expecting DFU_UPLOAD requests.
	DFU_STATE_ERROR									//An error has occurred. Awaiting the DFU_CLRSTATUS request.
}DFU_STATE;

#endif // USB_DFU_DEFS_H
