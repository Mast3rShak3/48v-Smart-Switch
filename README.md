Here’s your text rewritten in plain text with no photos or special formatting:

---

# 48V LED Strip Alexa Controller

Control high-power 48V LED strips with Alexa voice commands using ESP8266 and MOSFET switching.

Status: Working
Platform: ESP8266
License: MIT

---

## Features

* Alexa Voice Control - Example: "Alexa, turn on LED Lights"
* PWM Dimming - Smooth 0–100% brightness control
* Web Interface - Manual control at [http://device-ip:8080](http://device-ip:8080)
* High Power - Controls up to 192W (48V at 4A)

---

## Hardware Required

| Component        | Purpose                | Notes                                      |
| ---------------- | ---------------------- | ------------------------------------------ |
| ESP8266 D1 Mini  | Main controller        | With breakout board                        |
| IRLZ44N MOSFET   | High-current switching | Must be IRLZ44N (logic-level), not IRFZ44N |
| 220Ω Resistor    | Gate protection        | 1/4W                                       |
| 48V Power Supply | LED power              | 4A+ rating                                 |
| 48V LED Strip    | Lighting               | Up to 4A                                   |

Estimated total cost: \$40–60

---

## Wiring

D1 Mini:
D1 (GPIO5) → 220Ω resistor → MOSFET Gate
GND → MOSFET Source + 48V Supply Negative

48V Supply:
Positive → LED Strip Positive
Negative → MOSFET Source + D1 Mini GND

LED Strip:
Positive → 48V Supply Positive
Negative → MOSFET Drain

---

## Setup

1. Install ESP8266 board in Arduino IDE
2. Install library: "Espalexa by Christian Schwinne"
3. Update WiFi credentials in code:

   ```
   const char* ssid = "YOUR_WIFI_NAME";
   const char* password = "YOUR_PASSWORD";
   ```
4. Upload to D1 Mini
5. Wire circuit (ensure power is OFF during wiring)
6. Test web interface at [http://device-ip:8080](http://device-ip:8080)
7. In Alexa app, run "Discover devices"

---

## Usage

Voice Commands:

* "Alexa, discover devices"
* "Alexa, turn on LED Lights"
* "Alexa, set LED Lights to 50%"
* "Alexa, turn off LED Lights"

Web Interface:
Go to [http://device-ip:8080](http://device-ip:8080) for ON/OFF and dimming control.

Serial Commands (for debugging):

* 1 or on = Turn ON
* 0 or off = Turn OFF
* dim128 = Set brightness (0–255)
* test = Run test sequence

---

## Troubleshooting

| Problem                   | Solution                                        |
| ------------------------- | ----------------------------------------------- |
| LED strips too dim        | Replace IRFZ44N with IRLZ44N                    |
| Alexa can’t find device   | Ensure both are on the same 2.4GHz WiFi network |
| Voice commands don’t work | Use the web interface (known ESP8266 issue)     |
| No response               | Check Serial Monitor for device IP address      |

---

## Safety

* 48V can cause injury. Always disconnect power before wiring changes.
* Use the correct MOSFET. IRLZ44N (logic-level) is required for 3.3V operation.

---

## Network Requirements

* 2.4GHz WiFi (ESP8266 limitation)
* Alexa and ESP8266 must be on the same network
* Disable AP isolation in router if needed

---

## License

MIT License - Free to modify and share.

---

Do you want me to also make this formatted like a **README.txt** file (with consistent ASCII dividers), so it’s ready to drop into a project folder?
