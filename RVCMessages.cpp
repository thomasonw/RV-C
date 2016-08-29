//  RVCMessages.cpp
//
//
//      Copyright (c) 2016 by William A. Thomason.      http://arduinoalternatorregulator.blogspot.com/
//                                                      https://github.com/thomasonw/RV-C
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
//                      'Charger Status2' @ 1FF9Dh  (PROPOSED, TEMP USING OLD BRIDGE_DGN_LIST DGN #)
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
                      int16_t Temp, uint8_t SOC, uint16_t TR) {
    N2kMsg.SetPGN(0x1FFFC);
    N2kMsg.Priority=6;
    N2kMsg.AddByte(Instance);
    N2kMsg.AddByte(DevPri);
    N2kMsg.Add2ByteInt(Temp);
    N2kMsg.AddByte(SOC);
    N2kMsg.Add2ByteUInt(TR);
}

bool ParseRVCPGN1FFFC(const tN2kMsg &N2kMsg, uint8_t &Instance, uint8_t &DevPri, 
                       int16_t &Temp, uint8_t &SOC, uint16_t &TR) {
  if (N2kMsg.PGN!=0x1FFFC) return false;

  int Index=0;
  
  Instance=N2kMsg.GetByte(Index);
  DevPri=N2kMsg.GetByte(Index);
  Temp=N2kMsg.Get2ByteInt(Index);
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
    N2kMsg.AddByte((unsigned char)BatType || 0xf0);                        /* Unused bits must be set to 1's */
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
  BatType=(tRVCBatType)(N2kMsg.GetByte(Index) && 0x0f);        /* Mask out lower 4 bits */
    
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
    
  HVls   = (flag && 0x03   ) == 0x01;  
  HVld   = (flag && 0x03<<2) == 0x01<<2; 
  LVls   = (flag && 0x03<<4) == 0x01<<4; 
  LVld   = (flag && 0x03<<6) == 0x01<<6; 
  
  return true;
}





//*****************************************************************************
// DC Disconnect Status
void SetRVCPGN1FED0(tN2kMsg &N2kMsg, uint8_t Instance, bool CirCon, bool RecDisCom, bool Bypassed) {
    uint8_t  flag = 0xC0;               /* Unused bits must be set high */

    if (CirCon)     flag |= 0x01;
    if (!RecDisCom) flag |= 0x01<<2;
    if (Bypassed)   flag |= 0x01<<4;
    
    N2kMsg.SetPGN(0x1FED0);
    N2kMsg.Priority=6;
    N2kMsg.AddByte(Instance);
    N2kMsg.AddByte(flag);

}

bool ParseRVCPGN1FED0(const tN2kMsg &N2kMsg, uint8_t &Instance, bool &CirCon, bool &RecDisCom, bool &Bypassed) {
  if (N2kMsg.PGN!=0x1FED0) return false;

  int Index=0;
  uint8_t  flag;
  
  Instance=N2kMsg.GetByte(Index);
  flag=N2kMsg.GetByte(Index);
     
  CirCon     = (flag && 0x03   ) == 0x01;  
  RecDisCom  = (flag && 0x03<<2) == 0x01<<2; 
  Bypassed   = (flag && 0x03<<4) == 0x01<<4; 
  
  return true;
}





//*****************************************************************************
// DC Disconnect Command
void SetRVCPGN1FECF(tN2kMsg &N2kMsg, uint8_t Instance, bool Disconnect) {
    uint8_t  flag = 0xFC;               /* Unused bits must be set high */

    if (Disconnect)  flag |= 0x01;

    
    N2kMsg.SetPGN(0x1FECF);
    N2kMsg.Priority=6;
    N2kMsg.AddByte(Instance);
    N2kMsg.AddByte(flag);

}

bool ParseRVCPGN1FECF(const tN2kMsg &N2kMsg, uint8_t &Instance, bool &DisCmd) {
  if (N2kMsg.PGN!=0x1FECF) return false;

  int Index=0;
  uint8_t  flag;
  
  Instance=N2kMsg.GetByte(Index);
  flag=N2kMsg.GetByte(Index);
    
  DisCmd  = (flag && 0x03   ) == 0x01;  
  
  return true;
}





