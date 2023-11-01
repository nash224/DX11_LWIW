#pragma once

enum class EEVENTTYPE
{
	Crow_Meet,
	Dian_Quest_1,
	Dian_Quest_2,
	Dian_Quest_3,
	Dian_Quest_4,
	Dian_Quest_5,
	Aurea_Quest_1,
	Aurea_Quest_2,
	Aurea_Quest_3,
	Aurea_Quest_4,
	Virgil_Quest_1,
	Virgil_Quest_2,
	Virgil_Quest_3,
	Virgil_Quest_4,
	Guide_Machine_Juicy,
	Guide_Machine_Dispensation,
	Guide_Machine_Roaster,
	Guide_Interactive_1,
	Guide_Tool_DragonFly,
	Max,
};






// 설명 : Bool자료형의 이벤트 변수를 전역으로 제공합니다. 
class ContentsData
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

		void QuestComplete()
		{
			isQuestCompleted = true;
		}

	private:
		bool isQuestCompleted = false;

	};


	class Crow_Meet : public QuestUnitBase
	{
	public:
		bool CheckPrerequisiteQuest() override;

	};

	class Dian_Quest_1 : public QuestUnitBase
	{
	public:
		bool CheckPrerequisiteQuest() override;

	};

	class Dian_Quest_2 : public QuestUnitBase
	{
	public:
		bool CheckPrerequisiteQuest() override;

	};

	class Dian_Quest_3 : public QuestUnitBase
	{
	public:
		bool CheckPrerequisiteQuest() override;

	};

	class Dian_Quest_4 : public QuestUnitBase
	{
	public:
		bool CheckPrerequisiteQuest() override;

	};

	class Dian_Quest_5 : public QuestUnitBase
	{
	public:
		bool CheckPrerequisiteQuest() override;

	};



public:
	// constrcuter destructer
	ContentsData();
	~ContentsData();

	// delete Function
	ContentsData(const ContentsData& _Other) = delete;
	ContentsData(ContentsData&& _Other) noexcept = delete;
	ContentsData& operator=(const ContentsData& _Other) = delete;
	ContentsData& operator=(ContentsData&& _Other) noexcept = delete;

	static void Init();

	template<typename QuestType, typename EnumType>
	static void CreateQuest(EnumType _Enum)
	{
		CreateQuest<QuestType>(static_cast<int>(_Enum));
	}

	template<typename QuestType>
	static void CreateQuest(int _Enum)
	{
		std::shared_ptr<QuestUnitBase> questUnit = std::make_shared<QuestType>();
		QuestData.insert(std::make_pair(static_cast<int>(_Enum), questUnit));
	}


	template<typename EnumType>
	static const std::shared_ptr<ContentsData::QuestUnitBase> FindQuest(EnumType _Enum)
	{
		return FindQuest(static_cast<int>(_Enum));
	}

	static const std::shared_ptr<ContentsData::QuestUnitBase> FindQuest(int _Enum);


	static void Release();

protected:

public:
	static std::vector<bool> ToolData;
	static std::map<int, std::shared_ptr<QuestUnitBase>> QuestData;

};

