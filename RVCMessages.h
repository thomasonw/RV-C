//      RVCMessages.h
//
//
//      Copyright (c) 2016, 2018 by William A. Thomason.      http://arduinoalternatorregulator.blogspot.com/
//                                                            http://smartdcgenerator.blogspot.com/
//                                                            https://github.com/thomasonw/RV-C
//                                                        
//                                                        
//              For use with  NMEA2000 lib - Kave Oy, www.kave.fi/      https://github.com/ttlappalainen/NMEA2000
//              Extends NMEA2000 lib to include RV-C messages:          http://www.rv-c.com/?q=node/75
//
//
//              This program is free software: you can redistribute it and/or modify
//              it under the terms of the GNU General Public License as published by
//              the Free Software Foundation, either version 3 of the License, or
//              (at your option) any later version.
//      
//              This program is distributed in the hope that it will be useful,
//              but WITHOUT ANY WARRANTY; without even the implied warranty of
//              MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//              GNU General Public License for more details.
//      
//              You should have received a copy of the GNU General Public License
//              along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//
//                  8/29/2016   Initial posting.  Contains a pending change to the current RV-C spec:
//                      'Charger Status2' @ 1FEA3h
//
  


#ifndef _RVCMessages_H_
#define _RVCMessages_H_

#include <N2kMsg.h>
#include <N2kMessages.h>



enum tRVCBatChrgMode  {
                            RVCDCbcm_Undefined=0,
                            RVCDCbcm_Disabled=1,
                            RVCDCbcm_Bulk=2,
                            RVCDCbcm_Absorption=3,
                            RVCDCbcm_Overcharge=4,
                            RVCDCbcm_Equalize=5,
                            RVCDCbcm_Float=6,
                            RVCDCbcm_CVCC=7,
                            RVCDCbcm_Unknown=0xFF       /* Charge Mode is an 8-bit field - all 1's indicated undefined value in J1939 CAN standard) */
                          };
                          
    
enum tRVCChrgAlg  {
                            RVCDCca_ConstantVoltage=0,
                            RVCDCca_ConstantCurrent=1,
                            RVCDCca_3Stage=2,
                            RVCDCca_2Stage=3,
                            RVCDCca_Trickle=4,
                            RVCDCca_Custom2=249,
                            RVCDCca_Custom1=250
                          };
                          
                          
enum tRVCChrgMode  {
                            RVCDCcm_Standalone=0,
                            RVCDCcm_Primary=1,
                            RVCDCcm_Secondary=2,
                            RVCDCcm_Linked=3
                          };

              


enum tRVCChrgLine {
                            RVCDCcl_line1 = 0x00,
                            RVCDCcl_line2 = 0x01,
                            RVCDCcl_na    = 0x03        /* Bit field - all 1's indicated undefined value in J1939 CAN standard) */
                          };
                          

enum tRVCChrgStatus {
                            RVCDCcs_diable = 0,
                            RVCDCcs_enable = 1,
                            RVCDCcs_start_equalize = 2
                          };

                          
enum tRVCChrgForceChrg {
                            RVCDCfc_Cancel = 0,
                            RVCDCfc_Bulk   = 1,
                            RVCDCfc_Float  = 2
                          };



   
enum tRVCBatType  {
                            RVCDCbt_Flooded=0,
                            RVCDCbt_Gel=1,
                            RVCDCbt_AGM=2,
                            RVCDCbt_LiPo=3,
                            RVCDCbt_LiFeP04=4,          /* And related variances */
                            RVCDCbt_NiCad=5,
                            RVCDCbt_NiMh=6,
                            RVCDCbt_VD01=13,            /* Vender Defined types */
                            RVCDCbt_VD02=14,
                            RVCDCbt_Unknown=0x0F        /* Battery Type is a 4-bit field - all 1's indicated undefined value in J1939 CAN standard) */
                          };
enum  tRVCGenStatus {
                            RVCGst_Stopped=0,
                            RVCGst_PreHeat=1,
                            RVCGst_Chanking=2,
                            RVCGst_Running=3,
                            RVCGst_Priming=4,
                            RVCGst_Fault=5,
                            RVCGst_EngOnly=6,           /* Engine running, Geneartor head disabled */
                            RVCGst_TestMode=7,
                            RVCGst_VoltAdjMode=8,
                            RVCGst_FaltBypass=9,
                            RVCGst_ConfigMode=10                            
                          }; 
 
 
enum tRVCGenCmd  {
                            RVCGstStop=0,
                            RVCGstStart=1,
                            RVCGstManPrime=2,
                            RVCGstManPreht=3,
                            RVCGstStartQuiet=4,         /* Start in special 'Quite Mode' if Generator supports it */
                            RVCGstEnableAuxLoad=100,    /* Watermaker, Air Compressor, AC unit, etc.. */
                            RVCGstDisableAuxLoad=101,
                            RVCGst_Unknown=0xFF      
                          };
         
         
   
enum tRVCGenStrTyp  {					                /*  Details of generator Starter configuration.  Ref RV-C for more details */
                            RVCGstStRCI=1,		        /*  Run/Crank input 	     			        */
                            RVCGstStCGSI=2,		        /*  Crank/Glow & Stop inputs 			        */
                            RVCGstStPSPS=3,		        /*  Preheat/Start input and Prime/Stop 		    */
                            RVCGstStSIO=4,		        /*  Single On/Off input 			            */
                            RVCGstStCGCA=5,		        /*  Glow, Start input with Amp Shunt monitoring */
                            RVCGstSt_Unknown=0xFF 
                          };
         
                                          
                          
  
 enum tRVCChrgType  {                                   /* PROPOSED EXTENSION - FOR INSTANCE TYPE CLASSIFCAITON ON CHARGER DGNs */
                            RVCDCct_Default=0,          /* Default value, for backwards compatability */
                            RVCDCct_ACSourced=0,
                            RVCDCct_Solar=1,
                            RVCDCct_Wind=2,
                            RVCDCct_Alternator=3,        /* Engine alternator */
                            RVCDCct_FuelCell=4,
                            RVCDCct_Water=5,
                            RVCDCct_Generator=6,
                            RVCDCct_VD01=13,            /* Vender Defined types */
                            RVCDCct_VD02=14,
                            RVCDCct_Unknown=0x0F        /* Battery Type is a 4-bit field - all 1's indicated undefined value in J1939 CAN standard) */
                          };
                           
  
  
enum tISOAckType  {                                     // See --> Acknowledgment - E800h
                            ISOat_ACK=0,
                            ISOat_NAK=1,
                            ISOat_NotAcpt=2,
                            ISOat_NotAllowed=3,
                            ISOat_FormatErr=4, 
                            ISOat_OutRange=5,
                            ISOat_PsswdReq=6,
                            ISOat_TimeReq=7, 
                            ISOat_UsrOvrd=8
                                        // 9 to 127 Reserved
                                        // 128 to 254 Command-specific responses.
                          };
 

