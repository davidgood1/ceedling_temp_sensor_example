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

void test_Run_Should_PassFramesToModel_When_FrameIsReady(void)
{
    ProtocolHardware_GetFrame_ExpectAndReturn("[S0]");
    ProtocolModel_ReceiveFrame_Expect("[S0]");

    ProtocolConductor_Run();
}

void test_Run_ShouldNot_PassFrameToModel_When_FrameIsNotReady(void)
{
    ProtocolHardware_GetFrame_ExpectAndReturn(NULL);

    ProtocolConductor_Run();
}
