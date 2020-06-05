#ifndef Task_h
#define Task_h
#include <Arduino.h>

typedef enum {
  TASK_NONE = 0,
  TASK_RUNNING,
  TASK_COMPLETED
} TASK_STATUS;

class Task {
  private:
    bool _launched;
	bool _awaiting;
	bool _delayed;
    uint16_t _iterations;
    uint32_t _work;
    uint32_t _wait;
	uint32_t _time;
	TASK_STATUS _status;
    void (*_initialization)(void);
    void (*_finalization)(void);
  public:
    void configure(void (*initialization)(void) = NULL, void (*finalization)(void) = NULL);
	void run();
    bool launch(const uint32_t work, const uint32_t wait = 0, const uint16_t iterations = 1);
    bool launchWithDelay(const uint32_t work, const uint32_t wait = 0, const uint16_t iterations = 1);
    bool complete();
    bool reset();
    TASK_STATUS getStatus();
};

#endif