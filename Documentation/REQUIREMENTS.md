# Final Project — Source-grounded Requirements

**Primary source:** *Project Details, Presentation, and Report.pdf*, included in the provided course ZIP. Page references below use the **printed/slide handout page labels** (e.g., 6–16). The source also contains its own schedule/date inconsistency; check Canvas for official updates.

## Overall

- Project 1: Vehicle Sensing and Fusion
  - **1.1:** Signal Processing for One Ultrasonic Sensor
  - **1.2:** Sensor Fusion of Multiple Ultrasonic Sensors
- Project 2: Vehicle Control — Run Down the Hill
- Groups usually contain four students, some three.

## Project 1.1 — Single ultrasonic sensor (p. 6)

1. **Sampling:** Sample the ultrasonic sensor's **time data** as fast as possible.
2. **Filtering:** Design and implement filters for time-data noise. A **Kalman filter is mandatory**.
3. **Calibration:** Design an appropriate fitting function to map time to distance in **millimeters** and calculate its fitting parameters.
4. **Test:** Print distance in mm and variance in real time. When filtering has converged (variance is small enough and/or the estimate changes little), **flash a LED**, **stop printing** and **output time cost**.
5. Distance test range: **20 cm to 1.5 m**.

The source does not prescribe the calibration form, Kalman gains/variances, exact convergence threshold, or a specific LED pin; determine and document these experimentally.

## Project 1.2 — Two or more sensors (p. 7)

1. Sample time data from **at least two** ultrasonic sensors as fast as possible.
2. Design a time-to-distance fitting function and obtain fitting parameters **for each sensor**; may reuse 1.1 calibration results.
3. Implement a **Kalman filter to fuse the multiple distance measurements** to estimate true distance.
4. Print distance (mm) and variance in real time. On convergence, flash a LED, stop printing, and output time cost.
5. Same **20 cm to 1.5 m** range.

## Project 1 output protocol (p. 13)

- In `setup()`: `Serial.println("START");` and `Time1 = millis();`
- Print each measurement line as **`estimated distance, variance`**, one pair per line. The distance unit is **mm with two decimal places**.
- `Serial.println(val, 2)` is the example given for printing to two decimal places. Print the comma separator deliberately.
- **1.1 variance = time variance**. **1.2 variance = distance variance**.
- On convergence, stop streaming and print only elapsed **milliseconds**: `Time2 = millis(); Serial.println(Time2 - Time1);`
- Avoid extra labels/debug messages in the final test serial output unless explicitly permitted.

Suggested exact line structure (illustrative, not actual test data):

```text
START
<distance_mm>, <variance>
<distance_mm>, <variance>
...
<elapsed_ms>
```

## Project 1 testing and grading (pp. 11–13)

- **Two test distances for 1.1** followed by **two test distances for 1.2** (four tests total).
- TA resets Arduino after placement at each distance and records displayed data after completion.
- **60%** graded from serial output:
  - 1.1: accuracy 10%, variance 10%, time cost 10%.
  - 1.2: accuracy 10%, variance 10%, time cost 10%.
- **40%** graded from submitted code.
- If changes are needed during testing: **10% total-score deduction for each change** (as written).
- Peer evaluation penalty: up to 10%.
- Avoid transmitting ultrasonic pulses toward a group actively being tested.

## Project 2 — ACC and autonomous lane keeping (pp. 8–9)

**Goal:** Use ultrasonic-sensor-based embedded control to drive an RC vehicle down the ramp (CU-ICAR or an indoor track depending on weather) as quickly as possible without collisions.

- **Adaptive cruise control:** Maintain **30 cm** separation from obstacles ahead; stop at **30 cm** when obstacles are stationary.
- **Autonomous lane keeping:** Stay centered in a defined lane.
- At the beginning, a board is positioned **30 cm from the start line**. The car crosses the line, then reverses to **stop at the start line**.
- After the board is removed, descend while staying centered, avoid boundaries, and pass **five checkpoints**.
- At the end, a board is positioned **30 cm from the end line**; the vehicle must **stop at the end line**.
- The printed source phrase for the last board says "30 away" without units; context and other notes specify 30 cm.
- You may use **model-based or non-model-based** controllers, or combine controllers with simple logic. **Purely simple-logic control is not permitted.**

### Project 2 grading (pp. 14–15)

- **20%**: Stops 30 cm from boards at start and end, with minimal vibration/oscillation.
- **20%**: Time running down the hill (start line to end line).
- **20%**: No boundary collisions and pass all five checkpoints.
- **40%**: Submitted Arduino code.
- One extra run is free after all groups have tested if necessary; further runs cost **10% of Project 2 test score each**.
- Peer evaluations may penalize up to 10%.

## Testing day (pp. 10–11)

1. Upload **both projects' code to Canvas before the test class**.
2. Set up Projects 1 and 2 on the vehicle.
3. Load and test Project 1 (1.1, then 1.2).
4. Load and test Project 2.
5. After testing, each student submits **confidential peer ratings (1–10)** for teammates.

TA assistance covers suggested directions and high-level program logic, **not** compilation fixes or algorithm debugging.

## Group presentation (p. 16)

- **December 11** according to the handout.
- Group slides and a **recording**, covering approaches/solutions, results and discussions for **both** projects.
- **10 minutes total per group**, and every student must present (suggested **2.5 minutes each** for a group of four).
- Upload slides and recording to instructor-specified Google Drive folder: https://drive.google.com/drive/folders/14a6HNpEyjwJTuvKOY9YKx-HJG-ss9MRM?usp=sharing
- Grading: **40% slides**, **50% delivery**, **10% timing**.
- Preserve all experimental data for this presentation.

## Individual report (p. 16, supplied Word templates)

- Each student writes their own technical-style report describing **both** projects' work and findings.
- Sections expected: **Problem Statement; Technical Approach; Hardware and Software Implementation; Experimental Results; Discussions and Conclusions.**
- Two **recommended** templates supplied: one for Project 1 and one for Project 2; their exact outlines are in `Documentation/REPORT_OUTLINE.md`.
- Due **December 11 at 11:59 PM** (per handout).
- Submit the **course evaluation confirmation page without scores** along with the report; the handout says this may receive special consideration.

## Project schedule from the assignment (p. 5)

| Date | Course activity |
| --- | --- |
| Nov 10 | Project announcement and Arduino programming |
| Nov 17 | Ultrasonic sensing and RC vehicle control |
| Nov 19 | Sensing signal processing and control implementations |
| Nov 24 | Testing details, practice and Q&A |
| Dec 1 | Test preparation and Q&A |
| Dec 3 | Project test (12:30–2:00 PM per p. 10) |
| Dec 11 | Presentation recording and project report |

**Date caution:** One slide says "Project Test Day: Dec 3, Tuesday" while the 2026 calendar makes Dec 3 a **Thursday**. December 11, 2026 *is* Friday, matching the handout. Confirm day/time with course staff/Canvas rather than inferring the intended schedule.

## Project office hours (pp. 9–10)

- Tuesday and Thursday, 3:00–6:00 PM.
- Sunday, 1:00–5:00 PM.
- CU-ICAR lobby; other times by appointment via instructor/TAs.

## Repository documentation notes

This is a faithful **summary** of the assignment, not a replacement for the original PDF, lecture slides, or announcements. Where hardware model, constants, or test outcomes are not specified, no values have been invented.
