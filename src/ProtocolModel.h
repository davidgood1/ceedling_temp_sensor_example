/**
 * @filename ProtocolModel.h
 *
 * @brief Protocol module Model interface functions
 *
 * The Protocol module is structured using the Model-Controller-Hardware (MCH)
 * design pattern.
 *
 * The Model interface is responsible for accepting and validating incoming
 * Protocol frames and sending the appropriate reply.
 *
 * The protocol has the following bus rules:
 *
 * 1. The device never initiates communication.
 * 2. Frames are based on the simple Parser example built in the Udemy class.
 *    @see https://www.udemy.com/unit-testing-and-other-embedded-software-catalysts
 * 3. Every command has a response.
 *    The general response form is: [XNDD...]
 *    where X is the original command letter, N is the number of data bytes in
 *    the response, and DD is the actual response data.
 * 4. The response to Frames which are valid but contain unknown commands or
 *    invalid data is a single ASCII char '?'.
 *
 * Protocol Commands:
 *
 * T - Get current temperature reading
 *     No command data
 *     Response data is the filtered temperature value in Celsius as an ASCII
 *     encoded string of the form "%.1f"
 *     Example: A response frame with the temperature of 27.5 C = [T432372e35]
 *
 * V - Get the firmware version
 *     No command data
 *     Response data is the current version number in hex where the
 *     form is xx.yy.zz
 *     Example: Firmware Version 02.01.127 = [V302017F]
 *
 * S - Get status code
 *     No command data
 *     Response data is a single byte status code in hex from
 *     the @ProtocolStatusCodeEnum definitions.
 *     Example: Status Good = [S100]
 */
#ifndef PROTOCOL_MODEL_H
#define PROTOCOL_MODEL_H

/**
 * @brief Initializes the Model
 */
void ProtocolModel_Init(void);

/**
 * @brief Accepts incoming frames for processing by the Model
 *
 * @note This function does not hold the frame pointer and is finished with the
 * frame once it returns.
 */
void ProtocolModel_ReceiveFrame(char *frame);

/**
 * @brief Gets a response from the Model
 *
 * @returns A pointer to a response frame a response is ready, NULL otherwise
 */
char* ProtocolModel_GetResponse(void);

#endif  /* PROTOCOL_MODEL_H */
