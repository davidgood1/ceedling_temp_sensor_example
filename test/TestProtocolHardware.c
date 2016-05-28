#include "unity.h"
#include "ProtocolHardware.h"
#include "MockUsart.h"
#include "MockProtocolParser.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_Init_Should_CallUsartInit(void)
{
    Usart_Init_Expect();

    ProtocolHardware_Init();
}

void test_GetFrame_Should_ReturnNull_When_UsartHasNoCharacters(void)
{
    Usart_GetChar_ExpectAndReturn(0);

    TEST_ASSERT_NULL(ProtocolHardware_GetFrame());
}

void test_GetFrame_Should_FeedCharactersToParser_When_UsartHasCharacters(void)
{
    Usart_GetChar_ExpectAndReturn('[');
    ProtocolParser_AddChar_ExpectAndReturn('[', NULL);

    TEST_ASSERT_NULL(ProtocolHardware_GetFrame());
}

void test_GetFrame_Should_ReturnFrame_When_ParserDetectsFrame(void)
{
    Usart_GetChar_ExpectAndReturn(']');
    ProtocolParser_AddChar_ExpectAndReturn(']', "[S0]");

    TEST_ASSERT_EQUAL_STRING("[S0]", ProtocolHardware_GetFrame());
}
