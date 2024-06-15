// #include "SwitchAccessory.hpp"

// #include <freertos/FreeRTOS.h>
// #include <freertos/task.h>

// SwitchAccessory::SwitchAccessory(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule)
//     : m_relayModule(relayModule), m_buttonModule(buttonModule) {
//   m_buttonModule->onSinglePress(buttonFunction, this);
// }

// SwitchAccessory::~SwitchAccessory() {}

// void SwitchAccessory::setPower(bool power) { m_relayModule->setPower(power); }

// bool SwitchAccessory::getPower() { return m_relayModule->isOn(); }

// void SwitchAccessory::setReportAppCallback(CallBackReportFunction cb, AnyType *cb_parameter) {
//   m_reportAttributesCallback = cb;
//   m_reportAttributesCallbackParameter = cb_parameter;
// }

// void SwitchAccessory::identifyYourSelf() {
//   // Run task for 3 seconds to blink the LED
//   xTaskCreate(
//       [](void *self) {
//         SwitchAccessory *switchAccessory = static_cast<SwitchAccessory *>(self);
//         switchAccessory->setPower(0);
//         vTaskDelay(1000 / portTICK_PERIOD_MS);
//         switchAccessory->setPower(1);
//         vTaskDelay(1000 / portTICK_PERIOD_MS);
//         switchAccessory->setPower(0);
//         vTaskDelay(1000 / portTICK_PERIOD_MS);
//         switchAccessory->setPower(1);
//         vTaskDelay(1000 / portTICK_PERIOD_MS);
//         switchAccessory->setPower(0);

//         // delete the task
//         vTaskDelete(nullptr);
//       },
//       "identifyYourSelf", 2048, this, 5, nullptr);
// }

// void SwitchAccessory::buttonFunction(void *self) {
//   SwitchAccessory *switchAccessory = static_cast<SwitchAccessory *>(self);
//   switchAccessory->setPower(!switchAccessory->getPower());
//   if (switchAccessory->m_reportAttributesCallback) {
//     switchAccessory->m_reportAttributesCallback(switchAccessory->m_reportAttributesCallbackParameter);
//   }
// }