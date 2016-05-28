#include "unity.h"
#include "ProtocolHardware.h"
#include "MockUsart.h"

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
