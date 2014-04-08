short led_state[14];
short delta[14];
short run_state;
short cycle_count;
short front_state;


void setup() {
  // put your setup code here, to run once:
  for (short i = 0; i < 14; i++)
  {
    led_state[i] = 0;
  }
  for (short i = 0; i < 14; i++)
  {
    delta[i] = 0;
  }
}

short get_next_front(short id)
{
  led_state[id] = led_state[id] + delta[id];
  if (led_state[id] > 64)
  {
    led_state[id] = 64;
    delta[id] = 0;
  }
  return led_state[id];
}

short get_next(short id)
{
  if (id > 3)
  {
    return get_next_flow(id);
  }
  else
  {
    return get_next_front(id);
  }
}

short get_next_flow(short id)
{
  led_state[id] = led_state[id] + delta[id];
  if (led_state[id] > 64)
  {
    led_state[id] = 64;
    delta[id] = -1;
  }
  if (led_state[13] < 0 && delta[13] < 0)
  {
    run_state = 0;
  }
  return led_state[id];
}

short convert_intensity(short input)
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

void init_flow()
{
  led_state[4] = 0;
  for (short i = 5; i < 14; i++)
  {
    led_state[i] = led_state[i-1] -10;
  }
  for (short i = 4; i < 14; i++)
  {
    delta[i] = 1;
  }
  run_state = 1;
  cycle_count = 0;
  
  if (front_state == 0)
  {
    front_state = 1;
    led_state[2] = 0;
    delta[2] = 1;
    led_state[3] = 0;
    delta[3] = 0;
  }
  else if (front_state == 1)
  {
    front_state = 2;
    led_state[2] = 64;
    delta[2] = -1;
    led_state[3] = 0;
    delta[3] = 0;
  }
  else if (front_state == 2)
  {
    front_state = 3;
    led_state[2] = 0;
    delta[2] = 0;
    led_state[3] = 0;
    delta[3] = 1;
  }
  else if (front_state == 3)
  {
    front_state = 0;
    led_state[2] = 0;
    delta[2] = 0;
    led_state[3] = 64;
    delta[3] = -1;
  }
}


void loop() {
  // put your main code here, to run repeatedly:
  init_flow();

  //TODO: find optimal delay for main loop

  while(run_state)
  {
    cycle_count++;
    for (short j=0; j < 14; j++)
    {
      analogWrite(j,convert_intensity(get_next(j)));
    }
    delay(10);
  }
}
