int smoothing(int a)
{
  //-----------------------SMOOTHING----------------------------------------------------
  total= total - readings[index];       // subtract the last reading        
  readings[index] = a;        // get analog value
  total= total + readings[index];     // add the reading to the total
  index = index + 1;                 // advance to the next position in the array  

  if (index >= numReadings)      // if we're at the end of the array...
  {
    index = 0;       // ...wrap around to the beginning: 
  }
  average = total / numReadings;           // calculate the average
  return average;    // return smoothed value
  delay(1);        // delay in between reads for stability
  //------------------------------------------------------------------------------------
}

