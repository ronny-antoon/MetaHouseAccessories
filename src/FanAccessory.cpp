#include "FanAccessory.hpp"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

FanAccessory::FanAccessory(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule)
    : m_relayModule(relayModule), m_buttonModule(buttonModule) {
  m_buttonModule->onSinglePress(buttonFunction, this);
}

FanAccessory::~FanAccessory() {}

void FanAccessory::setPower(bool power) { m_relayModule->setPower(power); }

bool FanAccessory::getPower() { return m_relayModule->isOn(); }

void FanAccessory::setReportAppCallback(CallBackReportFunction cb, AnyType *cb_parameter) {
  m_reportAttributesCallback = cb;
  m_reportAttributesCallbackParameter = cb_parameter;
}

void FanAccessory::identifyYourSelf() {
  // Run task for 3 seconds to blink the LED
  xTaskCreate(
      [](void *self) {
        FanAccessory *fanAccessory = static_cast<FanAccessory *>(self);
        fanAccessory->setPower(0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        fanAccessory->setPower(1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        fanAccessory->setPower(0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        fanAccessory->setPower(1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        fanAccessory->setPower(0);

        // delete the task
        vTaskDelete(nullptr);
      },
      "identifyYourSelf", 2048, this, 5, nullptr);
}

void FanAccessory::buttonFunction(void *self) {
  FanAccessory *fanAccessory = static_cast<FanAccessory *>(self);
  fanAccessory->setPower(!fanAccessory->getPower());
  if (fanAccessory->m_reportAttributesCallback) {
    fanAccessory->m_reportAttributesCallback(fanAccessory->m_reportAttributesCallbackParameter);
  }
}