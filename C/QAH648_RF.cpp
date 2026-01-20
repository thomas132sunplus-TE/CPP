#include <Unison.h>
#include <iostream>
//===== NEW ADDED =====//
//#include "tiu_rw.h"
//#include <DlogMod.h>
#include <RF_math.h>
#include <ModDemod.h>
//#include <math.h>
#include "../Code/CohuAppLib.h"
#include "../Code/XdcAppLib.h"
//===== New ADDED END =====//
using namespace std;
StringS TEST123 = "myWaveBER";
BasicRfWaveform wave_SP_3DH5;
BoolS LoadWaveform;

//TMResultM ReturnValue(TMResultM val)
//{
//    return val;
//}
//void SetPowerSupply(PinML pins, FloatM value, FloatM range)
//{
//    VI.Initialize(pins);
//    VI.Connect(pins, VI_TO_DUT, VI_MODE_REMOTE);
//    VI.Gate(pins, VI_GATE_ON);
//    VI.SetMeasureIRange(pins, 1.0);
//    VI.SetClampsI(pins, 1.0);
//    VI.ForceV(pins, value, range);
//    TIME.Wait(5e-3);
//}
//
//void SetDigitalLevels(PinML pins, FloatM vil, FloatM vih, FloatM vol, FloatM voh, FloatM vref)
//{
//    DIGITAL.SetVihVil(pins, vih, vil);
//    DIGITAL.SetVohVol(pins, voh, vol);
//    DIGITAL.SetVref(pins, vref);
//}
//
//void SetDriversLow(PinML pins)
//{
//    DIGITAL.SetDriveMode(pins, DIGITAL_DRV_MODE_OFF);
//    DIGITAL.SetLoadMode(pins, DIGITAL_LD_MODE_OFF);
//}
//
//void RestoreDrivers(PinML pins)
//{
//    DIGITAL.SetDriveMode(pins, DIGITAL_DRV_MODE_PATTERN);
//    DIGITAL.SetLoadMode(pins, DIGITAL_LD_MODE_OFF);
//}
//
//void Disconnect(PinML pins)
//{
//    DIGITAL.Disconnect(pins, DIGITAL_DCL_TO_DUT);
//    
//    cout << "The following pins: " << pins << " have been disconnected from the tester.";
//    
//}
//
//FloatM AddMyValues(FloatM a, FloatM b)
//{
//	return a+b;
//}
//
//void StartClock()
//{
//	TIME.StartTimer();
//}
//
//
//TMResultM StopClock(FloatS MinTimeLimit, FloatS MaxTimeLimit, FloatS sim_value)
//{
//	FloatS meas_Result;
//  
//  if(RunTime.ConnectedToTester())
//    meas_Result = TIME.StopTimer();
//  else
//    meas_Result = sim_value;
//  
//  TMResultM TestTime = DLOG.Value(meas_Result, MinTimeLimit, MaxTimeLimit, "s",
//    "Elapsed Time", UTL_VOID, UTL_VOID, 0, ER_PASS, true);
//  
//  return (TestTime);
//}




//// =================================================== RF BT Testing =========================================== ////



    PinM        srcPin      = "BTRF";
    PinM        msrPin      = "BTRF";    
    PinML       Rx_IQ       = "DIG_I+DIG_Q";    //Captures BaseBand data.
    FloatS      CWTonPWR_Loss = 0.2dB+0.3dB;
    FloatS      TTonPWR_Loss  = 0.5dB+0.4dB;
    FloatM      Site_RF_Offset;
    
    IntS        RX_N        = 4096*2;
    FloatM      RX_Fs       = 32.768MHz;
    UnsignedM   RX_Points   = 4096*2;
    FloatM      Impd        = 50Ohm;
    
    StringS     PatternID;
    StringS     ReadFreqName; 
    StringS     Bist_Ver = "NONE" ;
    
//    FloatM      GlobalVariable_24440MHz_P_Gfsk = 10.2; 
    FloatM      GlobalVariable_24440MHz_P_Gfsk = 0.0; 
   
void ReadFreq(StringS &Freq_Name, FloatM CHKFrq) {
    if (CHKFrq==2407MHz){
    Freq_Name = "2407MHz";  }
    else if (CHKFrq==2440MHz){
    Freq_Name = "2440MHz";  }   
    else if (CHKFrq==2475MHz){
    Freq_Name = "2475MHz";  }
    else {Freq_Name = "No_Freq"; }
}    


void RF_OnLoadT() {
//    StringS wave_path = SYS.GetProgramPath();

    wave_SP_3DH5.LoadFromFile(TEST123,SYS.GetProgramPath() + "/../Waveforms/Bluetooth_3DH5_prbs9_SyncWord0x12345601234_LTADDR0_Flow0_ARQN0_SEQN1_LLID2_Flow0_Length1021_PnSeq0x1ff_fs32MHz_3.75ms.urf" );
    LoadWaveform = true;

    Site_RF_Offset[SITE_1] = 0.00dB;
    Site_RF_Offset[SITE_2] = 0.00dB;
    Site_RF_Offset[SITE_3] = 0.00dB;
    Site_RF_Offset[SITE_4] = 0.00dB;

}


void RF_UnLoadT() { 
    DSP.DeleteAllWaveforms();
    RF.Terminate("BTRF");      
}


void RF_PwrOn() {

std::cout << endl; 
std::cout << "  //// ===== BT START TESTING ===== ////  " << endl; 

    DIGITAL.Disconnect("AllPins_Pattern",DIGITAL_ALL_PATHS);

    CBIT.Close("K14");
    CBIT.Close("K4");
    CBIT.Close("K5");
    CBIT.Close("K6");
  
    CBIT.Close("K26"); // For UART Relay of Debugging
    TIME.Wait(0ms);



    VI.SetMeasureIRange("VDD11",1.0A); 
    
    DIGITAL.SetVihVil("AllPins_Pattern", 3.3V, 0.0V);
    DIGITAL.SetVohVol("AllPins_Pattern", 1.65V, 1.65V);
    DIGITAL.SetRlv("AllPins_Pattern", 4.2kOhm);    
    DIGITAL.SetVref("AllPins_Pattern", 0.0V);

    DIGITAL.Connect("AllPins_Pattern",DIGITAL_DCL_TO_DUT);
    DIGITAL.SetDriveMode("AllPins_Pattern",DIGITAL_DRV_MODE_PATTERN);

    DIGITAL.SetLoadMode("G_MX17+IV_MX0+IV_MX1+IV_MX2", DIGITAL_LD_MODE_RLOAD);
    DIGITAL.SetRlv("G_MX17+IV_MX0+IV_MX1+IV_MX2", 4.2kOhm);
    DIGITAL.SetVref("G_MX17+IV_MX0+IV_MX2", 3.3V);
    DIGITAL.SetVref("IV_MX1", 0.0V);
    TIME.Wait(1ms);

    DIGITAL.ExecutePattern("RF_SPI_MODE_RF_PwrOn_Trap");
    TIME.Wait(0ms);
 
 
    PinML DPS("VDD33+VDD11");
    VI.SetClampsI(DPS, 700.0mA);

    VI.Connect ("AllPwr_1p1V", VI_TO_DUT,VI_MODE_REMOTE );
    VI.ForceV ("AllPwr_1p1V", 1.1V);
    VI.Gate ("AllPwr_1p1V", VI_GATE_ON);

    VI.Connect ("AllPwr_3p3V", VI_TO_DUT,VI_MODE_REMOTE );
    VI.ForceV ("AllPwr_3p3V", 3.3V);
    VI.Gate ("AllPwr_3p3V", VI_GATE_ON);
//    VI.ForceV ("USB_VDD33", 1.0V);



    VI.Connect ("AllPwr_BT_1p35V", VI_TO_DUT,VI_MODE_REMOTE );
    VI.ForceV ("AllPwr_BT_1p35V", 1.45V);
    VI.Gate ("AllPwr_BT_1p35V", VI_GATE_ON);

    VI.Connect ("OTP_2p5V", VI_TO_DUT,VI_MODE_REMOTE );
    VI.ForceV ("OTP_2p5V", 0.0V);
    VI.Gate ("OTP_2p5V", VI_GATE_ON);

    VI.Connect ("PSRAM_1p8V", VI_TO_DUT,VI_MODE_REMOTE );
    VI.ForceV ("PSRAM_1p8V", 1.8V);
    VI.Gate ("PSRAM_1p8V", VI_GATE_ON);

    VI.Connect ("VDDA_PA", VI_TO_DUT,VI_MODE_REMOTE );
    VI.ForceV ("VDDA_PA", 2.4V);
    VI.Gate ("VDDA_PA", VI_GATE_ON);

    VI.Connect ("SPI_FLASH_VDD33",VI_TO_DUT,VI_MODE_REMOTE);
    VI.ForceV ("SPI_FLASH_VDD33", 3.3V);
    VI.Gate ("SPI_FLASH_VDD33", VI_GATE_ON);

    VI.Connect ("VCC_U1+VCC_U3",VI_TO_DUT,VI_MODE_REMOTE);
    VI.ForceV ("VCC_U1+VCC_U3", 5.0V);
    VI.Gate ("VCC_U1+VCC_U3", VI_GATE_ON);
    TIME.Wait(0ms);    
    
    VI.Connect ("VEE_U1+VEE_U3",VI_TO_DUT,VI_MODE_REMOTE);
    VI.ForceV ("VEE_U1+VEE_U3", -5.0V);
    VI.Gate ("VEE_U1+VEE_U3", VI_GATE_ON);
    TIME.Wait(0ms);    


//
    VI.SetMeasureIRange("AllPwr_3p3V",250mA);
    VI.SetMeasureIRange("AllPwr_1p1V",250mA);
    VI.SetMeasureIRange("VDD11",1.0A); 
    VI.SetMeasureIRange("AllPwr_BT_1p35V",250mA);
    VI.SetMeasureIRange("OTP_2p5V",250mA);
    VI.SetMeasureIRange("PSRAM_1p8V",250mA);
    VI.SetMeasureIRange("VDDA_PA",250mA);
    VI.SetMeasureIRange("SPI_FLASH_VDD33",250mA);
    
//    TIME.Wait(120ms);  // <<< Pervious code>>>
//    TIME.Wait(300ms);  // <<< 1.3 code>>>
//    CBIT.Close("K26");
    TIME.Wait(600ms);  // <<< For after New Flash code rev2.1 >>>  
 
}


TMResultM RF_SPI_FuncTest(IntS MinorID, StringS PatternID)
{ 
    TMResultM testResult = TM_NOTEST, local_Result ;
    StringS FuncName;

    
    if (PatternID == "RF_PSRAM_TEST_ID100"){
    FuncName = "PSRAM";  }
        else if (PatternID == "RF_PSDIF_AMP_Start_TEST_ID101"){
    FuncName = "SPDIF_AMP";  }   
        else if (PatternID == "RF_BIST_DFT_ID0"){
    FuncName = "RF_BIST_DFT";
    Bist_Ver = "_1P15";         
std::cout << endl; 
std::cout << "  //// ===== BIST 1P15 ===== ////  " << endl;     
                                                }
        else if (PatternID == "RF_BIST_1P1_ID22"){
    FuncName = "RF_BIST_1P1";  
    Bist_Ver = "_1P1";         }
        else {FuncName = "No_Pat"; }

    if ( PatternID != "RF_PSDIF_AMP_Stop_TEST_ID102" && PatternID != "RF_RESET_ID255" ) {
        //testResult = XdcFuncTest123(MinorID+00, FuncName+"_SPI_Pat", "RF_SPI_fail", PatternID, "AllPins_Pattern" );
//        DIGITAL.ExecutePattern("RF_RESET_ID255");
        
        testResult = XdcFuncTest123(MinorID+00, FuncName+"_SPI_Pat", UTL_VOID, PatternID, "AllPins_Pattern" );
        DLOG.AccumulateResults(local_Result, testResult);
        TIME.Wait(3ms);    }
    else if (PatternID == "RF_PSDIF_AMP_Stop_TEST_ID102") {
        DIGITAL.ExecutePattern(PatternID);
        std::cout<<"Running the RF_PSDIF_AMP_Stop_TEST_ID102 .."<< endl; 
        TIME.Wait(1ms);    } 
    else if (PatternID == "RF_RESET_ID255") {
        DIGITAL.ExecutePattern(PatternID);  
        TIME.Wait(0ms);    } 

    return (local_Result);    
}


TMResultM SPDIF_AMP_FuncTest(IntS MinorID, StringS PatternID)
{ 
    TMResultM testResult = TM_NOTEST, local_Result ;
    StringS FuncName;
    
     if (PatternID == "RF_PSDIF_AMP_Start_TEST_ID101"){
         FuncName = "SPDIF_AMP";  }   
     else {FuncName = "No_Pat"; }
      
      // G_MX14 to PEC
        CBIT.Close("K7");
        CBIT.Close("K40");
      // G_MX33 to PEC
        CBIT.Close("K8");
        CBIT.Close("K41");
        
        DIGITAL.SetVihVil("G_MX14", 0.334V, 0.0V); //  200mV= 334mV*(75 OMh/(75 +50))
        DIGITAL.SetVihVil("G_MX33", 0.334V, 0.0V);
        TIME.Wait(5ms);
        
        testResult = XdcFuncTest123(MinorID+00, FuncName+"_SPI_Pat", UTL_VOID, PatternID, "AllPins_Pattern" );
        DLOG.AccumulateResults(local_Result, testResult);
        TIME.Wait(3ms); 
   
        DIGITAL.ExecutePattern("RF_PSDIF_AMP_Stop_TEST_ID102");
        std::cout<<"Running the RF_PSDIF_AMP_Stop_TEST_ID102 .."<< endl; 
   
   
        DIGITAL.SetVihVil("G_MX14", 3.2V, 0V);
        DIGITAL.SetVihVil("G_MX33", 3.2V, 0V);
        
    CBIT.Open("K7+ K40");
    CBIT.Open("K8+ K41");
    return (local_Result);    
}

