//============================================================================================
//   �������� ��������� ������� ������ ������� ������������ ��
//   MAP_TX_AI_to_CPU.h - ���� ������� ���� ������ �������������
//   ���� ����������: � (STM32F103) ��� ��
//   
//   ����������: ��830-�1(2017)  
//
//   ����� ���������: 22.11.2017 12:36:31
//============================================================================================

//-------------------------------------------------------------
#define  MapAIToCPU_Length     (uint32_t)0x00D4     //����� ��������� MapAIToCPU MapAIToCPU

#define  MapAIToCPU_a     (uint32_t)0x0000     //MapAIToCPU MapAIToCPU

//-------------------------------------------------------------
#define  ToCPU_Length     (uint32_t)0x00D4     //����� ��������� ����� �������� ������ �� �� � ���

#define  ToCPU_a     (uint32_t)0x0000     //����� �������� ������ �� �� � ���

#define  ToCPU_Sign_a     (uint32_t)0x0000     //������� ���� ������� ��������� ��: 0-���������� ����� ������; 1-�������� ���������; 2-������ ���������� � �����; 3-������ ����� �����
#define  ToCPU_Sign_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_Sign_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_LengthData_a     (uint32_t)0x0001     //����� ����� ������ ���������� �� ��
#define  ToCPU_LengthData_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_LengthData_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

//-------------------------------------------------------------
#define  ToCPU_DT_Length     (uint32_t)0x0008     //����� ��������� ���� � �����

#define  ToCPU_DT_a     (uint32_t)0x0002     //���� � �����

//-------------------------------------------------------------
#define  ToCPU_DT_Date_Length     (uint32_t)0x0003     //����� ��������� ����

#define  ToCPU_DT_Date_a     (uint32_t)0x0002     //����

#define  ToCPU_DT_Date_Year_a     (uint32_t)0x0002     //���
#define  ToCPU_DT_Date_Year_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_DT_Date_Year_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_DT_Date_Month_a     (uint32_t)0x0003     //�����
#define  ToCPU_DT_Date_Month_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_DT_Date_Month_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_DT_Date_Day_a     (uint32_t)0x0004     //����
#define  ToCPU_DT_Date_Day_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_DT_Date_Day_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

//-------------------------------------------------------------
#define  ToCPU_DT_Time_Length     (uint32_t)0x0005     //����� ��������� �����

#define  ToCPU_DT_Time_a     (uint32_t)0x0005     //�����

#define  ToCPU_DT_Time_Hour_a     (uint32_t)0x0005     //���
#define  ToCPU_DT_Time_Hour_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_DT_Time_Hour_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_DT_Time_Minute_a     (uint32_t)0x0006     //������
#define  ToCPU_DT_Time_Minute_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_DT_Time_Minute_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_DT_Time_Second_a     (uint32_t)0x0007     //�������
#define  ToCPU_DT_Time_Second_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_DT_Time_Second_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_DT_Time_mSecond_a     (uint32_t)0x0008     //�����������
#define  ToCPU_DT_Time_mSecond_i     (uint32_t)0x0002     //����� ����� ����� ���������� (�����)
#define  ToCPU_DT_Time_mSecond_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

//-------------------------------------------------------------
#define  ToCPU_AD_Length     (uint32_t)0x0033     //����� ��������� ���������� ������ 1 ���������� ��������� (���������, ������� � ��)

#define  ToCPU_AD_a     (uint32_t)0x000A     //���������� ������ 1 ���������� ��������� (���������, ������� � ��)

//-------------------------------------------------------------
#define  ToCPU_AD_Ua_Length     (uint32_t)0x0004     //����� ��������� Ua *�������� � ����

#define  ToCPU_AD_Ua_a     (uint32_t)0x000A     //Ua *�������� � ����

#define  ToCPU_AD_Ua_v_a     (uint32_t)0x000A     //�������� ���� ����� �����, ���� ������� �����
#define  ToCPU_AD_Ua_v_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AD_Ua_v_f     (uint32_t)0x0001     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AD_Ua_a_a     (uint32_t)0x000C     //���� 2-� ������� ����� ����� �� 0 ��  360, ��� 1 (����)
#define  ToCPU_AD_Ua_a_i     (uint32_t)0x0002     //����� ����� ����� ���������� (�����)
#define  ToCPU_AD_Ua_a_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

//-------------------------------------------------------------
#define  ToCPU_AD_Ub_Length     (uint32_t)0x0004     //����� ��������� Ub *�������� � ����

#define  ToCPU_AD_Ub_a     (uint32_t)0x000E     //Ub *�������� � ����

#define  ToCPU_AD_Ub_v_a     (uint32_t)0x000E     //�������� ���� ����� �����, ���� ������� �����
#define  ToCPU_AD_Ub_v_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AD_Ub_v_f     (uint32_t)0x0001     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AD_Ub_a_a     (uint32_t)0x0010     //���� 2-� ������� ����� ����� �� 0 ��  360, ��� 1 (����)
#define  ToCPU_AD_Ub_a_i     (uint32_t)0x0002     //����� ����� ����� ���������� (�����)
#define  ToCPU_AD_Ub_a_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

//-------------------------------------------------------------
#define  ToCPU_AD_Uc_Length     (uint32_t)0x0004     //����� ��������� Uc *�������� � ����

#define  ToCPU_AD_Uc_a     (uint32_t)0x0012     //Uc *�������� � ����

#define  ToCPU_AD_Uc_v_a     (uint32_t)0x0012     //�������� ���� ����� �����, ���� ������� �����
#define  ToCPU_AD_Uc_v_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AD_Uc_v_f     (uint32_t)0x0001     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AD_Uc_a_a     (uint32_t)0x0014     //���� 2-� ������� ����� ����� �� 0 ��  360, ��� 1 (����)
#define  ToCPU_AD_Uc_a_i     (uint32_t)0x0002     //����� ����� ����� ���������� (�����)
#define  ToCPU_AD_Uc_a_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

//-------------------------------------------------------------
#define  ToCPU_AD_3Uo_Length     (uint32_t)0x0004     //����� ��������� 3Uo *�������� � ����

#define  ToCPU_AD_3Uo_a     (uint32_t)0x0016     //3Uo *�������� � ����

