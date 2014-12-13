
//-----------------------COMMUNICATION(verifying connection)------------------------------
boolean configureRadio() 
{
  Serial.flush(); 
  Serial.print("+++");    // put the radio in command mode
  delay(100);
  String ok_response = "OK\r";    // the response we expect
  String response = String("");    // Read the text of the response into the response variable 
  while (response.length() < ok_response.length()) 
  {
    if (Serial.available() > 0) 
    {
      response += (char) Serial.read(); 
    }
  }
  // If we got the right response, configure the radio and return true. 
  if (response.equals(ok_response)) 
  {
    Serial.print("ATAP1\r"); // Enter API mode 
    delay(100);
    Serial.print("ATCN\r"); // back to data mode return true;
  } 
  else 
  {
    return false; // This indicates the response was incorrect. 
  }
}
//-------------------------------------------------------------------------------------