enum tISOFMIType  {                                     // See --> ISO Failure Mode Identifier / Diagnostic Message (DM) - 1FECAh
                            ISOfmi_DVanr=0,                     // 0 Datum value above normal range
                            ISOfmi_DVbnr=1,                     // 1 Datum value below normal range
                            ISOfmi_DVer=2,                      // 2 Datum value erratic or invalid
                            ISOfmi_DVschv=3,                    // 3 Short circuit to high voltage (or complete sensor input failure)
                            ISOfmi_DVsclv=4,                    // 4 Short circuit to low voltage (or complete sensor input failure)
                            ISOfmi_DVoc=5,                      // 5 Open circuit, or output current below normal
                            ISOfmi_DVgc=6,                      // 6 Grounded circuit, or output current above normal
                            ISOfmi_DVmdnr=7,                    // 7 Mechanical device not responding
                            ISOfmi_DVdvf=8,                     // 8 Datum value showing error of frequency, pulse width, or period
                            ISOfmi_DVdur=9,                     // 9 Datum not updating at proper rate
                            ISOfmi_DVdvar=10,                   // 10 Datum value fluctuating at abnormal rate
                            ISOfmi_DVfni=11,                    // 11 Failure not identifiable
                            ISOfmi_DVbin=12,                    // 12 Bad intelligent RV-C node
                            ISOfmi_DVcr=13,                     // 13 Calibration required
                            ISOfmi_DVnota=14,                   // 14 "None of the above" (use sparingly!)
                            ISOfmi_DVdvwanr=15,                 // 15 Datum valid but above normal operational range (least severe)
                            ISOfmi_DVdvwanrm=16,                // 16 Datum valid but above normal operational range (moderately severe)
                            ISOfmi_DVdvwbnr=17,                 // 17 Datum valid but below normal operational range (least severe)
                            ISOfmi_DVdvwnbrm=18,                // 18 Datum valid but below normal operational range (moderately severe)
                            ISOfmi_DVrind=19,                   // 19 Received invalid network datum
                            /*  20 to 30 Reserved */
                            ISOfmi_DVna=31                      // 31 Failure mode not available
                          };
                          

                          
//*****************************************************************************
// Information request - EAxxh
// Input:
//  - Destion Address 
//  - Requested DGN       
// Output:
//  - N2kMsg                RV_C message ready to be send.
void  SetRVCPGNEAxx(tN2kMsg &N2kMsg, uint8_t Dest, uint32_t DGNReq);
              
inline void SetRVCDCRequestDGN(tN2kMsg &N2kMsg, uint8_t Dest, uint32_t DGNReq) {
   SetRVCPGNEAxx(N2kMsg, Dest, DGNReq);
}

bool ParseRVCPGNEAxx(const tN2kMsg &N2kMsg, uint8_t &Dest, uint32_t &DGNReq);
inline bool ParseRVCRequestDGN (const tN2kMsg &N2kMsg, uint8_t &Dest, uint32_t &DGNReq) {
  return ParseRVCPGNEAxx(N2kMsg, Dest, DGNReq);                   
}
                      




//*****************************************************************************
// DC Source Status 1 - 1FFFDh
// Input:
//  - Instance              DC Instance (bus) ID.  
//  - Device Priority       Relative ranking of DC Source
//  - DC Voltage            0..3212.5v, in 50mV steps
//  - DC Current            -2M..+2MA, in 1mA steps (0x77359400 = 0A)
// Output:
//  - N2kMsg                RV_C message ready to be send.
void SetRVCPGN1FFFD(tN2kMsg &N2kMsg, uint8_t Instance, uint8_t DevPri, uint16_t Vdc, uint32_t Adc);
              
inline void SetRVCDCSourceStatus1(tN2kMsg &N2kMsg, uint8_t Instance, uint8_t DevPri, uint16_t Vdc, uint32_t Adc) {
  SetRVCPGN1FFFD(N2kMsg,Instance, DevPri, Vdc, Adc);
}

bool ParseRVCPGN1FFFD(const tN2kMsg &N2kMsg, uint8_t &Instance, uint8_t &DevPri, uint16_t &Vdc, uint32_t &Adc);
inline bool ParseRVCDCSourceStatus1(const tN2kMsg &N2kMsg, uint8_t &Instance, uint8_t &DevPri, uint16_t &Vdc, uint32_t &Adc) {
  return ParseRVCPGN1FFFD(N2kMsg,Instance, DevPri, Vdc, Adc);                   
}



//*****************************************************************************
// DC Source Status 2 - 1FFFCh
// Input:
//  - Instance              DC Instance (bus) ID.  
//  - Device Priority       Relative ranking of DC Source
//  - Source Temperature     -273 to 1735 Deg-C  in 0.03125c steps
//  - State of Charge       Batteries: % SOC;  DC Charging sources:  Current % output.
//  - Time Remaining        Estimated number of minutes until SOC reaches 0% 
// Output:
//  - N2kMsg                RV_C message ready to be send.
void SetRVCPGN1FFFC(tN2kMsg &N2kMsg, uint8_t Instance, uint8_t DevPri, int16_t Temp, uint8_t SOC, uint16_t TR);
              
inline void SetRVCDCSourceStatus2(tN2kMsg &N2kMsg, uint8_t Instance, uint8_t DevPri, int16_t Temp, uint8_t SOC, uint16_t TR) {
  SetRVCPGN1FFFC(N2kMsg,Instance, DevPri, Temp, SOC, TR);
}

bool ParseRVCPGN1FFFC(const tN2kMsg &N2kMsg, uint8_t &Instance, uint8_t &DevPri, int16_t &Temp, uint8_t &SOC, uint16_t &TR);
inline bool ParseRVCDCSourceStatus2(const tN2kMsg &N2kMsg, uint8_t &Instance, uint8_t &DevPri, int16_t &Temp, uint8_t &SOC, uint16_t &TR) {
  return ParseRVCPGN1FFFC(N2kMsg,Instance, DevPri, Temp, SOC, TR);                   
}





//*****************************************************************************
// DC Source Status 3 - 1FFFBh
// Input:
//  - Instance              DC Instance (bus) ID.  
//  - Device Priority       Relative ranking of DC Source
//  - State of Health       % expected remaining lifetime
//  - Capacity Remaining    Current capacity / capability of battery in Ah
//  - Relative Capacity     % of current capacity vs. design specified capacity. 
//  - AC RMS Ripple         in mV
// Output:
//  - N2kMsg                RV_C message ready to be send.
void SetRVCPGN1FFFB(tN2kMsg &N2kMsg, uint8_t Instance, uint8_t DevPri, uint8_t SOH, uint16_t CapRem, uint8_t CapRemPer , uint16_t Ripple);
              
inline void SetRVCDCSourceStatus3(tN2kMsg &N2kMsg, uint8_t Instance, uint8_t DevPri, uint8_t SOH, 
                                                   uint16_t CapRem, uint8_t CapRemPer , uint16_t Ripple) {
  SetRVCPGN1FFFB(N2kMsg,Instance, DevPri, SOH, CapRem, CapRemPer, Ripple);
}

bool ParseRVCPGN1FFFB(const tN2kMsg &N2kMsg, uint8_t &Instance, uint8_t &DevPri, uint8_t &SOH, 
                                             uint16_t &CapRem, uint8_t &CapRemPer , uint16_t &Ripple);
inline bool ParseRVCDCSourceStatus3(const tN2kMsg &N2kMsg, uint8_t &Instance, uint8_t &DevPri, uint8_t &SOH, 
                                                          uint16_t &CapRem, uint8_t &CapRemPer, uint16_t &Ripple) {
  return ParseRVCPGN1FFFB(N2kMsg,Instance, DevPri, SOH, CapRem, CapRemPer, Ripple);                   
}