//*****************************************************************************
// Charger Status - 1FFC7h
void SetRVCPGN1FFC7(tN2kMsg &N2kMsg, uint8_t Instance, uint16_t CVdc, uint16_t CAdc, uint8_t PerMax,
                    tRVCBatChrgMode State, bool EnableAtPO, bool AutoRechg, tRVCChrgForceChrg ForcedChrg){
    uint8_t  flag;     
    
    flag = ForcedChrg << 4;
    if (EnableAtPO) flag |= 0x01;
    if (AutoRechg)  flag |= 0x01<<2;
    
    N2kMsg.SetPGN(0x1FFC7);
    N2kMsg.Priority=6;
    N2kMsg.AddByte(Instance);
    N2kMsg.Add2ByteUInt(CVdc);
    N2kMsg.Add2ByteUInt(CAdc);
    N2kMsg.AddByte(PerMax);
    N2kMsg.AddByte((uint8_t)State);
    N2kMsg.AddByte(flag);                    
}

bool ParseRVCPGN1FFC7(const tN2kMsg &N2kMsg, uint8_t &Instance, uint16_t &CVdc, uint16_t &CAdc, uint8_t &PerMax,
                            tRVCBatChrgMode &State, bool &EnableAtPO, bool &AutoRechg, tRVCChrgForceChrg &ForcedChrg){                           
  if (N2kMsg.PGN!=0x1FEC7) return false;

  int     Index=0;
  uint8_t flag;
  
  Instance=N2kMsg.GetByte(Index);
  CVdc=N2kMsg.Get2ByteUInt(Index);
  CAdc=N2kMsg.Get2ByteUInt(Index);
  PerMax=N2kMsg.GetByte(Index);
  State=(tRVCBatChrgMode)N2kMsg.GetByte(Index);
  flag=N2kMsg.GetByte(Index);
    
  EnableAtPO = (flag && 0x03   ) == 0x01;  
  AutoRechg  = (flag && 0x03<<2) == 0x01<<2;   
  ForcedChrg = (tRVCChrgForceChrg) (flag >> 4);
  
  return true;
}


////////////////   THIS IS A PROPOSED ONE!!!!!!  ???????????????????????????????
//*****************************************************************************
// Charger Status2 - 1FF9Dh  (PROPOSED, TEMP USING OLD BRIDGE_DGN_LIST DGN #)
#warning CHARGER STATUS2 USING TEMP PGN#1FF9Dh 
void SetRVCPGN1FF9D(tN2kMsg &N2kMsg, uint8_t ChrgInst, uint8_t DCInst, uint8_t DevPri, uint16_t Vdc, uint16_t Adc, uint8_t Temp) {
    N2kMsg.SetPGN(0x1FF9D);
    N2kMsg.Priority=6;
    N2kMsg.AddByte(ChrgInst);
    N2kMsg.AddByte(DCInst);
    N2kMsg.AddByte(DevPri);
    N2kMsg.Add2ByteUInt(Vdc);
    N2kMsg.Add2ByteUInt(Adc);
    N2kMsg.AddByte(Temp);
}

bool ParseRVCPGN1FF9D(const tN2kMsg &N2kMsg, uint8_t &ChrgInst, uint8_t &DCInst, uint8_t &DevPri, uint16_t &Vdc, uint16_t &Adc, uint8_t &Temp) {
  if (N2kMsg.PGN!=0x1FF9D) return false;

  int Index=0;
  
  ChrgInst=N2kMsg.GetByte(Index);
  DCInst=N2kMsg.GetByte(Index);
  DevPri=N2kMsg.GetByte(Index);
  Vdc=N2kMsg.Get2ByteUInt(Index);
  Adc=N2kMsg.Get2ByteUInt(Index);
  Temp=N2kMsg.GetByte(Index);
  return true; 
}
  

  
  
  
//*****************************************************************************
// Charger Command - 1FFC5h
void SetRVCPGN1FFC5(tN2kMsg &N2kMsg, uint8_t Instance, tRVCChrgStatus ChrgStat,  
                       bool EnableAtPO, bool AutoRechg, tRVCChrgForceChrg ForcedChrg){
    uint8_t  flag;     
    
    flag = ForcedChrg << 4;
    if (EnableAtPO) flag |= 0x01;
    if (AutoRechg)  flag |= 0x01<<2;
    
    N2kMsg.SetPGN(0x1FFC5);
    N2kMsg.Priority=6;
    N2kMsg.AddByte(Instance);
    N2kMsg.AddByte((uint8_t)ChrgStat);
    N2kMsg.AddByte(flag);  
    //N2kMsg.AddByte(0Xff);
    //N2kMsg.AddByte(0Xff);
    //N2kMsg.AddByte(0Xff);
    //N2kMsg.AddByte(0Xff);
    //N2kMsg.AddByte(0Xff);    
}

