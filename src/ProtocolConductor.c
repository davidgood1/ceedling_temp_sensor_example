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

}
