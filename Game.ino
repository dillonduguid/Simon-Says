//

#include "notes.h" // C document includes all defined note frequencies used throughout 

int ledPins[5] = {2, 3, 4, 5, 7}; //array of pins used for all LED output
int buzzerPin = 9; // pin used for buzzer input

int const delayVal = 200; //a value that will stay the same, used to determine how long in milliseconds, something should be delayed

long randomNumber; //integer stores random number

int difficulty = 5; //integer of difficulty to be used

int sensors[5]; //array of sensor inputs


//definition of methods, including neccesary paramters to be used.
void getSequence(int sequence[]); 
void playSequence(int note, int sequence[]);
void keyInput(int inputs[]);
void playNote(int note);
void compare(int sequence[], int inputs[]);


//setup runs once, declares outputs, etc
void setup() {

  Serial.begin(9600); //set rate of data in baud 
  randomSeed(analogRead(A5)); //initialise pseudorandom number generator on analog pin A5

  //initialize each ledPin in the ledPins array as an output pin
  for (int i = 0; i < 5; i++) { 
    pinMode(ledPins[i], OUTPUT);
  }

}

//loop function runs until program is stopped. This is used as a game loop
void loop() {

  //initialize sequence and inputs arrays to allow a particular ammount of elements, determined by difficulty variable
  int sequence[difficulty];
  int inputs[difficulty];

  //getSequence function is called, passing in the sequence array as only parameter
  getSequence(sequence);

  //keyInput function is called, passing in inputs array as parameter
  keyInput(inputs);

  //compare function is called, passing in sequence and inputs array as parameters
  compare(sequence, inputs);

}

/*getSequence function returns nothing, recieves array of integers 'sequence'.
  Function will get a single sequence of random numbers, then calls playSequence for each note in the sequence*/
void getSequence(int sequence[]) {
  
  bool repeat = true; //boolean repeat assigned value true

  //conditional loop runs until repeat is false
  while (repeat) {
    for (int i = 0; i < difficulty; i++) { //fixed loop repeats while i < difficulty
      randomNumber = random(0, 5); //randomNumber is assigned a random value between 0 and 5
      sequence[i] = randomNumber; //current element in sequence assigned current randomNumber value;
      playSequence(i, sequence); //playSequence function called, passes current i element in sequence and the sequence itself
    }
    repeat = false; //end while loop
  }

}

/*playSequence function returns nothing, recieves current note to be played and sequence to represent the note.
  Function will simply take in a note, compare it to an integer, and call the playNote function with a specific parameter.*/ 
void playSequence(int note, int sequence[]) {

  //determine if the current note in the sequence equates to an integer, then call a function to play the note assigned to that integer.
  if (sequence[note] == 0) {
    playNote(NOTE_C4);
  }
  else if (sequence[note] == 1) {
    playNote(NOTE_D4);
  }
  else if (sequence[note] == 2) {
    playNote(NOTE_E4);
  }
  else if (sequence[note] == 3) {
    playNote(NOTE_F4);
  }
  else if (sequence[note] == 4) {
    playNote(NOTE_G4);
  }

}

/*keyInput method returns nothing, recieves an array of integers 'inputs'
  function waits for the correct user input, then plays the note. This ends when the correct number of inputs are met*/
void keyInput(int inputs[]) {

  int threshold = 10; //threshold to be met for sensor input to be recieved
  int inputNumber = 0; //number of inputs 

  //conditional loops runs until the neccesay number of inputs meets the difficulty 
  while (inputNumber < difficulty) {

    /*For each sensor, check if there is an input from the respective pin.
      Based on the input, assign the current element in the inputs array to an integer,
      increment the number of inputs and play the respective note for that sensor.*/  
      
    sensors[0] = analogRead(A0); //assign reading from analogPin to respective index in sensors array
    if (sensors[0] > threshold) { //if the reading value is greater than the threshold
      inputs[inputNumber] = 0; //assign current inputs element to 0
      inputNumber++; //increment inputNumber

      playNote(NOTE_C4); //call playNote function and pass the specific note to be played.
    }

    sensors[1] = analogRead(A1);
    if (sensors[1] > threshold) {
      inputs[inputNumber] = 1;
      inputNumber++;

      playNote(NOTE_D4);
    }

    sensors[2] = analogRead(A2);
    if (sensors[2] > threshold) {
      inputs[inputNumber] = 2;
      inputNumber++;

      playNote(NOTE_E4);
    }

    sensors[3] = analogRead(A3);
    if (sensors[3] > threshold) {
      inputs[inputNumber] = 3;
      inputNumber++;

      playNote(NOTE_F4);
    }

    sensors[4] = analogRead(A4);
    if (sensors[4] > threshold) {
      inputs[inputNumber] = 4;
      inputNumber++;

      playNote(NOTE_G4);
    }
  }

}


