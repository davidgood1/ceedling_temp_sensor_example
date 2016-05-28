#include "unity.h"
#include "Types.h"
#include "ProtocolConductor.h"
#include "MockProtocolHardware.h"
#include "MockProtocolModel.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_Init_Should_CallProtocolInitAndHardwareInit(void)
{
    ProtocolHardware_Init_Expect();
    ProtocolModel_Init_Expect();

    ProtocolConductor_Init();
}
