# Circuit Diagram & Connection Details

## 🔌 Complete Wiring Guide

### Pin Configuration Table

| Component | Pin/Terminal | Arduino Pin | Wire Color (Suggested) |
|-----------|--------------|-------------|------------------------|
| Bottom IR Sensor | VCC | 5V | Red |
| Bottom IR Sensor | GND | GND | Black |
| Bottom IR Sensor | OUT | D2 | Yellow |
| Top IR Sensor | VCC | 5V | Red |
| Top IR Sensor | GND | GND | Black |
| Top IR Sensor | OUT | D3 | Green |
| Relay Module | VCC | 5V | Red |
| Relay Module | GND | GND | Black |
| Relay Module | IN | D7 | Blue |
| LED Indicator (Optional) | Anode (+) | D13 (via 220Ω) | - |
| LED Indicator (Optional) | Cathode (-) | GND | - |

---

## 📐 Detailed Circuit Schematic

```
                    +5V Power Supply
                          |
                          |
            +-------------+-------------+
            |             |             |
            |             |             |
        [Arduino]    [IR Sensor 1]  [IR Sensor 2]
            |         (Bottom)         (Top)
            |             |             |
            |             |             |
         D2 |<------------+             |
         D3 |<-----------------------+  |
         D7 |-->[Relay]                 |
            |      |                    |
            |      NO (Normally Open)   |
            |      |                    |
            |   [Lights]                |
            |      |                    |
        GND +------+--------------------+
                   |
                 [GND]
```

---

## 🔧 Component Connection Details

### 1. Arduino Uno/Nano
```
Pin Layout:
- 5V    → Power rail (red) - Powers all 5V components
- GND   → Ground rail (black) - Common ground
- D2    → Bottom IR Sensor signal
- D3    → Top IR Sensor signal  
- D7    → Relay control signal
- D13   → Built-in LED (used as indicator)
```

### 2. IR Proximity Sensors (x2)

**Bottom Sensor Connections:**
```
IR Sensor Pin    →    Arduino Pin
─────────────────────────────────
VCC (Power)      →    5V
GND (Ground)     →    GND
OUT (Signal)     →    D2 (Digital Pin 2)
```

**Top Sensor Connections:**
```
IR Sensor Pin    →    Arduino Pin
─────────────────────────────────
VCC (Power)      →    5V
GND (Ground)     →    GND
OUT (Signal)     →    D3 (Digital Pin 3)
```

**Sensor Adjustment:**
- Most IR sensors have a potentiometer for sensitivity adjustment
- Clockwise rotation = Increase detection range
- Counter-clockwise = Decrease detection range
- Optimal range: 10-20 cm for this application

### 3. Relay Module (5V Single Channel)

```
Relay Pin        →    Connection
─────────────────────────────────
VCC              →    Arduino 5V
GND              →    Arduino GND
IN (Signal)      →    Arduino D7

Terminal Block:
COM (Common)     →    AC Power Line (Live)
NO (Normally Open) → LED Strip/Light Positive
NC (Not used)    →    Leave unconnected
```

**Relay Operation:**
- When D7 is HIGH → Relay activated → COM connects to NO → Lights ON
- When D7 is LOW  → Relay off → COM disconnected from NO → Lights OFF

### 4. LED Strip / Lighting (12V DC or AC)

**For 12V DC LED Strip:**
```
12V Power Supply (+) → Relay COM
LED Strip (+)        → Relay NO  
LED Strip (-)        → 12V Power Supply (-)
```

**For AC Bulbs (230V/110V):**
```
AC Live Wire    → Relay COM
Light Fixture   → Relay NO
AC Neutral      → Directly to Light Neutral
AC Ground       → Properly grounded
```

⚠️ **SAFETY WARNING**: AC connections must be done by qualified personnel. Ensure proper insulation and use appropriate wire ratings.

---

## 🛠️ Assembly Steps

### Step 1: Prepare Breadboard/PCB
1. Place Arduino on breadboard or mount on base
2. Arrange components for minimal wire crossing
3. Plan power and ground rails

### Step 2: Power Distribution
```
1. Connect Arduino 5V pin to positive power rail (+)
2. Connect Arduino GND pin to negative power rail (-)
3. All component VCC pins connect to (+) rail
4. All component GND pins connect to (-) rail
```

### Step 3: Sensor Connections
1. Connect Bottom IR Sensor:
   - OUT pin to Arduino D2
   - VCC to power rail (+)
   - GND to ground rail (-)

2. Connect Top IR Sensor:
   - OUT pin to Arduino D3
   - VCC to power rail (+)
   - GND to ground rail (-)

### Step 4: Relay Module
1. Connect Relay IN to Arduino D7
2. Connect Relay VCC to power rail (+)
3. Connect Relay GND to ground rail (-)

### Step 5: Load Connection (Lights)
1. Wire lighting circuit to relay terminals
2. For DC: Connect through relay COM and NO
3. For AC: Use proper wire gauge and insulation
4. Test continuity with multimeter

### Step 6: Power Supply
1. Connect 5V adapter to Arduino VIN/5V
2. For LED strip, connect separate 12V supply
3. Ensure common ground between all power supplies
4. Add fuse for safety (recommended)

---

## 🧪 Testing Procedure

