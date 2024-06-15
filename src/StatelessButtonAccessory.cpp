// #include "StatelessButtonAccessory.hpp"

// #include <freertos/FreeRTOS.h>
// #include <freertos/task.h>

// StatelessButtonAccessory::StatelessButtonAccessory(ButtonModuleInterface *buttonModule)
//     : m_buttonModule(buttonModule) {
//   m_buttonModule->onSinglePress(
//       [](void *self) {
//         StatelessButtonAccessory *statelessButtonAccessory = static_cast<StatelessButtonAccessory *>(self);
//         statelessButtonAccessory->lastPressType_ = StatelessButtonAccessoryInterface::PressType::SinglePress;
//         if (statelessButtonAccessory->m_reportAttributesCallback) {
//           statelessButtonAccessory->m_reportAttributesCallback(
//               statelessButtonAccessory->m_reportAttributesCallbackParameter);
//         }
//       },
//       this);

//   m_buttonModule->onDoublePress(
//       [](void *self) {
//         StatelessButtonAccessory *statelessButtonAccessory = static_cast<StatelessButtonAccessory *>(self);
//         statelessButtonAccessory->lastPressType_ = StatelessButtonAccessoryInterface::PressType::DoublePress;
//         if (statelessButtonAccessory->m_reportAttributesCallback) {
//           statelessButtonAccessory->m_reportAttributesCallback(
//               statelessButtonAccessory->m_reportAttributesCallbackParameter);
//         }
//       },

//       this);

//   m_buttonModule->onLongPress(
//       [](void *self) {
//         StatelessButtonAccessory *statelessButtonAccessory = static_cast<StatelessButtonAccessory *>(self);
//         statelessButtonAccessory->lastPressType_ = StatelessButtonAccessoryInterface::PressType::LongPress;
//         if (statelessButtonAccessory->m_reportAttributesCallback) {
//           statelessButtonAccessory->m_reportAttributesCallback(
//               statelessButtonAccessory->m_reportAttributesCallbackParameter);
//         }
//       },
//       this);
// }

// StatelessButtonAccessory::~StatelessButtonAccessory() {}

// void StatelessButtonAccessory::setReportAppCallback(CallBackReportFunction cb, AnyType *cb_parameter) {
//   m_reportAttributesCallback = cb;
//   m_reportAttributesCallbackParameter = cb_parameter;
// }

// void StatelessButtonAccessory::identifyYourSelf() {}

// StatelessButtonAccessoryInterface::PressType StatelessButtonAccessory::getLastPressType() {
//   return lastPressType_;
// }