# -ADXL345-OLED-on-STM32F411-Bare-Metal-
This project demonstrates bare-metal firmware development on STM32F411 using register-level programming to interface an ADXL345 accelerometer and SSD1306 OLED display over I2C. The system detects motion/activity (> threshold G) using interrupts and displays the status on an OLED, with UART debug output

## 🧩 Features
* ✅ Bare-metal STM32 (no HAL / no Arduino)
* ✅ Register-level **I2C driver**
* ✅ Register-level **UART driver**
* ✅ **ADXL345 activity detection** (THRESH_ACT – `0x24`)
* ✅ **EXTI interrupt** based motion detection
* ✅ **OLED SSD1306 text rendering**
* ✅ Custom **ASCII font (5x7)**
* ✅ Modular driver structure
* ✅ GNU Makefile + linker script
* ✅ Debug & flash via **OpenOCD**
## 🛠️ Hardware Used
* **STM32F411** (Nucleo / custom board)
* **ADXL345** Accelerometer (I2C)
* **SSD1306 OLED** (I2C, 128×64)
* USB-UART (ST-Link VCP)
##  Connections
### I2C
| Signal | STM32F411 | Device         |
| ------ | --------- | -------------- |
| SDA    | PB9       | ADXL345 + OLED |
| SCL    | PB8       | ADXL345 + OLED |
| VCC    | 3.3V      | Both           |
| GND    | GND       | Both           |

### ADXL345 Interrupt

| Signal | STM32F411   |
| ------ | ----------- |
| INT1   | PA0 (EXTI0) |

### UART
| Signal | STM32F411 |
| ------ | --------- |
| TX     | PA2       |
| RX     | PA3       |
| Baud   | 115200    |

---

##  Project Structure
adxl_oled/
├── main.c
├── uart.c / uart.h
├── i2c.c / i2c.h
├── oled.c / oled.h
├── adxl345.c / adxl345.h
├── startup.s
├── system_stm32f4xx.c
├── linker.ld
├── syscalls.c
├── Makefile


## 📟Working Logic

1. STM32 initializes I2C, UART, OLED
2. ADXL345 configured for **activity interrupt**
3. Motion detected → **INT1 triggers EXTI**
4. STM32 reads `INT_SOURCE`
5. OLED displays:

6.  DETECTED 2G
   ```
6. LED ON + UART message
7. Message clears after delay



##  Key Registers Used

* **ADXL345**

  * `0x24` → THRESH_ACT
  * `0x27` → ACT_INACT_CTL
  * `0x2E` → INT_ENABLE
  * `0x30` → INT_SOURCE

* **STM32**

  * GPIO, I2C1, USART2, EXTI, NVIC

 Author

**Suraj Kumar**
Embedded Systems | Firmware | Bare-Metal
🇮🇳 India
