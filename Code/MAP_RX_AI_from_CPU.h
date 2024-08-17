//============================================================================================
//   �������� ��������� ������� ������ ������� ������������ ��
//   MAP_RX_AI_from_CPU.h - ���� ������� ���� ������ �������������
//   ���� ����������: � (STM32F103) ��� ��
//   
//   ����������: ��830-�1(2017)  
//
//   ����� ���������: 19.12.2017 12:42:33
//============================================================================================

//-------------------------------------------------------------
#define  MapCPUToAI_Length     (uint32_t)0x00DC     //����� ��������� MapCPUToAI MapCPUToAI

#define  MapCPUToAI_a     (uint32_t)0x0000     //MapCPUToAI MapCPUToAI

//-------------------------------------------------------------
#define  ToAI_Length     (uint32_t)0x00DC     //����� ��������� ����� �������� ������ �� ��� � ��

#define  ToAI_a     (uint32_t)0x0000     //����� �������� ������ �� ��� � ��

//-------------------------------------------------------------
#define  ToAI_ToAI_Length     (uint32_t)0x0005     //����� ��������� ������� ������������ �� ��

#define  ToAI_ToAI_a     (uint32_t)0x0000     //������� ������������ �� ��

#define  ToAI_ToAI_b_a     (uint32_t)0x0000     //���� ... ����� ��������� ������ ��� �������� �� ��
#define  ToAI_ToAI_b_i     (uint32_t)0x0005     //����� ����� ����� ���������� (�����)
#define  ToAI_ToAI_b_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_ToAI_b_LockMTZ1_a     (uint32_t)0x0000     //��. ��� 1 1 - ���������� (������) ��� 1 = 0, ������ ��� - �������, ����� ������� (����) = 0 (bit 0 [0:0])
#define  ToAI_ToAI_b_LockMTZ1_bit     (uint32_t)0x0000     //� ����: ��. ��� 1 1 - ���������� (������) ��� 1 = 0, ������ ��� - �������, ����� ������� (����) = 0 (bit 0 [0:0])

#define  ToAI_ToAI_b_LockMTZ2_a     (uint32_t)0x0000     //��. ��� 2 1 - ���������� (������) ��� 2 = 0, ������ ��� - �������, ����� ������� (����) = 0 (bit 1 [0:1])
#define  ToAI_ToAI_b_LockMTZ2_bit     (uint32_t)0x0001     //� ����: ��. ��� 2 1 - ���������� (������) ��� 2 = 0, ������ ��� - �������, ����� ������� (����) = 0 (bit 1 [0:1])

#define  ToAI_ToAI_b_LockMTZ3_a     (uint32_t)0x0000     //��. ��� 3 1 - ���������� (������) ��� 3 = 0, ������ ��� - �������, ����� ������� (����) = 0 (bit 2 [0:2])
#define  ToAI_ToAI_b_LockMTZ3_bit     (uint32_t)0x0002     //� ����: ��. ��� 3 1 - ���������� (������) ��� 3 = 0, ������ ��� - �������, ����� ������� (����) = 0 (bit 2 [0:2])

#define  ToAI_ToAI_b_LockMTZ4_a     (uint32_t)0x0000     //��. ��� 4 1 - ���������� (������) ��� 4 = 0, ������ ��� - �������, ����� ������� (����) = 0 (bit 3 [0:3])
#define  ToAI_ToAI_b_LockMTZ4_bit     (uint32_t)0x0003     //� ����: ��. ��� 4 1 - ���������� (������) ��� 4 = 0, ������ ��� - �������, ����� ������� (����) = 0 (bit 3 [0:3])

#define  ToAI_ToAI_b_RPO_a     (uint32_t)0x0000     //�������� ��� (1 | 0) (bit 4 [0:4])
#define  ToAI_ToAI_b_RPO_bit     (uint32_t)0x0004     //� ����: �������� ��� (1 | 0) (bit 4 [0:4])

#define  ToAI_ToAI_b_NCV_a     (uint32_t)0x0000     //����� ��������� ������� ������������ (1 | 0) (bit 5 [0:5])
#define  ToAI_ToAI_b_NCV_bit     (uint32_t)0x0005     //� ����: ����� ��������� ������� ������������ (1 | 0) (bit 5 [0:5])

