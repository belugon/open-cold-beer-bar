int led_state[14];
int delta[14];
int run_state;

//TODO: utilize front LEDs and make it cool

void setup() {
  // put your setup code here, to run once:
}



int get_next(int id)
{
  led_state[id] = led_state[id] + delta[id];
  if (led_state[id] > 64)
  {
    led_state[id] = 64;
    delta[id] = -1;
  }
  return led_state[id];
}

int convert_intensity(int input)
{
  //range from 0 to 64
  if (input < 0)
  {
    return 0;
  }
  if (input < 32)
  {
    return input;
  }
  if (input < 48)
  {
    return 32 + ((input-32) << 1);
  }
  if (input == 64)
    return 255;
  return 64 + ((input-48) << 3);
}


void loop() {
  // put your main code here, to run repeatedly:

  //TODO: move init code to separate function
  led_state[4] = 0;
  for (int i = 5; i < 14; i++)
  {
    led_state[i] = led_state[i-1] -10;
  }
  
  for (int i = 4; i < 14; i++)
  {
    delta[i] = 1;
  }
  analogWrite(2, 255);
  analogWrite(3, 255);

  //TODO: remove/replace counter here with state change
  //TODO: use one loop to update all controllable LEDs
  //TODO: find optimal delay for main loop
  //main loop should not worry about states

  for(int i=0; i<228; i++)
  {
    for (int j=4; j < 14; j++)
    {
      analogWrite(j,convert_intensity(get_next(j)));
    }
    delay(10);
  }
}
