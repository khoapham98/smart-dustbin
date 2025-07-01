# Smart Dustbin

This repository contains the firmware design for a **Smart Dustbin** project using an STM32F411 microcontroller. The dustbin automatically opens and closes its lid when it detects an object nearby, and displays the lid status on an OLED screen.

## Features

* **Automatic Lid Control**: Uses PWM to drive an SG90 servo motor (180) for opening and closing the lid.
* **Distance Measurement**: Employs an HC-SR04 ultrasonic sensor to detect objects within a defined range.
* **Status Display**: Shows current lid state (`Open` / `Closed`) on an I2C OLED display (SSD1306).
* **Bare-Metal Programming**: All peripherals are configured and controlled via direct register access (no HAL libraries).

## Hardware Components

| Component          | Quantity | Description                         |
| ------------------ | -------- | ----------------------------------- |
| STM32F411          | 1        | Microcontroller Unit                |
| SG90 Servo Motor   | 1        | Lid actuator                        |
| HC-SR04 Ultrasonic | 1        | Distance sensor                     |
| I2C OLED Display   | 1        | 128×32 SSD1306                      |
| Connecting Wires   | 11       | Jumper cables                       |
    	              
## Wiring Overview

1. **Servo Motor (SG90)**

   * VCC → 5 V
   * GND → GND
   * Signal → PB4 (TIM3\_CH1 PWM output)

2. **Ultrasonic Sensor (HC-SR04)**

   * VCC → 3 V
   * GND → GND
   * ECHO → PC6 (GPIO input)
   * TRIG → PC7 (GPIO output)

3. **0.91 inch OLED (SSD1306)**

   * VCC → 3 V
   * GND → GND
   * SDA → PB7 (I2C1\_SDA)
   * SCL → PB6 (I2C1\_SCL)

> **Note**: Ensure common ground between all devices.

## Software Setup

1. **Clone Repository**

   ```bash
   git clone https://github.com/khoapham98/smart-dustbin.git
   ```

2. **Open Project**

   * Launch **STM32CubeIDE**.
   * Import the existing project from the cloned folder.

3. **Build and Flash**

   * Configure your ST-Link or preferred programmer.
   * Build the project (`Project > Build All`).
   * Flash the binary to STM32F411 (`Run > Debug`).

4. **Run**

   * Power up the circuit.
   * When an object is within the set threshold (\~10 cm), the lid will open automatically. It will close once the object moves away.

## Customization

* **Distance Threshold**: Adjust the threshold in `hcsr04.c` to change the detection range.
* **PWM Parameters**: Tweak timer settings in `servo.c` for different servo speeds or angles.