#define  ToCPU_AD_3Uo_v_a     (uint32_t)0x0016     //�������� ���� ����� �����, ���� ������� �����
#define  ToCPU_AD_3Uo_v_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AD_3Uo_v_f     (uint32_t)0x0001     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AD_3Uo_a_a     (uint32_t)0x0018     //���� 2-� ������� ����� ����� �� 0 ��  360, ��� 1 (����)
#define  ToCPU_AD_3Uo_a_i     (uint32_t)0x0002     //����� ����� ����� ���������� (�����)
#define  ToCPU_AD_3Uo_a_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AD_F_a     (uint32_t)0x001A     //F *������� (��)
#define  ToCPU_AD_F_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AD_F_f     (uint32_t)0x0001     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AD_Uf_a     (uint32_t)0x001C     //U f *
#define  ToCPU_AD_Uf_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AD_Uf_f     (uint32_t)0x0001     // ����� ������� ����� ���������� (�����)

//-------------------------------------------------------------
#define  ToCPU_AD_Ian_Length     (uint32_t)0x0004     //����� ��������� Ia� *�������� � ����

#define  ToCPU_AD_Ian_a     (uint32_t)0x001E     //Ia� *�������� � ����

#define  ToCPU_AD_Ian_v_a     (uint32_t)0x001E     //�������� ���� ����� �����, ���� ������� �����
#define  ToCPU_AD_Ian_v_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AD_Ian_v_f     (uint32_t)0x0001     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AD_Ian_a_a     (uint32_t)0x0020     //���� 2-� ������� ����� ����� �� 0 ��  360, ��� 1 (����)
#define  ToCPU_AD_Ian_a_i     (uint32_t)0x0002     //����� ����� ����� ���������� (�����)
#define  ToCPU_AD_Ian_a_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

//-------------------------------------------------------------
#define  ToCPU_AD_Ibn_Length     (uint32_t)0x0004     //����� ��������� Ib� *�������� � ����

#define  ToCPU_AD_Ibn_a     (uint32_t)0x0022     //Ib� *�������� � ����

#define  ToCPU_AD_Ibn_v_a     (uint32_t)0x0022     //�������� ���� ����� �����, ���� ������� �����
#define  ToCPU_AD_Ibn_v_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AD_Ibn_v_f     (uint32_t)0x0001     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AD_Ibn_a_a     (uint32_t)0x0024     //���� 2-� ������� ����� ����� �� 0 ��  360, ��� 1 (����)
#define  ToCPU_AD_Ibn_a_i     (uint32_t)0x0002     //����� ����� ����� ���������� (�����)
#define  ToCPU_AD_Ibn_a_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

//-------------------------------------------------------------
#define  ToCPU_AD_Icn_Length     (uint32_t)0x0004     //����� ��������� Ic� *�������� � ����

#define  ToCPU_AD_Icn_a     (uint32_t)0x0026     //Ic� *�������� � ����

#define  ToCPU_AD_Icn_v_a     (uint32_t)0x0026     //�������� ���� ����� �����, ���� ������� �����
#define  ToCPU_AD_Icn_v_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AD_Icn_v_f     (uint32_t)0x0001     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AD_Icn_a_a     (uint32_t)0x0028     //���� 2-� ������� ����� ����� �� 0 ��  360, ��� 1 (����)
#define  ToCPU_AD_Icn_a_i     (uint32_t)0x0002     //����� ����� ����� ���������� (�����)
#define  ToCPU_AD_Icn_a_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

//-------------------------------------------------------------
#define  ToCPU_AD_Iak_Length     (uint32_t)0x0004     //����� ��������� Ia� *�������� � ����

#define  ToCPU_AD_Iak_a     (uint32_t)0x002A     //Ia� *�������� � ����

#define  ToCPU_AD_Iak_v_a     (uint32_t)0x002A     //�������� ���� ����� �����, ���� ������� �����
#define  ToCPU_AD_Iak_v_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AD_Iak_v_f     (uint32_t)0x0001     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AD_Iak_a_a     (uint32_t)0x002C     //���� 2-� ������� ����� ����� �� 0 ��  360, ��� 1 (����)
#define  ToCPU_AD_Iak_a_i     (uint32_t)0x0002     //����� ����� ����� ���������� (�����)
#define  ToCPU_AD_Iak_a_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

//-------------------------------------------------------------
#define  ToCPU_AD_Ibk_Length     (uint32_t)0x0004     //����� ��������� Ib� *�������� � ����

#define  ToCPU_AD_Ibk_a     (uint32_t)0x002E     //Ib� *�������� � ����

#define  ToCPU_AD_Ibk_v_a     (uint32_t)0x002E     //�������� ���� ����� �����, ���� ������� �����
#define  ToCPU_AD_Ibk_v_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AD_Ibk_v_f     (uint32_t)0x0001     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AD_Ibk_a_a     (uint32_t)0x0030     //���� 2-� ������� ����� ����� �� 0 ��  360, ��� 1 (����)
#define  ToCPU_AD_Ibk_a_i     (uint32_t)0x0002     //����� ����� ����� ���������� (�����)
#define  ToCPU_AD_Ibk_a_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

//-------------------------------------------------------------
#define  ToCPU_AD_Ick_Length     (uint32_t)0x0004     //����� ��������� Ic� *�������� � ����

#define  ToCPU_AD_Ick_a     (uint32_t)0x0032     //Ic� *�������� � ����

#define  ToCPU_AD_Ick_v_a     (uint32_t)0x0032     //�������� ���� ����� �����, ���� ������� �����
#define  ToCPU_AD_Ick_v_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AD_Ick_v_f     (uint32_t)0x0001     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AD_Ick_a_a     (uint32_t)0x0034     //���� 2-� ������� ����� ����� �� 0 ��  360, ��� 1 (����)
#define  ToCPU_AD_Ick_a_i     (uint32_t)0x0002     //����� ����� ����� ���������� (�����)
#define  ToCPU_AD_Ick_a_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

//-------------------------------------------------------------
#define  ToCPU_AD_3Io_Length     (uint32_t)0x0005     //����� ��������� 3Io *�������� � ����

#define  ToCPU_AD_3Io_a     (uint32_t)0x0036     //3Io *�������� � ����

