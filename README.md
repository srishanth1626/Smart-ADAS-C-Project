[README.txt](https://github.com/user-attachments/files/34849443/README.txt)
SMART ADAS - FORWARD COLLISION WARNING SYSTEM
C Programming Mini Project (C99)

FILES
1. adas_forward_collision_warning.c - complete C source code
2. PROJECT_REPORT.txt - project explanation and report content
3. TEST_CASES.txt - sample inputs and expected alert categories

HOW TO COMPILE AND RUN

Option A: GCC (Windows / Linux / macOS)
1. Install GCC (for example, MinGW-w64 on Windows).
2. Open Terminal / Command Prompt in this project folder.
3. Compile:
   gcc adas_forward_collision_warning.c -o adas
4. Run on Windows:
   adas.exe
   Run on Linux/macOS:
   ./adas

Option B: Code::Blocks
1. Open Code::Blocks and choose File > New > Project > Console application.
2. Select C as the language.
3. Replace the generated source with adas_forward_collision_warning.c.
4. Build and Run (F9).

HOW TO USE
1. Select 1 from the menu.
2. Enter the vehicle speed in km/h.
3. Enter the distance to the obstacle in metres.
4. Read the estimated stopping distance and alert.
5. Select 2 to view assumptions, 3 for project details, or 4 to exit.

IMPORTANT LIMITATION
This is a software-only educational simulation. It accepts manually entered
values; it is not connected to radar, camera, ultrasonic sensors, brakes or a
vehicle. It is not a real safety system and must not be used while driving.