TMResultM RF_RX_IM3_Measure(const FloatS MainTone_srcFreq, FloatS ToneLevel, IntS MinorID, StringS PatternID)
{  

    TMResultM testResult = TM_NOTEST, local_Result ;
    TMResultM IM3pat_testResult = TM_NOTEST ;
    
    FloatS ToneSpacing = 3MHz;     
    ReadFreq(ReadFreqName, MainTone_srcFreq);
    
    FloatM2D ComplexCapture(RX_N*2), ComplexCaptureSim(RX_N*2);  //RX_N = 4096*2;
    FloatM1D ComplexCapture_I(RX_N), ComplexCapture_Q(RX_N);
    FloatM1D ComplexCapture_merge;
    FloatM1D ComplexSpectrumVp, ComplexSpectrumRMS; 
        
    FloatM1D IQ_dBm(2048, -99.0);

    FloatM RBW = RX_Fs / RX_N;  //Target 4K
    FloatM Bin_1M = 1MHz / RBW;
    FloatM  L_Tone_VoltP, L_IM3_VoltP, L_Main_ToneVp, I_PWR, Q_PWR;
    
    CBIT.Close("K3");
    CBIT.Close("K28");

//    testResult = XdcFuncTest(testResult, MinorID-100, "RF_BIST_DFT", "RF_BIST_DFT_fail", "RF_BIST_DFT_ID0", "AllPins_Pattern" ); 
//    TIME.Wait(10ms);   

//    DIGITAL.ExecutePattern(PatternID);
    testResult = XdcFuncTest(IM3pat_testResult, MinorID+00, ReadFreqName+Bist_Ver+"IM3_PAT", "RF_Rx_IM3_PAT_fail", PatternID, "AllPins_Pattern" );    
    TIME.Wait(5ms);

    StringS waveform = "AWG Signal";
    FloatS AwgFs;
    FloatS Max_AwgFs = 60MHz;
    FloatS AwgFF = 1KHz;        
    RfPowerSpectrum spec;
    BoolS splitMode = false;

//Define Two Tone Parameter
    FloatS OffsetFreq =  0.0MHz;   //First Tone at XMHz,Second Tone at XXMHz
    FloatS AwgFilter = 50kHz;
    FloatM1D ComplexArr;
    FloatM par;

TIME.StartTimer();

//Generate 2 Tone using VSA library
    BasicRfWaveform TwoToneWave = VSA.Math.TwoTone(ToneSpacing,OffsetFreq,Max_AwgFs); 
    FloatM1D I_Array_VSA = TwoToneWave.iArray;
    FloatM1D Q_Array_VSA = TwoToneWave.qArray;
    AwgFs= TwoToneWave.bbSampleRate;
//    VSAPlotter::PLOT.BasicLine("ITime","Wave","I",I_Array_VSA) ;
//    VSAPlotter::PLOT.BasicLine("QTime","Wave","Q",Q_Array_VSA) ; 
    VSA.Math.InterleaveComplex(I_Array_VSA,Q_Array_VSA,ComplexArr);
    spec.CreateFromCplxTime(ComplexArr,AwgFs,AwgFF,0Hz) ;

    FloatM srcFiltFreq_M = 100MHz;  
    FloatM Max_AwgFs_M = 60MHz;

    StringS IDString = "TwoToneSource";

        RF.DeleteSetup      ( IDString );
        RF.DefineSetup      ( IDString , srcPin , RF_SOURCE_MOD,RF_GEN_SPLIT);
        RF.ResolveSetup     ( IDString );
        RF.SelectSetup      ( IDString );     
        
        RF.DefineWaveform   ( IDString , srcPin , Max_AwgFs_M , srcFiltFreq_M , RF_SAMPLING_AUTO , RF_MODULATION_I_Q , RF_TONE_1 );
        RF.LoadWaveform     ( IDString , I_Array_VSA ,Q_Array_VSA ,RF_TONE_1 );
        RF.ConnectAWG       ( srcPin , RF_MODULATION_I_Q, RF_TONE_1 );
        RF.SelectWaveform   ( IDString , srcPin ,RF_MODULATION_I_Q,RF_TONE_1);  // aryOffset , blockSz , RF_MODULATION_I_Q, RF_TONE_1);
        RF.EnableModulation ( srcPin   );
        RF.Prepare();
        TIME.Wait(3ms);
        
        RF.SetSource        ( srcPin, ToneLevel+6.0206dB+TTonPWR_Loss, MainTone_srcFreq+4.5MHz, RF_PERFORMANCE_HIGH_LINEARITY); //    ToneLevel = Setting + 6.0206dB;  // + peak to rms of waveform; // 2402MHz+4.5MHz for TwoTone 2405MHz & 2408MHz tonespacing
        TIME.Wait(0ms);
         
        RF.StartAWG(srcPin, RF_MODULATION_I_Q, RF_TONE_1);
        TIME.Wait(1ms);

//        RF.SetSource("BTRF" , -120dBm , MainTone_srcFreq+4.5MHz , RF_PERFORMANCE_HIGH_LINEARITY );
//        RF.Terminate("BTRF");

// ===== Send and Measure Rx_IM3 PWR ===== //
    Sites RunSites = ActiveSites; //keeps Running sites
    Sites GP1_Sites = NO_SITES ;
    Sites GP2_Sites = NO_SITES ;
    for (SiteIter siteIter = ActiveSites.Begin(); !siteIter.End(); ++siteIter) {   
  
    if (IntS(siteIter.GetValue()) == 1 || IntS(siteIter.GetValue()) == 3 )
    {GP1_Sites = GP1_Sites + siteIter.GetValue();}
    else if (IntS(siteIter.GetValue()) == 2 || IntS(siteIter.GetValue()) == 4 )
    {GP2_Sites = GP2_Sites + siteIter.GetValue();} 
    }

    if(GP1_Sites!=NO_SITES) {
    RunTime.SetActiveSites(GP1_Sites); 
        DSP.Initialize(Rx_IQ);
        DSP.SetConfiguration(Rx_IQ, DSP_CONFIG_DIRECT);
        DSP.Connect(Rx_IQ,DSP_TO_DUT,DSP_MODE_SE);
        DSP.SetOffsetMode (Rx_IQ, DSP_OFFSET_DUT);
        DSP.DefineWaveform("MyCapture1", Rx_IQ);
        DSP.SetSampleRate("MyCapture1", RX_Fs);
        DSP.SetFilter("MyCapture1", DSP_FILTER_LOW_PASS, 22MHz);
        DSP.SetRange("MyCapture1", 1V);
        DSP.SetPoints ("MyCapture1", RX_Points);
//        DIGITAL.DisconnectSyncRefs();
//        DSP.SetTimeout(2.0s);

        DSP.Select("MyCapture1", Rx_IQ);
        DSP.Prepare();
        TIME.Wait(10ms);    
        DSP.Start(Rx_IQ);
        TIME.Wait(10ms);
        BoolM1D DigitizerTimeout = DSP.Wait(Rx_IQ);

        
        if (DigitizerTimeout.AllNotEqual(true)) {
            BoolM1D OverrangeFlag = DSP.ReadOverrangeFlag(Rx_IQ);
            if (OverrangeFlag.AllNotEqual(true)) {
                DSP.ReadWaveform("MyCapture1",Rx_IQ, ComplexCapture, ComplexCaptureSim, DSP_DATA_TYPE_ALL);
                TIME.Wait(1us);
            } else {
                 //handle over-range
            }
        } else {
              // handle timeout error
        }
 // display  GP1_Sites (s1/s3) DigHSB digitize data in DataViewer
 #if 0
    for (SiteIter _site = ActiveSites.Begin(); !_site.End(); ++_site)
      {
         std::cout << "IQ_Site13 = " << _site << endl;
         
         FloatM1D ComplexCapture_S13_I(RX_N), ComplexCapture_S13_Q(RX_N);
         for (int x =0; x< RX_N; x++)
           {
             ComplexCapture_S13_I [*_site][x] = ComplexCapture[*_site][0][x];
             ComplexCapture_S13_Q [*_site][x] = ComplexCapture[*_site][1][x];                     
             
             std::cout << "ComplexCapture_S13_I/Q[" << *_site << "] [" << x << "]" << ComplexCapture_S13_I [*_site][x] << " " << ComplexCapture_S13_Q [*_site][x] << endl;
            }
     }
#endif

    }    // End : if(GP1_Sites!=NO_SITES)

    if(GP2_Sites!=NO_SITES) {
    RunTime.SetActiveSites(GP2_Sites); 
        DSP.Initialize(Rx_IQ);
        DSP.SetConfiguration(Rx_IQ, DSP_CONFIG_DIRECT);
        DSP.Connect(Rx_IQ,DSP_TO_DUT,DSP_MODE_SE);
        DSP.SetOffsetMode (Rx_IQ, DSP_OFFSET_DUT);
        DSP.DefineWaveform("MyCapture2", Rx_IQ);
        DSP.SetSampleRate("MyCapture2", RX_Fs);
        DSP.SetFilter("MyCapture2", DSP_FILTER_LOW_PASS, 22MHz);
        DSP.SetRange("MyCapture2", 1V);
        DSP.SetPoints ("MyCapture2", RX_Points);
//        DIGITAL.DisconnectSyncRefs();
//        DSP.SetTimeout(2.0s);

        DSP.Select("MyCapture2", Rx_IQ);
        DSP.Prepare();
        TIME.Wait(10ms);    
        DSP.Start(Rx_IQ);
        TIME.Wait(10ms);
        BoolM1D DigitizerTimeout = DSP.Wait(Rx_IQ);

        if (DigitizerTimeout.AllNotEqual(true)) {
            BoolM1D OverrangeFlag = DSP.ReadOverrangeFlag(Rx_IQ);
            if (OverrangeFlag.AllNotEqual(true)) {
                DSP.ReadWaveform("MyCapture2",Rx_IQ, ComplexCapture, ComplexCaptureSim, DSP_DATA_TYPE_ALL);
                TIME.Wait(1us);
            } else {
                 //handle over-range
            }
        } else {
              // handle timeout error
        }
// display  GP2_Sites (s2/s4) DigHSB digitize data in DataViewer        
 #if 0
    for (SiteIter _site = ActiveSites.Begin(); !_site.End(); ++_site)
      {
         std::cout << "IQ_Site24 = " << _site << endl;
         
         FloatM1D ComplexCapture_S24_I(RX_N), ComplexCapture_S24_Q(RX_N);
         for (int x =0; x< RX_N; x++)
           {
             ComplexCapture_S24_I [*_site][x] = ComplexCapture[*_site][0][x];
             ComplexCapture_S24_Q [*_site][x] = ComplexCapture[*_site][1][x];                     
             
             std::cout << "ComplexCapture_S24_I/Q[" << *_site << "] [" << x << "]" << ComplexCapture_S24_I [*_site][x] << " " << ComplexCapture_S24_Q [*_site][x] << endl;
            }
     }
#endif
        
    }  // END :  if(GP2_Sites!=NO_SITES)

    RunTime.SetActiveSites(RunSites);
 //       DSP.DeleteWaveform("TwoToneSource");
        DSP.Stop(Rx_IQ);
        RF.StopAWG(srcPin, RF_MODULATION_I_Q, RF_TONE_1);
        RF.SetSource(srcPin , -120dBm , MainTone_srcFreq+4.5MHz , RF_PERFORMANCE_HIGH_LINEARITY );
        RF.Terminate(srcPin);
    
        for (SiteIter _site = ActiveSites.Begin(); !_site.End(); ++_site)
        {
//          RunTime.SetActiveSites(*_site);
          RunTime.SetActiveSites(_site.GetValue());
          
//          std::cout<< endl;
//          IntS siteNo= _site.GetValue();
//          std::cout<<"Site= "<< siteNo<< endl;

          std::cout << "IQ_Site = " << _site << endl;
          for (int x =0; x< RX_N; x++)
          {
             ComplexCapture_I [*_site][x] = ComplexCapture[*_site][0][x];
             ComplexCapture_Q [*_site][x] = ComplexCapture[*_site][1][x];                     
//             std::cout << "ComplexCapture_I/Q[" << *_site << "] [" << x << "]" << ComplexCapture_I [*_site][x] << " " << ComplexCapture_Q [*_site][x] << endl;
          }

                 VSA.Math.InterleaveComplex(ComplexCapture_Q,ComplexCapture_I,ComplexCapture_merge);
                 ComplexSpectrumVp = MATH.ComplexPowerFFT(ComplexCapture_merge); //Time Domain to Freq 
                 ComplexSpectrumRMS = MATH.Sqrt(ComplexSpectrumVp/2 + 1fV); //Vpp to Vrms Volt
                 IQ_dBm = CONV.VoltsTodBm(ComplexSpectrumRMS, Impd);

//                 VSA.Math.InterleaveComplex(ComplexCapture_Q[*_site],ComplexCapture_I[*_site],ComplexCapture_merge);
//                 ComplexSpectrumVp[*_site] = MATH.ComplexPowerFFT(ComplexCapture_merge[*_site]); //Time Domain to Freq 
//                 ComplexSpectrumRMS[*_site] = MATH.Sqrt(ComplexSpectrumVp[*_site]/2 + 1fV); //Vpp to Vrms Volt
//                 IQ_dBm[*_site] = CONV.VoltsTodBm(ComplexSpectrumRMS[*_site], Impd[*_site]);

                 TIME.Wait(1us);

#if 0
                 FloatM1D ComplexSpectrumVp_I = MATH.ComplexPowerFFT(ComplexCapture_I); //Time Domain to Freq 
                 FloatM1D ComplexSpectrumRMS_I = MATH.Sqrt(ComplexSpectrumVp_I/2 + 1fV); //Vpp to Vrms Volt
                 FloatM1D I_dBm = CONV.VoltsTodBm(ComplexSpectrumRMS_I, Impd);
                 TIME.Wait(1us);                 

                 FloatM1D ComplexSpectrumVp_Q = MATH.ComplexPowerFFT(ComplexCapture_Q); //Time Domain to Freq 
                 FloatM1D ComplexSpectrumRMS_Q = MATH.Sqrt(ComplexSpectrumVp_Q/2 + 1fV); //Vpp to Vrms Volt
                 FloatM1D Q_dBm = CONV.VoltsTodBm(ComplexSpectrumRMS_Q, Impd);
                 TIME.Wait(1us); 

                 FloatM1D Spectrum_I = I_dBm.Slice(3090,3110);
                 FloatM1D Tone_Desire_I  = MATH.Xtrm(Spectrum_I);
                 I_PWR = Tone_Desire_I[0];
                 FloatM1D Spectrum_Q = Q_dBm.Slice(3090,3110);
                 FloatM1D Tone_Desire_Q  = MATH.Xtrm(Spectrum_Q);
                 Q_PWR = Tone_Desire_Q[0];
#endif                 

//    std::cout << ReadFreqName+"_I_TonePwr = "<< I_PWR    << endl;  
//    std::cout << ReadFreqName+"_Q_TonePwr = "<< Q_PWR    << endl;  

                //RBW 8K, 1MHz_Bin =125 ; 4MHz_Bin = 500  ; Diff = 375.
                //RBW 4K, 1MHz_Bin =250 ; 4MHz_Bin = 1000 ; Diff = 750.
                    FloatM  L_IM3 = Bin_1M;   // 250              
                    IntM    L_Tone    = L_IM3 + 375*2;
                    IntM    L_STp     = L_Tone - 10 , L_SPp     = L_Tone + 10;
                    IntM    L_IM3_STp = L_IM3 - 10  , L_IM3_SPp = L_IM3+10;
                    IntS ToneLL_Bin = 0, ToneLR_Bin = 0;
                    IntS IM3LL_Bin  = 0, IM3LR_Bin  = 0;
                    
                    FloatM1D Spectrum_L(21, -99), Spectrum_L_IM3(21, -99);
                             Spectrum_L = ComplexSpectrumVp.Slice(L_STp,L_SPp); //990, 1010
                    FloatM1D Tone_Desire_L  = MATH.Xtrm(Spectrum_L);

                    ToneLL_Bin = Tone_Desire_L[*_site][1]-1;
                    ToneLR_Bin = Tone_Desire_L[*_site][1]+1;

                    
//std::cout << endl;
//std::cout << "IM3_COUNT_Site = " << _site << endl;
//std::cout << "IM3_Desire_L = "<< IM3_Desire_L[*_site][1]   ; 
//std::cout << ",  Spectrum_L_IM3 = "<< IM3LL_Bin   ; 
//std::cout << ",  Spectrum_L_IM3 = "<< IM3LR_Bin   ;
//std::cout << endl;                        
                    
                    if (( ToneLL_Bin < 1) ||( ToneLR_Bin > 20 )) {
                    std::cout << "IQ_Site3 = " << _site << endl;
                    L_Tone_VoltP[*_site] = 1fV;}
                    else {
                    L_Tone_VoltP[*_site] = (Tone_Desire_L[*_site][0] + Spectrum_L[*_site][ToneLL_Bin]+ Spectrum_L[*_site] [ToneLR_Bin]);
                    
                    #if 1
                    std::cout<<"L_Tone_BIN["<< *_site<< "]= "<< Tone_Desire_L[*_site][1]+990 << endl;
                    std::cout<<"L_Tone_VoltP["<< *_site<< "]= "<< Spectrum_L[*_site][ToneLL_Bin]<< "+ "<< Tone_Desire_L[*_site][0]<< "+ " << Spectrum_L[*_site] [ToneLR_Bin]<< endl;  
                    
                    
                    #endif
                    
                    }
                    
                    L_Main_ToneVp[*_site] = Tone_Desire_L[*_site][0];

                    Spectrum_L_IM3 = ComplexSpectrumVp.Slice(L_IM3_STp,L_IM3_SPp); //240, 260
                    FloatM1D IM3_Desire_L  = MATH.Xtrm(Spectrum_L_IM3);
                    IM3LL_Bin = IM3_Desire_L[*_site][1]-1;
                    IM3LR_Bin = IM3_Desire_L[*_site][1]+1;
                    
//std::cout << endl;
//std::cout << "IM3_COUNT_Site = " << _site << endl;
//std::cout << "IM3_Desire_L = "<< IM3_Desire_L[*_site][1]   ; 
//std::cout << ",  Spectrum_L_IM3 = "<< IM3LL_Bin   ; 
//std::cout << ",  Spectrum_L_IM3 = "<< IM3LR_Bin   ;
//std::cout << endl;                        
                    
                    if (( IM3LL_Bin < 1) || (IM3LR_Bin > 20)) {
                    L_IM3_VoltP[*_site] = 1fV;}
                    else {
                    L_IM3_VoltP[*_site] = (IM3_Desire_L[*_site][0] + Spectrum_L_IM3[*_site][IM3LL_Bin]+ Spectrum_L_IM3[*_site][IM3LR_Bin]);   
                    }     
     TIME.Wait(1us);                
    }        // End of SiteIter          
   
   RunTime.SetActiveSites(RunSites);  
//        DSP.DeleteWaveform("MyCapture");
//        DSP.Stop(Rx_IQ);
//        RF.StopAWG(srcPin, RF_MODULATION_I_Q, RF_TONE_1);
//        RF.SetSource("BTRF" , -120dBm , MainTone_srcFreq+4.5MHz , RF_PERFORMANCE_HIGH_LINEARITY );
//        RF.Terminate("BTRF");
        FloatM L_Main_ToneVrms = MATH.Sqrt(L_Main_ToneVp/2 + 1fV);
        FloatM L_Main_PWR      = CONV.VoltsTodBm(L_Main_ToneVrms, Impd);
        
        FloatM L_Tone_Volt_RMS = MATH.Sqrt(L_Tone_VoltP/2 + 1fV);        
        FloatM L_Tone_PWR      = CONV.VoltsTodBm(L_Tone_Volt_RMS, Impd);
        
        FloatM L_IM3_Volt_RMS = MATH.Sqrt(L_IM3_VoltP/2 + 1fV);       
        FloatM L_IM3_PWR      = CONV.VoltsTodBm(L_IM3_Volt_RMS,  Impd);
        
        FloatM Rx_IM3_L = L_Tone_PWR - L_IM3_PWR;
        
        FloatM L_Rx_MidGain = L_Tone_PWR - (-39.0);  // spec 25dBc
        FloatM L_G_cal = L_Rx_MidGain - 27.0; // 27 is Ideal Gain
        FloatM L_IM3_Delta_cal = Rx_IM3_L + 2*L_G_cal; //L_side_IM3_Delta_cal spec 38dBc

//FloatS ElapsedTime10 = TIME.StopTimer();
//std::cout << " Cala_Bin_result = " << ElapsedTime10 << endl;
//    
//    std::cout << endl;
//    std::cout << "============= RX"+ReadFreqName <<"_IM3 NEW ================="<< endl;
//    std::cout << ReadFreqName+"_side_Tone = "       << L_Main_PWR << endl;
    std::cout << ReadFreqName+"_L_side_BandTone = "    << L_Tone_PWR << endl;
    std::cout << ReadFreqName+"_L_side_IM3 = "   << L_IM3_PWR  << endl;
//    std::cout << ReadFreqName+"_L_side_Rx_IM3_L = " << Rx_IM3_L << endl;
//    TIME.Wait(1us);
//
// update 
//   FloatM Rx_MidGain = L_Tone_PWR - (-39.0); // spec > 25
   std::cout<< ReadFreqName+"L_Rx_MidGain = "<< L_Rx_MidGain<< endl;



//    testResult = DLOG.Value (I_PWR,      -15,  -5, "dBm", ReadFreqName+"_I_PWR"         , "RF_Rx_IM3_fail", UTL_VOID, MinorID+11); 
//    testResult = DLOG.Value (Q_PWR,      -15,  -5, "dBm", ReadFreqName+"_Q_PWR"         , "RF_Rx_IM3_fail", UTL_VOID, MinorID+12); 
//    testResult = DLOG.Value (L_Main_PWR, -15,  -5, "dBm", ReadFreqName+"_L_Tone_PWR"    , "RF_Rx_IM3_fail", UTL_VOID, MinorID+00); 

    //testResult = DLOG.Value (L_Tone_PWR,   -13.5,   0, "dBm", ReadFreqName+Bist_Ver+"_L_Rx_Tone_Pwr" , "RF_Rx_IM3_fail", UTL_VOID, MinorID+01);
    //DLOG.AccumulateResults(local_Result, testResult);
    //testResult = DLOG.Value (Rx_IM3_L,      36,  50, "dBc", ReadFreqName+Bist_Ver+"_L_RxIMD_Delta" , "RF_Rx_IM3_fail", UTL_VOID, MinorID+02); 
    //DLOG.AccumulateResults(local_Result, testResult);

    testResult = DLOG.Value (L_Rx_MidGain,      24,  32, "dBc", ReadFreqName+Bist_Ver+"_L_Rx_MidGain" , UTL_VOID, UTL_VOID, MinorID+03); //20230222
    DLOG.AccumulateResults(local_Result, testResult);
    testResult = DLOG.Value (L_IM3_Delta_cal,   38,  50, "dBc", ReadFreqName+Bist_Ver+"_L_RxIM3_Delta_cal" , UTL_VOID, UTL_VOID, MinorID+04); //20230222
    DLOG.AccumulateResults(local_Result, testResult);

    
    	return (local_Result);                  
}