#define  ToAI_ToAI_b_DN_a     (uint32_t)0x0000     //������ �� �������� ������� ������ �� (1 | 0) (bit 6 [0:6])
#define  ToAI_ToAI_b_DN_bit     (uint32_t)0x0006     //� ����: ������ �� �������� ������� ������ �� (1 | 0) (bit 6 [0:6])

#define  ToAI_ToAI_b_KVT_a     (uint32_t)0x0000     //������������ ��������� ������� ������������ (1 | 0) (bit 7 [0:7])
#define  ToAI_ToAI_b_KVT_bit     (uint32_t)0x0007     //� ����: ������������ ��������� ������� ������������ (1 | 0) (bit 7 [0:7])

#define  ToAI_ToAI_b_BNN1DI_a     (uint32_t)0x0000     //����. DI ��� ���1 �������� ����� DI ������������ �� ���1 (bit 8 [1:0])
#define  ToAI_ToAI_b_BNN1DI_bit     (uint32_t)0x0008     //� ����: ����. DI ��� ���1 �������� ����� DI ������������ �� ���1 (bit 8 [1:0])

#define  ToAI_ToAI_b_BNN2DI_a     (uint32_t)0x0000     //����. DI ��� ���2 �������� ����� DI ������������ �� ���2 (bit 9 [1:1])
#define  ToAI_ToAI_b_BNN2DI_bit     (uint32_t)0x0009     //� ����: ����. DI ��� ���2 �������� ����� DI ������������ �� ���2 (bit 9 [1:1])

#define  ToAI_ToAI_b_ToAITrue_a     (uint32_t)0x0000     //�������� ������������� 1 - ��� ������� ���� ������������ � �������������, ��� ���������� CSToAI, 0 - ������� �� ������������� � ���� ����� ��������� !?  (bit 39 [4:7])
#define  ToAI_ToAI_b_ToAITrue_bit     (uint32_t)0x0027     //� ����: �������� ������������� 1 - ��� ������� ���� ������������ � �������������, ��� ���������� CSToAI, 0 - ������� �� ������������� � ���� ����� ��������� !?  (bit 39 [4:7])

#define  ToAI_CSToAI_a     (uint32_t)0x0005     //�� �������� ��� �� ������������ ����� - �������� ��� �������� ������� ���� ToAI
#define  ToAI_CSToAI_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_CSToAI_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Command_a     (uint32_t)0x0006     //�������� ��� ��
#define  ToAI_Command_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Command_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

//-------------------------------------------------------------
#define  ToAI_Data_Length     (uint32_t)0x00D4     //����� ��������� ������ ��� �� ������� �� ��������

#define  ToAI_Data_a     (uint32_t)0x0007     //������ ��� �� ������� �� ��������

