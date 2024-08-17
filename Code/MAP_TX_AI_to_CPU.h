//============================================================================================
//   Описание адресного массива данных текущей конфигурации АИ
//   MAP_TX_AI_to_CPU.h - этот сегмент кода создан автоматически
//   Язык реализации: С (STM32F103) для АИ
//   
//   Устройство: РС830-М1(2017)  
//
//   Время генерации: 22.11.2017 12:36:31
//============================================================================================

//-------------------------------------------------------------
#define  MapAIToCPU_Length     (uint32_t)0x00D4     //Длина структуры MapAIToCPU MapAIToCPU

#define  MapAIToCPU_a     (uint32_t)0x0000     //MapAIToCPU MapAIToCPU

//-------------------------------------------------------------
#define  ToCPU_Length     (uint32_t)0x00D4     //Длина структуры Буфер передачи данных из АИ в ЦПУ

#define  ToCPU_a     (uint32_t)0x0000     //Буфер передачи данных из АИ в ЦПУ

#define  ToCPU_Sign_a     (uint32_t)0x0000     //Признак Байт признак состояния АИ: 0-Нормальный режим работы; 1-Прошивка завершена; 2-Запрос информации о файле; 3-Запрос блока файла
#define  ToCPU_Sign_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_Sign_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_LengthData_a     (uint32_t)0x0001     //Длина Длина данных полученных от АИ
#define  ToCPU_LengthData_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_LengthData_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

//-------------------------------------------------------------
#define  ToCPU_DT_Length     (uint32_t)0x0008     //Длина структуры Дата и время

#define  ToCPU_DT_a     (uint32_t)0x0002     //Дата и время

//-------------------------------------------------------------
#define  ToCPU_DT_Date_Length     (uint32_t)0x0003     //Длина структуры Дата

#define  ToCPU_DT_Date_a     (uint32_t)0x0002     //Дата

#define  ToCPU_DT_Date_Year_a     (uint32_t)0x0002     //Год
#define  ToCPU_DT_Date_Year_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_DT_Date_Year_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_DT_Date_Month_a     (uint32_t)0x0003     //Месяц
#define  ToCPU_DT_Date_Month_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_DT_Date_Month_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_DT_Date_Day_a     (uint32_t)0x0004     //День
#define  ToCPU_DT_Date_Day_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_DT_Date_Day_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

//-------------------------------------------------------------
#define  ToCPU_DT_Time_Length     (uint32_t)0x0005     //Длина структуры Время

#define  ToCPU_DT_Time_a     (uint32_t)0x0005     //Время

#define  ToCPU_DT_Time_Hour_a     (uint32_t)0x0005     //Час
#define  ToCPU_DT_Time_Hour_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_DT_Time_Hour_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_DT_Time_Minute_a     (uint32_t)0x0006     //Минута
#define  ToCPU_DT_Time_Minute_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_DT_Time_Minute_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_DT_Time_Second_a     (uint32_t)0x0007     //Секунда
#define  ToCPU_DT_Time_Second_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_DT_Time_Second_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_DT_Time_mSecond_a     (uint32_t)0x0008     //Милисекунда
#define  ToCPU_DT_Time_mSecond_i     (uint32_t)0x0002     //Длина целой части переменной (числа)
#define  ToCPU_DT_Time_mSecond_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

//-------------------------------------------------------------
#define  ToCPU_AD_Length     (uint32_t)0x0033     //Длина структуры Аналоговые данные 1 Результаты измерений (первичные, пишутся в ЖА)

#define  ToCPU_AD_a     (uint32_t)0x000A     //Аналоговые данные 1 Результаты измерений (первичные, пишутся в ЖА)

//-------------------------------------------------------------
#define  ToCPU_AD_Ua_Length     (uint32_t)0x0004     //Длина структуры Ua *Значение и угол

#define  ToCPU_AD_Ua_a     (uint32_t)0x000A     //Ua *Значение и угол

#define  ToCPU_AD_Ua_v_a     (uint32_t)0x000A     //значение Байт челой части, байт дробной части
#define  ToCPU_AD_Ua_v_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AD_Ua_v_f     (uint32_t)0x0001     // Длина дробной части переменной (числа)

#define  ToCPU_AD_Ua_a_a     (uint32_t)0x000C     //угол 2-х байтное целое число от 0 до  360, шаг 1 (угол)
#define  ToCPU_AD_Ua_a_i     (uint32_t)0x0002     //Длина целой части переменной (числа)
#define  ToCPU_AD_Ua_a_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

//-------------------------------------------------------------
#define  ToCPU_AD_Ub_Length     (uint32_t)0x0004     //Длина структуры Ub *Значение и угол

#define  ToCPU_AD_Ub_a     (uint32_t)0x000E     //Ub *Значение и угол

#define  ToCPU_AD_Ub_v_a     (uint32_t)0x000E     //значение Байт челой части, байт дробной части
#define  ToCPU_AD_Ub_v_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AD_Ub_v_f     (uint32_t)0x0001     // Длина дробной части переменной (числа)

#define  ToCPU_AD_Ub_a_a     (uint32_t)0x0010     //угол 2-х байтное целое число от 0 до  360, шаг 1 (угол)
#define  ToCPU_AD_Ub_a_i     (uint32_t)0x0002     //Длина целой части переменной (числа)
#define  ToCPU_AD_Ub_a_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

//-------------------------------------------------------------
#define  ToCPU_AD_Uc_Length     (uint32_t)0x0004     //Длина структуры Uc *Значение и угол

#define  ToCPU_AD_Uc_a     (uint32_t)0x0012     //Uc *Значение и угол

#define  ToCPU_AD_Uc_v_a     (uint32_t)0x0012     //значение Байт челой части, байт дробной части
#define  ToCPU_AD_Uc_v_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AD_Uc_v_f     (uint32_t)0x0001     // Длина дробной части переменной (числа)

#define  ToCPU_AD_Uc_a_a     (uint32_t)0x0014     //угол 2-х байтное целое число от 0 до  360, шаг 1 (угол)
#define  ToCPU_AD_Uc_a_i     (uint32_t)0x0002     //Длина целой части переменной (числа)
#define  ToCPU_AD_Uc_a_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

//-------------------------------------------------------------
#define  ToCPU_AD_3Uo_Length     (uint32_t)0x0004     //Длина структуры 3Uo *Значение и угол

#define  ToCPU_AD_3Uo_a     (uint32_t)0x0016     //3Uo *Значение и угол

