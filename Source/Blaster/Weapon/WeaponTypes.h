#pragma once

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
        EWT_AssaultRiffle UMETA(DisplayName="Assault Rifle"),
        EWT_RocketLauncher UMETA(DisplayName="Rocket Launcher"),

        EWT_MAX UMETA(DisplayName="DefaultMAX")
};