#define  ToCPU_AD_3Io_v_a     (uint32_t)0x0036     //��������
#define  ToCPU_AD_3Io_v_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AD_3Io_v_f     (uint32_t)0x0002     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AD_3Io_a_a     (uint32_t)0x0039     //���� 2-� ������� ����� ����� �� 0 ��  360, ��� 1 (����)
#define  ToCPU_AD_3Io_a_i     (uint32_t)0x0002     //����� ����� ����� ���������� (�����)
#define  ToCPU_AD_3Io_a_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AD_kHeat_a     (uint32_t)0x003B     //kHeat *������������� ������� ��������� % (0-100)
#define  ToCPU_AD_kHeat_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AD_kHeat_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AD_Damage_a     (uint32_t)0x003C     //����������� ��� *����������� ��� ��� ��
#define  ToCPU_AD_Damage_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AD_Damage_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

//-------------------------------------------------------------
#define  ToCPU_ADtmp_Length     (uint32_t)0x0040     //����� ��������� ���������� ������ 2 ����� ��������� �� ����������� ������ 1�

#define  ToCPU_ADtmp_a     (uint32_t)0x003D     //���������� ������ 2 ����� ��������� �� ����������� ������ 1�

//-------------------------------------------------------------
#define  ToCPU_ADtmp_Uab_Length     (uint32_t)0x0005     //����� ��������� Uab #�������� � ����

#define  ToCPU_ADtmp_Uab_a     (uint32_t)0x003D     //Uab #�������� � ����

#define  ToCPU_ADtmp_Uab_v_a     (uint32_t)0x003D     //�������� 2 ����� ����� �����, ���� ������� �����
#define  ToCPU_ADtmp_Uab_v_i     (uint32_t)0x0002     //����� ����� ����� ���������� (�����)
#define  ToCPU_ADtmp_Uab_v_f     (uint32_t)0x0001     // ����� ������� ����� ���������� (�����)

#define  ToCPU_ADtmp_Uab_a_a     (uint32_t)0x0040     //���� 2-� ������� ����� ����� �� 0 ��  360, ��� 1 (����)
#define  ToCPU_ADtmp_Uab_a_i     (uint32_t)0x0002     //����� ����� ����� ���������� (�����)
#define  ToCPU_ADtmp_Uab_a_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

//-------------------------------------------------------------
#define  ToCPU_ADtmp_Ubc_Length     (uint32_t)0x0005     //����� ��������� Ubc #�������� � ����

#define  ToCPU_ADtmp_Ubc_a     (uint32_t)0x0042     //Ubc #�������� � ����

#define  ToCPU_ADtmp_Ubc_v_a     (uint32_t)0x0042     //�������� 2 ����� ����� �����, ���� ������� �����
#define  ToCPU_ADtmp_Ubc_v_i     (uint32_t)0x0002     //����� ����� ����� ���������� (�����)
#define  ToCPU_ADtmp_Ubc_v_f     (uint32_t)0x0001     // ����� ������� ����� ���������� (�����)

#define  ToCPU_ADtmp_Ubc_a_a     (uint32_t)0x0045     //���� 2-� ������� ����� ����� �� 0 ��  360, ��� 1 (����)
#define  ToCPU_ADtmp_Ubc_a_i     (uint32_t)0x0002     //����� ����� ����� ���������� (�����)
#define  ToCPU_ADtmp_Ubc_a_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

//-------------------------------------------------------------
#define  ToCPU_ADtmp_Uca_Length     (uint32_t)0x0005     //����� ��������� Uc� #�������� � ����

#define  ToCPU_ADtmp_Uca_a     (uint32_t)0x0047     //Uc� #�������� � ����

#define  ToCPU_ADtmp_Uca_v_a     (uint32_t)0x0047     //�������� 2 ����� ����� �����, ���� ������� �����
#define  ToCPU_ADtmp_Uca_v_i     (uint32_t)0x0002     //����� ����� ����� ���������� (�����)
#define  ToCPU_ADtmp_Uca_v_f     (uint32_t)0x0001     // ����� ������� ����� ���������� (�����)

#define  ToCPU_ADtmp_Uca_a_a     (uint32_t)0x004A     //���� 2-� ������� ����� ����� �� 0 ��  360, ��� 1 (����)
#define  ToCPU_ADtmp_Uca_a_i     (uint32_t)0x0002     //����� ����� ����� ���������� (�����)
#define  ToCPU_ADtmp_Uca_a_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_ADtmp_Ubnn_a     (uint32_t)0x004C     //U ���
#define  ToCPU_ADtmp_Ubnn_i     (uint32_t)0x0002     //����� ����� ����� ���������� (�����)
#define  ToCPU_ADtmp_Ubnn_f     (uint32_t)0x0001     // ����� ������� ����� ���������� (�����)

#define  ToCPU_ADtmp_U1_a     (uint32_t)0x004F     //U 1
#define  ToCPU_ADtmp_U1_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_ADtmp_U1_f     (uint32_t)0x0001     // ����� ������� ����� ���������� (�����)

#define  ToCPU_ADtmp_U2_a     (uint32_t)0x0051     //U 2
#define  ToCPU_ADtmp_U2_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_ADtmp_U2_f     (uint32_t)0x0001     // ����� ������� ����� ���������� (�����)

#define  ToCPU_ADtmp_Ida_a     (uint32_t)0x0053     //Ida
#define  ToCPU_ADtmp_Ida_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_ADtmp_Ida_f     (uint32_t)0x0001     // ����� ������� ����� ���������� (�����)

#define  ToCPU_ADtmp_Idb_a     (uint32_t)0x0055     //Idb
#define  ToCPU_ADtmp_Idb_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_ADtmp_Idb_f     (uint32_t)0x0001     // ����� ������� ����� ���������� (�����)

#define  ToCPU_ADtmp_Idc_a     (uint32_t)0x0057     //Idc
#define  ToCPU_ADtmp_Idc_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_ADtmp_Idc_f     (uint32_t)0x0001     // ����� ������� ����� ���������� (�����)

#define  ToCPU_ADtmp_Ita_a     (uint32_t)0x0059     //I�a
#define  ToCPU_ADtmp_Ita_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_ADtmp_Ita_f     (uint32_t)0x0001     // ����� ������� ����� ���������� (�����)

#define  ToCPU_ADtmp_Itb_a     (uint32_t)0x005B     //I�b
#define  ToCPU_ADtmp_Itb_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_ADtmp_Itb_f     (uint32_t)0x0001     // ����� ������� ����� ���������� (�����)

#define  ToCPU_ADtmp_Itc_a     (uint32_t)0x005D     //I�c
#define  ToCPU_ADtmp_Itc_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_ADtmp_Itc_f     (uint32_t)0x0001     // ����� ������� ����� ���������� (�����)

