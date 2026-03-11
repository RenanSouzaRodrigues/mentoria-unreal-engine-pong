#pragma once

namespace DSDebug {
	static void ErrorMessage(const FString& Message) {
		const auto finalMessage = "Game Error: " + Message;
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Red, finalMessage);
	}
	
	static void SuccessMessage(const FString& Message) {
		const auto finalMessage = "Game Success: " + Message;
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Green, finalMessage);
	}
	
	static void WarnMessage(const FString& Message) {
		const auto finalMessage = "Game Warning: " + Message;
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Orange, finalMessage);
	}
	
	static void InfoMessage(const FString& Message) {
		const auto finalMessage = "Game Info: " + Message;
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Cyan, finalMessage);
	}
}