/*playNote method returns nothing, recieves integer 'note' as parameter.
  Function will */
void playNote(int note) {

  if (note == NOTE_C4) {
    tone(buzzerPin, NOTE_C4, delayVal);
    digitalWrite(ledPins[0], HIGH);
    delay(delayVal + 300);
    digitalWrite(ledPins[0], LOW);
  }
  else if (note == NOTE_D4) {
    tone(buzzerPin, NOTE_D4, delayVal);
    digitalWrite(ledPins[1], HIGH);
    delay(delayVal + 300);
    digitalWrite(ledPins[1], LOW);
  }
  else if (note == NOTE_E4) {
    tone(buzzerPin, NOTE_E4, delayVal);
    digitalWrite(ledPins[2], HIGH);
    delay(delayVal + 300);
    digitalWrite(ledPins[2], LOW);
  }
  else if (note == NOTE_F4) {
    tone(buzzerPin, NOTE_F4, delayVal);
    digitalWrite(ledPins[3], HIGH);
    delay(delayVal + 300);
    digitalWrite(ledPins[3], LOW);
  }
  else if (note == NOTE_G4) {
    tone(buzzerPin, NOTE_G4, delayVal);
    digitalWrite(ledPins[4], HIGH);
    delay(delayVal + 300);
    digitalWrite(ledPins[4], LOW);
  }

}

void compare(int sequence[], int inputs[]) {

  int counter = 0;
  int i = 0;

  while (i < difficulty) {
    if (sequence[i] == inputs[i]) {
      counter++;
      Serial.print("Input: ");
      Serial.println(inputs[i]);
      Serial.print("Sequence: ");
      Serial.println(sequence[i]);
    }
    else{
      Serial.print("Input: ");
      Serial.println(inputs[i]);
      Serial.print("Sequence: ");
      Serial.println(sequence[i]);
    }
    i++;
  }

  if (counter == difficulty) {
    win();
    difficulty++;
  }
  else {
    lose();
    difficulty = 5;
  }
}

void win() {

  int winDelay = 100;

  delay(100);

  tone(buzzerPin, NOTE_A5);
  delay(50);
  tone(buzzerPin, NOTE_B5);
  delay(50);
  tone(buzzerPin, NOTE_C5);
  delay(50);
  tone(buzzerPin, NOTE_B5);
  delay(50);
  tone(buzzerPin, NOTE_C5);
  delay(50);
  tone(buzzerPin, NOTE_D5);
  delay(50);
  tone(buzzerPin, NOTE_C5);
  delay(50);
  tone(buzzerPin, NOTE_D5);
  delay(50);
  tone(buzzerPin, NOTE_E5);
  delay(50);
  tone(buzzerPin, NOTE_D5);
  delay(50);
  tone(buzzerPin, NOTE_E5);
  delay(50);
  tone(buzzerPin, NOTE_E5);
  delay(50);


  tone(buzzerPin, NOTE_E5, 200);
  delay(winDelay);

  Serial.print("Congrats");
  delay(1000);
}

void lose() {
  delay(1000);

  tone(buzzerPin, NOTE_G4);
  delay(250);
  tone(buzzerPin, NOTE_C4, 300);
  delay(500);

  Serial.print("Unlucky my dude");
  delay(1000);
}