#define  ToCPU_AD_3Uo_v_a     (uint32_t)0x0016     //значение Байт челой части, байт дробной части
#define  ToCPU_AD_3Uo_v_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AD_3Uo_v_f     (uint32_t)0x0001     // Длина дробной части переменной (числа)

#define  ToCPU_AD_3Uo_a_a     (uint32_t)0x0018     //угол 2-х байтное целое число от 0 до  360, шаг 1 (угол)
#define  ToCPU_AD_3Uo_a_i     (uint32_t)0x0002     //Длина целой части переменной (числа)
#define  ToCPU_AD_3Uo_a_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AD_F_a     (uint32_t)0x001A     //F *Частота (Гц)
#define  ToCPU_AD_F_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AD_F_f     (uint32_t)0x0001     // Длина дробной части переменной (числа)

#define  ToCPU_AD_Uf_a     (uint32_t)0x001C     //U f *
#define  ToCPU_AD_Uf_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AD_Uf_f     (uint32_t)0x0001     // Длина дробной части переменной (числа)

//-------------------------------------------------------------
#define  ToCPU_AD_Ian_Length     (uint32_t)0x0004     //Длина структуры Iaн *Значение и угол

#define  ToCPU_AD_Ian_a     (uint32_t)0x001E     //Iaн *Значение и угол

#define  ToCPU_AD_Ian_v_a     (uint32_t)0x001E     //значение Байт челой части, байт дробной части
#define  ToCPU_AD_Ian_v_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AD_Ian_v_f     (uint32_t)0x0001     // Длина дробной части переменной (числа)

#define  ToCPU_AD_Ian_a_a     (uint32_t)0x0020     //угол 2-х байтное целое число от 0 до  360, шаг 1 (угол)
#define  ToCPU_AD_Ian_a_i     (uint32_t)0x0002     //Длина целой части переменной (числа)
#define  ToCPU_AD_Ian_a_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

//-------------------------------------------------------------
#define  ToCPU_AD_Ibn_Length     (uint32_t)0x0004     //Длина структуры Ibн *Значение и угол

#define  ToCPU_AD_Ibn_a     (uint32_t)0x0022     //Ibн *Значение и угол

#define  ToCPU_AD_Ibn_v_a     (uint32_t)0x0022     //значение Байт челой части, байт дробной части
#define  ToCPU_AD_Ibn_v_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AD_Ibn_v_f     (uint32_t)0x0001     // Длина дробной части переменной (числа)

#define  ToCPU_AD_Ibn_a_a     (uint32_t)0x0024     //угол 2-х байтное целое число от 0 до  360, шаг 1 (угол)
#define  ToCPU_AD_Ibn_a_i     (uint32_t)0x0002     //Длина целой части переменной (числа)
#define  ToCPU_AD_Ibn_a_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

//-------------------------------------------------------------
#define  ToCPU_AD_Icn_Length     (uint32_t)0x0004     //Длина структуры Icн *Значение и угол

#define  ToCPU_AD_Icn_a     (uint32_t)0x0026     //Icн *Значение и угол

#define  ToCPU_AD_Icn_v_a     (uint32_t)0x0026     //значение Байт челой части, байт дробной части
#define  ToCPU_AD_Icn_v_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AD_Icn_v_f     (uint32_t)0x0001     // Длина дробной части переменной (числа)

#define  ToCPU_AD_Icn_a_a     (uint32_t)0x0028     //угол 2-х байтное целое число от 0 до  360, шаг 1 (угол)
#define  ToCPU_AD_Icn_a_i     (uint32_t)0x0002     //Длина целой части переменной (числа)
#define  ToCPU_AD_Icn_a_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

//-------------------------------------------------------------
#define  ToCPU_AD_Iak_Length     (uint32_t)0x0004     //Длина структуры Iaк *Значение и угол

#define  ToCPU_AD_Iak_a     (uint32_t)0x002A     //Iaк *Значение и угол

#define  ToCPU_AD_Iak_v_a     (uint32_t)0x002A     //значение Байт челой части, байт дробной части
#define  ToCPU_AD_Iak_v_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AD_Iak_v_f     (uint32_t)0x0001     // Длина дробной части переменной (числа)

#define  ToCPU_AD_Iak_a_a     (uint32_t)0x002C     //угол 2-х байтное целое число от 0 до  360, шаг 1 (угол)
#define  ToCPU_AD_Iak_a_i     (uint32_t)0x0002     //Длина целой части переменной (числа)
#define  ToCPU_AD_Iak_a_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

//-------------------------------------------------------------
#define  ToCPU_AD_Ibk_Length     (uint32_t)0x0004     //Длина структуры Ibк *Значение и угол

#define  ToCPU_AD_Ibk_a     (uint32_t)0x002E     //Ibк *Значение и угол

#define  ToCPU_AD_Ibk_v_a     (uint32_t)0x002E     //значение Байт челой части, байт дробной части
#define  ToCPU_AD_Ibk_v_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AD_Ibk_v_f     (uint32_t)0x0001     // Длина дробной части переменной (числа)

#define  ToCPU_AD_Ibk_a_a     (uint32_t)0x0030     //угол 2-х байтное целое число от 0 до  360, шаг 1 (угол)
#define  ToCPU_AD_Ibk_a_i     (uint32_t)0x0002     //Длина целой части переменной (числа)
#define  ToCPU_AD_Ibk_a_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

//-------------------------------------------------------------
#define  ToCPU_AD_Ick_Length     (uint32_t)0x0004     //Длина структуры Icк *Значение и угол

#define  ToCPU_AD_Ick_a     (uint32_t)0x0032     //Icк *Значение и угол

#define  ToCPU_AD_Ick_v_a     (uint32_t)0x0032     //значение Байт челой части, байт дробной части
#define  ToCPU_AD_Ick_v_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AD_Ick_v_f     (uint32_t)0x0001     // Длина дробной части переменной (числа)

#define  ToCPU_AD_Ick_a_a     (uint32_t)0x0034     //угол 2-х байтное целое число от 0 до  360, шаг 1 (угол)
#define  ToCPU_AD_Ick_a_i     (uint32_t)0x0002     //Длина целой части переменной (числа)
#define  ToCPU_AD_Ick_a_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

//-------------------------------------------------------------
#define  ToCPU_AD_3Io_Length     (uint32_t)0x0005     //Длина структуры 3Io *Значение и угол

#define  ToCPU_AD_3Io_a     (uint32_t)0x0036     //3Io *Значение и угол

#define  ToCPU_AD_3Io_v_a     (uint32_t)0x0036     //значение
#define  ToCPU_AD_3Io_v_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AD_3Io_v_f     (uint32_t)0x0002     // Длина дробной части переменной (числа)

