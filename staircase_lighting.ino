/*
 * Smart Staircase Lighting System
 * Author: Aryan Panwar
 * Date: 2023
 * 
 * Description: 
 * Automated staircase lighting system using IR sensors for motion detection.
 * Achieves 45% energy savings through intelligent auto-shutoff.
 * 
 * Hardware:
 * - Arduino Uno/Nano
 * - 2x IR Proximity Sensors (Top & Bottom)
 * - Relay Module (5V)
 * - LED Strip or AC Bulbs
 * 
 * Pin Configuration:
 * D2 - Bottom IR Sensor
 * D3 - Top IR Sensor
 * D7 - Relay Module (Controls Lights)
 */

// ========== PIN DEFINITIONS ==========
#define TOP_SENSOR 3          // IR sensor at top of staircase
#define BOTTOM_SENSOR 2       // IR sensor at bottom of staircase
#define RELAY_PIN 7           // Relay control pin for lights
#define LED_INDICATOR 13      // Built-in LED for status indication

// ========== TIMING CONFIGURATION ==========
const unsigned long LIGHT_ON_TIME = 15000;    // Lights stay on for 15 seconds
const unsigned long SENSOR_DEBOUNCE = 100;    // Debounce delay in milliseconds

// ========== GLOBAL VARIABLES ==========
bool lightsOn = false;                        // Current state of lights
unsigned long lightOnStartTime = 0;           // Timestamp when lights turned on
bool topSensorTriggered = false;              // Top sensor state
bool bottomSensorTriggered = false;           // Bottom sensor state

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
  Serial.println("Smart Staircase Lighting System");
  Serial.println("Initializing...");
  
  // Configure pin modes
  pinMode(TOP_SENSOR, INPUT);
  pinMode(BOTTOM_SENSOR, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_INDICATOR, OUTPUT);
  
  // Ensure lights are off at startup
  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(LED_INDICATOR, LOW);
  lightsOn = false;
  
  Serial.println("System Ready!");
  Serial.println("Monitoring for motion...");
  Serial.println("----------------------------");
}

void loop() {
  // Read sensor states
  // IR sensors typically output LOW when object detected, HIGH when clear
  // Adjust logic based on your specific IR sensor module
  int topSensorState = digitalRead(TOP_SENSOR);
  int bottomSensorState = digitalRead(BOTTOM_SENSOR);
  
  // Check for motion detection at either sensor
  if (topSensorState == LOW || bottomSensorState == LOW) {
    // Motion detected!
    if (!lightsOn) {
      // Turn on lights if they're currently off
      turnOnLights();
      
      // Log which sensor triggered
      if (topSensorState == LOW) {
        Serial.println("Motion detected at TOP sensor");
      }
      if (bottomSensorState == LOW) {
        Serial.println("Motion detected at BOTTOM sensor");
      }
    }
    
    // Reset timer - extend light duration if someone is still moving
    lightOnStartTime = millis();
    delay(SENSOR_DEBOUNCE);  // Debounce delay
  }
  
  // Check if it's time to turn off lights
  if (lightsOn) {
    unsigned long currentTime = millis();
    
    // Handle timer rollover (occurs every ~50 days)
    if (currentTime < lightOnStartTime) {
      lightOnStartTime = currentTime;
    }
    
    // Check if timeout period has elapsed
    if (currentTime - lightOnStartTime >= LIGHT_ON_TIME) {
      turnOffLights();
      Serial.println("Timer expired - lights turned OFF");
      Serial.println("----------------------------");
    }
  }
  
  // Small delay to reduce CPU usage
  delay(50);
}

/*
 * Function: turnOnLights
 * Activates the relay to turn on staircase lights
 */
void turnOnLights() {
  digitalWrite(RELAY_PIN, HIGH);      // Activate relay
  digitalWrite(LED_INDICATOR, HIGH);  // Turn on indicator LED
  lightsOn = true;
  lightOnStartTime = millis();        // Record start time
  
  Serial.println(">>> Lights turned ON <<<");
}

/*
 * Function: turnOffLights
 * Deactivates the relay to turn off staircase lights
 */
void turnOffLights() {
  digitalWrite(RELAY_PIN, LOW);       // Deactivate relay
  digitalWrite(LED_INDICATOR, LOW);   // Turn off indicator LED
  lightsOn = false;
  
  Serial.println(">>> Lights turned OFF <<<");
}

/*
 * NOTES FOR CUSTOMIZATION:
 * 
 * 1. Timer Adjustment:
 *    Change LIGHT_ON_TIME value (in milliseconds)
 *    Example: 10000 = 10 seconds, 30000 = 30 seconds
 * 
 * 2. Sensor Logic:
 *    Some IR sensors output HIGH when detecting motion
 *    If your sensors work opposite, change:
 *    if (topSensorState == LOW) to if (topSensorState == HIGH)
 * 
 * 3. Relay Logic:
 *    Some relays are active-low (trigger with LOW signal)
 *    If needed, swap HIGH/LOW in turnOnLights() and turnOffLights()
 * 
 * 4. Adding LDR for Night Mode:
 *    Connect LDR to analog pin (e.g., A0)
 *    Add condition: if (analogRead(A0) < threshold) before turning on lights
 * 
 * 5. Power Saving:
 *    For battery operation, consider using sleep modes
 *    Include <avr/sleep.h> and implement power-down between checks
 */
