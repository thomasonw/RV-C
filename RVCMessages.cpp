//  RVCMessages.cpp
//
//
//      Copyright (c) 2016, 2018, 2020 by William A. Thomason.http://arduinoalternatorregulator.blogspot.com/
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
//
  


#include "RVCMessages.h"




//*****************************************************************************
// Information request - EAxxh
void  SetRVCPGNEAxx(tN2kMsg &N2kMsg, uint8_t Dest, uint32_t DGNReq){
  
    N2kMsg.SetPGN(0xE800 | Dest);
    N2kMsg.Priority=6;
    N2kMsg.Add3ByteInt(DGNReq);  
}
              
bool ParseRVCPGNEAxx(const tN2kMsg &N2kMsg, uint8_t &Dest, uint32_t &DGNReq){
    
    if ((N2kMsg.PGN & 0xFF00)!=0xE800) return false;
    
    int Index=0;
    
    Dest=(uint8_t)N2kMsg.PGN;
    DGNReq = N2kMsg.GetByte(Index);
    DGNReq|=(N2kMsg.GetByte(Index)<<8);
    DGNReq|=(N2kMsg.GetByte(Index)<<16);

    return true;
}
  

//*****************************************************************************
// Acknowledgment - E800h
void SetRVCPGNE800(tN2kMsg &N2kMsg, tISOAckType Ack, uint8_t Inst, uint8_t InstBank, int32_t DGNAck){
    
    N2kMsg.SetPGN(0xE800);
    N2kMsg.Priority=6;
    N2kMsg.AddByte(Ack);
    N2kMsg.AddByte(Inst);
    N2kMsg.AddByte(InstBank | 0xF0);
    N2kMsg.Add3ByteInt(DGNAck);  
}

bool ParseRVCPGNE800(const tN2kMsg &N2kMsg, tISOAckType &Ack, uint8_t &Inst, uint8_t &InstBank, int32_t &DGNAck){
    
    if (N2kMsg.PGN!=0xE800) return false;

    int Index=0;
    
    Ack=(tISOAckType) N2kMsg.GetByte(Index);
    Inst=N2kMsg.GetByte(Index);
    InstBank=N2kMsg.GetByte(Index) & 0x0F;
    DGNAck = N2kMsg.GetByte(Index);
    DGNAck|=(N2kMsg.GetByte(Index)<<8);
    DGNAck|=(N2kMsg.GetByte(Index)<<16);

    return true;
}

//*****************************************************************************
// System Date and Time Status - 1FFFFh 
static void _SetRVCPNG1FFA0_1FFFF(tN2kMsg &N2kMsg, uint8_t Year, uint8_t Month, uint8_t Date, uint8_t DayOfWeek, uint8_t Hour, uint8_t Minute, uint8_t Second, tRVCTimeZone TimeZone)
{
    N2kMsg.AddByte(Year);
    N2kMsg.AddByte(Month);
    N2kMsg.AddByte(Date);
    N2kMsg.AddByte(DayOfWeek);
    N2kMsg.AddByte(Hour);
    N2kMsg.AddByte(Minute);
    N2kMsg.AddByte(Second);
    N2kMsg.AddByte(TimeZone);
}

static bool _ParseRVCPGN1FFA0_1FFFF(const tN2kMsg &N2kMsg, uint8_t &Year, uint8_t &Month, uint8_t &Date, uint8_t &DayOfWeek, 
					     uint8_t &Hour, uint8_t &Minute, uint8_t &Second, tRVCTimeZone &TimeZone)
{
    int Index;
    Year=N2kMsg.GetByte(Index);
    Month=N2kMsg.GetByte(Index);
    Date=N2kMsg.GetByte(Index);
    DayOfWeek=N2kMsg.GetByte(Index);
    Hour=N2kMsg.GetByte(Index);
    Minute=N2kMsg.GetByte(Index);
    Second=N2kMsg.GetByte(Index);
    TimeZone=(tRVCTimeZone)N2kMsg.GetByte(Index);

    return true;
}

void SetRVCPGN1FFFF(tN2kMsg &N2kMsg, uint8_t Year, uint8_t Month, uint8_t Date, uint8_t DayOfWeek, uint8_t Hour, uint8_t Minute, uint8_t Second, tRVCTimeZone TimeZone) 
{
    N2kMsg.SetPGN(0x1FFFF);
    N2kMsg.Priority=6;
    _SetRVCPNG1FFA0_1FFFF(N2kMsg, Year, Month, Date, DayOfWeek, Hour, Minute, Second, TimeZone);
}

bool ParseRVCPGN1FFFF(const tN2kMsg &N2kMsg, uint8_t &Year, uint8_t &Month, uint8_t &Date, uint8_t &DayOfWeek, 
					     uint8_t &Hour, uint8_t &Minute, uint8_t &Second, tRVCTimeZone &TimeZone)
{
    if (N2kMsg.PGN!=0x1FFFF) 
	return false;
    return _ParseRVCPGN1FFA0_1FFFF(N2kMsg, Year, Month, Date, DayOfWeek, Hour, Minute, Second, TimeZone);
}


//*****************************************************************************
// Set System Date and Time Command - 1FFFEh
void SetRVCPGN1FFFE(tN2kMsg &N2kMsg, uint8_t Year, uint8_t Month, uint8_t Date, uint8_t DayOfWeek, uint8_t Hour, uint8_t Minute, uint8_t Second, tRVCTimeZone TimeZone)
{
    N2kMsg.SetPGN(0x1FFFF);
    N2kMsg.Priority=5;
    _SetRVCPNG1FFA0_1FFFF(N2kMsg, Year, Month, Date, DayOfWeek, Hour, Minute, Second, TimeZone);
}

bool ParseRVCPGN1FFFE(const tN2kMsg &N2kMsg, uint8_t &Year, uint8_t &Month, uint8_t &Date, uint8_t &DayOfWeek, 
					     uint8_t &Hour, uint8_t &Minute, uint8_t &Second, tRVCTimeZone &TimeZone)
{
    if (N2kMsg.PGN!=0x1FFFE) 
	return false;
    return _ParseRVCPGN1FFA0_1FFFF(N2kMsg, Year, Month, Date, DayOfWeek, Hour, Minute, Second, TimeZone);
}

//*****************************************************************************
// GPS-Based Date and Time Status - 1FEA0h
void SetRVCPGN1FFA0(tN2kMsg &N2kMsg, uint8_t Year, uint8_t Month, uint8_t Date, uint8_t DayOfWeek, uint8_t Hour, uint8_t Minute, uint8_t Second, tRVCTimeZone TimeZone) 
{
    N2kMsg.SetPGN(0x1FFA0);
    N2kMsg.Priority=5;
    _SetRVCPNG1FFA0_1FFFF(N2kMsg, Year, Month, Date, DayOfWeek, Hour, Minute, Second, TimeZone);
}

