// #include "BlindAccessory.hpp"

// #include "esp_log.h"

// BlindAccessory::BlindAccessory(RelayModuleInterface *motorUp, RelayModuleInterface *motorDown,
//                                ButtonModuleInterface *buttonUp, ButtonModuleInterface *buttonDown,
//                                uint8_t timeToOpen, uint8_t timeToClose)
//     : m_motorUp(motorUp),
//       m_motorDown(motorDown),
//       m_buttonUp(buttonUp),
//       m_buttonDown(buttonDown),
//       m_timeToOpen(timeToOpen),
//       m_timeToClose(timeToClose),
//       m_blindPosition(0),
//       m_targetPosition(0),
//       m_moveBlindTaskHandle(nullptr),
//       m_reportAttributesCallback(nullptr),
//       m_reportAttributesCallbackParameter(nullptr) {
//   ESP_LOGI(__FILENAME__,
//            "Creating BlindAccessory with motorUp: %p, motorDown: %p, buttonUp: %p, buttonDown: %p, "
//            "timeToOpen: %d, timeToClose: %d",
//            motorUp, motorDown, buttonUp, buttonDown, timeToOpen, timeToClose);

//   m_buttonUp->onSinglePress(buttonUpFunction, this);
//   m_buttonDown->onSinglePress(buttonDownFunction, this);
// }

// BlindAccessory::~BlindAccessory() { ESP_LOGI(__FILENAME__, "Destroying BlindAccessory"); }

// void BlindAccessory::moveBlindTo(uint8_t new_position) {
//   ESP_LOGI(__FILENAME__, "moveBlindTo called with new_position: %d", new_position);

//   // Ensure position is within valid range
//   if (new_position > 100) {
//     ESP_LOGW(__FILENAME__, "New position %d is out of range, setting to 100", new_position);
//     new_position = 100;
//   } else if (new_position < 0) {
//     ESP_LOGW(__FILENAME__, "New position %d is out of range, setting to 0", new_position);
//     new_position = 0;
//   }

//   // Delete existing task handle if it exists
//   if (m_moveBlindTaskHandle) {
//     ESP_LOGI(__FILENAME__, "Deleting existing moveBlindTask");
//     vTaskDelete(m_moveBlindTaskHandle);
//     m_moveBlindTaskHandle = nullptr;
//   }

//   // Set the target position and create a task to move the blind to the target position
//   m_targetPosition = new_position;
//   xTaskCreate(moveBlindToTargetTask, "moveBlindToTask", 2048, this, 1, &m_moveBlindTaskHandle);
// }

// uint8_t BlindAccessory::getCurrentPosition() {
//   ESP_LOGI(__FILENAME__, "getCurrentPosition called, returning: %d", m_blindPosition);
//   return m_blindPosition;
// }

// uint8_t BlindAccessory::getTargetPosition() {
//   ESP_LOGI(__FILENAME__, "getTargetPosition called, returning: %d", m_targetPosition);
//   return m_targetPosition;
// }

// void BlindAccessory::setReportAppCallback(CallBackReportFunction cb, AnyType *cb_parameter) {
//   ESP_LOGI(__FILENAME__, "setReportAppCallback called with callback: %p, parameter: %p", cb, cb_parameter);
//   m_reportAttributesCallback = cb;
//   m_reportAttributesCallbackParameter = cb_parameter;
// }

// void BlindAccessory::identifyYourSelf() { ESP_LOGI(__FILENAME__, "identifyYourSelf called"); }

// void BlindAccessory::buttonDownFunction(void *self) {
//   BlindAccessory *blindAccessory = static_cast<BlindAccessory *>(self);
//   ESP_LOGI(__FILENAME__, "buttonDownFunction called");

//   if (blindAccessory->m_blindPosition != blindAccessory->m_targetPosition) {
//     blindAccessory->moveBlindTo(blindAccessory->m_blindPosition);
//   } else {
//     blindAccessory->moveBlindTo(0);
//   }
// }

// void BlindAccessory::buttonUpFunction(void *self) {
//   BlindAccessory *blindAccessory = static_cast<BlindAccessory *>(self);
//   ESP_LOGI(__FILENAME__, "buttonUpFunction called");

