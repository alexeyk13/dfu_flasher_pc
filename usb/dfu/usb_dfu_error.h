#ifndef USB_DFU_ERROR_H
#define USB_DFU_ERROR_H

#include <exception>

class ErrorDfu: public std::exception
{
	virtual const char* what() const throw()  {return "Generic DFU error";}
};

class ErrorDfuTarget: public std::exception
{
	virtual const char* what() const throw()  {return "File is not targeted for use by this device";}
};

class ErrorDfuFile: public std::exception
{
	virtual const char* what() const throw()  {return "File is for this device but fails some vendor-specific verification test";}
};

class ErrorDfuWrite: public std::exception
{
	virtual const char* what() const throw()  {return "Device is unable to write memory";}
};

class ErrorDfuErase: public std::exception
{
	virtual const char* what() const throw()  {return "Memory erase function failed";}
};

class ErrorDfuCheckErased: public std::exception
{
	virtual const char* what() const throw()  {return "Memory erase check failed";}
};

class ErrorDfuProg: public std::exception
{
	virtual const char* what() const throw()  {return "Program memory function failed";}
};

class ErrorDfuVerify: public std::exception
{
	virtual const char* what() const throw()  {return "Programmed memory failed verification";}
};

class ErrorDfuAddress: public std::exception
{
	virtual const char* what() const throw()  {return "Cannot program memory due to received address that is out of range";}
};

class ErrorDfuNotDone: public std::exception
{
	virtual const char* what() const throw()  {return "Received DFU_DNLOAD with wLength = 0, but device does not think it has all of the data yet";}
};

class ErrorDfuFirmware: public std::exception
{
	virtual const char* what() const throw()  {return "Device’s firmware is corrupt. It cannot return to run-time (non-DFU) operations";}
};

class ErrorDfuVendor: public std::exception
{
	virtual const char* what() const throw()  {return "iString indicates a vendor-specific error";}
};

class ErrorDfuUsbReset: public std::exception
{
	virtual const char* what() const throw()  {return "Device detected unexpected USB reset signaling";}
};

class ErrorDfuPor: public std::exception
{
	virtual const char* what() const throw()  {return "Device detected unexpected power on reset";}
};

class ErrorDfuUnknown: public std::exception
{
	virtual const char* what() const throw()  {return "Something went wrong, but the device does not know what it was";}
};

class ErrorDfuStalled: public std::exception
{
	virtual const char* what() const throw()  {return "Device stalled an unexpected request";}
};

#endif // USB_DFU_ERROR_H
