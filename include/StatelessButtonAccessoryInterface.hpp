#pragma once

#include "BaseAccessoryInterface.hpp"

/**
 * @brief Interface for Stateless Button Accessories.
 */
class StatelessButtonAccessoryInterface : public BaseAccessoryInterface {
 public:
  /**
   * @brief Enum to represent the type of button press.
   */
  enum PressType {
    SinglePress = 1,  ///< Represents a single press event.
    DoublePress = 2,  ///< Represents a double press event.
    LongPress = 3     ///< Represents a long press event.
  };
  /**
   * @brief Virtual destructor for the stateless button accessory interface.
   */
  ~StatelessButtonAccessoryInterface() = default;

  /**
   * @brief Set the callback function for reporting.
   *
   * @param cb Callback function pointer.
   * @param cb_parameter Optional parameter to be passed to the callback function.
   */
  virtual void setReportAppCallback(CallBackReportFunction cb, AnyType *cb_parameter = nullptr) override = 0;

  /**
   * @brief Method to identify the stateless button accessory.
   */
  virtual void identifyYourSelf() override = 0;

  /**
   * @brief Get Last Press Type
   *
   * @return PressType
   */
  virtual PressType getLastPressType() = 0;
};