//   if (blindAccessory->m_blindPosition != blindAccessory->m_targetPosition) {
//     blindAccessory->moveBlindTo(blindAccessory->m_blindPosition);
//   } else {
//     blindAccessory->moveBlindTo(100);
//   }
// }

// void BlindAccessory::startMoveUp() {
//   ESP_LOGI(__FILENAME__, "startMoveUp called");
//   m_motorDown->setPower(0);
//   m_motorUp->setPower(1);
// }

// void BlindAccessory::startMoveDown() {
//   ESP_LOGI(__FILENAME__, "startMoveDown called");
//   m_motorUp->setPower(0);
//   m_motorDown->setPower(1);
// }

// void BlindAccessory::stopMove() {
//   ESP_LOGI(__FILENAME__, "stopMove called");
//   m_motorUp->setPower(0);
//   m_motorDown->setPower(0);
// }

// void BlindAccessory::moveBlindToTargetTask(void *self) {
//   BlindAccessory *blindAccessory = static_cast<BlindAccessory *>(self);
//   ESP_LOGI(__FILENAME__, "moveBlindToTargetTask called");

//   // Return if the blind is already at the target position
//   if (blindAccessory->m_blindPosition == blindAccessory->m_targetPosition) {
//     ESP_LOGI(__FILENAME__, "Blind is already at the target position: %d", blindAccessory->m_targetPosition);
//     blindAccessory->stopMove();
//     if (blindAccessory->m_reportAttributesCallback) {
//       blindAccessory->m_reportAttributesCallback(blindAccessory->m_reportAttributesCallbackParameter);
//     }
//     blindAccessory->m_moveBlindTaskHandle = nullptr;
//     vTaskDelete(nullptr);
//     return;
//   }

//   // Start moving the blind in the determined direction
//   bool isMovingUp = blindAccessory->m_targetPosition > blindAccessory->m_blindPosition;

//   uint32_t checkInterval;  // Time in ms to wait before checking the position again (1% of open/close time)
//   if (isMovingUp) {
//     checkInterval = 1000 * (blindAccessory->m_timeToOpen) / 100;
//   } else {
//     checkInterval = 1000 * (blindAccessory->m_timeToClose) / 100;
//   }

//   bool updated = false;
//   ESP_LOGI(__FILENAME__, "Starting to move the blind %s", isMovingUp ? "up" : "down");
//   if (isMovingUp) {
//     blindAccessory->startMoveUp();
//   } else {
//     blindAccessory->startMoveDown();
//   }
//   TickType_t xLastWakeTime = xTaskGetTickCount();
//   const TickType_t xFrequency = checkInterval / portTICK_PERIOD_MS;
//   // Continue moving the blind until the target position is reached
//   while (!blindAccessory->targetPositionReached(isMovingUp)) {
//     xTaskDelayUntil(&xLastWakeTime, xFrequency);
//     blindAccessory->m_blindPosition += isMovingUp ? 1 : -1;

//     if (!updated && blindAccessory->m_reportAttributesCallback) {
//       blindAccessory->m_reportAttributesCallback(blindAccessory->m_reportAttributesCallbackParameter);
//     }
//   }

//   // Stop the motor and report the final position
//   blindAccessory->stopMove();
//   blindAccessory->m_targetPosition = blindAccessory->m_blindPosition;
//   ESP_LOGI(__FILENAME__, "Blind reached the target position: %d", blindAccessory->m_targetPosition);

//   if (blindAccessory->m_reportAttributesCallback) {
//     blindAccessory->m_reportAttributesCallback(blindAccessory->m_reportAttributesCallbackParameter);
//   }
//   blindAccessory->m_moveBlindTaskHandle = nullptr;
//   vTaskDelete(nullptr);
// }

// bool BlindAccessory::targetPositionReached(bool movingUp) {
//   ESP_LOGI(__FILENAME__, "targetPositionReached called, movingUp: %d, current: %d, target: %d", movingUp,
//            m_blindPosition, m_targetPosition);
//   if (movingUp) {
//     return m_blindPosition >= m_targetPosition;
//   } else {
//     return m_blindPosition <= m_targetPosition;
//   }
// }
