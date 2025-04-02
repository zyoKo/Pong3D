#pragma once

/**
 * Player_1(Left) and Player_2(Right)
 * AI Implementation (Out of the Scope of this project)
 */
UENUM(BluePrintType)
enum class EPaddleType : uint8
{
	PLAYER_1 = 0 UMETA(DisplayName = "Player One"),
	PLAYER_2 = 1 UMETA(DisplayName = "Player Two"),
	AI       = 2 UMETA(DisplayName = "AI"),
	NONE	 = 3 UMETA(DisplayName = "None")
};