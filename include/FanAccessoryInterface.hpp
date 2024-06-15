#pragma once

#include "BaseAccessoryInterface.hpp"

/**
 * @brief Interface for Fan Accessories.
 */
class FanAccessoryInterface : public BaseAccessoryInterface {
 public:
  /**
   * @brief Virtual destructor for the fan accessory interface.
   */
  ~FanAccessoryInterface() = default;

  /**
   * @brief Set the power state of the fan.
   *
   * @param power Power state to set (true for on, false for off).
   */
  virtual void setPower(bool power) = 0;

  /**
   * @brief Get the current power state of the fan.
   *
   * @return True if the fan is on, false otherwise.
   */
  virtual bool getPower() = 0;

  /**
   * @brief Set the callback function for reporting.
   *
   * @param cb Callback function pointer.
   * @param cb_parameter Optional parameter to be passed to the callback function.
   */
  virtual void setReportAppCallback(CallBackReportFunction cb, AnyType *cb_parameter = nullptr) override = 0;

  /**
   * @brief Method to identify the fan accessory.
   */
  virtual void identifyYourSelf() override = 0;
};