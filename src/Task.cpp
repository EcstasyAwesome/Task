#include "Task.h"

/*
 * @param initialization
 *        action that is launched at the beginning of task by a timer, see the Simple example or
 *        action that is launched at the end of task by a timer, see the Delayed example (Default is NULL)
 * @param finalization
 *        action that is launched at the end of task by a timer (Default is NULL)
 */

void Task::configure(void (*initialization)(void), void (*finalization)(void)) {
  _initialization = initialization;
  _finalization = finalization;
}

/*
 * @param work
 *        time (ms) between initialization and finalization methods
 * @param wait
 *        time (ms) before starting a new iteration (Default is 0)
 * @param iterations
 *        amount repeating of task (Default is 1)
 * @return true if the operation is successful
 */

bool Task::launch(const uint32_t work, const uint32_t wait, const uint16_t iterations) {
  if (_initialization != NULL && _finalization != NULL && _status != TASK_RUNNING) {
	_delayed = false;
    _status = TASK_RUNNING;
    _work = work;
    _wait = wait;
    _iterations = iterations;
	return true;
  }
  return false;
}

/*
 * @param work
 *        time (ms) before starting the initialization method
 * @param wait
 *        time (ms) before starting a new iteration (Default is 0)
 * @param iterations
 *        amount repeating of task (Default is 1)
 * @return true if the operation is successful
 */

bool Task::launchWithDelay(const uint32_t work, const uint32_t wait, const uint16_t iterations) {
  if (_initialization != NULL && _status != TASK_RUNNING) {
    _delayed = true;
    _status = TASK_RUNNING;
    _work = work;
    _wait = wait;
    _iterations = iterations;
	return true;
  }
  return false;
}

/*
 * The method runs in the main loop()
 * Launches actions by timer
 */
 
void Task::run() {
  if (_status == TASK_RUNNING) {
    if (!_awaiting) {
taskInitializationPoint:
      if (!_launched) {
        _launched = true;
        _time = millis();
        if (!_delayed) _initialization();
      }
      else if (millis() - _time >= _work) {
        if (--_iterations == 0) _status = TASK_COMPLETED;
        else {
          _time = millis();
          _awaiting = true;
        }
        _launched = false;
        _delayed ? _initialization() : _finalization();
      }
    }
    else if (millis() - _time >= _wait) {
      _awaiting = false;
      _time = millis();
      goto taskInitializationPoint;
    }
  }
}

/*
 * Interrupts a task
 * @return true if the operation is successful
 */

bool Task::complete() {
  if (_status == TASK_RUNNING) {
    if (!_delayed && _launched) _finalization();
    _launched = false;
	_awaiting = false;
    _status = TASK_COMPLETED;
	return true;
  }
  return false;
}

/*
 * Interrupts a task and resets a state
 * @return true if the operation is successful
 */

bool Task::reset() {
  if (_status != TASK_NONE) {
    if (!_delayed && _launched) _finalization();
    _launched = false;
	_awaiting = false;
    _status = TASK_NONE;
	return true;
  }
  return false;
}

/*
 * @return task status
 */

TASK_STATUS Task::getStatus() {
  return _status;
}