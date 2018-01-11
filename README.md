# RV-C

##RV-C:  Support library to extend NMEA2000 with addition of RV-C


This library extends the capability of Tim Lappaliainen's NMEA2000 (http: https://github.com/ttlappalainen/NMEA2000) with PGNs for RV-C

You will also need the appropriate underlying hardware CAN libraries, reference NMEA2000 above for details.


RV-C is an industry standard open-source CAN protocol:  http://rv-c.com, 
[RV-C specification PDF](http://www.rv-c.com/?q=node/75)


Like NMEA2000, RV-C is built upon the J1939 standard in a non-exclusive manner.

<br>
<br><br>
<br>

#### **DERIVATIONS FROM RV-C SPECIFICATION**.

Every attempt has been made to align OSEnergy with the RV-C specification, however as development continues areas have been identified which require a deviation.  The following documents the specific deviations.  Changes have been submitted to RV-C standard committee for consideration, and this guide will be updated pending the resolution of those submissions.

<br>

Addition to the RV-C specification:  *Charger Status 2.*  
It is currently enabled by reusing the retired PGN @ 1FF9Dh.   

```  
// Charger Status2 - 1FF9Dh  (PROPOSED, TEMP USING OLD BRIDGE_DGN_LIST DGN #)  
// Input:  
//  - Instance              Instance of charger  
//  - DC Source Instance    DC Instance (bus) ID associated with  
//  - Device Priority       Relative ranking of DC charging Source  
//  - DC Voltage            0..3212.5v, in 50mV steps  
//  - DC Current            -1600..1612.5a, in 50mA steps (0x7D00 = 0A)  
//  - Temperature           -40..210 in deg-C, in 1C steps
```

<br>
<br>


 ```Charger Type``` designation has been added to all the 'Charger' DGNs via the upper nibble of the existing Instance byte. (6.21.x in December 2015 release of RV-C spec).  This allows for a common approach to all charging sources, while being able to segregate the different type of chargers.  With this, device specific DC charging messages not be used.


<br>
<br>

**Global usage of Generator Instance.**
RV-C specification assumes only one generator per vehicle.  Many applications support more than one generator. An extension is to use the Generator Instance bits 0..3 as per the following:

```
| Byte | Bit    | Name     | Data Type | Unit | Value Description                    |
|------|--------|----------|-----------|------|--------------------------------------|
| 0    | 0 to 4 | Instance | bit4      | -    | 0000- not used  <b>  1110 - not used |
|      | 5 to 7 | RESERVED | bit4      | -    | 0000b                                |
```
Note that the Generator Instance nibble will be the same as the Charger instance nibble

<br>
<br>


## Please note, this lib is under development.  Several functions have not been tested - so expect bugs to be found and corrected.