//
TMResultM RF_RX_IM3_Measure_SERIAL(const FloatS MainTone_srcFreq, FloatS ToneLevel, IntS MinorID, StringS PatternID)
{  

    TMResultM testResult = TM_NOTEST, local_Result ;
    TMResultM IM3pat_testResult = TM_NOTEST ;
    
    FloatS ToneSpacing = 3MHz;     
    ReadFreq(ReadFreqName, MainTone_srcFreq);

    FloatM2D ComplexCapture(RX_N*2), ComplexCaptureSim(RX_N*2);
    FloatM1D ComplexCapture_I(RX_N), ComplexCapture_Q(RX_N);
    FloatM1D ComplexCapture_merge;
    FloatM1D ComplexSpectrumVp, ComplexSpectrumRMS; 
        
    FloatM1D IQ_dBm(2048, -99.0);

    FloatM RBW = RX_Fs / RX_N;  //Target 4K
    FloatM Bin_1M = 1MHz / RBW;
    FloatM  L_Tone_VoltP, L_IM3_VoltP, L_Main_ToneVp, I_PWR, Q_PWR;
    

//    CBIT.Close("K3");
//    CBIT.Close("K28");

//    testResult = XdcFuncTest(testResult, MinorID-100, "RF_BIST_DFT", "RF_BIST_DFT_fail", "RF_BIST_DFT_ID0", "AllPins_Pattern" ); 
//    TIME.Wait(10ms);   

//    DIGITAL.ExecutePattern(PatternID);

//    testResult = XdcFuncTest(IM3pat_testResult, MinorID+00, ReadFreqName+Bist_Ver+"IM3_PAT", "RF_Rx_IM3_PAT_fail", PatternID, "AllPins_Pattern" );    
//    TIME.Wait(5ms);

    StringS waveform = "AWG Signal";
    FloatS AwgFs;
    FloatS Max_AwgFs = 60MHz;
    FloatS AwgFF = 1KHz;        
    RfPowerSpectrum spec;
    BoolS splitMode = false;

//Define Two Tone Parameter
    FloatS OffsetFreq =  0.0MHz;   //First Tone at XMHz,Second Tone at XXMHz
    FloatS AwgFilter = 50kHz;
    FloatM1D ComplexArr;
    FloatM par;

    TIME.StartTimer();

//Generate 2 Tone using VSA library
    BasicRfWaveform TwoToneWave = VSA.Math.TwoTone(ToneSpacing,OffsetFreq,Max_AwgFs); 
    FloatM1D I_Array_VSA = TwoToneWave.iArray;
    FloatM1D Q_Array_VSA = TwoToneWave.qArray;
    AwgFs= TwoToneWave.bbSampleRate;
//    VSAPlotter::PLOT.BasicLine("ITime","Wave","I",I_Array_VSA) ;
//    VSAPlotter::PLOT.BasicLine("QTime","Wave","Q",Q_Array_VSA) ; 
    VSA.Math.InterleaveComplex(I_Array_VSA,Q_Array_VSA,ComplexArr);
    spec.CreateFromCplxTime(ComplexArr,AwgFs,AwgFF,0Hz) ;

    FloatM srcFiltFreq_M = 100MHz;  
    FloatM Max_AwgFs_M = 60MHz;

 
        StringS IDString = "TwoToneSource";

        RF.DeleteSetup      ( IDString );
        RF.DefineSetup      ( IDString , srcPin , RF_SOURCE_MOD,RF_GEN_SPLIT);
        RF.ResolveSetup     ( IDString );
        RF.SelectSetup      ( IDString );     
        
        RF.DefineWaveform   ( IDString , srcPin , Max_AwgFs_M , srcFiltFreq_M , RF_SAMPLING_AUTO , RF_MODULATION_I_Q , RF_TONE_1 );
        RF.LoadWaveform     ( IDString , I_Array_VSA ,Q_Array_VSA ,RF_TONE_1 );
        RF.ConnectAWG       ( srcPin , RF_MODULATION_I_Q, RF_TONE_1 );
        RF.SelectWaveform   ( IDString , srcPin ,RF_MODULATION_I_Q,RF_TONE_1);  // aryOffset , blockSz , RF_MODULATION_I_Q, RF_TONE_1);

    Sites RunSites = ActiveSites; //keeps Running sites
    for (SiteIter siteIter = ActiveSites.Begin(); !siteIter.End(); ++siteIter) {   

     std::cout<< endl;
     IntS siteNo= siteIter.GetValue();
     std::cout<<"Site= "<< siteNo<< endl;

      RunTime.SetActiveSites(siteIter.GetValue()); 

    CBIT.Close("K3");
    CBIT.Close("K28");
    testResult = XdcFuncTest(IM3pat_testResult, MinorID+00, ReadFreqName+Bist_Ver+"IM3_PAT", "RF_Rx_IM3_PAT_fail", PatternID, "AllPins_Pattern" );    
    TIME.Wait(5ms);


        RF.EnableModulation ( srcPin   );
        RF.Prepare();
        TIME.Wait(3ms);
        
        RF.SetSource        ( srcPin, ToneLevel+6.0206dB+TTonPWR_Loss, MainTone_srcFreq+4.5MHz, RF_PERFORMANCE_HIGH_LINEARITY); //    ToneLevel = Setting + 6.0206dB;  // + peak to rms of waveform; // 2402MHz+4.5MHz for TwoTone 2405MHz & 2408MHz tonespacing
        TIME.Wait(0ms);
         
        RF.StartAWG(srcPin, RF_MODULATION_I_Q, RF_TONE_1);
        TIME.Wait(1ms);

//        RF.SetSource("BTRF" , -120dBm , MainTone_srcFreq+4.5MHz , RF_PERFORMANCE_HIGH_LINEARITY );
//        RF.Terminate("BTRF");

// ===== Send and Measure Rx_IM3 PWR ===== //

//    Sites RunSites = ActiveSites; //keeps Running sites
//    for (SiteIter siteIter = ActiveSites.Begin(); !siteIter.End(); ++siteIter) {   
//        RunTime.SetActiveSites(siteIter.GetValue()); 
        
        DSP.Initialize(Rx_IQ);
        DSP.SetConfiguration(Rx_IQ, DSP_CONFIG_DIRECT);
        DSP.Connect(Rx_IQ,DSP_TO_DUT,DSP_MODE_SE);
        DSP.SetOffsetMode (Rx_IQ, DSP_OFFSET_DUT);
        DSP.DefineWaveform("MyCapture1", Rx_IQ);
        DSP.SetSampleRate("MyCapture1", RX_Fs);
        DSP.SetFilter("MyCapture1", DSP_FILTER_LOW_PASS, 22MHz);
        DSP.SetRange("MyCapture1", 1V);
        DSP.SetPoints ("MyCapture1", RX_Points);
//        DIGITAL.DisconnectSyncRefs();
//        DSP.SetTimeout(2.0s);

        DSP.Select("MyCapture1", Rx_IQ);
        DSP.Prepare();
        TIME.Wait(10ms);    
        DSP.Start(Rx_IQ);
        TIME.Wait(10ms);
        BoolM1D DigitizerTimeout = DSP.Wait(Rx_IQ);

        
        if (DigitizerTimeout.AllNotEqual(true)) {
            BoolM1D OverrangeFlag = DSP.ReadOverrangeFlag(Rx_IQ);
            if (OverrangeFlag.AllNotEqual(true)) {
                DSP.ReadWaveform("MyCapture1",Rx_IQ, ComplexCapture, ComplexCaptureSim, DSP_DATA_TYPE_ALL);
                TIME.Wait(1us);
            } else {
                 //handle over-range
            }
        } else {
              // handle timeout error
        }
   }  // End of siteItator


    RunTime.SetActiveSites(RunSites);
 //       DSP.DeleteWaveform("TwoToneSource");
        DSP.Stop(Rx_IQ);
        RF.StopAWG(srcPin, RF_MODULATION_I_Q, RF_TONE_1);
        RF.SetSource(srcPin , -120dBm , MainTone_srcFreq+4.5MHz , RF_PERFORMANCE_HIGH_LINEARITY );
        RF.Terminate(srcPin);
    
                for (SiteIter _site = ActiveSites.Begin(); !_site.End(); ++_site)
                 {
                    for (int x =0; x< RX_N; x++)
                     {
                      ComplexCapture_I [*_site][x] = ComplexCapture[*_site][0][x];
                      ComplexCapture_Q [*_site][x] = ComplexCapture[*_site][1][x];                     
                     }

                 std::cout << "IQ_Site = " << _site << endl;
                 VSA.Math.InterleaveComplex(ComplexCapture_Q,ComplexCapture_I,ComplexCapture_merge);
                 ComplexSpectrumVp = MATH.ComplexPowerFFT(ComplexCapture_merge); //Time Domain to Freq 
                 ComplexSpectrumRMS = MATH.Sqrt(ComplexSpectrumVp/2 + 1fV); //Vpp to Vrms Volt
                 IQ_dBm = CONV.VoltsTodBm(ComplexSpectrumRMS, Impd);
                 TIME.Wait(1us);

                 FloatM1D ComplexSpectrumVp_I = MATH.ComplexPowerFFT(ComplexCapture_I); //Time Domain to Freq 
                 FloatM1D ComplexSpectrumRMS_I = MATH.Sqrt(ComplexSpectrumVp_I/2 + 1fV); //Vpp to Vrms Volt
                 FloatM1D I_dBm = CONV.VoltsTodBm(ComplexSpectrumRMS_I, Impd);
                 TIME.Wait(1us);                 

                 FloatM1D ComplexSpectrumVp_Q = MATH.ComplexPowerFFT(ComplexCapture_Q); //Time Domain to Freq 
                 FloatM1D ComplexSpectrumRMS_Q = MATH.Sqrt(ComplexSpectrumVp_Q/2 + 1fV); //Vpp to Vrms Volt
                 FloatM1D Q_dBm = CONV.VoltsTodBm(ComplexSpectrumRMS_Q, Impd);
                 TIME.Wait(1us); 

    FloatM1D Spectrum_I = I_dBm.Slice(3090,3110);
    FloatM1D Tone_Desire_I  = MATH.Xtrm(Spectrum_I);
             I_PWR = Tone_Desire_I[0];
    FloatM1D Spectrum_Q = Q_dBm.Slice(3090,3110);
    FloatM1D Tone_Desire_Q  = MATH.Xtrm(Spectrum_Q);
             Q_PWR = Tone_Desire_Q[0];

//    std::cout << ReadFreqName+"_I_TonePwr = "<< I_PWR    << endl;  
//    std::cout << ReadFreqName+"_Q_TonePwr = "<< Q_PWR    << endl;  

                //RBW 8K, 1MHz_Bin =125 ; 4MHz_Bin = 500  ; Diff = 375.
                //RBW 4K, 1MHz_Bin =250 ; 4MHz_Bin = 1000 ; Diff = 750.
                    FloatM  L_IM3 = Bin_1M;                 
                    IntM    L_Tone    = L_IM3 + 375*2;
                    IntM    L_STp     = L_Tone - 10 , L_SPp     = L_Tone + 10;
                    IntM    L_IM3_STp = L_IM3 - 10  , L_IM3_SPp = L_IM3+10;
                    IntS ToneLL_Bin = 0, ToneLR_Bin = 0;
                    IntS IM3LL_Bin  = 0, IM3LR_Bin  = 0;
                    
                    FloatM1D Spectrum_L(21, -99), Spectrum_L_IM3(21, -99);
                             Spectrum_L = ComplexSpectrumVp.Slice(L_STp,L_SPp);
                    FloatM1D Tone_Desire_L  = MATH.Xtrm(Spectrum_L);

                    ToneLL_Bin = Tone_Desire_L[*_site][1]-1;
                    ToneLR_Bin = Tone_Desire_L[*_site][1]+1;

                    
//std::cout << endl;
//std::cout << "IM3_COUNT_Site = " << _site << endl;
//std::cout << "IM3_Desire_L = "<< IM3_Desire_L[*_site][1]   ; 
//std::cout << ",  Spectrum_L_IM3 = "<< IM3LL_Bin   ; 
//std::cout << ",  Spectrum_L_IM3 = "<< IM3LR_Bin   ;
//std::cout << endl;                        
                    
                    if (( ToneLL_Bin < 1) ||( ToneLR_Bin > 20 )) {
                    L_Tone_VoltP[*_site] = 1fV;}
                    else {
                    L_Tone_VoltP = (Tone_Desire_L[0] + Spectrum_L[ToneLL_Bin]+ Spectrum_L [ToneLR_Bin]);
                    }
                    L_Main_ToneVp = Tone_Desire_L[0];

                    Spectrum_L_IM3 = ComplexSpectrumVp.Slice(L_IM3_STp,L_IM3_SPp);
                    FloatM1D IM3_Desire_L  = MATH.Xtrm(Spectrum_L_IM3);
                    IM3LL_Bin = IM3_Desire_L[*_site][1]-1;
                    IM3LR_Bin = IM3_Desire_L[*_site][1]+1;
                    
//std::cout << endl;
//std::cout << "IM3_COUNT_Site = " << _site << endl;
//std::cout << "IM3_Desire_L = "<< IM3_Desire_L[*_site][1]   ; 
//std::cout << ",  Spectrum_L_IM3 = "<< IM3LL_Bin   ; 
//std::cout << ",  Spectrum_L_IM3 = "<< IM3LR_Bin   ;
//std::cout << endl;                        
                    
                    if (( IM3LL_Bin < 1) || (IM3LR_Bin > 20)) {
                    L_IM3_VoltP[*_site] = 1fV;}
                    else {
                    L_IM3_VoltP = (IM3_Desire_L[0] + Spectrum_L_IM3[IM3LL_Bin]+ Spectrum_L_IM3[IM3LR_Bin]);   
                    }                 
                 }                 
  
//        DSP.DeleteWaveform("MyCapture");
//        DSP.Stop(Rx_IQ);
//        RF.StopAWG(srcPin, RF_MODULATION_I_Q, RF_TONE_1);
//        RF.SetSource("BTRF" , -120dBm , MainTone_srcFreq+4.5MHz , RF_PERFORMANCE_HIGH_LINEARITY );
//        RF.Terminate("BTRF");
        FloatM L_Main_ToneVrms = MATH.Sqrt(L_Main_ToneVp/2 + 1fV);
        FloatM L_Main_PWR      = CONV.VoltsTodBm(L_Main_ToneVrms, Impd);
        FloatM L_Tone_Volt_RMS = MATH.Sqrt(L_Tone_VoltP/2 + 1fV);        
        FloatM L_Tone_PWR      = CONV.VoltsTodBm(L_Tone_Volt_RMS, Impd);
        FloatM L_IM3_Volt_RMS = MATH.Sqrt(L_IM3_VoltP/2 + 1fV);       
        FloatM L_IM3_PWR      = CONV.VoltsTodBm(L_IM3_Volt_RMS,  Impd);
        FloatM Rx_IM3_L = L_Tone_PWR - L_IM3_PWR;
        
        FloatM L_Rx_MidGain = L_Tone_PWR - (-39.0);  // spec 25dBc
        FloatM L_G_cal = L_Rx_MidGain - 27.0; // 27 is Ideal Gain
        FloatM L_IM3_Delta_cal = Rx_IM3_L + 2*L_G_cal; //L_side_IM3_Delta_cal spec 38dBc

//FloatS ElapsedTime10 = TIME.StopTimer();
//std::cout << " Cala_Bin_result = " << ElapsedTime10 << endl;
//    
//    std::cout << endl;
//    std::cout << "============= RX"+ReadFreqName <<"_IM3 NEW ================="<< endl;
//    std::cout << ReadFreqName+"_side_Tone = "       << L_Main_PWR << endl;
    std::cout << ReadFreqName+"_L_side_BandTone = "    << L_Tone_PWR << endl;
    std::cout << ReadFreqName+"_L_side_IM3 = "   << L_IM3_PWR  << endl;
//    std::cout << ReadFreqName+"_L_side_Rx_IM3_L = " << Rx_IM3_L << endl;
//    TIME.Wait(1us);
//
// update 
//   FloatM Rx_MidGain = L_Tone_PWR - (-39.0); // spec > 25
   std::cout<< ReadFreqName+"L_Rx_MidGain = "<< L_Rx_MidGain<< endl;



//    testResult = DLOG.Value (I_PWR,      -15,  -5, "dBm", ReadFreqName+"_I_PWR"         , "RF_Rx_IM3_fail", UTL_VOID, MinorID+11); 
//    testResult = DLOG.Value (Q_PWR,      -15,  -5, "dBm", ReadFreqName+"_Q_PWR"         , "RF_Rx_IM3_fail", UTL_VOID, MinorID+12); 
//    testResult = DLOG.Value (L_Main_PWR, -15,  -5, "dBm", ReadFreqName+"_L_Tone_PWR"    , "RF_Rx_IM3_fail", UTL_VOID, MinorID+00); 

    //testResult = DLOG.Value (L_Tone_PWR,   -13.5,   0, "dBm", ReadFreqName+Bist_Ver+"_L_Rx_Tone_Pwr" , "RF_Rx_IM3_fail", UTL_VOID, MinorID+01);
    //DLOG.AccumulateResults(local_Result, testResult);
    //testResult = DLOG.Value (Rx_IM3_L,      36,  50, "dBc", ReadFreqName+Bist_Ver+"_L_RxIMD_Delta" , "RF_Rx_IM3_fail", UTL_VOID, MinorID+02); 
    //DLOG.AccumulateResults(local_Result, testResult);

    testResult = DLOG.Value (L_Rx_MidGain,      24,  32, "dBc", ReadFreqName+Bist_Ver+"_L_Rx_MidGain" , UTL_VOID, UTL_VOID, MinorID+03); //20230222
    DLOG.AccumulateResults(local_Result, testResult);
    testResult = DLOG.Value (L_IM3_Delta_cal,   38,  50, "dBc", ReadFreqName+Bist_Ver+"_L_RxIM3_Delta_cal" , UTL_VOID, UTL_VOID, MinorID+04); //20230222
    DLOG.AccumulateResults(local_Result, testResult);

    
    	return (local_Result);                  
}

