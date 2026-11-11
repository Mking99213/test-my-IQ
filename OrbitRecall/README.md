# Orbit Recall
### A NASA-inspired astronaut memory puzzle · Unreal Engine 5 source starter

Prepare fuel routing, navigation, and life support by recalling three increasingly long symbol sequences. Board the rocket, watch the countdown and launch, and reach the mission success screen.

## What is included
- Complete C++ gameplay module, desktop mouse/keyboard HUD, movable primitive astronaut, procedural launch site and rocket.
- Three seeded sequence memory challenges (3, 4, then 5 symbols), persistent retry counter, system indicator lights, countdown, ascent, victory and restart.
- Editor map creation script, project configuration, portable rules tests, setup guide, and hackathon pitch outline.
- Four original WAV tones, imported by the setup script; VS Code workspace/build tasks; session CSV exports.
- No Marketplace purchases, external art downloads, or template content required. All meshes/materials come from Unreal Engine BasicShapes.

## Start here
Read [SETUP.md](Docs/SETUP.md). This is a **source project**, not a compiled game. Build the editor target, generate the map once with the included script, then press Play. Target: UE 5.4, with UE 5.4+ intended; later engine versions may require target-setting updates.

Controls: M selects Visual / Audio / Both before starting; WASD moves the astronaut on the launch apron; 1–4 or buttons repeat the pattern; Space starts/launches; R resets. Use a desktop window of at least 960×600 (1280×720 recommended). Click the viewport if keyboard focus is elsewhere.

## Play loop
1. Begin mission and observe flashes A–D. A short dark gap separates repeated symbols.
2. Repeat the pattern after the OBSERVE phase changes to RECALL. Input during OBSERVE is ignored.
3. A mistake replays the same pattern without losing completed systems.
4. Complete all three systems. Board & Launch starts a five-second countdown and six-second ascent.
5. Mission success ends the run. Fly Again resets all progress.

The terminal interactions are available from anywhere on the apron; walking is optional. The astronaut is represented by engine primitives and is hidden when boarding. Camera framing is fixed relative to the astronaut. The launch is a scripted animation; orbital insertion is a game abstraction, not a physics simulation.

## Project layout
`Source/OrbitRecall/MissionLogic.h` holds engine-independent rules. `MissionGame.h/.cpp` supplies the pawn, mission game mode, world geometry, input, and HUD. `Scripts/create_map.py` creates the saved level used for packaging. `Docs/` contains setup, architecture, acceptance checks and presentation notes.

## Validation status
The portable C++ mission rules tests were compiled and run in the delivery environment. No Unreal Engine installation was available, so UnrealHeaderTool, full C++ module compilation, editor play, rendered appearance and packaged execution have **not** been verified. Follow the acceptance checklist in SETUP before a demo. This is a working-code starter intended for local UE validation, not a certified packaged build.

## Theme and rights
Independent educational prototype inspired by NASA missions. Not affiliated with or endorsed by NASA. No NASA logos, insignia, photographs, or official assets are included. The code is MIT licensed; Unreal Engine and its bundled assets remain subject to Epic's terms. Do not imply agency endorsement when adding branding.

## Visual Studio Code and participant comparisons
See [VS Code setup](Docs/VSCODE.md) and [comparison protocol](Docs/COMPARISON_PROTOCOL.md). This prototype is not a validated cognitive assessment and does not establish fairness across ages or education. Visual/audio patterns reduce reliance on factual knowledge. Restart the editor after the first map/audio setup.
