#pragma once

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <ButtonModuleInterface.hpp>
#include <RelayModuleInterface.hpp>

#include "BlindAccessoryInterface.hpp"

/**
 * @brief Implementation of the Blind Accessory.
 */
class BlindAccessory : public BlindAccessoryInterface {
 public:
  /**
   * @brief Constructor for BlindAccessory.
   *
   * @param motorUp Pointer to the relay module for moving the blind up.
   * @param motorDown Pointer to the relay module for moving the blind down.
   * @param buttonUp Pointer to the button module for moving the blind up.
   * @param buttonDown Pointer to the button module for moving the blind down.
   * @param timeToOpen Time to open the blind in seconds.
   * @param timeToClose Time to close the blind in seconds.
   */
  BlindAccessory(RelayModuleInterface *motorUp, RelayModuleInterface *motorDown,
                 ButtonModuleInterface *buttonUp, ButtonModuleInterface *buttonDown, uint8_t timeToOpen = 30,
                 uint8_t timeToClose = 30);

  /**
   * @brief Destructor for BlindAccessory.
   */
  ~BlindAccessory();

  /**
   * @brief Move the blind to a specific position.
   *
   * @param new_position Desired position of the blind (0-100).
   */
  void moveBlindTo(uint8_t new_position) override;

  /**
   * @brief Get the current position of the blind.
   *
   * @return uint8_t Current position of the blind (0-100).
   */
  uint8_t getCurrentPosition() override;

  /**
   * @brief Get the target position of the blind.
   *
   * @return uint8_t Target position of the blind (0-100).
   */
  uint8_t getTargetPosition() override;

  /**
   * @brief Set the callback function for reporting.
   *
   * @param cb Callback function pointer.
   * @param cb_parameter Optional parameter to be passed to the callback function.
   */
  void setReportAppCallback(CallBackReportFunction cb, AnyType *cb_parameter = nullptr) override;

  /**
   * @brief Identify the blind accessory.
   */
  void identifyYourSelf() override;

 private:
  /**
   * @brief Function to handle the button down event.
   *
   * @param self Pointer to the BlindAccessory object.
   */
  static void buttonDownFunction(void *self);

  /**
   * @brief Function to handle the button up event.
   *
   * @param self Pointer to the BlindAccessory object.
   */
  static void buttonUpFunction(void *self);

  /**
   * @brief Start moving the blind up.
   */
  void startMoveUp();

  /**
   * @brief Start moving the blind down.
   */
  void startMoveDown();

  /**
   * @brief Stop moving the blind.
   */
  void stopMove();

  /**
   * @brief Task to move the blind to a specific position.
   *
   * @param self Pointer to the BlindAccessory object.
   */
  static void moveBlindToTargetTask(void *self);

  /**
   * @brief Check if the blind has reached the target position.
   *
   * @param movingUp Boolean indicating if the blind is moving up.
   * @return true if the target position is reached, false otherwise.
   */
  bool targetPositionReached(bool movingUp);

  RelayModuleInterface *m_motorUp;      ///< Pointer to the relay module for moving the blind up.
  RelayModuleInterface *m_motorDown;    ///< Pointer to the relay module for moving the blind down.
  ButtonModuleInterface *m_buttonUp;    ///< Pointer to the button module for moving the blind up.
  ButtonModuleInterface *m_buttonDown;  ///< Pointer to the button module for moving the blind down.
  uint8_t m_timeToOpen;                 ///< Time to open the blind in seconds.
  uint8_t m_timeToClose;                ///< Time to close the blind in seconds.
  uint8_t m_blindPosition;              ///< Current position of the blind. 0-100.
  uint8_t m_targetPosition;             ///< Target position of the blind. 0-100.
  TaskHandle_t m_moveBlindTaskHandle;   ///< Task handle for the moveBlindToTask.

  CallBackReportFunction m_reportAttributesCallback;  ///< Callback function for reporting attributes.
  AnyType *m_reportAttributesCallbackParameter;       ///< Parameter to be passed to the callback function.
};