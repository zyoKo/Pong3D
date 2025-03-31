#pragma once

UENUM(BluePrintType)
enum class EPaddleType : uint8
{
	PLAYER_1 UMETA(DisplayName = "Player One"),
	PLAYER_2 UMETA(DisplayName = "Player Two"),
	AI       UMETA(DisplayName = "AI"),
	NONE	 UMETA(DisplayName = "None")
};