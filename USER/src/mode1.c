#include <include.h>



/**
* ����ͼAPI����ϵͳ�Ƚ���ת��;
* WGS84����ϵ������������ϵ��������ͨ�õ�����ϵ���豸һ�����GPSоƬ���߱���оƬ��ȡ�ľ�γ��ΪWGS84��������ϵ,
* �ȸ��ͼ���õ���WGS84��������ϵ���й���Χ���⣩;
* GCJ02����ϵ������������ϵ�������й����Ҳ����ƶ��ĵ�����Ϣϵͳ������ϵͳ����WGS84����ϵ�����ܺ������ϵ��
* �ȸ��й���ͼ�������й���ͼ���õ���GCJ02��������ϵ; BD09����ϵ�����ٶ�����ϵ��GCJ02����ϵ�����ܺ������ϵ;
* �ѹ�����ϵ��ͼ������ϵ�ȣ�����Ҳ����GCJ02�����ϼ��ܶ��ɵġ� chenhua
*�ߵ¹�����GCJ��02����ϵ��������WGS84
*/

/**
* * ��������ϵ (GCJ-02) to 84 * *
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
* Description    : �Ƕ�ת���ɻ���
****************************************************************************** */
static double rad(double d)
{ 
  return d * PI/ 180.0; 
}

/*******************************************************************************
* Function Name  :double GetDistance(double lat1, double lng1, double lat2, double lng2)
* Description    : �����������(γ�ȣ�����)
****************************************************************************** */
double GetDistance(double lat1, double lng1, double lat2, double lng2)
{
double radLat1 = rad(lat1);
double radLat2 = rad(lat2);
double a = radLat1 - radLat2;//����γ��֮��
double b = rad(lng1) - rad(lng2);//����֮��


double s = 2 * asin(sqrt(pow(sin(a/2),2) +
cos(radLat1)*cos(radLat2)*pow(sin(b/2),2)));//�����������Ĺ�ʽ

s = s * EARTH_RADIUS;//�����˵���뾶���뾶Ϊ�ף�
s = llroundl(s*10000) / 10000.0;//��ȷ�������ֵ

//s = double b = ( ( int )( a * 1000000 + 0.5 ) ) / 1000000.0;//round(11111111.21);
//s = s/10000;

return s;
}

