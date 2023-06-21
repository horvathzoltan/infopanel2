#ifndef LIBCECHELPER_H
#define LIBCECHELPER_H

#ifdef LIBCEC
#include <libcec/cec.h>

using namespace CEC;

class LibCECHelper
{    
public:
        libcec_configuration  _g_config;
        void Init();
        void ListDevices(ICECAdapter *parser);
};
#endif

#endif // LIBCECHELPER_H