#define  ToCPU_AD_3Io_a_a     (uint32_t)0x0039     //угол 2-х байтное целое число от 0 до  360, шаг 1 (угол)
#define  ToCPU_AD_3Io_a_i     (uint32_t)0x0002     //Длина целой части переменной (числа)
#define  ToCPU_AD_3Io_a_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AD_kHeat_a     (uint32_t)0x003B     //kHeat *Относительный уровень перегрева % (0-100)
#define  ToCPU_AD_kHeat_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AD_kHeat_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AD_Damage_a     (uint32_t)0x003C     //Повреждение фаз *Повреждение фаз при КЗ
#define  ToCPU_AD_Damage_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AD_Damage_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

//-------------------------------------------------------------
#define  ToCPU_ADtmp_Length     (uint32_t)0x0040     //Длина структуры Аналоговые данные 2 Можно вычислить из «Аналоговые данные 1»

#define  ToCPU_ADtmp_a     (uint32_t)0x003D     //Аналоговые данные 2 Можно вычислить из «Аналоговые данные 1»

//-------------------------------------------------------------
#define  ToCPU_ADtmp_Uab_Length     (uint32_t)0x0005     //Длина структуры Uab #Значение и угол

#define  ToCPU_ADtmp_Uab_a     (uint32_t)0x003D     //Uab #Значение и угол

#define  ToCPU_ADtmp_Uab_v_a     (uint32_t)0x003D     //значение 2 байта челой части, байт дробной части
#define  ToCPU_ADtmp_Uab_v_i     (uint32_t)0x0002     //Длина целой части переменной (числа)
#define  ToCPU_ADtmp_Uab_v_f     (uint32_t)0x0001     // Длина дробной части переменной (числа)

#define  ToCPU_ADtmp_Uab_a_a     (uint32_t)0x0040     //угол 2-х байтное целое число от 0 до  360, шаг 1 (угол)
#define  ToCPU_ADtmp_Uab_a_i     (uint32_t)0x0002     //Длина целой части переменной (числа)
#define  ToCPU_ADtmp_Uab_a_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

//-------------------------------------------------------------
#define  ToCPU_ADtmp_Ubc_Length     (uint32_t)0x0005     //Длина структуры Ubc #Значение и угол

#define  ToCPU_ADtmp_Ubc_a     (uint32_t)0x0042     //Ubc #Значение и угол

#define  ToCPU_ADtmp_Ubc_v_a     (uint32_t)0x0042     //значение 2 байта челой части, байт дробной части
#define  ToCPU_ADtmp_Ubc_v_i     (uint32_t)0x0002     //Длина целой части переменной (числа)
#define  ToCPU_ADtmp_Ubc_v_f     (uint32_t)0x0001     // Длина дробной части переменной (числа)

#define  ToCPU_ADtmp_Ubc_a_a     (uint32_t)0x0045     //угол 2-х байтное целое число от 0 до  360, шаг 1 (угол)
#define  ToCPU_ADtmp_Ubc_a_i     (uint32_t)0x0002     //Длина целой части переменной (числа)
#define  ToCPU_ADtmp_Ubc_a_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

//-------------------------------------------------------------
#define  ToCPU_ADtmp_Uca_Length     (uint32_t)0x0005     //Длина структуры Ucа #Значение и угол

#define  ToCPU_ADtmp_Uca_a     (uint32_t)0x0047     //Ucа #Значение и угол

#define  ToCPU_ADtmp_Uca_v_a     (uint32_t)0x0047     //значение 2 байта челой части, байт дробной части
#define  ToCPU_ADtmp_Uca_v_i     (uint32_t)0x0002     //Длина целой части переменной (числа)
#define  ToCPU_ADtmp_Uca_v_f     (uint32_t)0x0001     // Длина дробной части переменной (числа)

#define  ToCPU_ADtmp_Uca_a_a     (uint32_t)0x004A     //угол 2-х байтное целое число от 0 до  360, шаг 1 (угол)
#define  ToCPU_ADtmp_Uca_a_i     (uint32_t)0x0002     //Длина целой части переменной (числа)
#define  ToCPU_ADtmp_Uca_a_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_ADtmp_Ubnn_a     (uint32_t)0x004C     //U бнн
#define  ToCPU_ADtmp_Ubnn_i     (uint32_t)0x0002     //Длина целой части переменной (числа)
#define  ToCPU_ADtmp_Ubnn_f     (uint32_t)0x0001     // Длина дробной части переменной (числа)

#define  ToCPU_ADtmp_U1_a     (uint32_t)0x004F     //U 1
#define  ToCPU_ADtmp_U1_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_ADtmp_U1_f     (uint32_t)0x0001     // Длина дробной части переменной (числа)

#define  ToCPU_ADtmp_U2_a     (uint32_t)0x0051     //U 2
#define  ToCPU_ADtmp_U2_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_ADtmp_U2_f     (uint32_t)0x0001     // Длина дробной части переменной (числа)

#define  ToCPU_ADtmp_Ida_a     (uint32_t)0x0053     //Ida
#define  ToCPU_ADtmp_Ida_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_ADtmp_Ida_f     (uint32_t)0x0001     // Длина дробной части переменной (числа)

#define  ToCPU_ADtmp_Idb_a     (uint32_t)0x0055     //Idb
#define  ToCPU_ADtmp_Idb_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_ADtmp_Idb_f     (uint32_t)0x0001     // Длина дробной части переменной (числа)

#define  ToCPU_ADtmp_Idc_a     (uint32_t)0x0057     //Idc
#define  ToCPU_ADtmp_Idc_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_ADtmp_Idc_f     (uint32_t)0x0001     // Длина дробной части переменной (числа)

#define  ToCPU_ADtmp_Ita_a     (uint32_t)0x0059     //Iтa
#define  ToCPU_ADtmp_Ita_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_ADtmp_Ita_f     (uint32_t)0x0001     // Длина дробной части переменной (числа)

#define  ToCPU_ADtmp_Itb_a     (uint32_t)0x005B     //Iтb
#define  ToCPU_ADtmp_Itb_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_ADtmp_Itb_f     (uint32_t)0x0001     // Длина дробной части переменной (числа)

#define  ToCPU_ADtmp_Itc_a     (uint32_t)0x005D     //Iтc
#define  ToCPU_ADtmp_Itc_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_ADtmp_Itc_f     (uint32_t)0x0001     // Длина дробной части переменной (числа)

