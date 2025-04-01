// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class CharacterLabStart54Target : TargetRules
{
    private bool bFasterWithoutUnity;

    public CharacterLabStart54Target(TargetInfo Target, bool bFasterWithoutUnity) : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
        ExtraModuleNames.Add("CharacterLabStart54");

        // Add the missing macro here
        ExtraModuleNames.AddRange(new string[] { "MyProject" });

        bUsePCHFiles = true;
        bFasterWithoutUnity = true;

        // Add the preprocessor macro
        GlobalDefinitions.Add("TEXTURESHARECORE_DEBUGLOG=1");
        this.bFasterWithoutUnity = bFasterWithoutUnity;
    }
}


