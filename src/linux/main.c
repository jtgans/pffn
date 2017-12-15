/*
 * PFFN -- Paste File From Network
 * Copyright (C) 2009  June R. Tate-Gans, Jonathan L. Tate
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include <pffn.h>

#include "main.h"
#include "daemon.h"
#include "logging.h"


char *g_binary_name;

/**
 * Show the usage text and exit.
 */
void show_usage(const char *fmt, ...)
{
    va_list ap;

    if (fmt != NULL) {
        va_start(ap, fmt);
        fprintf(stderr, "%s: ", g_binary_name);
        vfprintf(stderr, fmt, ap);
        fprintf(stderr, "\n");
        va_end(ap);
    }

    printf("Usage: %s [options]\n", g_binary_name);
    printf("\n");
    printf("Where options is one or more of the following:\n");
    printf("\t-h        show this text\n");
    printf("\t-f        don't daemonize (useful for debugging)\n");
    printf("\t-d        increase debugging level (cumulative)\n");
    printf("\t-s        log to stdout (implies -f)\n");

    exit(1);
}

/**
 * Parse arguments from main().
 *
 * Calls show_usage() whenever an invalid argument is found.
 *
 * @param argc The number of arguments to parse.
 * @param argv An array of strings containing each argument.
 */
void parse_args(int argc, char *argv[])
{
    int pos = 1;

    g_binary_name = strdup(argv[0]);

    for (pos = 1; pos < argc; pos++) {
        if (argv[pos][0] != '-') show_usage("Invalid option %s", argv[pos]);

        switch (argv[pos][1]) {
            /* -h -- help */
            case 'h':
                show_usage(NULL);
                break;

            /* -f -- run in foreground */
            case 'f':
                g_daemonize = 0;
                break;

            /* -d -- increase logging level */
            case 'd':
                if (g_log_level < LOG_MAX_PRIORITY) g_log_level++;
                break;

            /* -s -- log to stdout -- implies -f */
            case 's':
                g_daemonize = 0;
                g_log_to_syslog = 0;
                break;

            default:
                show_usage("Invalid option %s.", argv[pos]);
        }
    }
}

int main(int argc, char *argv[])
{
    parse_args(argc, argv);
    log_start();
    daemonize();

    logstrf(INFO, "%s v%d.%d.%d started.",
            g_binary_name, g_version[0], g_version[1], g_version[2]);

    log_end();
    daemon_shutdown();

    /* We'll never get here -- daemon_shutdown takes care of the return code. */
    /* The return statement is only here to placate compiler warnings. */
    return 0;
}