#define  ToCPU_ADtmp_I1n_a     (uint32_t)0x005F     //I1н
#define  ToCPU_ADtmp_I1n_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_ADtmp_I1n_f     (uint32_t)0x0001     // Длина дробной части переменной (числа)

#define  ToCPU_ADtmp_I2n_a     (uint32_t)0x0061     //I2н
#define  ToCPU_ADtmp_I2n_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_ADtmp_I2n_f     (uint32_t)0x0001     // Длина дробной части переменной (числа)

#define  ToCPU_ADtmp_I1k_a     (uint32_t)0x0063     //I1к
#define  ToCPU_ADtmp_I1k_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_ADtmp_I1k_f     (uint32_t)0x0001     // Длина дробной части переменной (числа)

#define  ToCPU_ADtmp_I2k_a     (uint32_t)0x0065     //I2к
#define  ToCPU_ADtmp_I2k_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_ADtmp_I2k_f     (uint32_t)0x0001     // Длина дробной части переменной (числа)

#define  ToCPU_ADtmp_I2divI1n_a     (uint32_t)0x0067     //I2/I1н
#define  ToCPU_ADtmp_I2divI1n_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_ADtmp_I2divI1n_f     (uint32_t)0x0001     // Длина дробной части переменной (числа)

#define  ToCPU_ADtmp_I2divI1k_a     (uint32_t)0x0069     //I2/I1к
#define  ToCPU_ADtmp_I2divI1k_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_ADtmp_I2divI1k_f     (uint32_t)0x0001     // Длина дробной части переменной (числа)

#define  ToCPU_ADtmp_dIn_a     (uint32_t)0x006B     //дельта Iн % (0-100)
#define  ToCPU_ADtmp_dIn_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_ADtmp_dIn_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_ADtmp_aIaUbc_a     (uint32_t)0x006C     //Ф Ia Ubc Угол между Ia и Ubc
#define  ToCPU_ADtmp_aIaUbc_i     (uint32_t)0x0002     //Длина целой части переменной (числа)
#define  ToCPU_ADtmp_aIaUbc_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_ADtmp_aIbUca_a     (uint32_t)0x006E     //Ф Ib Uca Угол между Ib и Uca
#define  ToCPU_ADtmp_aIbUca_i     (uint32_t)0x0002     //Длина целой части переменной (числа)
#define  ToCPU_ADtmp_aIbUca_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_ADtmp_aIcUab_a     (uint32_t)0x0070     //Ф Ic Uab Угол между Ic и Uab
#define  ToCPU_ADtmp_aIcUab_i     (uint32_t)0x0002     //Длина целой части переменной (числа)
#define  ToCPU_ADtmp_aIcUab_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_ADtmp_a3Io3Uo_a     (uint32_t)0x0072     //Ф 3Io 3Uo Угол между 3Io и 3Uo
#define  ToCPU_ADtmp_a3Io3Uo_i     (uint32_t)0x0002     //Длина целой части переменной (числа)
#define  ToCPU_ADtmp_a3Io3Uo_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_ADtmp_P_a     (uint32_t)0x0074     //P* В прямом коде (+,-), 8000 - нет значения
#define  ToCPU_ADtmp_P_i     (uint32_t)0x0002     //Длина целой части переменной (числа)
#define  ToCPU_ADtmp_P_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_ADtmp_Q_a     (uint32_t)0x0076     //Q* В прямом коде (+,-), 8000 - нет значения
#define  ToCPU_ADtmp_Q_i     (uint32_t)0x0002     //Длина целой части переменной (числа)
#define  ToCPU_ADtmp_Q_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_ADtmp_S_a     (uint32_t)0x0078     //S Полная мощность
#define  ToCPU_ADtmp_S_i     (uint32_t)0x0002     //Длина целой части переменной (числа)
#define  ToCPU_ADtmp_S_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_ADtmp_Cos_f_a     (uint32_t)0x007A     //Cos(ф)* В прямом коде(+,-), 800000 - нет значения
#define  ToCPU_ADtmp_Cos_f_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_ADtmp_Cos_f_f     (uint32_t)0x0002     // Длина дробной части переменной (числа)

//-------------------------------------------------------------
#define  ToCPU_Info_Length     (uint32_t)0x0001     //Длина структуры Блокировки... Набор битовых значений

#define  ToCPU_Info_a     (uint32_t)0x007D     //Блокировки... Набор битовых значений

#define  ToCPU_Info_Bs_a     (uint32_t)0x007D     //Биты ... Набор бит внутренних состояний (блокировок) АИ
#define  ToCPU_Info_Bs_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_Info_Bs_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_Info_Bs_VMB_a     (uint32_t)0x007D     //ВМБ Вольтметровая блокировка (bit 0 [0:0])
#define  ToCPU_Info_Bs_VMB_bit     (uint32_t)0x0000     //№ бита: ВМБ Вольтметровая блокировка (bit 0 [0:0])

#define  ToCPU_Info_Bs_Ufmin_a     (uint32_t)0x007D     //Uf мин Напряженеи меньше порогового значения для измерения частоты (bit 1 [0:1])
#define  ToCPU_Info_Bs_Ufmin_bit     (uint32_t)0x0001     //№ бита: Uf мин Напряженеи меньше порогового значения для измерения частоты (bit 1 [0:1])

#define  ToCPU_Info_Bs_Decr_U_a     (uint32_t)0x007D     //Decrease  U Факт снижения фазніх напряжений (bit 2 [0:2])
#define  ToCPU_Info_Bs_Decr_U_bit     (uint32_t)0x0002     //№ бита: Decrease  U Факт снижения фазніх напряжений (bit 2 [0:2])

//-------------------------------------------------------------
#define  ToCPU_Compar_Length     (uint32_t)0x0005     //Длина структуры Компараторы Набор битовых значений

#define  ToCPU_Compar_a     (uint32_t)0x007E     //Компараторы Набор битовых значений

#define  ToCPU_Compar_B1_a     (uint32_t)0x007E     //1-й байт Флаги МТЗ 1-4
#define  ToCPU_Compar_B1_i     (uint32_t)0x0005     //Длина целой части переменной (числа)
#define  ToCPU_Compar_B1_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_Compar_B1_MTZ1_a     (uint32_t)0x007E     //МТЗ 1 (1 | 0) (bit 0 [0:0])
#define  ToCPU_Compar_B1_MTZ1_bit     (uint32_t)0x0000     //№ бита: МТЗ 1 (1 | 0) (bit 0 [0:0])

#define  ToCPU_Compar_B1_MTZ2_a     (uint32_t)0x007E     //МТЗ 2 (1 | 0) (bit 1 [0:1])
#define  ToCPU_Compar_B1_MTZ2_bit     (uint32_t)0x0001     //№ бита: МТЗ 2 (1 | 0) (bit 1 [0:1])

