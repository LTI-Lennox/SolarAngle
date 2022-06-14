//
// Created by LTI-lennox on 2022/6/10.
//

#ifndef SOLARANGLE_SOLARANGLE_H
#define SOLARANGLE_SOLARANGLE_H

/**
 * LST: Local Solar Time 太阳时
 * LT: Local Time 地方时
 * EOT: Equation of Time 时差
 * */

typedef struct {
    int year;
    int month;
    int date;
    int hour;
    int min;
    int sec;
} typTIME;

typedef struct {
    int Angle;
    int min;
    int sec;
} typANGLE;

/** @brief 计算输入日期至1900年1月1日的天数
 * @param time 当前日期  输入范围2000-2099
 * @return time至1900年1月1日的天数
 * */
int dateVlue(typTIME time);
double radians(double Angle);

/**@brief 计算儒略日
 * @param time  当前时间
 * @param utc   当前时区
 * @return 返回儒略日
 * */
double julianDay(typTIME time, int utc);

double julianCentury(double julianDayNum);

double GeomMeanLongSun(double julianCenturyNum);

double GeomMeanAnomSun(double julianCenturyNum);

double EccentEarthOrbit(double julianCenturyNum);

double SunEqOfCtr(double julianCenturyNum, double GeomMeanAnomSunNum);

double SunTrueLong(double GeomMeanLongSunNum, double SunEqOfCtrNum);

double SunTrueAnom(double GeomMeanAnomSunNum, double SunEqOfCtrNum);

double SunRadVector(double EccentEarthOrbitNum, double SunTrueAnomNum);

double SunAppLong(double SunTrueLongNum, double julianCenturyNum);

double MeanObliqEcliptic(double julianCenturyNum);

double ObliqCorr(double MeanObliqEclipticNum, double julianCenturyNum);

double SunRtAscen(double SunAppLongNum, double ObliqCorrNum);

double SunDeclin(double SunAppLongNum, double ObliqCorrNum);

double varY(double ObliqCorrNum);

double EqOfTime(double varYNum, double GeomMeanLongSunNum, double GeomMeanAnomSunNum, double EccentEarthOrbitNum);

double HASunrise(typANGLE Latitude, double SunDeclinNum);

/**@brief Solar Noon (LST)
 * @return x to 24H
 * */
double SolarNoon(typANGLE Longitude, int utc, double EqOfTimeNum);

/**@brief Sunrise Time (LST)
 * @return x to 24H
 * */
double SunriseTime(double SolarNoonNum, double HASunriseNum);

/**@brief Sunset Time (LST)
 * @return x to 24H
 * */
double SunsetTime(double SolarNoonNum, double HASunriseNum);

/**@brief Sunlight Duration
 * @return min
 * */
double SunlightDuration(double HASunriseNum);

/**@brief True Solar Time
 * @return min
 * */
double TrueSolarTime(typTIME time, double EqOfTimeNum, typANGLE Longitude, int utc);

double HourAngle(double TrueSolarTimeNum);

double SolarZenithAngle(typANGLE Latitude, double SunDeclinNum, double HourAngleNum);

double SolarElevationAngle(double SolarZenithAngleNum);

double ApproxAtmosphericRefraction(double SolarElevationAngleNum);

double SolarElevationCorrectedForAtmRefraction(double SolarElevationAngleNum, double ApproxAtmosphericRefractionNum);

/**@brief deg CW from North
 * */
double SolarAzimuthAngle(typANGLE Latitude, double SunDeclinNum, double HourAngleNum, double SolarZenithAngleNum);

#endif //SOLARANGLE_SOLARANGLE_H