bool ParseRVCPGN1FFA0(const tN2kMsg &N2kMsg, uint8_t &Year, uint8_t &Month, uint8_t &Date, uint8_t &DayOfWeek, 
					     uint8_t &Hour, uint8_t &Minute, uint8_t &Second, tRVCTimeZone &TimeZone)
{
    if (N2kMsg.PGN!=0x1FFA0) 
	return false;
    return _ParseRVCPGN1FFA0_1FFFF(N2kMsg, Year, Month, Date, DayOfWeek, Hour, Minute, Second, TimeZone);
}



//*****************************************************************************
// DC Source Status 1
void SetRVCPGN1FFFD(tN2kMsg &N2kMsg, uint8_t Instance, uint8_t DevPri, 
                      uint16_t Vdc, uint32_t Adc) {
    N2kMsg.SetPGN(0x1FFFD);
    N2kMsg.Priority=6;
    N2kMsg.AddByte(Instance);
    N2kMsg.AddByte(DevPri);
    N2kMsg.Add2ByteUInt(Vdc);
    N2kMsg.Add4ByteUInt(Adc);
}

bool ParseRVCPGN1FFFD(const tN2kMsg &N2kMsg, uint8_t &Instance, uint8_t &DevPri, 
                      uint16_t &Vdc, uint32_t &Adc) {
  if (N2kMsg.PGN!=0x1FFFD) return false;

  int Index=0;
  
  Instance=N2kMsg.GetByte(Index);
  DevPri=N2kMsg.GetByte(Index);
  Vdc=N2kMsg.Get2ByteUInt(Index);
  Adc=N2kMsg.Get4ByteUInt(Index);
  return true; 
}
  
  
//*****************************************************************************
// DC Source Status 2
void SetRVCPGN1FFFC(tN2kMsg &N2kMsg, uint8_t Instance, uint8_t DevPri, 
                      uint16_t Temp, uint8_t SOC, uint16_t TR) {
    N2kMsg.SetPGN(0x1FFFC);
    N2kMsg.Priority=6;
    N2kMsg.AddByte(Instance);
    N2kMsg.AddByte(DevPri);
    N2kMsg.Add2ByteUInt(Temp);
    N2kMsg.AddByte(SOC);
    N2kMsg.Add2ByteUInt(TR);
    N2kMsg.AddByte(0xFF);
}

bool ParseRVCPGN1FFFC(const tN2kMsg &N2kMsg, uint8_t &Instance, uint8_t &DevPri, 
                       uint16_t &Temp, uint8_t &SOC, uint16_t &TR) {
  if (N2kMsg.PGN!=0x1FFFC) return false;

  int Index=0;
  
  Instance=N2kMsg.GetByte(Index);
  DevPri=N2kMsg.GetByte(Index);
  Temp=N2kMsg.Get2ByteUInt(Index);
  SOC=N2kMsg.GetByte(Index);
  TR=N2kMsg.Get2ByteUInt(Index);
  
  return true;
}


//*****************************************************************************
// DC Source Status 3
void SetRVCPGN1FFFB(tN2kMsg &N2kMsg, uint8_t Instance, uint8_t DevPri, 
                     uint8_t SOH, uint16_t CapRem, uint8_t CapRemPer , uint16_t Ripple) {
    N2kMsg.SetPGN(0x1FFFB);
    N2kMsg.Priority=6;
    N2kMsg.AddByte(Instance);
    N2kMsg.AddByte(DevPri);
    N2kMsg.AddByte(SOH);
    N2kMsg.Add2ByteUInt(CapRem);
    N2kMsg.AddByte(CapRemPer);
    N2kMsg.Add2ByteUInt(Ripple);
}

bool ParseRVCPGN1FFFB(const tN2kMsg &N2kMsg, uint8_t &Instance, uint8_t &DevPri, uint8_t &SOH, 
                      uint16_t &CapRem, uint8_t &CapRemPer , uint16_t &Ripple){
  if (N2kMsg.PGN!=0x1FFFB) return false;

  int Index=0;
  
  Instance=N2kMsg.GetByte(Index);
  DevPri=N2kMsg.GetByte(Index);
  SOH=N2kMsg.GetByte(Index);  
  CapRem=N2kMsg.Get2ByteUInt(Index);
  CapRemPer=N2kMsg.GetByte(Index);
  Ripple=N2kMsg.Get2ByteUInt(Index);
  
  return true;
}





//*****************************************************************************
// DC Source Status 4
void SetRVCPGN1FEC9(tN2kMsg &N2kMsg, uint8_t Instance, uint8_t DevPri, 
                    tRVCBatChrgMode DesCM, uint16_t DesVolt, uint16_t DesAmps , tRVCBatType BatType){
    N2kMsg.SetPGN(0x1FEC9);
    N2kMsg.Priority=6;
    N2kMsg.AddByte(Instance);
    N2kMsg.AddByte(DevPri);
    N2kMsg.AddByte((unsigned char)DesCM);
    N2kMsg.Add2ByteUInt(DesVolt);
    N2kMsg.Add2ByteUInt(DesAmps);
    N2kMsg.AddByte((unsigned char)BatType | 0xf0);                        /* Unused bits must be set to 1's */
}

bool ParseRVCPGN1FEC9(const tN2kMsg &N2kMsg, uint8_t &Instance, uint8_t &DevPri,  
                      tRVCBatChrgMode &DesCM, uint16_t &DesVolt, uint16_t &DesAmp , tRVCBatType &BatType){
  if (N2kMsg.PGN!=0x1FEC9) return false;

  int Index=0;
  
  Instance=N2kMsg.GetByte(Index);
  DevPri=N2kMsg.GetByte(Index);
  DesCM=(tRVCBatChrgMode)N2kMsg.GetByte(Index);
  DesVolt=N2kMsg.Get2ByteUInt(Index);
  DesAmp=N2kMsg.Get2ByteUInt(Index);  
  BatType=(tRVCBatType)(N2kMsg.GetByte(Index) & 0x0f);              /* Mask out lower 4 bits */
    
  return true;
}










//*****************************************************************************
// DC Source Status 5
void SetRVCPGN1FEC8(tN2kMsg &N2kMsg, uint8_t Instance, uint8_t DevPri, uint32_t Vdc,  uint16_t dVdT) {
    N2kMsg.SetPGN(0x1FEC8);
    N2kMsg.Priority=6;
    N2kMsg.AddByte(Instance);
    N2kMsg.AddByte(DevPri);
    N2kMsg.Add4ByteUInt(Vdc);
    N2kMsg.Add2ByteUInt(dVdT);
}