TMResultM RF_RX_ATP_SNR_Measure(const FloatM Tone_srcFreq, FloatS ToneLevel, IntS MinorID, StringS PatternID)
{  
    TMResultM testResult, local_Result     = TM_NOTEST ;
    TMResultM testResult_SNR = TM_NOTEST ;    
    ReadFreq(ReadFreqName, Tone_srcFreq);
    
    CBIT.Close("K3");
    CBIT.Close("K28");
    
//    DIGITAL.ExecutePattern(PatternID);
    testResult = XdcFuncTest(testResult_SNR, MinorID+00, ReadFreqName+Bist_Ver+"_Rx_ATP_SNR_Pat", "RF_Rx_ATP_SNR_PAT_fail", PatternID, "AllPins_Pattern" );  
    TIME.Wait(5ms);    

//    RxSNR_IQ    = "DIG_I+DIG_Q";  
//    RX_N        = 4096*8;
//    RX_Fs       = 32.768MHz;
//    UnsignedM RX_Points = 4096*8;

    FloatM BinRBW = RX_Fs/RX_N; //4K
    FloatM BinL = 1.0MHz/BinRBW;
    IntM    STp = BinL - (1.0e+6/BinRBW/2); //500KHz
    IntM    SPp = BinL + (1.0e+6/BinRBW/2); //1500KHz
                    
//    FloatM Impd = 50Ohm;
    FloatM2D    ComplexCapture_NoRF(RX_N*2);
    FloatM2D    ComplexCapture(RX_N*2);
    FloatM2D    ComplexCaptureSim(RX_N*2,0);
    FloatM1D    ComplexCapture_I_NOPWR(RX_N);
    FloatM1D    ComplexCapture_Q_NOPWR(RX_N);
    FloatM1D    ComplexCapture_I(RX_N);
    FloatM1D    ComplexCapture_Q(RX_N);
    FloatM      RxSNR_IQ_dBm_NoPwr;
    FloatM      RxSNR_IQ_dBm_Pwr;
    FloatM      RxSNR_IQ_dBm_Pwr_NF;
    
    BoolM1D     DigitizerTimeout = DSP.Wait(Rx_IQ);

//=========== Measures Noise Floor ===========
    Sites SavedSites = ActiveSites; //keeps Running sites
    Sites GP1_Sites = NO_SITES ;
    Sites GP2_Sites = NO_SITES ;
    for (SiteIter siteIter = ActiveSites.Begin(); !siteIter.End(); ++siteIter) {   
  
    if (IntS(siteIter.GetValue()) == 1 || IntS(siteIter.GetValue()) ==3 )
    {GP1_Sites=GP1_Sites+siteIter.GetValue();}
    else if (IntS(siteIter.GetValue()) == 2 || IntS(siteIter.GetValue()) == 4 )
    {GP2_Sites=GP2_Sites+siteIter.GetValue();} 
    }
    
    if(GP1_Sites!=NO_SITES) {
    RunTime.SetActiveSites(GP1_Sites);
    
    DSP.Initialize(Rx_IQ);
    DSP.SetConfiguration(Rx_IQ, DSP_CONFIG_DIRECT);
    DSP.Connect(Rx_IQ,DSP_TO_DUT,DSP_MODE_SE);
    DSP.SetOffsetMode (Rx_IQ, DSP_OFFSET_DUT);
    DSP.DefineWaveform("MyCapture1", Rx_IQ);
    DSP.SetSampleRate("MyCapture1", RX_Fs);
    DSP.SetFilter("MyCapture1", DSP_FILTER_LOW_PASS, 5MHz);
    DSP.SetRange("MyCapture1", 2V);
    DSP.SetPoints ("MyCapture1", RX_Points);
//    DIGITAL.DisconnectSyncRefs();
//    DSP.SetTimeout(2.0s);
        
    DSP.Select("MyCapture1", Rx_IQ);
    DSP.Prepare();
    TIME.Wait(10ms);    
    DSP.Start(Rx_IQ);
    TIME.Wait(10ms);    
//    BoolM1D DigitizerTimeout = DSP.Wait(RxSNR_IQ);

        if (DigitizerTimeout.AllNotEqual(true)) {
            BoolM1D OverrangeFlag = DSP.ReadOverrangeFlag(Rx_IQ);
            if (OverrangeFlag.AllNotEqual(true)) {
                DSP.ReadWaveform("MyCapture1",Rx_IQ, ComplexCapture_NoRF, ComplexCaptureSim, DSP_DATA_TYPE_ALL);
                TIME.Wait(1us);
            } else {
                 //handle over-range
            }
        } else {
              // handle timeout error
        }
    }
    
    if(GP2_Sites!=NO_SITES) {
    RunTime.SetActiveSites(GP2_Sites); 
    
    DSP.Initialize(Rx_IQ);
    DSP.SetConfiguration(Rx_IQ, DSP_CONFIG_DIRECT);
    DSP.Connect(Rx_IQ,DSP_TO_DUT,DSP_MODE_SE);
    DSP.SetOffsetMode (Rx_IQ, DSP_OFFSET_DUT);
    DSP.DefineWaveform("MyCapture1", Rx_IQ);
    DSP.SetSampleRate("MyCapture1", RX_Fs);
    DSP.SetFilter("MyCapture1", DSP_FILTER_LOW_PASS, 5MHz);
    DSP.SetRange("MyCapture1", 2V);
    DSP.SetPoints ("MyCapture1", RX_Points);
//    DIGITAL.DisconnectSyncRefs();
//    DSP.SetTimeout(2.0s);
        
    DSP.Select("MyCapture1", Rx_IQ);
    DSP.Prepare();
    TIME.Wait(10ms);    
    DSP.Start(Rx_IQ);
    TIME.Wait(10ms);    
//    BoolM1D DigitizerTimeout = DSP.Wait(RxSNR_IQ);

        if (DigitizerTimeout.AllNotEqual(true)) {
            BoolM1D OverrangeFlag = DSP.ReadOverrangeFlag(Rx_IQ);
            if (OverrangeFlag.AllNotEqual(true)) {
                DSP.ReadWaveform("MyCapture1",Rx_IQ, ComplexCapture_NoRF, ComplexCaptureSim, DSP_DATA_TYPE_ALL);
                TIME.Wait(1us);
            } else {
                 //handle over-range
            }
        } else {
              // handle timeout error
        }
    }

    RunTime.SetActiveSites(SavedSites);
        DSP.DeleteWaveform("MyCapture1");
        DSP.Stop(Rx_IQ);
    

//        if (DigitizerTimeout.AllNotEqual(true)) {
//            BoolM1D OverrangeFlag = DSP.ReadOverrangeFlag(Rx_IQ);
//            if (OverrangeFlag.AllNotEqual(true)) {
//                DSP.ReadWaveform("MyCapture1",Rx_IQ, ComplexCapture_NoRF, ComplexCaptureSim, DSP_DATA_TYPE_ALL);
//                TIME.Wait(1us);

                for (SiteIter s = ActiveSites.Begin(); !s.End(); ++s)
                 {
                    for (int x =0; x< RX_N; x++)
                     {
                      ComplexCapture_I_NOPWR [*s][x] = ComplexCapture_NoRF[*s][0][x];
                      ComplexCapture_Q_NOPWR [*s][x] = ComplexCapture_NoRF[*s][1][x];                     
                     }
                 }

    FloatM1D ComplexSpectrum((RX_N/2)+1);
    FloatM1D ComplexCapture_merge_NoPWR;
    
        VSA.Math.InterleaveComplex(ComplexCapture_Q_NOPWR,ComplexCapture_I_NOPWR,ComplexCapture_merge_NoPWR);
               
                ComplexSpectrum = MATH.ComplexPowerFFT(ComplexCapture_merge_NoPWR);

/* For checking Specturm only
                FloatM1D Spectrum_NoPWR_K = ComplexSpectrum.Slice(2,8190);
                FloatM1D Freq_NoPWR_RMS_K = MATH.Sqrt(Spectrum_NoPWR_K/2 + 1fV);
                FloatM1D RxSNR_IQ_dBm_NoPwr_K = CONV.VoltsTodBm(Freq_NoPWR_RMS_K, Impd);              */
                
                FloatM1D Spectrum_NoPWR = ComplexSpectrum.Slice(STp,SPp);
                FloatM Freq_NoPWR = MATH.Sum(Spectrum_NoPWR);
                FloatM Freq_NoPWR_RMS = MATH.Sqrt(Freq_NoPWR/2 + 1fV);
                RxSNR_IQ_dBm_NoPwr = CONV.VoltsTodBm(Freq_NoPWR_RMS, Impd);
                TIME.Wait(1us);



//=========== Measures Noise Floor Done ======

    BoolS splitMode    = false;
    StringS my_setup_1 ="RF_source_cw";
    FloatM Freq_Offset = 0.25MHz;
    
    RF.DefineSetup (my_setup_1, srcPin, RF_SOURCE_CW, RF_GEN_SPLIT);
    RF.ResolveSetup(my_setup_1);
    RF.SelectSetup (my_setup_1);
    RF.SetTimeout(0.5s);
    RF.SetSource(srcPin, ToneLevel+CWTonPWR_Loss, Tone_srcFreq+Freq_Offset, RF_PERFORMANCE_HIGH_LINEARITY); 
    TIME.Wait(2ms); //20ms
    RF.Prepare();
    TIME.Wait(1ms);
    
//    RF.SetSource(srcPin , -120dBm , Tone_srcFreq+Freq_Offset, RF_PERFORMANCE_HIGH_LINEARITY );
//    RF.Terminate(srcPin);
//    TIME.Wait(1ms);

    if(GP1_Sites!=NO_SITES) {
    RunTime.SetActiveSites(GP1_Sites);
    
    DSP.Initialize(Rx_IQ);
    DSP.SetConfiguration(Rx_IQ, DSP_CONFIG_DIRECT);
    DSP.Connect(Rx_IQ,DSP_TO_DUT,DSP_MODE_SE);
    DSP.SetOffsetMode (Rx_IQ, DSP_OFFSET_DUT);
    DSP.DefineWaveform("MyCaptureSNR", Rx_IQ);
    DSP.SetSampleRate("MyCaptureSNR", RX_Fs);
    DSP.SetFilter("MyCaptureSNR", DSP_FILTER_LOW_PASS, 1MHz);
    DSP.SetRange("MyCaptureSNR", 2V);
    DSP.SetPoints ("MyCaptureSNR", RX_Points);
//        DIGITAL.DisconnectSyncRefs();
//        DSP.SetTimeout(2.0s);
     
    DSP.Select("MyCaptureSNR", Rx_IQ);
    DSP.Prepare();
    TIME.Wait(10ms);
    DSP.Start(Rx_IQ);
    TIME.Wait(10ms);
    
        if (DigitizerTimeout.AllNotEqual(true)) {
            BoolM1D OverrangeFlag = DSP.ReadOverrangeFlag(Rx_IQ);
            if (OverrangeFlag.AllNotEqual(true)) {
                DSP.ReadWaveform("MyCaptureSNR",Rx_IQ, ComplexCapture, ComplexCaptureSim, DSP_DATA_TYPE_ALL);
                TIME.Wait(1us);
            } else {
                 //handle over-range
            }
        } else {
              // handle timeout error
        }
    }        

    if(GP2_Sites!=NO_SITES) {
    RunTime.SetActiveSites(GP2_Sites);
    
    DSP.Initialize(Rx_IQ);
    DSP.SetConfiguration(Rx_IQ, DSP_CONFIG_DIRECT);
    DSP.Connect(Rx_IQ,DSP_TO_DUT,DSP_MODE_SE);
    DSP.SetOffsetMode (Rx_IQ, DSP_OFFSET_DUT);
    DSP.DefineWaveform("MyCaptureSNR2", Rx_IQ);
    DSP.SetSampleRate("MyCaptureSNR2", RX_Fs);
    DSP.SetFilter("MyCaptureSNR2", DSP_FILTER_LOW_PASS, 1MHz);
    DSP.SetRange("MyCaptureSNR2", 2V);
    DSP.SetPoints ("MyCaptureSNR2", RX_Points);
//        DIGITAL.DisconnectSyncRefs();
//        DSP.SetTimeout(2.0s);
     
    DSP.Select("MyCaptureSNR2", Rx_IQ);
    DSP.Prepare();
    TIME.Wait(10ms);
    DSP.Start(Rx_IQ);
    TIME.Wait(10ms);
    
        if (DigitizerTimeout.AllNotEqual(true)) {
            BoolM1D OverrangeFlag = DSP.ReadOverrangeFlag(Rx_IQ);
            if (OverrangeFlag.AllNotEqual(true)) {
                DSP.ReadWaveform("MyCaptureSNR2",Rx_IQ, ComplexCapture, ComplexCaptureSim, DSP_DATA_TYPE_ALL);
                TIME.Wait(1us);
            } else {
                 //handle over-range
            }
        } else {
              // handle timeout error
        }
    }  

    RunTime.SetActiveSites(SavedSites);
    
//    DSP.DeleteAllWaveforms();
    DSP.Stop(Rx_IQ);
    RF.SetSource("BTRF" , -120dBm , Tone_srcFreq+Freq_Offset , RF_PERFORMANCE_HIGH_LINEARITY );
//    RF.Terminate("BTRF"); 
        
                for (SiteIter s = ActiveSites.Begin(); !s.End(); ++s)
                 {
                    for (int x =0; x< RX_N; x++)
                     {
                      ComplexCapture_I [*s][x] = ComplexCapture[*s][0][x];
                      ComplexCapture_Q [*s][x] = ComplexCapture[*s][1][x];                     
                     }
                 }
               
//    FloatM1D ComplexSpectrum((RX_N/2)+1);
    FloatM1D ComplexCapture_merge;

        VSA.Math.InterleaveComplex(ComplexCapture_Q,ComplexCapture_I,ComplexCapture_merge);
                ComplexSpectrum = MATH.ComplexPowerFFT(ComplexCapture_merge);
/* For Checking Spectrum only    */
                FloatM1D Spectrum_PWR_ALL = ComplexSpectrum.Slice(3,8190);
                FloatM1D Freq_PWR_RMS_ALL = MATH.Sqrt(Spectrum_PWR_ALL/2 + 1fV);
                FloatM1D RxSNR_ALL_dBm_Pwr = CONV.VoltsTodBm(Freq_PWR_RMS_ALL, Impd);

                FloatM1D Spectrum_PWR = ComplexSpectrum.Slice(STp,SPp);
                FloatM Freq_PWR = MATH.Sum(Spectrum_PWR);
                FloatM Freq_PWR_RMS = MATH.Sqrt(Freq_PWR/2 + 1fV);
                RxSNR_IQ_dBm_Pwr = CONV.VoltsTodBm(Freq_PWR_RMS, Impd);
              
                FloatM1D ComplexSpectrum_PFFTI = MATH.PowerFFT(ComplexCapture_I);
                FloatM1D Spectrum_PWR_I = ComplexSpectrum_PFFTI.Slice(STp,SPp);
                FloatM   Sum_PWR_I = MATH.Sum(Spectrum_PWR_I);                
                FloatM   Freq_PWR_RMS_I = MATH.Sqrt(Sum_PWR_I/2 + 1fV);
                FloatM   RxSNR_I_dBm_Pwr = CONV.VoltsTodBm(Freq_PWR_RMS_I, Impd);

                FloatM1D ComplexSpectrum_PFFTQ = MATH.PowerFFT(ComplexCapture_Q);
                FloatM1D Spectrum_PWR_Q = ComplexSpectrum_PFFTQ.Slice(STp,SPp);
                FloatM   Sum_PWR_Q = MATH.Sum(Spectrum_PWR_Q);                
                FloatM   Freq_PWR_RMS_Q = MATH.Sqrt(Sum_PWR_Q/2 + 1fV);
                FloatM   RxSNR_Q_dBm_Pwr = CONV.VoltsTodBm(Freq_PWR_RMS_Q, Impd);

    FloatM Rx_ATP_SNR     = RxSNR_IQ_dBm_Pwr - RxSNR_IQ_dBm_NoPwr;
 
    
//    std::cout << endl;
    std::cout << ReadFreqName+"_RxSNR_NoPwr_BAND1M = "      << RxSNR_IQ_dBm_NoPwr   << endl;    
    std::cout << ReadFreqName+"_RxSNR_m70dBmPwr_BAND1M = "  << RxSNR_IQ_dBm_Pwr     << endl;    
//    std::cout << ReadFreqName+"_Rx_ATP_SNR = "              << Rx_ATP_SNR           << endl;   
//    std::cout << ReadFreqName+"_Rx_ATP_PWR_SNR = "          << Rx_ATP_PWR_SNR       << endl;
    
//    testResult = DLOG.Value (RxSNR_I_dBm_Pwr,   -30, -15, "dBm", ReadFreqName+"_Rx_SNR_I_Bandpwr",     "RF_Rx_ATP_SNR_fail", UTL_VOID, MinorID+11); 
//    testResult = DLOG.Value (RxSNR_Q_dBm_Pwr,   -30, -15, "dBm", ReadFreqName+"_Rx_SNR_Q_Bandpwr",        "RF_Rx_ATP_SNR_fail", UTL_VOID, MinorID+12);
    testResult = DLOG.Value (RxSNR_IQ_dBm_Pwr,  -26.0, -10, "dBm",  ReadFreqName+Bist_Ver+"_Rx_ATP_SNR_BandPwr",     UTL_VOID, UTL_VOID, MinorID+13); //20230222
    DLOG.AccumulateResults(local_Result, testResult);
//    testResult = DLOG.Value (RxSNR_IQ_dBm_NoPwr,-70, -50, "dBm", ReadFreqName+"_Rx_ATP_SNR_BandNoise",     "RF_Rx_ATP_SNR_fail", UTL_VOID, MinorID+14); 

    
    testResult = DLOG.Value (Rx_ATP_SNR,     35, 50, "dB", ReadFreqName+Bist_Ver+"_Rx_ATP_SNR",     UTL_VOID, UTL_VOID, MinorID+01); 
    DLOG.AccumulateResults(local_Result, testResult); 
    return (local_Result);                    
}


