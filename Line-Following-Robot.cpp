#define IN1 10
#define IN2 9
#define IN3 8
#define IN4 7
#define enA 5
#define enB 3

int s[6], total, sensor_position;
int threshold = 600;
float avg;
int position[6] = { 1, 2, 3, 4, 5 };
int set_point = 3;

void setup() {
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  PID_LINE_FOLLOW();
}

void Sensor_reading() {
  sensor_position = 0;
  total = 0;
  for (byte i = 0; i < 5; i++) {
    s[i] = analogRead(i);
    if (s[i] > threshold) s[i] = 1;
    else s[i] = 0;
    sensor_position += s[i] * position[i];
    total += s[i];
  }
  if (total) avg = sensor_position / total;
}

void PID_LINE_FOLLOW() {

  int kp = 190, kd = 500, PID_Value, P, D;
  float error, previous_error;
  int base_speed = 120, left_motor_speed, right_motor_speed, turn_speed = 120;
  char t;

  while (1) {
    Sensor_reading();
    error = set_point - avg;
    D = kd * (error - previous_error);
    P = error * kp;
    PID_Value = P + D;
    previous_error = error;

    right_motor_speed = base_speed - PID_Value; 
    left_motor_speed = base_speed + PID_Value; 
    motor(left_motor_speed, right_motor_speed);  


    Sensor_reading();
    Serial.print(total);
    if (total == 0) {
      motor(0, 0);  
      while (total == 0) {
        Sensor_reading();  
      }
    }

    if (total == 5) {
      if (t != 's') {
        if (t == 'r') motor(turn_speed, -turn_speed); 
        else motor(-turn_speed, turn_speed);          
        while (!s[2]) Sensor_reading(); 
      }
    }

    if (s[4] == 1 && s[0] == 0) t = 'l';  
    if (s[4] == 0 && s[0] == 1) t = 'r'; 

    else if (total == 0) {
      Sensor_reading();
      if (total == 0) {
        motor(0, 0); 
        while (total == 0) Sensor_reading();
      } else if (total == 0) t = 's';
    }
  }
}

void motor(int a, int b) {
  if (a > 0) {
    digitalWrite(IN3, 1);
    digitalWrite(IN4, 0);
  } else {
    a = -(a);
    digitalWrite(IN3, 0);
    digitalWrite(IN4, 1);
  }
  if (b > 0) {
    digitalWrite(IN1, 1);
    digitalWrite(IN2, 0);
  } else {
    b = -(b);
    digitalWrite(IN1, 0);
    digitalWrite(IN2, 1);
  }

  if (a > 200) a = 200;
  if (b > 200) b = 200;

  analogWrite(enB, a);
  analogWrite(enA, b);
}