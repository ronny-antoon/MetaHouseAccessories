#pragma once

/**
 * @brief Base class interface for accessories.
 */
class BaseAccessoryInterface {
 public:
  /**
   * @brief Callback function type for reporting.
   */
  using CallBackReportFunction = void (*)(void *);

  /**
   * @brief Placeholder for any type.
   */
  using AnyType = void;

  /**
   * @brief Virtual destructor for the base accessory interface.
   */
  virtual ~BaseAccessoryInterface() = default;

  /**
   * @brief Set the callback function for reporting.
   *
   * @param cb Callback function pointer.
   * @param cb_parameter Optional parameter to be passed to the callback function.
   */
  virtual void setReportAppCallback(CallBackReportFunction cb, AnyType *cb_parameter = nullptr) = 0;

  /**
   * @brief Method to identify the accessory.
   */
  virtual void identifyYourSelf() = 0;
};