bool ParseRVCPGN1FEC8(const tN2kMsg &N2kMsg, uint8_t &Instance, uint8_t &DevPri,  uint32_t &Vdc,  uint16_t &dVdT) {
  if (N2kMsg.PGN!=0x1FEC8) return false;

  int Index=0;
  
  Instance=N2kMsg.GetByte(Index);
  DevPri=N2kMsg.GetByte(Index);
  Vdc=N2kMsg.Get4ByteUInt(Index);
  dVdT=N2kMsg.Get2ByteUInt(Index);  
   
  return true;
}






//*****************************************************************************
// DC Source Status 6
void SetRVCPGN1FEC7(tN2kMsg &N2kMsg, uint8_t Instance, uint8_t DevPri, bool HVls, bool HVld, bool LVls, bool LVld) {
    uint8_t  flag = 0;

    if (HVls) flag |= 0x01;
    if (HVld) flag |= 0x01<<2;
    if (LVls) flag |= 0x01<<4;
    if (LVld) flag |= 0x01<<6;
    
    N2kMsg.SetPGN(0x1FEC7);
    N2kMsg.Priority=6;
    N2kMsg.AddByte(Instance);
    N2kMsg.AddByte(DevPri);
    N2kMsg.AddByte(flag);

}

bool ParseRVCPGN1FEC7(const tN2kMsg &N2kMsg, uint8_t &Instance, uint8_t &DevPri, bool &HVls, bool &HVld, bool &LVls, bool &LVld) {
  if (N2kMsg.PGN!=0x1FEC7) return false;

  int Index=0;
  uint8_t  flag;
  
  Instance=N2kMsg.GetByte(Index);
  DevPri=N2kMsg.GetByte(Index);
  flag=N2kMsg.GetByte(Index);
    
  HVls   = (flag & 0x03   ) == 0x01;  
  HVld   = (flag & 0x03<<2) == 0x01<<2; 
  LVls   = (flag & 0x03<<4) == 0x01<<4; 
  LVld   = (flag & 0x03<<6) == 0x01<<6; 
  
  return true;
}







//*****************************************************************************
// DC Source Status 11
void SetRVCPGN1FEA5(tN2kMsg &N2kMsg, uint8_t Instance, uint8_t DevPri, bool PwrOnOff, bool ChrgOnOff, bool ChrgDet, bool ResvStat, uint16_t BatAHCap, uint16_t DCPower) {
    uint8_t  flag = 0;

    if (PwrOnOff) flag |= 0x01;
    if (ChrgOnOff) flag |= 0x01<<2;
    if (ChrgDet) flag |= 0x01<<4;
    if (ResvStat) flag |= 0x01<<6;
    
    N2kMsg.SetPGN(0x1FEA5);
    N2kMsg.Priority=6;
    N2kMsg.AddByte(Instance);
    N2kMsg.AddByte(DevPri);
    N2kMsg.AddByte(flag);
    N2kMsg.Add2ByteUInt(BatAHCap);
    N2kMsg.Add2ByteUInt(DCPower);
     N2kMsg.AddByte(0xff);

}

bool ParseRVCPGN1FEA5(const tN2kMsg &N2kMsg, uint8_t &Instance, uint8_t &DevPri, bool &PwrOnOff, bool &ChrgOnOff, bool &ChrgDet, bool &ResvStat, uint16_t &BatAHCap, uint16_t &DCPower) {
  if (N2kMsg.PGN!=0x1FEA5) return false;

  int Index=0;
  uint8_t  flag;
  
  Instance=N2kMsg.GetByte(Index);
  DevPri=N2kMsg.GetByte(Index);
  flag=N2kMsg.GetByte(Index);
    
  PwrOnOff   = (flag & 0x03   ) == 0x01;  
  ChrgOnOff  = (flag & 0x03<<2) == 0x01<<2; 
  ChrgDet    = (flag & 0x03<<4) == 0x01<<4; 
  ResvStat   = (flag & 0x03<<6) == 0x01<<6; 
  
  BatAHCap=N2kMsg.Get2ByteUInt(Index);
  DCPower =N2kMsg.Get2ByteUInt(Index);
  
  return true;
}





//*****************************************************************************
// DC Disconnect Status
void SetRVCPGN1FED0(tN2kMsg &N2kMsg, uint8_t Instance, bool Status, bool LastCom, bool Bypassed) {
    uint8_t  flag = 0xC0;               /* Unused bits must be set high */

    if (Status)     flag |= 0x01;
    if (LastCom)    flag |= 0x01<<2;
    if (Bypassed)   flag |= 0x01<<4;
    
    N2kMsg.SetPGN(0x1FED0);
    N2kMsg.Priority=6;
    N2kMsg.AddByte(Instance);
    N2kMsg.AddByte(flag);

}

bool ParseRVCPGN1FED0(const tN2kMsg &N2kMsg, uint8_t &Instance, bool &Status, bool &LastCom, bool &Bypassed) {
  if (N2kMsg.PGN!=0x1FED0) return false;

  int Index=0;
  uint8_t  flag;
  
  Instance=N2kMsg.GetByte(Index);
  flag=N2kMsg.GetByte(Index);
     
  Status     = (flag & 0x03   ) == 0x01;  
  LastCom    = (flag & 0x03<<2) == 0x01<<2; 
  Bypassed   = (flag & 0x03<<4) == 0x01<<4; 
  
  return true;
}





//*****************************************************************************
// DC Disconnect Command  - 1FECFh
void SetRVCPGN1FECF(tN2kMsg &N2kMsg, uint8_t Instance, bool Command) {
    uint8_t  flag = 0xFC;               /* Unused bits must be set high */

    if (Command)  flag |= 0x01;

    
    N2kMsg.SetPGN(0x1FECF);
    N2kMsg.Priority=6;
    N2kMsg.AddByte(Instance);
    N2kMsg.AddByte(flag);

}

bool ParseRVCPGN1FECF(const tN2kMsg &N2kMsg, uint8_t &Instance, bool &Command) {
  if (N2kMsg.PGN!=0x1FECF) return false;

  int Index=0;
  uint8_t  flag;
  
  Instance=N2kMsg.GetByte(Index);
  flag=N2kMsg.GetByte(Index);
    
  Command  = (flag & 0x03 ) == 0x01;  
  
  return true;
}



//*****************************************************************************
// Generator Status 1 - 1FFDCh
void SetRVCPGN1FFDC(tN2kMsg &N2kMsg, tRVCGenStatus Status, uint32_t Minutes, uint8_t Load, uint16_t SBVdc) {
    
    N2kMsg.SetPGN(0x1FECF);
    N2kMsg.Priority=6;
    N2kMsg.AddByte((uint8_t) Status);
    N2kMsg.Add4ByteUInt(Minutes);
    N2kMsg.AddByte(Load);  
    N2kMsg.AddByte(SBVdc);   
}