#define  ToCPU_ADtmp_I1n_a     (uint32_t)0x005F     //I1�
#define  ToCPU_ADtmp_I1n_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_ADtmp_I1n_f     (uint32_t)0x0001     // ����� ������� ����� ���������� (�����)

#define  ToCPU_ADtmp_I2n_a     (uint32_t)0x0061     //I2�
#define  ToCPU_ADtmp_I2n_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_ADtmp_I2n_f     (uint32_t)0x0001     // ����� ������� ����� ���������� (�����)

#define  ToCPU_ADtmp_I1k_a     (uint32_t)0x0063     //I1�
#define  ToCPU_ADtmp_I1k_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_ADtmp_I1k_f     (uint32_t)0x0001     // ����� ������� ����� ���������� (�����)

#define  ToCPU_ADtmp_I2k_a     (uint32_t)0x0065     //I2�
#define  ToCPU_ADtmp_I2k_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_ADtmp_I2k_f     (uint32_t)0x0001     // ����� ������� ����� ���������� (�����)

#define  ToCPU_ADtmp_I2divI1n_a     (uint32_t)0x0067     //I2/I1�
#define  ToCPU_ADtmp_I2divI1n_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_ADtmp_I2divI1n_f     (uint32_t)0x0001     // ����� ������� ����� ���������� (�����)

#define  ToCPU_ADtmp_I2divI1k_a     (uint32_t)0x0069     //I2/I1�
#define  ToCPU_ADtmp_I2divI1k_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_ADtmp_I2divI1k_f     (uint32_t)0x0001     // ����� ������� ����� ���������� (�����)

#define  ToCPU_ADtmp_dIn_a     (uint32_t)0x006B     //������ I� % (0-100)
#define  ToCPU_ADtmp_dIn_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_ADtmp_dIn_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_ADtmp_aIaUbc_a     (uint32_t)0x006C     //� Ia Ubc ���� ����� Ia � Ubc
#define  ToCPU_ADtmp_aIaUbc_i     (uint32_t)0x0002     //����� ����� ����� ���������� (�����)
#define  ToCPU_ADtmp_aIaUbc_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_ADtmp_aIbUca_a     (uint32_t)0x006E     //� Ib Uca ���� ����� Ib � Uca
#define  ToCPU_ADtmp_aIbUca_i     (uint32_t)0x0002     //����� ����� ����� ���������� (�����)
#define  ToCPU_ADtmp_aIbUca_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_ADtmp_aIcUab_a     (uint32_t)0x0070     //� Ic Uab ���� ����� Ic � Uab
#define  ToCPU_ADtmp_aIcUab_i     (uint32_t)0x0002     //����� ����� ����� ���������� (�����)
#define  ToCPU_ADtmp_aIcUab_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_ADtmp_a3Io3Uo_a     (uint32_t)0x0072     //� 3Io 3Uo ���� ����� 3Io � 3Uo
#define  ToCPU_ADtmp_a3Io3Uo_i     (uint32_t)0x0002     //����� ����� ����� ���������� (�����)
#define  ToCPU_ADtmp_a3Io3Uo_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_ADtmp_P_a     (uint32_t)0x0074     //P* � ������ ���� (+,-), 8000 - ��� ��������
#define  ToCPU_ADtmp_P_i     (uint32_t)0x0002     //����� ����� ����� ���������� (�����)
#define  ToCPU_ADtmp_P_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_ADtmp_Q_a     (uint32_t)0x0076     //Q* � ������ ���� (+,-), 8000 - ��� ��������
#define  ToCPU_ADtmp_Q_i     (uint32_t)0x0002     //����� ����� ����� ���������� (�����)
#define  ToCPU_ADtmp_Q_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_ADtmp_S_a     (uint32_t)0x0078     //S ������ ��������
#define  ToCPU_ADtmp_S_i     (uint32_t)0x0002     //����� ����� ����� ���������� (�����)
#define  ToCPU_ADtmp_S_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_ADtmp_Cos_f_a     (uint32_t)0x007A     //Cos(�)* � ������ ����(+,-), 800000 - ��� ��������
#define  ToCPU_ADtmp_Cos_f_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_ADtmp_Cos_f_f     (uint32_t)0x0002     // ����� ������� ����� ���������� (�����)

//-------------------------------------------------------------
#define  ToCPU_Info_Length     (uint32_t)0x0001     //����� ��������� ����������... ����� ������� ��������

#define  ToCPU_Info_a     (uint32_t)0x007D     //����������... ����� ������� ��������

#define  ToCPU_Info_Bs_a     (uint32_t)0x007D     //���� ... ����� ��� ���������� ��������� (����������) ��
#define  ToCPU_Info_Bs_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_Info_Bs_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_Info_Bs_VMB_a     (uint32_t)0x007D     //��� ������������� ���������� (bit 0 [0:0])
#define  ToCPU_Info_Bs_VMB_bit     (uint32_t)0x0000     //� ����: ��� ������������� ���������� (bit 0 [0:0])

#define  ToCPU_Info_Bs_Ufmin_a     (uint32_t)0x007D     //Uf ��� ���������� ������ ���������� �������� ��� ��������� ������� (bit 1 [0:1])
#define  ToCPU_Info_Bs_Ufmin_bit     (uint32_t)0x0001     //� ����: Uf ��� ���������� ������ ���������� �������� ��� ��������� ������� (bit 1 [0:1])

#define  ToCPU_Info_Bs_Decr_U_a     (uint32_t)0x007D     //Decrease  U ���� �������� ����� ���������� (bit 2 [0:2])
#define  ToCPU_Info_Bs_Decr_U_bit     (uint32_t)0x0002     //� ����: Decrease  U ���� �������� ����� ���������� (bit 2 [0:2])

//-------------------------------------------------------------
#define  ToCPU_Compar_Length     (uint32_t)0x0005     //����� ��������� ����������� ����� ������� ��������

#define  ToCPU_Compar_a     (uint32_t)0x007E     //����������� ����� ������� ��������

#define  ToCPU_Compar_B1_a     (uint32_t)0x007E     //1-� ���� ����� ��� 1-4
#define  ToCPU_Compar_B1_i     (uint32_t)0x0005     //����� ����� ����� ���������� (�����)
#define  ToCPU_Compar_B1_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_Compar_B1_MTZ1_a     (uint32_t)0x007E     //��� 1 (1 | 0) (bit 0 [0:0])
#define  ToCPU_Compar_B1_MTZ1_bit     (uint32_t)0x0000     //� ����: ��� 1 (1 | 0) (bit 0 [0:0])

