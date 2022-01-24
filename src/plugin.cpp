#include <Windows.h>
#include <Dbt.h>

#include "plugin.hpp"

using namespace reframework;

REFrameworkPluginFunctions* functions;

bool is_device_controller(PDEV_BROADCAST_HDR hdr, WPARAM w_param)
{
    if (hdr->dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE)
    {
        PDEV_BROADCAST_DEVICEINTERFACE d_interface = (PDEV_BROADCAST_DEVICEINTERFACE)hdr;

        if (d_interface->dbcc_classguid == XUSB_INTERFACE_CLASS_GUID)
        {
            functions->log_info("[DeviceStutterFix] Event 0x%04x: Relevant device detected", w_param);
            return true;
        }
    }

    functions->log_info("[DeviceStutterFix] Event 0x%04x: No relevant device detected", w_param);

    return false;
}

bool on_message(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param)
{
    if (msg == WM_DEVICECHANGE)
    {
        switch (w_param)
        {
        case DBT_DEVICEARRIVAL:
        case DBT_DEVICEREMOVECOMPLETE:
            return is_device_controller((PDEV_BROADCAST_HDR)l_param, w_param);
        default:
            // the other cases shouldn't matter to the game
            functions->log_info("[DeviceStutterFix] Event 0x%04x: Skipping", w_param);
            return false;
        }
    }

    return true;
}

extern "C" __declspec(dllexport) void reframework_plugin_required_version(REFrameworkPluginVersion *version)
{
    version->major = REFRAMEWORK_PLUGIN_VERSION_MAJOR;
    version->minor = REFRAMEWORK_PLUGIN_VERSION_MINOR;
    version->patch = REFRAMEWORK_PLUGIN_VERSION_PATCH;
}

extern "C" __declspec(dllexport) bool reframework_plugin_initialize(const REFrameworkPluginInitializeParam *param)
{
    API::initialize(param);

    functions = (REFrameworkPluginFunctions*)param->functions;
    functions->on_message((REFOnMessageCb)on_message);

    return true;
}