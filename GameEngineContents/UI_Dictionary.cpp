#include "PreCompile.h"
#include "UI_Dictionary.h"

#include "UIManager.h"
#include "UI_BiologyPage.h"
#include "UI_ProductPage.h"

EDICTIONARYCATEGORY UI_Dictionary::s_CurrentCategory = EDICTIONARYCATEGORY::None;
int UI_Dictionary::s_CurrentLeftPage = 0;
UI_Dictionary::UI_Dictionary() 
{
	if (EDICTIONARYCATEGORY::None == s_CurrentCategory)
	{
		s_CurrentCategory = EDICTIONARYCATEGORY::CreaturePage;
		s_CurrentLeftPage = 1;
	}

	if (nullptr == GameEngineSprite::Find("Info_Icon.png"))
	{
		GameEngineSprite::CreateCut("Info_Icon.png", 3, 1);
	}
}

UI_Dictionary::~UI_Dictionary() 
{
}


void UI_Dictionary::Start()
{
	UI_ToggleActor::Start();
}

void UI_Dictionary::Update(float _Delta)
{
	if (false == OnLevelStartCheck)
	{
		OnLevelStart();
		OnLevelStartCheck = true;
	}

	UI_ToggleActor::Update(_Delta);

	UpdateDictionary();
}

void UI_Dictionary::OnLevelStart()
{
	OffCategoryMark();
	ChangeCategoryMark();
}

void UI_Dictionary::LevelStart(class GameEngineLevel* _NextLevel)
{
	UI_ToggleActor::LevelStart(_NextLevel);
}

void UI_Dictionary::LevelEnd(class GameEngineLevel* _NextLevel)
{
	UI_ToggleActor::LevelEnd(_NextLevel);

	OffCategoryMark();
	OnLevelStartCheck = false;
}


#pragma region 이니셜

void UI_Dictionary::Init()
{
	CreateBase();
	CreateCategory();

	// CreaturePage
	CreatePage(EDICTIONARYCATEGORY::CreaturePage, "Mongsiri");
	CreatePage(EDICTIONARYCATEGORY::CreaturePage, "PumpkinTerrier");
	CreatePage(EDICTIONARYCATEGORY::CreaturePage, "BushBug");
	CreatePage(EDICTIONARYCATEGORY::CreaturePage, "FlowerBird");
	CreatePage(EDICTIONARYCATEGORY::CreaturePage, "BubbleLizard");

	// PlantPage
	CreatePage(EDICTIONARYCATEGORY::PlantPage, "WitchFlower");
	CreatePage(EDICTIONARYCATEGORY::PlantPage, "SilverStarFlower");
	CreatePage(EDICTIONARYCATEGORY::PlantPage, "MapleHerb");


	// PotionPage
	CreatePage(EDICTIONARYCATEGORY::PotionPage, "BadGrassPotion");
	CreatePage(EDICTIONARYCATEGORY::PotionPage, "NutritionPotion");
	CreatePage(EDICTIONARYCATEGORY::PotionPage, "FirecrackerPotion");

	// CandyPage
	CreatePage(EDICTIONARYCATEGORY::CandyPage, "UncurseCandy");
	CreatePage(EDICTIONARYCATEGORY::CandyPage, "HealingCandy");

	ChangeCategoryMark();

	std::vector<ButtonInfoParameter> Paras = 
	{ 
		{ EBUTTONTYPE::Arrow_Vertical, "카테고리 이동"},
		{ EBUTTONTYPE::Arrow_Horizontal, "페이지 이동"},
		{ EBUTTONTYPE::X, "닫기"},
	};
	UIGuide.SetGuideInfo(this, Paras);
	UIGuide.On();
}

void UI_Dictionary::CreateBase()
{
	const float Depth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Base);

	BookBase = CreateComponent<GameEngineUIRenderer>();
	BookBase->Transform.SetLocalPosition({ 0.0f , 0.0f, Depth });
	BookBase->SetSprite("Base.png");
}

