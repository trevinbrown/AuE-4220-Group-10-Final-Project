# AuE 4220 — Group 10 Final Project

Arduino-based automotive electronics integration project: ultrasonic distance sensing and fusion, then feedback control of a small RC vehicle.

## Repository map

| Path | Purpose |
| --- | --- |
| `PROJECT_CONTEXT.md` | Handoff context and working conventions for Codex / regular ChatGPT |
| `Documentation/REQUIREMENTS.md` | Requirements and assessment details transcribed/summarized from the instructor's project PDF |
| `Documentation/REPORT_OUTLINE.md` | Individual report structure from the supplied templates |
| `Project_1/Part_1_1/ultrasound1/ultrasound1.ino` | Matt Fielden's **original** single-sensor example, unchanged |
| `Project_1/Part_1_2/README.md` | Multi-sensor fusion work area |
| `Project_2/starter/newbasecode/newbasecode.ino` | Matt Fielden's **original** RC vehicle-control example, unchanged |
| `Project_2/ACC/README.md` | Adaptive cruise control work area |
| `Project_2/Lane_Keeping/README.md` | Lane-keeping work area |

## Project scope

- **Project 1.1:** Single ultrasonic sensor; fast echo-time sampling; mandatory Kalman filter; experimental time-to-distance calibration; distance (mm) and **time variance** serial output; convergence LED and elapsed time.
- **Project 1.2:** At least two calibrated ultrasonic sensors; Kalman-based distance fusion; distance (mm) and **distance variance** serial output; convergence LED and elapsed time.
- **Project 2:** Ultrasonic-sensor-based adaptive cruise control and lane keeping. Stop at start/end boards with a 30 cm gap; negotiate a downhill lane and all five checkpoints. Controller must not consist solely of simple rules.

**Read `Documentation/REQUIREMENTS.md` before changing or designing any solution.**

## Getting started with Codex

1. Open this repository in Codex.
2. Ask it to read `PROJECT_CONTEXT.md` and `Documentation/REQUIREMENTS.md` first.
3. Work from copies/new sketches; **do not overwrite the two instructor/team starter originals.**
4. Record calibration measurements, Kalman noise assumptions, convergence criteria and testing outcomes so results can be defended in the individual report.

## Source provenance

- Course assignment: *Project Details, Presentation, and Report.pdf*, from the supplied course ZIP.
- Report structure: *Project 1 Report Template.docx* and *Project 2 Report Template.docx*, from the supplied course ZIP.
- Starter Arduino code: Matthew Fielden, email **"RC Codes"**, November 19, 2026 (`ultrasound1.ino` and `newbasecode.ino`).
- Source PDFs and Word templates are not included in this initialization; the requirement summary here is a handoff, not a substitute for instructor updates.

## Status

Repository initialized with requirements and **unaltered examples** only. No calibrated, tested, or complete Project 1.1, 1.2, or Project 2 solution has been committed.