bool ParseRVCPGN1FFC5(const tN2kMsg &N2kMsg, uint8_t &Instance, tRVCChrgStatus &ChrgStat, 
                                            bool &EnableAtPO, bool &AutoRechg, tRVCChrgForceChrg &ForcedChrg){
  if (N2kMsg.PGN!=0x1FEC5) return false;

  int     Index=0;
  uint8_t flag;
  
  Instance=N2kMsg.GetByte(Index);
  ChrgStat=(tRVCChrgStatus)N2kMsg.GetByte(Index);
  flag=N2kMsg.GetByte(Index);
    
  
  EnableAtPO = (flag && 0x03   ) == 0x01;  
  AutoRechg  = (flag && 0x03<<2) == 0x01<<2;  
  
  ForcedChrg = (tRVCChrgForceChrg) (flag >> 4);
  
  return true;
}



//*****************************************************************************
// Charger Configuration Status - 1FFC6h
void SetRVCPGN1FFC6(tN2kMsg &N2kMsg, uint8_t Instance, tRVCChrgAlg  ChrgAlg,  tRVCChrgMode  ChrgMode, 
                       bool BatSense, tRVCChrgLine Line, bool Linked, tRVCBatType BatType,  uint16_t BatSize, uint8_t MaxAmps){
    uint8_t  flag;     
    
    flag = BatType << 4;
    if (BatSense) flag |= 0x01;
    if (Linked)   flag |= 0x01<<2;
    
    N2kMsg.SetPGN(0x1FFC6);
    N2kMsg.Priority=6;
    N2kMsg.AddByte(Instance);
    N2kMsg.AddByte((uint8_t)ChrgAlg);
    N2kMsg.AddByte((uint8_t)ChrgMode);
    N2kMsg.AddByte(flag); 
    N2kMsg.Add2ByteUInt(BatSize);    
    N2kMsg.AddByte(MaxAmps);
}

bool ParseRVCPGN1FFC6(const tN2kMsg &N2kMsg, uint8_t &Instance, tRVCChrgAlg  &ChrgAlg,  tRVCChrgMode  &ChrgMode, 
                               bool &BatSense, tRVCChrgLine &Line, bool &Linked, tRVCBatType &BatType,  uint16_t &BatSize, uint8_t &MaxAmps){
  if (N2kMsg.PGN!=0x1FEC6) return false;

  int     Index=0;
  uint8_t flag;
  
  Instance=N2kMsg.GetByte(Index);
  ChrgAlg=(tRVCChrgAlg)N2kMsg.GetByte(Index);
  ChrgMode=(tRVCChrgMode)N2kMsg.GetByte(Index);
  flag=N2kMsg.GetByte(Index);
  BatSize=N2kMsg.Get2ByteUInt(Index);
  MaxAmps=N2kMsg.Get2ByteUInt(Index);
    
  BatSense = (flag && 0x03   ) == 0x01;  
  Linked   = (flag && 0x03<<2) == 0x01<<2;  
  BatType  = (tRVCBatType) (flag >> 4);
  
  return true;
}


//*****************************************************************************
// Charger Configuration Status2 - 1FF96h
void SetRVCPGN1FF96(tN2kMsg &N2kMsg, uint8_t Instance, uint8_t PerMaxAmps, uint8_t PerMaxShore, uint8_t ShorBr, uint8_t DefBatTemp, uint16_t RchgVolt){
    N2kMsg.SetPGN(0x1FF96);
    N2kMsg.Priority=6;
    N2kMsg.AddByte(Instance);
    N2kMsg.AddByte(PerMaxAmps);
    N2kMsg.AddByte(PerMaxShore);
    N2kMsg.AddByte(DefBatTemp); 
    N2kMsg.Add2ByteUInt(RchgVolt); 
    //N2kMsg.Add2ByteUInt(0xFF);    
}