void UI_Dictionary::CreateCategory()
{
	const float AttachmentDepth = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Attachment);

	float4 CategoryPos = float4{ -345.0f , 128.0f };

	Category.Creature = CreateComponent<GameEngineUIRenderer>();
	Category.Creature->SetSprite("Tag_Creature_Normal.png");
	Category.Creature->SetPivotType(PivotType::Right);

	Category.Creature->Transform.SetLocalPosition(float4(CategoryPos.X, CategoryPos.Y, AttachmentDepth));

	constexpr float CategoryGap = 14.0f;

	std::shared_ptr<GameEngineTexture> CreatureTexture = GameEngineTexture::Find("Tag_Creature_Normal.png");
	if (nullptr == CreatureTexture)
	{
		MsgBoxAssert("텍스처를 불러오지 못했습니다.");
		return;
	}

	const float4& HTextureScale = CreatureTexture->GetScale().Half();
	CategoryPos.Y -= HTextureScale.Y + CategoryGap;


	std::shared_ptr<GameEngineTexture> PlantTexture = GameEngineTexture::Find("Tag_Plant_Normal.png");
	if (nullptr == PlantTexture)
	{
		MsgBoxAssert("텍스처를 불러오지 못했습니다.");
		return;
	}

	CategoryPos.Y -= PlantTexture->GetScale().hY();


	Category.Plant = CreateComponent<GameEngineUIRenderer>();
	Category.Plant->SetSprite("Tag_Plant_Normal.png");
	Category.Plant->SetPivotType(PivotType::Right);

	CategoryPos.Z = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Attachment);
	Category.Plant->Transform.SetLocalPosition(CategoryPos);

	CategoryPos.Y -= HTextureScale.Y + CategoryGap;


	std::shared_ptr<GameEngineTexture> PotionTexture = GameEngineTexture::Find("Tag_Potion_Normal.png");
	if (nullptr == PotionTexture)
	{
		MsgBoxAssert("텍스처를 불러오지 못했습니다.");
		return;
	}

	CategoryPos.Y -= PotionTexture->GetScale().hY();


	Category.Potion = CreateComponent<GameEngineUIRenderer>();
	Category.Potion->SetSprite("Tag_Potion_Normal.png");
	Category.Potion->SetPivotType(PivotType::Right);

	CategoryPos.Z = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Attachment);
	Category.Potion->Transform.SetLocalPosition(CategoryPos);

	CategoryPos.Y -= HTextureScale.Y + CategoryGap;


	std::shared_ptr<GameEngineTexture> CandyTexture = GameEngineTexture::Find("Tag_Candy_Normal.png");
	if (nullptr == CandyTexture)
	{
		MsgBoxAssert("텍스처를 불러오지 못했습니다.");
		return;
	}

	CategoryPos.Y -= CandyTexture->GetScale().hY();


	Category.Candy = CreateComponent<GameEngineUIRenderer>();
	Category.Candy->SetSprite("Tag_Candy_Normal.png");
	Category.Candy->SetPivotType(PivotType::Right);

	CategoryPos.Z = DepthFunction::CalculateFixDepth(EUI_RENDERORDERDEPTH::Attachment);
	Category.Candy->Transform.SetLocalPosition(CategoryPos);
}

void UI_Dictionary::CreatePage(EDICTIONARYCATEGORY _Type, std::string_view Name)
{
	switch (_Type)
	{
	case EDICTIONARYCATEGORY::None:
		break;
	case EDICTIONARYCATEGORY::CreaturePage:
	{
		std::shared_ptr<UI_BiologyPage> Page = GetLevel()->CreateActor<UI_BiologyPage>(EUPDATEORDER::UIComponent);
		Page->CreatePage(Name, CreaturePageCount);
		CreaturePages.push_back(Page);
	}
		break;
	case EDICTIONARYCATEGORY::PlantPage:
	{
		std::shared_ptr<UI_BiologyPage> Page = GetLevel()->CreateActor<UI_BiologyPage>(EUPDATEORDER::UIComponent);
		Page->CreatePage(Name, PlantPageCount);
		PlantPages.push_back(Page);
	}
		break;
	case EDICTIONARYCATEGORY::PotionPage:
	{
		std::shared_ptr<UI_ProductPage> Page = GetLevel()->CreateActor<UI_ProductPage>(EUPDATEORDER::UIComponent);
		Page->CreatePage(Name, PotionPageCount);
		PotionPages.push_back(Page);
	}
		break;
	case EDICTIONARYCATEGORY::CandyPage:
	{
		std::shared_ptr<UI_ProductPage> Page = GetLevel()->CreateActor<UI_ProductPage>(EUPDATEORDER::UIComponent);
		Page->CreatePage(Name, CandyPageCount);
		CandyPages.push_back(Page);
	}
		break;
	default:
		break;
	}
}

