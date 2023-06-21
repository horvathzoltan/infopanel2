#ifdef LIBCEC
#include <libcec/cec.h>
#include <libcec/cecc.h>
#include <libcec/cecloader.h>

#include <QString>

#include "helpers/logger.h"
#include "libcechelper.h"

void LibCECHelper::Init()
{
    cec_device_type_list list;
    list.Clear();

    //list.Add(CEC_DEVICE_TYPE_PLAYBACK_DEVICE);
    list.Add(CEC::CEC_DEVICE_TYPE_TV);
    ICECAdapter *adapter = LibCecInitialise(&_g_config);

    //this->ListDevices(adapter);
}

// https://github.com/Pulse-Eight/libcec/blob/master/src/cec-client/cec-client.cpp#L250
void LibCECHelper::ListDevices(ICECAdapter *parser)
{


    cec_adapter_descriptor devices[10];
    QString strMessage = QString("libCEC version: %1, %2").arg(
        parser->VersionToString(_g_config.serverVersion).c_str(),
        parser->GetLibInfo());
    zInfo(strMessage);

    int8_t iDevicesFound = parser->DetectAdapters(devices, 10, NULL);
    if (iDevicesFound <= 0)
    {
        zInfo("Found devices: NONE");
    }
    else
    {
        QString a = QString("Found devices: %1\n").arg(iDevicesFound);
        zInfo(a);

        for (int8_t iDevicePtr = 0; iDevicePtr < iDevicesFound; iDevicePtr++)
        {
            QString result;
            //QTextStream s(&result);

            result += QString("device:              %1").arg(iDevicePtr + 1);
            result += QString("\ncom port:            %1").arg(devices[iDevicePtr].strComName);
            result += QString("\nvendor id:           %1").arg(devices[iDevicePtr].iVendorId);//04x
            result += QString("\nproduct id:          %1").arg(devices[iDevicePtr].iProductId);//04x
            result += QString("\nfirmware version:    %1").arg(devices[iDevicePtr].iFirmwareVersion);
            zInfo(result);

            if (devices[iDevicePtr].iFirmwareBuildDate != CEC_FW_BUILD_UNKNOWN)
            {
                time_t buildTime = (time_t)devices[iDevicePtr].iFirmwareBuildDate;
                QString strDeviceInfo;
                strDeviceInfo = QString("firmware build date: %1").arg(asctime(gmtime(&buildTime)));
                //                strDeviceInfo = QString::Left(strDeviceInfo, strDeviceInfo.length() > 1 ? (unsigned)(strDeviceInfo.length() - 1) : 0); // strip \n added by asctime
                strDeviceInfo.append(" +0000");
                zInfo(strDeviceInfo);
            }

            if (devices[iDevicePtr].adapterType != ADAPTERTYPE_UNKNOWN)
            {
                QString a1 = QString("type:                %1").arg(parser->ToString(devices[iDevicePtr].adapterType));
                zInfo(a1);
            }

            zInfo(QString("\n"));
        }
    }
}





#endif
