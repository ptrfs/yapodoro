#include "pomodoro.h"
#include "clock.h"

// TODO: Actually do this function
int pomodoro(char *session_name) {
  int session_counter = 0;
  pomo_timer on_state, pause_state;
  on_state.session_name = session_name;
  on_state.sec = (25 * 60);
  on_state.state = on;
  on_state.current_session_number = 0;

  pause_state.session_name = session_name;
  pause_state.sec = (5 * 60);
  pause_state.state = p_break;
  pause_state.current_session_number = 0;

  char opt;

  bool is_on = true;
  while (is_on == true) {
    pomo_countdown(on_state);

    printf("Do you want to continue[y/n]: ");
    scanf("%c", &opt);

    if (opt != 'y' || opt != 'n' || opt == 'n') {
      is_on = false;
      break;
    }

    pomo_countdown(pause_state);
    session_counter++;
  }

  return session_counter;
}