bool ParseRVCPGN1FF96(const tN2kMsg &N2kMsg, uint8_t &Instance, uint8_t &PerMaxAmps, uint8_t &PerMaxShore, uint8_t &DefBatTemp, uint16_t &RchgVolt) {
  if (N2kMsg.PGN!=0x1FF96) return false;

  int     Index=0;
  
  Instance=N2kMsg.GetByte(Index);
  PerMaxAmps=N2kMsg.GetByte(Index);
  PerMaxShore=N2kMsg.GetByte(Index);
  DefBatTemp=N2kMsg.GetByte(Index);
  RchgVolt=N2kMsg.Get2ByteUInt(Index);
  
  return true;
}


//*****************************************************************************
// Charger Configuration Status3 - 1FECCh
void SetRVCPGN1FECC(tN2kMsg &N2kMsg, uint8_t Instance, uint16_t BulkV, uint16_t AbsorbV, uint16_t FloatV, uint8_t TempComp){
    N2kMsg.SetPGN(0x1FECC);
    N2kMsg.Priority=6;
    N2kMsg.AddByte(Instance);
    N2kMsg.Add2ByteUInt(BulkV);   
    N2kMsg.Add2ByteUInt(AbsorbV);   
    N2kMsg.Add2ByteUInt(FloatV);   
    N2kMsg.AddByte(TempComp);
}

bool ParseRVCPGN1FECC(const tN2kMsg &N2kMsg, uint8_t &Instance, uint16_t &BulkV, uint16_t &AbsorbV, uint16_t &FloatV, uint8_t &TempComp) {
  if (N2kMsg.PGN!=0x1FECC) return false;

  int     Index=0;
  
  Instance=N2kMsg.GetByte(Index);
  BulkV=N2kMsg.Get2ByteUInt(Index);
  AbsorbV=N2kMsg.Get2ByteUInt(Index);
  FloatV=N2kMsg.Get2ByteUInt(Index);
  TempComp=N2kMsg.GetByte(Index);
  
  return true;
}


//*****************************************************************************
// Charger Configuration Status4 - 1FEBFh
void SetRVCPGN1FEBF(tN2kMsg &N2kMsg, uint8_t Instance, uint16_t BulkT, uint16_t AbsorbT, uint16_t FloatT){
    N2kMsg.SetPGN(0x1FEBF);
    N2kMsg.Priority=6;
    N2kMsg.AddByte(Instance);
    N2kMsg.Add2ByteUInt(BulkT);   
    N2kMsg.Add2ByteUInt(AbsorbT);   
    N2kMsg.Add2ByteUInt(FloatT);  
    //N2kMsg.AddByte(0Xff);
}

bool ParseRVCPGN1FEBF(const tN2kMsg &N2kMsg, uint8_t &Instance, uint16_t &BulkT, uint16_t &AbsorbT, uint16_t &FloatT){
  if (N2kMsg.PGN!=0x1FEBF) return false;

  int     Index=0;
  
  Instance=N2kMsg.GetByte(Index);
  BulkT=N2kMsg.Get2ByteUInt(Index);
  AbsorbT=N2kMsg.Get2ByteUInt(Index);
  FloatT=N2kMsg.Get2ByteUInt(Index);
  
  return true;
}  
    


