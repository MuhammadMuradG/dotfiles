/* See LICENSE file for copyright and license details. */

/* interval between updates (in ms) */
const unsigned int interval = 300;

/* text to show if no value can be retrieved */
static const char unknown_str[] = "n/a";

static const char* const SEPARATOR = "  ";

/* maximum output string length */
#define MAXLEN 2048

/*
 * function            description                     argument (example)
 *
 * battery_perc        battery percentage              battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * battery_state       battery charging state          battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * battery_remaining   battery remaining HH:MM         battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * cpu_perc            cpu usage in percent            NULL
 * cpu_freq            cpu frequency in MHz            NULL
 * datetime            date and time                   format string (%F %T)
 * disk_free           free disk space in GB           mountpoint path (/)
 * disk_perc           disk usage in percent           mountpoint path (/)
 * disk_total          total disk space in GB          mountpoint path (/")
 * disk_used           used disk space in GB           mountpoint path (/)
 * entropy             available entropy               NULL
 * gid                 GID of current user             NULL
 * hostname            hostname                        NULL
 * ipv4                IPv4 address                    interface name (eth0)
 * ipv6                IPv6 address                    interface name (eth0)
 * kernel_release      `uname -r`                      NULL
 * keyboard_indicators caps/num lock indicators        format string (c?n?)
 *                                                     see keyboard_indicators.c
 * keymap              layout (variant) of current     NULL
 *                     keymap
 * load_avg            load average                    NULL
 * netspeed_rx         receive network speed           interface name (wlan0)
 * netspeed_tx         transfer network speed          interface name (wlan0)
 * notify              display a message and           bell signal which 0 or 1
 *                     optionally activate a bell      function name to trigger
 *                     according to arguments          and its arguments all
 *                                                     formatted as a string
 *                                                     seperated by space
 *                                                     (1 battery_warning 10)
 * num_files           number of files in a directory  path
 *                                                     (/home/foo/Inbox/cur)
 * ram_free            free memory in GB               NULL
 * ram_perc            memory usage in percent         NULL
 * ram_total           total memory size in GB         NULL
 * ram_used            used memory in GB               NULL
 * run_command         custom shell command            command (echo foo)
 * separator           string to echo                  NULL
 * swap_free           free swap in GB                 NULL
 * swap_perc           swap usage in percent           NULL
 * swap_total          total swap size in GB           NULL
 * swap_used           used swap in GB                 NULL
 * temp                temperature in degree celsius   sensor file
 *                                                     (/sys/class/thermal/...)
 *                                                     NULL on OpenBSD
 *                                                     thermal zone on FreeBSD
 *                                                     (tz0, tz1, etc.)
 * uid                 UID of current user             NULL
 * uptime              system uptime                   NULL
 * username            username of current user        NULL
 * vol_perc            OSS/ALSA volume in percent      mixer file (/dev/mixer)
 *                                                     NULL on OpenBSD
 * wifi_perc           WiFi signal in percent          interface name (wlan0)
 * wifi_essid          WiFi ESSID                      interface name (wlan0)
 */
static const struct arg args[] = {
	/* function          format            argument */
	{ separator,        "│🚨",             NULL },
	{ notification,     " 🔌 %s",          "1 battery_warning 5" },
	{ separator,        "│",               NULL },
	{ netspeed_rx,      "%8s",            "wlan0" },
	{ netspeed_tx,      "%-8s",           "wlan0" },
	{ separator,        SEPARATOR,         NULL },

	{ wifi_perc,        "󰖩 %s%%",          "wlan0" },
	{ separator,        SEPARATOR,         NULL },

	{ battery_perc,     "󱧥 %s%%",          NULL },
	{ separator,        SEPARATOR,         NULL },

	{ ram_perc,         " %s%%",          NULL },
	{ separator,        SEPARATOR,         NULL },

	{ cpu_perc,         " [%-3s%%",       NULL },
	{ temp,             ", %s℃]",          "tz0" },
	{ separator,        SEPARATOR,         NULL },

	{ vol_perc,         " %s%%",          "/dev/mixer" },
	{ separator,        SEPARATOR,         NULL },

	{ keymap,           " %s",            NULL },
	{ separator,        SEPARATOR,         NULL },

	{ datetime,         " %s",            "%a,%d %b" },
	{ separator,        SEPARATOR,         NULL },
	{ datetime,         " %s",            "%I:%M%p" },
};