TMResultM RF_RX_24MHz_SPUR_Measure(const FloatM Tone_srcFreq, FloatS ToneLevel_NF, FloatS ToneLevel, IntS MinorID, StringS PatternID)
{  
    TMResultM testResult, local_Result     = TM_NOTEST ;
    TMResultM testResult_SNR = TM_NOTEST ;    
    ReadFreq(ReadFreqName, Tone_srcFreq);
    
    CBIT.Close("K3");
    CBIT.Close("K28");
    
//    DIGITAL.ExecutePattern(PatternID);
    testResult = XdcFuncTest(testResult_SNR, MinorID+00, ReadFreqName+Bist_Ver+"_Rx_24MHzSpur_SNR_Pat", "RF_Rx_24MHzSpur_PAT_fail", PatternID, "AllPins_Pattern" );  
    TIME.Wait(5ms);    


    BoolS splitMode    = false;
    StringS my_setup_1 ="RF_source_cw";
    FloatM Freq_Offset_24M = 24MHz;
    
    RF.DefineSetup (my_setup_1, srcPin, RF_SOURCE_CW, RF_GEN_SPLIT);
    RF.ResolveSetup(my_setup_1);
    RF.SelectSetup (my_setup_1);
    RF.SetTimeout(0.5s);
    RF.SetSource(srcPin, ToneLevel_NF+CWTonPWR_Loss, Tone_srcFreq+Freq_Offset_24M, RF_PERFORMANCE_HIGH_LINEARITY); 
    TIME.Wait(2ms); //20ms
    RF.Prepare();
    TIME.Wait(1ms);

//    RF.SetSource(srcPin , -120dBm , Tone_srcFreq, RF_PERFORMANCE_HIGH_LINEARITY );
//    RF.Terminate(srcPin);
//    TIME.Wait(1ms);


//    RxSNR_IQ    = "DIG_I+DIG_Q";  
//    RX_N        = 4096*10;
//    RX_Fs       = 32.768MHz*2;
//    UnsignedM RX_Points = 4096*10;

    FloatM BinRBW = RX_Fs/RX_N; //4K
    FloatM BinL = 1.0MHz/BinRBW;
    IntM    STp = BinL - (1.0e+6/BinRBW/2); //500KHz
    IntM    SPp = BinL + (1.0e+6/BinRBW/2); //1500KHz
                    
//    FloatM Impd = 50Ohm;
    FloatM2D    ComplexCapture_NoRF(RX_N*2);
    FloatM2D    ComplexCapture(RX_N*2);
    FloatM2D    ComplexCaptureSim(RX_N*2,0);
    FloatM1D    ComplexCapture_I_NOPWR(RX_N);
    FloatM1D    ComplexCapture_Q_NOPWR(RX_N);
    FloatM1D    ComplexCapture_I(RX_N);
    FloatM1D    ComplexCapture_Q(RX_N);
    FloatM      RxSNR_IQ_dBm_NoPwr;
    FloatM      RxSNR_IQ_dBm_Pwr;
    FloatM      RxSNR_IQ_dBm_Pwr_NF;
    
    BoolM1D     DigitizerTimeout = DSP.Wait(Rx_IQ);

//=========== Measures Noise Floor ===========
    Sites SavedSites = ActiveSites; //keeps Running sites
    Sites GP1_Sites = NO_SITES ;
    Sites GP2_Sites = NO_SITES ;
    for (SiteIter siteIter = ActiveSites.Begin(); !siteIter.End(); ++siteIter) {   
  
    if (IntS(siteIter.GetValue()) == 1 || IntS(siteIter.GetValue()) ==3 )
    {GP1_Sites=GP1_Sites+siteIter.GetValue();}
    else if (IntS(siteIter.GetValue()) == 2 || IntS(siteIter.GetValue()) == 4 )
    {GP2_Sites=GP2_Sites+siteIter.GetValue();} 
    }
    
    if(GP1_Sites!=NO_SITES) {
    RunTime.SetActiveSites(GP1_Sites);
    
    DSP.Initialize(Rx_IQ);
    DSP.SetConfiguration(Rx_IQ, DSP_CONFIG_DIRECT);
    DSP.Connect(Rx_IQ,DSP_TO_DUT,DSP_MODE_SE);
    DSP.SetOffsetMode (Rx_IQ, DSP_OFFSET_DUT);
    DSP.DefineWaveform("MyCapture1", Rx_IQ);
    DSP.SetSampleRate("MyCapture1", RX_Fs);
    DSP.SetFilter("MyCapture1", DSP_FILTER_LOW_PASS, 5MHz);
    DSP.SetRange("MyCapture1", 2V);
    DSP.SetPoints ("MyCapture1", RX_Points);
//    DIGITAL.DisconnectSyncRefs();
//    DSP.SetTimeout(2.0s);
        
    DSP.Select("MyCapture1", Rx_IQ);
    DSP.Prepare();
    TIME.Wait(10ms);    
    DSP.Start(Rx_IQ);
    TIME.Wait(10ms);    
//    BoolM1D DigitizerTimeout = DSP.Wait(RxSNR_IQ);

        if (DigitizerTimeout.AllNotEqual(true)) {
            BoolM1D OverrangeFlag = DSP.ReadOverrangeFlag(Rx_IQ);
            if (OverrangeFlag.AllNotEqual(true)) {
                DSP.ReadWaveform("MyCapture1",Rx_IQ, ComplexCapture_NoRF, ComplexCaptureSim, DSP_DATA_TYPE_ALL);
                TIME.Wait(1us);
            } else {
                 //handle over-range
            }
        } else {
              // handle timeout error
        }
    }
    
    if(GP2_Sites!=NO_SITES) {
    RunTime.SetActiveSites(GP2_Sites); 
    
    DSP.Initialize(Rx_IQ);
    DSP.SetConfiguration(Rx_IQ, DSP_CONFIG_DIRECT);
    DSP.Connect(Rx_IQ,DSP_TO_DUT,DSP_MODE_SE);
    DSP.SetOffsetMode (Rx_IQ, DSP_OFFSET_DUT);
    DSP.DefineWaveform("MyCapture1", Rx_IQ);
    DSP.SetSampleRate("MyCapture1", RX_Fs);
    DSP.SetFilter("MyCapture1", DSP_FILTER_LOW_PASS, 5MHz);
    DSP.SetRange("MyCapture1", 2V);
    DSP.SetPoints ("MyCapture1", RX_Points);
//    DIGITAL.DisconnectSyncRefs();
//    DSP.SetTimeout(2.0s);
        
    DSP.Select("MyCapture1", Rx_IQ);
    DSP.Prepare();
    TIME.Wait(10ms);    
    DSP.Start(Rx_IQ);
    TIME.Wait(10ms);    
//    BoolM1D DigitizerTimeout = DSP.Wait(RxSNR_IQ);

        if (DigitizerTimeout.AllNotEqual(true)) {
            BoolM1D OverrangeFlag = DSP.ReadOverrangeFlag(Rx_IQ);
            if (OverrangeFlag.AllNotEqual(true)) {
                DSP.ReadWaveform("MyCapture1",Rx_IQ, ComplexCapture_NoRF, ComplexCaptureSim, DSP_DATA_TYPE_ALL);
                TIME.Wait(1us);
            } else {
                 //handle over-range
            }
        } else {
              // handle timeout error
        }
    }

    RunTime.SetActiveSites(SavedSites);
        DSP.DeleteWaveform("MyCapture1");
        DSP.Stop(Rx_IQ);
    

//        if (DigitizerTimeout.AllNotEqual(true)) {
//            BoolM1D OverrangeFlag = DSP.ReadOverrangeFlag(Rx_IQ);
//            if (OverrangeFlag.AllNotEqual(true)) {
//                DSP.ReadWaveform("MyCapture1",Rx_IQ, ComplexCapture_NoRF, ComplexCaptureSim, DSP_DATA_TYPE_ALL);
//                TIME.Wait(1us);

                for (SiteIter s = ActiveSites.Begin(); !s.End(); ++s)
                 {
                    for (int x =0; x< RX_N; x++)
                     {
                      ComplexCapture_I_NOPWR [*s][x] = ComplexCapture_NoRF[*s][0][x];
                      ComplexCapture_Q_NOPWR [*s][x] = ComplexCapture_NoRF[*s][1][x];                     
                     }
                 }

    FloatM1D ComplexSpectrum((RX_N/2)+1);
    FloatM1D ComplexCapture_merge_NoPWR;
    
        VSA.Math.InterleaveComplex(ComplexCapture_Q_NOPWR,ComplexCapture_I_NOPWR,ComplexCapture_merge_NoPWR);
               
                ComplexSpectrum = MATH.ComplexPowerFFT(ComplexCapture_merge_NoPWR);

/*
// For checking Specturm only
                FloatM1D Freq_NoPWR_RMS_K = MATH.Sqrt(ComplexSpectrum/2 + 1fV);
                FloatM1D RxSNR_IQ_dBm_NoPwr_K = CONV.VoltsTodBm(Freq_NoPWR_RMS_K, Impd);              
*/                
                FloatM1D Spectrum_NoPWR = ComplexSpectrum.Slice(STp,SPp);
                FloatM Freq_NoPWR = MATH.Sum(Spectrum_NoPWR);
                FloatM Freq_NoPWR_RMS = MATH.Sqrt(Freq_NoPWR/2 + 1fV);
                RxSNR_IQ_dBm_NoPwr = CONV.VoltsTodBm(Freq_NoPWR_RMS, Impd);
                TIME.Wait(1us);



//=========== Measures Noise Floor Done ======

//    BoolS splitMode    = false;
//    StringS my_setup_1 ="RF_source_cw";
    FloatM Freq_Offset = 0.25MHz;
//    
//    RF.DefineSetup (my_setup_1, srcPin, RF_SOURCE_CW, RF_GEN_SPLIT);
//    RF.ResolveSetup(my_setup_1);
//    RF.SelectSetup (my_setup_1);
//    RF.SetTimeout(0.5s);
    RF.SetSource(srcPin, ToneLevel+CWTonPWR_Loss, Tone_srcFreq+Freq_Offset, RF_PERFORMANCE_HIGH_LINEARITY); 
    TIME.Wait(2ms); //20ms
    RF.Prepare();
    TIME.Wait(1ms);
    
//    RF.SetSource(srcPin , -120dBm , Tone_srcFreq+Freq_Offset, RF_PERFORMANCE_HIGH_LINEARITY );
//    RF.Terminate(srcPin);
//    TIME.Wait(1ms);

    if(GP1_Sites!=NO_SITES) {
    RunTime.SetActiveSites(GP1_Sites);
    
    DSP.Initialize(Rx_IQ);
    DSP.SetConfiguration(Rx_IQ, DSP_CONFIG_DIRECT);
    DSP.Connect(Rx_IQ,DSP_TO_DUT,DSP_MODE_SE);
    DSP.SetOffsetMode (Rx_IQ, DSP_OFFSET_DUT);
    DSP.DefineWaveform("MyCaptureSNR", Rx_IQ);
    DSP.SetSampleRate("MyCaptureSNR", RX_Fs);
    DSP.SetFilter("MyCaptureSNR", DSP_FILTER_LOW_PASS, 1MHz);
    DSP.SetRange("MyCaptureSNR", 2V);
    DSP.SetPoints ("MyCaptureSNR", RX_Points);
//        DIGITAL.DisconnectSyncRefs();
//        DSP.SetTimeout(2.0s);
     
    DSP.Select("MyCaptureSNR", Rx_IQ);
    DSP.Prepare();
    TIME.Wait(10ms);
    DSP.Start(Rx_IQ);
    TIME.Wait(10ms);
    
        if (DigitizerTimeout.AllNotEqual(true)) {
            BoolM1D OverrangeFlag = DSP.ReadOverrangeFlag(Rx_IQ);
            if (OverrangeFlag.AllNotEqual(true)) {
                DSP.ReadWaveform("MyCaptureSNR",Rx_IQ, ComplexCapture, ComplexCaptureSim, DSP_DATA_TYPE_ALL);
                TIME.Wait(1us);
            } else {
                 //handle over-range
            }
        } else {
              // handle timeout error
        }
    }        

    if(GP2_Sites!=NO_SITES) {
    RunTime.SetActiveSites(GP2_Sites);
    
    DSP.Initialize(Rx_IQ);
    DSP.SetConfiguration(Rx_IQ, DSP_CONFIG_DIRECT);
    DSP.Connect(Rx_IQ,DSP_TO_DUT,DSP_MODE_SE);
    DSP.SetOffsetMode (Rx_IQ, DSP_OFFSET_DUT);
    DSP.DefineWaveform("MyCaptureSNR2", Rx_IQ);
    DSP.SetSampleRate("MyCaptureSNR2", RX_Fs);
    DSP.SetFilter("MyCaptureSNR2", DSP_FILTER_LOW_PASS, 1MHz);
    DSP.SetRange("MyCaptureSNR2", 2V);
    DSP.SetPoints ("MyCaptureSNR2", RX_Points);
//        DIGITAL.DisconnectSyncRefs();
//        DSP.SetTimeout(2.0s);
     
    DSP.Select("MyCaptureSNR2", Rx_IQ);
    DSP.Prepare();
    TIME.Wait(10ms);
    DSP.Start(Rx_IQ);
    TIME.Wait(10ms);
    
        if (DigitizerTimeout.AllNotEqual(true)) {
            BoolM1D OverrangeFlag = DSP.ReadOverrangeFlag(Rx_IQ);
            if (OverrangeFlag.AllNotEqual(true)) {
                DSP.ReadWaveform("MyCaptureSNR2",Rx_IQ, ComplexCapture, ComplexCaptureSim, DSP_DATA_TYPE_ALL);
                TIME.Wait(1us);
            } else {
                 //handle over-range
            }
        } else {
              // handle timeout error
        }
    }  

    RunTime.SetActiveSites(SavedSites);
    
//    DSP.DeleteAllWaveforms();
    DSP.Stop(Rx_IQ);
    RF.SetSource("BTRF" , -120dBm , Tone_srcFreq+Freq_Offset , RF_PERFORMANCE_HIGH_LINEARITY );
//    RF.Terminate("BTRF"); 
        
                for (SiteIter s = ActiveSites.Begin(); !s.End(); ++s)
                 {
                    for (int x =0; x< RX_N; x++)
                     {
                      ComplexCapture_I [*s][x] = ComplexCapture[*s][0][x];
                      ComplexCapture_Q [*s][x] = ComplexCapture[*s][1][x];                     
                     }
                 }
               
//    FloatM1D ComplexSpectrum((RX_N/2)+1);
    FloatM1D ComplexCapture_merge;

        VSA.Math.InterleaveComplex(ComplexCapture_Q,ComplexCapture_I,ComplexCapture_merge);
                ComplexSpectrum = MATH.ComplexPowerFFT(ComplexCapture_merge);
/* For Checking Spectrum only    */
                FloatM1D Spectrum_PWR_ALL = ComplexSpectrum.Slice(3,8190);
                FloatM1D Freq_PWR_RMS_ALL = MATH.Sqrt(Spectrum_PWR_ALL/2 + 1fV);
                FloatM1D RxSNR_ALL_dBm_Pwr = CONV.VoltsTodBm(Freq_PWR_RMS_ALL, Impd);

                FloatM1D Spectrum_PWR = ComplexSpectrum.Slice(STp,SPp);
                FloatM Freq_PWR = MATH.Sum(Spectrum_PWR);
                FloatM Freq_PWR_RMS = MATH.Sqrt(Freq_PWR/2 + 1fV);
                RxSNR_IQ_dBm_Pwr = CONV.VoltsTodBm(Freq_PWR_RMS, Impd);
              
                FloatM1D ComplexSpectrum_PFFTI = MATH.PowerFFT(ComplexCapture_I);
                FloatM1D Spectrum_PWR_I = ComplexSpectrum_PFFTI.Slice(STp,SPp);
                FloatM   Sum_PWR_I = MATH.Sum(Spectrum_PWR_I);                
                FloatM   Freq_PWR_RMS_I = MATH.Sqrt(Sum_PWR_I/2 + 1fV);
                FloatM   RxSNR_I_dBm_Pwr = CONV.VoltsTodBm(Freq_PWR_RMS_I, Impd);

                FloatM1D ComplexSpectrum_PFFTQ = MATH.PowerFFT(ComplexCapture_Q);
                FloatM1D Spectrum_PWR_Q = ComplexSpectrum_PFFTQ.Slice(STp,SPp);
                FloatM   Sum_PWR_Q = MATH.Sum(Spectrum_PWR_Q);                
                FloatM   Freq_PWR_RMS_Q = MATH.Sqrt(Sum_PWR_Q/2 + 1fV);
                FloatM   RxSNR_Q_dBm_Pwr = CONV.VoltsTodBm(Freq_PWR_RMS_Q, Impd);

    FloatM Rx_ATP_SNR     = RxSNR_IQ_dBm_Pwr - RxSNR_IQ_dBm_NoPwr;
 
    
//    std::cout << endl;
    std::cout << ReadFreqName+"_RxSNR_NoPwr_BAND1M = "      << RxSNR_IQ_dBm_NoPwr   << endl;    
    std::cout << ReadFreqName+"_RxSNR_m70dBmPwr_BAND1M = "  << RxSNR_IQ_dBm_Pwr     << endl;    
//    std::cout << ReadFreqName+"_Rx_ATP_SNR = "              << Rx_ATP_SNR           << endl;   
//    std::cout << ReadFreqName+"_Rx_ATP_PWR_SNR = "          << Rx_ATP_PWR_SNR       << endl;
    
//    testResult = DLOG.Value (RxSNR_I_dBm_Pwr,   -30, -15, "dBm", ReadFreqName+"_Rx_SNR_I_Bandpwr",     "RF_Rx_ATP_SNR_fail", UTL_VOID, MinorID+11); 
//    testResult = DLOG.Value (RxSNR_Q_dBm_Pwr,   -30, -15, "dBm", ReadFreqName+"_Rx_SNR_Q_Bandpwr",        "RF_Rx_ATP_SNR_fail", UTL_VOID, MinorID+12);
    
//    testResult = DLOG.Value (RxSNR_IQ_dBm_NoPwr,-70, -50, "dBm", ReadFreqName+"_Rx_ATP_SNR_BandNoise",     "RF_Rx_ATP_SNR_fail", UTL_VOID, MinorID+14); 

    //testResult = DLOG.Value (RxSNR_IQ_dBm_Pwr,  -25.5, -10, "dB",  ReadFreqName+Bist_Ver+"_Rx_ATP_SNR_24M_SPUR_BandPwr",     UTL_VOID, UTL_VOID, MinorID+13);
    //DLOG.AccumulateResults(local_Result, testResult);    
    testResult = DLOG.Value (Rx_ATP_SNR,     22.0, 50, "dB", ReadFreqName+Bist_Ver+"_Rx_SNR_24M_SPUR",     UTL_VOID, UTL_VOID, MinorID+01); 
    DLOG.AccumulateResults(local_Result, testResult); 
    return (local_Result);                    
}



