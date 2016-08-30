# RV-C

##RV-C:  Support library to extend NMEA2000 with addition of RV-C


This library extends the capability of Tim Lappaliainen's NMEA2000 (http: https://github.com/ttlappalainen/NMEA2000) with PGNs for RV-C

You will also need the appropriate underlying hardware CAN libraries, reference NMEA2000 above for details.


RV-C is an industry standard open-source CAN protocol:  http://rv-c.com, 
[RV-C specification PDF](http://www.rv-c.com/?q=node/75)


Like NMEA2000, RV-C is built upon the J1939 standard in a non-exclusive manner.


August 29, 2016 note: **DERIVATIONS FROM RV-C SPECIFICATION**.

The current release of RVCMessages contains one proposed addition to the RV-C specification, *Charger Status 2.*  
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


In addition, a ```Charger Type``` designation has been added to all the 'Charger' DGNs via the upper nibble of the existing Instance byte. (6.21.x in December 2015 release of RV-C spec).  This allows for a common approach to all charging sources, while being able to segregate the different type of chargers.


Users should take note of these submitted RV-C spec change requests and look for an update (Specificly, the DGN # for Charger Status2).


## Please note, this lib is under development.  Several functions have not been tested - so expect bugs to be found and corrected.