#include <Task.h>

Task task;

void print() {
  Serial.println("Initialization");
}

void setup() {
  Serial.begin(9600);
  task.configure(print);
  task.launchWithDelay(3000);
  Serial.println("Launched");
}

void loop() {
  task.run();
}