bool ParseRVCPGN1FFDC(const tN2kMsg &N2kMsg, tRVCGenStatus &Status, uint32_t &Minutes, uint8_t &Load, uint16_t &SBVdc) {
    if (N2kMsg.PGN!=0x1FEDC) return false;   
 
    int     Index=0;
    
    Status=(tRVCGenStatus)N2kMsg.GetByte(Index);
    Minutes=N2kMsg.Get4ByteUInt(Index);
    Load=N2kMsg.GetByte(Index);
    SBVdc=N2kMsg.GetByte(Index);   

    return true;
  
}


//*****************************************************************************
// Generator Status 2 - 1FFDBh
void SetRVCPGN1FFDB(tN2kMsg &N2kMsg, bool OvrTemp, bool LowOP, bool LowOL, bool CautLght, uint8_t EngTemp, uint16_t RPM, uint16_t FFlow) {
    
    uint8_t  flag = 0; 
    
    if (OvrTemp)    flag |= 0x01;
    if (LowOP)      flag |= 01<<2;
    if (LowOL)      flag |= 01<<4;
    if (CautLght)   flag |= 01<<6;
    
    N2kMsg.SetPGN(0x1FFDB);
    N2kMsg.Priority=6;
    N2kMsg.AddByte(flag);
    N2kMsg.AddByte(EngTemp);
    N2kMsg.Add2ByteUInt(RPM);
    N2kMsg.Add2ByteUInt(FFlow);
}

bool ParseRVCPGN1FFDB(const tN2kMsg &N2kMsg, bool &OvrTemp, bool &LowOP, bool &LowOL, bool &CautLght, uint8_t &EngTemp, uint16_t &RPM, uint16_t &FFlow) {
    if (N2kMsg.PGN!=0x1FFDB) return false;

    int     Index=0;
    uint8_t flag;   
    
    flag=N2kMsg.GetByte(Index);
    OvrTemp = (flag & 0x03   ) == 0x01; 
    LowOP   = (flag & 0x03<<2) == 0x01<<2;   
    LowOL   = (flag & 0x03<<4) == 0x01<<4;   
    CautLght= (flag & 0x03<<6) == 0x01<<6;   
    
    EngTemp=N2kMsg.GetByte(Index);
    RPM=N2kMsg.Get2ByteUInt(Index);
    FFlow=N2kMsg.Get2ByteUInt(Index);
     
    return true;
}




//*****************************************************************************
// Generator Command  -  1FFDAh
void SetRVCPGN1FFDA(tN2kMsg &N2kMsg, tRVCGenCmd Command) {
    N2kMsg.SetPGN(0x1FFDA);
    N2kMsg.Priority=6;
    
    N2kMsg.AddByte((uint8_t)Command);    
    
}

bool ParseRVCPGN1FFDA(const tN2kMsg &N2kMsg, tRVCGenCmd &Command) {
    if (N2kMsg.PGN!=0x1FFDA) return false;

    int     Index=0;   
    
    Command=(tRVCGenCmd)N2kMsg.GetByte(Index);

    return true;
}



//*****************************************************************************
// Generator Starter Configuration  -  1FFD9h
void SetRVCPGN1FFD9(tN2kMsg &N2kMsg, tRVCGenStrTyp GenType, uint8_t PreCrank, uint8_t MaxCrank, uint8_t Stop) {
    N2kMsg.SetPGN(0x1FFD9);
    N2kMsg.Priority=6;
    
    N2kMsg.AddByte((uint8_t) GenType); 
    N2kMsg.AddByte(PreCrank);
    N2kMsg.AddByte(MaxCrank);
    N2kMsg.AddByte(Stop);
}


bool ParseRVCPGN1FFD9(const tN2kMsg &N2kMsg, tRVCGenStrTyp &GenType, uint8_t &PreCrank, uint8_t &MaxCrank, uint8_t &Stop) {
    if (N2kMsg.PGN!=0x1FFD9) return false;

    int     Index=0;   
    
    GenType=(tRVCGenStrTyp)N2kMsg.GetByte(Index);
    PreCrank=N2kMsg.GetByte(Index);
    MaxCrank=N2kMsg.GetByte(Index);
    Stop=N2kMsg.GetByte(Index);
    
    return true;
}





//*****************************************************************************
// Generator Starter Configuration Command -  1FFD8h
void SetRVCPGN1FFD8(tN2kMsg &N2kMsg, tRVCGenStrTyp GenType, uint8_t PreCrank, uint8_t MaxCrank, uint8_t Stop) {
    N2kMsg.SetPGN(0x1FFD8);
    N2kMsg.Priority=6;
    
    N2kMsg.AddByte((uint8_t) GenType); 
    N2kMsg.AddByte(PreCrank);
    N2kMsg.AddByte(MaxCrank);
    N2kMsg.AddByte(Stop);
}


bool ParseRVCPGN1FFD8(const tN2kMsg &N2kMsg, tRVCGenStrTyp &GenType, uint8_t &PreCrank, uint8_t &MaxCrank, uint8_t &Stop) {
    if (N2kMsg.PGN!=0x1FFD8) return false;

    int     Index=0;   
    
    GenType=(tRVCGenStrTyp)N2kMsg.GetByte(Index);
    PreCrank=N2kMsg.GetByte(Index);
    MaxCrank=N2kMsg.GetByte(Index);
    Stop=N2kMsg.GetByte(Index);
    
    return true;
}








//*****************************************************************************
// Charger Status - 1FFC7h
void SetRVCPGN1FFC7(tN2kMsg &N2kMsg, tRVCChrgType ChrgType, uint8_t Instance, uint16_t CVdc, uint16_t CAdc, uint8_t PerMax,
                    tRVCBatChrgMode State, bool EnableAtPO, bool AutoRechg, tRVCChrgForceChrg ForcedChrg){
    uint8_t  flag;     
    
    flag = ForcedChrg << 4;
    if (EnableAtPO) flag |= 0x01;
    if (AutoRechg)  flag |= 0x01<<2;
    
    N2kMsg.SetPGN(0x1FFC7);
    N2kMsg.Priority=6;
    N2kMsg.AddByte((Instance & 0x0F) | ChrgType<<4);
    N2kMsg.Add2ByteUInt(CVdc);
    N2kMsg.Add2ByteUInt(CAdc);
    N2kMsg.AddByte(PerMax);
    N2kMsg.AddByte((uint8_t)State);
    N2kMsg.AddByte(flag);                    
}


