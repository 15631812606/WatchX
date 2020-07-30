#include "FileGroup.h"
#include "GUI/DisplayPrivate.h"
#include "MillisTaskManager/MillisTaskManager.h"

/*���������*/
static MillisTaskManager mtmMain;

/*CPUռ����(DEBUG��)*/
float CPU_Usage;

/**
  * @brief  CPUռ���ʸ���
  * @param  ��
  * @retval ��
  */
static void CPU_UsageUpdate()
{
    CPU_Usage = mtmMain.GetCPU_Usage();
}

/**
  * @brief  ϵͳ��ʼ��
  * @param  ��
  * @retval ��
  */
static void setup()
{
    /*LED*/
    pinMode(LED_Pin, OUTPUT);
    digitalWrite(LED_Pin, HIGH);
    
    /*��Դ����*/
    pinMode(POWER_ON_Pin, OUTPUT);
    digitalWrite(POWER_ON_Pin, HIGH);
    
    /*��Դ����*/
    pinMode(POWER_EN_Pin, INPUT);
    
    /*��س����*/
    pinMode(BAT_CHG_Pin, INPUT_PULLUP);

    /*�豸��ʼ��*/
    RTCx_Init();
    Power_Init();
    Backlight_Init();
    Button_Init();
    Display_Init();
    BMP_Init();
    
    /*��ص�ѹ���*/
    pinMode(BAT_DET_Pin, INPUT_ANALOG_DMA);
    ADC_DMA_Init();

    digitalWrite(LED_Pin, LOW);

    /*����ע��*/
    mtmMain.Register(Display_Update, 1);                //��Ļˢ��
    mtmMain.Register(Button_Update, 10);                //�����¼����
    mtmMain.Register(Power_AutoShutdownUpdate, 100);    //�Զ��ػ����
    mtmMain.Register(CPU_UsageUpdate, 1000);            //CPUռ���ʼ��
}

/**
  * @brief  ϵͳ��ѭ��
  * @param  ��
  * @retval ��
  */
static void loop()
{
    mtmMain.Running(millis());
}

/**
  * @brief  Main Function
  * @param  None
  * @retval None
  */
int main(void)
{
    NVIC_SetPriorityGrouping(NVIC_PriorityGroup_2);
    Delay_Init();
    setup();
    for(;;)loop();
}
