// Define the pins for the LEDs
const int redLedPin = 9;
const int greenLedPin = 10;
const int blueLedPin = 11;

// Define the analog pin for the ORP sensor
const int orpSensorPin = A0;
// Analog input pin for copper electrode (ORP) 
const float voltageReference = 5.0; 
// Voltage reference for Arduino (5V) 
const float conversionFactor = 100.0; 

void setup() {
  // Initialize the serial communication
  Serial.begin(9600);

  // Set the LED pins as outputs
  pinMode(orpSensorPin, INPUT); 
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);
}

void loop() 
{
  // Read the analog voltage from the ORP sensor
  int sensorValue = analogRead(orpSensorPin);
  
  // Convert the analog voltage to ORP value (you may need to adjust this based on your sensor)
  float orpValue = map(sensorValue, 0, 1023, 0, 5000); // Assuming sensor range is 0-1000 mV
    
  // Read analog voltage from copper electrode (ORP) 
  int rawORP_Copper = analogRead (orpSensorPin) ; 
  // Voltage from silver electrode (ORP) is considered OV (GND) 
  // Convert raw analog value to voltage value for copper electrode 
  float voltage_Copper = (float)rawORP_Copper / 1023.0 * voltageReference; 
  // Calculate voltage difference between copper and silver electrodes 
  float voltageDifference = voltage_Copper - 0.0; 
  // Silver electrode is GND
  // Convert voltage difference to pm of salt using the conversion factor 
  float ppmValue = voltageDifference * conversionFactor; 
  // Print ppm value and voltage to serial monitor for debugging 
 Serial.print("Voltage Difference: "); 
  Serial.print(voltageDifference); 
  Serial.print(" V\tPPM Value: "); 
  Serial.println(ppmValue); 
  
  // Wait for a short delay before taking the next reading
  delay(500); // Adjust delay time as needed
  // Map the ORP value to the range of each LED
  // Control LEDs based on ppm range 
  if (ppmValue >= 0 && ppmValue <= 799) 
  { 
    digitalwrite(greenLED, LOW); 
    // Turn on green LED 
    digitalwrite(yellowLED, LOW); 
    // Turn off yellow LED
    digitalwrite(redLED, LOW); 
    // Turn off red LED 
  } else if (ppmValue >= 800 && ppmValue <= 1499)
    digitalWrite(greenLED, HIGH);
    // Turn off green LED 
    digitalwrite(yellowLED, LOW); 
    // Turn on yellow LED 
    digitalwrite(redLED, LOW); 
    // Turn off red LED 
  } else if (ppmValue >= 1500 && ppmValue <= 5000)
    digitalwrite(greenLED, LOW); 
    // Turn off green LED 
    digitalwrite(yellowLED, LOW); 
    // Turn off yellow LED 
    digitalwrite(redLED, HIGH); 
    // Turn on red LED 
  } 
  delay(1000); 
}