bool ParseRVCPGN1FFC7(const tN2kMsg &N2kMsg, tRVCChrgType &ChrgType, uint8_t &Instance, uint16_t &CVdc, uint16_t &CAdc, uint8_t &PerMax,
                            tRVCBatChrgMode &State, bool &EnableAtPO, bool &AutoRechg, tRVCChrgForceChrg &ForcedChrg){                           
  if (N2kMsg.PGN!=0x1FFC7) return false;

  int     Index=0;
  uint8_t flag;
  
  flag=N2kMsg.GetByte(Index);
  Instance = flag&0x0F;
  ChrgType =(tRVCChrgType)( flag>>4);
  
  CVdc=N2kMsg.Get2ByteUInt(Index);
  CAdc=N2kMsg.Get2ByteUInt(Index);
  PerMax=N2kMsg.GetByte(Index);
  State=(tRVCBatChrgMode)N2kMsg.GetByte(Index);
  
  flag=N2kMsg.GetByte(Index);
  EnableAtPO = (flag & 0x03   ) == 0x01;  
  AutoRechg  = (flag & 0x03<<2) == 0x01<<2;   
  ForcedChrg = (tRVCChrgForceChrg) (flag >> 4);
  
  return true;
}


//*****************************************************************************
// Charger Status2 - 1FEA3h  
void SetRVCPGN1FEA3(tN2kMsg &N2kMsg, tRVCChrgType ChrgType, uint8_t ChrgInst, uint8_t DCInst, uint8_t DevPri, uint16_t Vdc, uint16_t Adc, uint8_t Temp) {
    N2kMsg.SetPGN(0x1FEA3);
    N2kMsg.Priority=6;
    N2kMsg.AddByte((ChrgInst & 0x0F) | ChrgType<<4);
    N2kMsg.AddByte(DCInst);
    N2kMsg.AddByte(DevPri);
    N2kMsg.Add2ByteUInt(Vdc);
    N2kMsg.Add2ByteUInt(Adc);
    N2kMsg.AddByte(Temp);
}

bool ParseRVCPGN1FEA3(const tN2kMsg &N2kMsg, tRVCChrgType &ChrgType, uint8_t &ChrgInst, uint8_t &DCInst, uint8_t &DevPri, uint16_t &Vdc, uint16_t &Adc, uint8_t &Temp) {
  if (N2kMsg.PGN!=0x1FEA3) return false;

  int Index=0;
  uint8_t flag;
  
  flag=N2kMsg.GetByte(Index);
  ChrgInst = flag & 0x0F;
  ChrgType =(tRVCChrgType)( flag>>4);
  DCInst=N2kMsg.GetByte(Index);
  DevPri=N2kMsg.GetByte(Index);
  Vdc=N2kMsg.Get2ByteUInt(Index);
  Adc=N2kMsg.Get2ByteUInt(Index);
  Temp=N2kMsg.GetByte(Index);
  return true; 
}
  

  
  
  
//*****************************************************************************
// Charger Command - 1FFC5h
void SetRVCPGN1FFC5(tN2kMsg &N2kMsg, tRVCChrgType ChrgType, uint8_t Instance, tRVCChrgStatus ChrgStat,  
                       bool EnableAtPO, bool AutoRechg, tRVCChrgForceChrg ForcedChrg){
    uint8_t  flag;     
    
    flag = ForcedChrg << 4;
    if (EnableAtPO) flag |= 0x01;
    if (AutoRechg)  flag |= 0x01<<2;
    
    N2kMsg.SetPGN(0x1FFC5);
    N2kMsg.Priority=6;
    N2kMsg.AddByte((Instance & 0x0F) | ChrgType<<4);
    N2kMsg.AddByte((uint8_t)ChrgStat);
    N2kMsg.AddByte(flag);  
    N2kMsg.AddByte(0Xff);
    N2kMsg.AddByte(0Xff);
    N2kMsg.AddByte(0Xff);
    N2kMsg.AddByte(0Xff);
    N2kMsg.AddByte(0Xff);    
}

bool ParseRVCPGN1FFC5(const tN2kMsg &N2kMsg, tRVCChrgType &ChrgType, uint8_t &Instance, tRVCChrgStatus &ChrgStat, 
                                            bool &EnableAtPO, bool &AutoRechg, tRVCChrgForceChrg &ForcedChrg){
  if (N2kMsg.PGN!=0x1FEC5) return false;

  int     Index=0;
  uint8_t flag;
  
  flag=N2kMsg.GetByte(Index);
  Instance = flag & 0x0F;
  ChrgType =(tRVCChrgType)( flag>>4);
  ChrgStat=(tRVCChrgStatus)N2kMsg.GetByte(Index);
  flag=N2kMsg.GetByte(Index);
  EnableAtPO = (flag & 0x03   ) == 0x01;  
  AutoRechg  = (flag & 0x03<<2) == 0x01<<2;  
  ForcedChrg = (tRVCChrgForceChrg) (flag >> 4);
  
  return true;
}



//*****************************************************************************
// Charger Configuration Status - 1FFC6h
void SetRVCPGN1FFC6(tN2kMsg &N2kMsg, tRVCChrgType ChrgType, uint8_t Instance, tRVCChrgAlg  ChrgAlg,  tRVCChrgMode  ChrgMode, 
                       bool BatSense, tRVCChrgLine Line, bool Linked, tRVCBatType BatType,  uint16_t BatSize, uint8_t MaxAmps){
    uint8_t  flag;     
    
    flag = BatType << 4;
    if (BatSense) flag |= 0x01;
    if (Linked)   flag |= 0x01<<2;
    
    N2kMsg.SetPGN(0x1FFC6);
    N2kMsg.Priority=6;
    N2kMsg.AddByte((Instance & 0x0F) | ChrgType<<4);
    N2kMsg.AddByte((uint8_t)ChrgAlg);
    N2kMsg.AddByte((uint8_t)ChrgMode);
    N2kMsg.AddByte(flag); 
    N2kMsg.Add2ByteUInt(BatSize);    
    N2kMsg.AddByte(MaxAmps);
}

bool ParseRVCPGN1FFC6(const tN2kMsg &N2kMsg, tRVCChrgType &ChrgType, uint8_t &Instance, tRVCChrgAlg  &ChrgAlg,  tRVCChrgMode  &ChrgMode, 
                               bool &BatSense, tRVCChrgLine &Line, bool &Linked, tRVCBatType &BatType,  uint16_t &BatSize, uint8_t &MaxAmps){
  if (N2kMsg.PGN!=0x1FEC6) return false;

  int     Index=0;
  uint8_t flag;
  
  flag=N2kMsg.GetByte(Index);
  Instance = flag & 0x0F;
  ChrgType =(tRVCChrgType)( flag>>4);
  
  ChrgAlg=(tRVCChrgAlg)N2kMsg.GetByte(Index);
  ChrgMode=(tRVCChrgMode)N2kMsg.GetByte(Index);
  flag=N2kMsg.GetByte(Index);
  BatSize=N2kMsg.Get2ByteUInt(Index);
  MaxAmps=N2kMsg.Get2ByteUInt(Index);
    
  BatSense = (flag & 0x03   ) == 0x01;  
  Linked   = (flag & 0x03<<2) == 0x01<<2;  
  BatType  = (tRVCBatType) (flag >> 4);
  
  return true;
}