#define  ToCPU_Compar_B1_MTZ3_a     (uint32_t)0x007E     //МТЗ 3 (1 | 0) (bit 2 [0:2])
#define  ToCPU_Compar_B1_MTZ3_bit     (uint32_t)0x0002     //№ бита: МТЗ 3 (1 | 0) (bit 2 [0:2])

#define  ToCPU_Compar_B1_MTZ4_a     (uint32_t)0x007E     //МТЗ 4 (1 | 0) (bit 3 [0:3])
#define  ToCPU_Compar_B1_MTZ4_bit     (uint32_t)0x0003     //№ бита: МТЗ 4 (1 | 0) (bit 3 [0:3])

#define  ToCPU_Compar_B1_KAM1_a     (uint32_t)0x007E     //KAM 1 (1 | 0) (bit 4 [0:4])
#define  ToCPU_Compar_B1_KAM1_bit     (uint32_t)0x0004     //№ бита: KAM 1 (1 | 0) (bit 4 [0:4])

#define  ToCPU_Compar_B1_KAM2_a     (uint32_t)0x007E     //KAM 2 (1 | 0) (bit 5 [0:5])
#define  ToCPU_Compar_B1_KAM2_bit     (uint32_t)0x0005     //№ бита: KAM 2 (1 | 0) (bit 5 [0:5])

#define  ToCPU_Compar_B1_KAM3_a     (uint32_t)0x007E     //KAM 3 (1 | 0) (bit 6 [0:6])
#define  ToCPU_Compar_B1_KAM3_bit     (uint32_t)0x0006     //№ бита: KAM 3 (1 | 0) (bit 6 [0:6])

#define  ToCPU_Compar_B1_ZNZ1_a     (uint32_t)0x007E     //ЗНЗ 1 (1 | 0) (bit 7 [0:7])
#define  ToCPU_Compar_B1_ZNZ1_bit     (uint32_t)0x0007     //№ бита: ЗНЗ 1 (1 | 0) (bit 7 [0:7])

#define  ToCPU_Compar_B1_ZNZ2_a     (uint32_t)0x007E     //ЗНЗ 2 (1 | 0) (bit 8 [1:0])
#define  ToCPU_Compar_B1_ZNZ2_bit     (uint32_t)0x0008     //№ бита: ЗНЗ 2 (1 | 0) (bit 8 [1:0])

#define  ToCPU_Compar_B1_ZNZ3_a     (uint32_t)0x007E     //ЗНЗ 3 (1 | 0) (bit 9 [1:1])
#define  ToCPU_Compar_B1_ZNZ3_bit     (uint32_t)0x0009     //№ бита: ЗНЗ 3 (1 | 0) (bit 9 [1:1])

#define  ToCPU_Compar_B1_OBR1_a     (uint32_t)0x007E     //ОБР 1 (1 | 0) (bit 10 [1:2])
#define  ToCPU_Compar_B1_OBR1_bit     (uint32_t)0x000A     //№ бита: ОБР 1 (1 | 0) (bit 10 [1:2])

#define  ToCPU_Compar_B1_OBR2_a     (uint32_t)0x007E     //ОБР 2 (1 | 0) (bit 11 [1:3])
#define  ToCPU_Compar_B1_OBR2_bit     (uint32_t)0x000B     //№ бита: ОБР 2 (1 | 0) (bit 11 [1:3])

#define  ToCPU_Compar_B1_DO_a     (uint32_t)0x007E     //ДО (1 | 0) (bit 12 [1:4])
#define  ToCPU_Compar_B1_DO_bit     (uint32_t)0x000C     //№ бита: ДО (1 | 0) (bit 12 [1:4])

#define  ToCPU_Compar_B1_DT_a     (uint32_t)0x007E     //ДТ (1 | 0) (bit 13 [1:5])
#define  ToCPU_Compar_B1_DT_bit     (uint32_t)0x000D     //№ бита: ДТ (1 | 0) (bit 13 [1:5])

#define  ToCPU_Compar_B1_DN_a     (uint32_t)0x007E     //ДН (1 | 0) (bit 14 [1:6])
#define  ToCPU_Compar_B1_DN_bit     (uint32_t)0x000E     //№ бита: ДН (1 | 0) (bit 14 [1:6])

#define  ToCPU_Compar_B1_ZMT_a     (uint32_t)0x007E     //ЗМТ (1 | 0) (bit 15 [1:7])
#define  ToCPU_Compar_B1_ZMT_bit     (uint32_t)0x000F     //№ бита: ЗМТ (1 | 0) (bit 15 [1:7])

#define  ToCPU_Compar_B1_ZNR_a     (uint32_t)0x007E     //ЗНР (1 | 0) (bit 16 [2:0])
#define  ToCPU_Compar_B1_ZNR_bit     (uint32_t)0x0010     //№ бита: ЗНР (1 | 0) (bit 16 [2:0])

#define  ToCPU_Compar_B1_ZN1_a     (uint32_t)0x007E     //ЗН 1 (1 | 0) (bit 17 [2:1])
#define  ToCPU_Compar_B1_ZN1_bit     (uint32_t)0x0011     //№ бита: ЗН 1 (1 | 0) (bit 17 [2:1])

#define  ToCPU_Compar_B1_ZN2_a     (uint32_t)0x007E     //ЗН 2 (1 | 0) (bit 18 [2:2])
#define  ToCPU_Compar_B1_ZN2_bit     (uint32_t)0x0012     //№ бита: ЗН 2 (1 | 0) (bit 18 [2:2])

#define  ToCPU_Compar_B1_ZN3_a     (uint32_t)0x007E     //ЗН 3 (1 | 0) (bit 19 [2:3])
#define  ToCPU_Compar_B1_ZN3_bit     (uint32_t)0x0013     //№ бита: ЗН 3 (1 | 0) (bit 19 [2:3])

#define  ToCPU_Compar_B1_ZN4_a     (uint32_t)0x007E     //ЗН 4 (1 | 0) (bit 20 [2:4])
#define  ToCPU_Compar_B1_ZN4_bit     (uint32_t)0x0014     //№ бита: ЗН 4 (1 | 0) (bit 20 [2:4])

#define  ToCPU_Compar_B1_ZN5_a     (uint32_t)0x007E     //ЗН 5 (1 | 0) (bit 21 [2:5])
#define  ToCPU_Compar_B1_ZN5_bit     (uint32_t)0x0015     //№ бита: ЗН 5 (1 | 0) (bit 21 [2:5])