#pragma endregion


void UI_Dictionary::OpenInternal()
{
	GameEngineInput::IsOnlyInputObject(this);
	OffAllCategoryMark();
	ChangeCategoryMark();
	OpenNextPage(s_CurrentCategory);
}

void UI_Dictionary::CloseInternal()
{
	CloseCurrentPage(s_CurrentCategory);

	GameEngineInput::IsObjectAllInputOn();
}



// 현재 장을 펼칩니다.
void UI_Dictionary::OpenNextPage(EDICTIONARYCATEGORY _Type)
{
	SFXFunction::PlaySFX("SFX_PenCompleteTearPaper.wav");

	if (s_CurrentLeftPage < 1)
	{
		MsgBoxAssert("0페이지는 존재하지 않습니다.");
		return;
	}

	int OpenPage = s_CurrentLeftPage - 1;

	switch (s_CurrentCategory)
	{
	case EDICTIONARYCATEGORY::None:
	{
		MsgBoxAssert("현재 카테고리로는 열람이 불가능합니다.");
		return;
	}
		break;
	case EDICTIONARYCATEGORY::CreaturePage:
	{
		std::weak_ptr<UI_BiologyPage> OddPage = CreaturePages[OpenPage++];
		if (true == OddPage.expired())
		{
			MsgBoxAssert("존재하지 않는 페이지를 참조했습니다.");
			return;
		}

		OddPage.lock()->On();

		if (s_CurrentLeftPage != CreaturePageCount)
		{
			std::weak_ptr<UI_BiologyPage> EvenPage = CreaturePages[OpenPage];
			if (true == EvenPage.expired())
			{
				MsgBoxAssert("존재하지 않는 페이지를 참조했습니다.");
				return;
			}

			EvenPage.lock()->On();
		}
	}
	break;
	case EDICTIONARYCATEGORY::PlantPage:
	{
		std::weak_ptr<UI_BiologyPage> OddPage = PlantPages[OpenPage++];
		if (true == OddPage.expired())
		{
			MsgBoxAssert("존재하지 않는 페이지를 참조했습니다.");
			return;
		}

		OddPage.lock()->On();

		if (s_CurrentLeftPage != PlantPageCount)
		{
			std::weak_ptr<UI_BiologyPage> EvenPage = PlantPages[OpenPage];
			if (true == EvenPage.expired())
			{
				MsgBoxAssert("존재하지 않는 페이지를 참조했습니다.");
				return;
			}

			EvenPage.lock()->On();
		}
	}
	break;
	case EDICTIONARYCATEGORY::PotionPage:
	{
		OpenPage /= 2;
		std::weak_ptr<UI_ProductPage> Page = PotionPages[OpenPage];
		if (true == Page.expired())
		{
			MsgBoxAssert("존재하지 않는 페이지를 참조했습니다.");
			return;
		}

		Page.lock()->On();
	}
		break;
	case EDICTIONARYCATEGORY::CandyPage:
	{
		OpenPage /= 2;
		std::weak_ptr<UI_ProductPage> Page = CandyPages[OpenPage];
		if (true == Page.expired())
		{
			MsgBoxAssert("존재하지 않는 페이지를 참조했습니다.");
			return;
		}

		Page.lock()->On();
	}
		break;
	default:
		break;
	}
}

