void breathingRate(int /*&*/breaths)
{
  
  int nextBreathes;    //MAKE NEW INT FOR BREATHS SO YOU CAN CANCEL OUT THE FULL TALLY AFTER MEASURE PERIOD
  unsigned long currentMillis = millis();

  if(currentMillis - measureStart > measurePeriod) 
  {
    measureStart = currentMillis;       // save the last time inhaled
    
    float rate = measurePeriod/breaths;
    breaths = 0;
   
    if (rate >= fastest && rate <= faster)
    {
    analogWrite(r, brightness);
    analogWrite(g, 0);
    analogWrite(b, 0);
    }
    
    if (rate >= faster && rate <= fast)
    {
    analogWrite(r, brightness);
    analogWrite(g, brightness/2);
    analogWrite(b, brightness/2);
    }
    
    if (rate >= fast && rate <= slow)
    {
    analogWrite(r, brightness);
    analogWrite(g, brightness);
    analogWrite(b, brightness);
    }
    
    if (rate >= slow && rate <= slower)
    {
    analogWrite(r, brightness/2);
    analogWrite(g, brightness/2);
    analogWrite(b, brightness);
    }
    
    if (rate >= slower && rate <= slowest)
    {
    analogWrite(r, 0);
    analogWrite(g, 0);
    analogWrite(b, brightness);
    }
    
  }
}

