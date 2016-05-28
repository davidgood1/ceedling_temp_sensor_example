/**
 * @filename ProtocolHardware.h
 *
 * @brief Protocol module Hardware interface functions
 *
 * The Protocol module is structured using the Model-Controller-Hardware (MCH)
 * design pattern.
 *
 * The Hardware interface is responsible for getting and sending Protocol frames
 * through the USART.
 */

/**
 * @brief Initializes the Protocol Hardware
 */
void ProtocolHardware_Init(void);

/**
 * @brief Gets a received frame from the underlying hardware
 *
 * @returns A pointer to a complete frame if a frame is ready, NULL otherwise
 */
char* ProtocolHardware_GetFrame(void);