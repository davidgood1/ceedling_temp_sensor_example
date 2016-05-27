/**
 * @filename ProtocolConductor.h
 *
 * @brief Protocol module Conductor interface functions
 *
 * The Protocol module is structured using the Model-Controller-Hardware (MCH)
 * design pattern.
 *
 * The Conductor is responsible for coordinating the activities of the Model
 * and Hardware parts of the module.  It looks for events in the Model and
 * passes them to the Hardware, and vice versa.
 */

/**
 * @brief Initializes the entire Protocol module
 */
void ProtocolConductor_Init(void);

/**
 * @brief Runs the conductor
 */
void ProtocolConductor_Run(void);
