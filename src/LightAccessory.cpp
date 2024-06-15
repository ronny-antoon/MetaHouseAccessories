#include "LightAccessory.hpp"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

LightAccessory::LightAccessory(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule)
    : m_relayModule(relayModule), m_buttonModule(buttonModule) {
  m_buttonModule->onSinglePress(buttonFunction, this);
}

LightAccessory::~LightAccessory() {}

void LightAccessory::setPower(bool power) { m_relayModule->setPower(power); }

bool LightAccessory::getPower() { return m_relayModule->isOn(); }

void LightAccessory::setReportAppCallback(CallBackReportFunction cb, AnyType *cb_parameter) {
  m_reportAttributesCallback = cb;
  m_reportAttributesCallbackParameter = cb_parameter;
}

void LightAccessory::identifyYourSelf() {
  // Run task for 3 seconds to blink the LED
  xTaskCreate(
      [](void *self) {
        LightAccessory *lightAccessory = static_cast<LightAccessory *>(self);
        lightAccessory->setPower(0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        lightAccessory->setPower(1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        lightAccessory->setPower(0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        lightAccessory->setPower(1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        lightAccessory->setPower(0);

        // delete the task
        vTaskDelete(nullptr);
      },
      "identifyYourSelf", 2048, this, 5, nullptr);
}

void LightAccessory::buttonFunction(void *self) {
  LightAccessory *lightAccessory = static_cast<LightAccessory *>(self);
  lightAccessory->setPower(!lightAccessory->getPower());
  if (lightAccessory->m_reportAttributesCallback) {
    lightAccessory->m_reportAttributesCallback(lightAccessory->m_reportAttributesCallbackParameter);
  }
}