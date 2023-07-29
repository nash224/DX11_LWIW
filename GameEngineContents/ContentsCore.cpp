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
		// ���ð� ������ �����Դϴ�.
		// �簢���� ����� ���ؼ� ���� 4�� ��������ϴ�.
		// �ٷ� ����� �ٷθ����
		// ������ �������� �ʴ´�.

		// ���û���
		std::vector<float4> Vertex;
		Vertex.resize(4 * 6);

		float4 BaseVertexs[4];

		BaseVertexs[0] = { -0.5f, -0.5f, -0.5f, 1.0f };
		BaseVertexs[1] = { 0.5f, -0.5f, -0.5f, 1.0f };
		BaseVertexs[2] = { 0.5f, 0.5f, -0.5f, 1.0f };
		BaseVertexs[3] = { -0.5f, 0.5f, -0.5f, 1.0f };

		// �ո�
		Vertex[0] = BaseVertexs[0];
		Vertex[1] = BaseVertexs[1];
		Vertex[2] = BaseVertexs[2];
		Vertex[3] = BaseVertexs[3];

		// �޸�
		Vertex[4] = float4::VectorRotationToDegX(BaseVertexs[0], 180.0f);
		Vertex[5] = float4::VectorRotationToDegX(BaseVertexs[1], 180.0f);
		Vertex[6] = float4::VectorRotationToDegX(BaseVertexs[2], 180.0f);
		Vertex[7] = float4::VectorRotationToDegX(BaseVertexs[3], 180.0f);

		// �����̳� ������
		Vertex[8] = float4::VectorRotationToDegY(BaseVertexs[0], 90.0f);
		Vertex[9] = float4::VectorRotationToDegY(BaseVertexs[1], 90.0f);
		Vertex[10] = float4::VectorRotationToDegY(BaseVertexs[2], 90.0f);
		Vertex[11] = float4::VectorRotationToDegY(BaseVertexs[3], 90.0f);

		// �����̳� ������
		Vertex[12] = float4::VectorRotationToDegY(BaseVertexs[0], -90.0f);
		Vertex[13] = float4::VectorRotationToDegY(BaseVertexs[1], -90.0f);
		Vertex[14] = float4::VectorRotationToDegY(BaseVertexs[2], -90.0f);
		Vertex[15] = float4::VectorRotationToDegY(BaseVertexs[3], -90.0f);

		// ���ų� �Ʒ�
		Vertex[16] = float4::VectorRotationToDegX(BaseVertexs[0], 90.0f);
		Vertex[17] = float4::VectorRotationToDegX(BaseVertexs[1], 90.0f);
		Vertex[18] = float4::VectorRotationToDegX(BaseVertexs[2], 90.0f);
		Vertex[19] = float4::VectorRotationToDegX(BaseVertexs[3], 90.0f);

		Vertex[20] = float4::VectorRotationToDegX(BaseVertexs[0], -90.0f);
		Vertex[21] = float4::VectorRotationToDegX(BaseVertexs[1], -90.0f);
		Vertex[22] = float4::VectorRotationToDegX(BaseVertexs[2], -90.0f);
		Vertex[23] = float4::VectorRotationToDegX(BaseVertexs[3], -90.0f);



		std::vector<int> Index =
		{
			0, 1, 2,
			0, 2, 3,
			0 + 4, 1 + 4, 2 + 4,
			0 + 4, 2 + 4, 3 + 4,
			0 + 8, 1 + 8, 2 + 8,
			0 + 8, 2 + 8, 3 + 8,
			0 + 12, 1 + 12, 2 + 12,
			0 + 12, 2 + 12, 3 + 12,
			0 + 16, 1 + 16, 2 + 16,
			0 + 16, 2 + 16, 3 + 16,
			0 + 20, 1 + 20, 2 + 20,
			0 + 20, 2 + 20, 3 + 20,
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


		// ������ ����
		static float4 Scale = { 100.0f, 100.0f, 100.0f }; // ũ��
		static float4 Rotation = { 0, 0, 0 }; // ȸ��
		static float4 Position = { 100.0f, 100.0f, 0.0f }; // �̵�
		Rotation.X += 360.0f * _Delta;
		Rotation.Y += 360.0f * _Delta;
		Rotation.Z += 360.0f * _Delta;

		float4x4 Scale4x4;
		float4x4 Rotation4x4X;
		float4x4 Rotation4x4Y;
		float4x4 Rotation4x4Z;
		float4x4 Rotation4x4;
		float4x4 Position4x4;


		Scale4x4.Scale(Scale);

		//Rotation4x4X.RotationXDegs(Rotation.X);
		//Rotation4x4Y.RotationYDegs(Rotation.Y);
		//Rotation4x4Z.RotationZDegs(Rotation.Z);
		//Rotation4x4 = Rotation4x4X * Rotation4x4Y * Rotation4x4Z;

		Position4x4.Pos(Position);

		// ����� ������ ��ȯ��Ģ�� �������� �ʽ��ϴ�.
		float4x4 World4x4 = Scale4x4 * Rotation4x4 * Position4x4;


		// ī�޶��� ����

		static float4 EyePos = { 0.0f, 0.0f, -500.0f, 1.0f };
		static float4 EyeDir = { 0.0f, 0.0f, 1.0f, 1.0f };
		// View4x4.LookToLH
		// float4 EyeLookPos = { 0.0f, 0.0f, 0.0f, 1.0f };
		// ���ο��� ���ȴ�.
		// float4 EyeDir = EyePos - EyeLookPos;
		static float4 EyeUp = { 0.0f, 1.0f, 0.0f, 1.0f };

		float CamSpeed = 300.0f;
		if (GameEngineInput::IsPress(VK_NUMPAD4))
		{
			EyePos -= float4::LEFT * _Delta * CamSpeed;
		}

		if (GameEngineInput::IsPress(VK_NUMPAD6))
		{
			EyePos -= float4::RIGHT * _Delta * CamSpeed;
		}

		if (GameEngineInput::IsPress(VK_NUMPAD8))
		{
			EyePos -= float4::FORWARD * _Delta * CamSpeed;
		}

		if (GameEngineInput::IsPress(VK_NUMPAD5))
		{
			EyePos -= float4::BACKWARD * _Delta * CamSpeed;
		}

		if (GameEngineInput::IsPress(VK_NUMPAD7))
		{
			EyeUp.VectorRotationToDegZ(360.0f * _Delta);
		}

		if (GameEngineInput::IsPress(VK_NUMPAD9))
		{
			EyeUp.VectorRotationToDegZ(-360.0f * _Delta);
		}

		float4x4 View4x4;
		View4x4.LookAtLH(EyePos, EyeDir, EyeUp);

		float4x4 Projection4x4;

		// 
		//                           ������� ȭ���� �ʺ� 
		//                           12800                       7200
		// ������ ũ�Ⱑ �ƴ϶� ���� ������ �ٶ󺸰� ���� ũ��
		// ���� �ܾƿ��� ���� ���� ����� �������̴�.

		static float Zoom = 1.0f;

		// Zoom += _Delta;

		Projection4x4.OrthographicLH(GetStartWindowSize().X * Zoom, GetStartWindowSize().Y * Zoom, 1000.0f, 0.1f);

		float4x4 ViewPort4x4;
		//                    Ȯ�� ��Ű���� ȭ�� ũ���� �������� ũ��
		ViewPort4x4.ViewPort(GetStartWindowSize().X, GetStartWindowSize().Y, 0.0f, 0.0f);

		float4x4 WorldViewProjection4x4 = World4x4 * View4x4 * Projection4x4;

		for (size_t indexCount = 0; indexCount < Index.size() / 3; indexCount++)
		{
			int ArrIndex[3];
			ArrIndex[0] = Index[indexCount * 3 + 0];
			ArrIndex[1] = Index[indexCount * 3 + 1];
			ArrIndex[2] = Index[indexCount * 3 + 2];

			float4 Trifloat4[3];
			std::vector<POINT> Tri;
			Tri.resize(3);
			for (size_t VertexCount = 0; VertexCount < Tri.size(); VertexCount++)
			{
				// ��ġ�� �����������ؼ� ���� ���·� �������״ٰ� �Ѵ�.
				float4 WorldPoint = Vertex[ArrIndex[VertexCount]];

				//��ȯ���� ���� �� �Ѱ��� �ΰ�.
				WorldPoint = WorldPoint * WorldViewProjection4x4;

				WorldPoint = WorldPoint * ViewPort4x4;

				Trifloat4[VertexCount] = WorldPoint;


				Tri[VertexCount] = WorldPoint.WindowPOINT();
			}
			float4 Dir0 = Trifloat4[0] - Trifloat4[1];
			float4 Dir1 = Trifloat4[1] - Trifloat4[2];
			float4 Check = float4::Cross3D(Dir1, Dir0);
			if (Check.Z < 1.0f)
			{
				continue;
			}
			Polygon(DC, &Tri[0], Tri.size());
		}

		// ȭ�鿡 3d��ü�� �����ϰ� �����ϱ� ���� ��ȯ�� �� ������
		// � ����Ϳ� �Ѹ���� ���� �ȴ�. ���������� ȭ�鿡 ��� �Ѹ����ΰ����� �����ִ�.

		GameEngineCore::MainWindow.DoubleBuffering();
	}
}

void ContentsCore::Release()
{

}