#define  ToCPU_Compar_B1_MTZ2_a     (uint32_t)0x007E     //��� 2 (1 | 0) (bit 1 [0:1])
#define  ToCPU_Compar_B1_MTZ2_bit     (uint32_t)0x0001     //� ����: ��� 2 (1 | 0) (bit 1 [0:1])

#define  ToCPU_Compar_B1_MTZ3_a     (uint32_t)0x007E     //��� 3 (1 | 0) (bit 2 [0:2])
#define  ToCPU_Compar_B1_MTZ3_bit     (uint32_t)0x0002     //� ����: ��� 3 (1 | 0) (bit 2 [0:2])

#define  ToCPU_Compar_B1_MTZ4_a     (uint32_t)0x007E     //��� 4 (1 | 0) (bit 3 [0:3])
#define  ToCPU_Compar_B1_MTZ4_bit     (uint32_t)0x0003     //� ����: ��� 4 (1 | 0) (bit 3 [0:3])

#define  ToCPU_Compar_B1_KAM1_a     (uint32_t)0x007E     //KAM 1 (1 | 0) (bit 4 [0:4])
#define  ToCPU_Compar_B1_KAM1_bit     (uint32_t)0x0004     //� ����: KAM 1 (1 | 0) (bit 4 [0:4])

#define  ToCPU_Compar_B1_KAM2_a     (uint32_t)0x007E     //KAM 2 (1 | 0) (bit 5 [0:5])
#define  ToCPU_Compar_B1_KAM2_bit     (uint32_t)0x0005     //� ����: KAM 2 (1 | 0) (bit 5 [0:5])

#define  ToCPU_Compar_B1_KAM3_a     (uint32_t)0x007E     //KAM 3 (1 | 0) (bit 6 [0:6])
#define  ToCPU_Compar_B1_KAM3_bit     (uint32_t)0x0006     //� ����: KAM 3 (1 | 0) (bit 6 [0:6])

#define  ToCPU_Compar_B1_ZNZ1_a     (uint32_t)0x007E     //��� 1 (1 | 0) (bit 7 [0:7])
#define  ToCPU_Compar_B1_ZNZ1_bit     (uint32_t)0x0007     //� ����: ��� 1 (1 | 0) (bit 7 [0:7])

#define  ToCPU_Compar_B1_ZNZ2_a     (uint32_t)0x007E     //��� 2 (1 | 0) (bit 8 [1:0])
#define  ToCPU_Compar_B1_ZNZ2_bit     (uint32_t)0x0008     //� ����: ��� 2 (1 | 0) (bit 8 [1:0])

#define  ToCPU_Compar_B1_ZNZ3_a     (uint32_t)0x007E     //��� 3 (1 | 0) (bit 9 [1:1])
#define  ToCPU_Compar_B1_ZNZ3_bit     (uint32_t)0x0009     //� ����: ��� 3 (1 | 0) (bit 9 [1:1])

#define  ToCPU_Compar_B1_OBR1_a     (uint32_t)0x007E     //��� 1 (1 | 0) (bit 10 [1:2])
#define  ToCPU_Compar_B1_OBR1_bit     (uint32_t)0x000A     //� ����: ��� 1 (1 | 0) (bit 10 [1:2])

#define  ToCPU_Compar_B1_OBR2_a     (uint32_t)0x007E     //��� 2 (1 | 0) (bit 11 [1:3])
#define  ToCPU_Compar_B1_OBR2_bit     (uint32_t)0x000B     //� ����: ��� 2 (1 | 0) (bit 11 [1:3])

#define  ToCPU_Compar_B1_DO_a     (uint32_t)0x007E     //�� (1 | 0) (bit 12 [1:4])
#define  ToCPU_Compar_B1_DO_bit     (uint32_t)0x000C     //� ����: �� (1 | 0) (bit 12 [1:4])

#define  ToCPU_Compar_B1_DT_a     (uint32_t)0x007E     //�� (1 | 0) (bit 13 [1:5])
#define  ToCPU_Compar_B1_DT_bit     (uint32_t)0x000D     //� ����: �� (1 | 0) (bit 13 [1:5])

#define  ToCPU_Compar_B1_DN_a     (uint32_t)0x007E     //�� (1 | 0) (bit 14 [1:6])
#define  ToCPU_Compar_B1_DN_bit     (uint32_t)0x000E     //� ����: �� (1 | 0) (bit 14 [1:6])

#define  ToCPU_Compar_B1_ZMT_a     (uint32_t)0x007E     //��� (1 | 0) (bit 15 [1:7])
#define  ToCPU_Compar_B1_ZMT_bit     (uint32_t)0x000F     //� ����: ��� (1 | 0) (bit 15 [1:7])

#define  ToCPU_Compar_B1_ZNR_a     (uint32_t)0x007E     //��� (1 | 0) (bit 16 [2:0])
#define  ToCPU_Compar_B1_ZNR_bit     (uint32_t)0x0010     //� ����: ��� (1 | 0) (bit 16 [2:0])

#define  ToCPU_Compar_B1_ZN1_a     (uint32_t)0x007E     //�� 1 (1 | 0) (bit 17 [2:1])
#define  ToCPU_Compar_B1_ZN1_bit     (uint32_t)0x0011     //� ����: �� 1 (1 | 0) (bit 17 [2:1])

#define  ToCPU_Compar_B1_ZN2_a     (uint32_t)0x007E     //�� 2 (1 | 0) (bit 18 [2:2])
#define  ToCPU_Compar_B1_ZN2_bit     (uint32_t)0x0012     //� ����: �� 2 (1 | 0) (bit 18 [2:2])

#define  ToCPU_Compar_B1_ZN3_a     (uint32_t)0x007E     //�� 3 (1 | 0) (bit 19 [2:3])
#define  ToCPU_Compar_B1_ZN3_bit     (uint32_t)0x0013     //� ����: �� 3 (1 | 0) (bit 19 [2:3])

#define  ToCPU_Compar_B1_ZN4_a     (uint32_t)0x007E     //�� 4 (1 | 0) (bit 20 [2:4])
#define  ToCPU_Compar_B1_ZN4_bit     (uint32_t)0x0014     //� ����: �� 4 (1 | 0) (bit 20 [2:4])

