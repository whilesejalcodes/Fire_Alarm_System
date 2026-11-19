# 🔥 Smart Fire Alarm System Using Arduino Uno

### Multi-Sensor Fire Detection with Hybrid Threshold-Based Decision Logic

A simulation-based embedded systems project that implements a **Smart Fire Detection and Alarm System** using an Arduino Uno R3.

The system combines simulated temperature, smoke/gas, and flame sensor inputs using a **hybrid threshold-based multi-sensor voting algorithm** to identify potential fire hazards and generate appropriate alerts.

The project is developed using the **Wokwi Simulation Platform**, allowing different fire-related scenarios to be evaluated without requiring physical hardware.

---

## 🚀 Live Simulation

### [▶️ Click Here to Run the Simulation](https://wokwi.com/projects/481039879796661249)

Click the link above and press the **Start Simulation** button to interact with the system.

---

## 📌 Project Overview

Conventional fire alarm systems may rely on a single sensing parameter, which can lead to false alarms or missed detections.

This project implements a multi-sensor approach that considers three environmental parameters:

- 🌡️ **Temperature:** Simulated LM35 temperature sensor
- 💨 **Smoke/Gas:** Simulated MQ-2 smoke/gas sensor
- 🔥 **Flame:** Simulated digital IR flame sensor

The system processes these inputs using an Arduino Uno and classifies environmental conditions into three operational states:

- 🟢 **NORMAL:** All sensor readings are within predefined thresholds.
- 🟡 **WARNING:** One sensor exceeds its warning threshold.
- 🔴 **EMERGENCY:** A critical threshold is exceeded, a flame is detected, or multiple sensors indicate abnormal conditions.

---

## ⚙️ Key Features

- Multi-sensor fire detection
- Hybrid threshold-based decision algorithm
- Multi-sensor voting for emergency classification
- Three-level alert system
- Immediate emergency classification upon flame detection
- Visual alerts using LEDs
- Audible alerts using a buzzer
- Real-time status display on a 16×2 I2C LCD
- Simulated exhaust fan activation during emergencies
- Serial monitoring of sensor readings
- Manual alarm acknowledgment using a push button
- Fully interactive virtual simulation

---

## 🧰 Components Used

| Component | Purpose |
|---|---|
| Arduino Uno R3 | Main microcontroller |
| Potentiometer 1 | Simulates LM35 temperature readings |
| Potentiometer 2 | Simulates MQ-2 smoke/gas readings |
| Slide Switch | Simulates IR flame detection |
| 16×2 I2C LCD | Displays system status |
| Green LED | Indicates NORMAL state |
| Yellow LED | Indicates WARNING state |
| Red LED | Indicates EMERGENCY state |
| Blue LED | Simulates exhaust fan activation |
| Buzzer | Generates audible alerts |
| Push Button | Manual alarm acknowledgment |

**Note:** The temperature and smoke sensors are represented by potentiometers, while the flame sensor is represented by a switch. No physical sensors are connected in this simulation.

---

## 🔌 Arduino Pin Configuration

| Component | Arduino Pin |
|---|---|
| Temperature Input | A0 |
| Smoke/Gas Input | A1 |
| Flame Detection | D2 |
| Reset Button | D3 |
| Buzzer | D6 |
| Green LED | D8 |
| Yellow LED | D9 |
| Red LED | D10 |
| Fan Indicator (Blue LED) | D11 |
| I2C LCD SDA | A4 |
| I2C LCD SCL | A5 |

---

## 🧠 Hybrid Fire Detection Algorithm

The system combines two decision-making techniques:

### 1. Threshold-Based Detection

Each analog sensor has two predefined thresholds:

- Warning threshold
- Critical threshold

If any sensor crosses its critical threshold, the system immediately enters the EMERGENCY state.

### 2. Multi-Sensor Voting

If two or more sensors exceed their warning thresholds, the system enters the EMERGENCY state even when neither analog sensor has reached its critical threshold.

### Detection Thresholds

| Sensor | Warning Threshold | Critical Threshold |
|---|---|---|
| Temperature | >45°C | >57°C |
| Smoke/Gas | >300 simulated ppm | >400 simulated ppm |
| Flame | — | Flame detected |

These values are illustrative simulation thresholds and should not be interpreted as calibrated fire-safety limits.

### Decision Logic

