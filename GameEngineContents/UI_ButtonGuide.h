#pragma once

enum class EBUTTONTYPE
{
	A,
	C,
	D,
	S,
	X,
	Z,
	Z_PressHold,
	QW,
	ER,
	Ctrl,
	Shift,
	Space,
	Tab,
	Arrow_1,
	Arrow_Horizontal,
	Arrow_Vertical,
	None,
};

class ButtonInfoParameter
{
public:
	ButtonInfoParameter(EBUTTONTYPE _Type, std::string_view _Text)
		: Type(_Type), Text(_Text)
	{

	}

public:
	EBUTTONTYPE Type; 
	std::string Text;

};


class UI_ButtonGuide
{
private:
	class ButtonInfo
	{
	public:
		std::shared_ptr<GameEngineUIRenderer> ButtonRenderer;
		std::shared_ptr<GameEngineUIRenderer> GuideRenderer;
		EBUTTONTYPE ButtonType = EBUTTONTYPE::None;
		float ButtonToTextSize = 0;

	};

public:
	// constrcuter destructer
	UI_ButtonGuide();
	~UI_ButtonGuide();

	// delete Function
	UI_ButtonGuide(const UI_ButtonGuide& _Other) = delete;
	UI_ButtonGuide(UI_ButtonGuide&& _Other) noexcept = delete;
	UI_ButtonGuide& operator=(const UI_ButtonGuide& _Other) = delete;
	UI_ButtonGuide& operator=(UI_ButtonGuide&& _Other) noexcept = delete;

	void SetGuideInfo(GameEngineActor* _Actor, const std::vector<ButtonInfoParameter>& _Paras);

	void On();
	void Off();

private:
	std::string ReturnButtonSpriteName(EBUTTONTYPE _Type) const;
	float GetTotalSize(std::string_view _FileName, int _StringSize) const;

private:
	std::vector<ButtonInfo> Guides;

};