TMResultM RF_TX_IM3_MEASURE_ORG(const FloatS _CenterFreq, FloatS _MeasureLevel,  IntS MinorID, StringS PatternID)
{
    TMResultM testResult, local_Result       = TM_NOTEST ;
    TMResultM testResult_TxIM3 = TM_NOTEST ;
    ReadFreq(ReadFreqName, _CenterFreq);

//    DIGITAL.ExecutePattern(PatternID);
    testResult = XdcFuncTest(testResult_TxIM3, MinorID+00, ReadFreqName+Bist_Ver+"_TxIM3_Pat", "RF_Tx_PWR_PAT_fail", PatternID, "AllPins_Pattern" );  
    TIME.Wait(50ms);
   
    StringS comments="RF Time Out";
    FloatM   carrier_pwr;
    UnsignedS   SAMPLE_SIZE  = 8192;    
    FloatS      SAMPLE_RATE  = 10.24MHz;
    FloatS      IF_FREQ      = 2.12125MHz;	
//    UnsignedS   SAMPLE_SIZE  = 8192;   
//    FloatS      SAMPLE_RATE  = 81.92MHz/4;
//    FloatS      IF_FREQ      = 2.10MHz;  //1.101111MHz
    FloatS      RBW          = SAMPLE_RATE/SAMPLE_SIZE; // RBW 1.25K
    FloatS      NUM_AVG      = 1;
    IntS        IF_BIN       = IF_FREQ/RBW; // 1697
    FloatM1D    time_domain_data ( SAMPLE_SIZE );
    FloatM1D    freq_domain_data_cal ( SAMPLE_SIZE/2+1);
    FloatM      RF_Gain, IF_Gain,RF_Cal_Factor,Meas_result; 
    IntM        carrier_bin   ;
	
    std::cout << endl;
    std::cout << "RBW = " << RBW << " ; IF =" << IF_FREQ << " ; IF_Bin = " << IF_BIN << endl;   	
    //  ------------------------------------ //
    //  MEAS SINGLE RF Two TONE WITH USER_RESBW  //
    //  ------------------------------------ //

    RF.DefineSetup ("RFmeasure_TxIM3", msrPin , RF_MEASURE) ;
    RF.ResolveSetup("RFmeasure_TxIM3");
    RF.SelectSetup ("RFmeasure_TxIM3");
    RF.SetTimeout(10ms);
    carrier_bin       = RF_MATH.ComputeBinNumber(IF_FREQ, SAMPLE_RATE, SAMPLE_SIZE);
    RF.SetMeasureUser(msrPin, RF_SCALAR, _MeasureLevel, _CenterFreq+1.25MHz, -IF_FREQ, RF_FILTER_LOW_PASS, 10MHz);
    RF.SetDigitizer (msrPin, SAMPLE_RATE, SAMPLE_SIZE, 10MHz, RF_HIGH_PRECISION, NUM_AVG, RF_AVERAGE_UTP, 1, false);
    RF.Prepare(); 		
    RF.Wait(msrPin);
    RF.StartMeasure (msrPin);
    TIME.Wait(1ms);   	
    RF.ReadFrequencyDomain (msrPin, RF_LOG_DBM, RF_DATA_CALIBRATED,freq_domain_data_cal, UTL_VOID);
    RF.ReadTimeDomain(msrPin,RF_DATA_CALIBRATED, time_domain_data, UTL_VOID);	
    comments = "RF TimeOut";
    if (RF.Wait(msrPin).AnyEqual(true)){ IO.Print (IO.Stdout,  comments+ " \n");}

//    RF.Terminate(msrPin);

                FloatM1D time_domain_PFFT = MATH.PowerFFT(time_domain_data);
                FloatM1D time_domain_RMS = MATH.Sqrt(time_domain_PFFT/2 + 1fV);
                FloatM1D time_domain_Pwr = CONV.VoltsTodBm(time_domain_RMS, Impd);
				
    FloatM1D Spectrum_ZoomIn = freq_domain_data_cal.Slice(1000,2400);
	
    //Rigth side
 
    IntM BIN = IF_BIN+202;  //R Bin
    IntM STp = BIN-5;
    IntM SPp = BIN+5;
    
    FloatM1D Spectrum_RVp     = time_domain_PFFT.Slice(STp,SPp);
    FloatM1D pDesire_RVp      = MATH.Xtrm(Spectrum_RVp);
    FloatM   pDesire_R_SumVp  = MATH.Sum(Spectrum_RVp);
    
    FloatM1D Spectrum_R1Vp    = time_domain_PFFT.Slice(BIN+395,BIN+405);
    FloatM1D pIMG_RVp         = MATH.Xtrm(Spectrum_R1Vp);
    FloatM   pDesire_IM3_R_SumVp = MATH.Sum(Spectrum_R1Vp);
    
    FloatM  pDesire_RVp1 = pDesire_RVp[0];
    FloatM  pIMG_RVp1  = pIMG_RVp [0];
    
    FloatM pDesire_R    = MATH.Sqrt(pDesire_RVp1/2 + 1fV);    
    FloatM R_Tone_PWR   = CONV.VoltsTodBm(pDesire_R, Impd);    
    FloatM pIMG_R       = MATH.Sqrt(pIMG_RVp1/2 + 1fV);    
    FloatM R_IM3_Pwr    = CONV.VoltsTodBm(pIMG_R, Impd);    
    FloatM pDesire_R_SumVrms = MATH.Sqrt(pDesire_R_SumVp/2 + 1fV);    
    FloatM R_Band_Pwr        = CONV.VoltsTodBm(pDesire_R_SumVrms, Impd);    
    FloatM pDesire_IM3_R_SumVrms = MATH.Sqrt(pDesire_IM3_R_SumVp/2 + 1fV);    
    FloatM R_Band_IM3_Pwr        = CONV.VoltsTodBm(pDesire_IM3_R_SumVrms, Impd);    
    
//    FloatM Tx_IM3_R=pDesire_R[0] - pIMG_R[0];
    
    std::cout << endl;
    std::cout << "R_Tone_PWR = "    << R_Tone_PWR << endl;
    std::cout << "R_IM3_Pwr = "     << R_IM3_Pwr    << endl;
    std::cout << "R_Band_Pwr = "    << R_Band_Pwr    << endl;
    std::cout << "R_Band_IM3_Pwr = "<< R_Band_IM3_Pwr    << endl;
    
  
    //Left side
    BIN=IF_BIN-198;  // 1499 for ver.A IC
//    BIN= 1493; for ver.B IC
    STp=BIN-5;
    SPp=BIN+5;
    
    FloatM1D Spectrum_LVp    = time_domain_PFFT.Slice(STp,SPp);
    FloatM1D pDesire_LVp     = MATH.Xtrm(Spectrum_LVp);
    FloatM   pDesire_L_SumVp = MATH.Sum(Spectrum_LVp);
    
    FloatM1D Spectrum_L1Vp       = time_domain_PFFT.Slice(BIN-405,BIN-395);
    FloatM1D pIMG_LVp            = MATH.Xtrm(Spectrum_L1Vp);
    FloatM   pDesire_IM3_L_SumVp = MATH.Sum(Spectrum_L1Vp);
    
    FloatM  pDesire_LVp1 = pDesire_LVp[0];
    FloatM  pIMG_LVp1  = pIMG_LVp [0];
    
    FloatM pDesire_L    = MATH.Sqrt(pDesire_LVp1/2 + 1fV);    
    FloatM L_Tone_PWR   = CONV.VoltsTodBm(pDesire_L, Impd);    
    FloatM pIMG_L       = MATH.Sqrt(pIMG_LVp1/2 + 1fV);    
    FloatM L_IM3_Pwr    = CONV.VoltsTodBm(pIMG_L, Impd);    
    FloatM pDesire_L_SumVrms = MATH.Sqrt(pDesire_L_SumVp/2 + 1fV);    
    FloatM L_Band_Pwr        = CONV.VoltsTodBm(pDesire_L_SumVrms, Impd);    
    FloatM pDesire_IM3_L_SumVrms = MATH.Sqrt(pDesire_IM3_L_SumVp/2 + 1fV);    
    FloatM L_Band_IM3_Pwr        = CONV.VoltsTodBm(pDesire_IM3_L_SumVrms, Impd);    

    FloatM Tx_IM3_L      = L_Tone_PWR - L_IM3_Pwr;
    FloatM Tx_IM3_BAND_L = L_Band_Pwr - L_Band_IM3_Pwr;

    std::cout << "L_Tone_PWR = "    << L_Tone_PWR << endl;
    std::cout << "L_IM3_Pwr = "     << L_IM3_Pwr    << endl;
    std::cout << "L_Band_Pwr = "    << L_Band_Pwr    << endl;
    std::cout << "L_Band_IM3_Pwr = "<< L_Band_IM3_Pwr    << endl;


//    testResult = DLOG.Value (L_Tone_PWR,    -5,   5, "dBm", ReadFreqName+"_Tx_PWR_L",       "RF_Tx_PWR_fail", UTL_VOID, MinorID+01); 
//    testResult = DLOG.Value (L_IM3_Pwr,     -99, 99, "dBm", ReadFreqName+"_Tx_IMR3_L",      "RF_Tx_PWR_fail", UTL_VOID, MinorID+02); 
//    testResult = DLOG.Value (R_Tone_PWR,    -5,   5, "dBm", ReadFreqName+"_Tx_PWR_R",       "RF_Tx_PWR_fail", UTL_VOID, MinorID+03); 
//    testResult = DLOG.Value (R_IM3_Pwr,     -99, 99, "dBm", ReadFreqName+"_Tx_IMR3_R",      "RF_Tx_PWR_fail", UTL_VOID, MinorID+04); 
    testResult = DLOG.Value (L_Band_Pwr,      -10, 10, "dBm", ReadFreqName+Bist_Ver+"_Tx_PWR_Band_L", UTL_VOID, UTL_VOID, MinorID+05);
    DLOG.AccumulateResults(local_Result, testResult);    
//    testResult = DLOG.Value (L_Band_IM3_Pwr,-99, 99, "dBm", ReadFreqName+"_Tx_IMR3_Band_L", "RF_Tx_PWR_fail", UTL_VOID, MinorID+06); 
//    testResult = DLOG.Value (R_Band_Pwr,    -2,   5, "dBm", ReadFreqName+"_Tx_PWR_Band_R",  "RF_Tx_PWR_fail", UTL_VOID, MinorID+07); 
//    testResult = DLOG.Value (R_Band_IM3_Pwr,-99, 99, "dBm", ReadFreqName+"_Tx_IMR3_Band_R", "RF_Tx_PWR_fail", UTL_VOID, MinorID+10); 
//
//    testResult = DLOG.Value (Tx_IM3_L,      30,  50, "dB",  ReadFreqName+"_Tx_IM3_L",       "RF_Tx_IM3_fail", UTL_VOID, MinorID+11); 
    testResult = DLOG.Value (Tx_IM3_BAND_L, 30,  50, "dB",  ReadFreqName+Bist_Ver+"_Tx_IM3_BAND_L",  UTL_VOID, UTL_VOID, MinorID+12); 
    DLOG.AccumulateResults(local_Result, testResult);
    
    return (local_Result); 

}

TMResultM RF_TX_IM3_MEASURE(const FloatS _CenterFreq, FloatS _MeasureLevel,  IntS MinorID, StringS PatternID)
{
    TMResultM testResult, local_Result       = TM_NOTEST ;
    TMResultM testResult_TxIM3 = TM_NOTEST ;
    ReadFreq(ReadFreqName, _CenterFreq);

//    DIGITAL.ExecutePattern(PatternID);
    testResult = XdcFuncTest(testResult_TxIM3, MinorID+00, ReadFreqName+Bist_Ver+"_TxIM3_Pat", "RF_Tx_PWR_PAT_fail", PatternID, "AllPins_Pattern" );  
    TIME.Wait(50ms);
   
    StringS comments="RF Time Out";
    FloatM   carrier_pwr;
    UnsignedS   SAMPLE_SIZE  = 8192;    
    FloatS      SAMPLE_RATE  = 10.24MHz;
    FloatS      IF_FREQ      = 2.12125MHz;	
//    UnsignedS   SAMPLE_SIZE  = 8192;   
//    FloatS      SAMPLE_RATE  = 81.92MHz/4;
//    FloatS      IF_FREQ      = 2.10MHz;  //1.101111MHz
    FloatS      RBW          = SAMPLE_RATE/SAMPLE_SIZE; // RBW 1.25K
    FloatS      NUM_AVG      = 1;
    IntS        IF_BIN       = IF_FREQ/RBW; // 1697
    FloatM1D    time_domain_data ( SAMPLE_SIZE );
    FloatM1D    freq_domain_data_cal ( SAMPLE_SIZE/2+1);
    FloatM      RF_Gain, IF_Gain,RF_Cal_Factor,Meas_result; 
    IntM        carrier_bin   ;
	
    std::cout << endl;
    std::cout << "RBW = " << RBW << " ; IF =" << IF_FREQ << " ; Ideal IF_Bin = " << IF_BIN << endl;   	
    //  ------------------------------------ //
    //  MEAS SINGLE RF Two TONE WITH USER_RESBW  //
    //  ------------------------------------ //
    StringS RF_Tx = "RFmeasure_TxIM3";
    RF.DefineSetup (RF_Tx, msrPin , RF_MEASURE) ;
    RF.ResolveSetup(RF_Tx);
    RF.SelectSetup (RF_Tx);
    RF.SetTimeout(10ms);
    carrier_bin       = RF_MATH.ComputeBinNumber(IF_FREQ, SAMPLE_RATE, SAMPLE_SIZE);
    RF.SetMeasureUser(msrPin, RF_SCALAR, _MeasureLevel, _CenterFreq+1.25MHz, -IF_FREQ, RF_FILTER_LOW_PASS, 10MHz);
    RF.SetDigitizer (msrPin, SAMPLE_RATE, SAMPLE_SIZE, 10MHz, RF_HIGH_PRECISION, NUM_AVG, RF_AVERAGE_UTP, 1, false);
    RF.Prepare(); 		
    RF.Wait(msrPin);
    RF.StartMeasure (msrPin);
    TIME.Wait(1ms);   	
    RF.ReadFrequencyDomain (msrPin, RF_LOG_DBM, RF_DATA_CALIBRATED,freq_domain_data_cal, UTL_VOID);
    RF.ReadTimeDomain(msrPin,RF_DATA_CALIBRATED, time_domain_data, UTL_VOID);	
    comments = "RF TimeOut";
    if (RF.Wait(msrPin).AnyEqual(true)){ IO.Print (IO.Stdout,  comments+ " \n");}

//    RF.Terminate(msrPin);

                FloatM1D time_domain_PFFT = MATH.PowerFFT(time_domain_data);
                
                FloatM1D time_domain_RMS = MATH.Sqrt(time_domain_PFFT/2 + 1fV);
                FloatM1D time_domain_Pwr = CONV.VoltsTodBm(time_domain_RMS, Impd);
				
    FloatM1D Spectrum_ZoomIn = freq_domain_data_cal.Slice(1000,2400);
	



//    //Rigth side
// 
//    IntM BIN = IF_BIN+202;  //R Bin
//    IntM STp = BIN-5;
//    IntM SPp = BIN+5;
//    
//    FloatM1D Spectrum_RVp     = time_domain_PFFT.Slice(STp,SPp);
//    FloatM1D pDesire_RVp      = MATH.Xtrm(Spectrum_RVp);
//    FloatM   pDesire_R_SumVp  = MATH.Sum(Spectrum_RVp);
//    
//    FloatM1D Spectrum_R1Vp    = time_domain_PFFT.Slice(BIN+395,BIN+405);
//    FloatM1D pIMG_RVp         = MATH.Xtrm(Spectrum_R1Vp);
//    FloatM   pDesire_IM3_R_SumVp = MATH.Sum(Spectrum_R1Vp);
//    
//    FloatM  pDesire_RVp1 = pDesire_RVp[0];
//    FloatM  pIMG_RVp1  = pIMG_RVp [0];
//    
//    FloatM pDesire_R    = MATH.Sqrt(pDesire_RVp1/2 + 1fV);    
//    FloatM R_Tone_PWR   = CONV.VoltsTodBm(pDesire_R, Impd);    
//    FloatM pIMG_R       = MATH.Sqrt(pIMG_RVp1/2 + 1fV);    
//    FloatM R_IM3_Pwr    = CONV.VoltsTodBm(pIMG_R, Impd);    
//    FloatM pDesire_R_SumVrms = MATH.Sqrt(pDesire_R_SumVp/2 + 1fV);    
//    FloatM R_Band_Pwr        = CONV.VoltsTodBm(pDesire_R_SumVrms, Impd);    
//    FloatM pDesire_IM3_R_SumVrms = MATH.Sqrt(pDesire_IM3_R_SumVp/2 + 1fV);    
//    FloatM R_Band_IM3_Pwr        = CONV.VoltsTodBm(pDesire_IM3_R_SumVrms, Impd);    
    
//    FloatM Tx_IM3_R=pDesire_R[0] - pIMG_R[0];
    
//    std::cout << endl;
//    std::cout << "R_Tone_PWR = "    << R_Tone_PWR << endl;
//    std::cout << "R_IM3_Pwr = "     << R_IM3_Pwr    << endl;
//    std::cout << "R_Band_Pwr = "    << R_Band_Pwr    << endl;
//    std::cout << "R_Band_IM3_Pwr = "<< R_Band_IM3_Pwr    << endl;
//    
  
    //Left side
    IntM    FBIN = IF_BIN-200; //1697-200 =1497
    IntM    FSTp = FBIN-8;     //1497-8
    IntM    FSPp = FBIN+8;     //1497+8

//// Search Peak for MainTone and MainIMD

                    IntM    L_Tone  = FBIN;
                    IntM    L_STp   = FSTp,   L_SPp   = FSPp;
                    IntM    FToneL_Bin = -99;
                    
                    FloatM1D Spectrum_L(17, -99), Spectrum_L_IMD(17, -99);
                             Spectrum_L = time_domain_PFFT.Slice(L_STp,L_SPp);
                    FloatM1D Tone_Desire_L  = MATH.Xtrm(Spectrum_L);

                    FToneL_Bin = Tone_Desire_L[1]+1489;
                    std::cout << "FToneL_Bin( Search...) = " << FToneL_Bin << endl;
//////

    IntM    Tone_STp = FToneL_Bin-5;
    IntM    Tone_SPp = FToneL_Bin+5;
    IntM    IMD_STp = FToneL_Bin-405;
    IntM    IMD_SPp = FToneL_Bin-395;
 
    FloatM L_Band_Pwr(99),  L_Band_IMD_Pwr(-99), pDesire_L_SumVp, pDesire_IMD_L_SumVp, pDesire_L_SumVrms, pDesire_IMD_L_SumVrms;
    FloatM1D Spectrum_LVp(11, 0), Spectrum_LIMDVp(11, 0);
    
        for (SiteIter _site = ActiveSites.Begin(); !_site.End(); ++_site)
            {
//std::cout << " CHK_Site = " << _site << endl;
                Spectrum_LVp[*_site]      = time_domain_PFFT[*_site].Slice(Tone_STp[*_site],Tone_SPp[*_site]);
                pDesire_L_SumVp[*_site]   = MATH.Sum(Spectrum_LVp[*_site]);
    
                pDesire_L_SumVrms[*_site] = MATH.Sqrt(pDesire_L_SumVp[*_site]/2 + 1fV);    
                L_Band_Pwr[*_site]        = CONV.VoltsTodBm(pDesire_L_SumVrms[*_site], Impd[*_site]); 


                Spectrum_LIMDVp[*_site]       = time_domain_PFFT[*_site].Slice(IMD_STp[*_site],IMD_SPp[*_site]);
                pDesire_IMD_L_SumVp[*_site]   = MATH.Sum(Spectrum_LIMDVp[*_site]);
  
                pDesire_IMD_L_SumVrms[*_site] = MATH.Sqrt(pDesire_IMD_L_SumVp[*_site]/2 + 1fV);    
                L_Band_IMD_Pwr[*_site]        = CONV.VoltsTodBm(pDesire_IMD_L_SumVrms[*_site], Impd[*_site]);
            }
                
    FloatM Tx_IMD_BAND_L = L_Band_Pwr - L_Band_IMD_Pwr;

    std::cout << "L_Band_Pwr(+-5Bin) = "    << L_Band_Pwr    << endl;
    std::cout << "L_Band_IMD_Pwr(+-5Bin) = "<< L_Band_IMD_Pwr    << endl;


    testResult = DLOG.Value (L_Band_Pwr,      -10, 10, "dBm", ReadFreqName+Bist_Ver+"_Tx_PWR_Band_L", UTL_VOID, UTL_VOID, MinorID+05);
    DLOG.AccumulateResults(local_Result, testResult);    

//    testResult = DLOG.Value (Tx_IM3_L,      30,  50, "dB",  ReadFreqName+"_Tx_IM3_L",       "RF_Tx_IM3_fail", UTL_VOID, MinorID+11); 
    testResult = DLOG.Value (Tx_IMD_BAND_L, 30,  50, "dB",  ReadFreqName+Bist_Ver+"_Tx_IM3_BAND_L", UTL_VOID, UTL_VOID, MinorID+12); 
    DLOG.AccumulateResults(local_Result, testResult);
    
    return (local_Result); 

}