//*****************************************************************************
// DC Source Status 4 - 1FEC9h
// Input:
//  - Instance              DC Instance (bus) ID.  
//  - Device Priority       Relative ranking of DC Source
//  - Desired Charge Mode   Charging mode / state being requested.  
//  - Desired DC Voltage    Target voltage for chargers to deliver  0..3212.5v, in 50mV steps
//  - Desired DC Current    Target current for all chargers to deliver combined  -1600A..1612.5A, in 50mA steps (0x7D00 = 0A)
//  - Battery Type          
// Output:
//  - N2kMsg                RV_C message ready to be send.
void SetRVCPGN1FEC9(tN2kMsg &N2kMsg, uint8_t Instance, uint8_t DevPri, tRVCBatChrgMode DesCM, uint16_t DesVolt, uint16_t DesAmp , tRVCBatType BatType);
              
inline void SetRVCDCSourceStatus4(tN2kMsg &N2kMsg, uint8_t Instance, uint8_t DevPri,  tRVCBatChrgMode DesCM, uint16_t DesVolt, uint16_t DesAmp , tRVCBatType BatType) {
  SetRVCPGN1FEC9(N2kMsg,Instance, DevPri, DesCM, DesVolt, DesAmp, BatType);
}

bool ParseRVCPGN1FEC9(const tN2kMsg &N2kMsg, uint8_t &Instance, uint8_t &DevPri,  tRVCBatChrgMode &DesCM, uint16_t &DesVolt, uint16_t &DesAmp , tRVCBatType &BatType);
inline bool ParseRVCDCSourceStatus4(const tN2kMsg &N2kMsg, uint8_t &Instance, uint8_t &DevPri, tRVCBatChrgMode &DesCM, uint16_t &DesVolt, uint16_t &DesAmp , tRVCBatType &BatType) {
  return ParseRVCPGN1FEC9(N2kMsg,Instance, DevPri, DesCM, DesVolt, DesAmp, BatType);                   
}





//*****************************************************************************
// DC Source Status 5 - 1FEC8h
// Input:
//  - Instance              DC Instance (bus) ID.  
//  - Device Priority       Relative ranking of DC Source
//  - DC Voltage            High precision value in 1mV.  Useful for remote instrumentation  
//  - VDC ROC               Rate-of-change (dV/dT) in mV/s  -- 32000 = 0 mV/s
// Output:
//  - N2kMsg                RV_C message ready to be send.
void SetRVCPGN1FEC8(tN2kMsg &N2kMsg, uint8_t Instance, uint8_t DevPri, uint32_t Vdc,  uint16_t dVdT);
              
inline void SetRVCDCSourceStatus5(tN2kMsg &N2kMsg, uint8_t Instance, uint8_t DevPri, uint32_t Vdc,  uint16_t dVdT) {
  SetRVCPGN1FEC8(N2kMsg,Instance, DevPri, Vdc, dVdT);
}

bool ParseRVCPGN1FEC8(const tN2kMsg &N2kMsg, uint8_t &Instance, uint8_t &DevPri,  uint32_t &Vdc,  uint16_t &dVdT);
inline bool ParseRVCDCSourceStatus5(const tN2kMsg &N2kMsg, uint8_t &Instance, uint8_t &DevPri, uint32_t &Vdc,  uint16_t &dVdT) {
  return ParseRVCPGN1FEC8(N2kMsg,Instance, DevPri, Vdc, dVdT);                   
}





//*****************************************************************************
// DC Source Status 6 - 1FEC7h
// Input:
//  - Instance              DC Instance (bus) ID.  
//  - Device Priority       Relative ranking of DC Source
//  - HV Limit Status       Reached upper operational voltage range?
//  - HV Limit Disconnect   Safety disconnect?
//  - LV Limit Status       Reached lower operational voltage range?
//  - LV Limit Disconnect   Safety disconnect?
// Output:
//  - N2kMsg                RV_C message ready to be send.
void SetRVCPGN1FEC7(tN2kMsg &N2kMsg, uint8_t Instance, uint8_t DevPri, bool HVls, bool HVld, bool LVls, bool LVld);
              
inline void SetRVCDCSourceStatus6(tN2kMsg &N2kMsg, uint8_t Instance, uint8_t DevPri, bool HVls, bool HVld, bool LVls, bool LVld) {
  SetRVCPGN1FEC7(N2kMsg,Instance, DevPri, HVls, HVld, LVls, LVld);
}

bool ParseRVCPGN1FEC7(const tN2kMsg &N2kMsg, uint8_t &Instance, uint8_t &DevPri,  
                       bool &HVls, bool &HVld, bool &LVls, bool &LVld);
inline bool ParseRVCDCSourceStatus6(const tN2kMsg &N2kMsg, uint8_t &Instance, uint8_t &DevPri, bool &HVls, bool &HVld, bool &LVls, bool &LVld) {
  return ParseRVCPGN1FEC7(N2kMsg,Instance, DevPri, HVls, HVld, LVls, LVld);                   
}




//*****************************************************************************
// DC Disconnect Status - 1FED0h
// Input:
//  - Instance                      DC Instance (bus) ID.  
//  - Status             	    Is Circuit currently connected? 
//  - Last Command    		    What was the last command received? (TRUE = connect)   
//  - Bypass Detected               Has an external bypass occurred? 
// Output:
//  - N2kMsg                        RV_C message ready to be send.
void SetRVCPGN1FED0(tN2kMsg &N2kMsg, uint8_t Instance, bool Status, bool LastCom, bool Bypassed);
              
inline void SetRVCDCDisconnectStatus(tN2kMsg &N2kMsg, uint8_t Instance, bool Status, bool LastCom, bool Bypassed) {
  SetRVCPGN1FED0(N2kMsg,Instance, Status, LastCom, Bypassed);
}

bool ParseRVCPGN1FED0(const tN2kMsg &N2kMsg, uint8_t &Instance, bool &Status, bool &LastCom, bool &Bypassed);
inline bool ParseRVCDCDisconnectStatus(const tN2kMsg &N2kMsg, uint8_t &Instance, bool &Status, bool &LastCom, bool &Bypassed) {
  return ParseRVCPGN1FED0(N2kMsg,Instance, Status, LastCom, Bypassed);                   
}






//*****************************************************************************
// DC Disconnect Command - 1FECFh
// Input:
//  - Instance              DC Instance (bus) ID.  
//  - Command               Command  (TRUE = command to connect)
// Output:
//  - N2kMsg                RV_C message ready to be send.
void SetRVCPGN1FECF(tN2kMsg &N2kMsg, uint8_t Instance, bool Command);
              
inline void SetRVCDCDisconnectCommand(tN2kMsg &N2kMsg, uint8_t Instance, bool Command) {
  SetRVCPGN1FECF(N2kMsg,Instance,Command);
}

bool ParseRVCPGN1FECF(const tN2kMsg &N2kMsg, uint8_t &Instance, bool &Command);
inline bool ParseRVCDCDisconnectCommand(const tN2kMsg &N2kMsg, uint8_t &Instance, bool &Command) {
  return ParseRVCPGN1FECF(N2kMsg,Instance,Command);                   
}





