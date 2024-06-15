// #pragma once

// #include <freertos/FreeRTOS.h>
// #include <freertos/task.h>

// #include <ButtonModuleInterface.hpp>
// #include <RelayModuleInterface.hpp>

// #include "DoorLockAccessoryInterface.hpp"

// /**
//  * @brief Implementation of the Door Lock Accessory.
//  */
// class DoorLockAccessory : public DoorLockAccessoryInterface {
//  public:
//   /**
//    * @brief Constructor for DoorLockAccessory.
//    *
//    * @param relayModule Pointer to the relay module interface.
//    * @param buttonModule Pointer to the button module interface.
//    */
//   DoorLockAccessory(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule,
//                     uint8_t openTime = 5);

//   /**
//    * @brief Destructor for DoorLockAccessory.
//    */
//   ~DoorLockAccessory();

//   /**
//    * @brief Set the lock state of the door lock.
//    *
//    * @param lock The state to set the door lock to.
//    */
//   void setState(DoorLockState lock) override;

//   /**
//    * @brief Get the current lock state of the door lock.
//    *
//    * @return The current state of the door lock.
//    */
//   DoorLockState getState() override;

//   /**
//    * @brief Set the callback function for reporting.
//    *
//    * @param cb Callback function pointer.
//    * @param cb_parameter Optional parameter to be passed to the callback function.
//    */
//   void setReportAppCallback(CallBackReportFunction cb, AnyType *cb_parameter = nullptr) override;

//   /**
//    * @brief Method to identify the door lock accessory.
//    */
//   void identifyYourSelf() override;

//  private:
//   /**
//    * @brief Static function to handle button press.
//    *
//    * @param self Pointer to the DoorLockAccessory instance.
//    */
//   static void buttonFunction(void *self);

//   void openDoor();
//   static void openDoorTask(void *pvParameters);
//   void closeDoor();

//   RelayModuleInterface *m_relayModule;    ///< Pointer to the relay module.
//   ButtonModuleInterface *m_buttonModule;  ///< Pointer to the button module.
//   uint8_t m_openTime;                     ///< Time in seconds to keep the door open.
//   TaskHandle_t *m_openDoorTaskHandle;     ///< Task handle for the open door task.

//   CallBackReportFunction m_reportAttributesCallback;  ///< Callback function for reporting attributes.
//   AnyType *m_reportAttributesCallbackParameter;       ///< Parameter to be passed to the callback function.
// };