//*****************************************************************************
// Charger Configuration Command - 1FFC4h
void SetRVCPGN1FFC4(tN2kMsg &N2kMsg, uint8_t Instance, tRVCChrgAlg  ChrgAlg,  tRVCChrgMode  ChrgMode, 
                       bool BatSense, tRVCChrgLine Line, bool Linked,  tRVCBatType BatType,  uint16_t BatSize, uint8_t MaxAmps){
    
    uint8_t  flag;    
    
    flag = (Line << 2) | 0xF0;                                           // Unused bits set to 1's 
    if (BatSense) flag |= 0x01;
    

    N2kMsg.SetPGN(0x1FFC4);
    N2kMsg.Priority=6;
    N2kMsg.AddByte(Instance);
    N2kMsg.AddByte((uint8_t)ChrgAlg);
    N2kMsg.AddByte((uint8_t)ChrgMode);
    N2kMsg.AddByte(flag);
    N2kMsg.Add2ByteUInt(BatSize);   
    N2kMsg.AddByte((uint8_t)BatType | 0xF0);
    N2kMsg.AddByte(MaxAmps);
}

bool ParseRVCPGN1FFC4(const tN2kMsg &N2kMsg, uint8_t &Instance, tRVCChrgAlg  &ChrgAlg,  tRVCChrgMode  &ChrgMode, 
                               bool &BatSense, tRVCChrgLine &Line, bool &Linked,  tRVCBatType &BatType,  uint16_t &BatSize, uint8_t &MaxAmps){
  if (N2kMsg.PGN!=0x1FFC4) return false;

  int     Index=0;
  uint8_t flag;
  
  Instance=N2kMsg.GetByte(Index);
  ChrgAlg=(tRVCChrgAlg)N2kMsg.GetByte(Index);
  ChrgMode=(tRVCChrgMode)N2kMsg.GetByte(Index);
  flag=N2kMsg.GetByte(Index);
  BatSize=N2kMsg.Get2ByteUInt(Index);
  BatType=(tRVCBatType)(N2kMsg.GetByte(Index) & 0x0F);
  MaxAmps=N2kMsg.GetByte(Index);
    
  BatSense = (flag && 0x03) == 0x01;  
  Line     = (tRVCChrgLine) ((flag >> 2) & 0x0F);
  
  return true;
}
  


//*****************************************************************************
// Charger Configuration Command2 - 1FF95h
void SetRVCPGN1FF95(tN2kMsg &N2kMsg, uint8_t Instance, uint8_t PerMaxAmps, uint8_t PerMaxShore, uint8_t ShorBr, uint8_t DefBatTemp, uint16_t RchgVolt){
    
    N2kMsg.SetPGN(0x1FF95);
    N2kMsg.Priority=6;
    N2kMsg.AddByte(Instance);
    N2kMsg.AddByte(PerMaxAmps);
    N2kMsg.AddByte(PerMaxShore);
    N2kMsg.AddByte(ShorBr);
    N2kMsg.AddByte(DefBatTemp);
    N2kMsg.Add2ByteUInt(RchgVolt); 
    //N2kMsg.AddByte(0Xff);    
}

bool ParseRVCPGN1FF95(const tN2kMsg &N2kMsg, uint8_t &Instance, uint8_t &PerMaxAmps, uint8_t &PerMaxShore, uint8_t &ShorBr, uint8_t &DefBatTemp, uint16_t &RchgVolt){
  if (N2kMsg.PGN!=0x1FFC4) return false;
  
  int     Index=0;
    
  Instance=N2kMsg.GetByte(Index);
  PerMaxAmps=N2kMsg.GetByte(Index);
  PerMaxShore=N2kMsg.GetByte(Index);
  ShorBr=N2kMsg.GetByte(Index);
  DefBatTemp=N2kMsg.GetByte(Index);
  RchgVolt=N2kMsg.Get2ByteUInt(Index);
  
  return true;  
}



//*****************************************************************************
// Charger Configuration Command3 - 1FECBh
void SetRVCPGN1FECB(tN2kMsg &N2kMsg, uint8_t Instance, uint16_t BulkV, uint16_t AbsorbV, uint16_t FloatV, uint8_t TempComp){
    N2kMsg.SetPGN(0x1FECB);
    N2kMsg.Priority=6;
    N2kMsg.AddByte(Instance);
    N2kMsg.Add2ByteUInt(BulkV);   
    N2kMsg.Add2ByteUInt(AbsorbV);   
    N2kMsg.Add2ByteUInt(FloatV);   
    N2kMsg.AddByte(TempComp);
    
}