//*****************************************************************************
// Generator Status 1 - 1FFDCh
// Input:
//  - Status                        Stopped, Started, Running, etc.
//  - Engine Runtime                Total minutes logged on engine
//  - Engine Load                   Current engine load % vs total capacity
//  - Start battery voltage
// Output:
//  - N2kMsg                        RV_C message ready to be send.
void SetRVCPGN1FFDC(tN2kMsg &N2kMsg, tRVCGenStatus Status, uint32_t Minutes, uint8_t Load, uint16_t SBVdc);
inline void SetRVCGeneratorStatus1(tN2kMsg &N2kMsg, tRVCGenStatus Status, uint32_t Minutes, uint8_t Load, uint16_t SBVdc) {
  SetRVCPGN1FFDC(N2kMsg,Status,Minutes,Load,SBVdc);
}

bool ParseRVCPGN1FFDC(const tN2kMsg &N2kMsg, tRVCGenStatus &Status, uint32_t &Minutes, uint8_t &Load, uint16_t &SBVdc);
inline bool ParseRVCGeneratorStatus1(const tN2kMsg &N2kMsg, tRVCGenStatus &Status, uint32_t &Minutes, uint8_t &Load, uint16_t &SBVdc) {
  return ParseRVCPGN1FFDC(N2kMsg,Status,Minutes,Load,SBVdc);                   
}



//*****************************************************************************
// Generator Status 2 - 1FFDBh
// Input:
//  - Overtemp Switch active
//  - Low Oil Pressure swtich active
//  - Low Oil level swtich active
//  - Caution Light
//  - Tempeture                     -40..210 in deg-C, in 1C steps
//  - Oil Pressure                  0..1000 kPa in 4Pa steps (0..145.04PSI)
//  - RPM                           0..8191RPM in 0.125 RPM steps
//  - Fuel Rate                     0..3212.5 LPH in 0.05lph steps
// Output:
//  - N2kMsg                        RV_C message ready to be send.

void SetRVCPGN1FFDB(tN2kMsg &N2kMsg, bool OvrTemp, bool LowOP, bool LowOL, bool CautLght, uint8_t EngTemp, uint16_t RPM, uint16_t FFlow);
inline void SetRVCGeneratorStatus2(tN2kMsg &N2kMsg, bool OvrTemp, bool LowOP, bool LowOL, bool CautLght, uint8_t EngTemp, uint16_t RPM, uint16_t FFlow) {
  SetRVCPGN1FFDB(N2kMsg,OvrTemp,LowOP,LowOL,CautLght,EngTemp,RPM,FFlow);
}

bool ParseRVCPGN1FFDB(const tN2kMsg &N2kMsg, bool &OvrTemp, bool &LowOP, bool &LowOL, bool &CautLght, uint8_t &EngTemp, uint16_t &RPM, uint16_t &FFlow);
inline bool ParseRVCGeneratorStatus2(const tN2kMsg &N2kMsg, bool &OvrTemp, bool &LowOP, bool &LowOL, bool &CautLght, uint8_t &EngTemp, uint16_t &RPM, uint16_t &FFlow) {
  return ParseRVCPGN1FFDB(N2kMsg,OvrTemp,LowOP,LowOL,CautLght,EngTemp,RPM,FFlow);                  
}




//*****************************************************************************
// Generator Command  -  1FFDAh
// Input:
//  - Command                       Start, Stop, Prime, etc.
// Output:
//  - N2kMsg                        RV_C message ready to be send.
void SetRVCPGN1FFDA(tN2kMsg &N2kMsg, tRVCGenCmd Command);
inline void SetRVCGeneratorCommand(tN2kMsg &N2kMsg, tRVCGenCmd Command) {
  SetRVCPGN1FFDA(N2kMsg,Command);
}

bool ParseRVCPGN1FFDA(const tN2kMsg &N2kMsg, tRVCGenCmd &Command);
inline bool ParseRVCGeneratorCommand(const tN2kMsg &N2kMsg, tRVCGenCmd &Command) {
  return ParseRVCPGN1FFDA(N2kMsg,Command);                  
}



//*****************************************************************************
// Generator Starter Configuration  -  1FFD9h
// Input:
//  - Generator Type                Method for how Start/Stop is controlled
//  - Generator pre-crank time      0..250 Preheat time, in seconds 
//  - Generator max crank time      0..250 Manimum time in seconds to engage starter in one attempt
//  - Generator Stop Time           0.250  Time in seconds stop-signal is active to assure engine is stopped.                        Start, Stop, Prime, etc.
// Output:
//  - N2kMsg                        RV_C message ready to be send.
void SetRVCPGN1FFD9(tN2kMsg &N2kMsg, tRVCGenStrTyp GenType, uint8_t PreCrank, uint8_t MaxCrank, uint8_t Stop);
inline void SetRVCGeneratorStarterConfig(tN2kMsg &N2kMsg, tRVCGenStrTyp GenType, uint8_t PreCrank, uint8_t MaxCrank, uint8_t Stop) {
  SetRVCPGN1FFD9(N2kMsg,GenType,PreCrank,MaxCrank,Stop);
}

bool ParseRVCPGN1FFD9(const tN2kMsg &N2kMsg, tRVCGenStrTyp &GenType, uint8_t &PreCrank, uint8_t &MaxCrank, uint8_t &Stop);
inline bool ParseRVCGeneratorStarterConfig(const tN2kMsg &N2kMsg, tRVCGenStrTyp &GenType, uint8_t &PreCrank, uint8_t &MaxCrank, uint8_t &Stop) {
  return ParseRVCPGN1FFD9(N2kMsg,GenType,PreCrank,MaxCrank,Stop);                  
}




//*****************************************************************************
// Generator Starter Configuration Command -  1FFD8h
// Input:
//  - Generator Type                Method for how Start/Stop is controlled
//  - Generator pre-crank time      0..250 Preheat time, in seconds 
//  - Generator max crank time      0..250 Manimum time in seconds to engage starter in one attempt
//  - Generator Stop Time           0.250  Time in seconds stop-signal is active to assure engine is stopped.                        Start, Stop, Prime, etc.
// Output:
//  - N2kMsg                        RV_C message ready to be send.
void SetRVCPGN1FFD9(tN2kMsg &N2kMsg, tRVCGenStrTyp GenType, uint8_t PreCrank, uint8_t MaxCrank, uint8_t Stop);
inline void SetRVCGeneratorStarterConfigCommand(tN2kMsg &N2kMsg, tRVCGenStrTyp GenType, uint8_t PreCrank, uint8_t MaxCrank, uint8_t Stop) {
  SetRVCPGN1FFD9(N2kMsg,GenType,PreCrank,MaxCrank,Stop);
}

bool ParseRVCPGN1FFD9(const tN2kMsg &N2kMsg, tRVCGenStrTyp &GenType, uint8_t &PreCrank, uint8_t &MaxCrank, uint8_t &Stop);
inline bool ParseRVCGeneratorStarterConfigCommand(const tN2kMsg &N2kMsg, tRVCGenStrTyp &GenType, uint8_t &PreCrank, uint8_t &MaxCrank, uint8_t &Stop) {
  return ParseRVCPGN1FFD9(N2kMsg,GenType,PreCrank,MaxCrank,Stop);                  
}


                         