```cpp
if (tempCritical || smokeCritical || flameDetected ||
    active_sensors >= 2) {

    systemState = 2;  // EMERGENCY

}
else if (active_sensors == 1) {

    systemState = 1;  // WARNING

}
else {

    systemState = 0;  // NORMAL

}
```

### System States

| State | Condition | LED | Buzzer | Fan Indicator |
|---|---|---|---|---|
| NORMAL | No warning thresholds exceeded | Green | OFF | OFF |
| WARNING | One warning threshold exceeded | Yellow | Intermittent | OFF |
| EMERGENCY | Critical threshold, flame detection, or multi-sensor agreement | Red | Continuous | ON |

---

## 🧪 Simulation Test Scenarios

The following test cases illustrate the expected behavior of the implemented algorithm.

| Test | Temperature | Smoke | Flame | Expected State |
|---|---|---|---|---|
| 1 | 25°C | 100 ppm | No | 🟢 NORMAL |
| 2 | 50°C | 100 ppm | No | 🟡 WARNING |
| 3 | 25°C | 350 ppm | No | 🟡 WARNING |
| 4 | 50°C | 350 ppm | No | 🔴 EMERGENCY |
| 5 | 60°C | 100 ppm | No | 🔴 EMERGENCY |
| 6 | 25°C | 450 ppm | No | 🔴 EMERGENCY |
| 7 | 25°C | 100 ppm | Yes | 🔴 EMERGENCY |

### Example: Multi-Sensor Voting

Suppose the simulated readings are:

- Temperature = 50°C
- Smoke = 350 ppm
- Flame = Not detected

Both temperature and smoke exceed their warning thresholds.

Although neither reaches its critical threshold, the system activates the **EMERGENCY** state because two sensors indicate abnormal conditions.

---

## ▶️ How to Run the Simulation

1. Open the [Wokwi Simulation](https://wokwi.com/projects/481039879796661249).
2. Click **Start Simulation**.
3. Adjust the first potentiometer to change the simulated temperature.
4. Adjust the second potentiometer to change the simulated smoke/gas concentration.
5. Toggle the slide switch to simulate flame detection.
6. Observe the LEDs, LCD, buzzer, and fan indicator.
7. Open the Serial Monitor to inspect sensor readings and system status.
8. Press the reset button to temporarily acknowledge the alarm.

The system automatically recalculates its state based on the latest sensor readings.

---

## 💻 Technologies Used

- **Microcontroller:** Arduino Uno R3 (ATmega328P)
- **Programming Language:** Arduino C/C++
- **Simulation Platform:** Wokwi
- **Display:** 16×2 I2C LCD
- **Libraries:**
  - `Wire.h`
  - `LiquidCrystal_I2C.h`

---

## 📁 Project Structure

```text
Smart-Fire-Alarm-System/
│
├── sketch.ino          # Arduino firmware and detection logic
├── diagram.json        # Wokwi circuit configuration
├── libraries.txt       # Required external libraries
└── README.md           # Project documentation
```

---

## ⚠️ Limitations

- The project is implemented entirely in simulation.
- Potentiometers replace physical temperature and smoke sensors.
- Smoke readings represent simulated values rather than calibrated MQ-2 measurements.
- Sensor noise, drift, and environmental variations are not modeled.
- Detection thresholds are predefined and require validation before physical deployment.
- The system uses blocking delays, which can affect responsiveness.
- The reset button temporarily acknowledges the alarm without permanently clearing an active emergency.
- The exhaust fan is represented by an LED rather than a physical motor.
- No real-world fire detection accuracy or response-time guarantees have been established.

**This is an educational prototype and must not be used as a certified life-safety fire alarm system.**

---

## 🔮 Future Enhancements

- Integration with physical LM35, MQ-2, and IR flame sensors
- Sensor calibration and filtering
- Non-blocking timing using `millis()`
- Hysteresis to prevent repeated state switching near thresholds
- IoT-based remote monitoring and notifications
- Real-time sensor data logging
- Hardware implementation and experimental validation

---

## 📚 Research Work

This project is associated with the research paper:

**Design and Simulation of a Multi-Sensor Fire Detection and Alarm System with Three-Tier Escalation Logic**

The paper describes the system architecture, hybrid detection algorithm, simulation methodology, and limitations.

---

## 👩‍💻 Authors

- Mimansha Kumar
- Mishka Malhotra
- Sejal Thakur
- Yashika

**Department of Electronics and Communication Engineering**  
Indira Gandhi Delhi Technical University for Women (IGDTUW)

---

⭐ If you find this project useful, consider starring the repository!
