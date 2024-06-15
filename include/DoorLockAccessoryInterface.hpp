#pragma once

#include "BaseAccessoryInterface.hpp"

/**
 * @brief Interface for Door Lock Accessories.
 */
class DoorLockAccessoryInterface : public BaseAccessoryInterface {
 public:
  /**
   * @brief Enum for the state of the door lock.
   */
  enum class DoorLockState { LOCKED, UNLOCKED };

  /**
   * @brief Virtual destructor for the door lock accessory interface.
   */
  ~DoorLockAccessoryInterface() = default;

  /**
   * @brief Set the lock state of the door lock.
   *
   * @param lock The state to set the door lock to.
   */
  virtual void setState(DoorLockState lock) = 0;

  /**
   * @brief Get the current lock state of the door lock.
   *
   * @return The current state of the door lock.
   */
  virtual DoorLockState getState() = 0;

  /**
   * @brief Set the callback function for reporting.
   *
   * @param cb Callback function pointer.
   * @param cb_parameter Optional parameter to be passed to the callback function.
   */
  virtual void setReportAppCallback(CallBackReportFunction cb, AnyType *cb_parameter = nullptr) override = 0;

  /**
   * @brief Method to identify the door lock accessory.
   */
  virtual void identifyYourSelf() override = 0;
};