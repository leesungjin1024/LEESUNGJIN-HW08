
#include "HUDWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

void UHUDWidget::SetScore(int32 InScore)
{
    if (ScoreText != nullptr)
    {
        ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score : %03d"), InScore)));
    }
}

void UHUDWidget::SetTime(int32 InTime)
{
    if (TimeText != nullptr)
    {
        TimeText->SetText(FText::FromString(FString::Printf(TEXT("Time : %03d"), InTime)));
    }
}

void UHUDWidget::SetHp(float InCurrentHp, float InMaxHp)
{
    if (HPBar != nullptr && InMaxHp > 0.0f)
    {
        HPBar->SetPercent(InCurrentHp/ InMaxHp);
    }
}
