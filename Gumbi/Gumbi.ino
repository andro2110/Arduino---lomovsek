
void setup() {
  Serial.begin(9600);

  pinMode(3, INPUT);
  pinMode(A6, INPUT);
  pinMode(2, INPUT);
  pinMode(A3, INPUT);
}

void loop() {

    Serial.print("D2: ");
    Serial.println(digitalRead(2));
    
    Serial.print("D3: ");
    Serial.println(digitalRead(3));


    Serial.print("A3: ");
    Serial.println(digitalRead(A3));
    
    Serial.print("A6: ");
    Serial.println(digitalRead(A6));
}
