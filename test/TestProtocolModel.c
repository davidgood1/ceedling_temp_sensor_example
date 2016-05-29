#include <string.h>
#include <stdint.h>
#include "unity.h"
#include "Types.h"
#include "ProtocolModel.h"

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
