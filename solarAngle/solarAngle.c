#include "solarAngle.h"
#include "stdio.h"
#include "math.h"

const int monthDay[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

double typAngle2Angle(typANGLE tAngle) {
    return (double) tAngle.Angle + (double) tAngle.min / 60 + (double) tAngle.sec / 3600;
}

double MOD(double num, double divisor) {
    double a = num / divisor;
    if (num < 0)
        a--;
    return num - (int) a * divisor;
}

double radians(double Angle) {
    //M_PI/180 = 0.0174532925199433
    return Angle * 0.0174532925199433;
}

double degrees(double radian) {
    return radian * 180 * M_1_PI;
}

int dateVlue(typTIME time) {
    int years = time.year;
    int leapYearNum = (years % 100) / 4 + 1;
    if ((time.month <= 2) && (time.year % 4 == 0)) {
        leapYearNum -= 1;
    }
    int days = years * 365 + leapYearNum + time.date;
    for (int i = 0; i < time.month - 1; i++) {
        days += monthDay[i];
    }
    return days + 36525;
}

double julianDay(typTIME time, int utc) {
    int dateNum = dateVlue(time);
    double hour = ((double) time.hour * 3600 + (double) time.min * 60 + (double) time.sec) / 86400;
    return dateNum + 2415018.5 + hour - (double) utc / 24;
}

double julianCentury(double julianDayNum) {
    return (julianDayNum - 2451545) / 36525;
}

double GeomMeanLongSun(double julianCenturyNum) {
    double GeomMeanLongSunNum = 280.46646 + julianCenturyNum * (36000.76983 + julianCenturyNum * 0.0003032);
    int modNum = (int) GeomMeanLongSunNum / 360;
    GeomMeanLongSunNum -= modNum * 360;
    return GeomMeanLongSunNum;
}

double GeomMeanAnomSun(double julianDayNum) {
    double GeomMeanAnomSunNum = 357.52911 + julianDayNum * (35999.05029 - 0.0001537 * julianDayNum);
    return GeomMeanAnomSunNum;
}

double EccentEarthOrbit(double julianCenturyNum) {
    return 0.016708634 - julianCenturyNum * (0.000042037 + 0.0000001267 * julianCenturyNum);
}

double SunEqOfCtr(double julianCenturyNum, double GeomMeanAnomSunNum) {
    return sin(radians(GeomMeanAnomSunNum)) * (1.914602 - julianCenturyNum * (0.004817 + 0.000014 * julianCenturyNum)) +
           sin(radians(2 * GeomMeanAnomSunNum)) * (0.019993 - 0.000101 * julianCenturyNum) +
           sin(radians(3 * GeomMeanAnomSunNum)) * 0.000289;
}

double SunTrueLong(double GeomMeanLongSunNum, double SunEqOfCtrNum) {
    return GeomMeanLongSunNum + SunEqOfCtrNum;
}

double SunTrueAnom(double GeomMeanAnomSunNum, double SunEqOfCtrNum) {
    return GeomMeanAnomSunNum + SunEqOfCtrNum;
}

double SunRadVector(double EccentEarthOrbitNum, double SunTrueAnomNum) {
    return (1.000001018 * (1 - EccentEarthOrbitNum * EccentEarthOrbitNum)) /
           (1 + EccentEarthOrbitNum * cos(radians(SunTrueAnomNum)));
}

double SunAppLong(double SunTrueLongNum, double julianCenturyNum) {
    return SunTrueLongNum - 0.00569 - 0.00478 * sin(radians(125.04 - 1934.136 * julianCenturyNum));
}

double MeanObliqEcliptic(double julianCenturyNum) {
    return 23 + (26 +
                 ((21.448 - julianCenturyNum * (46.815 + julianCenturyNum * (0.00059 - julianCenturyNum * 0.001813)))) /
                 60) / 60;
}

double ObliqCorr(double MeanObliqEclipticNum, double julianCenturyNum) {
    return MeanObliqEclipticNum + 0.00256 * (cos(radians(125.04 - 1934.136 * julianCenturyNum)));
}

double SunRtAscen(double SunAppLongNum, double ObliqCorrNum) {
    return degrees(atan2(cos(radians(ObliqCorrNum)) * sin(radians(SunAppLongNum)), cos(radians(SunAppLongNum))));
}

double SunDeclin(double SunAppLongNum, double ObliqCorrNum) {
    return degrees(asin(sin(radians(SunAppLongNum)) * sin(radians(ObliqCorrNum))));
}

double varY(double ObliqCorrNum) {
    return tan(radians(ObliqCorrNum / 2)) * tan(radians(ObliqCorrNum / 2));
}

double EqOfTime(double varYNum, double GeomMeanLongSunNum, double GeomMeanAnomSunNum, double EccentEarthOrbitNum) {
    return 4 * degrees(varYNum * sin(2 * radians(GeomMeanLongSunNum)) -
                       2 * EccentEarthOrbitNum * sin(radians(GeomMeanAnomSunNum)) +
                       4 * EccentEarthOrbitNum * varYNum * sin(radians(GeomMeanAnomSunNum)) *
                       cos(2 * radians(GeomMeanLongSunNum)) -
                       0.5 * varYNum * varYNum * sin(4 * radians(GeomMeanLongSunNum)) -
                       1.25 * EccentEarthOrbitNum * EccentEarthOrbitNum * sin(2 * radians(GeomMeanAnomSunNum)));
}

double HASunrise(typANGLE Latitude, double SunDeclinNum) {
    return degrees(acos(cos(radians(90.833)) / (cos(radians(typAngle2Angle(Latitude))) * cos(radians(SunDeclinNum))) -
                        tan(radians(typAngle2Angle(Latitude))) * tan(radians(SunDeclinNum))));
}

double SolarNoon(typANGLE Longitude, int utc, double EqOfTimeNum) {
    return (720 - 4 * typAngle2Angle(Longitude) - EqOfTimeNum + utc * 60) / 1440;
}

double SunriseTime(double SolarNoonNum, double HASunriseNum) {
    return SolarNoonNum - HASunriseNum * 4 / 1440;
}

double SunsetTime(double SolarNoonNum, double HASunriseNum) {
    return SolarNoonNum + HASunriseNum * 4 / 1440;
}

double SunlightDuration(double HASunriseNum) {
    return 8 * HASunriseNum;
}

double TrueSolarTime(typTIME time, double EqOfTimeNum, typANGLE Longitude, int utc) {
    double hour = ((double) time.hour * 3600 + (double) time.min * 60 + (double) time.sec) / 86400;
    return MOD(hour * 1440 + EqOfTimeNum + 4 * typAngle2Angle(Longitude) - 60 * utc, 1440);
}

double HourAngle(double TrueSolarTimeNum) {
    if (TrueSolarTimeNum / 4 < 0) {
        return TrueSolarTimeNum / 4 + 180;
    }
    else {
        return TrueSolarTimeNum / 4 - 180;
    }
}

double SolarZenithAngle(typANGLE Latitude, double SunDeclinNum, double HourAngleNum) {
    return degrees(acos(sin(radians(typAngle2Angle(Latitude))) * sin(radians(SunDeclinNum)) +
                        cos(radians(typAngle2Angle(Latitude))) * cos(radians(SunDeclinNum)) *
                        cos(radians(HourAngleNum))));
}

double SolarElevationAngle(double SolarZenithAngleNum) {
    return 90 - SolarZenithAngleNum;
}

double ApproxAtmosphericRefraction(double SolarElevationAngleNum) {
    double ApproxAtmosphericRefractionNum = 0;
    if (SolarElevationAngleNum > 85) {
        ApproxAtmosphericRefractionNum = 0;
    }
    else {
        if (SolarElevationAngleNum > 5) {
            ApproxAtmosphericRefractionNum =
                    58.1 / tan(radians(SolarElevationAngleNum)) - 0.07 / pow(tan(radians(SolarElevationAngleNum)), 3) +
                    0.000086 / pow(tan(radians(SolarElevationAngleNum)), 5);
        }
        else {
            if (SolarElevationAngleNum > -0.575) {
                ApproxAtmosphericRefractionNum = 1735 + SolarElevationAngleNum * (-518.2 + SolarElevationAngleNum *
                                                                                           (103.4 +
                                                                                            SolarElevationAngleNum *
                                                                                            (-12.79 +
                                                                                             SolarElevationAngleNum *
                                                                                             0.711)));
            }
            else {
                ApproxAtmosphericRefractionNum = (-20.772) / tan(radians(SolarElevationAngleNum));
            }
        }
    }
    return ApproxAtmosphericRefractionNum / 3600;
}

double SolarElevationCorrectedForAtmRefraction(double SolarElevationAngleNum, double ApproxAtmosphericRefractionNum) {
    return SolarElevationAngleNum + ApproxAtmosphericRefractionNum;
}

double SolarAzimuthAngle(typANGLE Latitude, double SunDeclinNum, double HourAngleNum, double SolarZenithAngleNum) {
    double SolarAzimuthAngleNum = degrees(
            acos(((sin(radians(typAngle2Angle(Latitude))) * cos(radians(SolarZenithAngleNum))) -
                  sin(radians(SunDeclinNum))) /
                 (cos(radians(typAngle2Angle(Latitude))) * sin(radians(SolarZenithAngleNum)))));
    if (HourAngleNum > 0) {
        return MOD(SolarAzimuthAngleNum+180, 360);
    }
    else {
        return MOD(540 - SolarAzimuthAngleNum, 360);
    }
}
