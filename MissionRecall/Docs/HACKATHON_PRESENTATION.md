# Mission Recall — 5-minute hackathon presentation

## 1 · Mission briefing (0:00–0:35)
**Slide:** “Can you remember your way to orbit?”
Pitch: A short NASA-inspired memory game where an astronaut earns launch readiness through recall. Three systems, one rocket, one clear finish. Visual, audio-only and combined modes use patterns rather than learned facts.

## 2 · Player experience (0:35–1:10)
**Slide:** Observe → Recall → Prepare → Launch.
Explain how increasing sequence length raises difficulty. Mistakes replay a pattern, preserving previous system progress. Visual letters and numbers avoid relying on color alone. Do not claim clinical memory improvements; that would require research.

## 3 · Live demonstration (1:10–2:45)
**Slide:** Live mission.
Start a fresh run. Narrate the first three flashes, deliberately miss once, then recover. Complete fuel, navigation and life support. Show each green indicator, board and launch. Let the success screen remain visible.
Practice full runs beforehand: random patterns mean the presenter must observe each sequence. Keep a locally recorded complete run as a backup; this package does not include a recording.

## 4 · What we built (2:45–3:35)
**Slide:** Small source project, complete loop.
Show the C++ state machine, engine-independent mission rules, procedural site and rocket, HUD controls, and map generation script. Explain that one recall mechanic appears in three mission systems. Mention any local UE compile/play/package validation actually completed; do not present portable rule tests as engine validation.

## 5 · Next mission (3:35–4:25)
**Slide:** From prototype to launch-ready demo.
Roadmap: input remapping, adjustable timing and difficulty, bespoke astronaut animation, proximity-based terminals, varied puzzle types, scores and user testing. Keep these distinct from delivered features.

## 6 · Closing and questions (4:25–5:00)
**Slide:** “Remember. Prepare. Launch.”
Ask judges to try a mission. Share a link/QR to your uploaded source archive or packaged build after hosting it. Credit Unreal Engine; describe this as independent and NASA-inspired. No NASA endorsement is claimed.

## Likely judge questions
- Why Unreal? A 3D launch payoff plus a native path to extending the astronaut and world.
- What makes it a game? A visible goal, escalating recall, recoverable errors, preparation progress and victory.
- What is original here? The mission framing and implementation; sequence recall itself is a familiar mechanic.
- How was it tested? Portable logic assertions plus your locally completed UE acceptance checks.
- What are its limits? Primitive art, one memory mechanic, fixed difficulty, desktop controls and session-only progress; CSV metrics are exploratory, not validated cognitive scores.