#define  ToCPU_Compar_B1_ZN5_a     (uint32_t)0x007E     //�� 5 (1 | 0) (bit 21 [2:5])
#define  ToCPU_Compar_B1_ZN5_bit     (uint32_t)0x0015     //� ����: �� 5 (1 | 0) (bit 21 [2:5])

#define  ToCPU_Compar_B1_ZC1_a     (uint32_t)0x007E     //�� 1 (1 | 0) (bit 22 [2:6])
#define  ToCPU_Compar_B1_ZC1_bit     (uint32_t)0x0016     //� ����: �� 1 (1 | 0) (bit 22 [2:6])

#define  ToCPU_Compar_B1_ZC2_a     (uint32_t)0x007E     //�� 2 (1 | 0) (bit 23 [2:7])
#define  ToCPU_Compar_B1_ZC2_bit     (uint32_t)0x0017     //� ����: �� 2 (1 | 0) (bit 23 [2:7])

#define  ToCPU_Compar_B1_ZZP_a     (uint32_t)0x007E     //��� (1 | 0) (bit 24 [3:0])
#define  ToCPU_Compar_B1_ZZP_bit     (uint32_t)0x0018     //� ����: ��� (1 | 0) (bit 24 [3:0])

#define  ToCPU_Compar_B1_ZBR_a     (uint32_t)0x007E     //��� (1 | 0) (bit 25 [3:1])
#define  ToCPU_Compar_B1_ZBR_bit     (uint32_t)0x0019     //� ����: ��� (1 | 0) (bit 25 [3:1])

#define  ToCPU_Compar_B1_Overheat_a     (uint32_t)0x007E     //�������� ����. ������ ���������, ���������� ��� ��������� � �������� ��������� (1 | 0) (bit 26 [3:2])
#define  ToCPU_Compar_B1_Overheat_bit     (uint32_t)0x001A     //� ����: �������� ����. ������ ���������, ���������� ��� ��������� � �������� ��������� (1 | 0) (bit 26 [3:2])

#define  ToCPU_Compar_B1_OverheatAlarm_a     (uint32_t)0x007E     //�������� ( �������������) ������ ���������, ������������� (1 | 0) (bit 27 [3:3])
#define  ToCPU_Compar_B1_OverheatAlarm_bit     (uint32_t)0x001B     //� ����: �������� ( �������������) ������ ���������, ������������� (1 | 0) (bit 27 [3:3])

#define  ToCPU_Compar_B1_UROV_a     (uint32_t)0x007E     //���� ���������� �������������� ������ ����������� (1 | 0) (bit 28 [3:4])
#define  ToCPU_Compar_B1_UROV_bit     (uint32_t)0x001C     //� ����: ���� ���������� �������������� ������ ����������� (1 | 0) (bit 28 [3:4])

#define  ToCPU_Compar_B1_PLS_a     (uint32_t)0x007E     //���. �� �����. ������ �� ��������� �� ����������� (1 | 0) (bit 29 [3:5])
#define  ToCPU_Compar_B1_PLS_bit     (uint32_t)0x001D     //� ����: ���. �� �����. ������ �� ��������� �� ����������� (1 | 0) (bit 29 [3:5])

#define  ToCPU_Compar_B1_APV_a     (uint32_t)0x007E     //��� (1 | 0) 1 - �� 5 ��, 1-���� !  (bit 30 [3:6])
#define  ToCPU_Compar_B1_APV_bit     (uint32_t)0x001E     //� ����: ��� (1 | 0) 1 - �� 5 ��, 1-���� !  (bit 30 [3:6])

#define  ToCPU_Compar_B1_BNN1_a     (uint32_t)0x007E     //���1 (1 | 0) (bit 31 [3:7])
#define  ToCPU_Compar_B1_BNN1_bit     (uint32_t)0x001F     //� ����: ���1 (1 | 0) (bit 31 [3:7])

#define  ToCPU_Compar_B1_MTZ1W_a     (uint32_t)0x007E     //���. ��� 1 (1 | 0) (bit 32 [4:0])
#define  ToCPU_Compar_B1_MTZ1W_bit     (uint32_t)0x0020     //� ����: ���. ��� 1 (1 | 0) (bit 32 [4:0])

#define  ToCPU_Compar_B1_MTZ2W_a     (uint32_t)0x007E     //���. ��� 2 (1 | 0) (bit 33 [4:1])
#define  ToCPU_Compar_B1_MTZ2W_bit     (uint32_t)0x0021     //� ����: ���. ��� 2 (1 | 0) (bit 33 [4:1])

#define  ToCPU_Compar_B1_MTZ3W_a     (uint32_t)0x007E     //���. ��� 3 (1 | 0) (bit 34 [4:2])
#define  ToCPU_Compar_B1_MTZ3W_bit     (uint32_t)0x0022     //� ����: ���. ��� 3 (1 | 0) (bit 34 [4:2])

#define  ToCPU_Compar_B1_MTZ4W_a     (uint32_t)0x007E     //���. ��� 4 (1 | 0) (bit 35 [4:3])
#define  ToCPU_Compar_B1_MTZ4W_bit     (uint32_t)0x0023     //� ����: ���. ��� 4 (1 | 0) (bit 35 [4:3])

#define  ToCPU_Compar_B1_StartM_a     (uint32_t)0x007E     //���� ���� ��������� (1 | 0) (bit 36 [4:4])
#define  ToCPU_Compar_B1_StartM_bit     (uint32_t)0x0024     //� ����: ���� ���� ��������� (1 | 0) (bit 36 [4:4])

#define  ToCPU_Compar_B1_WorkM_a     (uint32_t)0x007E     //������ ������ ��������� (1 | 0)  (bit 37 [4:5])
#define  ToCPU_Compar_B1_WorkM_bit     (uint32_t)0x0025     //� ����: ������ ������ ��������� (1 | 0)  (bit 37 [4:5])

#define  ToCPU_Compar_B1_BNN2_a     (uint32_t)0x007E     //���2 (1 | 0) ������, ��� ������� ���������� (bit 38 [4:6])
#define  ToCPU_Compar_B1_BNN2_bit     (uint32_t)0x0026     //� ����: ���2 (1 | 0) ������, ��� ������� ���������� (bit 38 [4:6])

//-------------------------------------------------------------
#define  ToCPU_Mode_Length     (uint32_t)0x0000     //����� ��������� ����� ����� ����� ������ ����� (�������������� ����� � ������������)

#define  ToCPU_Mode_a     (uint32_t)0x0083     //����� ����� ����� ������ ����� (�������������� ����� � ������������)

