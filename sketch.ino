#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Sensor inputs
const int TEMP_PIN = A0;
const int SMOKE_PIN = A1;
const int FLAME_PIN = 2;

// Outputs
const int GREEN_LED = 8;
const int YELLOW_LED = 9;
const int RED_LED = 10;
const int FAN_PIN = 11;
const int BUZZER_PIN = 6;
const int RESET_PIN = 3;

void setup() {
  Serial.begin(9600);

  pinMode(FLAME_PIN, INPUT_PULLUP);
  pinMode(RESET_PIN, INPUT_PULLUP);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("SMART FIRE ALARM");
  delay(1500);
  lcd.clear();
}

void loop() {

  // Read simulated sensors
  int tempRaw = analogRead(TEMP_PIN);
  int smokeRaw = analogRead(SMOKE_PIN);

  float temp_c = map(tempRaw, 0, 1023, 0, 100);
  int smoke_ppm = map(smokeRaw, 0, 1023, 0, 1000);

  int flame_pin = digitalRead(FLAME_PIN) == HIGH ? 1 : 0;

  // Warning thresholds
  bool tempWarning = temp_c > 45;
  bool smokeWarning = smoke_ppm > 300;

  // Critical thresholds
  bool tempCritical = temp_c > 57;
  bool smokeCritical = smoke_ppm > 400;

  // Flame detection
  bool flameDetected = (flame_pin == 1);

  // Count sensors crossing warning thresholds
  int active_sensors = 0;

  if (tempWarning) active_sensors++;
  if (smokeWarning) active_sensors++;
  if (flameDetected) active_sensors++;

  // Determine system state
  // 0 = NORMAL, 1 = WARNING, 2 = EMERGENCY

  int systemState;

  if (tempCritical || smokeCritical || flameDetected ||
      active_sensors >= 2) {

    systemState = 2;  // EMERGENCY

  }
  else if (active_sensors == 1) {

    systemState = 1;  // WARNING

  }
  else {

    systemState = 0;  // NORMAL

  }

  // Turn off all outputs before updating
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(FAN_PIN, LOW);
  noTone(BUZZER_PIN);

  lcd.clear();

  if (systemState == 0) {

    digitalWrite(GREEN_LED, HIGH);

    lcd.setCursor(0, 0);
    lcd.print("SYSTEM NORMAL");

    lcd.setCursor(0, 1);
    lcd.print("ALL SENSORS OK");

  }
  else if (systemState == 1) {

    digitalWrite(YELLOW_LED, HIGH);

    lcd.setCursor(0, 0);
    lcd.print("WARNING!");

    lcd.setCursor(0, 1);
    lcd.print("1 SENSOR ACTIVE");

    // Intermittent buzzer
    tone(BUZZER_PIN, 1000);
    delay(300);
    noTone(BUZZER_PIN);
    delay(300);

  }
  else {

    digitalWrite(RED_LED, HIGH);
    digitalWrite(FAN_PIN, HIGH);

    lcd.setCursor(0, 0);
    lcd.print("FIRE ALERT!");

    lcd.setCursor(0, 1);
    lcd.print("EVACUATE NOW!");

    tone(BUZZER_PIN, 1500);
  }

  // Print readings for debugging
  Serial.print("Temperature: ");
  Serial.print(temp_c);
  Serial.print(" C | Smoke: ");
  Serial.print(smoke_ppm);
  Serial.print(" ppm | Flame: ");
  Serial.print(flame_pin);
  Serial.print(" | Active sensors: ");
  Serial.println(active_sensors);
  Serial.print(active_sensors);

  Serial.print(" | System State: ");

  if (systemState == 0) {
    Serial.println("NORMAL");
  }
  else if (systemState == 1) {
    Serial.println("WARNING");
  }
  else {
    Serial.println("FIRE ALERT");
  }

  // Reset / acknowledge button
  if (digitalRead(RESET_PIN) == LOW) {
    noTone(BUZZER_PIN);
    lcd.clear();
    lcd.print("RESET REQUESTED");
    delay(500);
  }

  delay(300);
}
