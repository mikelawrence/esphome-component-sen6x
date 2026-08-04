#pragma once

#include "esphome/core/component.h"
#include "esphome/core/automation.h"
#include "sen6x.h"

namespace esphome::sen6x {

template<typename... Ts> class StartFanCleaningAction : public Action<Ts...>, public Parented<Sen6xComponent> {
 public:
  void play(const Ts &...x) override { this->parent_->start_fan_cleaning(); }
};

template<typename... Ts> class ActivateHeaterAction : public Action<Ts...>, public Parented<Sen6xComponent> {
 public:
  void play(const Ts &...x) override { this->parent_->activate_heater(); }
};

template<typename... Ts>
class SetAmbientPressureCompensationDeprecatedAction : public Action<Ts...>, public Parented<Sen6xComponent> {
 public:
  void play(const Ts &...x) override {
    auto value = this->value_.value(x...);
    this->parent_->set_ambient_pressure_compensation(value);
  }

 protected:
  TEMPLATABLE_VALUE(uint16_t, value)
};

template<typename... Ts> class SetAmbientPressureAction : public Action<Ts...>, public Parented<Sen6xComponent> {
 public:
  void play(const Ts &...x) override {
    auto value = this->value_.value(x...);
    this->parent_->set_ambient_pressure(value);
  }

 protected:
  TEMPLATABLE_VALUE(uint16_t, value)
};

template<typename... Ts>
class PerformForcedCo2RecalibrationAction : public Action<Ts...>, public Parented<Sen6xComponent> {
 public:
  void play(const Ts &...x) override {
    auto value = this->value_.value(x...);
    this->parent_->perform_forced_co2_recalibration(value);
  }

 protected:
  TEMPLATABLE_VALUE(uint16_t, value)
};

template<typename... Ts> class SetTemperatureOffsetAction : public Action<Ts...>, public Parented<Sen6xComponent> {
 public:
  void play(const Ts &...x) override {
    auto offset = this->offset_.value(x...);
    auto slope = this->slope_.value(x...);
    auto time_constant = this->time_constant_.value(x...);
    auto slot = this->slot_.value(x...);
    this->parent_->set_temperature_offset(offset, slope, time_constant, slot);
  }

 protected:
  TEMPLATABLE_VALUE(float, offset)
  TEMPLATABLE_VALUE(float, slope)
  TEMPLATABLE_VALUE(uint16_t, time_constant)
  TEMPLATABLE_VALUE(uint8_t, slot)
};

// deprecated: remove January 2027
template<typename... Ts>
class SetTemperatureCompensationDeprecatedAction : public Action<Ts...>, public Parented<Sen6xComponent> {
 public:
  void play(const Ts &...x) override {
    auto offset = this->offset_.value(x...);
    auto slope = this->slope_.value(x...);
    auto time_constant = this->time_constant_.value(x...);
    auto slot = this->slot_.value(x...);
    this->parent_->set_temperature_compensation(offset, slope, time_constant, slot);
  }

 protected:
  TEMPLATABLE_VALUE(float, offset)
  TEMPLATABLE_VALUE(float, slope)
  TEMPLATABLE_VALUE(uint16_t, time_constant)
  TEMPLATABLE_VALUE(uint8_t, slot)
};

}  // namespace esphome::sen6x
