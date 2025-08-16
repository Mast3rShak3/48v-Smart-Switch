
# 48V LED Strip Alexa Controller

A smart home controller that enables Alexa voice control of high-power 5V - 55V LED strips using an ESP8266 (D1 Mini) and MOSFET switching circuit.

---

## Features

* Alexa Voice Control – Example: "Alexa, turn on LED Lights"
* PWM Dimming – Smooth brightness control (0–100%)
* Web Interface – Manual control via browser
* Serial Commands – Debug and manual testing
* High Power – Controls up to 192W (48V at 4A) LED strips
* Safe Design – Isolated low/high voltage circuits

---

## Hardware Requirements (Bill of Materials)

| Component              | Qty   | Purpose                | Specs                  | Est. Cost |
| ---------------------- | ----- | ---------------------- | ---------------------- | --------- |
| ESP8266 D1 Mini        | 1     | Main microcontroller   | WiFi, 80MHz, 4MB Flash | \$3–5     |
| D1 Mini Breakout Board | 1     | Easy connections       | Breadboard compatible  | \$2–3     |
| IRLZ44N MOSFET         | 1     | Logic-level switching  | 55V, 47A, Logic-level  | \$1–2     |
| 220Ω Resistor          | 1     | MOSFET gate protection | 1/4W                   | \$0.10    |
| 48V Power Supply       | 1     | LED strip power        | 4A+ rating, regulated  | \$15–25   |
| 48V LED Strip          | 1+    | Lighting               | COB or SMD, up to 4A   | \$10–30   |
| Terminal Blocks        | 3     | Secure connections     | 5mm pitch, 10A rating  | \$2–5     |
| Perfboard              | 1     | Circuit assembly       | 70x90mm or larger      | \$2–5     |
| Jumper Wires           | 1 set | Internal connections   | Male-to-male           | \$2–5     |
| USB Cable              | 1     | Programming/power      | Micro USB to USB-A     | \$2–5     |

Total Estimated Cost: \$40–85

Important: Use IRLZ44N (logic-level). Do not use IRFZ44N.

---

## Circuit Diagram (Pin Assignments)

ESP8266 D1 Mini Connections:

* D1 (GPIO5) → 220Ω resistor → MOSFET Gate (PWM signal)
* GND → MOSFET Source + 48V negative (common ground)
* 3V3, 5V, D2–D8 → Available for future sensors/expansion

48V Power Supply Connections:

* +48V → LED Strip Positive
* GND → MOSFET Source + D1 Mini GND
* LED Strip Negative → MOSFET Drain

---

## Quick Start Guide

1. Clone Repository

```
git clone https://github.com/yourusername/48v-led-alexa-controller.git
cd 48v-led-alexa-controller
```

2. Arduino IDE Setup

* Install Arduino IDE (latest version)
* Add ESP8266 Support:
  File → Preferences → Additional Board Manager URLs:
  [http://arduino.esp8266.com/stable/package\_esp8266com\_index.json](http://arduino.esp8266.com/stable/package_esp8266com_index.json)
  Tools → Board → Boards Manager → Search "ESP8266" → Install
* Install Library: "Espalexa by Christian Schwinne"

3. Configure WiFi
   Edit `src/main.cpp`:

```
const char* ssid = "YOUR_WIFI_NAME";       // 2.4GHz network
const char* password = "YOUR_WIFI_PASSWORD";
```

4. Upload Code

* Connect D1 Mini via USB
* Tools → Board → LOLIN(WEMOS) D1 R2 & mini
* Tools → Port → Select COM port
* Upload

---

## Hardware Assembly

Step 1: Circuit Assembly

* Mount D1 Mini on breakout board
* Place IRLZ44N on perfboard (pins: Gate–Drain–Source)
* Install 220Ω resistor between D1 pin and MOSFET gate
* Add terminal blocks for LED and power connections

Step 2: Low Voltage Wiring

* D1 pin → 220Ω resistor → MOSFET Gate
* GND pin → MOSFET Source

Step 3: High Voltage Wiring (Power Off during wiring)

* +48V → LED Strip Positive
* -48V → MOSFET Source + D1 Mini GND
* LED Strip Negative → MOSFET Drain

Step 4: Testing

* USB Power Only: Test web interface
* Add 48V Power: Verify LED control
* Alexa: Run "Discover devices"

---

## Usage

Web Interface:
Navigate to http\://\[device-ip]:8080

* ON/OFF buttons
* Dimming presets: 25%, 50%, 75%
* Current brightness display

Alexa Voice Commands:

* "Alexa, discover devices"
* "Alexa, turn on LED Lights"
* "Alexa, turn off LED Lights"
* "Alexa, set LED Lights to 25%"
* "Alexa, dim LED Lights"

Serial Commands (115200 baud):

* 1 or on = Turn ON
* 0 or off = Turn OFF
* dim128 = Brightness (0–255)
* test = Test sequence
* status = Show system info
* help = List commands

---

## Network Configuration

* Requires 2.4GHz WiFi (ESP8266 limitation)
* Alexa device must be on same network
* Disable AP/client isolation in router if needed

Ports:

* Port 80 – Espalexa API (Alexa communication)
* Port 8080 – Manual control web interface

---

## Safety and Troubleshooting

Safety Warnings:

* 48V can cause injury – always power off before wiring
* Double-check polarity before connecting
* Use correct wire gauge (16–18 AWG for 4A)
* Secure all connections
* MOSFET may get hot – add heatsink if needed

Common Issues:

* LED strips dim → Replace IRFZ44N with IRLZ44N
* Alexa not finding device → Ensure both on same 2.4GHz network
* Voice commands fail → Use web interface
* No response → Check Serial Monitor for IP, verify WiFi connection

---

## Future Enhancements

Planned Sensors:

* DHT22: Temperature/humidity
* RD-03D: 24GHz radar motion detection
* LDR: Ambient light sensing

Planned Features:

* MQTT/Home Assistant integration
* OTA updates
* Scheduling
* Multiple zone support

---

## Performance Specifications

* Max LED Power: 192W (48V × 4A)
* Dimming Resolution: 8-bit (256 levels)
* WiFi Range: 50–150m typical
* Response Time: <100ms
* Controller Power: \~80mA
* Operating Temp: 0–70°C

---

## Contributing

We welcome contributions.

```
git clone https://github.com/yourusername/48v-led-alexa-controller.git
cd 48v-led-alexa-controller
git checkout -b feature/your-feature
git commit -m "Add your feature"
git push origin feature/your-feature
```

Open a Pull Request on GitHub.

Issues can be reported via GitHub Issues with hardware details, logs, and software version.

---

## License

This project is licensed under the MIT License.

Acknowledgments:

* Espalexa Library by Christian Schwinne
* ESP8266 Community
* Arduino Team

---

Do you want me to also **reformat both of these into one combined single README.txt** (instead of two separate ones) so you have one master plain-text guide?