//*****************************************************************************
// Charger Status - 1FFC7h
// Input:
//  - Type                          AC Charger, DC Generators, Alternator, Solar, etc.  (PROPOSED EXTENSION)
//  - Instance                      Instance of charger 0..13
//  - Charge Voltage                0..3212.5v, in 50mV steps
//  - Charge Current                -2M..+2MA, in 1mA steps (0x77359400 = 0A)
//  - % max current
//  - Operating State               (Bulk, float, etc)
//  - Default PO state
//  - Auto Recharge
//  - Force Charged 
// Output:
//  - N2kMsg                        RV_C message ready to be send.
void SetRVCPGN1FFC7(tN2kMsg &N2kMsg, tRVCChrgType Type, uint8_t Instance, uint16_t CVdc, uint16_t CAdc, uint8_t PerMax,
                    tRVCBatChrgMode State, bool EnableAtPO, bool AutoRechg, tRVCChrgForceChrg ForcedChrg);
              
inline void SetRVCChargerStatus(tN2kMsg &N2kMsg, tRVCChrgType  Type, uint8_t Instance, uint16_t CVdc, uint16_t CAdc, uint8_t PerMax,
                                  tRVCBatChrgMode State, bool EnableAtPO, bool AutoRechg, tRVCChrgForceChrg ForcedChrg) {
  SetRVCPGN1FFC7(N2kMsg,Type,Instance,CVdc,CAdc,PerMax,State,EnableAtPO,AutoRechg,ForcedChrg);
}

bool ParseRVCPGN1FFC7(const tN2kMsg &N2kMsg, tRVCChrgType  &Type, uint8_t &Instance, uint16_t &CVdc, uint16_t &CAdc, uint8_t &PerMax,
                            tRVCBatChrgMode &State, bool &EnableAtPO, bool &AutoRechg, tRVCChrgForceChrg &ForcedChrg);
inline bool ParseRVCChargerStatus(const tN2kMsg &N2kMsg, tRVCChrgType  &Type, uint8_t &Instance, uint16_t &CVdc, uint16_t &CAdc, uint8_t &PerMax,
                            tRVCBatChrgMode &State, bool &EnableAtPO, bool &AutoRechg, tRVCChrgForceChrg &ForcedChrg) {
  return ParseRVCPGN1FFC7(N2kMsg,Type,Instance,CVdc,CAdc,PerMax,State,EnableAtPO,AutoRechg,ForcedChrg);                   
}



//*****************************************************************************
// Charger Status2 - 1FEA3h  
// Input:
//  - Type                          AC Charger, Alternator, etc.
//  - Instance                      Instance of charger 0..13
//  - DC Source Instance            DC Instance (bus) ID associated with
//  - Device Priority               Relative ranking of DC charging Source
//  - DC Voltage                    0..3212.5v, in 50mV steps
//  - DC Current                    -1600..1612.5a, in 50mA steps (0x7D00 = 0A)
//  - Temperature                   -40..210 in deg-C, in 1C steps
// Output:
//  - N2kMsg                        RV_C message ready to be send.
void SetRVCPGN1FEA3(tN2kMsg &N2kMsg, tRVCChrgType Type, uint8_t ChrgInst, uint8_t DCInst, uint8_t DevPri, uint16_t Vdc, uint16_t Adc, uint8_t Temp);
              
inline void SetRVCChargerStatus2(tN2kMsg &N2kMsg, tRVCChrgType Type, uint8_t ChrgInst, uint8_t DCInst, uint8_t DevPri, uint16_t Vdc, uint16_t Adc, uint8_t Temp) {
  SetRVCPGN1FEA3(N2kMsg,Type,ChrgInst,DCInst,DevPri,Vdc,Adc,Temp);
}

bool ParseRVCPGN1FEA3(const tN2kMsg &N2kMsg, tRVCChrgType &Type, uint8_t &ChrgInst, uint8_t &DCInst, uint8_t &DevPri, uint16_t &Vdc, uint16_t &Adc, uint8_t &Temp);
inline bool ParseRVCChargerStatus2(const tN2kMsg &N2kMsg, tRVCChrgType &Type, uint8_t &ChrgInst, uint8_t &DCInst, uint8_t &DevPri, uint16_t &Vdc, uint16_t &Adc, uint8_t &Temp) {
  return ParseRVCPGN1FEA3(N2kMsg,Type,ChrgInst,DCInst,DevPri,Vdc,Adc,Temp);                   
}
                   
                                 

//*****************************************************************************
// Charger Command - 1FFC5h
// Input:
//  - Type                          AC Charger, Alternator, etc.  (PROPOSED EXTENSION)
//  - Instance                      Instance of charger 0..13
//  - Status
//  - Default PO state
//  - Auto Recharge
//  - Force Charged  
// Output:
//  - N2kMsg                RV_C message ready to be send.
void SetRVCPGN1FFC5(tN2kMsg &N2kMsg, tRVCChrgType Type, uint8_t Instance, tRVCChrgStatus ChrgStat,  
                       bool EnableAtPO, bool AutoRechg, tRVCChrgForceChrg ForcedChrg);
              
inline void SetRVCChargerCommand(tN2kMsg &N2kMsg, tRVCChrgType Type, uint8_t Instance, tRVCChrgStatus ChrgStat,  
                                            bool EnableAtPO, bool AutoRechg, tRVCChrgForceChrg ForcedChrg) {
  SetRVCPGN1FFC5(N2kMsg,Type,Instance,ChrgStat,EnableAtPO,AutoRechg,ForcedChrg);
}

bool ParseRVCPGN1FFC5(const tN2kMsg &N2kMsg, tRVCChrgType &Type, uint8_t &Instance, tRVCChrgStatus &ChrgStat, 
                                            bool &EnableAtPO, bool &AutoRechg, tRVCChrgForceChrg &ForcedChrg);
inline bool ParseRVCChargerCommand(const tN2kMsg &N2kMsg, tRVCChrgType &Type, uint8_t &Instance, tRVCChrgStatus &ChrgStat,  
                                            bool &EnableAtPO, bool &AutoRechg, tRVCChrgForceChrg &ForcedChrg) {
  return ParseRVCPGN1FFC5(N2kMsg,Type,Instance,ChrgStat,EnableAtPO,AutoRechg,ForcedChrg);                 
}



//*****************************************************************************
// Charger Configuration Status - 1FFC6h
// Input:
//  - Type                          AC Charger, Alternator, etc.  (PROPOSED EXTENSION)
//  - Instance                      Instance of charger 0..13
//  - Charging Algorithum  
//  - Controller Mode
//  - Battery Sensor Present
//  - Charger AC Line               Line 1 or 2 (AC Chargers only)
//  - Linkage Mode
//  - Battery Type
//  - Battery Bank Size             0..65,530 Ah, 1Ah increments
//  - Maximum charging current      0..250, 1A increments
// Output:
//  - N2kMsg                    RV_C message ready to be send.
void SetRVCPGN1FFC6(tN2kMsg &N2kMsg, tRVCChrgType Type, uint8_t Instance, tRVCChrgAlg  ChrgAlg,  tRVCChrgMode  ChrgMode, 
                       bool BatSense, tRVCChrgLine Line, bool Linked, tRVCBatType BatType,  uint16_t BatSize, uint8_t MaxAmps);
              
