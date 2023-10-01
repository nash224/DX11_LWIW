#pragma once
#include "UIEnum.h"
#include <memory>
#include <string>
#include <map>



// 설명 :
template <typename DataType>
class ContentsResource
{
public:
	// constrcuter destructer
	ContentsResource() {}
	~ContentsResource() {}

	// delete Function
	//ContentsResource(const ContentsResource& _Other) = delete;
	//ContentsResource(ContentsResource&& _Other) noexcept = delete;
	//ContentsResource& operator=(const ContentsResource& _Other) = delete;
	//ContentsResource& operator=(ContentsResource&& _Other) noexcept = delete;


	static void CreateData(std::string_view _Name, const DataType& _Data)
	{
		std::string UpperName = GameEngineString::ToUpperReturn(_Name);
		std::shared_ptr Data = std::make_shared<DataType>(_Data);
		NameData.insert(std::make_pair(UpperName, Data));
	}

	static const std::shared_ptr<DataType>& GetData(std::string_view _Name)
	{
		return Find(_Name);
	}

	static const std::shared_ptr<DataType>& Find(std::string_view _Name)
	{
		std::string UpperName = GameEngineString::ToUpperReturn(_Name);
		typename std::map<std::string, std::shared_ptr<DataType>>::iterator FindIter = NameData.find(UpperName);
		if (FindIter == NameData.end())
		{
			MsgBoxAssert("아이템 정보를 찾지 못했습니다. 값을 확인해주세요.");
			static const std::shared_ptr<DataType> ReturnValue;
			return ReturnValue;
		}

		return FindIter->second;
	}


private:
	static std::map<std::string, std::shared_ptr<DataType>> NameData;

};

template <typename DataType>
std::map<std::string, std::shared_ptr<DataType>> ContentsResource<DataType>::NameData;