#define  ToCPU_Compar_B1_ZC1_a     (uint32_t)0x007E     //ЗЧ 1 (1 | 0) (bit 22 [2:6])
#define  ToCPU_Compar_B1_ZC1_bit     (uint32_t)0x0016     //№ бита: ЗЧ 1 (1 | 0) (bit 22 [2:6])

#define  ToCPU_Compar_B1_ZC2_a     (uint32_t)0x007E     //ЗЧ 2 (1 | 0) (bit 23 [2:7])
#define  ToCPU_Compar_B1_ZC2_bit     (uint32_t)0x0017     //№ бита: ЗЧ 2 (1 | 0) (bit 23 [2:7])

#define  ToCPU_Compar_B1_ZZP_a     (uint32_t)0x007E     //ЗЗП (1 | 0) (bit 24 [3:0])
#define  ToCPU_Compar_B1_ZZP_bit     (uint32_t)0x0018     //№ бита: ЗЗП (1 | 0) (bit 24 [3:0])

#define  ToCPU_Compar_B1_ZBR_a     (uint32_t)0x007E     //ЗБР (1 | 0) (bit 25 [3:1])
#define  ToCPU_Compar_B1_ZBR_bit     (uint32_t)0x0019     //№ бита: ЗБР (1 | 0) (bit 25 [3:1])

#define  ToCPU_Compar_B1_Overheat_a     (uint32_t)0x007E     //Перегрев откл. Сигнал перегрева, отключение при перегреве с запретом включения (1 | 0) (bit 26 [3:2])
#define  ToCPU_Compar_B1_Overheat_bit     (uint32_t)0x001A     //№ бита: Перегрев откл. Сигнал перегрева, отключение при перегреве с запретом включения (1 | 0) (bit 26 [3:2])

#define  ToCPU_Compar_B1_OverheatAlarm_a     (uint32_t)0x007E     //Перегрев ( предпреждение) Сигнал перегрева, предпреждение (1 | 0) (bit 27 [3:3])
#define  ToCPU_Compar_B1_OverheatAlarm_bit     (uint32_t)0x001B     //№ бита: Перегрев ( предпреждение) Сигнал перегрева, предпреждение (1 | 0) (bit 27 [3:3])

#define  ToCPU_Compar_B1_UROV_a     (uint32_t)0x007E     //УРОВ Устройство резервирования отказа выключателя (1 | 0) (bit 28 [3:4])
#define  ToCPU_Compar_B1_UROV_bit     (uint32_t)0x001C     //№ бита: УРОВ Устройство резервирования отказа выключателя (1 | 0) (bit 28 [3:4])

#define  ToCPU_Compar_B1_PLS_a     (uint32_t)0x007E     //Вып. из синхр. Защита от выпадения из синхронизма (1 | 0) (bit 29 [3:5])
#define  ToCPU_Compar_B1_PLS_bit     (uint32_t)0x001D     //№ бита: Вып. из синхр. Защита от выпадения из синхронизма (1 | 0) (bit 29 [3:5])

#define  ToCPU_Compar_B1_APV_a     (uint32_t)0x007E     //АПВ (1 | 0) 1 - на 5 мс, 1-крат !  (bit 30 [3:6])
#define  ToCPU_Compar_B1_APV_bit     (uint32_t)0x001E     //№ бита: АПВ (1 | 0) 1 - на 5 мс, 1-крат !  (bit 30 [3:6])

#define  ToCPU_Compar_B1_BNN1_a     (uint32_t)0x007E     //БНН1 (1 | 0) (bit 31 [3:7])
#define  ToCPU_Compar_B1_BNN1_bit     (uint32_t)0x001F     //№ бита: БНН1 (1 | 0) (bit 31 [3:7])

#define  ToCPU_Compar_B1_MTZ1W_a     (uint32_t)0x007E     //Раб. МТЗ 1 (1 | 0) (bit 32 [4:0])
#define  ToCPU_Compar_B1_MTZ1W_bit     (uint32_t)0x0020     //№ бита: Раб. МТЗ 1 (1 | 0) (bit 32 [4:0])

#define  ToCPU_Compar_B1_MTZ2W_a     (uint32_t)0x007E     //Раб. МТЗ 2 (1 | 0) (bit 33 [4:1])
#define  ToCPU_Compar_B1_MTZ2W_bit     (uint32_t)0x0021     //№ бита: Раб. МТЗ 2 (1 | 0) (bit 33 [4:1])

#define  ToCPU_Compar_B1_MTZ3W_a     (uint32_t)0x007E     //Раб. МТЗ 3 (1 | 0) (bit 34 [4:2])
#define  ToCPU_Compar_B1_MTZ3W_bit     (uint32_t)0x0022     //№ бита: Раб. МТЗ 3 (1 | 0) (bit 34 [4:2])

#define  ToCPU_Compar_B1_MTZ4W_a     (uint32_t)0x007E     //Раб. МТЗ 4 (1 | 0) (bit 35 [4:3])
#define  ToCPU_Compar_B1_MTZ4W_bit     (uint32_t)0x0023     //№ бита: Раб. МТЗ 4 (1 | 0) (bit 35 [4:3])

#define  ToCPU_Compar_B1_StartM_a     (uint32_t)0x007E     //Пуск Пуск двигателя (1 | 0) (bit 36 [4:4])
#define  ToCPU_Compar_B1_StartM_bit     (uint32_t)0x0024     //№ бита: Пуск Пуск двигателя (1 | 0) (bit 36 [4:4])

#define  ToCPU_Compar_B1_WorkM_a     (uint32_t)0x007E     //Работа Работа двигателя (1 | 0)  (bit 37 [4:5])
#define  ToCPU_Compar_B1_WorkM_bit     (uint32_t)0x0025     //№ бита: Работа Работа двигателя (1 | 0)  (bit 37 [4:5])

#define  ToCPU_Compar_B1_BNN2_a     (uint32_t)0x007E     //БНН2 (1 | 0) Резерв, для будущих расширений (bit 38 [4:6])
#define  ToCPU_Compar_B1_BNN2_bit     (uint32_t)0x0026     //№ бита: БНН2 (1 | 0) Резерв, для будущих расширений (bit 38 [4:6])

//-------------------------------------------------------------
#define  ToCPU_Mode_Length     (uint32_t)0x0000     //Длина структуры Режим защит Режим работы защит (Дополнительный флаги к компараторам)

#define  ToCPU_Mode_a     (uint32_t)0x0083     //Режим защит Режим работы защит (Дополнительный флаги к компараторам)

