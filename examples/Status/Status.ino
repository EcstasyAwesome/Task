#include <Task.h>

Task task;

void print1() {
  Serial.println("LED on");
  digitalWrite(LED_BUILTIN, HIGH);
}

void print2() {
  Serial.println("LED off");
  digitalWrite(LED_BUILTIN, LOW);
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  task.configure(print1, print2);
}

void loop() {
  task.run();
  if (task.getStatus() == TASK_NONE) task.launch(3000);
  else if (task.getStatus() == TASK_RUNNING && millis() > 2000) {
    Serial.println("Immediately interrupted after 2 sec");
    task.complete();
  }
  else if (task.getStatus() == TASK_COMPLETED) {
    Serial.println("Done");
    task.reset();
    while (true) {}
  }
}