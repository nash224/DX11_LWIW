#pragma once

enum class EQUESTTYPE
{
	Find_Letter,
	Letter_Read,
	Clean_Dust,
	Aurea_Find,
	Aurea_Curse,
	Aurea_UnCurse,
	Crow_Meet,
	Dian_Catalogue,
	Dian_BadWeedPotion,
	Aurea_HealCandy,
	Dian_Cracker_Recipe,
	Max,
};


// ���� : Bool�ڷ����� �̺�Ʈ ������ �������� �����մϴ�. 
class ContentsEvent
{
public:
	class QuestUnitBase
	{
	public:
		virtual bool CheckPrerequisiteQuest() 
		{
			return false;
		}

		bool isQuestComplete() const
		{
			return isQuestCompleted;
		}

		virtual void QuestComplete()
		{
			isQuestCompleted = true;
		}

	public:
		// ContentsGUI���� �䱸�մϴ�. 
		// ���� �ܺη� ������ ���� ������
		// friend ������ �ص� �ȸ����� public���� �Ӵϴ�.
		bool isQuestCompleted = false;

	};

	class Letter_Read : public QuestUnitBase
	{
	public:
		bool CheckPrerequisiteQuest() override;

	};

	class Aurea_Find : public QuestUnitBase
	{
	public:
		bool CheckPrerequisiteQuest() override;

	};

	class Aurea_Curse : public QuestUnitBase
	{
	public:
		bool CheckPrerequisiteQuest() override;

	};

	class Aurea_UnCurse : public QuestUnitBase
	{
	public:
		bool CheckPrerequisiteQuest() override;

	};

	class Crow_Meet : public QuestUnitBase
	{
	public:
		bool CheckPrerequisiteQuest() override;

	};

	class Dian_Cracker : public QuestUnitBase
	{
	public:
		bool CheckPrerequisiteQuest() override;
		void QuestComplete() override;
	};


public:
	// constrcuter destructer
	ContentsEvent();
	~ContentsEvent();

	// delete Function
	ContentsEvent(const ContentsEvent& _Other) = delete;
	ContentsEvent(ContentsEvent&& _Other) noexcept = delete;
	ContentsEvent& operator=(const ContentsEvent& _Other) = delete;
	ContentsEvent& operator=(ContentsEvent&& _Other) noexcept = delete;

	static void Init();

	template<typename QuestType>
	static void CreateQuest(std::string_view _QuestName)
	{
		std::string UpperName = GameEngineString::ToUpperReturn(_QuestName);

		std::shared_ptr<QuestUnitBase> questUnit = std::make_shared<QuestType>();
		QuestData.insert(std::make_pair(UpperName, questUnit));
	}

	static const std::shared_ptr<ContentsEvent::QuestUnitBase> FindQuest(std::string_view _QuestName);


	static void Release();

protected:

public:
	static std::vector<bool> ToolData;
	static std::map<std::string, std::shared_ptr<QuestUnitBase>> QuestData;

};

