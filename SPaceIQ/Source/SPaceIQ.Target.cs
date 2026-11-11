using UnrealBuildTool;
using System.Collections.Generic;
public class SPaceIQTarget : TargetRules {
 public SPaceIQTarget(TargetInfo Target) : base(Target) {
  Type = TargetType.Game; DefaultBuildSettings = BuildSettingsVersion.Latest;
  IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
  ExtraModuleNames.Add("SPaceIQ");
 }
}
