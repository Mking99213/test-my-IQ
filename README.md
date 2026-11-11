# test-my-IQ · Orbit Recall

A NASA-inspired Unreal Engine 5.4 memory puzzle starter: prepare three rocket systems with visual, auditory, or combined pattern recall, then board and launch.

## Download and run

[Download the source starter ZIP](https://github.com/Mking99213/test-my-IQ/raw/refs/heads/orbit-recall-starter/downloads/OrbitRecall-UE5-Starter.zip)

Extract the ZIP completely. Install UE 5.4 and a compatible C++ toolchain. Open `OrbitRecall/OrbitRecall.code-workspace` in VS Code and build the Editor target, or generate and build the Visual Studio solution. Open `OrbitRecall.uproject`, run `Scripts/create_map.py` using Tools → Execute Python Script, restart Unreal after tone import, open Content/Maps/LaunchSite and press Play.

- [Complete Unreal setup](OrbitRecall/Docs/SETUP.md)
- [VS Code build instructions](OrbitRecall/Docs/VSCODE.md)
- [Hackathon presentation](OrbitRecall/Docs/HACKATHON_PRESENTATION.md)
- [Comparison protocol and limitations](OrbitRecall/Docs/COMPARISON_PROTOCOL.md)

## Validation and claims

Portable C++ mission logic tests pass. Full Unreal compilation, rendered gameplay and packaged execution remain unverified in the delivery environment, which has no Unreal installation. Follow the included local acceptance checklist.

This is a pattern-recall prototype, not a validated IQ test, clinical assessment or astronaut selection tool. Patterns reduce reliance on factual knowledge but do not establish fairness across ages and education. No NASA affiliation or endorsement is claimed.