#define  ToCPU_GT_a     (uint32_t)0x0083     //����. ������ ���������� ������ � ��������, 4-� ������� ����� �����
#define  ToCPU_GT_i     (uint32_t)0x0004     //����� ����� ����� ���������� (�����)
#define  ToCPU_GT_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_Status_a     (uint32_t)0x0087     //������ ���� ����� ��
#define  ToCPU_Status_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_Status_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_Status_COMPARATORS_IS_VALID_a     (uint32_t)0x0087     //�������� ������������ ������������� �� = 1, ��� = 0 (bit 0 [0:0])
#define  ToCPU_Status_COMPARATORS_IS_VALID_bit     (uint32_t)0x0000     //� ����: �������� ������������ ������������� �� = 1, ��� = 0 (bit 0 [0:0])

#define  ToCPU_Status_REQ_FOR_SETP_REPEAT_a     (uint32_t)0x0087     //������ �� ��������� �������� ������� �� = 1, ��� = 0 (bit 1 [0:1])
#define  ToCPU_Status_REQ_FOR_SETP_REPEAT_bit     (uint32_t)0x0001     //� ����: ������ �� ��������� �������� ������� �� = 1, ��� = 0 (bit 1 [0:1])

#define  ToCPU_Status_SUCCESS_CALIBRATION_a     (uint32_t)0x0087     //���������� ������ ������� �� = 1, ��� = 0 (bit 2 [0:2])
#define  ToCPU_Status_SUCCESS_CALIBRATION_bit     (uint32_t)0x0002     //� ����: ���������� ������ ������� �� = 1, ��� = 0 (bit 2 [0:2])

#define  ToCPU_Status_Write_Osc_a     (uint32_t)0x0087     //�� ���������� ������ ������������� �� = 1, ��� = 0 (bit 3 [0:3])
#define  ToCPU_Status_Write_Osc_bit     (uint32_t)0x0003     //� ����: �� ���������� ������ ������������� �� = 1, ��� = 0 (bit 3 [0:3])

#define  ToCPU_Status_IsDataOsc_a     (uint32_t)0x0087     //����� ������ �������� ������ ������������ �� = 1, ��� = 0 (bit 4 [0:4])
#define  ToCPU_Status_IsDataOsc_bit     (uint32_t)0x0004     //� ����: ����� ������ �������� ������ ������������ �� = 1, ��� = 0 (bit 4 [0:4])

#define  ToCPU_Status_VersionAI_a     (uint32_t)0x0087     //����� �������� ������ �� �� = 1, ��� = 0 (bit 5 [0:5])
#define  ToCPU_Status_VersionAI_bit     (uint32_t)0x0005     //� ����: ����� �������� ������ �� �� = 1, ��� = 0 (bit 5 [0:5])

#define  ToCPU_Status_DataFromOut_a     (uint32_t)0x0087     //����� �������� ����� �� ������� ������ ��������������� � ����� �� �� = 1, ��� = 0 (bit 6 [0:6])
#define  ToCPU_Status_DataFromOut_bit     (uint32_t)0x0006     //� ����: ����� �������� ����� �� ������� ������ ��������������� � ����� �� �� = 1, ��� = 0 (bit 6 [0:6])

#define  ToCPU_Status_CalibrationCoefficients_a     (uint32_t)0x0087     //����� �������� ������������� ������������. ����� �� �������� �� = 1, ��� = 0 (bit 7 [0:7])
#define  ToCPU_Status_CalibrationCoefficients_bit     (uint32_t)0x0007     //� ����: ����� �������� ������������� ������������. ����� �� �������� �� = 1, ��� = 0 (bit 7 [0:7])

//-------------------------------------------------------------
#define  ToCPU_AddData_Length     (uint32_t)0x004B     //����� ��������� ����� ��� ������

#define  ToCPU_AddData_a     (uint32_t)0x0088     //����� ��� ������

#define  ToCPU_AddData_B01_a     (uint32_t)0x0088     //���� 01
#define  ToCPU_AddData_B01_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B01_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B02_a     (uint32_t)0x0089     //���� 02
#define  ToCPU_AddData_B02_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B02_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B03_a     (uint32_t)0x008A     //���� 03
#define  ToCPU_AddData_B03_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B03_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B04_a     (uint32_t)0x008B     //���� 04
#define  ToCPU_AddData_B04_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B04_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B05_a     (uint32_t)0x008C     //���� 05
#define  ToCPU_AddData_B05_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B05_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B06_a     (uint32_t)0x008D     //���� 06
#define  ToCPU_AddData_B06_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B06_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B07_a     (uint32_t)0x008E     //���� 07
#define  ToCPU_AddData_B07_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B07_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B08_a     (uint32_t)0x008F     //���� 08
#define  ToCPU_AddData_B08_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B08_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B09_a     (uint32_t)0x0090     //���� 09
#define  ToCPU_AddData_B09_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B09_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B10_a     (uint32_t)0x0091     //���� 10
#define  ToCPU_AddData_B10_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B10_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B11_a     (uint32_t)0x0092     //���� 11
#define  ToCPU_AddData_B11_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B11_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B12_a     (uint32_t)0x0093     //���� 12
#define  ToCPU_AddData_B12_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B12_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B13_a     (uint32_t)0x0094     //���� 13
#define  ToCPU_AddData_B13_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B13_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B14_a     (uint32_t)0x0095     //���� 14
#define  ToCPU_AddData_B14_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B14_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B15_a     (uint32_t)0x0096     //���� 15
#define  ToCPU_AddData_B15_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B15_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B16_a     (uint32_t)0x0097     //���� 16
#define  ToCPU_AddData_B16_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B16_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B17_a     (uint32_t)0x0098     //���� 17
#define  ToCPU_AddData_B17_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B17_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B18_a     (uint32_t)0x0099     //���� 18
#define  ToCPU_AddData_B18_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B18_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B19_a     (uint32_t)0x009A     //���� 19
#define  ToCPU_AddData_B19_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B19_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B20_a     (uint32_t)0x009B     //���� 20
#define  ToCPU_AddData_B20_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B20_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B21_a     (uint32_t)0x009C     //���� 21
#define  ToCPU_AddData_B21_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B21_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B22_a     (uint32_t)0x009D     //���� 22
#define  ToCPU_AddData_B22_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B22_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B23_a     (uint32_t)0x009E     //���� 23
#define  ToCPU_AddData_B23_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B23_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B24_a     (uint32_t)0x009F     //���� 24
#define  ToCPU_AddData_B24_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B24_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B25_a     (uint32_t)0x00A0     //���� 25
#define  ToCPU_AddData_B25_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B25_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B26_a     (uint32_t)0x00A1     //���� 26
#define  ToCPU_AddData_B26_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B26_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B27_a     (uint32_t)0x00A2     //���� 27
#define  ToCPU_AddData_B27_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B27_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B28_a     (uint32_t)0x00A3     //���� 28
#define  ToCPU_AddData_B28_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B28_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B29_a     (uint32_t)0x00A4     //���� 29
#define  ToCPU_AddData_B29_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B29_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B30_a     (uint32_t)0x00A5     //���� 30
#define  ToCPU_AddData_B30_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B30_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B31_a     (uint32_t)0x00A6     //���� 31
#define  ToCPU_AddData_B31_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B31_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B32_a     (uint32_t)0x00A7     //���� 32
#define  ToCPU_AddData_B32_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B32_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B33_a     (uint32_t)0x00A8     //���� 33
#define  ToCPU_AddData_B33_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B33_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B34_a     (uint32_t)0x00A9     //���� 34
#define  ToCPU_AddData_B34_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B34_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B35_a     (uint32_t)0x00AA     //���� 35
#define  ToCPU_AddData_B35_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B35_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B36_a     (uint32_t)0x00AB     //���� 36
#define  ToCPU_AddData_B36_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B36_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B37_a     (uint32_t)0x00AC     //���� 37
#define  ToCPU_AddData_B37_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B37_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B38_a     (uint32_t)0x00AD     //���� 38
#define  ToCPU_AddData_B38_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B38_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B39_a     (uint32_t)0x00AE     //���� 39
#define  ToCPU_AddData_B39_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B39_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B40_a     (uint32_t)0x00AF     //���� 40
#define  ToCPU_AddData_B40_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B40_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B41_a     (uint32_t)0x00B0     //���� 41
#define  ToCPU_AddData_B41_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B41_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B42_a     (uint32_t)0x00B1     //���� 42
#define  ToCPU_AddData_B42_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B42_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B43_a     (uint32_t)0x00B2     //���� 43
#define  ToCPU_AddData_B43_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B43_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B44_a     (uint32_t)0x00B3     //���� 44
#define  ToCPU_AddData_B44_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B44_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B45_a     (uint32_t)0x00B4     //���� 45
#define  ToCPU_AddData_B45_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B45_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B46_a     (uint32_t)0x00B5     //���� 46
#define  ToCPU_AddData_B46_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B46_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B47_a     (uint32_t)0x00B6     //���� 47
#define  ToCPU_AddData_B47_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B47_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B48_a     (uint32_t)0x00B7     //���� 48
#define  ToCPU_AddData_B48_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B48_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B49_a     (uint32_t)0x00B8     //���� 49
#define  ToCPU_AddData_B49_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B49_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B50_a     (uint32_t)0x00B9     //���� 50
#define  ToCPU_AddData_B50_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B50_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B51_a     (uint32_t)0x00BA     //���� 51
#define  ToCPU_AddData_B51_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B51_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B52_a     (uint32_t)0x00BB     //���� 52
#define  ToCPU_AddData_B52_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B52_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B53_a     (uint32_t)0x00BC     //���� 53
#define  ToCPU_AddData_B53_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B53_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B54_a     (uint32_t)0x00BD     //���� 54
#define  ToCPU_AddData_B54_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B54_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B55_a     (uint32_t)0x00BE     //���� 55
#define  ToCPU_AddData_B55_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B55_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B56_a     (uint32_t)0x00BF     //���� 56
#define  ToCPU_AddData_B56_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B56_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B57_a     (uint32_t)0x00C0     //���� 57
#define  ToCPU_AddData_B57_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B57_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B58_a     (uint32_t)0x00C1     //���� 58
#define  ToCPU_AddData_B58_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B58_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B59_a     (uint32_t)0x00C2     //���� 59
#define  ToCPU_AddData_B59_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B59_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B60_a     (uint32_t)0x00C3     //���� 60
#define  ToCPU_AddData_B60_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B60_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B61_a     (uint32_t)0x00C4     //���� 61
#define  ToCPU_AddData_B61_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B61_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B62_a     (uint32_t)0x00C5     //���� 62
#define  ToCPU_AddData_B62_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B62_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B63_a     (uint32_t)0x00C6     //���� 63
#define  ToCPU_AddData_B63_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B63_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B64_a     (uint32_t)0x00C7     //���� 64
#define  ToCPU_AddData_B64_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B64_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B65_a     (uint32_t)0x00C8     //���� 65
#define  ToCPU_AddData_B65_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B65_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B66_a     (uint32_t)0x00C9     //���� 66
#define  ToCPU_AddData_B66_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B66_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B67_a     (uint32_t)0x00CA     //���� 67
#define  ToCPU_AddData_B67_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B67_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B68_a     (uint32_t)0x00CB     //���� 68
#define  ToCPU_AddData_B68_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B68_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B69_a     (uint32_t)0x00CC     //���� 69
#define  ToCPU_AddData_B69_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B69_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B70_a     (uint32_t)0x00CD     //���� 70
#define  ToCPU_AddData_B70_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B70_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B71_a     (uint32_t)0x00CE     //���� 71
#define  ToCPU_AddData_B71_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B71_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B72_a     (uint32_t)0x00CF     //���� 72
#define  ToCPU_AddData_B72_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B72_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B73_a     (uint32_t)0x00D0     //���� 73
#define  ToCPU_AddData_B73_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B73_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B74_a     (uint32_t)0x00D1     //���� 74
#define  ToCPU_AddData_B74_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B74_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_AddData_B75_a     (uint32_t)0x00D2     //���� 75
#define  ToCPU_AddData_B75_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_AddData_B75_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)

#define  ToCPU_CS_a     (uint32_t)0x00D3     //����������� ����� XOR ����� ������ (����� ������� � ����������� �� IOAI_RX_Length � IOAI_RX_Sign)
#define  ToCPU_CS_i     (uint32_t)0x0001     //����� ����� ����� ���������� (�����)
#define  ToCPU_CS_f     (uint32_t)0x0000     // ����� ������� ����� ���������� (�����)
//============================================================================================
//   ����� ������������� ��������������� ���� �MAP_TX_AI_to_CPU.h�
//============================================================================================
