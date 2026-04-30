
#pragma once

#include "CoreMinimal.h"

#define MYLOG(text, ...) \
{ \
	FString msg = FString::Printf(TEXT(text), ##__VA_ARGS__); \
	UE_LOG(LogTemp, Warning, TEXT("%s"), *msg); \
}

#define MYSCREENLOG(text, ...) \
{ \
   	if (GEngine != nullptr) \
	{ \
		FString msg = FString::Printf(TEXT(text),  ##__VA_ARGS__); \
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, msg); \
	} \
}

#define MYSCREENLOGT(duration, text, ...) \
{ \
   	if (GEngine != nullptr) \
	{ \
		FString msg = FString::Printf(TEXT(text),  ##__VA_ARGS__); \
		GEngine->AddOnScreenDebugMessage(-1, duration, FColor::Blue, msg); \
	} \
}

#define MYGLOG(text, ...) \
{ \
	if (GLog != nullptr) \
	{ \
		FString msg = FString::Printf(TEXT(text),  ##__VA_ARGS__); \
		GLog->Log(msg); \
	} \
}

#define MYLOGTRACE(format, ...) \
{\
      UE_LOG(LogTemp, Warning, TEXT("[%s:%d] " format), \
        TEXT(__FILE__), __LINE__, ##__VA_ARGS__); \
}