TMResultM RF_TX_EDR3_Test(TMResultM _testResult, const FloatS _CenterFreq, FloatS _MeasureLevel,  IntS MinorID, StringS PatternID)
{
    TMResultM testResult,  local_Result       = TM_NOTEST ;
    TMResultM testResult_TxEDR3 = TM_NOTEST ;
    ReadFreq(ReadFreqName, _CenterFreq);

    testResult = XdcFuncTest(testResult_TxEDR3, MinorID+00, ReadFreqName+Bist_Ver+"_TxEDR3_Pat", "RF_Tx_EDR3_PAT_fail", PatternID, "AllPins_Pattern" );  
    TIME.Wait(5ms);

    UnsignedS NumSlots = 12;
    UnsignedS OSR = 32;  //Mini is 4xOSR
    UnsignedS SAMPLE_RATE = 32MHz;  //Mini is 4xN MHz
    BoolS Edropt;
    
    FloatM TX_RMS_DEVM(0), TX_PEAK_DEVM(0), TX_FREQ_ERR(0), TX_DEVM99Pct(999), TX_FREQ_MAX_ERR(0),TX_rmsEvmPct(999) ;    
    FloatM TX_gfskBurstPowerdBm(-99), TX_edrBurstPowerdBm(-99);

    BluetoothEdrDemodOptions myEdrOpt; //For maximumEdrBlockFrequencyError only
    myEdrOpt.enablePskDriftTracking = true; //For maximumEdrBlockFrequencyError only
        
    ModDemodBluetooth myBlueTooth;
    VSA.Library.SetExecutionMode(MODE_PARALLEL);
    myBlueTooth.SetMeasureSiteMode(RF_ACTIVE_SITES);
    
    myBlueTooth.MeasureSetup(msrPin, _MeasureLevel, _CenterFreq, NumSlots, OSR);
    TIME.Wait(0ms);
    
    myBlueTooth.Measure();
    TIME.Wait(20ms);
    
    FloatM1D cplxM = myBlueTooth.GetMeasureTimeDomain(true);
    BluetoothEdrDemodResults demodresults_DEVM;
    VSA.BT.EdrDemodulation(cplxM, SAMPLE_RATE, demodresults_DEVM, myEdrOpt, 0, false, "AA123"); // this library contain all BLE standard test items
//    VSA.BT.EdrDemodulation(cplxM, SAMPLE_RATE, demodresults_DEVM,0,false,"AA123"); // this library contain all BLE standard test items

//    RF.SetSource(msrPin , -120dBm , _CenterFreq , RF_PERFORMANCE_HIGH_LINEARITY );
//    RF.Terminate(msrPin);


    TX_rmsEvmPct        = demodresults_DEVM.rmsEvmPct;
    TX_PEAK_DEVM        = demodresults_DEVM.peakDevm;
    TX_RMS_DEVM         = demodresults_DEVM.rmsDevm;
    TX_FREQ_ERR         = demodresults_DEVM.carrierFrequencyError;
    TX_DEVM99Pct        = demodresults_DEVM.devm99pct;   
    TX_FREQ_MAX_ERR     = demodresults_DEVM.maximumEdrBlockFrequencyError;
    TX_gfskBurstPowerdBm= demodresults_DEVM.gfskBurstPowerdBm;
    TX_edrBurstPowerdBm = demodresults_DEVM.edrBurstPowerdBm;
    
    cout << endl;
//    cout << ReadFreqName+"_TX_rmsEvm_% = "          << TX_rmsEvmPct         << "%"  <<  endl;
//    cout << ReadFreqName+"_TX_RMS_DEVM_% = "        << TX_RMS_DEVM*100      << "%"  <<  endl;
//    cout << ReadFreqName+"_TX_PEAK_DEVM_% = "       << TX_PEAK_DEVM*100     << "%"  <<  endl;
//    cout << ReadFreqName+"_TX_DEVM99_% = "          << TX_DEVM99Pct*100     << "%"  <<  endl;
//    cout << ReadFreqName+"_TX_FREQ_ERR_KHz = "      << TX_FREQ_ERR/1000     << "KHz"<<  endl;    
//    cout << ReadFreqName+"_TX_FREQ_MAX_ERR_KHz = "  << TX_FREQ_MAX_ERR/1000 << "KHz"<<  endl;
    
//    FloatM Result_TX_rmsEvmPct  = TX_rmsEvmPct;
    FloatM Result_TX_PEAK_DEVM      = TX_PEAK_DEVM*100;
    FloatM Result_TX_RMS_DEVM       = TX_RMS_DEVM*100;
    FloatM Result_TX_DEVM99Pct      = TX_DEVM99Pct*100;
    FloatM Result_TX_FREQ_ERR       = TX_FREQ_ERR;
    FloatM Result_TX_FREQ_MAX_ERR   = TX_FREQ_MAX_ERR;
    
    FloatM Power_Rel                = TX_edrBurstPowerdBm - TX_gfskBurstPowerdBm;

    
/*
    FloatM rmsEvmPct;   ///<RMS EVM in percent
    FloatM rmsDevm;     ///<RMS DEVM in percent
    FloatM peakDevm;    ///<Peak DEVM value in percent
    UnsignedM peakDevmLocation;   ///<Symbol number where the peak DEVM value occurs
    FloatM devm99pct;   ///<RMS DEVM value for which 99% of the measured DEVM symbol values are lower
    FloatM carrierFrequencyError; ///<Average carrier frequency error (relative to center channel) in Hz
    FloatM maximumEdrBlockFrequencyError; ///<Maximum carrier frequency error (relative to the center channel) of all measured EDR 50Symbol blocks in Hz. Note: This value is only populated if EDR Frequency Tracking is enabled
    FloatM rmsPhaseErrorDegrees; ///<RMS phase error in degrees
    FloatM rmsMagErrorPct;      ///<RMS Magnitude error in percent
    FloatM gfskBurstPowerdBm;   ///<Power of the GFSK portion of the measured signal
    FloatM edrBurstPowerdBm;    ///<Power of the EDR portion of the measured signal
*/    
 
    TIME.Wait(10ms);

    testResult = DLOG.Value (Result_TX_RMS_DEVM,         0,     20,   "%", ReadFreqName+Bist_Ver+"_TX_RMS_DEVM", UTL_VOID, UTL_VOID, MinorID+01); 
    DLOG.AccumulateResults(local_Result, testResult);
    testResult = DLOG.Value (Result_TX_PEAK_DEVM,        0,     20,   "%", ReadFreqName+Bist_Ver+"_TX_PEAK_DEVM", UTL_VOID, UTL_VOID, MinorID+02); 
    DLOG.AccumulateResults(local_Result, testResult);
    testResult = DLOG.Value (Result_TX_DEVM99Pct,        0,     20,   "%", ReadFreqName+Bist_Ver+"_TX_DEVM99Pct", UTL_VOID, UTL_VOID, MinorID+03); 
    DLOG.AccumulateResults(local_Result, testResult);
//    testResult = DLOG.Value (Result_TX_FREQ_ERR,    -10000,  10000, "KHz", ReadFreqName+"_TX_FREQ_ERR",        "RF_Tx_EDR3_Freq_fail", UTL_VOID, MinorID+04); 
//    testResult = DLOG.Value (Result_TX_FREQ_MAX_ERR,-10000,  10000, "KHz", ReadFreqName+"_TX_FREQ_MAX_ERR",    "RF_Tx_EDR3_Freq_fail", UTL_VOID, MinorID+05); 
    //-testResult = DLOG.Value (TX_gfskBurstPowerdBm,       8,     10.6, "dBm", ReadFreqName+Bist_Ver+"_TX_gfskBurstPowerdBm", "RF_Tx_EDR3_Pwr_fail",  UTL_VOID, MinorID+06); // 1st version spec
    testResult = DLOG.Value (TX_gfskBurstPowerdBm,       7.5,     11.5, "dBm", ReadFreqName+Bist_Ver+"_TX_gfskBurstPowerdBm", UTL_VOID,  UTL_VOID, MinorID+06); //20230222
    DLOG.AccumulateResults(local_Result, testResult);
    testResult = DLOG.Value (TX_edrBurstPowerdBm,        4,      7.6, "dBm", ReadFreqName+Bist_Ver+"_TX_edrBurstPowerdBm", UTL_VOID,  UTL_VOID, MinorID+07); //20230222
//    testResult = DLOG.Value (TX_edrBurstPowerdBm,        4,      8.6, "dBm", ReadFreqName+Bist_Ver+"_TX_edrBurstPowerdBm", UTL_VOID,  UTL_VOID, MinorID+07); //20230222 try
    DLOG.AccumulateResults(local_Result, testResult);
    testResult = DLOG.Value (Power_Rel,                 -4,      0, "dBm", ReadFreqName+Bist_Ver+"_Power_ReldBc", UTL_VOID,  UTL_VOID, MinorID+10); 
    DLOG.AccumulateResults(local_Result, testResult);

   if (PatternID == "RFTX_EDR3_DEVM_2440MHz_ID14") {
      std::cout<< "24440MHz_P_Gfsk= "<< TX_gfskBurstPowerdBm<< endl;
      GlobalVariable_24440MHz_P_Gfsk= TX_gfskBurstPowerdBm;
      }
   
    testResult = XdcFuncTest123(1, "RF_RESET_ID255 Test", "RF_Tx_EDR3_PAT_fail", "RF_RESET_ID255", "AllPins_Pattern" );    
   // DIGITAL.ExecutePattern("RF_RESET_ID255"); 
   TIME.Wait(5ms);
    
    return (local_Result);     
}


TMResultM RF_RX_BER_Test(FloatS _CenterFreq, FloatS _ScrLevel,  IntS MinorID, StringS PatternID)
{

//    DIGITAL.ExecutePattern("RF_RESET_ID255"); // for fail retest
    
    TMResultM BERtestResult       = TM_NOTEST;
    ReadFreq(ReadFreqName, _CenterFreq);
    TIME.Wait(50ms);    

//===== Output IQ =====
//    FloatS1D iarry;
//    FloatS1D qarry;
//    StringS MVStr = wave_SP_3DH5.waveIdString;
//    RfWaveform RFMV;
//    IntS DATA_ARR = RFMV.GetBasebandArrays(MVStr, iarry, qarry);
//=====   END     ===== 

    UnsignedS SampleRate = wave_SP_3DH5.bbSampleRate;
    VSA.HW.SetSourceSplitMode(true);

//std::cout << endl; 
//StringS WAVE_WORK =    wave_SP_3DH5.waveIdString; 
//std::cout << " waveIdString = " << WAVE_WORK << endl; 
 
if(LoadWaveform == true )
{
//    VSA.HW.SourceWaveform(srcPin, "myWaveBER", _CenterFreq, _ScrLevel, true, NO_RF_TRIGGER_SOURCE, 0);
    VSA.HW.SourceWaveform(srcPin, wave_SP_3DH5.waveIdString, _CenterFreq, _ScrLevel+CWTonPWR_Loss, wave_SP_3DH5.iArray, wave_SP_3DH5.qArray, SampleRate, LoadWaveform);    
    LoadWaveform = false;
    }
else
//    VSA.HW.SourceWaveform(srcPin, "myWaveBER", _CenterFreq, _ScrLevel, false, NO_RF_TRIGGER_SOURCE, 0);
    VSA.HW.SourceWaveform(srcPin, wave_SP_3DH5.waveIdString, _CenterFreq, _ScrLevel+CWTonPWR_Loss, wave_SP_3DH5.iArray, wave_SP_3DH5.qArray, SampleRate, LoadWaveform);
//    VSA.HW.SourceWaveform(srcPin, wave_SP_3DH5.waveIdString, _CenterFreq, _ScrLevel+CWTonPWR_Loss, wave_BER.iArray, wave_BER.qArray, SampleRate, false);
//    VSA.HW.SourceWaveform(srcPin, wave.waveIdString, SrcFreq, -45dBm + wave.bbPeakToAverage, wave.iArray, wave.qArray, SampleRate, LoadWaveform);

    TIME.Wait(5ms);  
    BERtestResult = XdcFuncTest123(MinorID+00, ReadFreqName+Bist_Ver+"_RxBER_Pat", UTL_VOID, PatternID, "AllPins_Pattern" );  
    TIME.Wait(0ms);

    VSA.HW.StopSourceWaveform(srcPin);
    TIME.Wait(0ms);
  
    DIGITAL.ExecutePattern("RF_RESET_ID255"); // for fail retest
  
    return (BERtestResult);
}



//TMResultM RF_RX_BER_serialTest(TMResultM _testResult, FloatS _CenterFreq, FloatS _ScrLevel,IntS MinorID, StringS PatternID)
//{
//    TMResultM testResult       = TM_NOTEST;
//    TMResultM BER_testResult   = TM_NOTEST;    
//
//TIME.StartTimer();
//
//    UnsignedS SampleRate = wave_SP_3DH5.bbSampleRate;
//    VSA.HW.SetSourceSplitMode(true);
//    VSA.HW.SourceWaveform(srcPin, wave_SP_3DH5.waveIdString, _CenterFreq, _ScrLevel+CWTonPWR_Loss, wave_SP_3DH5.iArray, wave_SP_3DH5.qArray, SampleRate, LoadWaveform);
////    VSA.HW.SourceWaveform(srcPin, wave.waveIdString, SrcFreq, -45dBm + wave.bbPeakToAverage, wave.iArray, wave.qArray, SampleRate, LoadWaveform);
//    TIME.Wait(0ms);    
//
//FloatS ElapsedTime1 = TIME.GetTimer();
//std::cout << " BER_SRC = " << ElapsedTime1 << endl;
//
//     BER_testResult = XdcFuncTest123(MinorID+00, ReadFreqName+"_RxBER_Pat", UTL_VOID, PatternID, "AllPins_Pattern" );  
//    TIME.Wait(10ms);
//
//FloatS ElapsedTime2 = TIME.GetTimer();
//std::cout << " BER_Result = " << ElapsedTime2 << endl;
//    
//    VSA.HW.StopSourceWaveform(srcPin);
//
//FloatS ElapsedTime3 = TIME.StopTimer();
//std::cout << " BER_DONE = " << ElapsedTime3 << endl;
//   
//    return (BER_testResult);    
//}


void BER_SRC(FloatS _CenterFreq, FloatS _ScrLevel)
{

    wave_SP_3DH5.LoadFromFile("myWaveBER",SYS.GetProgramPath() + "/../Waveforms/Bluetooth_3DH5_prbs9_SyncWord0x12345601234_LTADDR0_Flow0_ARQN0_SEQN1_LLID2_Flow0_Length1021_PnSeq0x1ff_fs32MHz_3.75ms.urf" );
    LoadWaveform = true;

//    BasicRfWaveform wave ;
PinM   SSPin = "CHK_SRC";
   
    UnsignedS SampleRate = wave_SP_3DH5.bbSampleRate;
    VSA.HW.SetSourceSplitMode(true);
    VSA.HW.SourceWaveform(SSPin,wave_SP_3DH5.waveIdString, _CenterFreq, _ScrLevel, wave_SP_3DH5.iArray, wave_SP_3DH5.qArray, SampleRate, LoadWaveform);
//    VSA.HW.SourceWaveform(srcPin, wave.waveIdString, _CenterFreq, -85dBm, wave.iArray, wave.qArray, SampleRate, LoadWaveform);
//    VSA.HW.SourceWaveform(srcPin, wave.waveIdString, SrcFreq, -45dBm + wave.bbPeakToAverage, wave.iArray, wave.qArray, SampleRate, LoadWaveform);
    TIME.Wait(0ms);    


    UnsignedS NumSlots = 12;
    UnsignedS OSR = 32;  //Mini is 4xOSR
    UnsignedS SAMPLE_RATE = 32MHz;  //Mini is 4xN MHz
    BoolS Edropt;
    

    BluetoothEdrDemodOptions myEdrOpt; //For maximumEdrBlockFrequencyError only
    myEdrOpt.enablePskDriftTracking = true; //For maximumEdrBlockFrequencyError only
        
    ModDemodBluetooth myBlueTooth;
//    VSA.Library.SetExecutionMode(MODE_PARALLEL);
    myBlueTooth.SetMeasureSiteMode(RF_ACTIVE_SITES);
    
    myBlueTooth.MeasureSetup(msrPin, -70dBm, 2402MHz, NumSlots, OSR);
    TIME.Wait(0ms);
    
    myBlueTooth.Measure();
    TIME.Wait(20ms);
    
    FloatM1D cplxM = myBlueTooth.GetMeasureTimeDomain(true);
    BluetoothEdrDemodResults demodresults_DEVM;
    VSA.BT.EdrDemodulation(cplxM, SAMPLE_RATE, demodresults_DEVM, myEdrOpt, 0, true, "AA123"); // this library contain all BLE standard test items
//    VSA.BT.EdrDemodulation(cplxM, SAMPLE_RATE, demodresults_DEVM,1,true,"AA123"); // this library contain all BLE standard test items
    RF.Terminate(msrPin);



    
    VSA.HW.StopSourceWaveform(SSPin);
//    RF.Terminate(srcPin);
//    RF.DeleteWaveform("myWaveBER");

}


