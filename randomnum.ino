const int buttonPin = 2;
int buttonState;
int lastButtonState = HIGH;
int guess = 1;
int randomNumber;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
unsigned long buttonPressStart = 0;
bool checking = false;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
  randomSeed(analogRead(A0)); // Use analog pin noise as random seed
  randomNumber = random(1, 10); // Random number between 1 and 9
  Serial.println("Guess the number between 1 and 9");
}

void loop() {
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // If button was pressed
    if (reading == LOW && lastButtonState == HIGH) {
      buttonPressStart = millis();
    }

    // If button is held
    if (reading == LOW && (millis() - buttonPressStart > 1000) && !checking) {
      checking = true;
      Serial.print("You guessed: ");
      Serial.println(guess);

      if (guess == randomNumber) {
        Serial.println("Correct! 🎉 Generating new number...");
        delay(1000);
        randomNumber = random(1, 10);
        Serial.println("New Game: Guess the number between 1 and 9");
        guess = 1;
      } else if (guess < randomNumber) {
        Serial.println("Too Low!");
      } else {
        Serial.println("Too High!");
      }
    }

    // Short press to increase guess
    if (reading == HIGH && lastButtonState == LOW && !checking) {
      guess++;
      if (guess > 9) guess = 1;
      Serial.print("Current Guess: ");
      Serial.println(guess);
    }

    // Button released after checking
    if (reading == HIGH && checking) {
      checking = false;
    }
  }

  lastButtonState = reading;
}
