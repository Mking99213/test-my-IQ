# Comparison protocol — exploratory prototype

This is a pattern-recall game, not an intelligence test, clinical assessment, validated brain-training intervention or astronaut selection tool. No evidence establishes that it is the best game or completely fair across age and education. Prior learning, hearing, vision, motor skills, fatigue, age and game familiarity affect results. Visual and auditory conditions are separate tasks; do not pool their scores.

## Conditions
Choose Visual, Audio, or Both using M or the mode button before starting. Audio uses four original tones: 1=330 Hz, 2=440 Hz, 3=587.33 Hz, 4=783.99 Hz. Inputs are the same in all modes. During observe, audio-only does not light the symbol buttons. Both provides redundant cues and is not equivalent to either single modality.

Use the same computer, display, keyboard, headphones, comfortable volume, instructions, mode and test environment for every participant in a comparison. Provide the same practice period to learn the tone-to-key mapping. Confirm participants can perceive every stimulus; record accommodations and analyze them separately. Participation should be voluntary, with appropriate consent for student research.

All runs reset the pattern generator to seed 2026. This gives matching patterns on the same engine version/build but causes practice effects on repeated runs. Do not present repeated exposure as independent improvement. A stronger study needs balanced alternate forms, randomized order, a control group, age-appropriate norms and statistical validation.

## Recorded output
When the third system passes, one row is appended to `Saved/Results/sessions.csv`: UTC timestamp, seed, mode, retry count, total observe-plus-recall seconds and completed systems. Launch time is excluded. This is a coarse session measure, not per-trial response latency. Incomplete runs are not logged, so retain a separate record of withdrawals/timeouts to avoid completion bias. R resets elapsed time and retries. No names or participant identifiers are collected automatically.

Use anonymized external IDs to match rows to participants. Keep demographic and consent records separate. Review retry count and completion time separately; there is no validated composite score, age ranking or fairness correction. Time includes forced observation and replays, so it is not a pure processing-speed measure. CSV saving failures appear in Unreal's Output Log.

Before comparing people, complete the engine acceptance checklist, verify exported rows, test audio timing on the target hardware, and have an appropriate research lead review the study. Desktop frame hitches may disrupt cue timing; a controlled assessment requires stronger timing instrumentation.
