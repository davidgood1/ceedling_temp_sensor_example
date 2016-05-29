#include <string.h>
#include <stdio.h>
#include "Types.h"
#include "ProtocolModel.h"
#include "ProtocolParser.h"
#include "TemperatureFilter.h"

static char _frame[PROTOCOL_BUFFER_LENGTH_MAX];
static uint8 _responseReady;
static char _hexStr[(9 * 2) + 1];

void ProtocolModel_Init(void)
{
    memset(_frame, 0, sizeof _frame);
    _responseReady = 0;
}

void ProtocolModel_ReceiveFrame(char *frame)
{
    char cmd;
    float temperature;
    if (frame == NULL)
    {
        _responseReady = 0;
        return;
    }

    _responseReady = 1;
    cmd = *(frame + 1);
    switch (cmd)
    {
    case 'S':
        strcpy(_frame, "[S100]");
        break;
    case 'T':
        temperature = TemperatureFilter_GetTemperatureInCelcius();
        if (temperature == -INFINITY)
        {
            strcpy(_frame, "[T1FF]");
        }
        else
        {
            uint8 len;
            sprintf(_frame, "%.1f", temperature);
            len = strlen(_frame);
            sprintf(_frame, "[T%u%s]", len, ProtocolModel_StrToHexStr(_frame));
        }
        break;
    default:
        strcpy(_frame, "?");
    }
}

char* ProtocolModel_GetResponse(void)
{
    if (_responseReady == 0)
        return NULL;

    _responseReady = 0;
    return _frame;
}

char *ProtocolModel_StrToHexStr(char *str)
{
    char *hex = _hexStr;

    if (str == NULL || strlen(str) > 9)
    {
        return NULL;
    }

    while (*str != 0)
    {
        sprintf(hex, "%02X", (uint8)(*str));
        hex += 2;
        ++str;
    }
    return _hexStr;
}
