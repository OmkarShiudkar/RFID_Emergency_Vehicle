char input[12] = "";  
char tag1[13] = "5900D5187BEF";
unsigned long lastTagScanTime = 0;

const int light1_red = 8;
const int light1_green = 9;
const int light2_red = 10;
const int light2_green = 11;
const int light3_red = 12;
const int light3_green = 13;
const int light4_red = 6;
const int light4_green = 7;

void setup()
{
   Serial.begin(9600);  
   pinMode(light1_red, OUTPUT); 
   pinMode(light1_green, OUTPUT); 
   pinMode(light2_red, OUTPUT); 
   pinMode(light2_green, OUTPUT); 
   pinMode(light3_red, OUTPUT); 
   pinMode(light3_green, OUTPUT); 
   pinMode(light4_red, OUTPUT); 
   pinMode(light4_green, OUTPUT); 

   regularTrafficFlow();  // Set the lights to the default state at startup
}

void loop()
{
    if(Serial.available())
    {
      int count = 0;
      delay(100); // Allow buffer to fill up
      while(Serial.available() && count < 12)  // Read 12 characters and store them in input array
      {
        input[count] = Serial.read();
        count++;
      }
      input[count] = '\0';  // Null terminate the string

      boolean isMatch = true;
      for(int i = 0; i < 12; i++)
      {
        if(input[i] != tag1[i])
        {
          isMatch = false;
          break;
        }
      }

      if(isMatch)
      {
        emergencyVehicleApproaching();
        Serial.println(input);
      }
      else
      {
        Serial.println("Unauthorized Tag");
      }
      
      // Clear the input for next reading
      for(int i = 0; i < 12; i++)
      {
        input[i] = 0;
      }
    }
     if (lastTagScanTime > 0 && millis() - lastTagScanTime >= 25000) 
    {
        regularTrafficFlow();
        lastTagScanTime = 0; // Reset the timer
    }
}

void regularTrafficFlow()
{
  digitalWrite(light1_green, LOW);
  digitalWrite(light1_red, HIGH);
  digitalWrite(light3_green, LOW);
  digitalWrite(light3_red, HIGH);
  
  digitalWrite(light4_red, LOW);
  digitalWrite(light4_green, HIGH);
  digitalWrite(light2_red, LOW);
  digitalWrite(light2_green, HIGH);
}

void emergencyVehicleApproaching()
{
  digitalWrite(light1_green, HIGH);
  digitalWrite(light1_red, LOW);
  digitalWrite(light3_green, HIGH);
  digitalWrite(light3_red, LOW);

  digitalWrite(light4_red, HIGH);
  digitalWrite(light4_green, LOW);
  digitalWrite(light2_red, HIGH);
  digitalWrite(light2_green, LOW);

  Serial.println("Emergency Vehicle Approaching");
  Serial.println("All signals changed");
  lastTagScanTime = millis();
}
