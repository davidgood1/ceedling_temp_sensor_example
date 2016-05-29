#include <string.h>
#include "Types.h"
#include "ProtocolModel.h"
#include "ProtocolParser.h"

static char _frame[PROTOCOL_BUFFER_LENGTH_MAX];
static uint8 _responseReady;

void ProtocolModel_Init(void)
{
    memset(_frame, 0, sizeof _frame);
    _responseReady = 0;
}

void ProtocolModel_ReceiveFrame(char *frame)
{
    if (frame == NULL)
    {
        _responseReady = 0;
    }
    else {
        strcpy(_frame, "?");
        _responseReady = 1;
    }
}

char* ProtocolModel_GetResponse(void)
{
    if (_responseReady == 0)
        return NULL;

    _responseReady = 0;
    return _frame;
}