inline void SetRVCChargerConfigStatus(tN2kMsg &N2kMsg, tRVCChrgType Type, uint8_t Instance, tRVCChrgAlg  ChrgAlg,  tRVCChrgMode  ChrgMode, 
                    bool BatSense, tRVCChrgLine Line, bool Linked, tRVCBatType BatType,  uint16_t BatSize, uint8_t MaxAmps) {
  SetRVCPGN1FFC6(N2kMsg,Type,Instance,ChrgAlg,ChrgMode,BatSense,Line,Linked,BatType,BatSize,MaxAmps);
}

bool ParseRVCPGN1FFC6(const tN2kMsg &N2kMsg, tRVCChrgType &Type, uint8_t &Instance, tRVCChrgAlg  &ChrgAlg,  tRVCChrgMode  &ChrgMode, 
                               bool &BatSense, tRVCChrgLine &Line, bool &Linked, tRVCBatType &BatType,  uint16_t &BatSize, uint8_t &MaxAmps);
inline bool ParseRVCChargerConfigStatus(const tN2kMsg &N2kMsg, tRVCChrgType &Type, uint8_t &Instance, tRVCChrgAlg &ChrgAlg,  tRVCChrgMode &ChrgMode, 
                                         bool &BatSense, tRVCChrgLine &Line, bool &Linked, tRVCBatType &BatType,  uint16_t &BatSize, uint8_t &MaxAmps) {
  return ParseRVCPGN1FFC6(N2kMsg,Type,Instance,ChrgAlg,ChrgMode,BatSense,Line,Linked,BatType,BatSize,MaxAmps);                   
}


//*****************************************************************************
// Charger Configuration Status2 - 1FF96h
// Input:
//  - Type                          AC Charger, Alternator, etc.  (PROPOSED EXTENSION)
//  - Instance                      Instance of charger 0..13
//  - Max Charge Current %
//  - Max AC current %              Of attached line      (AC Chargers only) 
//  - Shore Breaker Size            0..250, 1A increments (AC Chargers only)
//  - Default Batt Temp
//  - Recharge Voltage              0..3212.5v, in 50mV steps
// Output:
//  - N2kMsg                        RV_C message ready to be send.
void SetRVCPGN1FF96(tN2kMsg &N2kMsg, tRVCChrgType Type, uint8_t Instance, uint8_t PerMaxAmps, uint8_t PerMaxShore, uint8_t ShorBr, uint8_t DefBatTemp, uint16_t RchgVolt);
              
inline void SetRVCChargerConfigStatus2(tN2kMsg &N2kMsg, tRVCChrgType Type, uint8_t Instance, uint8_t PerMaxAmps, uint8_t PerMaxShore, uint8_t ShorBr, uint8_t DefBatTemp, uint16_t RchgVolt) {
  SetRVCPGN1FF96(N2kMsg,Type,Instance,PerMaxAmps,PerMaxShore,ShorBr,DefBatTemp,RchgVolt);
}

bool ParseRVCPGN1FF96(const tN2kMsg &N2kMsg, tRVCChrgType &Type, uint8_t &Instance, uint8_t &PerMaxAmps, uint8_t &PerMaxShore, uint8_t &ShorBr, uint8_t &DefBatTemp, uint16_t &RchgVolt);
inline bool ParseRVCChargerConfigStatus2(const tN2kMsg &N2kMsg, tRVCChrgType &Type, uint8_t &Instance, uint8_t &PerMaxAmps, uint8_t &ShorBr, uint8_t &PerMaxShore, uint8_t &DefBatTemp, uint16_t &RchgVolt) {
  return ParseRVCPGN1FF96(N2kMsg,Type,Instance,PerMaxAmps,PerMaxShore,ShorBr,DefBatTemp,RchgVolt);                   
}


//*****************************************************************************
// Charger Configuration Status3 - 1FECCh
// Input:
//  - Type                          AC Charger, Alternator, etc.  (PROPOSED EXTENSION)
//  - Instance                      Instance of charger 0..13
//  - Bulk Voltage                  0..3212.5v, in 50mV steps
//  - Absorption Voltage            0..3212.5v, in 50mV steps
//  - Float Voltage                 0..3212.5v, in 50mV steps
//  - Temp Comp                     mV/K
// Output:
//  - N2kMsg                        RV_C message ready to be send.
void SetRVCPGN1FECC(tN2kMsg &N2kMsg, tRVCChrgType Type, uint8_t Instance, uint16_t BulkV, uint16_t AbsorbV, uint16_t FloatV, uint8_t TempComp);
              
inline void SetRVCChargerConfigStatus3(tN2kMsg &N2kMsg, tRVCChrgType Type, uint8_t Instance, uint16_t BulkV, uint16_t AbsorbV, uint16_t FloatV, uint8_t TempComp) {
  SetRVCPGN1FECC(N2kMsg,Type,Instance,BulkV,AbsorbV,FloatV,TempComp);
}

bool ParseRVCPGN1FECC(const tN2kMsg &N2kMsg, tRVCChrgType &Type, uint8_t &Instance, uint16_t &BulkV, uint16_t &AbsorbV, uint16_t &FloatV, uint8_t &TempComp);
inline bool ParseRVCChargerConfigStatus3(const tN2kMsg &N2kMsg, tRVCChrgType &Type, uint8_t &Instance, uint16_t &BulkV, uint16_t &AbsorbV, uint16_t &FloatV, uint8_t &TempComp) {
  return ParseRVCPGN1FECC(N2kMsg,Type,Instance,BulkV,AbsorbV,FloatV,TempComp);                   
}


//*****************************************************************************
// Charger Configuration Status4 - 1FEBFh
// Input:
//  - Type                          AC Charger, Alternator, etc.  (PROPOSED EXTENSION)
//  - Instance                      Instance of charger 0..13
//  - Bulk Time                     0..65,530min in 1min steps
//  - Absorption Time               0..65,530min in 1min steps
//  - Float Time                    0..65,530min in 1min steps
// Output:
//  - N2kMsg                        RV_C message ready to be send.
void SetRVCPGN1FEBF(tN2kMsg &N2kMsg, tRVCChrgType Type, uint8_t Instance, uint16_t BulkT, uint16_t AbsorbT, uint16_t FloatT);
              
inline void SetRVCChargerConfigStatus4(tN2kMsg &N2kMsg, tRVCChrgType Type, uint8_t Instance, uint16_t BulkT, uint16_t AbsorbT, uint16_t FloatT) {
  SetRVCPGN1FEBF(N2kMsg,Type,Instance,BulkT,AbsorbT,FloatT);
}

bool ParseRVCPGN1FEBF(const tN2kMsg &N2kMsg, tRVCChrgType &Type, uint8_t &Instance, uint16_t &BulkT, uint16_t &AbsorbT, uint16_t &FloatT);
inline bool ParseRVCChargerConfigStatus4(const tN2kMsg &N2kMsg, tRVCChrgType &Type, uint8_t &Instance, uint16_t &BulkT, uint16_t &AbsorbT, uint16_t &FloatT) {
  return ParseRVCPGN1FEBF(N2kMsg,Type,Instance,BulkT,AbsorbT,FloatT);                   
}