void CHK_LOSS(PinM _srcPort, PinM _msrPort, FloatS _ScrLevel, FloatS _MeasureLevel, FloatS _CenterFreq)
{
    StringS my_setup_1 ="RF_source_cw";

    RF.DefineSetup (my_setup_1, _srcPort, RF_SOURCE_CW, RF_GEN_SPLIT);
    RF.ResolveSetup(my_setup_1);
    RF.SelectSetup (my_setup_1);
    RF.SetTimeout(0.5s);
    RF.SetSource(_srcPort, _ScrLevel, _CenterFreq, RF_PERFORMANCE_HIGH_LINEARITY); 
    TIME.Wait(2ms); //20ms
    RF.Prepare();
    TIME.Wait(1ms);
//cable+through ~ 0.6dB loss @2402M
//    RF.Terminate(_srcPort);    
//    RF.SetSource(_srcPort , -120dBm , _CenterFreq, RF_PERFORMANCE_HIGH_LINEARITY );

    
    ReadFreq(ReadFreqName, _CenterFreq);
    
    StringS comments="";
    FloatM   carrier_pwr;
    FloatM  msrpwr , msrpwr1;
    FloatM  msrpwr_sim = -99dBm;
    UnsignedS   SAMPLE_SIZE  = 8192;    
    FloatS      SAMPLE_RATE  = 10.24MHz;
    FloatS      IF_FREQ      = 2.12125MHz;
    FloatS      RBW          = SAMPLE_RATE/SAMPLE_SIZE; // RBW 2.5K
    FloatS      NUM_AVG      = 1;
    IntS        IF_BIN       = IF_FREQ/RBW; //840
    FloatM1D    time_domain_data ( SAMPLE_SIZE );
    FloatM1D    freq_domain_data_cal ( SAMPLE_SIZE/2+1);
    FloatM      RF_Gain, IF_Gain,RF_Cal_Factor,Meas_result; 
    IntM        carrier_bin   ;
    //  ------------------------------------ //
    //  MEAS SINGLE RF Two TONE WITH USER_RESBW  //
    //  ------------------------------------ //

    RF.DefineSetup ("CHKTT", _msrPort , RF_MEASURE) ;
    RF.ResolveSetup("CHKTT");
    RF.SelectSetup ("CHKTT");
    RF.SetTimeout(10ms);
    carrier_bin       = RF_MATH.ComputeBinNumber(IF_FREQ, SAMPLE_RATE, SAMPLE_SIZE);
    RF.SetMeasureUser(_msrPort, RF_SCALAR, _MeasureLevel, _CenterFreq+0.25MHz, -IF_FREQ, RF_FILTER_LOW_PASS, 10MHz);
//    RF.SetDigitizer (_msrPort, SAMPLE_RATE, SAMPLE_SIZE, 10MHz, RF_HIGH_PRECISION, NUM_AVG, RF_AVERAGE_UTP, 1, false);
    RF.SetDigitizer (_msrPort, SAMPLE_RATE, SAMPLE_SIZE, 10MHz, RF_HIGH_PRECISION, NUM_AVG, RF_AVERAGE_POWER, 1, false);
    RF.Prepare(); 		
    RF.Wait(_msrPort);
    RF.StartMeasure (_msrPort);
    RF.ReadFrequencyDomain (_msrPort, RF_LOG_DBM, RF_DATA_CALIBRATED,freq_domain_data_cal, UTL_VOID);
    RF.ReadPower(_msrPort, msrpwr, msrpwr_sim);
    FloatM     MyuserP,MyuserPim,MyuserP_sim,MyuserPim_sim;
    RF.ReadPowerUser(_msrPort,  _CenterFreq-0MHz, 50KHz   ,MyuserP, MyuserP_sim);
    RF.ReadPowerUser(_msrPort,  _CenterFreq-1.75MHz, 50KHz     ,MyuserPim, MyuserPim_sim);

//     
    comments = "RF TimeOut";
    if (RF.Wait(_msrPort).AnyEqual(true)){ IO.Print (IO.Stdout,  comments+ " \n");}

    std::cout << endl;
    std::cout << "RBW = " << RBW << " ; IF =" << IF_FREQ << " ; IF_Bin = " << IF_BIN << endl; 

    FloatM1D Spectrum_ZoomIn = freq_domain_data_cal.Slice(1000,2400);
    
//    RF.Terminate(msrPin);
//
//                FloatM1D time_domain_PFFT = MATH.PowerFFT(time_domain_data);
//                FloatM1D time_domain_RMS = MATH.Sqrt(time_domain_PFFT/2 + 1fV);
//                FloatM1D time_domain_Pwr = CONV.VoltsTodBm(time_domain_RMS, Impd);

    //Rigth side
    IntM Bin_Lo = 1697;    
    IntM BIN = Bin_Lo+202;  //Bin1242-Bin1442
    IntM STp = BIN-10;
    IntM SPp = BIN+10;
    
    FloatM1D Spectrum_R = freq_domain_data_cal.Slice(STp,SPp);
    FloatM1D pDesire_R= MATH.Xtrm(Spectrum_R);
    Spectrum_R = freq_domain_data_cal.Slice(BIN+390,BIN+410);
    FloatM1D pIMG_R= MATH.Xtrm(Spectrum_R);
    FloatM Tx_IM3_R=pDesire_R[0] - pIMG_R[0];
    
    std::cout << endl;
//    std::cout << "=============TX2402M_IM3================="<< endl;
    std::cout << "R_side_Tx_IM3_R = " << Tx_IM3_R     << endl;
    std::cout << "R_side_Tone = "     << pDesire_R[0] << endl;
    std::cout << "R_side_IM3 = "      << pIMG_R[0]    << endl;
    
  
    //Left side
    BIN=Bin_Lo-198;
    STp=BIN-10;
    SPp=BIN+10;
    
    FloatM1D Spectrum_L = freq_domain_data_cal.Slice(STp,SPp);
    FloatM1D pDesire_L= MATH.Xtrm(Spectrum_L);
    Spectrum_L = freq_domain_data_cal.Slice(BIN-410,BIN-390);
    FloatM1D pIMG_L= MATH.Xtrm(Spectrum_L);
    FloatM Tx_IM3_L=pDesire_L[0] - pIMG_L[0];
    FloatM Tx_PWR  =pDesire_L[0];
    
    std::cout << ReadFreqName+"_L_side_Tx_IM3_L = " << Tx_IM3_L     << endl;
    std::cout << ReadFreqName+"_L_side_Tone = "     << pDesire_L[0] << endl;
    std::cout << ReadFreqName+"_L_side_IM3 = "      << pIMG_L[0]    << endl;   
    std::cout << ReadFreqName+"_MyuserP = "      << MyuserP    << endl;   
    std::cout << ReadFreqName+"_MyuserPim3 = "      << MyuserPim    << endl;   

    RF.Terminate(_srcPort);    
    RF.SetSource(_srcPort , -120dBm , _CenterFreq, RF_PERFORMANCE_HIGH_LINEARITY );


}


/////////////// For Verification ////////////////

void CHK_TT(PinM _srcPort, PinM _msrPort, FloatS _MeasureLevel, FloatS _CenterFreq, FloatS MainTone_srcFreq, FloatS ToneLevel )
{
    FloatS ToneSpacing = 0.5MHz;  
//    FloatS ToneSpacing = 3MHz;  
    StringS waveform = "AWG Signal";
    FloatS AwgFs;
    FloatS Max_AwgFs = 60MHz;
    FloatS AwgFF = 1KHz;        
    RfPowerSpectrum spec;
    BoolS splitMode = false;

//Define Two Tone Parameter
    FloatS OffsetFreq =  0.0MHz;   //First Tone at XMHz,Second Tone at XXMHz
    FloatS AwgFilter = 50kHz;
    FloatM1D ComplexArr;
    FloatM par;

TIME.StartTimer();

//Generate 2 Tone using VSA library
    BasicRfWaveform TwoToneWave = VSA.Math.TwoTone(ToneSpacing,OffsetFreq,Max_AwgFs); 
    FloatM1D I_Array_VSA = TwoToneWave.iArray;
    FloatM1D Q_Array_VSA = TwoToneWave.qArray;
//    FloatM1D I_Array_VSA = TwoToneWave.iArray[SITE_1];
//    FloatM1D Q_Array_VSA = TwoToneWave.qArray[SITE_1];    
    AwgFs= TwoToneWave.bbSampleRate;
//    VSAPlotter::PLOT.BasicLine("ITime","Wave","I",I_Array_VSA) ;
//    VSAPlotter::PLOT.BasicLine("QTime","Wave","Q",Q_Array_VSA) ; 
    VSA.Math.InterleaveComplex(Q_Array_VSA,I_Array_VSA,ComplexArr);
    spec.CreateFromCplxTime(ComplexArr,AwgFs,AwgFF,0Hz) ;

    FloatM srcFiltFreq_M = 100MHz;  
    FloatM Max_AwgFs_M = 60MHz;
//
    StringS IDString = "TwoToneSource";

        RF.DeleteSetup      ( IDString );
        RF.DefineSetup      ( IDString , _srcPort , RF_SOURCE_MOD,RF_GEN_SPLIT);
        RF.ResolveSetup     ( IDString );
        RF.SelectSetup      ( IDString );     
        
        RF.DefineWaveform   ( IDString , _srcPort , Max_AwgFs_M , srcFiltFreq_M , RF_SAMPLING_AUTO , RF_MODULATION_I_Q , RF_TONE_1 );
        RF.LoadWaveform     ( IDString , I_Array_VSA ,Q_Array_VSA ,RF_TONE_1 );
        RF.ConnectAWG       ( _srcPort , RF_MODULATION_I_Q, RF_TONE_1 );
        RF.SelectWaveform   ( IDString , _srcPort ,RF_MODULATION_I_Q,RF_TONE_1);  // aryOffset , blockSz , RF_MODULATION_I_Q, RF_TONE_1);
        RF.EnableModulation ( _srcPort   );
        RF.Prepare();
        TIME.Wait(3ms);
        
        RF.SetSource        ( _srcPort, ToneLevel+6.0206dB+0.1dB, MainTone_srcFreq+1.25MHz, RF_PERFORMANCE_HIGH_LINEARITY); //    ToneLevel = Setting + 6.0206dB;  // + peak to rms of waveform; // 2402MHz+4.5MHz for TwoTone 2405MHz & 2408MHz tonespacing
//        RF.SetSource        ( _srcPort, ToneLevel+6.0206dB, MainTone_srcFreq+4.5MHz, RF_PERFORMANCE_HIGH_LINEARITY); //    ToneLevel = Setting + 6.0206dB;  // + peak to rms of waveform; // 2402MHz+4.5MHz for TwoTone 2405MHz & 2408MHz tonespacing
        TIME.Wait(0ms);
        FloatM TTValue = ToneLevel+6.0206dB;
        
        RF.StartAWG(_srcPort, RF_MODULATION_I_Q, RF_TONE_1);
        TIME.Wait(1ms);
        

    ReadFreq(ReadFreqName, MainTone_srcFreq);
    
    StringS comments="";
    FloatM   carrier_pwr;
    FloatM  msrpwr , msrpwr1;
    FloatM  msrpwr_sim = -99dBm;
    UnsignedS   SAMPLE_SIZE  = 8192;    
    FloatS      SAMPLE_RATE  = 10.24MHz;
    FloatS      IF_FREQ      = 2.12125MHz;
    FloatS      RBW          = SAMPLE_RATE/SAMPLE_SIZE; // RBW 2.5K
    FloatS      NUM_AVG      = 1;
    IntS        IF_BIN       = IF_FREQ/RBW; //840
    FloatM1D    time_domain_data ( SAMPLE_SIZE );
    FloatM1D    freq_domain_data_cal ( SAMPLE_SIZE/2+1);
    FloatM      RF_Gain, IF_Gain,RF_Cal_Factor,Meas_result; 
    IntM        carrier_bin   ;
    //  ------------------------------------ //
    //  MEAS SINGLE RF Two TONE WITH USER_RESBW  //
    //  ------------------------------------ //

    RF.DefineSetup ("CHKTT", _msrPort , RF_MEASURE) ;
    RF.ResolveSetup("CHKTT");
    RF.SelectSetup ("CHKTT");
    RF.SetTimeout(10ms);
    carrier_bin       = RF_MATH.ComputeBinNumber(IF_FREQ, SAMPLE_RATE, SAMPLE_SIZE);
    RF.SetMeasureUser(_msrPort, RF_SCALAR, _MeasureLevel, _CenterFreq+1.25MHz, -IF_FREQ, RF_FILTER_LOW_PASS, 10MHz);
    RF.SetDigitizer (_msrPort, SAMPLE_RATE, SAMPLE_SIZE, 10MHz, RF_HIGH_PRECISION, NUM_AVG, RF_AVERAGE_UTP, 1, false);
//    RF.SetDigitizer (_msrPort, SAMPLE_RATE, SAMPLE_SIZE, 10MHz, RF_HIGH_PRECISION, NUM_AVG, RF_AVERAGE_POWER, 1, false);
    RF.Prepare(); 		
    RF.Wait(_msrPort);
    RF.StartMeasure (_msrPort);
    RF.ReadFrequencyDomain (_msrPort, RF_LOG_DBM, RF_DATA_CALIBRATED,freq_domain_data_cal, UTL_VOID);
    RF.ReadPower(_msrPort, msrpwr, msrpwr_sim);
    FloatM     MyuserP,MyuserPim,MyuserP_sim,MyuserPim_sim;
    RF.ReadPowerUser(_msrPort,  2.403GHz,   500KHz, MyuserP,    MyuserP_sim);
    RF.ReadPowerUser(_msrPort,  2.4025GHz, 500KHz, MyuserPim,  MyuserPim_sim);

//     
    comments = "RF TimeOut";
    if (RF.Wait(_msrPort).AnyEqual(true)){ IO.Print (IO.Stdout,  comments+ " \n");}

    std::cout << endl;
    std::cout << "RBW = " << RBW << " ; IF =" << IF_FREQ << " ; IF_Bin = " << IF_BIN << endl; 

    FloatM1D Spectrum_ZoomIn = freq_domain_data_cal.Slice(1000,2400);
    
//    RF.Terminate(msrPin);
//
//                FloatM1D time_domain_PFFT = MATH.PowerFFT(time_domain_data);
//                FloatM1D time_domain_RMS = MATH.Sqrt(time_domain_PFFT/2 + 1fV);
//                FloatM1D time_domain_Pwr = CONV.VoltsTodBm(time_domain_RMS, Impd);

    //Rigth side
    IntM Bin_Lo = 1697;    
    IntM BIN = Bin_Lo+202;  //Bin1242-Bin1442
    IntM STp = BIN-10;
    IntM SPp = BIN+10;
    
    FloatM1D Spectrum_R = freq_domain_data_cal.Slice(STp,SPp);
    FloatM1D pDesire_R= MATH.Xtrm(Spectrum_R);
    Spectrum_R = freq_domain_data_cal.Slice(BIN+390,BIN+410);
    FloatM1D pIMG_R= MATH.Xtrm(Spectrum_R);
    FloatM Tx_IM3_R=pDesire_R[0] - pIMG_R[0];
    
    std::cout << endl;
//    std::cout << "=============TX2402M_IM3================="<< endl;
    std::cout << "R_side_Tx_IM3_R = " << Tx_IM3_R     << endl;
    std::cout << "R_side_Tone = "     << pDesire_R[0] << endl;
    std::cout << "R_side_IM3 = "      << pIMG_R[0]    << endl;
    
  
    //Left side
    BIN=Bin_Lo-198;
    STp=BIN-10;
    SPp=BIN+10;
    
    FloatM1D Spectrum_L = freq_domain_data_cal.Slice(STp,SPp);
    FloatM1D pDesire_L= MATH.Xtrm(Spectrum_L);
    Spectrum_L = freq_domain_data_cal.Slice(BIN-410,BIN-390);
    FloatM1D pIMG_L= MATH.Xtrm(Spectrum_L);
    FloatM Tx_IM3_L=pDesire_L[0] - pIMG_L[0];
    FloatM Tx_PWR  =pDesire_L[0];
    
    std::cout << ReadFreqName+"_L_side_Tx_IM3_L = " << Tx_IM3_L     << endl;
    std::cout << ReadFreqName+"_L_side_Tone = "     << pDesire_L[0] << endl;
    std::cout << ReadFreqName+"_L_side_IM3 = "      << pIMG_L[0]    << endl;   
    std::cout << ReadFreqName+"_MyuserP = "      << MyuserP    << endl;   
    std::cout << ReadFreqName+"_MyuserPim3 = "      << MyuserPim    << endl;   

    RF.Terminate(_srcPort);    
    RF.SetSource(_srcPort , -120dBm , _CenterFreq, RF_PERFORMANCE_HIGH_LINEARITY );

}

TMResultM TxPower_Gfsk_Binning_TEST()
{
    TMResultM localResult= TM_NOTEST;
  
    TMResultM Result= DLOG.Value(GlobalVariable_24440MHz_P_Gfsk, 7.5, 10.2,"dBm", UTL_VOID, UTL_VOID, UTL_VOID,ER_PASS);   
//    TMResultM Result= DLOG.Value(GlobalVariable_24440MHz_P_Gfsk, 7.5, 10.0,"dBm", UTL_VOID, UTL_VOID, UTL_VOID,ER_PASS);   
    DLOG.AccumulateResults(localResult, Result);

    return (localResult);
}

