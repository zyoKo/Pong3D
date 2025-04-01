#pragma once

UENUM(BluePrintType)
enum class EPaddleType : uint8
{
	PLAYER_1 = 0 UMETA(DisplayName = "Player One"),
	PLAYER_2 = 1 UMETA(DisplayName = "Player Two"),
	AI       = 2 UMETA(DisplayName = "AI"),
	NONE	 = 3 UMETA(DisplayName = "None")
};