//*****************************************************************************
// Charger Configuration Status2 - 1FF96h
void SetRVCPGN1FF96(tN2kMsg &N2kMsg, tRVCChrgType ChrgType, uint8_t Instance, uint8_t PerMaxAmps, uint8_t PerMaxBank, uint8_t ShorBr, uint8_t DefBatTemp, uint16_t RchgVolt){
    N2kMsg.SetPGN(0x1FF96);
    N2kMsg.Priority=6;
    N2kMsg.AddByte((Instance & 0x0F) | ChrgType<<4);
    N2kMsg.AddByte(PerMaxAmps);
    N2kMsg.AddByte(PerMaxBank);
    N2kMsg.AddByte(ShorBr);
    N2kMsg.AddByte(DefBatTemp); 
    N2kMsg.Add2ByteUInt(RchgVolt); 
    N2kMsg.AddByte(0xFF);    
}

bool ParseRVCPGN1FF96(const tN2kMsg &N2kMsg, tRVCChrgType &ChrgType, uint8_t &Instance, uint8_t &PerMaxAmps, uint8_t &PerMaxBank, uint8_t &ShorBr, uint8_t &DefBatTemp, uint16_t &RchgVolt) {
  if (N2kMsg.PGN!=0x1FF96) return false;

  int     Index=0;
  uint8_t flag;
  
  flag=N2kMsg.GetByte(Index);
  Instance = flag & 0x0F;
  ChrgType =(tRVCChrgType)( flag>>4);
  PerMaxAmps=N2kMsg.GetByte(Index);
  PerMaxBank=N2kMsg.GetByte(Index);
  ShorBr=N2kMsg.GetByte(Index);
  DefBatTemp=N2kMsg.GetByte(Index);
  RchgVolt=N2kMsg.Get2ByteUInt(Index);
  
  return true;
}



//*****************************************************************************
// Charger Configuration Status3 - 1FECCh
void SetRVCPGN1FECC(tN2kMsg &N2kMsg, tRVCChrgType ChrgType, uint8_t Instance, uint16_t BulkV, uint16_t AbsorbV, uint16_t FloatV, uint8_t TempComp){
    N2kMsg.SetPGN(0x1FECC);
    N2kMsg.Priority=6;
    N2kMsg.AddByte((Instance & 0x0F) | ChrgType<<4);
    N2kMsg.Add2ByteUInt(BulkV);   
    N2kMsg.Add2ByteUInt(AbsorbV);   
    N2kMsg.Add2ByteUInt(FloatV);   
    N2kMsg.AddByte(TempComp);
}

bool ParseRVCPGN1FECC(const tN2kMsg &N2kMsg, tRVCChrgType &ChrgType, uint8_t &Instance, uint16_t &BulkV, uint16_t &AbsorbV, uint16_t &FloatV, uint8_t &TempComp) {
  if (N2kMsg.PGN!=0x1FECC) return false;

  int     Index=0;
  uint8_t flag;
  
  flag=N2kMsg.GetByte(Index);
  Instance = flag & 0x0F;
  ChrgType =(tRVCChrgType)( flag>>4);
  BulkV=N2kMsg.Get2ByteUInt(Index);
  AbsorbV=N2kMsg.Get2ByteUInt(Index);
  FloatV=N2kMsg.Get2ByteUInt(Index);
  TempComp=N2kMsg.GetByte(Index);
  
  return true;
}


//*****************************************************************************
// Charger Configuration Status4 - 1FEBFh
void SetRVCPGN1FEBF(tN2kMsg &N2kMsg, tRVCChrgType ChrgType, uint8_t Instance, uint16_t BulkT, uint16_t AbsorbT, uint16_t FloatT){
    N2kMsg.SetPGN(0x1FEBF);
    N2kMsg.Priority=6;
    N2kMsg.AddByte((Instance & 0x0F) | ChrgType<<4);
    N2kMsg.Add2ByteUInt(BulkT);   
    N2kMsg.Add2ByteUInt(AbsorbT);   
    N2kMsg.Add2ByteUInt(FloatT);  
    N2kMsg.AddByte(0Xff);
}

bool ParseRVCPGN1FEBF(const tN2kMsg &N2kMsg, tRVCChrgType &ChrgType, uint8_t &Instance, uint16_t &BulkT, uint16_t &AbsorbT, uint16_t &FloatT){
  if (N2kMsg.PGN!=0x1FEBF) return false;

  int     Index=0;
  uint8_t flag;
  
  flag=N2kMsg.GetByte(Index);
  Instance = flag & 0x0F;
  ChrgType =(tRVCChrgType)( flag>>4);
  BulkT=N2kMsg.Get2ByteUInt(Index);
  AbsorbT=N2kMsg.Get2ByteUInt(Index);
  FloatT=N2kMsg.Get2ByteUInt(Index);
  
  return true;
}  
    


//*****************************************************************************
// Charger Configuration Command - 1FFC4h
void SetRVCPGN1FFC4(tN2kMsg &N2kMsg, tRVCChrgType ChrgType, uint8_t Instance, tRVCChrgAlg  ChrgAlg,  tRVCChrgMode  ChrgMode, 
                       bool BatSense, tRVCChrgLine Line, bool Linked,  tRVCBatType BatType,  uint16_t BatSize, uint8_t MaxAmps){
    
    uint8_t  flag;    
    
    flag = (Line << 2) | 0xF0;                                           // Unused bits set to 1's 
    if (BatSense) flag |= 0x01;
    

    N2kMsg.SetPGN(0x1FFC4);
    N2kMsg.Priority=6;
    N2kMsg.AddByte((Instance & 0x0F) | ChrgType<<4);
    N2kMsg.AddByte((uint8_t)ChrgAlg);
    N2kMsg.AddByte((uint8_t)ChrgMode);
    N2kMsg.AddByte(flag);
    N2kMsg.Add2ByteUInt(BatSize);   
    N2kMsg.AddByte((uint8_t)BatType | 0xF0);
    N2kMsg.AddByte(MaxAmps);
}

