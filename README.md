# ESPHome Component SEN6X

<p align="center">
    <img src="https://sensirion.com/_next/image?url=https%3A%2F%2Fsensirion.com%2Fmedia%2Fportfolio%2Fproduct%2Fimage%2Fd2b23157-ec1c-40f7-b89f-e38ad4d4a40f.webp&w=2048&q=75" width="50%"><br />
    SEN66 Environmental Sensor
</p>

This external component adds SEN62, SEN63C, SEN65, SEN66, SEN68 and SEN69C support to ESPHome.

```yaml
# Example SEN66 sensor configuration entry example
external_components:
  - source:
      type: git
      url: https://github.com/mikelawrence/esphome-components
    components: [ sen6x ]

sensor:
  - platform: sen6x
    id: my_sen66
    type: SEN66
    temperature_compensation:
      offset: 0
      normalized_offset_slope: 0
      time_constant: 0
    temperature_acceleration:
      k: 20
      p: 20
      t1: 100
      t2: 300
    pm_1_0:
      name: "PM <1µm Mass concentration"
    pm_2_5:
      name: "PM <2.5µm Mass concentration"
    pm_4_0:
      name: "PM <4µm Mass concentration"
    pm_10_0:
      name: "PM <10µm Mass concentration"
    temperature:
      name: "Temperature"
    humidity:
      name: "Humidity"
    voc:
      name: "VOC"
      store_algorithm_state: true
      algorithm_tuning:
        index_offset: 100
        learning_time_offset_hours: 12
        learning_time_gain_hours: 12
        gating_max_duration_minutes: 180
        std_initial: 50
        gain_factor: 230
    nox:
      name: "NOx"
      algorithm_tuning:
        index_offset: 1
        learning_time_offset_hours: 12
        gating_max_duration_minutes: 720
        gain_factor: 230
    co2:
      name: "CO₂"
      automatic_self_calibration: false
      ambient_pressure_compensation_source: pressure_hpa
```

## Configuration Variables

