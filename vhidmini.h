/*++
    vhidmini.h
--*/

//应该用得着
#ifdef _KERNEL_MODE
#include <ntddk.h>
#else
#include <windows.h>
#endif

#include <wdf.h>

#include <hidport.h>  // located in $(DDK_INC_PATH)/wdm

#include "common.h"

typedef UCHAR HID_REPORT_DESCRIPTOR, *PHID_REPORT_DESCRIPTOR;

DRIVER_INITIALIZE                   DriverEntry;
EVT_WDF_DRIVER_DEVICE_ADD           EvtDeviceAdd;
EVT_WDF_TIMER                       EvtTimerFunc;

//-------------------------------------------
//定义DEVICE_CONTEXT及其...
//-------------------------------------------
typedef struct _DEVICE_CONTEXT
{
    WDFDEVICE               Device;
    WDFQUEUE                DefaultQueue; //第一个queue
    WDFQUEUE                ManualQueue;  //第二个queue
    HID_DEVICE_ATTRIBUTES   HidDeviceAttributes;
    BYTE                    DeviceData;
    HID_DESCRIPTOR          HidDescriptor;
    PHID_REPORT_DESCRIPTOR  ReportDescriptor;
    BOOLEAN                 ReadReportDescFromRegistry;

} DEVICE_CONTEXT, *PDEVICE_CONTEXT;

//上面结构后面必须有这个宏
WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(DEVICE_CONTEXT, GetDeviceContext);

//-------------------------------------------
//定义QUEUE_CONTEXT及其...
//-------------------------------------------
typedef struct _QUEUE_CONTEXT
{
    WDFQUEUE                Queue;
    PDEVICE_CONTEXT         DeviceContext;
    UCHAR                   OutputReport;

} QUEUE_CONTEXT, *PQUEUE_CONTEXT;

WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(QUEUE_CONTEXT, GetQueueContext);

//-------------------------------------------
//定义MANUAL_QUEUE_CONTEXT及其...
//-------------------------------------------
typedef struct _MANUAL_QUEUE_CONTEXT
{
    WDFQUEUE                Queue;
    PDEVICE_CONTEXT         DeviceContext;
    WDFTIMER                Timer;

} MANUAL_QUEUE_CONTEXT, *PMANUAL_QUEUE_CONTEXT;

WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(MANUAL_QUEUE_CONTEXT, GetManualQueueContext);

//函数declare...

QueueCreate(...
ManualQueueCreate(...
ReadReport(...
WriteReport(...
GetFeature(...
SetFeature(...
GetInputReport(...
SetOutputReport(...
GetString(...
GetIndexedString(...
GetStringId(...
RequestCopyFromBuffer(...
RequestGetHidXferPacket_ToReadFromDevice(...
RequestGetHidXferPacket_ToWriteToDevice(...
CheckRegistryForDescriptor(...
ReadDescriptorFromRegistry(...

//
// Misc definitions
//
#define CONTROL_FEATURE_REPORT_ID   0x01

//
// These are the device attributes returned by the mini driver in response
// to IOCTL_HID_GET_DEVICE_ATTRIBUTES.
//
#define HIDMINI_PID             0xFEED
#define HIDMINI_VID             0xDEED
#define HIDMINI_VERSION         0x0101
