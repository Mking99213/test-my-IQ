# Visual Studio Code workflow (Windows, UE 5.8)

VS Code is the editor. Unreal C++ still requires the MSVC compiler and Windows SDK; VS Code alone cannot build this project.

1. Install Unreal Engine 5.8, VS Code, and Visual Studio 2022 or its Build Tools with Game development with C++, the MSVC toolset and Windows SDK supported by your UE 5.8 installation.
2. Open `MissionRecall.code-workspace` in VS Code and install the recommended Microsoft C/C++ extension.
3. Press Ctrl+Shift+B. Choose UE: Build Editor (Windows) and enter the engine installation folder, for example `C:/Program Files/Epic Games/UE_5.8` (not its Engine subfolder).
4. After a successful build, run Terminal → Run Task → UE: Open Editor (Windows), or open the .uproject normally.
5. Follow SETUP.md to run create_map.py. It imports tones and saves the level. **Close and reopen Unreal after the first import**, because sound references are loaded when the native game mode class is constructed.
6. Open LaunchSite, press Play, choose the mode, and begin.

For engine-aware IntelliSense and generated debug configurations, set Unreal Editor Preferences → Source Code → Source Code Editor to Visual Studio Code, then use Tools → Refresh Visual Studio Code Project (menu naming may vary). Unreal may generate/replace workspace configuration; retain a copy of the supplied tasks if desired. Header errors in VS Code are not a substitute for checking an actual Unreal build.

After changing reflected headers, close Unreal and rebuild the Editor target. Live Coding is optional and is not the recommended first-build workflow.

Mac/Linux: the supplied VS Code tasks are Windows-specific. Use your UE installation's platform Build.sh with target MissionRecallEditor, platform Mac or Linux, configuration Development, and the absolute .uproject path. Install the toolchain supported by your UE version. Follow the same editor map/audio setup afterwards.
