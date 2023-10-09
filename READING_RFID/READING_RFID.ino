int count = 0;                                          // count = 0
char input[12];                                         // character array of size 12 
boolean flag = 0;                                       // flag =0
void setup()
{
   Serial.begin(9600);                                  // begin serial port with baud rate 9600bps
}
void loop()
{
   if(Serial.available())
   {
      count = 0;
      while(Serial.available() && count < 12)          // Read 12 characters and store them in input array
      {
         input[count] = Serial.read();
         count++;
         delay(5);
      }
      Serial.print(input);                             // Print RFID tag number 
      
      if((input[0] ^ input[2] ^ input[4] ^ input[6] ^ input[8] == input[10]) && 
         (input[1] ^ input[3] ^ input[5] ^ input[7] ^ input[9] == input[11]))
            Serial.println("No Error");
      else
            Serial.println("Error");      
   }
}