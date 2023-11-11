#pragma once

enum class EALERTTYPE
{
	Enter,
	QuestAccept,
	QuestClear,
	Tutorial,
	None,
};

class AlertData
{
public:
	AlertData(std::string_view _AlertName, EALERTTYPE _Type)
		:
		Type(_Type),
		AlertName(_AlertName)
	{

	}

public:
	std::string AlertName;
	EALERTTYPE Type;

};


// Ό³Έν :
class AlertManager
{
	friend class PlayLevel;
	friend class UI_Alert_Quest;
	friend class UI_Alert_Enter;

private:
	static bool isAlerting;

public:
	// constrcuter destructer
	AlertManager();
	~AlertManager();

	// delete Function
	AlertManager(const AlertManager& _Other) = delete;
	AlertManager(AlertManager&& _Other) noexcept = delete;
	AlertManager& operator=(const AlertManager& _Other) = delete;
	AlertManager& operator=(AlertManager&& _Other) noexcept = delete;

	void RegisterAlert(const AlertData& _Data);

protected:
	void Update(float _Delta);
	void AlertCall(const std::shared_ptr<AlertData>& _Data);


private:
	std::list<std::shared_ptr<AlertData>> Data;

	float AlertTime = 0.0f;

};