bool ParseRVCPGN1FECB(const tN2kMsg &N2kMsg, uint8_t &Instance, uint16_t &BulkV, uint16_t &AbsorbV, uint16_t &FloatV, uint8_t &TempComp){
  if (N2kMsg.PGN!=0x1FECB) return false;
  
  int     Index=0;

  Instance=N2kMsg.GetByte(Index);
  BulkV=N2kMsg.Get2ByteUInt(Index);
  AbsorbV=N2kMsg.Get2ByteUInt(Index);
  FloatV=N2kMsg.Get2ByteUInt(Index);
  TempComp=N2kMsg.GetByte(Index); 
  
  return true;
}


//*****************************************************************************
// Charger Configuration Command4 - 1FEBEh
void SetRVCPGN1FEBE(tN2kMsg &N2kMsg, uint8_t Instance, uint16_t BulkT, uint16_t AbsorbT, uint16_t FloatT){

    N2kMsg.SetPGN(0x1FEBE);
    N2kMsg.Priority=6;
    N2kMsg.AddByte(Instance);
    N2kMsg.Add2ByteUInt(BulkT);   
    N2kMsg.Add2ByteUInt(AbsorbT);   
    N2kMsg.Add2ByteUInt(FloatT);  
    //N2kMsg.AddByte(0Xff);
}

bool ParseRVCPGN1FEBE(const tN2kMsg &N2kMsg, uint8_t &Instance, uint16_t &BulkT, uint16_t &AbsorbT, uint16_t &FloatT){
  if (N2kMsg.PGN!=0x1FEBE) return false;

  int     Index=0;
  
  Instance=N2kMsg.GetByte(Index);
  BulkT=N2kMsg.Get2ByteUInt(Index);
  AbsorbT=N2kMsg.Get2ByteUInt(Index);
  FloatT=N2kMsg.Get2ByteUInt(Index); 

  return true;  
}





//*****************************************************************************
// Charger Equalization Status - 1FF99h
void SetRVCPGN1FF99(tN2kMsg &N2kMsg, uint8_t Instance, uint16_t Time, bool PreChrg){
    uint8_t  flag = 0xFC;                                         // Unused bits set to 1's 
    if (PreChrg) flag |= 0x01;
        
    N2kMsg.SetPGN(0x1FF99);
    N2kMsg.Priority=6;
    N2kMsg.AddByte(Instance);
    N2kMsg.Add2ByteUInt(Time);   
    N2kMsg.AddByte(flag);
    //N2kMsg.AddByte(0Xff);
    //N2kMsg.AddByte(0Xff);
    //N2kMsg.AddByte(0Xff);
    //N2kMsg.AddByte(0Xff);
}

bool ParseRVCPGN1FF99(const tN2kMsg &N2kMsg, uint8_t &Instance, uint16_t &Time, bool &PreChrg){
  if (N2kMsg.PGN!=0x1FF99) return false;

  int     Index=0;
  uint8_t flag;
  
  Instance=N2kMsg.GetByte(Index);
  Time=N2kMsg.Get2ByteUInt(Index);
  flag=N2kMsg.GetByte(Index);
  
  PreChrg = (flag && 0x03) == 0x01;  

  return true;  
}







//*****************************************************************************
// Charger Equalization Configuration Status - 1FF98h

void SetRVCPGN1FF98(tN2kMsg &N2kMsg, uint8_t Instance, uint16_t Volts, uint16_t Time){
    
    N2kMsg.SetPGN(0x1FF98);
    N2kMsg.Priority=6;
    N2kMsg.AddByte(Instance);
    N2kMsg.Add2ByteUInt(Volts);   
    N2kMsg.Add2ByteUInt(Time);   
    //N2kMsg.AddByte(0Xff);
    //N2kMsg.AddByte(0Xff);
    //N2kMsg.AddByte(0Xff);
}

bool ParseRVCPGN1FF98(const tN2kMsg &N2kMsg, uint8_t &Instance, uint16_t &Volts, uint16_t &Time){
   if (N2kMsg.PGN!=0x1FF98) return false;

  int     Index=0;
  
  Instance=N2kMsg.GetByte(Index);
  Volts=N2kMsg.Get2ByteUInt(Index);
  Time=N2kMsg.Get2ByteUInt(Index);
  
  return true;
}






