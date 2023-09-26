#include "PreCompile.h"
#include "ItemInfo.h"

std::map<std::string, BiologyItemData> ItemInfo::BiologyItemInfo;
ItemInfo::ItemInfo() 
{
}

ItemInfo::~ItemInfo() 
{

}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////



void ItemInfo::InsertItemInfo(const BiologyItemData& _Info)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Info.BiologyName);

	BiologyItemInfo.insert(std::make_pair(UpperName, _Info));
}

const BiologyItemData& ItemInfo::GetBiologyItemInfo(std::string_view _BiologyName)
{
	return BiologyInfoFind(_BiologyName);
}

const BiologyItemData& ItemInfo::BiologyInfoFind(std::string_view _BiologyName)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_BiologyName);

	std::map<std::string, BiologyItemData>::iterator FindIter = BiologyItemInfo.find(UpperName);
	if (FindIter == BiologyItemInfo.end())
	{
		MsgBoxAssert("아이템 정보를 찾지 못했습니다. 값을 확인해주세요.");
		static const BiologyItemData ReturnValue ;
		return ReturnValue;
	}

	return FindIter->second;
}