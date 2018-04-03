#include <include.h>



/**
* 各地图API坐标系统比较与转换;
* WGS84坐标系：即地球坐标系，国际上通用的坐标系。设备一般包含GPS芯片或者北斗芯片获取的经纬度为WGS84地理坐标系,
* 谷歌地图采用的是WGS84地理坐标系（中国范围除外）;
* GCJ02坐标系：即火星坐标系，是由中国国家测绘局制订的地理信息系统的坐标系统。由WGS84坐标系经加密后的坐标系。
* 谷歌中国地图和搜搜中国地图采用的是GCJ02地理坐标系; BD09坐标系：即百度坐标系，GCJ02坐标系经加密后的坐标系;
* 搜狗坐标系、图吧坐标系等，估计也是在GCJ02基础上加密而成的。 chenhua
*高德国内是GCJ－02坐标系，国外是WGS84
*/

/**
* * 火星坐标系 (GCJ-02) to 84 * *
* 
* @param lng
* @param lat
* @return Gps
*/
/*
public static Gps gcj02ToGps84(double lng, double lat) {
Gps gps = transform(lng, lat);
double lontitude = lng * 2 - gps.getLng();
double latitude = lat * 2 - gps.getLat();
return new Gps(lontitude, latitude);
}*/
/*******************************************************************************
* Function Name  :static double rad(double d)
* Description    : 角度转换成弧度
****************************************************************************** */
static double rad(double d)
{ 
  return d * PI/ 180.0; 
}

/*******************************************************************************
* Function Name  :double GetDistance(double lat1, double lng1, double lat2, double lng2)
* Description    : 两点间距离测量(纬度，经度)
****************************************************************************** */
double GetDistance(double lat1, double lng1, double lat2, double lng2)
{
double radLat1 = rad(lat1);
double radLat2 = rad(lat2);
double a = radLat1 - radLat2;//两点纬度之差
double b = rad(lng1) - rad(lng2);//经度之差


double s = 2 * asin(sqrt(pow(sin(a/2),2) +
cos(radLat1)*cos(radLat2)*pow(sin(b/2),2)));//计算两点距离的公式

s = s * EARTH_RADIUS;//弧长乘地球半径（半径为米）
s = llroundl(s*10000) / 10000.0;//精确距离的数值

//s = double b = ( ( int )( a * 1000000 + 0.5 ) ) / 1000000.0;//round(11111111.21);
//s = s/10000;

return s;
}