bool ParseRVCPGN1FFC4(const tN2kMsg &N2kMsg, tRVCChrgType &ChrgType, uint8_t &Instance, tRVCChrgAlg  &ChrgAlg,  tRVCChrgMode  &ChrgMode, 
                               bool &BatSense, tRVCChrgLine &Line, bool &Linked,  tRVCBatType &BatType,  uint16_t &BatSize, uint8_t &MaxAmps){
  if (N2kMsg.PGN!=0x1FFC4) return false;

  int     Index=0;
  uint8_t flag;
  
  flag=N2kMsg.GetByte(Index);
  Instance = flag & 0x0F;
  ChrgType =(tRVCChrgType)( flag>>4);
  ChrgAlg=(tRVCChrgAlg)N2kMsg.GetByte(Index);
  ChrgMode=(tRVCChrgMode)N2kMsg.GetByte(Index);
  flag=N2kMsg.GetByte(Index);
  BatSize=N2kMsg.Get2ByteUInt(Index);
  BatType=(tRVCBatType)(N2kMsg.GetByte(Index) & 0x0F);
  MaxAmps=N2kMsg.GetByte(Index);
    
  BatSense = (flag & 0x03) == 0x01;  
  Line     = (tRVCChrgLine) ((flag >> 2) & 0x0F);
  
  return true;
}
  


//*****************************************************************************
// Charger Configuration Command2 - 1FF95h
void SetRVCPGN1FF95(tN2kMsg &N2kMsg, tRVCChrgType ChrgType, uint8_t Instance, uint8_t PerMaxAmps, uint8_t PerMaxShore, uint8_t ShorBr, uint8_t DefBatTemp, uint16_t RchgVolt){
    
    N2kMsg.SetPGN(0x1FF95);
    N2kMsg.Priority=6;
    N2kMsg.AddByte((Instance & 0x0F) | ChrgType<<4);
    N2kMsg.AddByte(PerMaxAmps);
    N2kMsg.AddByte(PerMaxShore);
    N2kMsg.AddByte(ShorBr);
    N2kMsg.AddByte(DefBatTemp);
    N2kMsg.Add2ByteUInt(RchgVolt); 
    N2kMsg.AddByte(0Xff);    
}

bool ParseRVCPGN1FF95(const tN2kMsg &N2kMsg, tRVCChrgType &ChrgType, uint8_t &Instance, uint8_t &PerMaxAmps, uint8_t &PerMaxShore, uint8_t &ShorBr, uint8_t &DefBatTemp, uint16_t &RchgVolt){
  if (N2kMsg.PGN!=0x1FFC4) return false;
  
  int     Index=0;
  uint8_t flag;
  
  flag=N2kMsg.GetByte(Index);
  Instance = flag & 0x0F;
  ChrgType =(tRVCChrgType)( flag>>4);
  PerMaxAmps=N2kMsg.GetByte(Index);
  PerMaxShore=N2kMsg.GetByte(Index);
  ShorBr=N2kMsg.GetByte(Index);
  DefBatTemp=N2kMsg.GetByte(Index);
  RchgVolt=N2kMsg.Get2ByteUInt(Index);
  
  return true;  
}



//*****************************************************************************
// Charger Configuration Command3 - 1FECBh
void SetRVCPGN1FECB(tN2kMsg &N2kMsg, tRVCChrgType ChrgType, uint8_t Instance, uint16_t BulkV, uint16_t AbsorbV, uint16_t FloatV, uint8_t TempComp){
    N2kMsg.SetPGN(0x1FECB);
    N2kMsg.Priority=6;
    N2kMsg.AddByte((Instance & 0x0F) | ChrgType<<4);
    N2kMsg.Add2ByteUInt(BulkV);   
    N2kMsg.Add2ByteUInt(AbsorbV);   
    N2kMsg.Add2ByteUInt(FloatV);   
    N2kMsg.AddByte(TempComp);
    
}

bool ParseRVCPGN1FECB(const tN2kMsg &N2kMsg, tRVCChrgType &ChrgType, uint8_t &Instance, uint16_t &BulkV, uint16_t &AbsorbV, uint16_t &FloatV, uint8_t &TempComp){
  if (N2kMsg.PGN!=0x1FECB) return false;
  
  int     Index=0;
  uint8_t flag;
  
  flag=N2kMsg.GetByte(Index);
  Instance = flag & 0x0F;
  ChrgType =(tRVCChrgType)( flag>>4);
  BulkV=N2kMsg.Get2ByteUInt(Index);
  AbsorbV=N2kMsg.Get2ByteUInt(Index);
  FloatV=N2kMsg.Get2ByteUInt(Index);
  TempComp=N2kMsg.GetByte(Index); 
  
  return true;
}


//*****************************************************************************
// Charger Configuration Command4 - 1FEBEh
void SetRVCPGN1FEBE(tN2kMsg &N2kMsg, tRVCChrgType ChrgType, uint8_t Instance, uint16_t BulkT, uint16_t AbsorbT, uint16_t FloatT){

    N2kMsg.SetPGN(0x1FEBE);
    N2kMsg.Priority=6;
    N2kMsg.AddByte((Instance & 0x0F) | ChrgType<<4);
    N2kMsg.Add2ByteUInt(BulkT);   
    N2kMsg.Add2ByteUInt(AbsorbT);   
    N2kMsg.Add2ByteUInt(FloatT);  
    N2kMsg.AddByte(0Xff);
}

bool ParseRVCPGN1FEBE(const tN2kMsg &N2kMsg, tRVCChrgType &ChrgType, uint8_t &Instance, uint16_t &BulkT, uint16_t &AbsorbT, uint16_t &FloatT){
  if (N2kMsg.PGN!=0x1FEBE) return false;

  int     Index=0;
  uint8_t flag;
  
  flag=N2kMsg.GetByte(Index);
  Instance = flag & 0x0F;
  ChrgType =(tRVCChrgType)( flag>>4);
  BulkT=N2kMsg.Get2ByteUInt(Index);
  AbsorbT=N2kMsg.Get2ByteUInt(Index);
  FloatT=N2kMsg.Get2ByteUInt(Index); 

  return true;  
}





//*****************************************************************************
// Charger Equalization Status - 1FF99h
void SetRVCPGN1FF99(tN2kMsg &N2kMsg, tRVCChrgType ChrgType, uint8_t Instance, uint16_t Time, bool PreChrg){
    uint8_t  flag = 0xFC;                                         // Unused bits set to 1's 
    if (PreChrg) flag |= 0x01;
        
    N2kMsg.SetPGN(0x1FF99);
    N2kMsg.Priority=6;
    N2kMsg.AddByte((Instance & 0x0F) | ChrgType<<4);
    N2kMsg.Add2ByteUInt(Time);   
    N2kMsg.AddByte(flag);
    N2kMsg.AddByte(0Xff);
    N2kMsg.AddByte(0Xff);
    N2kMsg.AddByte(0Xff);
    N2kMsg.AddByte(0Xff);
}

