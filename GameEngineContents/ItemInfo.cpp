#include "PreCompile.h"
#include "ItemInfo.h"

std::map<std::string, BiologyData> ItemInfo::BiologyInfo;
ItemInfo::ItemInfo() 
{
}

ItemInfo::~ItemInfo() 
{

}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////



void ItemInfo::InsertItemInfo(const BiologyData& _Info)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_Info.BiologyName);

	BiologyInfo.insert(std::make_pair(UpperName, _Info));
}

const BiologyData& ItemInfo::GetBiologyInfo(std::string_view _BiologyName)
{
	return BiologyInfoFind(_BiologyName);
}

const BiologyData& ItemInfo::BiologyInfoFind(std::string_view _BiologyName)
{
	std::string UpperName = GameEngineString::ToUpperReturn(_BiologyName);

	std::map<std::string, BiologyData>::iterator FindIter = BiologyInfo.find(UpperName);
	if (FindIter == BiologyInfo.end())
	{
		MsgBoxAssert("������ ������ ã�� ���߽��ϴ�. ���� Ȯ�����ּ���.");
		static const BiologyData ReturnValue ;
		return ReturnValue;
	}

	return FindIter->second;
}