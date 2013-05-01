// This program controls a stepper motor and a camera remote shutter control
// See http://roxen.github.io/360-capture/

#define STEPS_PER_REV 6400 // 400 physical motor steps * 16 substeps from Big EasyDriver
#define NOF_IMAGES 36
int STEPS_PER_IMAGE = STEPS_PER_REV / NOF_IMAGES;

#define TURN_CLOCKWISE_BTN_PIN 2
#define TURN_COUNTERCLOCKWISE_BTN_PIN 3
#define TAKE_PHOTO_BTN_PIN 4
#define RUN_SEQUENCE_BTN_PIN 5

#define CAMERA_SHUTTER_PIN 7

#define STEPPER_DIR_PIN 8
#define STEPPER_STEP_PIN 9

#define STEPPER_DELAY 20 // Adjust to set rotation speed

void setup() {
  pinMode(TURN_CLOCKWISE_BTN_PIN, INPUT);
  pinMode(TURN_COUNTERCLOCKWISE_BTN_PIN, INPUT);
  pinMode(TAKE_PHOTO_BTN_PIN, INPUT);
  pinMode(RUN_SEQUENCE_BTN_PIN, INPUT);

  pinMode(CAMERA_SHUTTER_PIN, OUTPUT);
  digitalWrite(CAMERA_SHUTTER_PIN, LOW);

  pinMode(STEPPER_DIR_PIN, OUTPUT);
  pinMode(STEPPER_STEP_PIN, OUTPUT);
}

void loop() {
  if (digitalRead(TURN_CLOCKWISE_BTN_PIN) == HIGH) {
    step(1);
  }

  if (digitalRead(TURN_COUNTERCLOCKWISE_BTN_PIN) == HIGH) {
    step(-1);
  }

  if (digitalRead(TAKE_PHOTO_BTN_PIN) == HIGH) {
    take_photo();
  }

  if (digitalRead(RUN_SEQUENCE_BTN_PIN) == HIGH) {
    for (int i = 0; i < NOF_IMAGES; i++) {
      take_photo();
      delay(100); // Adjust to not move until picture is taken
      step(STEPS_PER_IMAGE);
      delay(900); // Adjust to avoid camera buffer overload and let platform settle in new position
    }
  }
}

void take_photo() {
  digitalWrite(CAMERA_SHUTTER_PIN, HIGH);
  delay(20);
  digitalWrite(CAMERA_SHUTTER_PIN, LOW);
}

void step(int steps) {
  if (steps > 0) {
    digitalWrite(STEPPER_DIR_PIN, HIGH);
  } 
  else {
    digitalWrite(STEPPER_DIR_PIN, LOW);
  }

  for (int i = 0; i < abs(steps); i++) {
    digitalWrite(STEPPER_STEP_PIN, LOW);
    digitalWrite(STEPPER_STEP_PIN, HIGH);
    delay(STEPPER_DELAY);
  }
}




