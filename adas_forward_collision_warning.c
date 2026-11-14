/*
 * SMART ADAS - FORWARD COLLISION WARNING SYSTEM (ACADEMIC SIMULATION)
 * Language: C (C99)
 * Purpose: Demonstrates a basic forward-collision warning calculation.
 * NOTE: This is a console-based learning prototype. It does NOT read real
 * vehicle sensors and must never be used to control or operate a real vehicle.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define REACTION_TIME 1.5       /* seconds */
#define BRAKING_DECEL 6.0       /* m/s^2; assumed constant deceleration */
#define SAFETY_MARGIN 5.0       /* extra distance in metres */
#define WARNING_EXTRA 15.0      /* caution zone beyond calculated stop distance */
#define GRAVITY 9.81

static int read_number(const char *prompt, double *value,
                       double minimum, double maximum) {
    char line[128];
    char *end;
    double number;

    for (;;) {
        printf("%s", prompt);
        if (fgets(line, sizeof line, stdin) == NULL) return 0;
        number = strtod(line, &end);
        while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n') end++;
        if (end == line || *end != '\0' || !isfinite(number)) {
            printf("Invalid input. Please enter a number.\n\n");
            continue;
        }
        if (number < minimum || number > maximum) {
            printf("Enter a value from %.1f to %.1f.\n\n", minimum, maximum);
            continue;
        }
        *value = number;
        return 1;
    }
}

static void show_project_info(void) {
    printf("\nSMART ADAS - FORWARD COLLISION WARNING SYSTEM\n");
    printf("Academic mini-project developed in C programming.\n");
    printf("It estimates stopping distance from speed and compares it\n");
    printf("with the entered distance to an obstacle.\n");
    printf("All values are typed by the user; no physical sensors are connected.\n\n");
}

static void show_assumptions(void) {
    printf("\nMODEL SETTINGS / ASSUMPTIONS\n");
    printf("Driver reaction time : %.1f seconds\n", REACTION_TIME);
    printf("Assumed deceleration : %.1f m/s^2\n", BRAKING_DECEL);
    printf("Safety margin        : %.1f metres\n", SAFETY_MARGIN);
    printf("Warning zone         : %.1f metres beyond stopping distance\n", WARNING_EXTRA);
    printf("\nThese are simplified educational assumptions. Real ADAS uses\n");
    printf("calibrated sensors, vehicle-specific models and safety validation.\n\n");
}

static void analyse_situation(void) {
    double speed_kmh, gap_m;
    double speed_ms, reaction_distance, braking_distance;
    double stopping_distance, warning_distance, ttc;

    printf("\n--- ENTER SIMULATED VEHICLE DATA ---\n");
    if (!read_number("Vehicle speed (km/h, 0-200): ", &speed_kmh, 0.0, 200.0)) return;
    if (!read_number("Distance to obstacle (metres, 0-500): ", &gap_m, 0.0, 500.0)) return;

    speed_ms = speed_kmh / 3.6;
    reaction_distance = speed_ms * REACTION_TIME;
    braking_distance = (speed_ms * speed_ms) / (2.0 * BRAKING_DECEL);
    stopping_distance = reaction_distance + braking_distance + SAFETY_MARGIN;
    warning_distance = stopping_distance + WARNING_EXTRA;
    ttc = (speed_ms > 0.0) ? gap_m / speed_ms : INFINITY;

    printf("\n========== ADAS ANALYSIS RESULT ==========\n");
    printf("Vehicle speed              : %.1f km/h\n", speed_kmh);
    printf("Distance to obstacle       : %.1f m\n", gap_m);
    printf("Estimated reaction distance: %.1f m\n", reaction_distance);
    printf("Estimated braking distance: %.1f m\n", braking_distance);
    printf("Estimated stopping distance: %.1f m (includes %.1f m margin)\n",
           stopping_distance, SAFETY_MARGIN);
    if (isfinite(ttc)) printf("Estimated time to obstacle : %.2f seconds\n", ttc);
    else printf("Estimated time to obstacle : Not applicable (vehicle speed is zero)\n");

    printf("\nDRIVER ALERT: ");
    if (speed_kmh == 0.0) {
        printf("STATIONARY\n");
        printf("The simulated vehicle is not moving.\n");
    } else if (gap_m <= stopping_distance) {
        printf("DANGER - COLLISION RISK\n");
        printf("The available distance is at or below the estimated stopping distance.\n");
        printf("The prototype would issue an urgent collision warning.\n");
    } else if (gap_m <= warning_distance || ttc <= 3.0) {
        printf("CAUTION - REDUCE SPEED / INCREASE GAP\n");
        printf("The obstacle is approaching the warning zone.\n");
    } else {
        printf("SAFE - NO IMMEDIATE WARNING\n");
        printf("The entered gap is above the estimated warning distance.\n");
    }
    printf("=========================================\n\n");
}

int main(void) {
    char choice_line[32];
    int choice;

    printf("=================================================\n");
    printf("       SMART ADAS - COLLISION WARNING DEMO       \n");
    printf("=================================================\n");
    printf("C Programming Mini Project | Console Simulation\n");

    for (;;) {
        printf("\nMAIN MENU\n");
        printf("1. Analyse a driving situation\n");
        printf("2. View model settings and assumptions\n");
        printf("3. About this project\n");
        printf("4. Exit\n");
        printf("Enter your choice (1-4): ");
        if (fgets(choice_line, sizeof choice_line, stdin) == NULL) break;
        if (sscanf(choice_line, "%d", &choice) != 1) choice = 0;

        switch (choice) {
            case 1: analyse_situation(); break;
            case 2: show_assumptions(); break;
            case 3: show_project_info(); break;
            case 4:
                printf("Thank you for trying the ADAS simulation. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Please select 1, 2, 3 or 4.\n");
        }
    }
    return 0;
}