void UI_Dictionary::CloseCurrentPage(EDICTIONARYCATEGORY _Type)
{
	switch (_Type)
	{
	case EDICTIONARYCATEGORY::None:
		break;
	case EDICTIONARYCATEGORY::CreaturePage:
	{
		for (int i = 0; i < CreaturePages.size(); i++)
		{
			std::shared_ptr<UI_BiologyPage> Object = CreaturePages[i];
			if (nullptr == Object)
			{
				MsgBoxAssert("벡터 배열에 존재하지 않는 액터가 있습니다.");
				return;
			}

			Object->Off();
		}
	}
	break;
	case EDICTIONARYCATEGORY::PlantPage:
	{
		for (int i = 0; i < PlantPages.size(); i++)
		{
			std::shared_ptr<UI_BiologyPage> Object = PlantPages[i];
			if (nullptr == Object)
			{
				MsgBoxAssert("벡터 배열에 존재하지 않는 액터가 있습니다.");
				return;
			}

			Object->Off();
		}
	}
	break;
	case EDICTIONARYCATEGORY::PotionPage:
	{
		for (int i = 0; i < PotionPages.size(); i++)
		{
			std::shared_ptr<UI_ProductPage> Object = PotionPages[i];
			if (nullptr == Object)
			{
				MsgBoxAssert("벡터 배열에 존재하지 않는 액터가 있습니다.");
				return;
			}

			Object->Off();
		}
	}
		break;
	case EDICTIONARYCATEGORY::CandyPage:
	{
		for (int i = 0; i < CandyPages.size(); i++)
		{
			std::shared_ptr<UI_ProductPage> Object = CandyPages[i];
			if (nullptr == Object)
			{
				MsgBoxAssert("벡터 배열에 존재하지 않는 액터가 있습니다.");
				return;
			}

			Object->Off();
		}
	}
		break;
	default:
		break;
	}
}


void UI_Dictionary::UpdateDictionary()
{
	if (true == CheckOpenDictionary())
	{
		return;
	}
	
	if (true == CheckTurningPage())
	{
		return;
	}

	if (true == CheckMoveCategory())
	{
		return;
	}
}

bool UI_Dictionary::CheckOpenDictionary()
{
	if (false == OpenCheck)
	{
		if (true == GameEngineInput::IsDown('X', this))
		{
			Close();
			return true;
		}
	}

	OpenCheck = false;
	return false;
}


bool UI_Dictionary::CheckMoveCategory()
{
	if (true == GameEngineInput::IsDown(VK_DOWN, this))
	{
		NextCategory();
		return true;
	}

	if (true == GameEngineInput::IsDown(VK_UP, this))
	{
		PrevCategory();
		return true;
	}

	return false;
}

bool UI_Dictionary::CheckTurningPage()
{
	if (true == GameEngineInput::IsDown(VK_LEFT, this))
	{
		PrevPage();
		return true;
	}

	if (true == GameEngineInput::IsDown(VK_RIGHT, this))
	{
		NextPage();
		return true;
	}

	return false;
}

void UI_Dictionary::NextPage()
{
	int MaxPage = -1;

	switch (s_CurrentCategory)
	{
	case EDICTIONARYCATEGORY::None:
	{
		MsgBoxAssert("None은 들어올 수 없습니다.");
		return;
	}
	break;
	case EDICTIONARYCATEGORY::CreaturePage:
		MaxPage = CreaturePageCount;
		break;
	case EDICTIONARYCATEGORY::PlantPage:
		MaxPage = PlantPageCount;
		break;
	case EDICTIONARYCATEGORY::PotionPage:
		MaxPage = PotionPageCount;
		break;
	case EDICTIONARYCATEGORY::CandyPage:
		MaxPage = CandyPageCount;
		break;
	default:
		break;
	}

	if (s_CurrentLeftPage == MaxPage || s_CurrentLeftPage + 1 == MaxPage)
	{
		return;
	}

	s_CurrentLeftPage += 2;

	CloseCurrentPage(s_CurrentCategory);
	OpenNextPage(s_CurrentCategory);
}

void UI_Dictionary::PrevPage()
{
	if (s_CurrentLeftPage <= 2)
	{
		return;
	}

	s_CurrentLeftPage -= 2;

	CloseCurrentPage(s_CurrentCategory);
	OpenNextPage(s_CurrentCategory);
}



