using UnrealBuildTool;
using System.Collections.Generic;
public class OrbitRecallTarget : TargetRules {
 public OrbitRecallTarget(TargetInfo Target) : base(Target) {
  Type = TargetType.Game; DefaultBuildSettings = BuildSettingsVersion.V5;
  ExtraModuleNames.Add("OrbitRecall");
 }
}