#define  ToAI_Data_B001_a     (uint32_t)0x0007     //���� 001
#define  ToAI_Data_B001_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B001_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B002_a     (uint32_t)0x0008     //���� 002
#define  ToAI_Data_B002_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B002_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B003_a     (uint32_t)0x0009     //���� 003
#define  ToAI_Data_B003_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B003_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B004_a     (uint32_t)0x000A     //���� 004
#define  ToAI_Data_B004_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B004_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B005_a     (uint32_t)0x000B     //���� 005
#define  ToAI_Data_B005_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B005_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B006_a     (uint32_t)0x000C     //���� 006
#define  ToAI_Data_B006_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B006_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B007_a     (uint32_t)0x000D     //���� 007
#define  ToAI_Data_B007_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B007_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B008_a     (uint32_t)0x000E     //���� 008
#define  ToAI_Data_B008_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B008_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B009_a     (uint32_t)0x000F     //���� 009
#define  ToAI_Data_B009_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B009_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B010_a     (uint32_t)0x0010     //���� 010
#define  ToAI_Data_B010_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B010_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B011_a     (uint32_t)0x0011     //���� 011
#define  ToAI_Data_B011_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B011_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B012_a     (uint32_t)0x0012     //���� 012
#define  ToAI_Data_B012_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B012_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B013_a     (uint32_t)0x0013     //���� 013
#define  ToAI_Data_B013_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B013_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B014_a     (uint32_t)0x0014     //���� 014
#define  ToAI_Data_B014_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B014_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B015_a     (uint32_t)0x0015     //���� 015
#define  ToAI_Data_B015_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B015_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B016_a     (uint32_t)0x0016     //���� 016
#define  ToAI_Data_B016_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B016_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B017_a     (uint32_t)0x0017     //���� 017
#define  ToAI_Data_B017_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B017_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B018_a     (uint32_t)0x0018     //���� 018
#define  ToAI_Data_B018_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B018_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B019_a     (uint32_t)0x0019     //���� 019
#define  ToAI_Data_B019_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B019_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B020_a     (uint32_t)0x001A     //���� 020
#define  ToAI_Data_B020_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B020_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B021_a     (uint32_t)0x001B     //���� 021
#define  ToAI_Data_B021_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B021_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B022_a     (uint32_t)0x001C     //���� 022
#define  ToAI_Data_B022_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B022_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B023_a     (uint32_t)0x001D     //���� 023
#define  ToAI_Data_B023_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B023_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B024_a     (uint32_t)0x001E     //���� 024
#define  ToAI_Data_B024_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B024_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B025_a     (uint32_t)0x001F     //���� 025
#define  ToAI_Data_B025_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B025_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B026_a     (uint32_t)0x0020     //���� 026
#define  ToAI_Data_B026_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B026_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B027_a     (uint32_t)0x0021     //���� 027
#define  ToAI_Data_B027_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B027_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B028_a     (uint32_t)0x0022     //���� 028
#define  ToAI_Data_B028_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B028_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B029_a     (uint32_t)0x0023     //���� 029
#define  ToAI_Data_B029_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B029_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B030_a     (uint32_t)0x0024     //���� 030
#define  ToAI_Data_B030_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B030_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B031_a     (uint32_t)0x0025     //���� 031
#define  ToAI_Data_B031_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B031_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B032_a     (uint32_t)0x0026     //���� 032
#define  ToAI_Data_B032_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B032_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B033_a     (uint32_t)0x0027     //���� 033
#define  ToAI_Data_B033_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B033_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B034_a     (uint32_t)0x0028     //���� 034
#define  ToAI_Data_B034_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B034_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B035_a     (uint32_t)0x0029     //���� 035
#define  ToAI_Data_B035_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B035_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B036_a     (uint32_t)0x002A     //���� 036
#define  ToAI_Data_B036_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B036_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B037_a     (uint32_t)0x002B     //���� 037
#define  ToAI_Data_B037_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B037_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B038_a     (uint32_t)0x002C     //���� 038
#define  ToAI_Data_B038_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B038_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B039_a     (uint32_t)0x002D     //���� 039
#define  ToAI_Data_B039_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B039_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B040_a     (uint32_t)0x002E     //���� 040
#define  ToAI_Data_B040_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B040_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B041_a     (uint32_t)0x002F     //���� 041
#define  ToAI_Data_B041_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B041_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B042_a     (uint32_t)0x0030     //���� 042
#define  ToAI_Data_B042_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B042_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B043_a     (uint32_t)0x0031     //���� 043
#define  ToAI_Data_B043_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B043_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B044_a     (uint32_t)0x0032     //���� 044
#define  ToAI_Data_B044_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B044_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B045_a     (uint32_t)0x0033     //���� 045
#define  ToAI_Data_B045_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B045_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B046_a     (uint32_t)0x0034     //���� 046
#define  ToAI_Data_B046_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B046_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B047_a     (uint32_t)0x0035     //���� 047
#define  ToAI_Data_B047_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B047_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B048_a     (uint32_t)0x0036     //���� 048
#define  ToAI_Data_B048_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B048_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B049_a     (uint32_t)0x0037     //���� 049
#define  ToAI_Data_B049_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B049_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B050_a     (uint32_t)0x0038     //���� 050
#define  ToAI_Data_B050_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B050_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B051_a     (uint32_t)0x0039     //���� 051
#define  ToAI_Data_B051_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B051_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B052_a     (uint32_t)0x003A     //���� 052
#define  ToAI_Data_B052_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B052_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B053_a     (uint32_t)0x003B     //���� 053
#define  ToAI_Data_B053_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B053_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B054_a     (uint32_t)0x003C     //���� 054
#define  ToAI_Data_B054_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B054_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B055_a     (uint32_t)0x003D     //���� 055
#define  ToAI_Data_B055_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B055_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B056_a     (uint32_t)0x003E     //���� 056
#define  ToAI_Data_B056_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B056_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B057_a     (uint32_t)0x003F     //���� 057
#define  ToAI_Data_B057_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B057_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B058_a     (uint32_t)0x0040     //���� 058
#define  ToAI_Data_B058_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B058_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B059_a     (uint32_t)0x0041     //���� 059
#define  ToAI_Data_B059_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B059_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B060_a     (uint32_t)0x0042     //���� 060
#define  ToAI_Data_B060_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B060_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B061_a     (uint32_t)0x0043     //���� 061
#define  ToAI_Data_B061_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B061_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B062_a     (uint32_t)0x0044     //���� 062
#define  ToAI_Data_B062_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B062_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B063_a     (uint32_t)0x0045     //���� 063
#define  ToAI_Data_B063_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B063_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B064_a     (uint32_t)0x0046     //���� 064
#define  ToAI_Data_B064_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B064_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B065_a     (uint32_t)0x0047     //���� 065
#define  ToAI_Data_B065_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B065_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B066_a     (uint32_t)0x0048     //���� 066
#define  ToAI_Data_B066_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B066_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B067_a     (uint32_t)0x0049     //���� 067
#define  ToAI_Data_B067_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B067_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B068_a     (uint32_t)0x004A     //���� 068
#define  ToAI_Data_B068_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B068_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B069_a     (uint32_t)0x004B     //���� 069
#define  ToAI_Data_B069_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B069_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B070_a     (uint32_t)0x004C     //���� 070
#define  ToAI_Data_B070_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B070_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B071_a     (uint32_t)0x004D     //���� 071
#define  ToAI_Data_B071_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B071_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B072_a     (uint32_t)0x004E     //���� 072
#define  ToAI_Data_B072_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B072_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B073_a     (uint32_t)0x004F     //���� 073
#define  ToAI_Data_B073_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B073_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B074_a     (uint32_t)0x0050     //���� 074
#define  ToAI_Data_B074_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B074_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B075_a     (uint32_t)0x0051     //���� 075
#define  ToAI_Data_B075_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B075_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B076_a     (uint32_t)0x0052     //���� 076
#define  ToAI_Data_B076_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B076_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B077_a     (uint32_t)0x0053     //���� 077
#define  ToAI_Data_B077_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B077_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B078_a     (uint32_t)0x0054     //���� 078
#define  ToAI_Data_B078_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B078_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B079_a     (uint32_t)0x0055     //���� 079
#define  ToAI_Data_B079_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B079_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B080_a     (uint32_t)0x0056     //���� 080
#define  ToAI_Data_B080_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B080_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B081_a     (uint32_t)0x0057     //���� 081
#define  ToAI_Data_B081_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B081_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B082_a     (uint32_t)0x0058     //���� 082
#define  ToAI_Data_B082_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B082_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B083_a     (uint32_t)0x0059     //���� 083
#define  ToAI_Data_B083_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B083_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B084_a     (uint32_t)0x005A     //���� 084
#define  ToAI_Data_B084_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B084_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B085_a     (uint32_t)0x005B     //���� 085
#define  ToAI_Data_B085_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B085_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B086_a     (uint32_t)0x005C     //���� 086
#define  ToAI_Data_B086_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B086_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B087_a     (uint32_t)0x005D     //���� 087
#define  ToAI_Data_B087_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B087_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B088_a     (uint32_t)0x005E     //���� 088
#define  ToAI_Data_B088_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B088_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B089_a     (uint32_t)0x005F     //���� 089
#define  ToAI_Data_B089_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B089_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B090_a     (uint32_t)0x0060     //���� 090
#define  ToAI_Data_B090_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B090_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B091_a     (uint32_t)0x0061     //���� 091
#define  ToAI_Data_B091_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B091_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B092_a     (uint32_t)0x0062     //���� 092
#define  ToAI_Data_B092_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B092_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B093_a     (uint32_t)0x0063     //���� 093
#define  ToAI_Data_B093_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B093_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B094_a     (uint32_t)0x0064     //���� 094
#define  ToAI_Data_B094_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B094_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B095_a     (uint32_t)0x0065     //���� 095
#define  ToAI_Data_B095_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B095_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B096_a     (uint32_t)0x0066     //���� 096
#define  ToAI_Data_B096_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B096_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B097_a     (uint32_t)0x0067     //���� 097
#define  ToAI_Data_B097_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B097_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B098_a     (uint32_t)0x0068     //���� 098
#define  ToAI_Data_B098_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B098_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B099_a     (uint32_t)0x0069     //���� 099
#define  ToAI_Data_B099_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B099_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B100_a     (uint32_t)0x006A     //���� 100
#define  ToAI_Data_B100_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B100_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B101_a     (uint32_t)0x006B     //���� 101
#define  ToAI_Data_B101_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B101_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B102_a     (uint32_t)0x006C     //���� 102
#define  ToAI_Data_B102_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B102_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B103_a     (uint32_t)0x006D     //���� 103
#define  ToAI_Data_B103_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B103_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B104_a     (uint32_t)0x006E     //���� 104
#define  ToAI_Data_B104_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B104_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B105_a     (uint32_t)0x006F     //���� 105
#define  ToAI_Data_B105_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B105_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B106_a     (uint32_t)0x0070     //���� 106
#define  ToAI_Data_B106_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B106_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B107_a     (uint32_t)0x0071     //���� 107
#define  ToAI_Data_B107_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B107_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B108_a     (uint32_t)0x0072     //���� 108
#define  ToAI_Data_B108_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B108_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B109_a     (uint32_t)0x0073     //���� 109
#define  ToAI_Data_B109_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B109_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B110_a     (uint32_t)0x0074     //���� 110
#define  ToAI_Data_B110_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B110_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B111_a     (uint32_t)0x0075     //���� 111
#define  ToAI_Data_B111_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B111_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B112_a     (uint32_t)0x0076     //���� 112
#define  ToAI_Data_B112_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B112_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B113_a     (uint32_t)0x0077     //���� 113
#define  ToAI_Data_B113_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B113_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B114_a     (uint32_t)0x0078     //���� 114
#define  ToAI_Data_B114_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B114_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B115_a     (uint32_t)0x0079     //���� 115
#define  ToAI_Data_B115_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B115_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B116_a     (uint32_t)0x007A     //���� 116
#define  ToAI_Data_B116_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B116_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B117_a     (uint32_t)0x007B     //���� 117
#define  ToAI_Data_B117_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B117_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B118_a     (uint32_t)0x007C     //���� 118
#define  ToAI_Data_B118_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B118_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B119_a     (uint32_t)0x007D     //���� 119
#define  ToAI_Data_B119_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B119_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B120_a     (uint32_t)0x007E     //���� 120
#define  ToAI_Data_B120_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B120_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B121_a     (uint32_t)0x007F     //���� 121
#define  ToAI_Data_B121_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B121_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B122_a     (uint32_t)0x0080     //���� 122
#define  ToAI_Data_B122_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B122_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B123_a     (uint32_t)0x0081     //���� 123
#define  ToAI_Data_B123_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B123_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B124_a     (uint32_t)0x0082     //���� 124
#define  ToAI_Data_B124_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B124_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B125_a     (uint32_t)0x0083     //���� 125
#define  ToAI_Data_B125_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B125_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B126_a     (uint32_t)0x0084     //���� 126
#define  ToAI_Data_B126_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B126_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B127_a     (uint32_t)0x0085     //���� 127
#define  ToAI_Data_B127_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B127_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B128_a     (uint32_t)0x0086     //���� 128
#define  ToAI_Data_B128_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B128_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B129_a     (uint32_t)0x0087     //���� 129
#define  ToAI_Data_B129_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B129_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B130_a     (uint32_t)0x0088     //���� 130
#define  ToAI_Data_B130_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B130_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B131_a     (uint32_t)0x0089     //���� 131
#define  ToAI_Data_B131_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B131_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B132_a     (uint32_t)0x008A     //���� 132
#define  ToAI_Data_B132_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B132_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B133_a     (uint32_t)0x008B     //���� 133
#define  ToAI_Data_B133_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B133_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B134_a     (uint32_t)0x008C     //���� 134
#define  ToAI_Data_B134_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B134_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B135_a     (uint32_t)0x008D     //���� 135
#define  ToAI_Data_B135_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B135_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B136_a     (uint32_t)0x008E     //���� 136
#define  ToAI_Data_B136_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B136_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B137_a     (uint32_t)0x008F     //���� 137
#define  ToAI_Data_B137_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B137_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B138_a     (uint32_t)0x0090     //���� 138
#define  ToAI_Data_B138_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B138_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B139_a     (uint32_t)0x0091     //���� 139
#define  ToAI_Data_B139_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B139_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B140_a     (uint32_t)0x0092     //���� 140
#define  ToAI_Data_B140_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B140_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B141_a     (uint32_t)0x0093     //���� 141
#define  ToAI_Data_B141_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B141_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B142_a     (uint32_t)0x0094     //���� 142
#define  ToAI_Data_B142_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B142_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B143_a     (uint32_t)0x0095     //���� 143
#define  ToAI_Data_B143_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B143_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B144_a     (uint32_t)0x0096     //���� 144
#define  ToAI_Data_B144_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B144_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B145_a     (uint32_t)0x0097     //���� 145
#define  ToAI_Data_B145_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B145_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B146_a     (uint32_t)0x0098     //���� 146
#define  ToAI_Data_B146_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B146_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B147_a     (uint32_t)0x0099     //���� 147
#define  ToAI_Data_B147_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B147_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B148_a     (uint32_t)0x009A     //���� 148
#define  ToAI_Data_B148_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B148_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B149_a     (uint32_t)0x009B     //���� 149
#define  ToAI_Data_B149_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B149_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B150_a     (uint32_t)0x009C     //���� 150
#define  ToAI_Data_B150_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B150_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B151_a     (uint32_t)0x009D     //���� 151
#define  ToAI_Data_B151_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B151_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B152_a     (uint32_t)0x009E     //���� 152
#define  ToAI_Data_B152_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B152_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B153_a     (uint32_t)0x009F     //���� 153
#define  ToAI_Data_B153_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B153_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B154_a     (uint32_t)0x00A0     //���� 154
#define  ToAI_Data_B154_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B154_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B155_a     (uint32_t)0x00A1     //���� 155
#define  ToAI_Data_B155_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B155_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B156_a     (uint32_t)0x00A2     //���� 156
#define  ToAI_Data_B156_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B156_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B157_a     (uint32_t)0x00A3     //���� 157
#define  ToAI_Data_B157_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B157_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B158_a     (uint32_t)0x00A4     //���� 158
#define  ToAI_Data_B158_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B158_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B159_a     (uint32_t)0x00A5     //���� 159
#define  ToAI_Data_B159_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B159_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B160_a     (uint32_t)0x00A6     //���� 160
#define  ToAI_Data_B160_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B160_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B161_a     (uint32_t)0x00A7     //���� 161
#define  ToAI_Data_B161_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B161_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B162_a     (uint32_t)0x00A8     //���� 162
#define  ToAI_Data_B162_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B162_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B163_a     (uint32_t)0x00A9     //���� 163
#define  ToAI_Data_B163_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B163_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B164_a     (uint32_t)0x00AA     //���� 164
#define  ToAI_Data_B164_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B164_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B165_a     (uint32_t)0x00AB     //���� 165
#define  ToAI_Data_B165_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B165_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B166_a     (uint32_t)0x00AC     //���� 166
#define  ToAI_Data_B166_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B166_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B167_a     (uint32_t)0x00AD     //���� 167
#define  ToAI_Data_B167_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B167_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B168_a     (uint32_t)0x00AE     //���� 168
#define  ToAI_Data_B168_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B168_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B169_a     (uint32_t)0x00AF     //���� 169
#define  ToAI_Data_B169_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B169_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B170_a     (uint32_t)0x00B0     //���� 170
#define  ToAI_Data_B170_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B170_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B171_a     (uint32_t)0x00B1     //���� 171
#define  ToAI_Data_B171_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B171_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B172_a     (uint32_t)0x00B2     //���� 172
#define  ToAI_Data_B172_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B172_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B173_a     (uint32_t)0x00B3     //���� 173
#define  ToAI_Data_B173_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B173_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B174_a     (uint32_t)0x00B4     //���� 174
#define  ToAI_Data_B174_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B174_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B175_a     (uint32_t)0x00B5     //���� 175
#define  ToAI_Data_B175_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B175_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B176_a     (uint32_t)0x00B6     //���� 176
#define  ToAI_Data_B176_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B176_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B177_a     (uint32_t)0x00B7     //���� 177
#define  ToAI_Data_B177_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B177_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B178_a     (uint32_t)0x00B8     //���� 178
#define  ToAI_Data_B178_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B178_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B179_a     (uint32_t)0x00B9     //���� 179
#define  ToAI_Data_B179_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B179_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B180_a     (uint32_t)0x00BA     //���� 180
#define  ToAI_Data_B180_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B180_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B181_a     (uint32_t)0x00BB     //���� 181
#define  ToAI_Data_B181_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B181_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B182_a     (uint32_t)0x00BC     //���� 182
#define  ToAI_Data_B182_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B182_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B183_a     (uint32_t)0x00BD     //���� 183
#define  ToAI_Data_B183_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B183_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B184_a     (uint32_t)0x00BE     //���� 184
#define  ToAI_Data_B184_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B184_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B185_a     (uint32_t)0x00BF     //���� 185
#define  ToAI_Data_B185_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B185_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B186_a     (uint32_t)0x00C0     //���� 186
#define  ToAI_Data_B186_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B186_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B187_a     (uint32_t)0x00C1     //���� 187
#define  ToAI_Data_B187_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B187_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B188_a     (uint32_t)0x00C2     //���� 188
#define  ToAI_Data_B188_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B188_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B189_a     (uint32_t)0x00C3     //���� 189
#define  ToAI_Data_B189_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B189_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B190_a     (uint32_t)0x00C4     //���� 190
#define  ToAI_Data_B190_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B190_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B191_a     (uint32_t)0x00C5     //���� 191
#define  ToAI_Data_B191_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B191_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B192_a     (uint32_t)0x00C6     //���� 192
#define  ToAI_Data_B192_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B192_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B193_a     (uint32_t)0x00C7     //���� 193
#define  ToAI_Data_B193_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B193_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B194_a     (uint32_t)0x00C8     //���� 194
#define  ToAI_Data_B194_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B194_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B195_a     (uint32_t)0x00C9     //���� 195
#define  ToAI_Data_B195_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B195_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B196_a     (uint32_t)0x00CA     //���� 196
#define  ToAI_Data_B196_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B196_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B197_a     (uint32_t)0x00CB     //���� 197
#define  ToAI_Data_B197_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B197_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B198_a     (uint32_t)0x00CC     //���� 198
#define  ToAI_Data_B198_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B198_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B199_a     (uint32_t)0x00CD     //���� 199
#define  ToAI_Data_B199_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B199_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B200_a     (uint32_t)0x00CE     //���� 200
#define  ToAI_Data_B200_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B200_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B201_a     (uint32_t)0x00CF     //���� 201
#define  ToAI_Data_B201_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B201_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B202_a     (uint32_t)0x00D0     //���� 202
#define  ToAI_Data_B202_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B202_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B203_a     (uint32_t)0x00D1     //���� 203
#define  ToAI_Data_B203_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B203_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B204_a     (uint32_t)0x00D2     //���� 204
#define  ToAI_Data_B204_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B204_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B205_a     (uint32_t)0x00D3     //���� 205
#define  ToAI_Data_B205_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B205_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B206_a     (uint32_t)0x00D4     //���� 206
#define  ToAI_Data_B206_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B206_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B207_a     (uint32_t)0x00D5     //���� 207
#define  ToAI_Data_B207_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B207_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B208_a     (uint32_t)0x00D6     //���� 208
#define  ToAI_Data_B208_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B208_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B209_a     (uint32_t)0x00D7     //���� 209
#define  ToAI_Data_B209_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B209_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B210_a     (uint32_t)0x00D8     //���� 210
#define  ToAI_Data_B210_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B210_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B211_a     (uint32_t)0x00D9     //���� 211
#define  ToAI_Data_B211_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B211_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_Data_B212_a     (uint32_t)0x00DA     //���� 212
#define  ToAI_Data_B212_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_Data_B212_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToAI_CS_a     (uint32_t)0x00DB     //�� ������������ ����� - ������� ��� ��������� ����� ����� ������ ��������, ������� �� ���������� � IOAI_TX_Buffer ��������� ������
#define  ToAI_CS_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToAI_CS_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)
//============================================================================================
//   ����� ������������� ��������������� ���� �MAP_RX_AI_from_CPU.h�
//============================================================================================
