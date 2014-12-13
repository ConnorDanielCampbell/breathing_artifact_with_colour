// reads stretch sensor from an XBee API frame
// smoothes and maps value
// tracks breathing rate
// sets brightness of RGB LED accordingly
// sets colour of RGB LED accordingly

// (c) connor campbell 2014
// www.connor.xyz

// reference code:
// - XBeeAnalogReceiveSeries1 by Michael Margolis
// - Smoothing by David A. Mellis and Tom Igoe


//-----------------------SMOOTHING AND MAPPING
const int numReadings = 2;     // number of values in series to average out (lower=faster output, higher=smoother)
int readings[numReadings];      // the readings from the analog input
int index = 0;                  // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average
const int highest = 1023;       // highest sensor value for inhale (as per calibration)
const int lowest = 0;           // lowest sensor value for exhale (as per calibration)

//-----------------------BREATHING RATE
const int thresholdMax = 600;    // every inhale must surpass this number
const int thresholdMin = 400;    // every exhale must surpass this number
unsigned long interval = 700;      // shortest possible breath (milliseconds)
unsigned long measurePeriod = 5000;     // period after wish breathing rate will be assesed 
long previousMillis = 0;        // will store last time threshold was hit
long measureStart = 0;        // will store last time threshold was hit
int breathCounter = 0;          // counts each inhale and exhale (each full breath = 2)
const int fastest = 1000;
const int faster = fastest + 200;
const int fast = faster + 200;
const int slow = fast + 200;
const int slower = slow + 200;
const int slowest = slower + 200;

//------------------------LED
const int sensorPin = A0;        // pin that the sensor is attached to
const int r = 9;
const int g = 10;
const int b = 11;
const int darkest = 0;           // darkest LED value according to biggest exhale
const int brightest = 255;       // brightest LED value according to bieggest inhale

int brightness;


void setup() {

  Serial.begin(9600);    // start Serial
  configureRadio();      // check the return value if you need error handling

  //-----------------------set up LED pins
    pinMode(r, OUTPUT);
    pinMode(g, OUTPUT);
    pinMode(b, OUTPUT);

  //-----------------------smoothing stuff
  for (int thisReading = 0; thisReading < numReadings; thisReading++)
  {
    readings[thisReading] = 0;    // initialize all the readings to 0
  }

}

void loop() {

  if (Serial.available() >= 14)     // Wait until we have a mouthful of data 
  {
    if (Serial.read() == 0x7E)     // Start delimiter of a frame
    {
      for (int i = 0; i < 10; i++)     // Skip over the bytes in the API frame we don't care about 
      {  
        Serial.read(); 
      }
      int analogHigh = Serial.read();  // The next two bytes are the high and low bytes of the sensor reading
      int analogLow = Serial.read();
      int analogValue = analogLow + (analogHigh * 256);    // Scale the value to the Arduino PWM range 
      int valueConstrained = constrain(analogValue, lowest, highest);      //constrain sensor value 
      //Serial.print("analogValue = ");
      //Serial.print(analogValue);
      //Serial.print(", ");
      int valueSmoothed = smoothing(valueConstrained);    // smooth value with smoothing() function
      brightness = map(valueSmoothed, lowest, highest, darkest, brightest);  //map sensor value
      //Serial.print("valueMapped = ");
      //Serial.print(valueMapped);
      //Serial.print(", ");

      //int brightness = smoothing(valueMapped);    //smooth sensor value
      //Serial.print("brightness = ");
      //Serial.println(brightness);

      //------------------------------------------------------------------BREATHING RATE
      unsigned long currentMillis = millis();
      
      if(currentMillis - previousMillis > interval) 
      {
        previousMillis = currentMillis;       // save the last time inhaled
        
        if(valueSmoothed > thresholdMin && valueSmoothed < thresholdMax)
        {
          breathCounter++;
        }
      }
      breathingRate(breathCounter);
      //---------------------------------------------------------------------------------
    }
  }
}










