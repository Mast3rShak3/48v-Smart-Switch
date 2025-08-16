48V LED Strip Alexa Controller
A smart home controller that enables Alexa voice control of high-power 48V LED strips using an ESP8266 (D1 Mini) and MOSFET switching circuit.


✨ Features
🎙️ Alexa Voice Control - "Alexa, turn on LED Lights"
💡 PWM Dimming - Smooth brightness control (0-100%)
🌐 Web Interface - Manual control via browser
🔧 Serial Commands - Debug and manual testing
⚡ High Power - Controls up to 192W (48V @ 4A) LED strips
🛡️ Safe Design - Isolated low/high voltage circuits


🛠️ Hardware Requirements
Bill of Materials (BOM)
Component	Quantity	Purpose	Specs	Est. Cost
ESP8266 D1 Mini	1	Main microcontroller	WiFi, 80MHz, 4MB Flash	$3-5
D1 Mini Breakout Board	1	Easy connections	Breadboard compatible	$2-3
IRLZ44N MOSFET ⚠️	1	Logic-level switching	55V, 47A, Logic Level	$1-2
220Ω Resistor	1	MOSFET gate protection	1/4W, through-hole	$0.10
48V Power Supply	1	LED strip power	4A+ rating, regulated	$15-25
48V LED Strip	1+	High-power lighting	COB or SMD, 4A max	$10-30
Terminal Blocks	3	Secure connections	5mm pitch, 10A rating	$2-5
Perfboard	1	Circuit assembly	70x90mm or larger	$2-5
Jumper Wires	1 set	Internal connections	Male-to-male, various	$2-5
USB Cable	1	Programming/power	Micro USB to USB-A	$2-5
💰 Total Estimated Cost: $40-85

⚠️ CRITICAL: Use IRLZ44N (logic-level), NOT IRFZ44N!

✅ IRLZ44N: Works with 3.3V logic
❌ IRFZ44N: Requires 10V+, causes dim output
🔌 Circuit Diagram
                    ESP8266 D1 Mini (3.3V Logic)
                    ┌─────────────────────┐
                    │                     │
                    │  ┌─────────────┐    │
                    │  │   ESP8266   │    │
                    │  │             │    │
                    │  │     D1 ─────┼────┼─── 220Ω ──┐
                    │  │             │    │            │
                    │  │    GND ─────┼────┼────────────┼─── Common GND
                    │  │             │    │            │
                    │  └─────────────┘    │            │
                    └─────────────────────┘            │
                                                       │
              48V Power Supply                         │
              ┌──────────────┐                        │
              │      +48V ───┼─────┐                  │
              │              │     │                  │
              │      GND ────┼─────┼──────────────────┘
              └──────────────┘     │                   
                                   │                   
                            48V LED Strip              
                            ┌─────────────┐           
                            │  +       -  │           
                            │  │       │  │           
                            │  │       │  │           
                            └──┼───────┼──┘           
                               │       │               
                               │       │               
                               │    ┌──▼── IRLZ44N     
                               │    │ G │  (TO-220)     
                               │    │   │               
                               └────┤ D │               
                                    │   │               
                            ────────┤ S │               
                            GND     └─────
Pin Assignments
D1 Mini Pin	Connection	Purpose
D1 (GPIO5)	220Ω → MOSFET Gate	PWM control signal
GND	MOSFET Source + 48V(-)	Common ground
3V3	Available	Future sensors
5V	Available	Future sensors
D2-D8	Available	Future expansion
🚀 Quick Start Guide
1. Clone Repository
bash
git clone https://github.com/yourusername/48v-led-alexa-controller.git
cd 48v-led-alexa-controller
2. Arduino IDE Setup
Install Arduino IDE (latest version)
Add ESP8266 Support:
File → Preferences
Additional Board Manager URLs:
http://arduino.esp8266.com/stable/package_esp8266com_index.json
Tools → Board → Boards Manager → Search "ESP8266" → Install
Install Libraries:
Sketch → Include Library → Manage Libraries
Search and install: "Espalexa by Christian Schwinne"
3. Configure WiFi
Edit src/main.cpp lines 25-26:

cpp
const char* ssid = "YOUR_WIFI_NAME";        // Your 2.4GHz network
const char* password = "YOUR_WIFI_PASSWORD"; // Your WiFi password
4. Upload Code
Connect D1 Mini via USB
Tools → Board → LOLIN(WEMOS) D1 R2 & mini
Tools → Port → Select your COM port
Click Upload button
⚡ Hardware Assembly
Step 1: Circuit Assembly
Mount D1 Mini on breakout board
Place IRLZ44N on perfboard (identify pins: Gate-Drain-Source)
Install 220Ω resistor between D1 and MOSFET gate
Add terminal blocks for external connections
Step 2: Low Voltage Wiring (Safe)
D1 Mini Breakout → Circuit:
D1 pin → 220Ω resistor → MOSFET Gate
GND pin → MOSFET Source
Step 3: High Voltage Wiring ⚠️
SAFETY: Power OFF all supplies before wiring!

