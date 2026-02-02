#include "board_config.h"


QueDMACircular g_xCirclQue_Lidr;
QueDMACircular g_xCirclQue_Gmu;
QueDMACircular g_xCirclQue_ModNet;

u16 m_rawValue[(int)(eAnalogSensRank::max)];



u16* AnalogSensing_boardConfig(){

    static portSTM32Adc adcIf(nullptr);

    adcIf.GetAdcHw(&hadc1);

    adcIf.ADCStartDMA(&m_rawValue[0], (uint8_t)(eAnalogSensRank::max));


    return &m_rawValue[0];
}



ITimer* HardTimer_boardConfig(){

    static portSTM32Timer hardTimer;
    hardTimer.GetTimerInstace(&htim6);

    return (ITimer*)&hardTimer;
}



ICANBus* MainCANBus_boardConfing(){
    static portStm32CANBus g_Stm32CanBus(&hcan1);

	g_Stm32CanBus.OpenCANBus();


	return (ICANBus*)(&g_Stm32CanBus);
}




IGpio* KeepAliveLed_boardConfig(){

    static FactoryGpioPin keepAliveLed(GPIOE, GPIO_PIN_3);

    return keepAliveLed.GetGpioPin();
}





DrvRs485* ModuleNetworkPort_boardConfig(IGpio*& pIndicateLed){

    static FactoryGpioPin flowPin(GPIOD, GPIO_PIN_14);
    static FactoryGpioPin indicateLed(GPIOE, GPIO_PIN_5);
    static portSTM32Uart ModuleNetUart;
    static DrvRs485 ModuleNet;


    ModuleNetUart.InitHw(&huart6);
    
    ModuleNetUart.SetRcvQueuePtr(nullptr, &g_xCirclQue_ModNet, (u32*)&huart6.hdmarx->Instance->NDTR);
    ModuleNetUart.OpenPort(eUartRcvMode::DMA_BUF_CIRCULAR);


    pIndicateLed = indicateLed.GetGpioPin();


    ModuleNet.Init(&ModuleNetUart, flowPin.GetGpioPin());
    ModuleNet.AvailableSendDoneCheck(true);

    return &ModuleNet;
}





#define WHEEL_DIAMETER_MM      (3.141592 * 415)
#define GEAR_TOOTH_CNT          (57)




EncOneway* DriveSpeedSens_Config(){

    static EncOneway driveEngineEnc;
    static portSTM32_Pwm portPwmTmVehicleSpd(&htim2, TIM_CHANNEL_1);

    portPwmTmVehicleSpd.GetPwmSrcTimer(&htim2);
    portPwmTmVehicleSpd.InputCaptureOnOff(true, TIM_CHANNEL_1);

    // Timer Frq : 1Mhz, One Period timer tick : 20,000,000
    driveEngineEnc.Init((IPwm*)(&portPwmTmVehicleSpd), TIM_CHANNEL_1, 1*1000*1000, 20*1000*1000);

    driveEngineEnc.InitMechanicAttribute(WHEEL_DIAMETER_MM, GEAR_TOOTH_CNT);

    return &driveEngineEnc;
}






DigitFiltNode_t* DigitalIn_boardConfig(IGpio*& pPin1, IGpio*& pPin2, IGpio*& pPin3, IGpio*& pPin4){

    

    static FactoryGpioPin pin_1(GPI_MODE_SW_GPIO_Port, GPI_MODE_SW_Pin);
    static FactoryGpioPin pin_2(GPIOC, GPIO_PIN_13);
    static FactoryGpioPin pin_3(GPI_CTRLER_SW_GPIO_Port, GPI_CTRLER_SW_Pin);
    static FactoryGpioPin pin_4(GPIOD, GPIO_PIN_15);

    static DigitFiltNode_t xDigitInHeader       = {nullptr, 0, 0, nullptr};
    static DigitFiltNode_t xDigitIn_1      = {nullptr, 0, 0, nullptr};
    static DigitFiltNode_t xDigitIn_2   = {nullptr, 0, 0, nullptr};
    static DigitFiltNode_t xDigitIn_3     = {nullptr, 0, 0, nullptr};
    static DigitFiltNode_t xDigitIn_4     = {nullptr, 0, 0, nullptr};

    // assign pin
    pPin1 = pin_1.GetGpioPin();
    pPin2 = pin_2.GetGpioPin();
    pPin3 = pin_3.GetGpioPin();
    pPin4 = pin_4.GetGpioPin();

    xDigitInHeader.pxPin = nullptr;
    xDigitIn_1.pxPin = pPin1;
    xDigitIn_2.pxPin = pPin2;
    xDigitIn_3.pxPin = pPin3;
    xDigitIn_4.pxPin = pPin4;

    // link node ( = makes linked list)
    xDigitInHeader.next = &xDigitIn_1;
    xDigitIn_1.next = &xDigitIn_2;
    xDigitIn_2.next = &xDigitIn_3;
    xDigitIn_3.next = &xDigitIn_4;
    xDigitIn_4.next = &xDigitInHeader;

    /* ************************************************************************************
    버튼 디지털 입력 연결리스트 구조
    Node : Header ---> gpio_in_1 ---> gpio_in_2 ---> gpio_in_3 ---> gpio_in_4
    Pin  : (null)                                                        |
            /|\                                                          |
             |___________________________________________________________|

    ************************************************************************************ */
    

    return &xDigitInHeader;
}




bool DigitalOut1_boardConfig(IGpio*& pBuzzor, IGpio*& pBoostLed, IGpio*& pHeadlight){

    static FactoryGpioPin BuzzorPin(GPIOD, GPIO_PIN_11);
    static FactoryGpioPin BoostLedPin(GPIOE, GPIO_PIN_6);
    static FactoryGpioPin HeadLightPin(GPIOE, GPIO_PIN_15);

    pBuzzor = BuzzorPin.GetGpioPin();
    pBoostLed = BoostLedPin.GetGpioPin();
    pHeadlight = HeadLightPin.GetGpioPin();

    return true;
}


bool DigitalOut2_boardConfig( IGpio*& pStsLightL, IGpio*& pStsLightR, IGpio*& pBrkLight){

    static FactoryGpioPin StsLeftLightPin(GPIOD, GPIO_PIN_4);
    static FactoryGpioPin StsRightLightPin(GPIOD, GPIO_PIN_3);
    static FactoryGpioPin BrakeLightPin(GPIOB, GPIO_PIN_8);

    pStsLightL = StsLeftLightPin.GetGpioPin();
    pStsLightR = StsRightLightPin.GetGpioPin();
    pBrkLight = BrakeLightPin.GetGpioPin();

    return true;
}





