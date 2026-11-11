"""Run in UE Editor after compiling the C++ module. Creates only a missing map."""
import unreal
from pathlib import Path
project = Path(unreal.Paths.convert_relative_path_to_full(unreal.Paths.project_dir()))
tasks = []
for index in range(1, 5):
    destination = f"/Game/Audio/Tone{index}"
    if not unreal.EditorAssetLibrary.does_asset_exist(destination):
        task = unreal.AssetImportTask()
        task.set_editor_property("filename", str(project / "Assets" / "Audio" / f"Tone{index}.wav"))
        task.set_editor_property("destination_path", "/Game/Audio")
        task.set_editor_property("automated", True)
        task.set_editor_property("save", True)
        tasks.append(task)
if tasks:
    unreal.AssetToolsHelpers.get_asset_tools().import_asset_tasks(tasks)
for index in range(1, 5):
    if not unreal.EditorAssetLibrary.does_asset_exist(f"/Game/Audio/Tone{index}"):
        raise RuntimeError("Tone import failed; check Assets/Audio and Output Log")
unreal.log("Audio assets ready. Restart editor after initial setup to load sound references.")
MAP = "/Game/Maps/LaunchSite"
if unreal.EditorAssetLibrary.does_asset_exist(MAP):
    unreal.log("LaunchSite already exists; keeping your map unchanged.")
else:
    subsystem = unreal.get_editor_subsystem(unreal.LevelEditorSubsystem)
    if not subsystem.new_level(MAP):
        raise RuntimeError("Could not create LaunchSite")
    world = unreal.get_editor_subsystem(unreal.UnrealEditorSubsystem).get_editor_world()
    mode = unreal.load_class(None, "/Script/SPaceIQ.MissionMode")
    if mode is None:
        raise RuntimeError("Compile SPaceIQEditor before generating the map")
    world.get_world_settings().set_editor_property("default_game_mode", mode)
    if not subsystem.save_current_level():
        raise RuntimeError("Could not save LaunchSite")
    unreal.log("LaunchSite saved. Press Play to begin SPace IQ.")
