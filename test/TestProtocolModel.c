#include <string.h>
#include <stdint.h>
#include "unity.h"
#include "Types.h"
#include "ProtocolModel.h"
#include "MockTemperatureFilter.h"

void setUp(void)
{
    ProtocolModel_Init();
}

void tearDown(void)
{
}

void test_GetResponse_Should_ReturnNull_When_NoResponseReady(void)
{
    TEST_ASSERT_NULL(ProtocolModel_GetResponse());
}

void test_ReceiveFrame_Should_RespondQuestionMark_When_CommandUnrecognized(void)
{
    ProtocolModel_ReceiveFrame("[X0]");

    TEST_ASSERT_EQUAL_STRING("?", ProtocolModel_GetResponse());
}

void test_ReceiveFrame_ShouldNot_HaveAnyResponse_When_FrameIsNull(void)
{
    ProtocolModel_ReceiveFrame(NULL);

    TEST_ASSERT_NULL(ProtocolModel_GetResponse());
}

void test_GetResponse_Should_RespondNull_After_GetResponse(void)
{
    ProtocolModel_ReceiveFrame("[X0]");

    TEST_ASSERT_EQUAL_STRING("?", ProtocolModel_GetResponse());
    TEST_ASSERT_NULL(ProtocolModel_GetResponse());
}

void test_ReceiveFrame_Should_RespondOkToStatusCommand(void)
{
    ProtocolModel_ReceiveFrame("[S0]");

    TEST_ASSERT_EQUAL_STRING("[S100]", ProtocolModel_GetResponse());
}

void test_StrToAsciiCodes_Should_ReturnCorrectString_When_LessThanTenBytes(void)
{
    TEST_ASSERT_EQUAL_STRING("32372E35", ProtocolModel_StrToHexStr("27.5"));
    TEST_ASSERT_EQUAL_STRING("41426324", ProtocolModel_StrToHexStr("ABc$"));
    TEST_ASSERT_EQUAL_STRING("011B7FCD", ProtocolModel_StrToHexStr("\x01\x1B\x7F\xCD"));
    TEST_ASSERT_EQUAL_STRING("313233343536373839", ProtocolModel_StrToHexStr("123456789"));
}

void test_StrToAsciiCodes_Should_ReturnNull_When_MoreThanTenBytes(void)
{
    TEST_ASSERT_NULL(ProtocolModel_StrToHexStr("123456789A"));
}

void test_StrToAsciiCodes_Should_ReturnNull_When_InputStringIsNull(void)
{
    TEST_ASSERT_NULL(ProtocolModel_StrToHexStr(NULL));
}

void test_StrToAsciiCodes_Should_ReturnCorrectString_When_StrangeInputValues(void)
{
    TEST_ASSERT_EQUAL_STRING("011B7FCD", ProtocolModel_StrToHexStr("\x01\x1B\x7F\xCD"));
}

void test_GetTemperatureCommand_Should_ReturnCurrentTemperature_When_TemperatureIsValid(void)
{
    TemperatureFilter_GetTemperatureInCelcius_ExpectAndReturn(27.5);
    ProtocolModel_ReceiveFrame("[T0]");

    TEST_ASSERT_EQUAL_STRING("[T432372E35]", ProtocolModel_GetResponse());

    TemperatureFilter_GetTemperatureInCelcius_ExpectAndReturn(0.0);
    ProtocolModel_ReceiveFrame("[T0]");

    TEST_ASSERT_EQUAL_STRING("[T3302E30]", ProtocolModel_GetResponse());

    TemperatureFilter_GetTemperatureInCelcius_ExpectAndReturn(100.0);
    ProtocolModel_ReceiveFrame("[T0]");

    TEST_ASSERT_EQUAL_STRING("[T53130302E30]", ProtocolModel_GetResponse());
}

void test_GetTemperatureCommand_Should_ReturnErrorFrame_When_TemperatureSensorFailed(void)
{
    TemperatureFilter_GetTemperatureInCelcius_ExpectAndReturn(-INFINITY);
    ProtocolModel_ReceiveFrame("[T0]");

    TEST_ASSERT_EQUAL_STRING("[T1FF]", ProtocolModel_GetResponse());
}
