#include <stddef.h>
#include <ctype.h>
#include "ProtocolParser.h"

typedef enum _PARSER_STATE_T {
    PARSER_LOOKING_FOR_START = 0,
    PARSER_LOOKING_FOR_CMD,
    PARSER_LOOKING_FOR_LEN,
    PARSER_LOOKING_FOR_DATA,
    PARSER_LOOKING_FOR_END,
} PARSER_STATE_T;

static PARSER_STATE_T _state = PARSER_LOOKING_FOR_START;

static char _buffer[PROTOCOL_PARSER_BUFFER_LENGTH_MAX];
static unsigned int _index = 0;
static unsigned int _remainingDataChars = 0;

char* ProtocolParser_AddChar (char NewChar)
{
    if (NewChar == '[')
    {
        _buffer[0] = NewChar;
        _state = PARSER_LOOKING_FOR_CMD;
        return 0;
    }

    switch (_state)
    {
    case PARSER_LOOKING_FOR_CMD:
        if (isupper (NewChar))
        {
            _buffer[1] = NewChar;
            _state = PARSER_LOOKING_FOR_LEN;
        }
        else {
            _state = PARSER_LOOKING_FOR_START;
        }
        break;
    case PARSER_LOOKING_FOR_LEN:
        if (NewChar == '0')
        {
            _buffer[2] = NewChar;
            _index = 3;
            _state = PARSER_LOOKING_FOR_END;
        }
        else if (isdigit (NewChar))
        {
            _buffer[2] = NewChar;
            _remainingDataChars = (NewChar & 0x0F) * 2;
            _index = 3;
            _state = PARSER_LOOKING_FOR_DATA;
        }
        else
        {
            _state = PARSER_LOOKING_FOR_START;
        }
        break;
    case PARSER_LOOKING_FOR_DATA:
        if (isxdigit (NewChar) != 0 && _remainingDataChars != 0)
        {
            _buffer[_index] = NewChar;
            ++_index;
            --_remainingDataChars;
            if (_remainingDataChars == 0)
            {
                _state = PARSER_LOOKING_FOR_END;
            }
        }
        else
        {
            _state = PARSER_LOOKING_FOR_START;
        }
        break;
    case PARSER_LOOKING_FOR_END:
        _state = PARSER_LOOKING_FOR_START;
        if (NewChar == ']')
        {
            _buffer[_index]     = NewChar;
            _buffer[_index + 1] = 0;
            return _buffer;
        }
        break;
    default: break;
    }

    return NULL;
}
