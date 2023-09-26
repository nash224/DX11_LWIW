#include "PreCompile.h"
#include "ItemInfo.h"

std::map<std::string, std::shared_ptr<BiologyData>> ItemInfo::BiologyInfo;
ItemInfo::ItemInfo() 
{
}

ItemInfo::~ItemInfo() 
{

}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////



void ItemInfo::CreateData(const BiologyData& _Info)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Info.BiologyName);

	std::shared_ptr Data = std::make_shared<BiologyData>(_Info);

	BiologyInfo.insert(std::make_pair(UpperName, Data));
}

const std::shared_ptr<BiologyData>& ItemInfo::GetBiologyInfo(std::string_view _BiologyName)
{
	return FindBiologyInfo(_BiologyName);
}

const std::shared_ptr<BiologyData>& ItemInfo::FindBiologyInfo(std::string_view _BiologyName)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_BiologyName);

	std::map<std::string, std::shared_ptr<BiologyData>>::iterator FindIter = BiologyInfo.find(UpperName);
	if (FindIter == BiologyInfo.end())
	{
		MsgBoxAssert("아이템 정보를 찾지 못했습니다. 값을 확인해주세요.");
		static const std::shared_ptr<BiologyData> ReturnValue;
		return ReturnValue;
	}

	return FindIter->second;
}