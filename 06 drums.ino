#define MAXPADS 4

int STAGE0 = 8;
int STAGE1 = 12;
int speakerOut = 12;
int val = 0 ;

int piezoStart[] = {0,0,0,0};
int piezoIn[] = {0,1,2,3};
int piezoState[] = {0,0,0,0};

void setup() {
  pinMode(speakerOut, OUTPUT);
  for (int i=0; i<MAXPADS; i++) {
      pinMode(piezoIn[i], INPUT);
  }
  //  Set MIDI baud rate:
  Serial.begin(31250);
  delay(100);
  midiInit(); 
}

void playDrum(int drum) {
   switch (drum) {
     case 0:
     //break;
       noteOn(0x99, 0x24, 0x7F); delay(200); break;     
     case 1:
       break;
     //noteOn(0x99, 0x24, 0x7F); delay(100); break;
     case 2:
       // break;
     noteOn(0x99, 0x31, 0x7F); delay(100); break;
     case 3:
     noteOn(0x99, 0x28, 0x7F); delay(200); break;
     case 4:
     break;
     //noteOn(0x99, 0x33, 0x7F); delay(100); break;     
     case 5:
     break;
     //noteOn(0x99, 0x33, 0x7F); delay(100); break;     
  }
}

//  plays a MIDI note.  Doesn't check to see that
//  cmd is greater than 127, or that data values are  less than 127:
void noteOn(int cmd, int pitch, int velocity) {
   Serial.write(cmd);
   Serial.write(pitch);
   Serial.write(velocity);
}

void midiInit() {
   //Serial.write(0xC0);
   //Serial.write(0x7F);
   //delay(100);
   //Serial.write(0xC0);
   //Serial.write(0xC0);
   //delay(100);
}

void loop(){
  
  STAGE0 = abs(analogRead(5) / 64);
  STAGE1 = abs(STAGE0 * 1.5);
  
  for (int i=0; i<MAXPADS; i++) {
     val = analogRead(piezoIn[i]);
     if(( val >= STAGE0) && (piezoState[i] == false)) {
       piezoState[i] = true;
       piezoStart[i] = val;
     } else if ( ((val - piezoStart[i]) > STAGE1) && (piezoState[i] == true)) {
       piezoState[i] = false;
       playDrum(i);   
     } else if ((piezoState[i] == true) && ( val < STAGE0)) {
       piezoState[i] = false;
     }
   }
   delay(1);
}


