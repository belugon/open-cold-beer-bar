open-cold-beer-bar
==================

the COLD BEER bar

The bar is outfit with 2 programmable light strips in the front and 10 LED clusters on the top. 
The integers that control these are:

byte front_even_LED = 2;// even front lights 
byte front_odd_LED = 3; //odd front lights
byte left1 = 4; //blue left side
byte left2 = 5; //red left side
byte left3 = 6; //yellow left side
byte left4 = 7; //green left side
byte left5 = 8; //white left side
byte right1 = 9; //blue right side
byte right2 = 10; //green right side
byte right3 = 11; //red light side
byte right4 = 12; //white right side
byte right5 =  13; //yellow right side

The bar also has two light sensors on A1 and A2. Note these must be int in order to read between 0 and 1023

int var1=analogRead(A1); //left hand side
int var2=analogRead(A2); //right hand side 



PROGRAMS:
--------------------------------------------------------------------------------------

1. //make the front LEDs glow
if (state1 == 0)
{
bright1 = bright1 + 1;
bright2 = bright2 - 1;
      if (bright1 > 249)
      {
        state1=1;
      }
}

if (state1 == 1)
{
bright1 = bright1 - 1;
bright2 = bright2 + 1;

      if (bright1 < 11)
      {
        state1=0;
      }
}

analogWrite(front_even_LED,bright1);
analogWrite(front_odd_LED,bright2);



-------------------------------------------------------------------------------------

2. // make the top LEDs glow

nt led_state[14];
int delta[14];
int run_state;

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

  for(int i=0; i<228; i++)
  {
    for (int j=4; j < 14; j++)
    {
      analogWrite(j,convert_intensity(get_next(j)));
    }
    delay(10);
  }
}


--------------------------------------------------------------------------------------
