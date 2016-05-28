/**
 * @filename ProtocolParser.h
 *
 * @brief Detects incoming Protocol frames
 *
 * This parser was initially developed as an example in the Unity class on
 * Udemy.com.
 * @see https://www.udemy.com/unit-testing-and-other-embedded-software-catalysts
 *
 * Frames take the form: [CNDD...], where
 *   '[' and ']' are literal square bracket characters
 *   C is a single, upper case, ASCII character representing the frame command
 *   N is an ascii number ('0' through '9') that indicates how many additional
 *     data bytes follow in the frame
 *   DD... is 0 or more ASCII character pairs which represent a hexadecimal byte
 */
#ifndef PROTOCOL_PARSER_H
#define PROTOCOL_PARSER_H

#define PROTOCOL_PARSER_BUFFER_LENGTH_MAX  (23) /**< Assumes max data bytes of 9 and space for NULL */

/**
 * @brief Adds a character to the parser
 *
 * @returns A pointer to a valid frame if one was detected, otherwise NULL
 */
char* ProtocolParser_AddChar (char NewChar);

#endif /* PROTOCOL_PARSER_H */
