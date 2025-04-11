/* See LICENSE file for copyright and license details. */
#include <stdio.h>
#include <string.h>

#include "../util.h"

#if defined(__linux__)

#elif defined(__OpenBSD__)

#elif defined(__FreeBSD__)
#include <stdlib.h>
#include <sys/sysctl.h>

const char *battery_warning(const char *threshold) {
  int cap, state;
  size_t lencap, lenstate;

  lencap = sizeof(cap);
  if (sysctlbyname("hw.acpi.battery.life", &cap, &lencap, NULL, 0) == -1 ||
      !lencap)
    return NULL;

  // Current status of the battery encoded in the following:
  //      ACPI_BATT_STAT_DISCHARG (0x0001): Battery is discharging,
  //      ACPI_BATT_STAT_CHARGING (0x0002): Battery is being charged
  //      ACPI_BATT_STAT_CRITICAL (0x0004): Remaining battery life is
  //                                        critically low.
  // Note  that the status bits of each battery will be consolidated when
  // ACPI_BATTERY_ALL_UNITS is	specified.
  lenstate = sizeof(state);
  if (sysctlbyname("hw.acpi.battery.state", &state, &lenstate, NULL, 0) == -1 ||
      !lenstate)
    return NULL;

  if (cap <= atoi(threshold) && state != 2) {
    return "Plug into power source!";
  } else {
    return NULL;
  }
}
#endif

const char *notification(const char *notification_args) {
  char args[50][50];
  int i = 0, j = 0, k = 0;

  while (notification_args[j]) {
    if (notification_args[j] != ' ') {
      args[i][k] = notification_args[j];
      j++;
      k++;
    } else {
      i++;
      j++;
      k = 0;
    }
  }

  if (strcmp("battery_warning", args[1]) == 0) {
    const char *message = battery_warning(args[2]);
    if (message != NULL) {
      if (atoi(args[0]) == 1) {
        system("beep");
      }
      return message;
    }
  }
  return NULL;
}
