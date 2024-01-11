const int notes[] = {262, 294, 330, 349, 392};
const int ledPins[] = {2, 3, 4, 5, 6};
int selectedSequence = 99;
bool initialSetup = true;

const int sequences[][30] = {
  {3,2,1,2,3,3,3,2,2,2,3,5,5,3,2,1,2,3,3,3,3,2,2,3,2,1,5,3,4,5},
  {3,3,4,5,5,4,3,2,1,1,2,3,3,2,2,3,3,4,5,5,4,3,2,1,1,2,3,2,1,1},
  {1,2,3,1,1,2,3,1,3,4,5,3,4,5,1,2,3,1,1,2,3,1,3,4,5,3,4,5,1,1},
  {5,3,5,3,1,2,3,4,2,5,3,1,5,3,5,3,1,2,3,4,2,5,3,1,5,3,4,2,3,1},
  {3,3,3,3,3,3,3,5,1,2,3,4,4,4,4,4,3,3,3,3,3,2,3,2,5,3,3,3,3,3},
};

void playNoteAndFlash(int noteIndex) {
  tone(8, notes[noteIndex]);
  digitalWrite(ledPins[noteIndex], HIGH);
  delay(500);
  digitalWrite(ledPins[noteIndex], LOW);
  noTone(8);
}
void playSequence(int sequenceIndex) {
  for (int i = 0; i < 30; i++) {
    int note = sequences[sequenceIndex][i] - 1;
    playNoteAndFlash(note);
    delay(100);
  }
}

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 5; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  initialSetup = true;
}
void loop() {
  if (initialSetup){
    int keyVal = analogRead(A0);
    Serial.println(keyVal);
    if (keyVal == 1023) {
      selectedSequence = 0;
    } else if (keyVal >= 1 && keyVal <= 3) {
      selectedSequence = 1;
    } else if (keyVal >= 324 && keyVal <= 328) {
      selectedSequence = 2;
    } else if (keyVal >= 975 && keyVal <= 980) {
      selectedSequence = 3;
    } else if (keyVal >= 842 && keyVal <= 849) {
      selectedSequence = 4;
    } else {
      noTone(8);
    }
    if (selectedSequence != 99){
      playSequence(selectedSequence);
      initialSetup = false;
    }
  }else {
    int keyVal = analogRead(A0);
    Serial.println(keyVal);
    if (keyVal == 1023) {
      tone(8, notes[0]);
    } else if (keyVal >= 1 && keyVal <= 3) {
      tone(8, notes[1]);
    } else if (keyVal >= 324 && keyVal <= 328) {
      tone(8, notes[2]);
    } else if (keyVal >= 975 && keyVal <= 980) {
      tone(8, notes[3]);
    } else if (keyVal >= 842 && keyVal <= 849) {
      tone(8, notes[4]);
    } else {
      noTone(8);
    }
  }
}