* **type** (*Required*, enum): The type of the connected sensor.Provides compile time config validation of sensors. Must be one of the following:
  SEN62, SEN63C, SEN65, SEN66, SEN68 or SEN69C. All options from [Sensor](/components/sensor#config-sensor).

* **id** (*Optional*, [ID](https://esphome.io/guides/configuration-types/#id)): Manually specify the ID for the sen6x component. Required if there are multiple SEN6Xs configured.

* **address** (*Optional*, int): Manually specify the I²C address of the sensor. Defaults to `0x6B`.

* **temperature_acceleration** (*Optional*): This command allows user to set custom temperature acceleration
  parameters.

  This is a good starting point for these values.

  | Acceleration Level     |   T1    |   T1    |   K    |   P    |
  | -----------------------|:-------:|:-------:|:------:|:------:|
  | Light (IAQM)           |   100   |   300   |   20   |   20   |
  | Middle                 |   100   |   300   |   50   |   20   |
  | Strong (Air Purifier)  |   250   |   300   |  150   |   20   |

  For more information see
  [SEN6x – Temperature Acceleration and Compensation Instructions](https://sensirion.com/media/documents/C964FCC8/693FD554/PS_AN_SEN6x_Temperature_Compensation_and_Acceleration_Application_No.pdf).

  * **k** (*Required*): Filter constant K.
  * **p** (*Required*): Filter constant P.
  * **t1** (*Required*): Time constant T1 in seconds.
  * **t2** (*Required*): Time constant T2 in seconds.

* **temperature_compensation** (*Optional*, sequence): These parameters allow the user to compensate temperature
  effects of the design-in at the customer side by applying custom temperature offsets to the ambient temperature.
  Temperature Compensation is a sequence (called slots) of compensation parameter sets. Up to five
  temperature compensation sets are supported.
  See [Temperature Compensation](#temperature-compensation) section below for more information.

  * **offset** (*Optional*, float): Temperature offset, in °C. Defaults to `0`.
  * **normalized_offset_slope** (*Optional*, float): Normalized temperature offset slope. Defaults to `0`.
  * **time_constant** (*Optional*, positive int): Time constant in seconds. Defaults to `0`.

# Sensors

* **pm_1_0** (*Optional*): The information for the **Mass Concentration** sensor for fine particles up to
  1μm in size. Readings in µg/m³. All options from [Sensor](/components/sensor#config-sensor).

* **pm_2_5** (*Optional*): The information for the **Mass Concentration** sensor for fine particles up to
  2.5μm in size. Readings in µg/m³. All options from [Sensor](/components/sensor#config-sensor).

* **pm_4_0** (*Optional*): The information for the **Mass Concentration** sensor for coarse particles up to
  4μm in size. Readings in µg/m³. All options from [Sensor](/components/sensor#config-sensor).

* **pm_10_0** (*Optional*): The information for the **Mass Concentration** sensor for coarse particles up to
  10μm in size. Readings in µg/m³. All options from [Sensor](/components/sensor#config-sensor).

* **temperature** (*Optional*): The information for the Temperature sensor. Only available with
  SEN62, SEN63C, SEN65, SEN66, SEN68 or SEN69C. All options from [Sensor](/components/sensor#config-sensor).

* **humidity** (*Optional*): The information for the Relative Humidity sensor. Only available with
  SEN62, SEN63C, SEN65, SEN66, SEN68 or SEN69C. All options from [Sensor](/components/sensor#config-sensor).

* **co2** (*Optional*): The information for the Carbon dioxide (CO₂) sensor. Readings in ppm. Only available with
  SEN63C, SEN66 or SEN69C.

  * **auto_self_calibration** (*Optional*, boolean): True enables automatic CO₂ self calibration.
  False disables automatic CO₂ calibration. Default is `true`.
  * **altitude_compensation** (*Optional*, integer): When set to altitude (in meters), the CO₂ sensor will be
  statically compensated for deviations due to current altitude. See [CO₂ Compensation](#co₂-compensation) section below
  for more information.
  * **ambient_pressure_compensation_source** (*Optional*, [ID](/guides/configuration-types#config-id)):
  Sets an external pressure sensor ID (must report in hPA). This will compensate the CO₂ sensor for deviations
  due to current pressure. This correction is applied with each update of the CO₂ sensor. See
  [CO₂ Compensation](#co₂-compensation) section below for more information.
  * All options from [Sensor](/components/sensor#config-sensor).

* **voc** (*Optional*): The information for the VOC Index sensor. Only available with SEN65, SEN66, SEN69 or SEN69C.

  * **store_algorithm_state** (*Optional*, boolean): When set to `true` the VOC algorithm state is saved to flash every
    2 hours. During setup of the sensor the previously saved algorithm state is loaded and the VOC sensor will
    skip the initial learning phase.
    Only available with SEN65, SEN66, SEN68 or SEN69C.
  * **algorithm_tuning** (*Optional*): The VOC algorithm can be customized by tuning 6 different parameters.
    For more details see
    [Engineering Guidelines for SEN5X](https://sensirion.com/media/documents/25AB572C/62B463AA/Sensirion_Engineering_Guidelines_SEN5x.pdf)

    * **index_offset** (*Optional*): VOC index representing typical (average) conditions.
      Allowed values are in range 1..250. The default value is 100.
    * **learning_time_offset_hours** (*Optional*): Time constant to estimate the VOC algorithm offset from the
      history in hours. Past events will be forgotten after about twice the learning time.
      Allowed values are in range 1..1000. The default value is 12 hour.
    * **learning_time_gain_hours** (*Optional*): Time constant to estimate the VOC algorithm gain from the
      history in hours. Past events will be forgotten after about twice the learning time.
      Allowed values are in range 1..1000. The default value is 12 hours.
    * **gating_max_duration_minutes** (*Optional*): Maximum duration of gating in minutes (freeze of estimator
      during high VOC index signal). Zero disables the gating. Allowed values are in range 0..3000.
      The default value is 180 minutes.
    * **std_initial** (*Optional*): Initial estimate for standard deviation. Lower value boosts events during
      initial learning period, but may result in larger device-to-device variations.
      Allowed values are in range 10..5000. The default value is 50.
    * **gain_factor** (*Optional*): Gain factor to amplify or to attenuate the VOC index output.
      Allowed values are in range 1..1000. The default value is 230. All options from [Sensor](/components/sensor#config-sensor).

* **nox** (*Optional*): NOx Index. Only available with SEN65, SEN66, SEN69 or SEN69C.

  * **algorithm_tuning** (*Optional*): Like VOC the NOx algorithm can be customized by tuning 5 different parameters.
    For more details see
    [Engineering Guidelines for SEN5X](https://sensirion.com/media/documents/25AB572C/62B463AA/Sensirion_Engineering_Guidelines_SEN5x.pdf)

    * **index_offset** (*Optional*): NOx index representing typical (average) conditions.
      Allowed values are in range 1..250. The default value is 100.
    * **learning_time_offset_hours** (*Optional*): Time constant to estimate the NOx algorithm offset from the
      history in hours. Past events will be forgotten after about twice the learning time.
      Allowed values are in range 1..1000. The default value is 12 hour.
    * **learning_time_gain_hours** (*Optional*): Here for completeness, but this is ignored by NOx Algorithm Tuning.
    * **gating_max_duration_minutes** (*Optional*): Maximum duration of gating in minutes (freeze of estimator
      during high NOx index signal). Zero disables the gating. Allowed values are in range 0..3000.
      The default value is 180 minutes.
    * **std_initial** (*Optional*): Here for completeness, but this is ignored by NOx Algorithm Tuning.
    * **gain_factor** (*Optional*): Gain factor to amplify or to attenuate the NOx index output.
      Allowed values are in range 1..1000. The default value is 230. All options from [Sensor](/components/sensor#config-sensor).

* **hcho** (*Optional*): The information for the Formaldehyde (HCHO) sensor. Readings in ppb. Only available with
  SEN68 or SEN69C. All options from [Sensor](/components/sensor#config-sensor).

> [!NOTE]
> This component reports readings as soon as they are available without regard initial accuracy.
> Your configuration should limit reporting of sensor values for a period of time after power-up.
> A good starting point is 5 minutes.
>
> * The PM sensor has a start-up time of 30 seconds.
> * The temperature sensor has a response time of 1 minute with no mention start-up time.
> * The humidity sensor has a response time of 20 seconds with no mention start-up time.
> * The VOC sensor will start detecting events in 1 minute but may take up to 1 hour to meet
>   data sheet specifications.
> * The NOx sensor will start detecting events in 5 minutes but may take up to 6 hours to meet
>   data sheet specifications.
> * The CO₂ sensor has a response time of between 60 and 70 seconds with no mention start-up time.
> * The HCHO sensor has a start-up time of 10 minutes.

# Actions

Multiple actions are available with this component and are queued when requested. Queued actions will wait until the sensor is not busy, either from other actions or reading sensor data and the perform the requested actions. Some actions will pause sensor readings while the action is in progress. Trying to queue the same action more than once does nto make sense and the second action will be ignored.

## Fan Cleaning

The sensor supports a manual fan cleaning cycle by using the
`sen6x.start_fan_cleaning` action.

### `sen6x.start_fan_cleaning` Action

This [action](https://esphome.io/automations/actions/#actions) manually starts fan cleaning. During the fan cleaning
process sensor measurements are paused or stopped, depending on the sensor, while the fan is running at
the elevated rate. The entire fan cleaning sequence takes 12 seconds.

```yaml
on_...:
  then:
    - sen6x.start_fan_cleaning: sen62
```

The previous generation SEN5X sensor had an optional automatic fan cleaning every 7 days. You can emulate this
automatic fan cleaning by calling the `sen6x.start_fan_cleaning:` action periodically.

For example, to clean the fan every 7 days while the device is on, as recommended by the manufacturer, the
following configuration can be added:

```yaml
interval:
  - interval: 7d
    then:
      - sen6x.start_fan_cleaning: my_sen66
```

## Humidity Sensor Heater

The SEN6X humidity sensor can develop an offset in the humidity reading when exposed to high levels of
humidity for extended periods of time. It supports a heater similar to the one in the SHT4X. The
difference is no automatic mode. Instead you have to trigger `sen6x.activate_heater` action occasionally.

### `sen6x.activate_heater` Action

This [action](https://esphome.io/automations/actions/#actions) manually starts the heater. First all measurements are
stopped, then the heater is turned on at 200mW for 1s, finally there is a 20 second delay before
reenabling the measurements. This is to ensure the heating effects are gone before temperature measurements
resume. The entire activate heater sequence takes 22 seconds.

```yaml
on_...:
  then:
    - sen6x.activate_heater: my_sen66
```

## CO₂ Calibration

The CO₂ sensor by default has auto-calibration enabled. Auto-calibration will adjust the minimum measurement
over the last week or so to the outdoor average of slightly more than 400 ppm. Auto-calibration assumes that
you are opening the windows at least once a week. If you don't open the windows then over time the CO₂ level
will tend downward.

If you know your minimums are not going to be 400 ppm then you can disable auto-calibration and occasionally
take the sensor outside for 5 minutes and then force a manual CO₂ calibration to the expected outdoor CO₂ level.
Be sure to watch the log output of your device when you perform this action. If the sensor reports an error
during the recalibration process it will be reported in the log.

### `sen6x.perform_forced_co2_recalibration` Action

This [action](https://esphome.io/automations/actions/#actions) forces a manual calibration on the CO₂ sensor. Measurements
are stopped before issuing the forced co2 recalibrate command to the sensor. The entire perform forced co2
recalibration action takes 2 seconds.

The example below will recalibrate the CO₂ sensor when the "CO₂ Calibrate" button is pressed using the
"CO₂ Calibration Value" number's current value.

```yaml
number:
  - platform: template
    id: co2_forced_cal_value
    name: "CO₂ Calibration Value"
    device_class: carbon_dioxide
    entity_category: CONFIG
    optimistic: true
    max_value: 1200
    min_value: 400
    step: 1
    initial_value: 420
button:
  - platform: template
    name: "CO₂ Calibrate"
    entity_category: CONFIG
    on_press:
      - sen6x.perform_forced_co2_recalibration:
          value: !lambda "return id(co2_forced_cal_value).state;"
          id: sen66_sensor
sensor:
  - platform: sen6x
    type: SEN66
    id: sen66_sensor
    co2:
      name: "CO₂"
```

## CO₂ Compensation

The CO₂ sensor supports pressure/altitude compensation to improve CO₂ accuracy. If a pressure sensor is available
you can dynamically adjust pressure compensation by either adding `ambient_pressure_compensation_source` to your
configuration for automatic updates or you can periodically call the `sen6x.set_ambient_pressure_compensation`
action with the current ambient pressure. You can also statically define `altitude_compensation`.

### Dynamic example with a local sensor

```yaml
sensor:
  - platform: bmp581
    id: bmp581_sensor
    pressure:
      id: pressure_hpa
      filters:
        - lambda: |-
            // convert Pa to hPa (or mBar)
            return x * 0.01;
  - platform: sen6x
    type: SEN69C
    co2:
      name: "CO₂"
      ambient_pressure_compensation_source: pressure_hpa
```

### Dynamic example `sen6x.set_ambient_pressure_compensation` Action

This [action](https://esphome.io/automations/actions/#actions) updates the current pressure used in CO₂ pressure compensation.
Must be in hPa or mBar. Note: Once `set_ambient_pressure_compensation` is called `altitude_compensation`, if
set in the configuration, will be ignored. Only available with SEN63C, SEN66 or SEN69C.

```yaml
sensor:
  - platform: bmp581
    id: bmp581_sensor
    pressure:
      id: pressure_hpa
      filters:
        - lambda: |-
            // convert Pa to hPa (or mBar)
            return x * 0.01;
    on_value:
      then:
        - lambda: !lambda |-
            id(sen66_sensor).set_ambient_pressure_compensation(x);
  - platform: sen6x
    type: SEN69C
    id: sen66_sensor
    co2:
      name: "CO₂"
```

### Static example with altitude

```yaml
sensor:
  - platform: sen6x
    type: SEN66
    co2:
      name: "CO₂"
      altitude_compensation: 427m
```

## Temperature Compensation

These sensors contain an internal temperature compensation mechanism. The compensated ambient temperature is
calculated as follows:

```c++
T_Ambient_Compensated = T_Ambient + (slope*T_Ambient) + offset
```

Where slope and offset are the values set with `temperature_compensation` configuration variables, smoothed
with the specified time constant, also a `temperature_compensation` configuration variable. The time constant
is how fast the slope and offset are applied. After the specified value in seconds, 63% of the new slope and
offset are applied.

More details about the tuning of these parameters is included in the application note:
[SEN6x – Temperature Acceleration and Compensation Instructions](https://sensirion.com/media/documents/C964FCC8/693FD554/PS_AN_SEN6x_Temperature_Compensation_and_Acceleration_Application_No.pdf).

### `sen6x.set_temperature_compensation` Action

This [action](https://esphome.io/automations/actions/#actions) give you access to temperature compensation slots 0-4.
This is a dynamic compensation that for example can be used when internal devices are turned on that cause additional heating.

```yaml
button:
  - platform: template
    name: "Set Slot 1 TC"
    on_press:
      - sen6x.set_temperature_compensation:
          id: sen66_sensor
          slot: 1
          offset: -1.2
          normalized_offset_slope: 0
          time_constant: 0
```
