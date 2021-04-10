#pragma once

enum LerpType { Linear, EaseIn, EaseOut };
typedef float (*LerpFunction)(float args);

namespace LerpFuncts
{
	//Nomenclatura
	//Todos los métodos que incluyen p_ son privados y no deben ser llamados desde fuera
	//Todos los métodos que incluten por f_, son LerpFunctions

	inline float p_f_Linear(float t)  { return t;     }	 // no easing, no acceleration
	inline float p_f_Flip(float x)    { return 1 - x; }
	inline float p_f_EaseIn(float t)  { return t * t; }	 // decelerating to zero velocity
	inline float p_f_EaseOut(float t) { return p_f_Flip(p_f_EaseIn(p_f_Flip(t))); }

	/*
	 * Devuelve un número entre v0 y v1 en función de t y la función de lerping
	 */
	inline float p_CustomLerp(float v0, float v1, float t, LerpFunction function = p_f_Linear) 
	{
		t = function(t);
		return (1 - t) * v0 + t * v1;
	}

	/*
	 * Este es el método a llamar para usar el lerping
	 */
	inline float Lerp(float v0, float v1, float t, LerpType lerpType = LerpType::EaseOut) 
	{
		switch (lerpType)
		{
			case Linear:	  return p_CustomLerp(v0, v1, t, p_f_Linear);  break;
			case EaseIn:	  return p_CustomLerp(v0, v1, t, p_f_EaseIn);  break;
			case EaseOut:	  return p_CustomLerp(v0, v1, t, p_f_EaseOut); break;
			default:		  throw("Algo fue mal"); break;
		}
	}
}

