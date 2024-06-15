#pragma once

#include "BaseAccessoryInterface.hpp"

/**
 * @brief Interface for Switch Accessories.
 */
class SwitchAccessoryInterface : public BaseAccessoryInterface {
 public:
  /**
   * @brief Virtual destructor for the switch accessory interface.
   */
  ~SwitchAccessoryInterface() = default;

  /**
   * @brief Set the power state of the switch.
   *
   * @param power Power state to set (true for on, false for off).
   */
  virtual void setPower(bool power) = 0;

  /**
   * @brief Get the current power state of the switch.
   *
   * @return True if the switch is on, false otherwise.
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
   * @brief Method to identify the switch accessory.
   */
  virtual void identifyYourSelf() override = 0;
};