#pragma once

enum LerpType { Linear, EaseIn, EaseOut };
typedef float (*LerpFunction)(const float &lerpTime);

namespace LerpFuncts
{
	//Nomenclatura
	//Todos los m�todos que incluyen p_ son privados y no deben ser llamados desde fuera
	//Todos los m�todos que incluten por f_, son LerpFunctions

	inline float p_f_Linear (const float &t)  { return t;     }	 // no easing, no acceleration
	inline float p_f_Flip   (const float &x)  { return 1 - x; }
	inline float p_f_EaseIn (const float &t)  { return t * t; }	 // decelerating to zero velocity
	inline float p_f_EaseOut(const float &t)  { return p_f_Flip(p_f_EaseIn(p_f_Flip(t))); }

	//Devuelve un n�mero entre v0 y v1 en funci�n de t y la funci�n de lerping
	inline float p_CustomLerp(const float &v0, const float &v1, const float &t, LerpFunction function = p_f_Linear) 
	{
		float auxT = function(t);
		return (1 - auxT) * v0 + auxT * v1;
	}

	//Este es el m�todo a llamar para usar el lerping
	inline float Lerp(const float &v0,const float &v1, const float &t, LerpType lerpType = LerpType::EaseOut) 
	{
		switch (lerpType)
		{
			case Linear:	  return p_CustomLerp(v0, v1, t, p_f_Linear);  break;
			case EaseIn:	  return p_CustomLerp(v0, v1, t, p_f_EaseIn);  break;
			case EaseOut:	  return p_CustomLerp(v0, v1, t, p_f_EaseOut); break;
			default:		  throw("No se encontr� la funci�n de lerp");  break;
		}
	}
}

