# Mission Recall — Unreal Engine 5.8.4 upgrade

This source revision targets the UE 5.8 installation family shown in your launcher screenshot (5.8.4). The engine association is 5.8; the launcher installation folder is normally UE_5.8. This is not a claim that 5.8.4 is the newest available release globally.

## Changes
- Renamed the project, C++ module, game/editor targets, exported API macro, VS Code workspace and display name to MissionRecall / Mission Recall.
- Updated the project engine association and VS Code engine path to 5.8.
- Build targets use BuildSettingsVersion.Latest and EngineIncludeOrderVersion.Latest so the installed engine supplies its defaults.
- The map script uses UnrealEditorSubsystem for editor-world access.
- Added retained engine mesh/material references and an explicit audio cook directory for packaged procedural scenes.
- Preserved visual/audio/combined recall, seeded patterns, results CSV, rocket preparation and launch.

## Fresh setup recommended
1. Finish installing UE 5.8.4 in Epic Games Launcher. The earlier screenshot showed an installation dialog, not a completed installation.
2. Extract MissionRecall-UE5.8-Starter.zip to a new writable directory. Do not overlay generated files from the old OrbitRecall project.
3. Install the compiler and Windows SDK supported by your UE 5.8 build. VS Code does not include a C++ compiler. If UBT reports an unsupported toolchain, install the exact version it recommends through Visual Studio Installer.
4. Open MissionRecall.code-workspace. Run the build task with engine root C:/Program Files/Epic Games/UE_5.8 (or your actual install folder).
5. Open MissionRecall.uproject, run Scripts/create_map.py using Tools → Execute Python Script, close and reopen the editor, open LaunchSite and press Play.

Keep the old project as a backup. The native module was renamed, so an old saved level referencing /Script/OrbitRecall.MissionMode is not a drop-in replacement. This archive generates a fresh level referencing /Script/MissionRecall.MissionMode. Custom maps or Blueprints need their game-mode/class references updated manually; no automatic asset migration is claimed.

## Validation boundary
Portable mission tests, script syntax, JSON consistency, rename references and ZIP integrity are checked here. UE 5.8.4 is not installed in this environment. UnrealHeaderTool, native compilation, editor scripting API compatibility, play, audio and packaged builds still require local verification. Latest target defaults are a migration setting, not proof of compatibility. Use the acceptance checklist and report the first build error if compilation fails.

## Mission Recall rename
The current project is MissionRecall. Extract it to a fresh folder. Both former OrbitRecall and SPaceIQ projects have different native module names; update custom map and Blueprint references to /Script/MissionRecall.MissionMode manually. Do not reuse their Binaries or Intermediate directories.
