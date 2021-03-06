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
    ProtocolModel_GetResponse_IgnoreAndReturn(NULL);

    ProtocolConductor_Run();
}

void test_Run_ShouldNot_PassFrameToModel_When_FrameIsNotReady(void)
{
    ProtocolHardware_GetFrame_ExpectAndReturn(NULL);
    ProtocolModel_GetResponse_IgnoreAndReturn(NULL);

    ProtocolConductor_Run();
}

void test_Run_Should_SendResponseToHardware_When_ModelHasResponse(void)
{
    ProtocolHardware_GetFrame_ExpectAndReturn(NULL);
    ProtocolModel_GetResponse_ExpectAndReturn("[S100]");
    ProtocolHardware_SendResponse_Expect("[S100]");

    ProtocolConductor_Run();
}

void test_Run_ShouldNot_SendResponseToHardware_When_ModelDoesNotHaveResponse(void)
{
    ProtocolHardware_GetFrame_ExpectAndReturn(NULL);
    ProtocolModel_GetResponse_ExpectAndReturn(NULL);

    ProtocolConductor_Run();
}
