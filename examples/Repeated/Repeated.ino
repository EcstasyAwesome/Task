#include <Task.h>

Task task;

void print1() {
  Serial.println("Initialization");
}

void print2() {
  Serial.println("Finalization");
}

void setup() {
  Serial.begin(9600);
  task.configure(print1, print2);
  task.launch(3000, 1000, 3);
}

void loop() {
  task.run();
}