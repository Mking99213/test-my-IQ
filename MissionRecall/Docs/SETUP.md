# Setup and local verification

## Requirements
- Unreal Engine 5.8.4 through Epic Games Launcher (or a compatible source build).
- Windows: Visual Studio 2022 with **Game development with C++**, the MSVC and Windows SDK versions supported by your UE 5.8 installation. Mac: an Xcode version supported by your UE version. Linux: Epic's matching toolchain and a working UE installation.
- A desktop with UE5-capable graphics. Python scripting is an editor plugin enabled in the project; it is not required by the packaged game.

## Open and build
1. Extract the entire ZIP into a writable folder. Keep `MissionRecall.uproject`, `Source`, `Config`, `Scripts` together.
2. On Windows, right-click `MissionRecall.uproject` → Generate Visual Studio project files. Open the generated solution. Build **Development Editor / Win64 / MissionRecall**. Alternatively open the .uproject and accept the prompt to compile missing modules. On Mac/Linux generate project files and compile `MissionRecallEditor` using your engine's normal workflow.
3. Open the .uproject with UE 5.8. A missing LaunchSite map warning on the first open is expected: no binary .umap is shipped. Dismiss it or open a new empty level.
4. In **Tools → Execute Python Script**, choose `Scripts/create_map.py`. If that menu is absent, enable **Python Editor Script Plugin** and **Editor Scripting Utilities**, restart, and try again. The script creates and saves `/Game/Maps/LaunchSite`. It preserves an existing map.
5. **Close and reopen Unreal after the script imports the tones.** Then open `Content/Maps/LaunchSite` and press **Play** in Selected Viewport or New Editor Window. Ensure Play uses the default player at a current camera location or default spawn; runtime geometry is created by the game mode. A PlayerStart is not required.

To create the map via command line after a successful editor build:

Windows PowerShell (replace paths; run from the extracted project folder):
```powershell
& 'C:\Program Files\Epic Games\UE_5.8\Engine\Binaries\Win64\UnrealEditor-Cmd.exe' "$PWD\MissionRecall.uproject" "-ExecutePythonScript=$PWD\Scripts\create_map.py" -unattended -nosplash -NullRHI
```
Use your platform's UnrealEditor-Cmd binary on Linux/Mac. The interactive Tools menu path is recommended for the first run.

## Package a downloadable game
1. Generate/save the map and validate Play in Editor first.
2. Project Settings → Maps & Modes: verify both default maps are LaunchSite, and default game mode is MissionMode.
3. Platforms → your desktop platform → Package Project. Install a matching SDK/toolchain if prompted. Development packaging is sufficient for a hackathon; use Shipping for a release after testing.
4. Run the produced executable outside the editor. ZIP the **entire packaged output directory**, including content, dependencies and executable. The provided source ZIP is different from this game distribution.

## Demo acceptance checklist (requires Unreal locally)
- Start: astronaut, rocket, apron, three orange indicators, title and briefing are visible.
- Walk with WASD; astronaut remains within the apron boundary.
- Start with Space or Begin Mission; no pattern input is accepted while flashes play.
- Enter a wrong symbol: retry count increases once, the same pattern replays, system count stays fixed.
- Enter each correct sequence: system count advances 1/3, 2/3, 3/3; each corresponding lamp turns green.
- Repeated symbols display separately with a dark interval.
- Launch is unavailable before all systems pass. Space after 3/3 boards crew and starts countdown.
- Rocket rises after five seconds; success appears after six more seconds.
- R works during observe, recall, countdown and victory; rocket returns, crew reappears, lamps and progress reset.
- Mouse buttons and keyboard both work; test in 1280×720 and the packaged game.

## Portable rules check
No UE required:
```sh
g++ -std=c++17 -Wall -Wextra -pedantic Tests/mission_test.cpp -o mission_test
./mission_test
```

## Troubleshooting
- Missing module: compile the **Editor** target, check compiler/SDK compatibility, and read the first error in the build output.
- Blank scene: verify MissionMode is the map's GameMode override and Play is running, not Simulate. Static editor viewport is empty because geometry spawns at runtime.
- Missing map when cooking: run create_map.py and verify LaunchSite is saved under Content/Maps.
- Keys do nothing: click inside the Play viewport. Shift+F1 releases the mouse in editor play.
- Later UE version: switch the engine association through the .uproject context menu and regenerate/build. Treat warnings and target-setting changes as local upgrade work.

## Added modes and results
Before starting, press M or click Mode to select Visual, Audio, or Both. Audio symbols map low-to-high to keys 1–4. Verify each cue through headphones, and verify audio-only hides flashes. Complete all systems and inspect Saved/Results/sessions.csv. Repeat after R to verify a new row and matching initial pattern. See VSCODE.md for editor build tasks and COMPARISON_PROTOCOL.md for interpretation limits.