### 1. Visual Inspection
- [ ] Check all connections are secure
- [ ] Verify no short circuits
- [ ] Confirm correct polarity
- [ ] Inspect solder joints (if soldered)

### 2. Power-On Test (Without Load)
```
1. Connect Arduino via USB
2. Upload test sketch
3. Open Serial Monitor (9600 baud)
4. Verify Arduino boots successfully
```

### 3. Sensor Test
```
1. Wave hand near Bottom sensor
2. Check Serial Monitor for detection message
3. Repeat for Top sensor
4. Adjust sensor sensitivity if needed
```

### 4. Relay Test (No AC Load Yet)
```
1. Trigger sensor
2. Listen for relay "click" sound
3. Check built-in LED D13 lights up
4. Verify relay LED indicator turns on
5. Wait for timeout and confirm relay turns off
```

### 5. Load Test (With Lights)
```
1. Connect low-power LED first (test load)
2. Trigger sensor
3. Verify lights turn on
4. Check for proper shutoff after timer
5. If successful, connect final lighting
```

---

## 📏 Physical Installation Guidelines

### Sensor Placement

**Bottom Sensor:**
```
Position: 10-15 cm above first step
Angle: Slightly upward (15-20°)
Height from floor: ~25-30 cm
Mounting: Adhesive tape or bracket
```

**Top Sensor:**
```
Position: 10-15 cm below last step
Angle: Slightly downward (15-20°)
Height from ceiling: ~25-30 cm
Mounting: Adhesive tape or bracket
```

### Controller Enclosure
- Mount Arduino and relay in weatherproof box
- Position near power source
- Ensure ventilation for relay heat dissipation
- Keep electronics away from moisture
- Use cable glands for wire entry

### Wire Routing
- Use cable clips along staircase wall
- Separate low-voltage (sensor) and high-voltage (AC) wires
- Use conduit for AC wiring
- Maintain minimum 5cm separation between power levels
- Secure wires to prevent tripping hazard

---

## 🔍 Troubleshooting Connection Issues

### Problem: Sensors not responding
**Check:**
- [ ] VCC connected to 5V (not 3.3V)
- [ ] GND connected properly
- [ ] Signal wire to correct Arduino pin
- [ ] Sensor LED indicator working
- [ ] Adjust sensitivity potentiometer

### Problem: Relay not clicking
**Check:**
- [ ] D7 pin connection secure
- [ ] Relay VCC has 5V power
- [ ] Relay LED indicator lights up
- [ ] Try different relay module
- [ ] Check code is uploading correctly

### Problem: Lights not turning on
**Check:**
- [ ] Relay terminals: COM and NO connections
- [ ] Power supply to lights is working
- [ ] Test lights directly without relay
- [ ] Check wire continuity with multimeter
- [ ] Verify relay is rated for load current

### Problem: Random triggering
**Check:**
- [ ] Sensor sensitivity too high
- [ ] Electromagnetic interference nearby
- [ ] Add 0.1µF capacitor across sensor VCC-GND
- [ ] Shield sensor wires
- [ ] Reposition sensors away from vibration

---

## 💡 Optimization Tips

1. **Add Pull-up Resistors**: 10kΩ resistors from D2, D3 to 5V for stability
2. **Debounce Capacitor**: 0.1µF ceramic capacitor across each sensor
3. **Relay Protection**: Add flyback diode (1N4007) across relay coil
4. **Power Filtering**: 100µF electrolytic capacitor across power supply
5. **Wire Shielding**: Use shielded cable for long sensor runs (>1m)

---

## 🎯 Alternative Configurations

### Configuration A: Single Sensor (Bottom Only)
```
- Remove top sensor connections
- Modify code to trigger on bottom sensor only
- Simpler installation
- Works for single-direction traffic
```

### Configuration B: Multiple Staircases
```
- Use multiple Arduino boards
- OR use Arduino Mega with more pins
- Replicate circuit for each staircase
- Independent operation per location
```

### Configuration C: Day/Night Mode
```
Additional Component: LDR (Light Dependent Resistor)

Connection:
LDR + 10kΩ resistor voltage divider
Connect to Arduino A0 (analog pin)
Add condition in code: if (analogRead(A0) < threshold)
System only active when dark
```

---

## 📦 Tools Required for Assembly

- Soldering iron (if making permanent connections)
- Wire strippers
- Multimeter (for testing continuity and voltage)
- Screwdriver set
- Cable ties or zip ties
- Heat shrink tubing
- Electrical tape
- Drill (for mounting holes)

---

## ⚠️ Safety Checklist

Before powering on:
- [ ] All connections double-checked
- [ ] No exposed AC wiring
- [ ] Proper wire gauge for load current
- [ ] Fuse installed in AC circuit
- [ ] Enclosure is properly closed
- [ ] No short circuits present
- [ ] Ground connection verified (for AC)
- [ ] Tested with low-power load first

---

## 📞 Need Help?

If you encounter issues with connections:
1. Take clear photos of your setup
2. Note any error messages in Serial Monitor
3. Measure voltages at key points with multimeter
4. Check continuity of all connections

**Contact:**
- Email: aryanpanwar10005@gmail.com
- Create an issue on GitHub repository

---

*Last Updated: 2023*  
*Circuit tested and verified on Arduino Uno R3*

---

## ⚠️ Disclaimer
All diagrams created by AI.