#define  ToCPU_GT_a     (uint32_t)0x0083     //Глоб. таймер Глобальный таймер в секундах, 4-х байтное целое число
#define  ToCPU_GT_i     (uint32_t)0x0004     //Длина целой части переменной (числа)
#define  ToCPU_GT_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_Status_a     (uint32_t)0x0087     //Статус байт Флаги АИ
#define  ToCPU_Status_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_Status_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_Status_COMPARATORS_IS_VALID_a     (uint32_t)0x0087     //Значения компараторов действительны Да = 1, Нет = 0 (bit 0 [0:0])
#define  ToCPU_Status_COMPARATORS_IS_VALID_bit     (uint32_t)0x0000     //№ бита: Значения компараторов действительны Да = 1, Нет = 0 (bit 0 [0:0])

#define  ToCPU_Status_REQ_FOR_SETP_REPEAT_a     (uint32_t)0x0087     //Запрос на повторную передачу уставок Да = 1, Нет = 0 (bit 1 [0:1])
#define  ToCPU_Status_REQ_FOR_SETP_REPEAT_bit     (uint32_t)0x0001     //№ бита: Запрос на повторную передачу уставок Да = 1, Нет = 0 (bit 1 [0:1])

#define  ToCPU_Status_SUCCESS_CALIBRATION_a     (uint32_t)0x0087     //Калибровка прошла успешно Да = 1, Нет = 0 (bit 2 [0:2])
#define  ToCPU_Status_SUCCESS_CALIBRATION_bit     (uint32_t)0x0002     //№ бита: Калибровка прошла успешно Да = 1, Нет = 0 (bit 2 [0:2])

#define  ToCPU_Status_Write_Osc_a     (uint32_t)0x0087     //АИ производит запись осциллограммы Да = 1, Нет = 0 (bit 3 [0:3])
#define  ToCPU_Status_Write_Osc_bit     (uint32_t)0x0003     //№ бита: АИ производит запись осциллограммы Да = 1, Нет = 0 (bit 3 [0:3])

#define  ToCPU_Status_IsDataOsc_a     (uint32_t)0x0087     //Буфер ответа содержит данные осциллографа Да = 1, Нет = 0 (bit 4 [0:4])
#define  ToCPU_Status_IsDataOsc_bit     (uint32_t)0x0004     //№ бита: Буфер ответа содержит данные осциллографа Да = 1, Нет = 0 (bit 4 [0:4])

#define  ToCPU_Status_VersionAI_a     (uint32_t)0x0087     //Буфер содержит версию АИ Да = 1, Нет = 0 (bit 5 [0:5])
#define  ToCPU_Status_VersionAI_bit     (uint32_t)0x0005     //№ бита: Буфер содержит версию АИ Да = 1, Нет = 0 (bit 5 [0:5])

#define  ToCPU_Status_DataFromOut_a     (uint32_t)0x0087     //Буфер содержит ответ на внешний запрос непосредственно к плате АИ Да = 1, Нет = 0 (bit 6 [0:6])
#define  ToCPU_Status_DataFromOut_bit     (uint32_t)0x0006     //№ бита: Буфер содержит ответ на внешний запрос непосредственно к плате АИ Да = 1, Нет = 0 (bit 6 [0:6])

#define  ToCPU_Status_CalibrationCoefficients_a     (uint32_t)0x0087     //Буфер содержит калибровочные коэффициенты. Ответ на комманду Да = 1, Нет = 0 (bit 7 [0:7])
#define  ToCPU_Status_CalibrationCoefficients_bit     (uint32_t)0x0007     //№ бита: Буфер содержит калибровочные коэффициенты. Ответ на комманду Да = 1, Нет = 0 (bit 7 [0:7])

//-------------------------------------------------------------
#define  ToCPU_AddData_Length     (uint32_t)0x004B     //Длина структуры Буфер доп дпнных

#define  ToCPU_AddData_a     (uint32_t)0x0088     //Буфер доп дпнных

