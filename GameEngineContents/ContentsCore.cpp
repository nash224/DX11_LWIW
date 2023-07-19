#include "PreCompile.h"
#include "ContentsCore.h"

ContentsCore::ContentsCore() 
{
}

ContentsCore::~ContentsCore() 
{
}

void ContentsCore::Start()
{

}

void ContentsCore::Update(float _Delta)
{
	HDC DC;
	{
		// ������ Ŭ����
		DC = GameEngineCore::MainWindow.GetBackBuffer()->GetImageDC();
		float4 WinScale = GameEngineCore::MainWindow.GetScale();
		Rectangle(DC, 0, 0, WinScale.iX(), WinScale.iY());
	}


	{
		// ��ü�μ��� ũ�� ȸ�� ��ġ
		static float4 Scale = {100.0f, 100.0f, 100.0f}; // ũ��
		static float4 Rotation = {0, 0, 0}; // ȸ��
		static float4 Position = {100.0f, 100.0f, 100.0f }; // �̵�

		//static float Dir = 1.0f;

		//Scale -= float4(100.0f, 100.0f, 100.0f) * _Delta * Dir;

		//if (100.0f <= abs(Scale.X))
		//{
		//	Dir *= -1.0f;
		//}


		Rotation.X += 360.0f * _Delta;
		Rotation.Y += 360.0f * _Delta;
		Rotation.Z += 360.0f * _Delta;


		// ���ð� ������ �����Դϴ�.
		// �簢���� ����� ���ؼ� ���� 4�� ��������ϴ�.
		// �ٷ� ����� �ٷθ����
		// ������ �������� �ʴ´�.

		// ���û���
		std::vector<float4> Vertex;
		Vertex.resize(4 * 6);

		// �ո�
		Vertex[0] = { -0.5f, -0.5f, -0.5f };
		Vertex[1] = { 0.5f, -0.5f, -0.5f };
		Vertex[2] = { 0.5f, 0.5f, -0.5f };
		Vertex[3] = { -0.5f, 0.5f, -0.5f };

		// �޸�
		Vertex[4] = float4::VectorRotationToDegX(Vertex[0], 180.0f);
		Vertex[5] = float4::VectorRotationToDegX(Vertex[1], 180.0f);
		Vertex[6] = float4::VectorRotationToDegX(Vertex[2], 180.0f);
		Vertex[7] = float4::VectorRotationToDegX(Vertex[3], 180.0f);

		//// �����̳� ������
		//Vertex[8] = float4::VectorRotationToDegY(Vertex[0], 90.0f);
		//Vertex[9] = float4::VectorRotationToDegY(Vertex[1], 90.0f);
		//Vertex[10] = float4::VectorRotationToDegY(Vertex[2], 90.0f);
		//Vertex[11] = float4::VectorRotationToDegY(Vertex[3], 90.0f);

		//// �����̳� ������
		//Vertex[12] = float4::VectorRotationToDegY(Vertex[0], -90.0f);
		//Vertex[13] = float4::VectorRotationToDegY(Vertex[1], -90.0f);
		//Vertex[14] = float4::VectorRotationToDegY(Vertex[2], -90.0f);
		//Vertex[15] = float4::VectorRotationToDegY(Vertex[3], -90.0f);

		//// ���ų� �Ʒ�
		//Vertex[16] = float4::VectorRotationToDegX(Vertex[0], 90.0f);
		//Vertex[17] = float4::VectorRotationToDegX(Vertex[1], 90.0f);
		//Vertex[18] = float4::VectorRotationToDegX(Vertex[2], 90.0f);
		//Vertex[19] = float4::VectorRotationToDegX(Vertex[3], 90.0f);

		//Vertex[20] = float4::VectorRotationToDegX(Vertex[0], -90.0f);
		//Vertex[21] = float4::VectorRotationToDegX(Vertex[1], -90.0f);
		//Vertex[22] = float4::VectorRotationToDegX(Vertex[2], -90.0f);
		//Vertex[23] = float4::VectorRotationToDegX(Vertex[3], -90.0f);



		std::vector<int> Index = 
		{
			0, 1, 2, 
			0, 2, 3,
			0 + 4, 1 + 4, 2 + 4,
			0 + 4, 2 + 4, 3 + 4,
			//0 + 8, 1 + 8, 2 + 8,
			//0 + 8, 2 + 8, 3 + 8,
			//0 + 12, 1 + 12, 2 + 12,
			//0 + 12, 2 + 12, 3 + 12,
			//0 + 16, 1 + 16, 2 + 16,
			//0 + 16, 2 + 16, 3 + 16,
			//0 + 20, 1 + 20, 2 + 20,
			//0 + 20, 2 + 20, 3 + 20,
		};

		// 0   1
		// 3   2


		// ù��° ���
		// Vertex[0] = { -0.5f, -0.5f }; 16
		// Vertex[1] = { 0.5f, -0.5f }; 16
		// Vertex[2] = { 0.5f, 0.5f }; 16
		// 
		// Vertex1[0] = { -0.5f, -0.5f }; 16
		// Vertex1[1] = { 0.5f, -0.5f }; 16
		// Vertex1[2] = { 0.5f, 0.5f }; 16 
		// 
		// �ι�° ���
		// Vertex[0] = { -0.5f, -0.5f }; 16
		// Vertex[1] = { 0.5f, -0.5f }; 16
		// Vertex[2] = { 0.5f, 0.5f }; 16
		// Vertex[3] = { -0.5f, 0.5f }; 16
		// 
		// short Arr[2][3] = {{0, 1, 2}, {0, 2, 3}}; 24

		for (size_t indexCount = 0; indexCount < Index.size() / 3; indexCount++)
		{
			int ArrIndex[3];
			ArrIndex[0] = Index[indexCount * 3 + 0];
			ArrIndex[1] = Index[indexCount * 3 + 1];
			ArrIndex[2] = Index[indexCount * 3 + 2];

			std::vector<POINT> Tri;
			Tri.resize(3);
			for (size_t VertexCount = 0; VertexCount < Tri.size(); VertexCount++)
			{
				// ��ġ�� �����������ؼ� ���� ���·� �������״ٰ� �Ѵ�.
				float4 WorldPoint = Vertex[ArrIndex[VertexCount]];

				// ��ġ ũ�� ȸ���� �����ų�� ���������� �����
				// �������� ������ �ֽ��ϴ�.
				// ũ�� ȸ�� ��ġ ������� ������Ѿ� �մϴ�.

				WorldPoint *= Scale;
				WorldPoint = WorldPoint.VectorRotationToDegX(Rotation.X);
				WorldPoint = WorldPoint.VectorRotationToDegY(Rotation.Y);
				WorldPoint = WorldPoint.VectorRotationToDegZ(Rotation.Z);
				WorldPoint += Position;
				Tri[VertexCount] = WorldPoint.WindowPOINT();
			}
			Polygon(DC, &Tri[0], Tri.size());
		}


		GameEngineCore::MainWindow.DoubleBuffering();
	}
}

void ContentsCore::Release()
{

}