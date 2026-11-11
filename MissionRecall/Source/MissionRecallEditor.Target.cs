using UnrealBuildTool;
using System.Collections.Generic;
public class MissionRecallEditorTarget : TargetRules {
 public MissionRecallEditorTarget(TargetInfo Target) : base(Target) {
  Type = TargetType.Editor; DefaultBuildSettings = BuildSettingsVersion.Latest;
  IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
  ExtraModuleNames.Add("MissionRecall");
 }
}
