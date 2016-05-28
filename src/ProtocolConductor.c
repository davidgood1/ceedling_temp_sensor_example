#include "Types.h"
#include "ProtocolConductor.h"
#include "ProtocolHardware.h"
#include "ProtocolModel.h"

void ProtocolConductor_Init(void)
{
    ProtocolHardware_Init();
    ProtocolModel_Init();
}

void ProtocolConductor_Run(void)
{
    char *frame;
    frame = ProtocolHardware_GetFrame();
    if (frame != NULL)
    {
        ProtocolModel_ReceiveFrame(frame);
    }

    frame = ProtocolModel_GetResponse();
    if (frame != NULL)
    {
        ProtocolHardware_SendResponse(frame);
    }
}
