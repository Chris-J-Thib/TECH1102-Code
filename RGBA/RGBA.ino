using namespace std;

int pinR=5;
int pinG=4;
int pinB=3;

int RGBA[4];
int count;

String input, out;

void setup(){
  Serial.begin(9600);
  pinMode(pinR, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(pinB, OUTPUT);
}

void loop(){
  Serial.println("Enter R G B A");
  while (Serial.available() == 0);
  input = Serial.readStringUntil("\n");
  input = input.substring(0,input.indexOf("\n"))+ "%\n";
  Serial.println(input);
  count = 0;
  while (input.indexOf(" ")!=-1){
    RGBA[count] = input.substring(0, input.indexOf(" ")).toInt();
    count++;
    input = input.substring(input.indexOf(" ")+1);
  }
  RGBA[count] = input.toInt();

  for(int i = 0; i < 4; i++){
    RGBA[i] = (RGBA[i] * RGBA[3])/100;
  }

  analogWrite(pinR, RGBA[0]);
  analogWrite(pinG, RGBA[1]);
  analogWrite(pinB, RGBA[2]);

}