48V Supply → LED Strip → MOSFET:
48V(+) → LED Strip(+)
48V(-) → MOSFET Source + D1 Mini GND
LED Strip(-) → MOSFET Drain
Step 4: Testing
USB Power Only: Test web interface
Add 48V Power: Test LED control
Alexa Discovery: "Alexa, discover devices"
🎮 Usage
Web Interface
URL: http://[device-ip]:8080


Features:

Large Control Buttons: ON/OFF with visual feedback
Dimming Presets: 25%, 50%, 75% brightness
Live Status: Current brightness display
Mobile Friendly: Responsive design
Alexa Voice Commands
bash
"Alexa, discover devices"           # Initial setup
"Alexa, turn on LED Lights"        # Full brightness
"Alexa, turn off LED Lights"       # Turn off
"Alexa, set LED Lights to 25%"     # Specific brightness
"Alexa, dim LED Lights"            # Reduce brightness
Serial Commands (Debug)
Connect USB, open Serial Monitor (115200 baud):

bash
1 or on        # Turn ON (100%)
0 or off       # Turn OFF  
dim128         # Set brightness (0-255)
test           # Run test sequence
status         # Show system info
help           # List all commands
🔧 Network Configuration
WiFi Requirements
2.4GHz Network: D1 Mini only supports 2.4GHz
Same Network: Alexa device must be on same network as D1 Mini
Network Isolation: Disable AP/Client isolation in router
Router Setup
If you have separate 2.4GHz/5GHz networks:

Option A: Connect both devices to 2.4GHz network
Option B: Enable band steering in router settings
Option C: Use guest network bridging
Port Usage
Port 80: Espalexa API (Alexa communication)
Port 8080: Manual control web interface
🚨 Safety & Troubleshooting
Safety Warnings
⚠️ HIGH VOLTAGE: 48V can cause injury

Always power off before wiring changes
Double-check polarity before connecting
Use appropriate wire gauge (16-18 AWG for 4A)
Ensure secure connections in terminal blocks
⚠️ HEAT GENERATION: MOSFET can get warm

Consider heatsink for continuous operation
Ensure adequate ventilation around circuit
Monitor temperature during initial testing
Common Issues
Problem	Cause	Solution
LED strips too dim	Wrong MOSFET (IRFZ44N)	Replace with IRLZ44N
Alexa can't find device	Network band mismatch	Put Alexa & D1 on same network
Voice commands don't work	WebServer JSON parsing	Use web interface (known issue)
No web response	Wrong IP or WiFi issue	Check Serial Monitor for IP
Erratic behavior	Power supply issues	Check all ground connections
Debug Steps
Check Serial Output: Monitor for error messages
Test Web Interface: Verify basic functionality
Measure Voltages: 3.3V at MOSFET gate when ON
Network Test: Ping device IP from computer
🚀 Future Enhancements
Planned Sensors
DHT22: Temperature & humidity monitoring
RD-03D: 24GHz radar motion detection
LDR: Automatic brightness based on ambient light
Software Features
MQTT Integration: Home Assistant compatibility
OTA Updates: Wireless code updates
Schedules: Time-based automation
Multiple Zones: Control several LED strips
Sensor Wiring Preview
cpp
// Future pin assignments
#define DHT22_PIN    D2    // Temperature/humidity
#define RADAR_RX     D3    // Motion detection RX
#define RADAR_TX     D4    // Motion detection TX
#define LDR_PIN      A0    // Light sensor (analog)
📊 Performance Specs
Metric	Specification
Max LED Power	192W (48V × 4A)
Dimming Resolution	8-bit (256 levels)
WiFi Range	50-150m (typical)
Response Time	<100ms
Power Consumption	80mA (D1 Mini only)
Operating Temp	0-70°C
🤝 Contributing
We welcome contributions! Please see our Contributing Guidelines.

Development Setup
bash
git clone https://github.com/yourusername/48v-led-alexa-controller.git
cd 48v-led-alexa-controller
# Make your changes
git checkout -b feature/your-feature
git commit -m "Add your feature"
git push origin feature/your-feature
# Open Pull Request
Reporting Issues
Use GitHub Issues
Include Serial Monitor output
Describe hardware setup
Mention software versions
📄 License
This project is licensed under the MIT License - see the LICENSE file for details.

🏆 Acknowledgments
Espalexa Library by Christian Schwinne
ESP8266 Community for excellent documentation
Arduino Team for making embedded development accessible
📞 Support
📖 Documentation: Check this README first
🐛 Bug Reports: GitHub Issues
💬 Questions: GitHub Discussions
📧 Contact: Create an issue for direct help
⭐ Star this repo if it helped you! | 🍴 Fork to customize for your needs


# 48v-Smart-Switch