#define  ToCPU_AddData_B01_a     (uint32_t)0x0088     //Байт 01
#define  ToCPU_AddData_B01_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B01_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B02_a     (uint32_t)0x0089     //Байт 02
#define  ToCPU_AddData_B02_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B02_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B03_a     (uint32_t)0x008A     //Байт 03
#define  ToCPU_AddData_B03_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B03_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B04_a     (uint32_t)0x008B     //Байт 04
#define  ToCPU_AddData_B04_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B04_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B05_a     (uint32_t)0x008C     //Байт 05
#define  ToCPU_AddData_B05_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B05_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B06_a     (uint32_t)0x008D     //Байт 06
#define  ToCPU_AddData_B06_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B06_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B07_a     (uint32_t)0x008E     //Байт 07
#define  ToCPU_AddData_B07_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B07_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B08_a     (uint32_t)0x008F     //Байт 08
#define  ToCPU_AddData_B08_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B08_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B09_a     (uint32_t)0x0090     //Байт 09
#define  ToCPU_AddData_B09_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B09_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B10_a     (uint32_t)0x0091     //Байт 10
#define  ToCPU_AddData_B10_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B10_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B11_a     (uint32_t)0x0092     //Байт 11
#define  ToCPU_AddData_B11_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B11_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B12_a     (uint32_t)0x0093     //Байт 12
#define  ToCPU_AddData_B12_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B12_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B13_a     (uint32_t)0x0094     //Байт 13
#define  ToCPU_AddData_B13_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B13_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B14_a     (uint32_t)0x0095     //Байт 14
#define  ToCPU_AddData_B14_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B14_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B15_a     (uint32_t)0x0096     //Байт 15
#define  ToCPU_AddData_B15_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B15_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B16_a     (uint32_t)0x0097     //Байт 16
#define  ToCPU_AddData_B16_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B16_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B17_a     (uint32_t)0x0098     //Байт 17
#define  ToCPU_AddData_B17_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B17_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B18_a     (uint32_t)0x0099     //Байт 18
#define  ToCPU_AddData_B18_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B18_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B19_a     (uint32_t)0x009A     //Байт 19
#define  ToCPU_AddData_B19_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B19_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B20_a     (uint32_t)0x009B     //Байт 20
#define  ToCPU_AddData_B20_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B20_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B21_a     (uint32_t)0x009C     //Байт 21
#define  ToCPU_AddData_B21_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B21_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B22_a     (uint32_t)0x009D     //Байт 22
#define  ToCPU_AddData_B22_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B22_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B23_a     (uint32_t)0x009E     //Байт 23
#define  ToCPU_AddData_B23_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B23_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B24_a     (uint32_t)0x009F     //Байт 24
#define  ToCPU_AddData_B24_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B24_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B25_a     (uint32_t)0x00A0     //Байт 25
#define  ToCPU_AddData_B25_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B25_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B26_a     (uint32_t)0x00A1     //Байт 26
#define  ToCPU_AddData_B26_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B26_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B27_a     (uint32_t)0x00A2     //Байт 27
#define  ToCPU_AddData_B27_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B27_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B28_a     (uint32_t)0x00A3     //Байт 28
#define  ToCPU_AddData_B28_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B28_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B29_a     (uint32_t)0x00A4     //Байт 29
#define  ToCPU_AddData_B29_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B29_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B30_a     (uint32_t)0x00A5     //Байт 30
#define  ToCPU_AddData_B30_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B30_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B31_a     (uint32_t)0x00A6     //Байт 31
#define  ToCPU_AddData_B31_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B31_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B32_a     (uint32_t)0x00A7     //Байт 32
#define  ToCPU_AddData_B32_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B32_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B33_a     (uint32_t)0x00A8     //Байт 33
#define  ToCPU_AddData_B33_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B33_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B34_a     (uint32_t)0x00A9     //Байт 34
#define  ToCPU_AddData_B34_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B34_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B35_a     (uint32_t)0x00AA     //Байт 35
#define  ToCPU_AddData_B35_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B35_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B36_a     (uint32_t)0x00AB     //Байт 36
#define  ToCPU_AddData_B36_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B36_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B37_a     (uint32_t)0x00AC     //Байт 37
#define  ToCPU_AddData_B37_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B37_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B38_a     (uint32_t)0x00AD     //Байт 38
#define  ToCPU_AddData_B38_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B38_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B39_a     (uint32_t)0x00AE     //Байт 39
#define  ToCPU_AddData_B39_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B39_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B40_a     (uint32_t)0x00AF     //Байт 40
#define  ToCPU_AddData_B40_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B40_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B41_a     (uint32_t)0x00B0     //Байт 41
#define  ToCPU_AddData_B41_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B41_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B42_a     (uint32_t)0x00B1     //Байт 42
#define  ToCPU_AddData_B42_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B42_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B43_a     (uint32_t)0x00B2     //Байт 43
#define  ToCPU_AddData_B43_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B43_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B44_a     (uint32_t)0x00B3     //Байт 44
#define  ToCPU_AddData_B44_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B44_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B45_a     (uint32_t)0x00B4     //Байт 45
#define  ToCPU_AddData_B45_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B45_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B46_a     (uint32_t)0x00B5     //Байт 46
#define  ToCPU_AddData_B46_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B46_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B47_a     (uint32_t)0x00B6     //Байт 47
#define  ToCPU_AddData_B47_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B47_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B48_a     (uint32_t)0x00B7     //Байт 48
#define  ToCPU_AddData_B48_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B48_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B49_a     (uint32_t)0x00B8     //Байт 49
#define  ToCPU_AddData_B49_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B49_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B50_a     (uint32_t)0x00B9     //Байт 50
#define  ToCPU_AddData_B50_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B50_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B51_a     (uint32_t)0x00BA     //Байт 51
#define  ToCPU_AddData_B51_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B51_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B52_a     (uint32_t)0x00BB     //Байт 52
#define  ToCPU_AddData_B52_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B52_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B53_a     (uint32_t)0x00BC     //Байт 53
#define  ToCPU_AddData_B53_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B53_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B54_a     (uint32_t)0x00BD     //Байт 54
#define  ToCPU_AddData_B54_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B54_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B55_a     (uint32_t)0x00BE     //Байт 55
#define  ToCPU_AddData_B55_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B55_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B56_a     (uint32_t)0x00BF     //Байт 56
#define  ToCPU_AddData_B56_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B56_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B57_a     (uint32_t)0x00C0     //Байт 57
#define  ToCPU_AddData_B57_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B57_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B58_a     (uint32_t)0x00C1     //Байт 58
#define  ToCPU_AddData_B58_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B58_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B59_a     (uint32_t)0x00C2     //Байт 59
#define  ToCPU_AddData_B59_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B59_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B60_a     (uint32_t)0x00C3     //Байт 60
#define  ToCPU_AddData_B60_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B60_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B61_a     (uint32_t)0x00C4     //Байт 61
#define  ToCPU_AddData_B61_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B61_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B62_a     (uint32_t)0x00C5     //Байт 62
#define  ToCPU_AddData_B62_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B62_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B63_a     (uint32_t)0x00C6     //Байт 63
#define  ToCPU_AddData_B63_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B63_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B64_a     (uint32_t)0x00C7     //Байт 64
#define  ToCPU_AddData_B64_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B64_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B65_a     (uint32_t)0x00C8     //Байт 65
#define  ToCPU_AddData_B65_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B65_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B66_a     (uint32_t)0x00C9     //Байт 66
#define  ToCPU_AddData_B66_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B66_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B67_a     (uint32_t)0x00CA     //Байт 67
#define  ToCPU_AddData_B67_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B67_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B68_a     (uint32_t)0x00CB     //Байт 68
#define  ToCPU_AddData_B68_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B68_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B69_a     (uint32_t)0x00CC     //Байт 69
#define  ToCPU_AddData_B69_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B69_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B70_a     (uint32_t)0x00CD     //Байт 70
#define  ToCPU_AddData_B70_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B70_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B71_a     (uint32_t)0x00CE     //Байт 71
#define  ToCPU_AddData_B71_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B71_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B72_a     (uint32_t)0x00CF     //Байт 72
#define  ToCPU_AddData_B72_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B72_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B73_a     (uint32_t)0x00D0     //Байт 73
#define  ToCPU_AddData_B73_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B73_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B74_a     (uint32_t)0x00D1     //Байт 74
#define  ToCPU_AddData_B74_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B74_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_AddData_B75_a     (uint32_t)0x00D2     //Байт 75
#define  ToCPU_AddData_B75_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_AddData_B75_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)

#define  ToCPU_CS_a     (uint32_t)0x00D3     //Контрольная сумма XOR всего буфера (может плавать в зависимости от IOAI_RX_Length и IOAI_RX_Sign)
#define  ToCPU_CS_i     (uint32_t)0x0001     //Длина целой части переменной (числа)
#define  ToCPU_CS_f     (uint32_t)0x0000     // Длина дробной части переменной (числа)
//============================================================================================
//   Конец автоматически сгенерированого кода «MAP_TX_AI_to_CPU.h»
//============================================================================================
