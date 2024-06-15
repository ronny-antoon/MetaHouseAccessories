#pragma once

#include "BaseAccessoryInterface.hpp"

/**
 * @brief Interface for Light Accessories.
 */
class LightAccessoryInterface : public BaseAccessoryInterface {
 public:
  /**
   * @brief Virtual destructor for the light accessory interface.
   */
  ~LightAccessoryInterface() = default;

  /**
   * @brief Set the power state of the light.
   *
   * @param power Power state to set (true for on, false for off).
   */
  virtual void setPower(bool power) = 0;

  /**
   * @brief Get the current power state of the light.
   *
   * @return True if the light is on, false otherwise.
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
   * @brief Method to identify the light accessory.
   */
  virtual void identifyYourSelf() override = 0;
};