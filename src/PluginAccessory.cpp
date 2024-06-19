#include "PluginAccessory.hpp"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

PluginAccessory::PluginAccessory(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule)
    : m_relayModule(relayModule), m_buttonModule(buttonModule) {
  m_buttonModule->onSinglePress(buttonFunction, this);
}

PluginAccessory::~PluginAccessory() {}

void PluginAccessory::setPower(bool power) { m_relayModule->setPower(power); }

bool PluginAccessory::getPower() { return m_relayModule->isOn(); }

void PluginAccessory::setReportAppCallback(CallBackReportFunction cb, AnyType *cb_parameter) {
  m_reportAttributesCallback = cb;
  m_reportAttributesCallbackParameter = cb_parameter;
}

void PluginAccessory::identifyYourSelf() {
  // Run task for 3 seconds to blink the LED
  xTaskCreate(
      [](void *self) {
        PluginAccessory *pluginAccessory = static_cast<PluginAccessory *>(self);
        pluginAccessory->setPower(0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        pluginAccessory->setPower(1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        pluginAccessory->setPower(0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        pluginAccessory->setPower(1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        pluginAccessory->setPower(0);

        // delete the task
        vTaskDelete(nullptr);
      },
      "identifyYourSelf", 2048, this, 5, nullptr);
}

void PluginAccessory::buttonFunction(void *self) {
  PluginAccessory *pluginAccessory = static_cast<PluginAccessory *>(self);
  pluginAccessory->setPower(!pluginAccessory->getPower());
  if (pluginAccessory->m_reportAttributesCallback) {
    pluginAccessory->m_reportAttributesCallback(pluginAccessory->m_reportAttributesCallbackParameter);
  }
}
