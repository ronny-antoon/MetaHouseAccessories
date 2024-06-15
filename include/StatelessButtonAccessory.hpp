// #pragma once

// #include <ButtonModuleInterface.hpp>

// #include "StatelessButtonAccessoryInterface.hpp"

// /**
//  * @brief Implementation of the Stateless Button Accessory.
//  */
// class StatelessButtonAccessory : public StatelessButtonAccessoryInterface {
//  public:
//   /**
//    * @brief Constructor for StatelessButtonAccessory.
//    *
//    * @param buttonModule Pointer to the button module interface.
//    */
//   StatelessButtonAccessory(ButtonModuleInterface *buttonModule);

//   /**
//    * @brief Destructor for StatelessButtonAccessory.
//    */
//   ~StatelessButtonAccessory();

//   /**
//    * @brief Set the callback function for reporting.
//    *
//    * @param cb Callback function pointer.
//    * @param cb_parameter Optional parameter to be passed to the callback function.
//    */
//   void setReportAppCallback(CallBackReportFunction cb, AnyType *cb_parameter = nullptr) override;

//   /**
//    * @brief Method to identify the stateless button accessory.
//    */
//   void identifyYourSelf() override;

//   /**
//    * @brief Get Last Press Type
//    *
//    * @return PressType
//    */
//   PressType getLastPressType();

//  private:
//   ButtonModuleInterface *m_buttonModule;  ///< Pointer to the button module.
//   PressType lastPressType_;               ///< Last press type

//   CallBackReportFunction m_reportAttributesCallback;  ///< Callback function for reporting attributes.
//   AnyType *m_reportAttributesCallbackParameter;       ///< Parameter to be passed to the callback function.
// };