//*****************************************************************************
// Charger Equalization Configuration Command - 1FF97h
void SetRVCPGN1FF97(tN2kMsg &N2kMsg, uint8_t Instance, uint16_t Volts, uint16_t Time){
    
    N2kMsg.SetPGN(0x1FF97);
    N2kMsg.Priority=6;
    N2kMsg.AddByte(Instance);
    N2kMsg.Add2ByteUInt(Volts);   
    N2kMsg.Add2ByteUInt(Time);   
    //N2kMsg.AddByte(0Xff);
    //N2kMsg.AddByte(0Xff);
    //N2kMsg.AddByte(0Xff);    
}

bool ParseRVCPGN1FF97(const tN2kMsg &N2kMsg, uint8_t &Instance, uint16_t &Volts, uint16_t &Time){
   if (N2kMsg.PGN!=0x1FF97) return false;

  int     Index=0;
  
  Instance=N2kMsg.GetByte(Index);
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
    
    N2kMsg.AddByte(Count);
    for (i = 0; ((i < Count) && (i < 8)); i++)  N2kMsg.AddByte(*Characters++);
    for (; i < 8; i++)                          N2kMsg.AddByte(0xFF);                          // Pass unused data bytes with 0xFF per spec.      
}

              
bool ParseRVCPGN17E00(const tN2kMsg &N2kMsg, uint8_t &Source, int &Count, char characters[8]) {
  if ((N2kMsg.PGN & 0xFFFF00)!=0x17E00) return false;

  int Index=0;
  int i;
  
  Source=N2kMsg.Source;
  Count==N2kMsg.GetByte(Index);
  for (i=0; ((i < Count) && (i < 8)); i++)
      characters[i] = N2kMsg.GetByte(Index);

  return true;
       
    
    
}








//*****************************************************************************
// ISO Diagnostics Message - 1FECAh
void SetISOPGN1FECA(tN2kMsg &N2kMsg, bool On, bool Active, bool Red, bool Yellow, uint8_t DSA,
                    uint32_t SPN, tISOFMIType FMI, uint8_t Count, uint8_t DSA_ext, uint8_t Bank){
    
    uint8_t flag = 0x00;
    
    if (On)      flag |= 0x01;
    if (Active)  flag |= 0x01 << 2;
    if (Red)     flag |= 0x01 << 4;
    if (Yellow)  flag |= 0x01 << 6;
 
    
    N2kMsg.SetPGN(0x1FECA);
    N2kMsg.Priority=6;
    N2kMsg.AddByte(flag);
    N2kMsg.AddByte(DSA);
    N2kMsg.Add3ByteInt((int32_t) (SPN + (uint32_t)FMI)<<20);
    N2kMsg.AddByte(Count | 0x80);
    N2kMsg.AddByte(DSA_ext);
    N2kMsg.AddByte(Bank | 0xF0); 

}

bool ParseISOPGN1FECA(tN2kMsg &N2kMsg, bool &On, bool &Active, bool &Red, bool &Yellow, uint8_t DSA,
                    uint32_t &SPN, tISOFMIType &FMI, uint8_t &Count, uint8_t &DSA_ext, uint8_t &Bank){
   if (N2kMsg.PGN!=0x1FECA) return false;

  int     Index=0;
  uint8_t flag, part;
  
  
  flag=N2kMsg.GetByte(Index);
  DSA=N2kMsg.GetByte(Index);
  SPN=N2kMsg.GetByte(Index);
  SPN=N2kMsg.GetByte(Index)<<8;
  part=N2kMsg.GetByte(Index);
  Count=N2kMsg.GetByte(Index) & 0x7F;
  DSA_ext=N2kMsg.GetByte(Index);
  Bank=N2kMsg.GetByte(Index)  & 0x0F;
  
  FMI  = (tISOFMIType) (part>>4);
  SPN += (uint32_t)(part & 0x0F) << 16;
  
  On      = (flag && 0x03   ) == 0x01;  
  Active  = (flag && 0x03<<2) == 0x01<<2; 
  Red     = (flag && 0x03<<4) == 0x01<<4; 
  Yellow  = (flag && 0x03<<6) == 0x01<<6; 
  
  return true;
}







