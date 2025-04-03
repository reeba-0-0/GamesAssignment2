// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class CharacterLabStart54Target : TargetRules
{
    private bool bFasterWithoutUnity;
    public CharacterLabStart54Target(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
        ExtraModuleNames.Add("CharacterLabStart54");
        bUsePCHFiles = true;
        GlobalDefinitions.Add("TEXTURESHARECORE_DEBUGLOG=1");
        // Optional: Remove this if not needed
        // ExtraModuleNames.AddRange(new string[] { "MyProject" });
    }
}