//*****************************************************************************
// Charger Configuration Command - 1FFC4h
// Input:
//  - Type                          AC Charger, Alternator, etc.  (PROPOSED EXTENSION)
//  - Instance                      Instance of charger 0..13
//  - Charging Algorithm  
//  - Controller Mode
//  - Battery Sensor Present
//  - Charger AC Line               Line 1 or 2 (AC Chargers only)
//  - Linkage Mode
//  - Battery Bank Size             0..65,530 Ah, 1Ah increments
//  - Battery Type
//  - Maximum charging current      0..250, 1A increments
// Output:
//  - N2kMsg                        RV_C message ready to be send.
void SetRVCPGN1FFC4(tN2kMsg &N2kMsg, tRVCChrgType Type, uint8_t Instance, tRVCChrgAlg  ChrgAlg,  tRVCChrgMode  ChrgMode, 
                       bool BatSense, tRVCChrgLine Line, bool Linked,  tRVCBatType BatType,  uint16_t BatSize, uint8_t MaxAmps);
              
inline void SetRVCChargerConfigCommand(tN2kMsg &N2kMsg, tRVCChrgType Type, uint8_t Instance, tRVCChrgAlg  ChrgAlg,  tRVCChrgMode  ChrgMode, 
                    bool BatSense, tRVCChrgLine Line, bool Linked,  tRVCBatType BatType,  uint16_t BatSize, uint8_t MaxAmps) {
  SetRVCPGN1FFC4(N2kMsg,Type,Instance,ChrgAlg,ChrgMode,BatSense,Line, Linked,BatType,BatSize,MaxAmps);
}

bool ParseRVCPGN1FFC4(const tN2kMsg &N2kMsg, tRVCChrgType &Type, uint8_t &Instance, tRVCChrgAlg  &ChrgAlg,  tRVCChrgMode  &ChrgMode, 
                               bool &BatSense, tRVCChrgLine &Line, bool &Linked,  tRVCBatType &BatType,  uint16_t &BatSize, uint8_t &MaxAmps);
inline bool ParseRVCChargerConfigCommand(const tN2kMsg &N2kMsg, tRVCChrgType &Type, uint8_t &Instance, tRVCChrgAlg  &ChrgAlg,  tRVCChrgMode  &ChrgMode, 
                                         bool &BatSense, tRVCChrgLine &Line, bool &Linked,  tRVCBatType &BatType,  uint16_t &BatSize, uint8_t &MaxAmps) {
  return ParseRVCPGN1FFC4(N2kMsg,Type,Instance,ChrgAlg,ChrgMode,BatSense,Line, Linked,BatType,BatSize,MaxAmps);                   
}


//*****************************************************************************
// Charger Configuration Command2 - 1FF95h
// Input:
//  - Type                          AC Charger, Alternator, etc.  (PROPOSED EXTENSION)
//  - Instance                      Instance of charger 0..13
//  - Max Charge Current %
//  - Max AC current %              Of attached line      (AC Chargers only) 
//  - Shore Breaker Size            0..250, 1A increments (AC Chargers only)
//  - Default Batt Temp
//  - Recharge Voltage              0..3212.5v, in 50mV steps
// Output:
//  - N2kMsg                        RV_C message ready to be send.
void SetRVCPGN1FF95(tN2kMsg &N2kMsg, tRVCChrgType Type, uint8_t Instance, uint8_t PerMaxAmps, uint8_t PerMaxShore, uint8_t DefBatTemp, uint16_t RchgVolt);
              
inline void SetRVCChargerConfigCommand2(tN2kMsg &N2kMsg, tRVCChrgType Type, uint8_t Instance, uint8_t PerMaxAmps, uint8_t PerMaxShore, uint8_t DefBatTemp, uint16_t RchgVolt) {
  SetRVCPGN1FF95(N2kMsg,Type,Instance,PerMaxAmps,PerMaxShore,DefBatTemp,RchgVolt);
}

bool ParseRVCPGN1FF95(const tN2kMsg &N2kMsg, tRVCChrgType &Type, uint8_t &Instance, uint8_t &PerMaxAmps, uint8_t &PerMaxShore, uint8_t &DefBatTemp, uint16_t &RchgVolt);
inline bool ParseRVCChargerConfigCommand2(const tN2kMsg &N2kMsg, tRVCChrgType &Type, uint8_t &Instance, uint8_t &PerMaxAmps, uint8_t &PerMaxShore, uint8_t &DefBatTemp, uint16_t &RchgVolt) {
  return ParseRVCPGN1FF95(N2kMsg,Type,Instance,PerMaxAmps,PerMaxShore,DefBatTemp,RchgVolt);                   
}



//*****************************************************************************
// Charger Configuration Command3 - 1FECBh
// Input:
//  - Type                          AC Charger, Alternator, etc.  (PROPOSED EXTENSION)
//  - Instance                      Instance of charger 0..13
//  - Bulk Voltage                  0..3212.5v, in 50mV steps
//  - Absorption Voltage            0..3212.5v, in 50mV steps
//  - Float Voltage                 0..3212.5v, in 50mV steps
//  - Temp Comp                     mV/K
// Output:
//  - N2kMsg                        RV_C message ready to be send.
void SetRVCPGN1FECB(tN2kMsg &N2kMsg, tRVCChrgType Type, uint8_t Instance, uint16_t BulkV, uint16_t AbsorbV, uint16_t FloatV, uint8_t TempComp);
              
inline void SetRVCChargerConfigCommand3(tN2kMsg &N2kMsg, tRVCChrgType Type, uint8_t Instance, uint16_t BulkV, uint16_t AbsorbV, uint16_t FloatV, uint8_t TempComp) {
  SetRVCPGN1FECB(N2kMsg,Type,Instance,BulkV,AbsorbV,FloatV,TempComp);
}

bool ParseRVCPGN1FECB(const tN2kMsg &N2kMsg, tRVCChrgType &Type, uint8_t &Instance, uint16_t &BulkV, uint16_t &AbsorbV, uint16_t &FloatV, uint8_t &TempComp);
inline bool ParseRVCChargerConfigCommand3(const tN2kMsg &N2kMsg, tRVCChrgType &Type, uint8_t &Instance, uint16_t &BulkV, uint16_t &AbsorbV, uint16_t &FloatV, uint8_t &TempComp) {
  return ParseRVCPGN1FECB(N2kMsg,Type,Instance,BulkV,AbsorbV,FloatV,TempComp);                   
}


//*****************************************************************************
// Charger Configuration Command4 - 1FEBEh
// Input:
//  - Type                          AC Charger, Alternator, etc.  (PROPOSED EXTENSION)
//  - Instance                      Instance of charger 0..13
//  - Bulk Time                     0..65,530min in 1min steps
//  - Absorption Time               0..65,530min in 1min steps
//  - Float Time                    0..65,530min in 1min steps
// Output:
//  - N2kMsg                 RV_C message ready to be send.
void SetRVCPGN1FEBE(tN2kMsg &N2kMsg, tRVCChrgType Type, uint8_t Instance, uint16_t BulkT, uint16_t AbsorbT, uint16_t FloatT);
              
inline void SetRVCChargerConfigCommand4(tN2kMsg &N2kMsg, tRVCChrgType Type, uint8_t Instance, uint16_t BulkT, uint16_t AbsorbT, uint16_t FloatT) {
  SetRVCPGN1FEBE(N2kMsg,Type,Instance,BulkT,AbsorbT,FloatT);
}

