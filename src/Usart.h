/**
 * @filename Usart.h
 *
 * @brief Hardware abstracted USART driver
 *
 * The USART module module is structured using the Driver-(Interrupt)-Hardware
 * D(I)H design pattern.
 */

/**
 * @brief Initializes the driver and underlying hardware
 */
void Usart_Init(void);

/**
 * @brief Gets a character from the Usart receive buffer
 *
 * @returns A character if there is one, otherwise 0
 *
 * @note If binary character 0 is a valid character for the application,
 * it must call Usart_IsEmpty first to check if there are characters to get.
 * If IsEmpty returns FALSE and this function returns 0, it is actually valid
 * data, not buffer empty.
 */
char Usart_GetChar(void);