void UI_Dictionary::PrevCategory()
{
	OffCategoryMark();
	CloseCurrentPage(s_CurrentCategory);

	int CurCategory = static_cast<int>(s_CurrentCategory);
	--CurCategory;
	if (0 == CurCategory)
	{
		CurCategory = 4;
	}

	s_CurrentCategory = static_cast<EDICTIONARYCATEGORY>(CurCategory);

	s_CurrentLeftPage = 1;

	OpenNextPage(s_CurrentCategory);
	ChangeCategoryMark();
}

void UI_Dictionary::NextCategory()
{
	OffCategoryMark();
	CloseCurrentPage(s_CurrentCategory);

	int CurCategory = static_cast<int>(s_CurrentCategory);
	++CurCategory;
	if (5 == CurCategory)
	{
		CurCategory = 1;
	}

	s_CurrentCategory = static_cast<EDICTIONARYCATEGORY>(CurCategory);

	s_CurrentLeftPage = 1;

	OpenNextPage(s_CurrentCategory);
	ChangeCategoryMark();
};

void UI_Dictionary::OffCategoryMark()
{
	switch (s_CurrentCategory)
	{
	case EDICTIONARYCATEGORY::None:
		break;
	case EDICTIONARYCATEGORY::CreaturePage:
		if (nullptr == Category.Creature)
		{
			MsgBoxAssert("렌더러가 존재하지 않습니다");
			return;
		}

		Category.Creature->SetSprite("Tag_Creature_Normal.png");
		break;
	case EDICTIONARYCATEGORY::PlantPage:
		if (nullptr == Category.Plant)
		{
			MsgBoxAssert("렌더러가 존재하지 않습니다");
			return;
		}

		Category.Plant->SetSprite("Tag_Plant_Normal.png");
		break;
	case EDICTIONARYCATEGORY::PotionPage:
		if (nullptr == Category.Potion)
		{
			MsgBoxAssert("렌더러가 존재하지 않습니다");
			return;
		}

		Category.Potion->SetSprite("Tag_Potion_Normal.png");
		break;
	case EDICTIONARYCATEGORY::CandyPage:
		if (nullptr == Category.Candy)
		{
			MsgBoxAssert("렌더러가 존재하지 않습니다");
			return;
		}

		Category.Candy->SetSprite("Tag_Candy_Normal.png");
		break;
	default:
		break;
	}
}

void UI_Dictionary::OffAllCategoryMark()
{
	if (nullptr == Category.Creature 
		|| nullptr == Category.Plant
		|| nullptr == Category.Potion
		|| nullptr == Category.Candy)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다");
		return;
	}

	Category.Creature->SetSprite("Tag_Creature_Normal.png");
	Category.Plant->SetSprite("Tag_Plant_Normal.png");
	Category.Potion->SetSprite("Tag_Potion_Normal.png");
	Category.Candy->SetSprite("Tag_Candy_Normal.png");
}

void UI_Dictionary::ChangeCategoryMark()
{
	switch (s_CurrentCategory)
	{
	case EDICTIONARYCATEGORY::None:
		break;
	case EDICTIONARYCATEGORY::CreaturePage:
		if (nullptr == Category.Creature)
		{
			MsgBoxAssert("렌더러가 존재하지 않습니다");
			return;
		}

		Category.Creature->SetSprite("Tag_Creature_Selected.png");
		break;
	case EDICTIONARYCATEGORY::PlantPage:
		if (nullptr == Category.Plant)
		{
			MsgBoxAssert("렌더러가 존재하지 않습니다");
			return;
		}

		Category.Plant->SetSprite("Tag_Plant_Selected.png");
		break;
	case EDICTIONARYCATEGORY::PotionPage:
		if (nullptr == Category.Potion)
		{
			MsgBoxAssert("렌더러가 존재하지 않습니다");
			return;
		}

		Category.Potion->SetSprite("Tag_Potion_Selected.png");
		break;
	case EDICTIONARYCATEGORY::CandyPage:
		if (nullptr == Category.Candy)
		{
			MsgBoxAssert("렌더러가 존재하지 않습니다");
			return;
		}

		Category.Candy->SetSprite("Tag_Candy_Selected.png");
		break;
	default:
		break;
	}
}