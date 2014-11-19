#ifndef USB_DFU_H
#define USB_DFU_H

class Usb;
/*
class UsbDfu : public Port
{
	Q_OBJECT
private:
	int vid, pid, ep;
	Usb* usb;
	int usbTimeout;
	int getStatus();
	int getState();
	void dnLoad(const QByteArray& buf, int dlNum);
	void upLoad(QByteArray& buf, int ulNum, int timeout);
protected:
	virtual void internalOpen();
	virtual void internalClose();

	virtual void internalWrite(const QByteArray& buf);
	virtual void internalWriteWaitCompletion() {}

	virtual void internalRead(QByteArray& buf, int maxSize, int timeout);
public:
	UsbDfu(int vid, int pid, int ep, PhoneObject* parent = NULL);
	virtual ~UsbDfu();

	void setUsbTimeout(int usbTimeout) {UsbDfu::usbTimeout = usbTimeout;}
};
*/
#endif // USB_DFU_H
