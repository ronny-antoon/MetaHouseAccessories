#pragma once

#include <ButtonModuleInterface.hpp>
#include <RelayModuleInterface.hpp>

#include "LightAccessoryInterface.hpp"

/**
 * @brief Implementation of the Light Accessory.
 */
class LightAccessory : public LightAccessoryInterface {
 public:
  /**
   * @brief Constructor for LightAccessory.
   *
   * @param relayModule Pointer to the relay module interface.
   * @param buttonModule Pointer to the button module interface.
   */
  LightAccessory(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule);

  /**
   * @brief Destructor for LightAccessory.
   */
  ~LightAccessory();

  /**
   * @brief Set the power state of the light.
   *
   * @param power Power state to set (true for on, false for off).
   */
  void setPower(bool power);

  /**
   * @brief Get the current power state of the light.
   *
   * @return True if the light is on, false otherwise.
   */
  bool getPower();

  /**
   * @brief Set the callback function for reporting.
   *
   * @param cb Callback function pointer.
   * @param cb_parameter Optional parameter to be passed to the callback function.
   */
  void setReportAppCallback(CallBackReportFunction cb, AnyType *cb_parameter = nullptr) override;

  /**
   * @brief Method to identify the light accessory.
   */
  void identifyYourSelf() override;

 private:
  /**
   * @brief Static function to handle button press.
   *
   * @param self Pointer to the LightAccessory instance.
   */
  static void buttonFunction(void *self);

  RelayModuleInterface *m_relayModule;    ///< Pointer to the relay module.
  ButtonModuleInterface *m_buttonModule;  ///< Pointer to the button module.

  CallBackReportFunction m_reportAttributesCallback;  ///< Callback function for reporting attributes.
  AnyType *m_reportAttributesCallbackParameter;       ///< Parameter to be passed to the callback function.
};