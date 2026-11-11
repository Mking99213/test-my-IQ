using UnrealBuildTool;
using System.Collections.Generic;
public class OrbitRecallEditorTarget : TargetRules {
 public OrbitRecallEditorTarget(TargetInfo Target) : base(Target) {
  Type = TargetType.Editor; DefaultBuildSettings = BuildSettingsVersion.V5;
  ExtraModuleNames.Add("OrbitRecall");
 }
}
