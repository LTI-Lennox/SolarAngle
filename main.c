#include <stdio.h>
#include "math.h"
#include "solarAngle/solarAngle.h"

int main() {
    typTIME time;
    time.year = 22;
    time.month = 6;
    time.date = 13;
    time.hour = 0;
    time.min = 6;
    time.sec = 0;

    typANGLE latitude;
    latitude.Angle = 0;
    latitude.min = 0;
    latitude.sec = 0;

    typANGLE longitude;
    longitude.Angle = 0;
    longitude.min = 0;
    longitude.sec = 0;

    int utc = 8;

    printf("%d\n", dateVlue(time));

    double julianDayNum = julianDay(time, utc);
    printf("julianDayNum:%f\n", julianDayNum);

    double julianCenturyNum = julianCentury(julianDayNum);
    printf("julianCenturyNum:%f\n", julianCenturyNum);

    double GeomMeanLongSunNum = GeomMeanLongSun(julianCenturyNum);
    printf("GeomMeanLongSunNum:%f\n", GeomMeanLongSunNum);

    double GeomMeanAnomSunNum = GeomMeanAnomSun(julianCenturyNum);
    printf("GeomMeanAnomSunNum:%f\n", GeomMeanAnomSunNum);

    double EccentEarthOrbitNum = EccentEarthOrbit(julianCenturyNum);
    printf("EccentEarthOrbitNum:%f\n", EccentEarthOrbitNum);

    double SunEqOfCtrNum = SunEqOfCtr(julianCenturyNum, GeomMeanAnomSunNum);
    printf("SunEqOfCtrNum:%f\n", SunEqOfCtrNum);

    double SunTrueLongNum = SunTrueLong(GeomMeanLongSunNum, SunEqOfCtrNum);
    printf("SunTrueLongNum:%f\n", SunTrueLongNum);

    double SunTrueAnomNum = SunTrueAnom(GeomMeanAnomSunNum, SunEqOfCtrNum);
    printf("SunTrueAnomNum:%f\n", SunTrueAnomNum);

    double SunRadVectorNum = SunRadVector(EccentEarthOrbitNum, SunTrueAnomNum);
    printf("SunRadVectorNum:%f\n", SunRadVectorNum);

    double SunAppLongNum = SunAppLong(SunTrueLongNum, julianCenturyNum);
    printf("SunAppLongNum:%f\n", SunAppLongNum);

    double MeanObliqEclipticNum = MeanObliqEcliptic(julianCenturyNum);
    printf("MeanObliqEclipticNum:%f\n", MeanObliqEclipticNum);

    double ObliqCorrNum = ObliqCorr(MeanObliqEclipticNum, julianCenturyNum);
    printf("ObliqCorrNum:%f\n", ObliqCorrNum);

    double SunRtAscenNum = SunRtAscen(SunAppLongNum, ObliqCorrNum);
    printf("SunRtAscenNum:%f\n", SunRtAscenNum);

    double SunDeclinNum = SunDeclin(SunAppLongNum, ObliqCorrNum);
    printf("SunDeclinNum:%f\n", SunDeclinNum);

    double varYNum = varY(ObliqCorrNum);
    printf("varYNum:%f\n", varYNum);

    double EqOfTimeNum = EqOfTime(varYNum, GeomMeanLongSunNum, GeomMeanAnomSunNum, EccentEarthOrbitNum);
    printf("EqOfTimeNum:%f\n", EqOfTimeNum);

    double HASunriseNum = HASunrise(latitude, SunDeclinNum);
    printf("HASunriseNum:%f\n", HASunriseNum);

    typANGLE Longitude = {108, 0, 0};
    double SolarNoonNum = SolarNoon(Longitude, 8, EqOfTimeNum);
    printf("SolarNoonNum:%f\n", SolarNoonNum);

    double SunriseTimeNum = SunriseTime(SolarNoonNum, HASunriseNum);
    printf("SunriseTimeNum:%f\n", SunriseTimeNum);

    double SunsetTimeNum = SunsetTime(SolarNoonNum, HASunriseNum);
    printf("SunsetTimeNum:%f\n", SunsetTimeNum);

    double SunlightDurationNum = SunlightDuration(HASunriseNum);
    printf("SunlightDurationNum:%f\n", SunlightDurationNum);

    double TrueSolarTimeNum = TrueSolarTime(time, EqOfTimeNum,longitude, utc);
    printf("TrueSolarTimeNum:%f\n", TrueSolarTimeNum);

    double HourAngleNum = HourAngle(TrueSolarTimeNum);
    printf("HourAngleNum:%f\n", HourAngleNum);

    double SolarZenithAngleNum = SolarZenithAngle(latitude, SunDeclinNum, HourAngleNum);
    printf("SolarZenithAngleNum:%f\n", SolarZenithAngleNum);

    double SolarElevationAngleNum = SolarElevationAngle(SolarZenithAngleNum);
    printf("SolarElevationAngleNum:%f\n", SolarElevationAngleNum);

    double ApproxAtmosphericRefractionNum = ApproxAtmosphericRefraction(SolarElevationAngleNum);
    printf("ApproxAtmosphericRefractionNum:%f\n", ApproxAtmosphericRefractionNum);

    double SolarElevationCorrectedForAtmRefractionNum = SolarElevationCorrectedForAtmRefraction(SolarElevationAngleNum, ApproxAtmosphericRefractionNum);
    printf("SolarElevationCorrectedForAtmRefractionNum:%f\n", SolarElevationCorrectedForAtmRefractionNum);

    double SolarAzimuthAngleNum = SolarAzimuthAngle(latitude, SunDeclinNum, HourAngleNum, SolarZenithAngleNum);
    printf("SolarAzimuthAngleNum:%f\n", SolarAzimuthAngleNum);
}
