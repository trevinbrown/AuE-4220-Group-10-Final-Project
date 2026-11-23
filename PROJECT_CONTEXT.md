# Working context for ChatGPT and Codex

## Objective and workflow

This is Clemson AuE 4220's Group 10 electronics integration final project. Use this repo as the common source of truth across regular ChatGPT and Codex. Start with **Project 1.1**. Conceptual explanations and report analysis may be developed in a regular chat; source-code work and verification may be done in Codex; both should read the tracked files.

**Important:** Chat histories are not automatically shared. Update this file when assumptions, pin assignments, test data, decisions, or algorithm parameters change.

## Grading-critical instructor requirements

- **1.1:** One ultrasonic sensor, sample echo time as fast as possible, **Kalman filter mandatory**, calibrate time-to-distance in mm, print `distance, variance` in real time. **Variance refers to TIME** for 1.1.
- **1.2:** At least two ultrasonic sensors, calibrate each, Kalman-fuse distance estimates; print `distance, variance` in real time. **Variance refers to DISTANCE** for 1.2.
- Both sensing parts test within **20 cm to 1.5 m**. When converged (small enough variance and/or stable estimate), **flash an LED, stop the stream, print elapsed milliseconds**.
- Serial protocol from instructor: print `START` in `setup()`, set starting `millis()`, print distance in **mm with two decimal places** and variance each line, then report `Time2 - Time1` using `millis()`. Choose and document a defensible convergence criterion: assignment specifies no exact threshold.
- 1.1 tests two unknown distances; 1.2 tests two unknown distances; each penalizes accuracy, variance, elapsed time; the code accounts for 40% of Project 1 grading.
- Project 2: ultrasonic-feedback ACC, stop 30 cm from boards at start/end, reverse to start line after initially crossing, remain centered downhill, pass five checkpoints without hitting walls. **Pure rule-based control is disallowed**; feedback controller(s) plus simple logic are allowed.

See `Documentation/REQUIREMENTS.md` for the fuller rubric, submission and report requirements.

## Starter code — ORIGINAL / DO NOT OVERWRITE

`Project_1/Part_1_1/ultrasound1/ultrasound1.ino`
- Original email attachment `ultrasound1.ino` by Matthew Fielden, Nov 19, 2026.
- Pins: **13 trigger**, **12 echo**. 9600 baud. Pulses trigger HIGH for 10 µs and calls `pulseIn(echoPin,HIGH)`; prints raw echo time in µs; waits 100 ms.
- **Not a finished 1.1 solution:** no calibration, Kalman filter, convergence criterion, time variance, LED, or course-format serial output.
- `pulseIn` has no specified timeout; design an explicit timeout and invalid-sample handling suitable for the 1.5 m test range. A 2,000 µs timeout, seen in a *different* supplied lecture example, is too short for 1.5 m. Avoid simply deleting trigger spacing without checking echo interference.

`Project_2/starter/newbasecode/newbasecode.ino`
- Original email attachment `newbasecode.ino` by Matthew Fielden, Nov 19, 2026.
- Uses Arduino `Servo.h`. Steering servo on **pin 10**, ESC on **pin 11**; both neutral at **1500 µs**. Steering commands clamped to **1050–1950 µs** and throttle to **1200–1900 µs** within `setVehicle(int s,int v)`.
- Contains example neutral commands and delays, **not** a working ACC or lane-keeping solution. The provided file asks students not to alter the vehicle command helper; leave the archived original alone. Build actual control logic in a new sketch.
- Instructor's course-ZIP `basecode.ino` has a separate mismatch: it calls `setVehicleCommands` while defining `setVehicle`; Matt's emailed `newbasecode.ino` already calls `setVehicle`.

## Implementation conventions

1. Preserve both original `.ino` files byte-for-byte; create a new working sketch folder for each solution (Arduino IDE often expects the sketch file to match its folder name).
2. Before assuming an exact sensor model, LED pin, MCU board, pin budget, available motor behavior, or calibration constants, verify them from the actual test setup.
3. Record **measured** calibration points and calculate the fitting function from those data. Never invent calibration coefficients or measured performance.
4. Define and record Kalman state/measurement units, observation-noise variance, process-noise variance, initialization, invalid-sample behavior, and convergence condition.
5. Be explicit about units: microseconds, mm, µs² (time variance in 1.1), mm² (distance variance in 1.2), milliseconds for time cost.
6. Validate serial output, actual sensor wiring/behavior, and program compile on the group's hardware before claiming requirements are satisfied.
7. Keep track of observed distance error, convergence variance and elapsed time for the presentation/report.

## Instructor-supplied schedule (verify on Canvas)

- Nov 24: test details and practice.
- Dec 1: test preparation.
- Dec 3: project demonstration (12:30–2 PM in the PDF).
- Dec 11: group presentation and individual report (report 11:59 PM).

The PDF labels **Dec 3 as Tuesday**, inconsistent with the 2026 calendar (Dec 3, 2026 is Thursday). Confirm the actual testing date/time directly.

## Snapshot state

Initialization only. No measured calibration samples, tuned Kalman parameters, verified LED pin, finished controller, or bench-test results have been supplied to this repository yet.