bool ParseRVCPGN1FF99(const tN2kMsg &N2kMsg, tRVCChrgType &ChrgType, uint8_t &Instance, uint16_t &Time, bool &PreChrg){
  if (N2kMsg.PGN!=0x1FF99) return false;

  int     Index=0;
  uint8_t flag;
  
  flag=N2kMsg.GetByte(Index);
  Instance = flag & 0x0F;
  ChrgType =(tRVCChrgType)( flag>>4);
  Time=N2kMsg.Get2ByteUInt(Index);
  flag=N2kMsg.GetByte(Index);
  PreChrg = (flag & 0x03) == 0x01;  

  return true;  
}







//*****************************************************************************
// Charger Equalization Configuration Status - 1FF98h

void SetRVCPGN1FF98(tN2kMsg &N2kMsg, tRVCChrgType ChrgType, uint8_t Instance, uint16_t Volts, uint16_t Time){
    
    N2kMsg.SetPGN(0x1FF98);
    N2kMsg.Priority=6;
    N2kMsg.AddByte((Instance & 0x0F) | ChrgType<<4);
    N2kMsg.Add2ByteUInt(Volts);   
    N2kMsg.Add2ByteUInt(Time);   
    N2kMsg.AddByte(0Xff);
    N2kMsg.AddByte(0Xff);
    N2kMsg.AddByte(0Xff);
}

bool ParseRVCPGN1FF98(const tN2kMsg &N2kMsg, tRVCChrgType &ChrgType, uint8_t &Instance, uint16_t &Volts, uint16_t &Time){
   if (N2kMsg.PGN!=0x1FF98) return false;

  int     Index=0;
  uint8_t flag;
  
  flag=N2kMsg.GetByte(Index);
  Instance = flag & 0x0F;
  ChrgType =(tRVCChrgType)( flag>>4);
  Volts=N2kMsg.Get2ByteUInt(Index);
  Time=N2kMsg.Get2ByteUInt(Index);
  
  return true;
}






//*****************************************************************************
// Charger Equalization Configuration Command - 1FF97h
void SetRVCPGN1FF97(tN2kMsg &N2kMsg, tRVCChrgType ChrgType, uint8_t Instance, uint16_t Volts, uint16_t Time){
    
    N2kMsg.SetPGN(0x1FF97);
    N2kMsg.Priority=6;
    N2kMsg.AddByte((Instance & 0x0F) | ChrgType<<4);
    N2kMsg.Add2ByteUInt(Volts);   
    N2kMsg.Add2ByteUInt(Time);   
    N2kMsg.AddByte(0Xff);
    N2kMsg.AddByte(0Xff);
    N2kMsg.AddByte(0Xff);    
}

bool ParseRVCPGN1FF97(const tN2kMsg &N2kMsg, tRVCChrgType &ChrgType, uint8_t &Instance, uint16_t &Volts, uint16_t &Time){
   if (N2kMsg.PGN!=0x1FF97) return false;

  int     Index=0;
  uint8_t flag;
  
  flag=N2kMsg.GetByte(Index);
  Instance = flag & 0x0F;
  ChrgType =(tRVCChrgType)( flag>>4);
  Volts=N2kMsg.Get2ByteUInt(Index);
  Time=N2kMsg.Get2ByteUInt(Index);
  
  return true;
    
}







//*****************************************************************************
// Terminal - 17E00h
void SetRVCPGN17E00(tN2kMsg &N2kMsg, uint8_t Destination, int Count, char *Characters){
    int i;
    
    N2kMsg.SetPGN(0x17E00);
    N2kMsg.Destination = Destination;                                                           // Terminal is a node-to-node only communication protocol
    N2kMsg.Priority=7;
    
    for (i = 0; ((i < Count) && (i < 8)); i++)  N2kMsg.AddByte(*Characters++);
}

              
bool ParseRVCPGN17E00(const tN2kMsg &N2kMsg, uint8_t &Source, int &Count, char characters[8]) {
  if ((N2kMsg.PGN & 0xFFFF00)!=0x17E00) return false;

  int Index=0;
  int i;
  
  Source=N2kMsg.Source;
  Count =N2kMsg.DataLen;
  for (i=0; ((i < Count) && (i < 8)); i++)
      characters[i] = N2kMsg.GetByte(Index);

  return true;
       
    
    
}








//*****************************************************************************
// ISO Diagnostics Message - 1FECAh
void SetISOPGN1FECA(tN2kMsg &N2kMsg, bool On, bool Active, bool Red, bool Yellow, uint8_t DSA,
                    uint32_t SPN, tISOFMIType FMI, uint8_t Count, uint8_t DSA_ext, uint8_t Bank){
    
    uint8_t flag = 0x00;
    
    if (On)      flag |=  0x01;
    if (Active)  flag |= (0x01 << 2);
    if (Yellow)  flag |= (0x01 << 4);
    if (Red)     flag |= (0x01 << 6);
 
    
    N2kMsg.SetPGN(0x1FECA);
    N2kMsg.Priority=6;
    N2kMsg.AddByte(flag);
    N2kMsg.AddByte(DSA);
    N2kMsg.AddByte((uint8_t) (SPN >> 11));
    N2kMsg.AddByte((uint8_t) (SPN >>  3));
    N2kMsg.AddByte(((uint8_t)(SPN << 5)) | (FMI & 0x1F));
    N2kMsg.AddByte(Count | 0x80);
    N2kMsg.AddByte(DSA_ext);
    N2kMsg.AddByte(Bank | 0xF0); 

}

bool ParseISOPGN1FECA(const tN2kMsg &N2kMsg, bool &On, bool &Active, bool &Red, bool &Yellow, uint8_t &DSA,
                    uint32_t &SPN, tISOFMIType &FMI, uint8_t &Count, uint8_t &DSA_ext, uint8_t &Bank){
   if (N2kMsg.PGN!=0x1FECA) return false;

  int     Index=0;
  uint8_t flag, part;
 
                        
  flag=N2kMsg.GetByte(Index);
  DSA =N2kMsg.GetByte(Index);
  SPN =N2kMsg.GetByte(Index)<<8;
  SPN|=N2kMsg.GetByte(Index);
  part=N2kMsg.GetByte(Index);
  Count=N2kMsg.GetByte(Index) & 0x7F;
  DSA_ext=N2kMsg.GetByte(Index);
  Bank=N2kMsg.GetByte(Index)  & 0x0F;
  
  FMI  = (tISOFMIType) (part & 0x1F);
  SPN  = (SPN << 3) | (part >> 5);
  SPN &= 0x7FFFF;                           // SPN is a 19 bit value     
    
  On      = (flag &  0x03    ) == 0x01;  
  Active  = (flag & (0x03<<2)) == 0x01<<2; 
  Yellow  = (flag & (0x03<<4)) == 0x01<<4; 
  Red     = (flag & (0x03<<6)) == 0x01<<6; 
  
  return true;
}







