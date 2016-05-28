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
