#pragma once

struct MU_4float
{
	float Red;
	float Green;
	float Blue;
	float Alpha;

	MU_4float()
	{
		
	}

	MU_4float(float red, float green, float blue, float alpha)
	{
		this->Red = red;
		this->Green = green;
		this->Blue = blue;
		this->Alpha = alpha;
	}
	
	void set(float red, float green, float blue, float alpha)
	{
		this->Red = red;
		this->Green = green;
		this->Blue = blue;
		this->Alpha = alpha;
	}
};