bool ParseRVCPGN1FEBE(const tN2kMsg &N2kMsg, tRVCChrgType &Type, uint8_t &Instance, uint16_t &BulkT, uint16_t &AbsorbT, uint16_t &FloatT);
inline bool ParseRVCChargerConfigCommand4(const tN2kMsg &N2kMsg, tRVCChrgType &Type, uint8_t &Instance, uint16_t &BulkT, uint16_t &AbsorbT, uint16_t &FloatT) {
  return ParseRVCPGN1FEBE(N2kMsg,Type,Instance,BulkT,AbsorbT,FloatT);                   
}


//*****************************************************************************
// Charger Equalization Status - 1FF99h
// Input:
//  - Type                          AC Charger, Alternator, etc.  (PROPOSED EXTENSION)
//  - Instance                      Instance of charger 0..13
//  - Time Remaining                0..65,530min in 1min steps
//  - Pre-Charging
// Output:
//  - N2kMsg                        RV_C message ready to be send.
void SetRVCPGN1FF99(tN2kMsg &N2kMsg, tRVCChrgType Type, uint8_t Instance, uint16_t Time, bool PreChrg);
              
inline void SetRVCChargerEqualStatus(tN2kMsg &N2kMsg, tRVCChrgType Type, uint8_t Instance, uint16_t Time, bool PreChrg) {
  SetRVCPGN1FF99(N2kMsg,Type,Instance,Time,PreChrg);
}

bool ParseRVCPGN1FF99(const tN2kMsg &N2kMsg, tRVCChrgType &Type, uint8_t &Instance, uint16_t &Time, bool &PreChrg);
inline bool ParseRVCChargerEqualStatus(const tN2kMsg &N2kMsg, tRVCChrgType &Type, uint8_t &Instance, uint16_t &Time, bool &PreChrg) {
  return ParseRVCPGN1FF99(N2kMsg,Type,Instance,Time,PreChrg);
}


//*****************************************************************************
// Charger Equalization Configuration Status - 1FF98h
// Input:
//  - Type                          AC Charger, Alternator, etc.  (PROPOSED EXTENSION)
//  - Instance                      Instance of charger 0..13
//  - Equalization Voltage          0..3212.5v, in 50mV steps
//  - Equalization Time             0..65,530min in 1min steps
// Output:
//  - N2kMsg                        RV_C message ready to be send.
void SetRVCPGN1FF98(tN2kMsg &N2kMsg, tRVCChrgType Type, uint8_t Instance, uint16_t Volts, uint16_t Time);
              
inline void SetRVCChargerEqualConfigStatus(tN2kMsg &N2kMsg, tRVCChrgType Type, uint8_t Instance, uint16_t Volts, uint16_t Time) {
  SetRVCPGN1FF98(N2kMsg,Type,Instance,Volts,Time);
}

bool ParseRVCPGN1FF98(const tN2kMsg &N2kMsg, tRVCChrgType &Type, uint8_t &Instance, uint16_t &Volts, uint16_t &Time);
inline bool ParseRVCChargerEqualConfigStatus(const tN2kMsg &N2kMsg, tRVCChrgType &Type, uint8_t &Instance, uint16_t &Volts, uint16_t &Time) {
  return ParseRVCPGN1FF98(N2kMsg,Type,Instance,Volts,Time);
}



//*****************************************************************************
// Charger Equalization Configuration Command - 1FF97h
// Input:
//  - Type                          AC Charger, Alternator, etc.  (PROPOSED EXTENSION)
//  - Instance                      Instance of charger 0..13
//  - Equalization Voltage          0..3212.5v, in 50mV steps
//  - Equalization Time             0..65,530min in 1min steps
// Output:
//  - N2kMsg                        RV_C message ready to be send.
void SetRVCPGN1FF97(tN2kMsg &N2kMsg, tRVCChrgType Type, uint8_t Instance, uint16_t Volts, uint16_t Time);
              
inline void SetRVCChargerEqualConfigStatusCommand(tN2kMsg &N2kMsg, tRVCChrgType Type, uint8_t Instance, uint16_t Volts, uint16_t Time) {
  SetRVCPGN1FF97(N2kMsg,Type,Instance,Volts,Time);
}

bool ParseRVCPGN1FF97(const tN2kMsg &N2kMsg, tRVCChrgType &Type, uint8_t &Instance, uint16_t &Volts, uint16_t &Time);
inline bool ParseRVCChargerEqualConfigCommand(const tN2kMsg &N2kMsg, tRVCChrgType &Type, uint8_t &Instance, uint16_t &Volts, uint16_t &Time) {
  return ParseRVCPGN1FF97(N2kMsg,Type,Instance,Volts,Time);
}





//*****************************************************************************
// Terminal - 17E00h
// Input:
//  - Source / Destination
//  - Count                     0..8
//  - Characters                Buffer with up to 8 characters
// Output:
//  - N2kMsg                    RV_C message ready to be send.
void SetRVCPGN17E00(tN2kMsg &N2kMsg, uint8_t Destination, int Count, char *Characters);

              
inline void SetRVCPGNTerminal(tN2kMsg &N2kMsg, uint8_t Destination, int Count, char *Characters) {
  SetRVCPGN17E00(N2kMsg,Destination,Count,Characters);
}

bool ParseRVCPGN17E00(const tN2kMsg &N2kMsg, uint8_t &Source, int &Count, char Characters[8]);

inline bool ParseRVCPGNTerminal(const tN2kMsg &N2kMsg, uint8_t &Source, int &Count, char Characters[8]) {
  return ParseRVCPGN17E00(N2kMsg,Source,Count,Characters);
}








//*****************************************************************************
// ISO Diagnostics Message - 1FECAh
// Input:
//  - On / Off
//  - Active / Standby
//  - DSA                       Default Source Address (Standard fault codes) 
//  - SPN                       Service Point Number  (Device Specific)
//  - FMI                       Failure Mode Identifier      
//  - Occurrence Count
//  - DSA Extension
//  - Bank Select
// Output:
//  - N2kMsg                    RV_C message ready to be send.
void SetISOPGN1FECA(tN2kMsg &N2kMsg, bool On, bool Active, bool Red, bool Yellow,  uint8_t DSA,
                    uint32_t SPN, tISOFMIType FMI, uint8_t Count, uint8_t DSA_ext, uint8_t Bank);
              
inline void SetISODiagnosticsMessage(tN2kMsg &N2kMsg, bool On, bool Active, bool Red, bool Yellow, uint8_t DSA, 
                          uint32_t SPN, tISOFMIType FMI, uint8_t Count, uint8_t DSA_ext, uint8_t Bank) {
  SetISOPGN1FECA(N2kMsg,On,Active,Red,Yellow,DSA,SPN,FMI,Count,DSA_ext,Bank);
}

bool ParseISOPGN1FECA(const tN2kMsg &N2kMsg, bool &On, bool &Active, bool &Red, bool &Yellow,  uint8_t &DSA,
                            uint32_t &SPN, tISOFMIType &FMI, uint8_t &Count, uint8_t &DSA_ext, uint8_t &Bank);

inline bool ParseISODiagnosticsMessage(const tN2kMsg &N2kMsg, bool &On, bool &Active, bool &Red, bool &Yellow,  uint8_t &DSA,
                            uint32_t &SPN, tISOFMIType &FMI, uint8_t &Count, uint8_t &DSA_ext, uint8_t &Bank) {
  return ParseISOPGN1FECA(N2kMsg,On,Active,Red,Yellow,DSA,SPN,FMI,Count,DSA_ext,Bank);
}











#endif  //_RVCMessages_H_

