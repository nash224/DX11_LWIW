#pragma once

enum class EQUESTTYPE
{
	StartTraining,
	House_Dust,
	Clean_Dust,
	FindWorkPlace,
	Craft_Potion,
	Repair_Extractor,
	Aurea_Find,
	Aurea_Cure,
	Crow_Meet,
	Dian_Catalogue,
	Dian_BadWeedPotion,
	Dian_Cracker_Recipe,
	Craft_Cracker_Potion,
	Max,
};


// 설명 : Bool자료형의 이벤트 변수를 전역으로 제공합니다. 
class ContentsEvent
{
public:
	class QuestUnitBase : public std::enable_shared_from_this<QuestUnitBase>
	{
	public:
		bool CheckPrerequisiteQuest() 
		{
			if (true == isQuestCompleted)
			{
				return false;
			}

			if (true == QuestClearPrerequisite())
			{
				return true;
			}

			return false;
		}

		bool isQuestComplete() const
		{
			return isQuestCompleted;
		}

		void QuestComplete()
		{
			if (true == isQuestCompleted)
			{
				return;
			}

			CompleteInternal();

			isQuestAccepted = true;
			isQuestCompleted = true;
		}


		bool IsQuestAccepted() const
		{
			return isQuestAccepted;
		}

		void QuestAccept() 
		{
			if (true == isQuestAccepted)
			{
				return;
			}

			AcceptInternal();

			isQuestAccepted = true;
		}

		template<typename ConvertType>
		std::shared_ptr<ConvertType> Get_DynamicCast_This()
		{
			std::shared_ptr<ContentsEvent::QuestUnitBase> Quest = shared_from_this();
			std::shared_ptr<ConvertType> CastQuest = std::dynamic_pointer_cast<ConvertType>(Quest);

			if (nullptr == CastQuest)
			{
				MsgBoxAssert("다이나믹 캐스팅에 실패했습니다.");
				return nullptr;
			}

			return CastQuest;
		}

	protected:
		virtual void AcceptInternal() {}
		virtual bool QuestClearPrerequisite() = 0;
		virtual void CompleteInternal() {}
			

	public:
		// ContentsGUI에서 요구합니다. 
		// 절때 외부로 공개할 일은 없지만
		// friend 선언을 해도 안먹혀서 public으로 둡니다.
		bool isQuestCompleted = false;

	protected:
		bool isQuestAccepted = false;

	};

	class StartTraining : public QuestUnitBase
	{
	public:
		void AcceptInternal() override;
		bool QuestClearPrerequisite() override;
		void CompleteInternal() override;

	};

	class Aurea_Find : public QuestUnitBase
	{
	public:
		bool QuestClearPrerequisite() override;

	};

	class House_Dust : public QuestUnitBase
	{
	public:
		bool QuestClearPrerequisite() override;

	};

	class FindWorkPlace : public QuestUnitBase
	{
	public:
		bool QuestClearPrerequisite() override;

	};

	class Craft_Potion : public QuestUnitBase
	{
	public:
		void AcceptInternal() override;
		bool QuestClearPrerequisite() override;
		void CompleteInternal() override;

	};

	class Repair_Extractor : public QuestUnitBase
	{
	public:
		void AcceptInternal() override;
		bool QuestClearPrerequisite() override;
		void CompleteInternal() override;

	};

	class Aurea_Cure : public QuestUnitBase
	{
	public:
		void AcceptInternal() override;
		bool QuestClearPrerequisite() override;
		void CompleteInternal() override;

	};

	class Crow_Meet : public QuestUnitBase
	{
	public:
		bool QuestClearPrerequisite() override;
		void CompleteInternal() override;

		int GetEventDay() const
		{
			return EventDay;
		}

	private:
		int EventDay = -999;

	};

	class Dian_Catalogue : public QuestUnitBase
	{
	public:
		bool QuestClearPrerequisite() override;

	};

	class Dian_BadWeedPotion : public QuestUnitBase
	{
	public:
		void AcceptInternal() override;
		bool QuestClearPrerequisite() override;
		void CompleteInternal() override;

	};

	class Dian_Cracker : public QuestUnitBase
	{
	public:
		void AcceptInternal() override;
		bool QuestClearPrerequisite() override;
		void CompleteInternal() override;
	};

	class Craft_Cracker_Potion : public QuestUnitBase
	{
	public:
		bool QuestClearPrerequisite() override;
		void CompleteInternal() override;
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
	static bool HasWitchBroom;
	static std::map<std::string, std::shared_ptr<QuestUnitBase>> QuestData;

};