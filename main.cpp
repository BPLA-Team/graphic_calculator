#include "frontend.h"

int main() {
  Graphix_window grw;
  while (grw.window_is_open())
    grw.wait_for_button();
}