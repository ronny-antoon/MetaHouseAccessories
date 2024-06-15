#pragma once

#include "BaseAccessoryInterface.hpp"

/**
 * @brief Interface for Blind Accessories.
 */
class BlindAccessoryInterface : public BaseAccessoryInterface {
 public:
  /**
   * @brief Virtual destructor for the BlindAccessoryInterface.
   */
  ~BlindAccessoryInterface() = default;

  /**
   * @brief Move the blind to a specific position.
   *
   * @param new_position Desired position of the blind (0-100).
   */
  virtual void moveBlindTo(uint8_t new_position) = 0;

  /**
   * @brief Get the current position of the blind.
   *
   * @return uint8_t Current position of the blind (0-100).
   */
  virtual uint8_t getCurrentPosition() = 0;

  /**
   * @brief Get the target position of the blind.
   *
   * @return uint8_t Target position of the blind (0-100).
   */
  virtual uint8_t getTargetPosition() = 0;

  /**
   * @brief Set the callback function for reporting.
   *
   * @param cb Callback function pointer.
   * @param cb_parameter Optional parameter to be passed to the callback function.
   */
  virtual void setReportAppCallback(CallBackReportFunction cb, AnyType *cb_parameter = nullptr) override = 0;

  /**
   * @brief Identify the blind accessory.
   */
  virtual void identifyYourSelf() override = 0;
};