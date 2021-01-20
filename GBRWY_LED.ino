// Define Pins
#define GREEN 11
#define BLUE 10
#define RED 9
#define WHITE 6
#define YELLOW 5
#define MICRO 3
#define MODE1 1
#define MODE2 2

int soundSignal = LOW;
int mode = MODE1;
int singleLEDDelay = 25;
int LEDArray[] = {GREEN, BLUE, RED, WHITE, YELLOW};
int LEDCount = sizeof(LEDArray) / sizeof(LEDArray[0]);
int next = 0;
int before = LEDCount - 1;

void setup()
{
  Serial.begin(9600);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(WHITE, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(MICRO, INPUT);
  digitalWrite(GREEN, HIGH);
  digitalWrite(BLUE, LOW);
  digitalWrite(RED, LOW);
  digitalWrite(WHITE, LOW);
  digitalWrite(YELLOW, LOW);
}

void loop()
{

  soundSignal = digitalRead(MICRO); //read the value of the digital interface 3 assigned to val

  switch (mode)
  {
  case MODE1:
    mode1();
    break;
  case MODE2:
    mode2();
    break;
  default:
    break;
  }
}

void mode1()
{
  if (soundSignal == HIGH)
  {
    for (int i = 0; i < LEDCount; i++)
    {
      digitalWrite(LEDArray[i], HIGH);
      delay(singleLEDDelay);
      digitalWrite(LEDArray[i], LOW);
    }
  }
}

void mode2()
{
  next = next % 5;
  before = before % 5;
  if (soundSignal == HIGH)
  {
    delay(singleLEDDelay);
    digitalWrite(LEDArray[before], LOW);
    digitalWrite(LEDArray[next], HIGH);
    next++;
    before++;
  }
}
