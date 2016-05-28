#include "Types.h"
#include "ProtocolHardware.h"
#include "Usart.h"
#include "ProtocolParser.h"

void ProtocolHardware_Init(void)
{
    Usart_Init();
}

char* ProtocolHardware_GetFrame(void)
{
    char ch = Usart_GetChar();
    if (ch != 0)
    {
        return ProtocolParser_AddChar(ch);
    }

    return NULL;
}
