/*
 * 
 * Class to control Kinect's motor on Linux Ubuntu
 * Code taken from: https://github.com/manctl/openni/blob/manctl/Samples/Kinect/kinect-motors.cpp
 * Adapted and modified by : Oscar Lima
 * 
 */

#include <XnUSB.h>
#include <cstdio>

#ifdef _WIN32
#include <Windows.h>
void pause_ ()
{
    Sleep(1000);
}
#else
#include <unistd.h>
void pause_ ()
{
    sleep(1);
}
#endif

#include <iostream>
using namespace std;

int MAX_ATTEMPS = 3; 			//Maximum amount of times the user should tilt the kinect
int KINECT_ANGLE_RANGE = 40;	//60 max, for safety reasons: 40

class KinectMotors
{
public:
    enum { MaxDevs = 16 };

public:
    KinectMotors();
    virtual ~KinectMotors();
    
    /**
* Open device.
* @return true if succeeded, false - overwise
*/
    bool Open();
    
    /**
* Close device.
*/
    void Close();
    
    /**
* Move motor up or down to specified angle value.
* @param angle angle value
* @return true if succeeded, false - overwise
*/
    bool Move(int angle);
    
private:
    XN_USB_DEV_HANDLE m_devs[MaxDevs];
    XnUInt32 m_num;
    bool m_isOpen;
};

KinectMotors::KinectMotors()
{
    m_isOpen = false;
}

KinectMotors::~KinectMotors()
{
    Close();
}

bool KinectMotors::Open()
{
    const XnUSBConnectionString *paths;
    XnUInt32 count;
    XnStatus res;
    
    // Init OpenNI USB
    res = xnUSBInit();
    if (res != XN_STATUS_OK)
    {
        xnPrintError(res, "xnUSBInit failed");
        return false;
    }
    
    // Open all "Kinect motor" USB devices
    res = xnUSBEnumerateDevices(0x045E /* VendorID */, 0x02B0 /*ProductID*/, &paths, &count);
    if (res != XN_STATUS_OK)
    {
        xnPrintError(res, "xnUSBEnumerateDevices failed");
        return false;
    }
    
    // Open devices
    for (XnUInt32 index = 0; index < count; ++index)
    {
        res = xnUSBOpenDeviceByPath(paths[index], &m_devs[index]);
        if (res != XN_STATUS_OK) {
            xnPrintError(res, "xnUSBOpenDeviceByPath failed");
            return false;
        }
    }
    
    m_num = count;
    XnUChar buf[1]; // output buffer
    
    // Init motors
    for (XnUInt32 index = 0; index < m_num; ++index)
    {
        /*res = xnUSBSendControl(m_devs[index], (XnUSBControlType) 0xc0, 0x10, 0x00, 0x00, buf, sizeof(buf), 0);
        if (res != XN_STATUS_OK) {
            xnPrintError(res, "xnUSBSendControl failed");
            Close();
            return false;
        }*/
        
        res = xnUSBSendControl(m_devs[index], XN_USB_CONTROL_TYPE_VENDOR, 0x06, 0x01, 0x00, NULL, 0, 0);
        if (res != XN_STATUS_OK) {
            xnPrintError(res, "xnUSBSendControl failed");
            Close();
            return false;
        }
    }
    
    m_isOpen = true;
    
    return true;
}

void KinectMotors::Close()
{
    if (m_isOpen) {
        for (XnUInt32 index = 0; index < m_num; ++index) {
            xnUSBCloseDevice(m_devs[index]);
        }
        m_isOpen = false;
    }
}

bool KinectMotors::Move(int angle)
{
    XnStatus res;
    
    // Send move control requests
    for (XnUInt32 index = 0; index < m_num; ++index)
    {
        res = xnUSBSendControl(m_devs[index], XN_USB_CONTROL_TYPE_VENDOR, 0x31, angle, 0x00, NULL, 0, 0);

        if (res != XN_STATUS_OK)
        {
            xnPrintError(res, "xnUSBSendControl failed");
            return false;
        }
    }
    return true;
}

int main(int argc, char *argv[])
{
    KinectMotors motors;
    int kinect_angle = 0;
	int times_moving_kinect = 0;
	
    if (!motors.Open()) // Open motor devices
        return 1;
	
	do
	{
		motors.Move(kinect_angle);
		pause_();
		cout << "\nPlease enter angle [+/- ";
		cout << KINECT_ANGLE_RANGE;
		cout << " degree] : ";
		cin >> kinect_angle;
		
	} while(-KINECT_ANGLE_RANGE < kinect_angle && kinect_angle < KINECT_ANGLE_RANGE && times_moving_kinect++ < MAX_ATTEMPS);
	
	if(times_moving_kinect > MAX_ATTEMPS)
	{
		cout << "\nWarning!! : Kinect tilt motor is not designed for constant or repetitive movement, "
			<< "you should tilt the Kinect as few times as possible"
			<< ", please let it rest for 1 min\n\n";
	}
	else
	{
		cout << "\nValue not in range, program ended\n";
	}
	
    return 0;
}