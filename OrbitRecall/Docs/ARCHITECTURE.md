# Implementation and extension points

The game mode owns mission state, procedural world construction and launch progression. The pawn provides a third-person overview camera and constrained walking. The HUD draws immediate-mode panels and click hitboxes. The native player controller is used; no Blueprint, Enhanced Input mapping asset, UMG widget or external content is needed.

State flow: briefing → observe → recall → next observe / ready → countdown + ascent → won. Incorrect recall returns to observe with the same pattern. R returns to briefing from any state. Inputs are gated by phase; completed systems cannot be skipped by pressing launch early. Patterns use FRandomStream with seed 2026, reset each session; sampling is with replacement, so repeated symbols are intentional.

The three systems use the same sequence mechanic under different mission labels. These are not three different puzzle types. Portable tests cover lengths, wrong answers, progress, completion, invalid symbols, repeated symbols and reset; they do not test the engine API or HUD.

To extend: adjust lengths in MissionLogic, but update its five-element storage if exceeding five. Replace engine shapes in Part calls with owned art, add audio cues synchronized to observe flashes, or replace DrawHUD with UMG. Add proximity interaction, a skeletal astronaut, persistent best scores or accessibility settings as follow-up work. Current progress is session-only, input is desktop-only, strings are English, and four synthesized auditory cues are included.

For scalable production code, move mission state into a subsystem/component, use data assets for challenge definitions and input actions for remapping, and separate presentation from state transitions. This starter favors a small, inspectable hackathon codebase.
