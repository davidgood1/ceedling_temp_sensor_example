#include "unity.h"
#include "ProtocolParser.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void insert_valid_minimal_packet (char cmd, char *packet)
{
    TEST_ASSERT_NULL (ProtocolParser_AddChar ('['));
    TEST_ASSERT_NULL (ProtocolParser_AddChar (cmd));
    TEST_ASSERT_NULL (ProtocolParser_AddChar ('0'));
    TEST_ASSERT_EQUAL_STRING (packet, ProtocolParser_AddChar (']'));
}

void insert_valid_data_packet (char cmd, char dataNum, char *dataStr, char *packet)
{
    TEST_ASSERT_NULL (ProtocolParser_AddChar ('['));
    TEST_ASSERT_NULL (ProtocolParser_AddChar (cmd));
    TEST_ASSERT_NULL (ProtocolParser_AddChar (dataNum));
    while (*dataStr != 0) {
        TEST_ASSERT_NULL (ProtocolParser_AddChar (*dataStr++));
    }
    TEST_ASSERT_EQUAL_STRING (packet, ProtocolParser_AddChar (']'));
}

void test_ProtocolParser_AddChar_should_HandleValidPacketWithNoData (void)
{
    insert_valid_minimal_packet ('A', "[A0]");
}

void test_ProtocolParser_AddChar_should_HandleBackToBackValidPackets (void)
{
    insert_valid_minimal_packet ('A', "[A0]");
    insert_valid_minimal_packet ('Z', "[Z0]");
    insert_valid_minimal_packet ('W', "[W0]");
}

void test_ProtocolParser_AddChar_should_IgnoreInvalidStartCharacters (void)
{
    TEST_ASSERT_NULL (ProtocolParser_AddChar ('9'));
    insert_valid_minimal_packet ('A', "[A0]");

    TEST_ASSERT_NULL (ProtocolParser_AddChar (']'));
    insert_valid_minimal_packet ('B', "[B0]");

    TEST_ASSERT_NULL (ProtocolParser_AddChar ('A'));
    insert_valid_minimal_packet ('C', "[C0]");
}

void test_ProtocolParser_AddChar_should_DiscardIncompletePacketsWhenStartCharacter (void)
{
    TEST_ASSERT_NULL (ProtocolParser_AddChar ('['));
    TEST_ASSERT_NULL (ProtocolParser_AddChar ('A'));
    insert_valid_minimal_packet ('R', "[R0]");

    TEST_ASSERT_NULL (ProtocolParser_AddChar ('['));
    TEST_ASSERT_NULL (ProtocolParser_AddChar ('B'));
    TEST_ASSERT_NULL (ProtocolParser_AddChar ('2'));
    TEST_ASSERT_NULL (ProtocolParser_AddChar ('1'));
    insert_valid_minimal_packet ('R', "[R0]");
}

void test_ProtocolParser_AddChar_should_IgnoreInvalidCommandCharacters (void)
{
    TEST_ASSERT_NULL (ProtocolParser_AddChar ('['));
    TEST_ASSERT_NULL (ProtocolParser_AddChar ('a'));
    insert_valid_minimal_packet ('R', "[R0]");

    insert_valid_minimal_packet ('z', NULL);
    insert_valid_minimal_packet ('F', "[F0]");

    insert_valid_minimal_packet (']', NULL);
    insert_valid_minimal_packet ('G', "[G0]");

    insert_valid_minimal_packet ('@', NULL);
    insert_valid_minimal_packet ('H', "[H0]");
}

void test_ProtocolParser_AddChar_should_HandleValidPacketWithDataCharacters (void)
{
    insert_valid_data_packet ('A', '1', "00", "[A100]");
    insert_valid_data_packet ('X', '5', "1122334455", "[X51122334455]");
    insert_valid_data_packet ('Z', '9', "FFEEDDCCAA99887766", "[Z9FFEEDDCCAA99887766]");
    insert_valid_data_packet ('H', '4', "1a2b3c4d", "[H41a2b3c4d]");
}

void test_ProtocolParser_AddChar_should_RejectInvalidDataCharacters (void)
{
    insert_valid_data_packet ('A', '1', "1g", NULL);
    insert_valid_data_packet ('B', '2', "5G", NULL);
    insert_valid_data_packet ('Z', '2', "5@", NULL);
}

void test_ProtocolParser_AddChar_should_RejectPacketsWithNotEnoughDataCharacters (void)
{
    insert_valid_data_packet ('A', '1', "", NULL);
    insert_valid_data_packet ('B', '3', "1122", NULL);
    insert_valid_data_packet ('B', '3', "11223", NULL);
}

void test_ProtocolParser_AddChar_should_RejectPacketsWithTooManyDataCharacters (void)
{
    insert_valid_data_packet ('A', '1', "3344", NULL);
    insert_valid_data_packet ('B', '3', "AABBCCD", NULL);
}

void test_ProtocolParser_AddChar_should_RejectInvalidEndCharacters (void)
{
    TEST_ASSERT_NULL (ProtocolParser_AddChar ('['));
    TEST_ASSERT_NULL (ProtocolParser_AddChar ('A'));
    TEST_ASSERT_NULL (ProtocolParser_AddChar ('0'));
    TEST_ASSERT_NULL (ProtocolParser_AddChar ('?'));
    insert_valid_minimal_packet ('Z', "[Z0]");

    TEST_ASSERT_NULL (ProtocolParser_AddChar ('['));
    TEST_ASSERT_NULL (ProtocolParser_AddChar ('B'));
    TEST_ASSERT_NULL (ProtocolParser_AddChar ('1'));
    TEST_ASSERT_NULL (ProtocolParser_AddChar ('A'));
    TEST_ASSERT_NULL (ProtocolParser_AddChar ('B'));
    TEST_ASSERT_NULL (ProtocolParser_AddChar ('C'));
    insert_valid_minimal_packet ('X', "[X0]");
}
